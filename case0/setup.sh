#! /bin/bash
sudo ip netns add h1
sudo ip netns add h2

sudo ip netns exec h1 ifconfig lo up
sudo ip netns exec h2 ifconfig lo up

sudo ip link set em1 netns h1
sudo ip link set em2 netns h2

sudo ip netns exec h1 ifconfig em1 hw ether 800000000002
sudo ip netns exec h2 ifconfig em2 hw ether 800000000012

sudo ip netns exec h1 ifconfig em1 192.168.0.2/24 up
sudo ip netns exec h2 ifconfig em2 192.168.1.2/24 up

sudo ip netns exec h1 route add default gw 192.168.0.1
sudo ip netns exec h2 route add default gw 192.168.1.1

sudo ip netns exec h1 arp -s 192.168.0.1 80:00:00:00:00:01
sudo ip netns exec h2 arp -s 192.168.1.1 80:00:00:00:00:11

