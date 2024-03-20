# Capture

## 抓包软件

- Fiddler
- HttpCanary小黄鸟
- Wireshark

## 抓包格式

- Pcap
- Pcapng

## 底层实现

抓包方式

- 实际网卡抓包 - FPGA。CRC错误在网卡层就会被丢弃，抓CRC错包只能在这一层抓
- 绕开协议栈抓包 - wireshark、DPDK、eBPF
- 证书、协议抓包 - Fiddler

## 环境

(见PcapPlusPlus文档有一版相关介绍)

- DPDK
- BPF
- 等

## 抓包/分析库

### 选型

#### 不限语言

（20240126）

- C/C++
  - **Libpcap**: 这是最著名的PCAP库，支持C/C++。很多其他库都是基于libpcap构建的。尽管它的功能强大，但它的API并不是很易用。
    - https://github.com/the-tcpdump-group/libpcap，**2.4k**
    - https://wiki.wireshark.org/libpcap，https://www.tcpdump.org/
  - **PcapPlusPlus**: PcapPlusPlus是一个多语言的网络分析和模拟框架。它提供了一些工具来生成和解析PCAP文件
    - https://github.com/seladb/PcapPlusPlus，**2.5k**
    - https://pcapplusplus.github.io/docs/quickstart
- Python
  - **Scapy**: Scapy是一个强大的Python库，可以生成、解析、发送和接收网络报文。Scapy 支持大量的协议，并且可以方便地添加新协议。
    - https://github.com/secdev/scapy，**9.7k**
    - https://scapy.net/
  - **Trex**：使用的Scapy库
    - https://github.com/cisco-system-traffic-generator/trex-core，1.2k
    - https://trex-tgn.cisco.com/
  - **Pypcap**
    - 基于**libpcap C库**，它让你能够使用Python更方便地使用libpcap
    - https://github.com/pynetwork/pypcap，295
    - 下载：pip install pypcap，pypi地址：https://pypi.org/project/pypcap/
  - **Dpkt**: Dpkt是一个Python库，它可以解析和创建网络报文。与Scapy相比，Dpkt的API更加简洁
    - https://github.com/kbandla/dpkt，1k
- 可参考项目
  - **Json2Pcap**: 一款用于将json数据转换为pcap文件的工具，其源码托管在Github上。
  - **Brimsec/zq**: 这是一个用go编写的处理PCAP的开源工具，其中有一部分是将pcap转json，可以在此基础上修改为生成pcap。

#### 深度分析库

这里的笔记主要是抓包不是分析，分析只是提一嘴。可以参考PcapPlusPlus文档，或者如果只是简单解析，一些pcap工具都能做。深度可以看nDPI这种深度分析工具

#### 比较 - Python库

（20240126）

下表中的 "Trex" 不参与横向比较，以为他底层使用的Scapy，更像是Scapy的上层封装

|             | Pypcap                                      | Dpkt                                    | **Scapy**                                    | **(Trex)**                                                   |
| ----------- | ------------------------------------------- | --------------------------------------- | -------------------------------------------- | ------------------------------------------------------------ |
| 难度        | 低                                          | 中                                      | 难                                           |                                                              |
| 功能 - 捕获 | ✅                                           | ✅                                       | ✅                                            |                                                              |
| 功能 - 解析 | ❌，需要配合Dpkt等解析                       | ✅，支持大多数协议                       | ✅，多协议，还可添加自定义                    |                                                              |
| 功能 - 创建 | ❌                                           | ✅                                       | ✅                                            |                                                              |
| 功能 - 发送 | ❌                                           | ✅                                       | ✅                                            |                                                              |
| 功能 - 其他 | ——                                          | ——                                      | 数据包的嗅探与注入、<br>网络扫描、路由跟踪等 | 总体性能测试，<br>支持有状态流量、模拟大并发                 |
| 开源 - 是否 | ✅                                           | ✅                                       | ✅                                            |                                                              |
| 开源 - Star | 295                                         | 1k                                      | 9.7k                                         | 1.2k                                                         |
| 开源 - 地址 | [地址](https://github.com/pynetwork/pypcap) | [地址](https://github.com/kbandla/dpkt) | [地址](https://github.com/secdev/scapy)      | [地址](https://github.com/cisco-system-traffic-generator/trex-core) |
| 规模        | 小                                          | 中                                      | 大                                           |                                                              |
| 实现        | libpcap C库                                 | 不依赖于libpcap                         | 可以选择是否使用libpcap                      |                                                              |

Trex vs Scapy

Q：综合考虑下来，我选择使用Scapy作为json生成pcap的工具的开发。那 Trex 呢，他好像也是使用的Scapy库，那我使用Trex和使用Scapy有什么区别？

A：Trex和Scapy都是强大的网络包处理库，但它们的使用场景和功能有所不同。

- Scapy是一个Python库，主要用于解析和构造网络包，它具有强大的数据包解析和生成能力。Scapy可以解析大多数常见的网络协议，可以方便地创建和发送自定义的网络包。你可以使用Scapy进行各种网络测试和尝试，例如扫描网络、嗅探数据包、分析网络流量等。

- Trex则是一款总体性能测试工具，它支持多种流量模式，包括stateful（有状态）和stateless（无状态）的流量模式。
  在stateful模式下，Trex能够模拟大量并发的网络连接，发送复杂的网络流量。在stateless模式下，Trex提供了一个简单的API，可以方便地发送自定义的网络包。Trex还提供了丰富的统计和分析功能，可以详细地分析测试结果。

- Trex底层使用Scapy构造数据包，因此Trex继承了Scapy的强大功能。

  然而，如果你要进行大规模的网络性能测试，你可能会发现Scapy无法满足你的需求，因为Scapy的性能相对较低。这时候，你可能需要使用Trex这样的专业性能测试工具。如果你只需要解析和生成网络包，那么Scapy可能是更好的选择。

总的来说，Scapy和Trex各有优势，你应该根据自己的具体需求来选择。

#### 比较 - C库

如果用C库的话，应该就是PcapPlusPlus了，公司几个项目都是用的这个

#### 比较 - Python库 vs Cpp库

这里重点比较的的是Python的Trex (with Scapy)库，和Cpp的PcapPlusPlus库

|                | PcapPlusPlus                           | Scapy (+Trex)                   | Trex     |
| -------------- | -------------------------------------- | ------------------------------- | -------- |
| 性能           | 高                                     | 相对较低                        | 性能提高 |
| 开源 - 是否    | ✅                                      | ✅                               | ✅        |
| 开源 - Star    | 2.5k                                   | 9.7k                            | 1.2k     |
| 开源 - 地址    | https://github.com/seladb/PcapPlusPlus | https://github.com/secdev/scapy |          |
| 官网地址       | https://pcapplusplus.github.io/        | https://scapy.net/              |          |
| 功能 - 有状态  | ❌                                      | ❌                               | ✅        |
| 开发与维护难度 | 稍低                                   | 高                              | 高       |

重点考虑的几个参数

- 非主要考虑
  - 性能：由于现在调研的目的是，做一个Pcap生成器，而非实时的网络报文解析和Pcap生成，性能要求不高，性能参数不列入考虑。
  - 易于调用：另外也只是一个单独的工具，而非库，也不是主要的考虑因素
- 主要考虑
  - 开发维护
    - 学习和开发成本上，这些库之前没接触过，Python肯定成本更低
    - Python库开发进度更快，也更好维护。特别是对于自定义协议的添加，可以给其他人做。如果选用C库，如PcapPlusPlus，这些可能就要自己写了
    - 开发周期初步设定是两周以内（过年前），Python库更易于的deadline前完成该项目并使之可用。使用C库压力更大，主要是如果要去实现 "有状态" 模式，这会非常麻烦
  - 长远考虑
    - 学习PcapPlusPlus可能更有利于公司其他项目的维护（因为目前有几个项目都使用的该库），长远来看可能也更好。
    - 但Scapy库的通用性也不差，灵活性很大，社区规模也比PcapPlusPlus大

总结双方优势

- Python Trex (with Scapy)
  - 开发周期短，维护容易
  - 自定义协议的添加容易，可给别人做
  - 灵活性更大
  - 无需再次实现**有状态**模式，直接就有有状态模式的功能
- Cpp PcapPlusPlus
  - 易于协调公司的其他项目

最后我选择的是：Trex (with Scapy)









