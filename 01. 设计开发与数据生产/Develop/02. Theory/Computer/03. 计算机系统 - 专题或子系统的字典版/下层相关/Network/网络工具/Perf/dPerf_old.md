# dPerf

https://github.com/baidu/dperf

dperf 是一个100Gbps的网络性能与压力测试软件。

## 介绍

### 文档

- [配置手册](https://github.com/baidu/dperf/blob/main/docs/configuration-CN.md)
- [设计原理](https://github.com/baidu/dperf/blob/main/docs/design-CN.md)
- [编译指导](https://github.com/baidu/dperf/blob/main/docs/build.md)
- [统计说明](https://github.com/baidu/dperf/blob/main/docs/statistics-CN.md)

### 优点

- 性能强大：
  - 基于 DPDK，使用一台普通 x86 服务器就可以产生巨大的流量：千万级的 HTTP 每秒新建连接数，数百Gbps的带宽，几十亿的并发连接数
- 统计信息详细：
  - 能够输出详细的统计信息，并且识别每一个丢包
- 使用场景丰富：
  - 可用于对四层负载均衡等四层网关进行性能压力测试、长稳测试
  - 可用于对云上虚拟机的网络性能进行测试
  - 可用于对网卡性能、CPU的网络报文处理能力进行测试
  - 压测场景下，可作为高性能的HTTP Server或HTTP Client单独使用

### 性能









### 统计数据









## 开始使用

### 设置大页

```bash
# 参考如下参数编辑 '/boot/grub2/grub.cfg'，然后重启OS
linux16 /vmlinuz-... nopku transparent_hugepage=never default_hugepagesz=1G hugepagesz=1G hugepages=8
```

### 编译DPDK

```bash
# 编辑'config/common_base'打开PMD开关
# Mellanox CX4/CX5 requires 'CONFIG_RTE_LIBRTE_MLX5_PMD=y'
# HNS3 requires 'CONFIG_RTE_LIBRTE_HNS3_PMD=y'
# VMXNET3 requires 'CONFIG_RTE_LIBRTE_VMXNET3_PMD=y'

TARGET=x86_64-native-linuxapp-gcc #or arm64-armv8a-linuxapp-gcc
cd /root/dpdk/dpdk-stable-19.11.10
make install T=$TARGET -j16
```

### 编译dperf

```bash
cd dperf
make -j8 RTE_SDK=/root/dpdk/dpdk-stable-19.11.10 RTE_TARGET=$TARGET
```

### 绑定网卡

```bash
#Mellanox网卡跳过此步
#假设PCI号是0000:1b:00.0

modprobe uio
modprobe uio_pci_generic
/root/dpdk/dpdk-stable-19.11.10/usertools/dpdk-devbind.py -b uio_pci_generic 0000:1b:00.0
```

### 启动dperf server

```bash
#dperf server监听6.6.241.27:80, 网关是6.6.241.1
./build/dperf -c test/http/server-cps.conf
```

### 从客户端发送请求

```bash
#客户端IP必须要在配置文件的'client'范围内
ping 6.6.241.27
curl http://6.6.241.27/
```

## 运行测试

下面的例子运行一个HTTP CPS压力测试。

```bash
# 在server端运行dperf ./build/dperf -c test/http/server-cps.conf
# 以另一台机器作为client端，运行dperf
./build/dperf -c test/http/client-cps.conf
```

## 其他

### 限制



### 相关文章



### 贡献



### 作者



### 许可















































