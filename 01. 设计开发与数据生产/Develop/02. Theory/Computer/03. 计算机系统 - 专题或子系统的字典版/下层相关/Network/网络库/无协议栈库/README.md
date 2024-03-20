# eBPF

# 目录

# 学习路线

个人学习路线 + 学后改良

入门阶段

1.  先看官网的介绍文档+Lab
2.  再看狄卫华博文前两章
3.  看B站的《高效入门eBPF》
4.  写基础demo

深入阶段

1.  看Cilium文档，学习 XDP

1.  狄卫华 +《Linux内核观测技术BPF》混着看

    （《Linux内核观测技术BPF》，但这本书连环境配置的内容，不适合刚开始看）

高级阶段

1.   未触及，应该是内核和eBPF源码相关的东西吧

# 资料收集

## 官网资料

-   [官网 ebpf.io](https://ebpf.io/)
-   [官网介绍文档](https://ebpf.io/what-is-ebpf/)
-   [官网博客](https://ebpf.io/blog/)，包括的模块：社区、如何、发布、技术、更新、外部
-   [官网在线虚拟机](https://play.instruqt.com/embed/isovalent/tracks/ebpf-getting-started)
-   **【主要资料】**文档
    -   详细文档与教程：https://ebpf.io/what-is-ebpf/#documentation（吐槽：这个藏得真深，居然在介绍文档的底部，没有独立入口）
    -   社区与文档：https://docs.cilium.io/en/stable/bpf/
    -   内核中的BPF文档：https://www.kernel.org/doc/html/latest/bpf/index.html



## 其他参考资料

### 博客 / 系列文章

-   **【主要资料】**[中文个人博客](https://www.ebpf.top/)，这是一个专门研究eBPF的人写的专题博客，会有一些对于官网内容的翻译。

    重点说一下这个作者 —— “狄卫华”

    -   是《Linux内核观测技术BPF》的译者之一
    -   个人博客如上，网站第一篇文章，就是对eBPF的介绍：[【BPF入门系列-1】eBPF 技术简介](https://www.ebpf.top/post/ebpf_intro/)
        ~~[【云原生社区】eBPF 技术简介](https://cloudnative.to/blog/bpf-intro/)，内容和上面这篇一样，但图片更模糊了~~
    -   Github：https://github.com/DavadDi/bpf_study，但更新不频繁
    -   B站：https://space.bilibili.com/423716136，更新也很少
    -   详见 [[狄卫华博客文章目录]] 的内容

-   **【主要资料】**[0voice的个人文章](https://github.com/0voice/kernel_new_features/blob/main/ebpf/%E6%96%87%E7%AB%A0/eBPF%E8%AF%A6%E8%A7%A3.md)，这个也不错，内容挺多

-   **【主要资料】**[【redhat官网】使用 BCC 进行网络跟踪](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/8/html/configuring_and_managing_networking/network-tracing-using-the-bpf-compiler-collection_configuring-and-managing-networking)

### 文章

-   [【知乎】一文看懂eBPF、eBPF的使用（超详细）](https://zhuanlan.zhihu.com/p/480811707)

-   [【酷壳】EBPF 介绍](https://coolshell.cn/articles/22320.html)

-   [深入浅出eBPF](https://www.ebpf.top/)

-   [咨询 - 颠覆传统、应用大爆发，eBPF 何以改变 Linux？](https://www.infoq.cn/article/5xvc1ic6bdlqyju6ywv0)

-   [【51CTO】深入浅出eBPF｜你要了解的七个核心问题](https://www.51cto.com/article/711018.html)

### 文献 / 二次参考资料

（主要是 “BPF入门系列 - 狄卫华” 的引用资料）

-   [The BSD Packet Filter: A New Architecture for User-level Packet Capture](https://www.tcpdump.org/papers/bpf-usenix93.pdf)
-   [[译\] Cilium：BPF 和 XDP 参考指南（2019） ](http://arthurchiao.art/blog/cilium-bpf-xdp-reference-guide-zh/)[Cillum BPF and XDP Reference Guide](https://docs.cilium.io/en/v1.8/bpf/)
-   [Cloudflare架构以及BPF如何占据世界](https://blog.cloudflare.com/zh/cloudflare-architecture-and-how-bpf-eats-the-world-zh/)
-   [關於 BPF 和 eBPF 的筆記](https://www.luoow.com/dc_tw/106805603)
-   [Dive into BPF: a list of reading material](https://qmonnet.github.io/whirl-offload/2016/09/01/dive-into-bpf/) [中文](https://blog.csdn.net/F8qG7f9YD02Pe/article/details/79815702)
-   [eBPF 简史](https://www.ibm.com/developerworks/cn/linux/l-lo-eBPF-history/index.html)
-   https://www.youtube.com/watch?v=znBGt7oHJyQ
-   [BPF Documentation](https://www.infradead.org/~mchehab/kernel_docs/bpf/index.html) [HOWTO interact with BPF subsystem](https://www.kernel.org/doc/html/latest/bpf/bpf_devel_QA.html#q-how-do-i-indicate-which-tree-bpf-vs-bpf-next-my-patch-should-be-applied-to)
-   [Linux 内核 BPF 文档](https://www.infradead.org/~mchehab/kernel_docs/bpf/index.html)
-   [Linux Extended BPF (eBPF) Tracing Tools](http://www.brendangregg.com/ebpf.html) Brendan Gregg
-   [性能提升40%: 腾讯 TKE 用 eBPF绕过 conntrack 优化K8s Service](https://mp.weixin.qq.com/s/3BQU9AYh1ScZ_1V17BJ4wg)
-   [SDN handbook](https://tonydeng.github.io/sdn-handbook/)
-   Linux BPF 帮助文档 [bpf(2)](https://man7.org/linux/man-pages/man2/bpf.2.html) [bpf-helpers(7)](https://man7.org/linux/man-pages/man7/bpf-helpers.7.html) [tc-bpf(8)](https://man7.org/linux/man-pages/man8/tc-bpf.8.html)

国内大厂 eBPF 实践经验

-   [eBPF 在网易轻舟云原生的应用实践](https://www.infoq.cn/article/OVCVwQijztA7JlexgDOc)
-   [性能提升40%: 腾讯 TKE 用 eBPF绕过 conntrack 优化K8s Service](https://mp.weixin.qq.com/s?__biz=MzI5ODQ2MzI3NQ==&mid=2247491111&idx=2&sn=db348d6f13e1df4b3b9aba2dce0ba0e4&chksm=eca42763dbd3ae757530f6922ca1748736e42eb863e01076e94622c81be542e5582c9678874b&scene=27#wechat_redirect)
-   [字节跳动：eBPF 技术实践：高性能 ACL](https://www.infoq.cn/article/Tc5Bugo5vBAkyaRb5CCU)
-   [阿里：eBPF Internal：Instructions and Runtime](https://www.infoq.cn/article/c6t2IL23O6EbdQgUpQhb)
-   [使用 ebpf 深入分析容器网络 dup 包问题](https://mp.weixin.qq.com/s?__biz=MzI5ODQ2MzI3NQ==&mid=2247488831&idx=1&sn=3da3a976439d0134e3789a3e035ea1f0&chksm=eca42c7bdbd3a56d35c482d07798ee9d48a2f1103724f78f0634953ab33d8bd1ab9700190fb6&scene=27#wechat_redirect)
-   [eBay 云计算“网”事：网络超时篇](https://www.infoq.cn/article/JmCbkA0XX9NqrcX6loIo)  [eBay云计算“网”事｜网络丢包篇](https://mp.weixin.qq.com/s/IpUr3pnVgMInqKAkBfawtA)
-   [字节跳动容器化场景下的性能优化实践](https://www.infoq.cn/article/mu-1bFHNmrdd0kybgPXx)

### 社区 / 论坛 / 群

-   官方推荐的论坛与文档：https://docs.cilium.io/en/stable/bpf/
-   似乎没有群，频道、qq、Telegram Desktop、Discord都没有
-   论坛 / 社区：没有说单独的社区，但在Slack、Stack Overflow、reddit、Wikipedia、eCHO、Newsletter、Contribute 中有相应的子分区

### Github

开源项目类：

-   [iovisor/bpftrace](https://github.com/iovisor/bpftrace)， 用于增强eBPF
-   [iovisor/gobpf](https://github.com/iovisor/gobpf)， 用于创建 BPF 程序的 Go 绑定
-   [iovisor/bcc](https://github.com/iovisor/bcc)， BCC - 基于 BPF 的 Linux IO 分析、网络、监控等工具。  ==（里面提供了非常多的案例demo，可以作为学习参考）==
-   [libbpf/libbpf-bootstrap](https://github.com/libbpf/libbpf-bootstrap)， 使用 libbpf 和 BPF CO-RE 进行 BPF 应用程序开发的脚手架
-   [google/nsjail](https://github.com/google/nsjail)， 轻量级进程隔离工具，利用 Linux 命名空间和 seccomp-bpf 系统调用过滤器（借助 kafel bpf 语言）

资料类：

-   https://github.com/DavadDi/bpf_study， 狄卫华的源码资料
-   https://github.com/bpftools/linux-observability-with-bpf， 《Linux内核观测技术BPF》的附件内容
-   [cloudflare/bpftools](https://github.com/cloudflare/bpftools)， 数据包分析工具包

## 官网提供的学习途径

[官网提供的学习途径](https://ebpf.io/get-started/)：书、视频、实验室

-   [根据官网给的书录](https://ebpf.io/get-started/)：
    -   《What Is eBPF ?》
    -   《Systems Performance》
    -   《BPF Performance Tools》
    -   《Linux Observability with BPF》，这本有精译版**《Linux内核观测技术BPF》**，可pdf
    -   《Learning eBPF》
-   [实验室](https://play.instruqt.com/embed/isovalent/tracks/ebpf-getting-started)
    开始会有段和官网文档一样内容的PPT，跳过就好。进去之后（可能需要点时间）会给你两个终端程序来运行
-   视频
    略
-   “进一步阅读”，详见下面

## 狄卫华博客文章目录

针对 https://www.ebpf.top/ 博客进行目录编辑（该博客最近更新：230506/230719）

博客有一些与eBPF无关的东西，先在分类里筛剩eBPF。推荐首先查看：[【BPF入门系列-2】BPF 学习路径总结](https://www.ebpf.top/post/ebpf_learn_path/)

### BPF入门系列

-   [【BPF入门系列-1】eBPF 技术简介](https://www.ebpf.top/post/ebpf_intro/)

    -   目录：BPF 、eBPF、应用案例、编写BPF程序、国内大厂eBPF实践经验、参考资料

-   [【BPF入门系列-2】BPF 学习路径总结](https://www.ebpf.top/post/ebpf_learn_path/)
    -   目录：为什么要学习BPF、BPF应该怎么学习、BPF资料汇总
-   [【BPF入门系列-3】BPF 环境搭建](https://www.ebpf.top/post/ebpf_c_env/)

-   [【BPF入门系列-4】如何在 BPF 程序中正确地按照 PID 过滤？](https://www.ebpf.top/post/ebpf_prog_pid_filter/)
-   [【BPF入门系列-5】基于 eBPF 实现容器运行时安全](https://www.ebpf.top/post/ebpf_container_security/)
-   [【BPF入门系列-6】BPF 环形缓冲区](https://www.ebpf.top/post/bpf_ring_buffer/)
-   [【BPF入门系列-7】使用 ebpf 实时持续跟踪进程文件记录](https://www.ebpf.top/post/ebpf_trace_file_open/)
-   [【BPF入门系列-8】文件打开记录跟踪之 perf_event 篇](https://www.ebpf.top/post/ebpf_trace_file_open_perf_output/)
-   [【BPF入门系列-9】文件打开记录结果跟踪篇](https://www.ebpf.top/post/ebpf_trace_file_return/)
-   [【BPF入门系列-10】使用 tracepoint 跟踪文件 open 系统调用](https://www.ebpf.top/post/open_tracepoint_trace/)
-   [【BPF入门系列-12】【译】eBPF 和 Go 经验初探](https://www.ebpf.top/post/ebpf_go_translation/)

### BPF网络篇系列

-   [【BPF网络篇系列-1】k8s api-server slb 异常流量定位分析](https://www.ebpf.top/post/ebpf_network_traffic_monitor/)
-   [【BPF网络篇系列-2】容器网络延时之 ipvs 定时器篇](https://www.ebpf.top/post/ebpf_network_kpatch_ipvs/)

### eBPF概述系列

-   [【译】eBPF 概述：第 1 部分：介绍](https://www.ebpf.top/post/ebpf-overview-part-1/)
-   [【译】eBPF 概述：第 2 部分：机器和字节码](https://www.ebpf.top/post/ebpf-overview-part-2/)
-   [【译】eBPF 概述：第 3 部分：软件开发生态](https://www.ebpf.top/post/ebpf-overview-part-3/)
-   [【译】eBPF 概述：第 4 部分：在嵌入式系统运行](https://www.ebpf.top/post/ebpf-overview-part-4/)
-   [【译】eBPF 概述：第 5 部分：跟踪用户进程](https://www.ebpf.top/post/ebpf-overview-part-5/)

### BPF 攻防系列

-   [【BPF 攻防系列-1】【译】开战！！！](https://www.ebpf.top/post/offensive-bpf-getting-started/)
-   [【BPF 攻防系列-2】【译】恶意使用的 bpftrace 🤯](https://www.ebpf.top/post/offensive-bpf-bpftrace/)

### 其他

一些译文

-   [[译\] BPF 可移植性和 CO-RE（一次编译，到处运行）【转载】](https://www.ebpf.top/post/bpf_core/)
-   [BPF 二进制文件：BTF，CO-RE 和 BPF 性能工具的未来【译】](https://www.ebpf.top/post/bpf-co-re-btf-libbpf/)
-   [在 Windows 平台上启用 eBPF【译】](https://www.ebpf.top/post/ebpf_on_windows/)
-   [BCC 到 libbpf 的转换指南【译】](https://www.ebpf.top/post/bcc-to-libbpf-guid/)
-   [【译】神奇的 eBPF](https://www.ebpf.top/post/awesome-ebpf/)
-   [【译】聊聊对 BPF 程序至关重要的 vmlinux.h 文件](https://www.ebpf.top/post/intro_vmlinux_h/)
-   [【译】BTFGen: 让 eBPF 程序可移植发布更近一步](https://www.ebpf.top/post/btfgen-one-step-closer-to-truly-portable-ebpf-programs/)
-   [【译】2023 年 6 个值得关注的 eBPF 趋势 ](https://www.ebpf.top/post/six-bpf-trends-for-2023/)

原创

-   [使用 Go 语言管理和分发 ebpf 程序](https://www.ebpf.top/post/ebpf_go/)

    [eBPF 与 Go，超能力组合（含视频）](https://www.ebpf.top/post/ebpf_and_go/)

    [Rust  Aya 框架编写 eBPF 程序 ](https://www.ebpf.top/post/ebpf_rust_aya/)

-   [深入浅出 eBPF 安全项目 Tracee](https://www.ebpf.top/post/tracee_intro/)

-   [深入浅出 BPF TCP 拥塞算法实现原理 ](https://www.ebpf.top/post/ebpf_struct_ops/)

-   [当 BPF 邂逅 CPU 调度器 ](https://www.ebpf.top/post/cfs_scheduler_bpf/)

-   [百页 PPT BPF 技术全览 - 深入浅出 BPF 技术 ](https://www.ebpf.top/post/head_first_bpf/)

-   [基于 eBPF 的网络监测实践](https://www.ebpf.top/post/ebpf_network_exporter/)

-   [Cilium 1.11 发布，带来内核级服务网格、拓扑感知路由....](https://www.ebpf.top/post/cilium_1_11_new/)

-   [揭秘 BPF map 前生今世](https://www.ebpf.top/post/map_internal/)

-   [BumbleBee: 如丝般顺滑构建、交付和运行 eBPF 程序](https://www.ebpf.top/post/bumblebee/)

-   [eBPF: 从 BPF to BPF Calls 到 Tail Calls](https://www.ebpf.top/post/bpf2pbpf_tail_call/)

-   [BTF：实践指南](https://www.ebpf.top/post/btf-bpf-type-format/)

-   [使用 XDP 实现负载均衡器实战](https://www.ebpf.top/post/xdp_lb_demo/)

## 狄卫华博客的学习路径

详见：[【BPF入门系列-2】BPF 学习路径总结](https://www.ebpf.top/post/ebpf_learn_path/)

## 官网中 “进一步阅读”

### 文档

-   [BPF & XDP Reference Guide](https://cilium.readthedocs.io/en/stable/bpf/), Cilium Documentation, Aug 2020
     BPF 和 XDP 参考指南，Cilium 文档，2020 年 8 月
-   [BPF Documentation](https://www.kernel.org/doc/html/latest/bpf/index.html), BPF Documentation in the Linux Kernel
     BPF 文档、Linux 内核中的 BPF 文档
-   [BPF Design Q&A](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/Documentation/bpf/bpf_design_QA.rst), FAQ for kernel-related eBPF questions
    BPF 设计问答，内核相关 eBPF 问题的常见问题解答

### 教程

-   [Learn eBPF Tracing: Tutorial and Examples](http://www.brendangregg.com/blog/2019-01-01/learn-ebpf-tracing.html), Brendan Gregg's Blog, Jan 2019
    学习 eBPF 跟踪：教程和示例，Brendan Gregg 的博客，2019 年 1 月
-   [XDP Hands-On Tutorials](https://github.com/xdp-project/xdp-tutorial), Various authors, 2019
     XDP 实践教程，多位作者，2019 年
-   [BCC, libbpf and BPF CO-RE Tutorials](https://facebookmicrosites.github.io/bpf/blog/), Facebook's BPF Blog, 2020
     BCC、libbpf 和 BPF CO-RE 教程，Facebook 的 BPF 博客，2020

### 会谈

#### Generic 通用的

-   [eBPF and Kubernetes: Little Helper Minions for Scaling Microservices](https://www.youtube.com/watch?v=99jUcLt3rSk) ([Slides](https://kccnceu20.sched.com/event/ZemQ/ebpf-and-kubernetes-little-helper-minions-for-scaling-microservices-daniel-borkmann-cilium)), Daniel Borkmann, KubeCon EU, Aug 2020
     eBPF 和 Kubernetes：用于扩展微服务的 Little Helper Minions（幻灯片），Daniel Borkmann，KubeCon EU，2020 年 8 月
-   [eBPF - Rethinking the Linux Kernel](https://www.infoq.com/presentations/facebook-google-bpf-linux-kernel/) ([Slides](https://docs.google.com/presentation/d/1AcB4x7JCWET0ysDr0gsX-EIdQSTyBtmi6OAW7bE0jm0)), Thomas Graf, QCon London, April 2020
     eBPF - 重新思考 Linux 内核（幻灯片），Thomas Graf，QCon 伦敦，2020 年 4 月
-   [BPF as a revolutionary technology for the container landscape](https://www.youtube.com/watch?v=U3PdyHlrG1o&t=7) ([Slides](https://fosdem.org/2020/schedule/event/containers_bpf/attachments/slides/4122/export/events/attachments/containers_bpf/slides/4122/BPF_as_a_revolutionary_technology_for_the_container_landscape.pdf)), Daniel Borkmann, FOSDEM, Feb 2020
     BPF 作为容器领域的革命性技术（幻灯片），Daniel Borkmann，FOSDEM，2020 年 2 月
-   [BPF at Facebook](https://www.youtube.com/watch?v=ZYBXZFKPS28), Alexei Starovoitov, Performance Summit, Dec 2019
     Facebook 的 BPF，Alexei Starovoitov，性能峰会，2019 年 12 月
-   [BPF: A New Type of Software](https://youtu.be/7pmXdG8-7WU?t=8) ([Slides](https://www.slideshare.net/brendangregg/um2019-bpf-a-new-type-of-software)), Brendan Gregg, Ubuntu Masters, Oct 2019
     BPF：一种新型软件（幻灯片），Brendan Gregg，Ubuntu Masters，2019 年 10 月
-   [The ubiquity but also the necessity of eBPF as a technology](https://www.youtube.com/watch?v=mFxs3VXABPU), David S. Miller, Kernel Recipes, Oct 2019
     eBPF 作为一项技术的普遍性和必要性，David S. Miller，Kernel Recipes，2019 年 10 月

#### Deep Dives 深潜

-   [BPF and Spectre: Mitigating transient execution attacks](https://www.youtube.com/watch?v=6N30Yp5f9c4) ([Slides](https://ebpf.io/summit-2021-slides/eBPF_Summit_2021-Keynote-Daniel_Borkmann-BPF_and_Spectre.pdf)) , Daniel Borkmann, eBPF Summit, Aug 2021
     BPF 和 Spectre：缓解瞬时执行攻击（幻灯片），Daniel Borkmann，eBPF 峰会，2021 年 8 月
-   [BPF Internals](https://www.usenix.org/conference/lisa21/presentation/gregg-bpf) ([Slides](https://www.usenix.org/system/files/lisa21_slides_gregg_bpf.pdf)), Brendan Gregg, USENIX LISA, Jun 2021
    BPF 内部结构（幻灯片），Brendan Gregg，USENIX LISA，2021 年 6 月

#### Cilium 纤毛

-   [Advanced BPF Kernel Features for the Container Age](https://www.youtube.com/watch?v=PJY-rN1EsVw) ([Slides](https://fosdem.org/2021/schedule/event/containers_ebpf_kernel/attachments/slides/4358/export/events/attachments/containers_ebpf_kernel/slides/4358/Advanced_BPF_Kernel_Features_for_the_Container_Age_FOSDEM.pdf)), Daniel Borkmann, FOSDEM, Feb 2021
     容器时代的高级 BPF 内核功能（幻灯片），Daniel Borkmann，FOSDEM，2021 年 2 月
-   [Kubernetes Service Load-Balancing at Scale with BPF & XDP](https://www.youtube.com/watch?v=UkvxPyIJAko&t=21s) ([Slides](https://linuxplumbersconf.org/event/7/contributions/674/attachments/568/1002/plumbers_2020_cilium_load_balancer.pdf)), Daniel Borkmann & Martynas Pumputis, Linux Plumbers, Aug 2020
     使用 BPF 和 XDP 进行大规模 Kubernetes 服务负载平衡（幻灯片），Daniel Borkmann 和 Martynas Pumputis，Linux Plumbers，2020 年 8 月
-   [Liberating Kubernetes from kube-proxy and iptables](https://www.youtube.com/watch?v=bIRwSIwNHC0) ([Slides](https://docs.google.com/presentation/d/1cZJ-pcwB9WG88wzhDm2jxQY4Sh8adYg0-N3qWQ8593I/edit#slide=id.g7055f48ba8_0_0)), Martynas Pumputis, KubeCon US 2019
     将 Kubernetes 从 kube-proxy 和 iptables 中解放出来（幻灯片），Martynas Pumputis，KubeCon US 2019
-   [Understanding and Troubleshooting the eBPF Datapath in Cilium](https://www.youtube.com/watch?v=Kmm8Hl57WDU) ([Slides](https://static.sched.com/hosted_files/kccncna19/20/eBPF and the Cilium Datapath.pdf)), Nathan Sweet, KubeCon US 2019
     了解 Cilium 中的 eBPF 数据路径并对其进行故障排除（幻灯片），Nathan Sweet，KubeCon US 2019
-   [Transparent Chaos Testing with Envoy, Cilium and BPF](https://www.youtube.com/watch?v=gPvl2NDIWzY) ([Slides](https://static.sched.com/hosted_files/kccnceu19/54/Chaos Testing with Envoy%2C Cilium and eBPF.pdf)), Thomas Graf, KubeCon EU 2019
     使用 Envoy、Cilium 和 BPF 进行透明混沌测试（幻灯片），Thomas Graf，KubeCon EU 2019
-   [Cilium - Bringing the BPF Revolution to Kubernetes Networking and Security](https://www.youtube.com/watch?v=QmmId1QEE5k) ([Slides](https://www.slideshare.net/ThomasGraf5/cilium-bringing-the-bpf-revolution-to-kubernetes-networking-and-security)), Thomas Graf, All Systems Go!, Berlin, Sep 2018
     Cilium - 将 BPF 革命带入 Kubernetes 网络和安全（幻灯片），Thomas Graf，All Systems Go!，柏林，2018 年 9 月
-   [How to Make Linux Microservice-Aware with eBPF](https://www.youtube.com/watch?v=_Iq1xxNZOAo) ([Slides](https://www.slideshare.net/InfoQ/how-to-make-linux-microserviceaware-with-cilium-and-ebpf)), Thomas Graf, QCon San Francisco, 2018
     如何使用 eBPF 实现 Linux 微服务感知（幻灯片），Thomas Graf，QCon 旧金山，2018 年
-   [Accelerating Envoy with the Linux Kernel](https://www.youtube.com/watch?v=ER9eIXL2_14), Thomas Graf, KubeCon EU 2018
     使用 Linux 内核加速 Envoy，Thomas Graf，KubeCon EU 2018
-   [Cilium - Network and Application Security with BPF and XDP](https://www.youtube.com/watch?v=ilKlmTDdFgk) ([Slides](https://www.slideshare.net/ThomasGraf5/dockercon-2017-cilium-network-and-application-security-with-bpf-and-xdp)), Thomas Graf, DockerCon Austin, Apr 2017
     Cilium - 使用 BPF 和 XDP 实现网络和应用程序安全（幻灯片），Thomas Graf，DockerCon 奥斯汀，2017 年 4 月

#### Hubble 哈勃

-   [Hubble - eBPF Based Observability for Kubernetes](https://static.sched.com/hosted_files/kccnceu20/1b/Aug19-Hubble-eBPF_Based_Observability_for_Kubernetes_Sebastian_Wicki.pdf), Sebastian Wicki, KubeCon EU, Aug 2020
     Hubble - 基于 eBPF 的 Kubernetes 可观测性，Sebastian Wicki，KubeCon EU，2020 年 8 月

### 图书

-   [Learning eBPF](https://isovalent.com/learning-ebpf/), Liz Rice, O'Reilly, 2023
     学习 eBPF，Liz Rice，O'Reilly，2023
-   [Security Observability with eBPF](https://isovalent.com/ebpf-security/), Natália Réka Ivánkó and Jed Salazar, O'Reilly, 2022
     eBPF 的安全可观察性，Natália Réka Ivánkó 和 Jed Salazar，O'Reilly，2022 年
-   [What is eBPF?](https://isovalent.com/ebpf/), Liz Rice, O'Reilly, 2022
     什么是 eBPF？，Liz Rice，O'Reilly，2022
-   [Systems Performance: Enterprise and the Cloud, 2nd Edition](http://www.brendangregg.com/systems-performance-2nd-edition-book.html), Brendan Gregg, Addison-Wesley Professional Computing Series, 2020
     系统性能：企业和云，第二版，Brendan Gregg，Addison-Wesley 专业计算系列，2020 年
-   [BPF Performance Tools](http://www.brendangregg.com/bpf-performance-tools-book.html), Brendan Gregg, Addison-Wesley Professional Computing Series, Dec 2019
     BPF 性能工具，Brendan Gregg，Addison-Wesley 专业计算系列，2019 年 12 月
-   [Linux Observability with BPF](https://www.oreilly.com/library/view/linux-observability-with/9781492050193/), David Calavera, Lorenzo Fontana, O'Reilly, Nov 2019
     使用 BPF 进行 Linux 可观察性，David Calavera，Lorenzo Fontana，O'Reilly，2019 年 11 月

### 文章和博客

-   [BPF for security - and chaos - in Kubernetes](https://lwn.net/Articles/790684/), Sean Kerner, LWN, Jun 2019
     BPF 在 Kubernetes 中实现安全和混乱，Sean Kerner，LWN，2019 年 6 月
-   [Linux Technology for the New Year: eBPF](https://thenewstack.io/linux-technology-for-the-new-year-ebpf/), Joab Jackson, Dec 2018
     新年 Linux 技术：eBPF，Joab Jackson，2018 年 12 月
-   [A thorough introduction to eBPF](https://lwn.net/Articles/740157/), Matt Fleming, LWN, Dec 2017
     eBPF 全面介绍，Matt Fleming，LWN，2017 年 12 月
-   [Cilium, BPF and XDP](https://opensource.googleblog.com/2016/11/cilium-networking-and-security.html), Google Open Source Blog, Nov 2016
     Cilium、BPF 和 XDP，Google 开源博客，2016 年 11 月
-   [Archive of various articles on BPF](https://lwn.net/Kernel/Index/#Berkeley_Packet_Filter), LWN, since Apr 2011
     自 2011 年 4 月以来 BPF、LWN 上各种文章的存档
-   [Various articles on BPF by Cloudflare](https://blog.cloudflare.com/tag/ebpf/), Cloudflare, since March 2018
     自 2018 年 3 月以来，Cloudflare、Cloudflare 有关 BPF 的各种文章
-   [Various articles on BPF by Facebook](https://facebookmicrosites.github.io/bpf/blog/), Facebook, since August 2018
     自 2018 年 8 月以来 Facebook、Facebook 在 BPF 上发表的各种文章

































