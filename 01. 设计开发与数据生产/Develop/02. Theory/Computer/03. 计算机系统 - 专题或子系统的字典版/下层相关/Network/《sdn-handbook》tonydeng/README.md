# 《sdn-handbook》

## 博客介绍

### 博客内容

- [SDN 网络相关个人博客](https://tonydeng.github.io/sdn-handbook/basic/icmp.html) 
  - 多备份几个链接：
  - [GitBook](https://tonydeng.gitbooks.io/sdn/)
  - [Github](https://github.com/tonydeng/sdn-handbook), 1.2k Star, tony deng的
  - [ePub](https://www.gitbook.com/download/epub/book/tonydeng/sdn)
  - [PDF](https://www.gitbook.com/download/pdf/book/tonydeng/sdn)
  - [项目源码](https://github.com/tonydeng/sdn-handbook)
- 另一个 SDN book。这个是我后来才发现的，似乎也不错，以后再看
  - [Github](https://github.com/feiskyer/sdn-handbook), 1.4k Star, feiskyer的 (这个是上海人)
  - https://sdn.feisky.xyz/
  - https://kubernetes.feisky.xyz/



个人评价：

- 进度
  - “03. Linux网络”
  - 暂时粗略看 “02. 网络基础理论/（06及往后）”，后面再详细看

- 优点
  - 内容广泛丰富。包括基础，又包括更深入的容器、SDN、NFV、DPDK、OVS、eBPF、XDP 等。
  - 分章合理
  - 参考资源齐全（例如TCP那里将许多TCP相关机制的RFC文档都给列出来了）
- 缺点
  - 但有点像我网站那样，是直接把个人笔记直接放到网站上了，整理和梳理不是为别人服务的，纯粹是自己看得懂就行 “教学性” 较差
  - 大章分章可以，但内部 “排版” 和 “分章” 一般，内联样式过于泛用了

### 相关网站

这个网站是 [TonyDeng's Blog](https://tonydeng.github.io/) 博客里的其中一个子分类，还有其他的目录：

- [TonyDeng's Blog](https://tonydeng.github.io/)，这里还有分类和标签体系，不错

  - [GitBook](https://tonydeng.github.io/gitbook-zh/)，**主要学习该目录**

    - 架构设计
      - [架构师手册](https://tonydeng.github.io/architect-manual)，不错，有时间去看看
      - [企业架构设计方法与实践](https://tonydeng.github.io/EA-practices)
    - SDN
      - [SDN手册](https://tonydeng.github.io/sdn-handbook/)，**主要学习该目录**
      - [RFC8040 (RESTCONF Protocol) 中文翻译](https://tonydeng.github.io/rfc8040-zh/)，这几个RFC文档的翻译也不错
      - [RFC7950 (The YANG 1.1 Data Modeling Language)翻译](https://tonydeng.github.io/rfc7950-zh/)
      - [RFC6241 - Network Configuration Protocol(NETCONF)翻译](https://tonydeng.github.io/rfc6241-zh/)
    - 产品设计
      - [敏捷的用户故事方法](https://tonydeng.github.io/user-stories-applied/)
      - [简约至上：交互式设计四策略（Simple and Usable Web,Mobile, and Interaction Design）笔记](https://tonydeng.github.io/Interactive-design-notes/)
    - Gitbook
      - [Gitbook使用入门](https://tonydeng.github.io/gitbook-zh/gitbook-howtouse/)

  - [分类](https://tonydeng.github.io/categories/)，这里都是一些单篇的离散文章

    - [JUnit5 Tutorial](https://tonydeng.github.io/categories/JUnit5-Tutorial/) 3

    - [Leiningen + Clojure之旅](https://tonydeng.github.io/categories/Leiningen-Clojure之旅/) 2

    - [Mac OSX](https://tonydeng.github.io/categories/Mac-OSX/) 4

    - [Rust入坑之旅](https://tonydeng.github.io/categories/Rust入坑之旅/) 2

    - [SDN](https://tonydeng.github.io/categories/SDN/) 1

    - [产品设计](https://tonydeng.github.io/categories/产品设计/) 2

    - [创业](https://tonydeng.github.io/categories/创业/) 1

    - [威胁建模](https://tonydeng.github.io/categories/威胁建模/) 1

    - [安全](https://tonydeng.github.io/categories/安全/) 2

    - [工程师文化](https://tonydeng.github.io/categories/工程师文化/) 3

    - [性能](https://tonydeng.github.io/categories/性能/) 4

    - [效率](https://tonydeng.github.io/categories/效率/) 27

    - [数据库](https://tonydeng.github.io/categories/数据库/) 1

    - [架构设计](https://tonydeng.github.io/categories/架构设计/) 4

    - [生活感悟](https://tonydeng.github.io/categories/生活感悟/) 3

    - [程序设计](https://tonydeng.github.io/categories/程序设计/) 7

    - [算法及实现](https://tonydeng.github.io/categories/算法及实现/) 2

    - [管理](https://tonydeng.github.io/categories/管理/) 4

## 目录

- 前言
- 网络基础
  - 网络基础理论
    - TCP/IP 网络模型
    - ARP
    - ICMP
    - 路由
    - 交换机
    - UDP
    - DHCP/DNS
    - TCP
    - VLAN
    - Overlay
    - SNMP
    - LLDP
  - Linux网络
    - Linux网络配置
      - 虚拟网络设备
    - iptables/netfilter
    - 负载均衡
    - 流量控制
    - SR-IOV
    - 内核VRF
    - eBPF
      - bcc
      - 故障排查
    - XDP
      - XDP架构
      - 使用场景
    - 常用工具
      - 网络抓包tcpdump
      - scapy
    - 内核网络参数
  - Open vSwitch
    - OVS介绍
    - OVS编译
    - OVS原理
    - Open Virtual Network
      - OVN在Ubuntu编译
      - OVN实践
      - OVN高可用
      - OVN Kubernetes插件
      - OVN Docker插件
      - OVN OpenStack
  - DPDK
    - DPDK简介
    - DPDK安装
    - 报文转发模型
    - NUMA
    - Ring和共享内存
    - PCIe
    - 网卡性能优化
    - 多队列
    - 硬件offload
    - 虚拟化
    - OVS DPDK
    - SPDK
    - OpenFastPath
  - 安全设备
    - VPN
    - IPSec VPN
    - SSL VPN
    - ICG
    - Firewall
      - 工作原理
      - 常见分类
      - 演进过程
- SDN & NFV
  - SDN
    - YANG Language
    - SDN 控制器
      - OpenDaylight
        - OpenDaylight Projects
        - DataStore
      - ONOS
      - Floodlight
      - Ryu
      - NOX/POX
    - 南向接口
      - OpenFlow
      - OF-COnfig
      - INETCONF
        - NETCONF Call Home
        - YANG Module for NETCONF Monitoring
        - NETCONF请求和响应中的标签
      - P4
      - AAA
        - Radius
  - 数据平面
  - NFV
  - SDWAN
- SDN实践
  - Mininet
  - Neutron
  - SDN实践案例
    - Google数据中心网络
- SDN业务类型示例
  - 业务类型
  - SDN控制器应用场景
  - 业务控制平台-SCP
- 参考文档
  - FAQ
  - 参考文档

