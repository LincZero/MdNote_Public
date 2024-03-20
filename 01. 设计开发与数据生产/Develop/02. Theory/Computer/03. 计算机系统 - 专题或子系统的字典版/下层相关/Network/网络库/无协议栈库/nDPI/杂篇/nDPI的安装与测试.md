# nDPI

# 目录

# nDPI 的安装与测试

参考：

- [【博客园】nDPI的安装与测试](https://www.cnblogs.com/vancasola/p/9817283.html)
  - [官方Quick Start](https://www.ntop.org/wp-content/uploads/2013/12/nDPI_QuickStartGuide.pdf)
  - [nDPI 的 github](https://github.com/ntop/nDPI)

## 简介

nDPI是一个开源的基于 OpenDPI 的 DPI 库，目前由 ntop在维护

- nDPI 提供以下功能：
  - 应用层协议检测
  - 加密流量检测
  - 子协议检测
- 可以检测的内容包括：
  - 某个 IP 的：包个数、比特数、流总数、nDPI的吞吐量
  - 源目的端口号
  - 每个协议的：包个数、比特数、流个数
  - 一些测量的统计信息

## nDPI的环境依赖项安装

```bash
$ sudo apt install autotools # GNU autotools
$ sudo apt install libtool # libtool
$ sudo apt install gawk
$ sudo apt install gcc
$ sudo apt install build-essential
```

## nDPI 安装

```bash
$ git clone https://github.com/ntop/nDPI.git
$ cd <nDPI source code directory>
$ ./autogen.sh
$ ./configure
$ make
$ cd example
$ make
```

## nDPI测试

- 通过 ifconfig 查看网卡设备信息，选择其中的网卡 ens33

  ```bash
  $ ifconfig
  ```

- 记得开启 root

- 运行测试 nDPIReader，参数 -i 表示指定网卡号，-s 指定测试时间

- 本测试中 测试网卡 ens33，测量10s

- 开始测试以后，疯狂刷新 百度 qq 谷歌 等网站

- 测试结果如下

  ```bash
  $ ./ndpiReader -i ens33 -s 10 # 这里的 -s 是测试时长，可以调得更长
  ……
  ```

# 