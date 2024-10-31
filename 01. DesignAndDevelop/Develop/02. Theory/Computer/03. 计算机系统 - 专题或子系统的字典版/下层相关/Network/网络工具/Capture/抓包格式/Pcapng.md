# Pcapng

Pcapng是Pcap格式的扩展，需要先看Pcap笔记或属性Pcap格式后再来看该篇笔记

参考：

- [网络分析笔记01：pcapng格式的整体解包](https://snmplink.blog.csdn.net/article/details/126419291)（使用allow copy插件复制）
- [pcapng 报文头格式分析](https://zhuanlan.zhihu.com/p/653256520)

## 前言

本文首先介绍对pcapng格式进行介绍，然后讲解pcapng的整体结构，并使用Python语言进行块（block）的解包。

在此需要说明的是，本文是为了能够深入对pcapng格式进行分析，所以不使用python的**scapy**库。

## pcapng文件

对网络传输数据进行处理，需使用专用的抓包工具，例如WireShark等，对于抓包后的数据进行分析，就需要用到一些专用的数据格式，pcapng就是其中广为使用的一种。我们先对其进行简要介绍。

### 1、pcapng概述

网络上的数据是以流的方式进行数据传输的，我们从网络上抓包后，需要进行数据分析，所以需要对数据进行存储，pcapng就是用于存储的格式。

pcnpng来源于IETF（互联网工程工作组），是pcap的新一代格式，相比较于原有的pcap格式，更具有逻辑性和可扩展性。

### 2、特点

1. 支持从多接口捕获
   - pcapng允许捕获文件使用“接口描述块”定义多个接口。 每个包都可以与特定的接口相关联。
2. 提高时间戳分辨率
   - pcap的时间戳分辨率是微秒，pcapng的时间戳是一个64位数，表示自1970年1月1日以来的时间单位数量。
3. 可以嵌入注释信息
   - pcapng允许在捕获文件中嵌入注释信息。
4. 可嵌入额外数据
   - 使用pcapng，接口描述块允许描述字段、操作系统字段和过滤器字段，这些字段可以提供捕获源的额外细节。
5. 可扩展文件格式
   - 该格式部署了一个通用的块结构，该结构允许工具忽略未理解的块。 这允许格式随着时间的推移而演进。 特定的块是为接口和包定义的。 额外的元数据可以存储在可选块中。

## 块（block）结构

pcapng由各种block组成，其结构描述如下：

```bash
       0               1               2               3
       0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    0 |                      Block Type (块类型)                       |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    4 |                  Block Total Length (块长度)                   |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    8 |                  Block Body (块内容) 对齐32位                   |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   12 |                  Block Total Length (块长度)                   |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

字段含义

1. 块类型，block type
   - 不同类型的块有不同的类型值。
2. 块长度，block total length
   - 块的总长度，单位字节，
   - block body的长度 = block total length - 12
3. 块内容，block body
   - 4字节对齐
4. 块长度，block total length
   - 重复长度

## block的类型

主要块类型如下

|            | 类型           | 说明                                                         |
| ---------- | -------------- | ------------------------------------------------------------ |
| 0x0A0D0D0A | 节标题块       | 它标识捕获转储文件的一部分的开头。节头块不包含数据，但它标识逻辑相关的块（接口、数据包）列表 |
| 0x00000001 | 接口描述块     | 用于描述指定进行捕获的网络接口的特征                         |
| 0x00000006 | 增强型数据包块 | 增强型数据包块是用于存储来自网络的数据包的标准容器           |
| 0x00000003 | 简单数据包块   | 简单数据包块是一个轻量级容器，用于存储来自网络的数据包       |
| 0x00000004 | 名称解析块     | 名称解析块用于支持数字地址（存在于捕获的数据包中）与其相应的规范名称的相关性 |
| 0x00000005 | 接口统计块     | 接口统计数据块包含给定接口的捕获统计数据                     |

### 节头块 (Section Header Block）

0x0A0D0D0A

节头块是强制性的，它确定了捕获转储文件的一节的开头。节头块不包含数据，而是标识了逻辑上相关的块（接口块，数据块）列表。

节标题块是.pcapng 文件类型标识，定义信息

| 块类型       | 4字节    | 0x0A0D0D0A                                            |
| ------------ | -------- | ----------------------------------------------------- |
| 块长度       | 4字节    | 块类型到选项长度                                      |
| 块的数据顺序 | 4字节    | 大端或者小端模式,0x4D3C2B1A为小端，0x1A2B3C4D为大端。 |
| 版本信息     | 4字节    | 主版本和次版本                                        |
| 下一块长度   | 8字节    | 指定后续块的字，-1代表未指定后续块的大小              |
| 选项         | 可变字节 | 根据块总长度确定可变选项                              |

### 接口描述块 (Interface Description Block）

0x00000001

接口描述块是强制性的。该块被用来指定进行捕获的网络接口的特性。 为了把捕获的数据关联到相应的接口，该接口描述块必须在使用它的任何其它块之前定义; 因此，此块通常会紧跟着节头块放置。 一个接口描述块只在其所在的一节内有效的。

| 块类型   | 4字节    | 0x00000001                                                   |
| -------- | -------- | ------------------------------------------------------------ |
| 块长度   | 4字节    | 块类型到选项长度                                             |
| 链接类型 | 4字节    | 定义该接口的链路层类型的值。1代表以太网。                    |
| SnapLen  | 4字节    | 从每个数据包转储的最大字节数。每个数据包超过此值的部分将不会存储在文件中。 |
| 选项     | 可变字节 | 根据块总长度确定可变选项                                     |

（1）、选项：由Option Type（2字节）+选项长度（2 个字节）+选项值（可变长度）组成

Option Type（2字节）：包含指定当前TLV记录类型的代码。

选项长度（2 个字节）：它包含以下“选项值”字段的实际长度，不包含填充字节。

选项值（可变长度）：它包含给定选项的值，与 32 位边界对齐。该字段的实际长度（即没有填充字节）由选项长度字段指定。

| 名称           | 类型的代码 | 长度     | 描述                                                         | 案列                                                         |
| -------------- | ---------- | -------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| if_name        | 2          | Variable | A UTF-8 string containing the name of the device used to capture data. | "eth0" / "\Device\NPF_{AD1CE675-96D0-47C5-ADD0-2504B9126B68}" / ... |
| if_description | 3          | Variable | A UTF-8 string containing the description of the device used to capture data. | "Broadcom NetXtreme" / "First Ethernet Interface" / ...      |
| if_IPv4addr    | 4          | 8        | Interface network address and netmask. This option can be repeated multiple times within the same Interface Description Block when multiple IPv4  addresses are assigned to the interface. | 192 168 1 1 255 255 255 0                                    |
| if_IPv6addr    | 5          | 17       | Interface network address and prefix length (stored in the last byte). This  option can be repeated multiple times within the same Interface  Description Block when multiple IPv6 addresses are assigned to the  interface. | 2001:0db8:85a3:08d3:1319:8a2e:0370:7344/64 is written (in hex) as "20 01 0d b8 85 a3 08 d3 13 19 8a 2e 03 70 73 44 40" |
| if_MACaddr     | 6          | 6        | Interface Hardware MAC address (48 bits).                    | 00 01 02 03 04 05                                            |
| if_EUIaddr     | 7          | 8        | Interface Hardware EUI address (64 bits), if available.      | TODO: give a good example                                    |
| if_speed       | 8          | 8        | Interface speed (in bps).                                    | 100000000 for 100Mbps                                        |
| if_tsresol     | 9          | 1        | Resolution of timestamps. If the Most Significant Bit is equal to zero, the  remaining bits indicates the resolution of the timestamp as as a  negative power of 10 (e.g. 6 means microsecond resolution, timestamps  are the number of microseconds since 1/1/1970). If the Most Significant  Bit is equal to one, the remaining bits indicates the resolution as as  negative power of 2 (e.g. 10 means 1/1024 of second). If this option is  not present, a resolution of 10^-6 is assumed (i.e. timestamps have the  same resolution of the standard 'libpcap' timestamps). | 6                                                            |
| if_tzone       | 10         | 4        | Time zone for GMT support (TODO: specify better).            | TODO: give a good example                                    |
| if_filter      | 11         | variable | The filter (e.g. "capture only TCP traffic") used to capture traffic. The  first byte of the Option Data keeps a code of the filter used (e.g. if  this is a libpcap string, or BPF bytecode, and more). More details about this format will be presented in Appendix XXX (TODO). (TODO: better use different options for different fields? e.g. if_filter_pcap,  if_filter_bpf, ...) | 00 "tcp port 23 and host 10.0.0.5"                           |
| if_os          | 12         | variable | A UTF-8 string containing the name of the operating system of the machine in which this interface is installed. This can be different from the  same information that can be contained by the Section Header Block  (Section 3.1) because the capture can have been done on a remote  machine. | "Windows XP SP2" / "openSUSE 10.2" / ...                     |
| if_fcslen      | 13         | 1        | An integer value that specified the length of the Frame Check Sequence (in bits) for this interface. For link layers whose FCS length can change  during time, the Packet Block Flags Word can be used (see Appendix A). | 4                                                            |
| if_tsoffset    | 14         | 8        | A 64 bits integer value that specifies an offset (in seconds) that must  be added to the timestamp of each packet to obtain the absolute  timestamp of a packet. If the option is missing, the timestamps stored  in the packet must be considered absolute timestamps. The time zone of  the offset can be specified with the option if_tzone. TODO: won't a  if_tsoffset_low for fractional second offsets be useful for highly  syncronized capture systems? | 1234                                                         |

### 分组块 (Packet Block）

0x00000002

过时，使用增强分组块代替，

### 简单分组块 (Simple Packet Block）

0x00000003

简单分组块是可选的，用于存储来自网络的分组的轻量级容器。

简单分组块类似于分组块（见第3.5节），但它更小、处理起来更简单，只包含了一组最小信息集合。当性能或占用空间是关键因素时，这个块将优先于标准分组块被使用，如在持续流量转储应用程序。一个捕获文件可以同时包含分组块和简单的数据包块：例如硬件资源成为瓶颈时，捕捉工具可以从分组块切换到简单分组块。

### 名称解析块 (Name Resolution Block

0x00000004

名称解析块用来把数字地址（存在于捕获的数据包）及其相应的规范名称关联起来，这是可选的。通过在文件中保存名称，这可以防止名称解析中的延迟时间。名称解析块避免了在跟踪捕获文件时发出大量的DNS的请求，并且允许在未联网的计算机上读取捕获数据时进行名称解析。

### 接口统计块 (Interface Statistics Block）

0x00000005

接口统计块是可选的，它包含给定接口的捕获统计信息。在当前节（Section）中，接口相关的统计信息被接口ID字段中标识的接口引用。接口统计块通常被放置在该文件的末尾，但是没有明确要求关于其放置位置 - 它甚至可以出现多次对相同的接口。

### 增强分组块 (Enhanced Packet Block）

0x00000006

一个增强分组块是用来存储来自网络的数据包的标准容器。增强型分组块是可选的，因为数据包可以通过该块或简单分组块进行存储。

数据包主要在增强型数据包块。其格式如下

| 块类型       | 0x00000006(4字节) |                                                              |
| ------------ | ----------------- | ------------------------------------------------------------ |
| 块总长度     | 4字节             | 块类型到选项长度                                             |
| 接口ID       | 4字节             | 指定该数据包来自哪个接口                                     |
| 时间戳（高） | 4字节             | 表示时间戳的 64 位值的高 32 位和低 32 位。时间戳是一个 64 位无符号整数，表示自 1970 年 1 月 1  日以来的单位数。解释该字段的方式由该数据包引用的接口描述块的“if_tsresol”选项指定。与 libpcap  文件格式不同，时间戳不会保存为两个 32 位值，分别表示自 1970 年 1 月 1 日以来的秒和微秒。它们被保存为单个 64  位数量，另存为两个 32 位字。默认分辨率为 10^-6，即时间戳的 64 位值除以10的6次方，整数部分为秒，小数部分为微秒。 |
| 时间戳（低） | 8字节             |                                                              |
| 捕获长度     | 4字节             | 从数据包中捕获的字节数                                       |
| 数据包长度   | 4字节             | 数据包在网络上传输时的实际长度                               |
| 数据包       | 捕获长度字节      | 来自网络的数据，包括链路层标头。该字段的实际长度是捕获长度。 |
| 选项         | 可变字节          | 根据块总长度确定可变选项                                     |

## 块解析源代码（Python）

```python
import sys
import struct

file = open("example.pcap", "rb")
file_result = open("result.txt", "w")
blockNumber = 0

print("对pcap文件进行分析...")

while True:
    # 读取block类型和长度
    try:
        data = file.read(8)
    except Exception as error:
        break
    if len(data) < 8:
        break

    print(".", end = "")

    (block_type, block_total_len) = struct.unpack("=LL", data)
    blockNumber = blockNumber + 1
    # 判读block类型和长度
    if block_type == 0x0A0D0D0A:
        file_result.write("|--%05u号块，类型：节头块(Section Header Block, 0x%08x)\n" % (blockNumber, block_type))
    elif block_type == 0x0000001:
        file_result.write("|--%05u号块，类型：接口描述块(Interface Description Block, 0x%08x)\n" % (blockNumber, block_type))
    elif block_type == 0x0000002:
        file_result.write("|--%05u号块，类型：分组块(Packet Block, 0x%08x)\n" % (blockNumber, block_type))
    elif block_type == 0x0000003:
        file_result.write("|--%05u号块，类型：简单分组块(Simple Packet Block, 0x%08x)\n" % (blockNumber, block_type))
    elif block_type == 0x0000004:
        file_result.write("|--%05u号块，类型：名称解析块(Name Resolution Block, 0x%08x)\n" % (blockNumber, block_type))
    elif block_type == 0x0000005:
        file_result.write("|--%05u号块，类型：接口统计块(Interface Statistics Block, 0x%08x)\n" % (blockNumber, block_type))
    elif block_type == 0x0000006:
        file_result.write("|--%05u号块，类型：增强分组块(Enhanced Packet Block, 0x%08x)\n" % (blockNumber, block_type))
    else:
        file_result.write("|--%05u号块，类型：未知(unknow, 0x%08x\n)" % (blockNumber, block_type))
    file_result.write("|  |--长度：%d\n" % block_total_len)
    block_bytes = file.read(block_total_len - 8)

file_result.write("|--所有包均已读取完毕！\n")
print("\npcap文件分析完毕！")
```

运行结果

```bash
|--00001号块，类型：节头块(Section Header Block, 0x0a0d0d0a)
|  |--长度：184
|--00002号块，类型：接口描述块(Interface Description Block, 0x00000001)
|  |--长度：88
|--00003号块，类型：增强分组块(Enhanced Packet Block, 0x00000006)
|  |--长度：628
|--00004号块，类型：增强分组块(Enhanced Packet Block, 0x00000006)
|  |--长度：628
|--00005号块，类型：增强分组块(Enhanced Packet Block, 0x00000006)
|  |--长度：628
|--00006号块，类型：增强分组块(Enhanced Packet Block, 0x00000006)
|  |--长度：180
|--00007号块，类型：增强分组块(Enhanced Packet Block, 0x00000006)
|  |--长度：180
|--00008号块，类型：增强分组块(Enhanced Packet Block, 0x00000006)
|  |--长度：180
|--00009号块，类型：增强分组块(Enhanced Packet Block, 0x00000006)
|  |--长度：628
|--00010号块，类型：增强分组块(Enhanced Packet Block, 0x00000006)
|  |--长度：628
|--00011号块，类型：增强分组块(Enhanced Packet Block, 0x00000006)
|  |--长度：628
|--00012号块，类型：增强分组块(Enhanced Packet Block, 0x00000006)
|  |--长度：180
```

























































