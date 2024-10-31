# nDPI

# 目录

# nDPI快速上手指南

参考：

- [nDPI快速上手指南](https://blog.csdn.net/banruoju/article/details/78806533) 或 [nDPI – 快速入门指南(翻译自官方文档)](https://blog.csdn.net/A_lber_t/article/details/89552332)，这两篇其实都是对官方文档的一个润色翻译，我综合着来看
  - nDPI官方文档 [nDPI- Quick Start Guide](https://github.com/ntop/nDPI/blob/dev/doc/guide/nDPI_QuickStartGuide.pdf) 

这是一篇针对nDPI官方文档 [nDPI- Quick Start Guide](https://github.com/ntop/nDPI/blob/dev/doc/guide/nDPI_QuickStartGuide.pdf) 的翻译，由于文档太老了(13年)，所以部分接口已经发生了变化，本人将基于Version2.0对这些过时的接口进行更新。由于水平有限，翻译的、修补的内容不保证一定准确，各位最好上手之后对照源码细读一遍吧。

## 介绍

nDPI是一个从OpenDPI发展而来的DPI库，现在由ntop组织负责维护。

为了给你提供一个跨平台DPI的体验，nDPI除了支持Unix平台，还支持Windows(和Mac)。为了使nDPI更加适合应用于流量监控，我们将会持续进行优化，比如一旦发现存在对网络流量监控非必须的、却拖慢了DPI引擎的功能时，可以执行关闭。

不管使用了哪个端口，nDPI都可以探测到实际的应用层协议。这意味着既可以探测运行在非标准端口上的协议(e.g探测运行在非80端口上的http流量)，又可以探测运行在一个标准端口上的其他协议(e.g探测运行在80端口上的Skype流量)。这是因为现在端口跟协议关联的概念已经被打破。


在过去的几个月里，我们已经为nDPI增加了以下多个功能：

- 一个名为ndpiReader的增强型demo
- 可以被编译进kernel成为一个模块，使其更加高效
- 从各方面提升了识别速度，目前nDPI在这方面已经远远超过了前代的OpenDPI
- 新增了大量的协议支持(目前为止已经支持超过180种协议)，覆盖范围从商业类协议(如SAP和Citrix)到桌面协议(如Dropbox和Spotify)
- 可以定义基于端口(端口范围)的协议探测，丰富了传统的仅仅基于端口的探测手段
- 为了使nDPI支持探测加密连接，我们增加一个用于SSL的解码器(同时支持客户端和服务端)，用以找出那些使用了加密证书的协议。这使我们可以识别那些以前无法探测到的协议，比如Citrix和AppleiCloud等
- 通过基于额外的一些字符串匹配方式，我们可以支持识别一些常见的应用子协议

## nDPI库编译与运行

在你搭建ntop和nProbe的过程中nDPI就会自动被下载。也可以作为一个独立的DPI库来使用，源代码可以通过gitclone https://github.com/ntop/nDPI.git下载

nDPI库

### 编译 nDPI 源代码

使用nDPI库很简单。编译这个库时需要依赖以下这些工具和组件：

- GNUautotools/libtool
- gawk
- gcc
- libpcap 或 PF_RING (虽然是可选的，但非常建议装上)

安装方式跟平台以及发行版相关，这里列举了一些：

```bash
# Ubuntu/Debian
$ apt-get install build-essential
$ apt-get install git autoconf automake autogen libpcap-dev libtool

# Fedora/CentOS
$ yum groupinstall "Development tools"
$ yum install git autoconf automake autogen libpcap-devel libtool

# MacOSX(using http://brew.sh)
$ brew install autoconf automake libtool git

# FreeBSD
$ pkg install autoconf automake libtool gmake git
```

在装完了依赖的工具之后，你就可以通过以下这组命令来编译nDPI了：

```bash
$ ./autogen.sh
$ make
```

### 编译示例程序 —— ndpiReader

Version2.0版本在工程目录下执行make时，默认就编译了example目录下的ndpiReader

#### ndpiReader 的命令行选项

以下列出了该demo程序的有效选项以及对应的简单解释

```bash
$ ./ndpiReader -h
ndpiReader-i <file|device> [-f <filter>][-s ][-m<duration>]
[-p<protos>][-l  [-q][-d][-h][-t][-v ]
[-n<threads>] [-w <file>] [-j <file>]

# Usage:
-i<file.pcap|device>                   |指定一个需要被识别的pcap文件/文件列表，或者需要被嗅探的
                                                   |设备接口/接口列表(文件列表或接口列表使用","作为分隔符)
-f<BPF filter>                            |指定一条BPF规则的过滤字串
-s<duration>                             |最大的嗅探时间(显然只在嗅探接口时生效)
-m<duration>                            | pcap文件分段解析超时时间(显然只在解析pcap文件时生效)
-p<file>.protos                          |指定一个自定义的协议识别配置文件(eg.protos.txt)
-l<num loops>                           |指定循环执行嗅探的次数(仅用于测试)
-n<num threads>                       |指定线程数量，缺省跟设备接口数量对应
                                                   |如果传入的是pcap文件时固定使用单线程
-j<file.json>                               |指定一个输出包内容的json文件
-g<id:id...>                                |指定线程-CPU亲和关系映射表
-d                                              |禁止协议猜测功能
-q                                              |安静模式，意味着不打印信息
-t                                               |解析GTP隧道协议
-r                                               |打印 nDPI版本和git版本
-w<path>                                  |指定测试信息的输出文件
-h                                              | help信息
-v<1|2|3>                                  |按级别进一步打印包的详细信息，分为1、2、3级
```

### 协议文件

**通过基于字符串的匹配方式**，nDPI可以支持识别应用层的子协议。这是因为存在很多像 AppleiCloud/iMessage, WhatsApp 等新出现的子协议，以及其他使用http(s)的协议，这些协议可以通过解码主机SSL证书或http头中的"Host"字段而被识别。

因此我们决定将一个基于流行的Aho-Corasick 算法的高效字符匹配库嵌入到nDPI中，用于数十万子字符的高效匹配（即在普通硬件上能足够快地支持10Gb的流量）。

通过使用一个协议文件，你可以在运行时设置自定义的子协议，格式如下：

```bash
# Subprotocols
# Format:
# host:"<value>",host:"<value>",.....@<subproto>
host:"googlesyndication.com"@Google
host:"venere.com"@Venere
host:"kataweb.it",host:"repubblica.it"@Repubblica
host:"ntop"@ntop
```

你还可以配置基于IP的子协议，格式如下：

```bash
# IP based Subprotocols
# Format:
# ip:<value>,ip:<value>,.....@<subproto>
ip:213.75.170.11@CustomProtocol
```

你还可以配置基于端口的子协议，格式如下：

```bash
# Format:
# <tcp|udp>:<port>,<tcp|udp>:<port>,.....@<proto>
tcp:81,tcp:8181@HTTP
udp:5061-5062@SIP
tcp:860,udp:860,tcp:3260,udp:3260@iSCSI
tcp:3000@ntop
```

只需要在运行 ndpiReader 时加上使用 “-p” 选项，就可以测试你自定义的配置协议了。当然你也可以通过在你的程序中调用nDPI的API `ndpi_load_protocols_file()` 来测试你的配置。

## 示例 —— ndpiReader程序

这节中我们将展示一些demo程序 ndpiReader 的使用范例。

### 现场捕获模式

下面这个例子展示了ndpiReader的现场捕获模式，其中“-i”选项用来指定需要进行嗅探的设备接口，“-s” 选项指定了嗅探的时间。

```bash
$sudo ./ndpiReader -i eth0 -s 20
-----------------------------------------------------------
*NOTE: This is demo app to show *some* nDPI features.
*In this demo we have implemented only some basic features
*just to show you what you can do with the library. Feel
*free to extend it and send us the patches for inclusion
------------------------------------------------------------
UsingnDPI (2.0.0-838-6607c33) [1 thread(s)]
Capturinglive traffic from device eth0...
Capturingtraffic up to 5 seconds
Runningthread 0...

nDPIMemory statistics:
nDPIMemory (once): 93.13 KB
FlowMemory (per flow): 1.25 KB
ActualMemory: 1.49 MB
PeakMemory: 1.49 MB
Trafficstatistics:
Ethernetbytes: 80367 (includes ethernet CRC/IFC/trailer)
Discardedbytes: 1200
IPpackets: 236 of 256 packets total
IPbytes: 74703 (avg pkt size 291 bytes)
Uniqueflows: 165
TCPPackets: 0
UDPPackets: 230
VLANPackets: 4
MPLSPackets: 0
PPPoEPackets: 0
FragmentedPackets: 0
MaxPacket size: 328
PacketLen < 64: 28
PacketLen 64-128: 9
PacketLen 128-256: 6
PacketLen 256-1024: 193
PacketLen 1024-1500: 0
PacketLen > 1500: 0
nDPIthroughput: 47.22 pps / 125.62 Kb/sec
Analysisbegin: 01/Jan/1970 08:00:00
Analysisend: 01/Jan/1970 08:00:00
Trafficthroughput: 47.22 pps / 125.62 Kb/sec
Trafficduration: 4.998 sec
Guessedflow protos: 1
Detectedprotocols:
Unknown packets: 194 bytes: 69976 flows: 143
NetBIOS packets: 19 bytes: 2116 flows: 8
SSDP packets: 2 bytes: 416 flows: 2
IGMP packets: 2 bytes: 120 flows: 2
ICMPV6 packets: 4 bytes: 344 flows: 1
DHCPV6 packets: 3 bytes: 455 flows: 3
LLMNR packets: 10 bytes: 760 flows: 5
Cloudflare packets: 2 bytes: 516 flows: 1
Protocolstatistics:
Acceptable 4727 bytes
Unrated 69976 bytes
```

### 文件捕获模式

最简单的创建一个pcap文件的方法是使用tcpdump命令，就像下面这个例子一项：

```bash
$sudo tcpdump -i eth0 -w /var/tmp/capture.pcap -v
tcpdump:listening on eth0, link-type EN10MB (Ethernet), capture size 262144bytes
^C248packets captured
252packets received by filter
0packets dropped by kernel
```

一旦pcap文件被创建，你就可以像下面这样运行ndpiReader：

```bash
$sudo ./ndpiReader -i /var/tmp/capture.pcap
-----------------------------------------------------------
*NOTE: This is demo app to show *some* nDPI features.
*In this demo we have implemented only some basic features
*just to show you what you can do with the library. Feel
*free to extend it and send us the patches for inclusion
------------------------------------------------------------
UsingnDPI (2.0.0-838-6607c33) [1 thread(s)]
Capturinglive traffic from device eth0...
Capturingtraffic up to 5 seconds
Runningthread 0...
nDPIMemory statistics:
nDPIMemory (once): 93.13 KB
FlowMemory (per flow): 1.25 KB
ActualMemory: 1.49 MB
PeakMemory: 1.49 MB

Trafficstatistics:
Ethernetbytes: 80650 (includes ethernet CRC/IFC/trailer)
Discardedbytes: 1020
IPpackets: 231 of 248 packets total
IPbytes: 75106 (avg pkt size 302 bytes)
Uniqueflows: 164
TCPPackets: 2
UDPPackets: 227
VLANPackets: 1
MPLSPackets: 0
PPPoEPackets: 0
FragmentedPackets: 0
MaxPacket size: 328
PacketLen < 64: 19
PacketLen 64-128: 6
PacketLen 128-256: 13
PacketLen 256-1024: 193
PacketLen 1024-1500: 0
PacketLen > 1500: 0
nDPIthroughput: 155.03 K pps / 412.96 Mb/sec
Analysisbegin: 14/Dec/2017 15:37:39
Analysisend: 14/Dec/2017 15:37:44
Trafficthroughput: 49.59 pps / 135.25 Kb/sec
Trafficduration: 4.659 sec
Guessedflow protos: 0

Detectedprotocols:
Unknown packets: 200 bytes: 71136 flows: 146
MDNS packets: 6 bytes: 1197 flows: 3
NetBIOS packets: 6 bytes: 552 flows: 3
SSDP packets: 3 bytes: 624 flows: 2
ICMPV6 packets: 1 bytes: 86 flows: 1
DHCPV6 packets: 5 bytes: 761 flows: 5
LLMNR packets: 10 bytes: 750 flows: 4

Protocolstatistics:
Acceptable 3970 bytes
Unrated 71136 bytes
```

### 协议文件

为了阐述清楚协议文件的作用，我们现在就来讲解如何识别ntop.org的流量。

可以像下面这样编辑protos.txt.

```bash
$echo 'host:"ntop.org"@nTop' > protos.txt
```

修改完协议文件之后，你就可以像下面这样运行ndpiReader：

```bash
$sudo ./ndpiReader -i eth0 -s 30 -p ./protos.txt
```

## API nDPI

这节中高亮的就是nDPI的API。

这节中将ndpiReader作为一个基本范例来展示如何初始化nDPI库。首先需要一个编译完成的库以及一个合适的Makefile (i.e就像ndpiReader的Makefile那样)

为了在你的程序中使用nDPI的API，你除了要include自己的头文件外，还需要添加类似下面这一行：

```bash
#include<ndpi/ndpi_main.h>
```

库可以按照下面的顺序执行初始化：

### (1) 创建并初始化一个nDPI核心库探测模块

```c
structndpi_detection_module_struct * module =ndpi_init_detection_module();
```

备注：本API格式在Version2.0版本中较之前版本差异很大。

这个探测模块中维护了所有支持的协议。

本API只是注册了所有支持的协议，但并未使能其中任何一个协议

### (2) ndpiReader接下来通过一些宏使能了探测模块中的所有协议(显然你可以根据自己的需求来决定使能哪些协议)

```c
/**
 * @param ndpi_struct 指向当前操作的探测模块
 * @param dbm 调用者实际通过该集合来控制实际需要应用的协议，只有该字段中被置1的对应协议，其协议分析器才真正允许被加载
 */
NDPI_BITMASK_SET_ALL(all);
ndpi_set_protocol_detection_bitmask2(
    structndpi_detection_module_struct *ndpi_struct,
    constNDPI_PROTOCOL_BITMASK * dbm
);
```

备注：本API的作用就是使能一个已经初始化的nDPI核心库探测模块中的协议

### (3) 为了导入已经存在的协议文件，你还必须调用下面的API

```c
/*
 * @param ndpi_mod 指向当前操作的探测模块
 * @param path 协议文件的路径
 */
ndpi_load_protocols_file(structndpi_detection_module_struct *ndpi_mod, char* path);
```

### (4) 一旦从你的pcap文件或设备接口上捕获到了数据流，就可以调用下面的API来进行分析

```c
/**
 * @param
 *     ndpi_struct 指向传入包所属的探测模块
 *     ndpi_flow 指向传入包所属的数据流
 *     packet 指向传入包的IP头
 *     packetlen IP包的长度
 *     current_tick_l 收到该IP包的时间(ms)
 *     src 指向源用户状态机
 *     dst 指向目的用户状态机
 */
ndpi_protocolndpi_detection_process_packet(
    structndpi_detection_module_struct *ndpi_struct,
    structndpi_flow_struct *flow,
    constunsigned char *packet,
    constunsigned short packetlen,
    constu_int64_t current_tick_l,
    structndpi_id_struct *src,
    structndpi_id_struct *dst
)
```

备注：本API是ndpi核心库处理收到包的入口，通过分析传入的IP包，完成数据流的识别，最后返回是别结果

如果想了解更深入的信息，我们建议你阅读下面这些文件：

- nDPI/example/pcapReader.c
- nDPI/src/include/ndpi_structs.h
- nDPI/src/include/ndpi_public_functions.h
- nDPI/src/ndpi_main.c


具体的协议解析器文件都被放在 nDPI/src/protocols 文件夹中。

## 开发nDPI自定义协议

在这一节中，我们将展示将你的协议包含在nDPI中的方法。

### 介绍

每个nDPI协议都会作为一个入口函数被实现，在运行时通过nDPI被使用。nDPI有几个协议可以被用来当作这个方面的例子。下面，我们列出了一些主要的概念，如果你打算开发一个nDPI协议，这些是你必须知道的。

### 创建新的协议

每一个协议都必须在下面的头文件中有一个对应的#define：

```c
<nDPI source code directory>/src/include/ndpi_protocols_osdpi.h
```

例如：

```c
#define NDPI_PROTOCOL_MY_PROTOCOL     171
// NDPI_PROTOCOL_MY_PROTOCOL是这个协议的名字，171是这个协议的ID，且必须是独一无二的。
```

协议被定义好了之后，你必须创建一个协议源文件，就像：

```c
<nDPI source code direcotry>/src/lib/protocols/my_protocol.c
```

包括以下内容

```c
#include "ndpi_utils.h"
#ifdef NDPI_PROTOCOL_MY_PROTOCOLS
……
#endif
```

在里面，需要定义一个入口函数，如：

```c
void ndpi_search_my_protocol(
	struct ndpi_detection_module_struct *ndpi_struct,
    struct ndpi_flow_struct *flow
){
    struct ndpi_packet_struct *packet = &flow->packet;
    NDPI_LOG(NDPI_PROTOCOL_MY_PROTOCOL, ndpi_struct, NDPI_LOG_DEBUG, "my protocol detection...\n");
    
    // skip marked packets by checking if the detection protocol stack
    if (packet->detected_protocol_stack[0] ！= NDPI_PROTOCOL_MY_PROTOCOL){
        ndpi_check_my_protocol(ndpi_struct, flow);
    }
}
```

和一个检测核心函数，用来处理一个流的数据包，包括以下内容：

```c
static void ndpi check my protocol(
	struct ndpi detection module struct *ndpi struct,
	struct ndpi flow struct *flow
){
	struct ndpi packet struct *packet = &flow->packet;
	u int32 t payload len = packet->payload packet len;
	.....
	.....
	if("Found Protocol"){
		NDPI LOG(NDPI PROTOCOL MY PROTOCOL, ndpi struct, NDPI LOG DEBUG，"Found my protocol.\n");
		ndpi int my_protocol add connection(ndpi struct，flow);
		return;
    }
    
	/*Exclude Protocol*/
	NDPI LOG(NDPI PROTOCOL MY PROTOCOL, ndpi struct，NDPI LOG DEBUG, "exclude my protocol.\n");
	NDPI ADD PROTOCOL TO BITMASK(
		flow->excluded protocol bitmask,
		NDPI PROTOCOL MY PROTOCOL
    );
}
```

和一个特定的函数用来报告关于协议正确的识别信息，如：

```c
static void ndpi int my protocol add connection(
	struct ndpi detection module struct *ndpi struct,
	struct ndpi flow struct *flow,
	u_int8_t due to correlation
){
	ndpi int add connection(ndpi struct, flow, NDPI PROTOCOL MY PROTOCOL, 
		/*Choose the type of your protocol*/
		NDPI_CORRELATED_PROTOCOL or NDPI_REAL_PROTOCOL
	);
}
```

### 添加你的协议到nDPI

协议被创建之后，你必须在下面的头文件中声明你的入口函数：

```c
<nDPI source code directory>/src/include/ndpi_protocols.h
```

包括如下内容：

```c
/* my protocol entry */
void ndpi search my protocol(
	struct ndpi detection module struct *ndpi struct,
	struct ndpi flow struct *flow);
```

每个协议必须与一个NDPI_SELECTION_BITMASK相关联。NDPI_SELECTION_BITMASK的完整列表被包含在文件：

```c
<nDPI source code directory>/src/include/ndpi_define.h
```

在为你的协议选择了一个确定的位掩码之后，你必须通知nDPI新协议的存在，通过编辑文件：

```c
<nDPI source code directory>/src/lib/ndpi_main.h
```

你需要将你的协议添加到如下函数中：

```c
void ndpi set protocol detection bitmask2(
	struct ndpi detection module struct *ndpi struct,
	const NDPI PROTOCOL BITMASK * dbm)
......
......
......
#ifdef NDPI PROTOCOL MY PROTOCOL
	ndpi set bitmask protocol detection(ndpi struct, detection bitmask, a,
                                    	NDPI PROTOCOL MY PROTOCOL,
                                    	ndpi search my protoco1,
                                    	NDPI SELECTION BITMASK MY PROTOCOL,
                                    	SAVE DETECTION BITMASK AS UNKNOW,
                                    	ADD TO DETECTION BITMASK);
	/* 更新回调缓冲区索引 */
	a++;
#endif
ndpi struct->callback buffer size = a;
NDPI LOG(NDPI PROTOCOL UNKNOWN，ndpi struct，NDPI LOG DEBUG,
         "callback buffer size is u\n", ndpi struct->callback buffer size);
```





















