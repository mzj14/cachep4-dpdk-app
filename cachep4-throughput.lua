local dpdk   = require "dpdk"
local memory = require "memory"
local device = require "device"
local stats  = require "stats"

--- set address here
local MAC_1 = "80:00:00:00:00:01"
local MAC_2 = "80:00:00:00:00:02"
local MAC_3 = "80:00:00:00:00:11"
local MAC_4 = "80:00:00:00:00:12"
local IP_1 = "192.168.0.2"
local IP_2 = "192.168.1.2"

function master(name)
    local p0 = device.config(0)
    local p1 = device.config(1)
    -- local p2 = device.config(2)
    -- local p3 = device.config(3)

    p0:wait()
    p1:wait()
    -- p2:wait()
    -- p3:wait()

    stats.startStatsTask({p0})
    stats.startStatsTask({p1})
    -- stats.startStatsTask({p2})
    -- stats.startStatsTask({p3})

    dpdk.sleepMillis(100) -- make sure the burst thread starts first

    dpdk.launchLua("loadSlave", 0, MAC_2, MAC_1, IP_1, IP_2)
    -- dpdk.launchLua("loadSlave", 1, "10.0.0.1")
    -- dpdk.launchLua("loadSlave", 2, "10.0.0.4")
    -- dpdk.launchLua("loadSlave", 3, "10.0.0.3")

    dpdk.waitForSlaves()
end



function loadSlave(port, srcMac, dstMac, srcIP, dstIP)
	local queue = device.get(port):getTxQueue(0)
        queue:setRate(1000)
	local mem = memory.createMemPool(function(buf)
	    buf:getUdpPacket():fill{
                ethSrc = srcMac,
                ethDst = dstMac,
                ip4Src = srcIP,
                ip4Dst = dstIP,
                udpSrc = 8000,
                udpDst = 8000,
                pktLength = 256
        }
	end)

	local bufs = mem:bufArray()
	while dpdk.running() do
		bufs:alloc(64)
		queue:send(bufs)
	end
end
