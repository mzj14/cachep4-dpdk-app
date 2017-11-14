local mg     = require "moongen"
local memory = require "memory"
local device = require "device"
local ts     = require "timestamping"
local filter = require "filter"
local hist   = require "histogram"
local stats  = require "stats"
local timer  = require "timer"
local arp    = require "proto.arp"
local log    = require "log"

-- set addresses here
local SRC_MAC           = "80:00:00:00:00:02"
local DST_MAC		= "80:00:00:00:00:01"
local SRC_IP	        = "192.168.0.2"
local DST_IP		= "192.168.1.2"
local SRC_PORT		= 8000
local DST_PORT		= 8000

local PKT_TOTAL_NUM     = 10^5

function configure(parser)
	parser:description("Generates UDP traffic and measure latencies. Edit the source to modify constants like IPs.")
	parser:argument("txDev", "Device to transmit from."):convert(tonumber)
	parser:argument("rxDev", "Device to receive from."):convert(tonumber)
	parser:option("-r --rate", "Transmit rate in Mbit/s."):default(10000):convert(tonumber)
        parser:option("-f --file", "CSV file name."):convert(tostring)
        parser:option("-f --flows", "Number of flows (randomized source IP)."):default(0):convert(tonumber)
	parser:option("-s --size", "Packet size."):default(84):convert(tonumber)
end

function master(args)
	txDev = device.config{port = args.txDev, rxQueues = 2, txQueues = 2}
	rxDev = device.config{port = args.rxDev, rxQueues = 2, txQueues = 2}
	device.waitForLinks()
        txDev:getTxQueue(0):setRate(args.rate)
	mg.startTask("loadSlave", txDev:getTxQueue(0), rxDev, args.size)
	mg.startTask("timerSlave", txDev:getTxQueue(1), rxDev:getRxQueue(1), args.size, args.file)
	mg.waitForTasks()
end

local function fillUdpPacket(buf, len)
	buf:getUdpPacket():fill{
		ethSrc = SRC_MAC,
		ethDst = DST_MAC,
		ip4Src = SRC_IP,
		ip4Dst = DST_IP,
		udpSrc = SRC_PORT,
		udpDst = DST_PORT,
                pktLength = len
	}
end

function loadSlave(queue, rxDev, size)
	local mempool = memory.createMemPool(function(buf)
		fillUdpPacket(buf, size)
	end)
	local bufs = mempool:bufArray()
	local txCtr = stats:newDevTxCounter(queue, "plain")
	local rxCtr = stats:newDevRxCounter(rxDev, "plain")
	while mg.running() do
		bufs:alloc(size)
                bufs:offloadIPChecksums()
		bufs:offloadUdpChecksums()
		queue:send(bufs)
		txCtr:update()
		rxCtr:update()
	end
	txCtr:finalize()
	rxCtr:finalize()
end

function timerSlave(txQueue, rxQueue, size, file)
	if size < 84 then
		log:warn("Packet size %d is smaller than minimum timestamp size 84. Timestamped packets will be larger than load packets.", size)
		size = 84
	end
	local timestamper = ts:newUdpTimestamper(txQueue, rxQueue)
	local hist = hist:new()
	mg.sleepMillis(1000) -- ensure that the load task is running
	local counter = 0
	local rateLimit = timer:new(0.001)
	while counter < PKT_TOTAL_NUM and mg.running() do
		hist:update(timestamper:measureLatency(size, function(buf)
			fillUdpPacket(buf, size)
		end))
		rateLimit:wait()
		rateLimit:reset()
                counter = counter + 1;
	end
	-- print the latency stats after all the other stuff
	mg.sleepMillis(300)
	hist:print()
	hist:save(file..".csv")
end

