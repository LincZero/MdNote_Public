# nTopng

# 目录

# nTopng

这个也是开源的。nTop在Github上有三个开源项目：

- ntopng， 基于web的流量和安全网络流量监控
- nDPI， 开源深度包检测软件工具包
- PF_RING， 高速分组处理框架

## 介绍

ntopng® 是一款基于 Web 的网络流量监控应用程序，在 GPLv3 下发布。它是 1998 年编写的原始 ntop 的新版本，现在在性能、可用性和功能方面进行了改进。

虽然您可以在 ntop 网站 (http://www.ntop.org) 上阅读有关 ntopng 的更多信息，但我们建议您开始阅读 doc/README.md 文件以了解如何编译和使用 ntopng。

如果您更喜欢使用预构建的包而不是源代码，请访问 http://packages.ntop.org（但这个网站坏掉了）新版本，现在在性能、可用和功能方面进行了改进。

我们为以下平台构建二进制包：

- Debian/Ubuntu LTS x64 Debian/Ubuntu LTS x64
- CentOS/RedHat/RockyLinux Linux x64
  CentOS/RedHat/RockyLinux Linux x64
- Windows x64 Windows x64
- RaspberryPI 树莓派

### 文档

如果您想了解有关 ntopng 的更多信息，请访问 [用户指南](https://www.ntop.org/guides/ntopng/) 和 [API文档](https://www.ntop.org/guides/ntopng/api/index.html)

### 细节

有关 ntopng 的更多信息，请访问 http://ntop.org

ntopng 是在美国和欧盟的注册商标。

## 什么是 ntopng

ntopng 是一个基于 Web 的流量监控应用程序，能够：

- 通过被动捕获网络流量来被动监控流量
- 收集网络流量（NetFlow、sFlow 和 IPFIX）
- 主动监控选定的网络设备
- 通过 SNMP 监控网络基础设施

ntopng 和流量收集器之间的主要区别在于，ntopng 不仅报告流量统计数据，还分析流量，根据观察到的流量类型得出结论并报告网络安全指标。

## 安装

（由于上面的网站坏掉了，这里找了下其他的替代安装方案）

参考：（这两链接的内容是一样的，都是 “虹科网络安全” 发的帖。他的CSDN博文也挺多的，主要集中为 “网络安全与可视化”）

- [【CSDN】ntopng安装和基本使用教程](https://blog.csdn.net/HongkeTraining/article/details/108447830)
- [【知乎】ntopng安装和基本使用教程](https://zhuanlan.zhihu.com/p/256995093)

注意原文环境为 ubuntu 18.04，而我的是 ubuntu 20.04，后面的内容我会作些调整

1. ### 安装ntop存储库

原文安装ntop存储库

```bash
sudo apt-get install software-properties-common wget
sudo add-apt-repository universe
sudo wget http://apt-stable.ntop.org/18.04/all/apt-ntop-stable.deb
sudo apt install ./apt-ntop-stable.deb
```

这边20.04版本大同小异

```bash
apt-get install software-properties-common wget
add-apt-repository universe
wget https://packages.ntop.org/apt-stable/22.04/all/apt-ntop-stable.deb
apt install ./apt-ntop-stable.deb 
```

其他Ubuntu版本或其他Linux发行版见完整apt：https://packages.ntop.org/apt-stable/

2. ### 安装ntop软件包

```bash
sudo apt-get clean all
sudo apt-get update
sudo apt-get install pfring-dkms nprobe ntopng n2disk cento
sudo apt-get install pfring-drivers-zc-dkms
```

3. ### 启动ntopng

```bash
systemctl start ntopng
systemctl status ntopng
```

4. ### Web GUI

启动ntopng之后，您可以查看GUI。默认情况下，可以从任何Web浏览器访问GUI 。

浏览器打开web界面输入：http://127.0.0.1:3000/



