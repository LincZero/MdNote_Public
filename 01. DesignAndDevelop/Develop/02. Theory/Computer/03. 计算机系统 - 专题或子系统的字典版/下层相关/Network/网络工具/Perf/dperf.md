## DPDK环境部分 (不建议先单独安装DPDK，而是按DPerf的说明安装DPDK)

### 参考

- 官网：https://www.dpdk.org/
- 下载：http://core.dpdk.org/download/
- 安装：http://core.dpdk.org/doc/quick-start/
- 文档：https://doc.dpdk.org/guides/linux_gsg/index.html

### 安装

```bash
tar xf dpdk.tar.gz
cd dpdk

meson build
ninja -C build

# 安装
cd build
ninja
meson install
ldconfig

# 安装后的二进制库路径：/usr/local/lib/x86_64-linux-gnu/
# 安装后的头文件路径：/usr/local/include/
```

### 卸载环境

删除库和头文件

```bash
sudo rm -rf /usr/local/include/dpdk
sudo rm -rf /usr/local/lib/librte_*
```

卸载DPDK驱动

```bash
sudo rmmod igb_uio
sudo rmmod rte_kni
```

删除配置文件

```bash
sudo rm /usr/local/etc/rte.conf
```
### 额外参考 - dperf

另外 dperf 也写了个自动编译脚本：https://dperf.org/doc/html/compile-dpdk-22.11

### 额外参考 - packetMaster

PacketMaster自动化脚本

```bash
#!/bin/bash

# Debian10 编译环境安装

# 非零退出状态的命令时立即终止
set -e

# apt换源
cp /etc/apt/sources.list /etc/apt/sources.list_bak
cp sources.list /etc/apt/sources.list

# 更新apt（如果出现GPG错误，请注释这一行，脚本先更新GPG密钥）
apt update

# 获取GPG最新密钥
apt install gnupg
apt-key adv --refresh-keys --keyserver keyserver.ubuntu.com

# 如果还是报GPG密钥错误，获取指定密钥
#apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 0E98404D386FA1D9 6ED0E7B82643E131

apt update
apt upgrade -y

# 安装环境
apt install -y build-essential cmake subversion wget git nano python3-pip ninja-build net-tools pciutils zip libpcap-dev pkg-config iproute2 kmod rsync ccache

# pip换源
pip3 config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple # 清华
# pip3 config set global.index-url http://mirrors.aliyun.com/pypi/simple/ # 阿里云
# pip3 config set global.index-url https://pypi.mirrors.ustc.edu.cn/simple/ # 中科大
# pip3 config set global.index-url http://pypi.douban.com/simple/ # 豆瓣

# 创建文件夹
if [ ! -d "/root/packetmaster_install_script" ]; then
    mkdir "/root/packetmaster_install_script"
fi

# python环境
pip3 install meson pyelftools

# DPDK
cd /root/packetmaster_install_script
rm -rf dpdksource
git clone https://gitee.com/mirrors/dpdksource.git # gitee镜像
# git clone https://github.com/DPDK/dpdk
cd dpdksource
git checkout v22.11
meson build
cd build
ninja
ninja install

# cryptopp
cd /root/packetmaster_install_script
rm -rf cryptopp
git clone https://gitee.com/mirrors/cryptopp.git # gitee镜像
# git clone https://github.com/weidai11/cryptopp
cd cryptopp
make -j 4
make install
make install-lib

# PcapPlusPlus
cd /root/packetmaster_install_script
rm -rf PcapPlusPlus
git clone https://gitee.com/mirrors/PcapPlusPlus.git # gitee镜像
# git clone https://github.com/seladb/PcapPlusPlus
cd PcapPlusPlus
mkdir build
cd build
cmake -DPCAPPP_USE_DPDK=true ..
make Pcap++ -j
make install Pcap++ -j

# PacketMaster
cd /root/packetmaster_install_script
rm -rf packetmaster
git clone http://mochazi:Aa123456@192.168.1.50/packetmaster/packetmaster.git
cd packetmaster/
# Set the username and password
username="mochazi"
password="Aa123456"

# Define the target URL
target_url="192.168.1.50/"

# Generate the URL with username and password
url_with_credentials="http://${username}:${password}@${target_url}"

# Replace the URL in the .gitmodules file
sed -i "s|url = http://192.168.1.50|url = ${url_with_credentials}|" .gitmodules
git submodule update --init --recursive

# install 3rdParty
cd 3rdParty/
cd PcapTool/ && mkdir build && cd build && cmake ..
make

cd /root/packetmaster_install_script/packetmaster/scripts/
chmod +x *.sh
sed -i "s/make PacketMaster -j 8/make PacketMaster -j 4/g" package.sh
./package.sh
dpkg -i ../release/*.deb


# 设置UTF-8编码
export LC_ALL=C.UTF-8

# 更新环境变量
ldconfig
```

## DPerf环境

### 参考

- [Github](https://github.com/baidu/dperf)，有中文 README.md
- [官方文档](https://dperf.org/)，主要参考
- [参数说明](https://dperf.org/doc/html/configuration)
- 配置参考：https://dperf.org/doc/html/compile-dperf-on-ubuntu-22.04（他这里有N个版本的编译流程，就很烦）
- 配置参考：https://github.com/digger-yu/blog/blob/main/how%20to%20install%20dperf%20on%20ubuntu.md（居然还有个中文版的）

### 安装

与他DPerf的流程不同，他这个默认是要指定安装位置的。如果之前安装了，就把build文件夹删了

```bash
# 编译 DPDK
……
meson build --prefix=/root/CLion/dpdk/dpdk-stable-22.11.4/mydpdk -Denable_kmods=true -Ddisable_libs=""
ninja -C build install

# 编译 dperf
cd dperf
export PKG_CONFIG_PATH=/root/CLion/dpdk/dpdk-stable-22.11.4/mydpdk/lib/x86_64-linux-gnu/pkgconfig
make

# 运行 dperf
export LD_LIBRARY_PATH=/root/CLion/dpdk/dpdk-stable-22.11.4/mydpdk/lib/x86_64-linux-gnu
./build/dperf -h
```

如果是默认的方式安装DPDK，对应的路径有所不同：

```bash
root@msy:/usr# find ./ -name pkgconfig
./lib/x86_64-linux-gnu/pkgconfig
./lib/pkgconfig
./share/pkgconfig
```
### FAQ

#### 官方FAQ

https://dperf.org/doc/html/dperf-faq

目录：

1. 支持性
	1. 支持哪些DPDK版本？
	2. 支持哪些平台？
	3. 支持哪些网卡？
	4. 支持哪些操作系统？
	5. 有安装包吗？
2. 环境类
	1. 如何编译dperf？
	2. 如何配置大页和绑定网卡？
	3. 如何运行 dperf，参数是什么？
	4. 启动失败报网卡初始化失败
	5. 启动失败报找不到网关
3. 配置类
	1. 如何配置 dperf？
	2. 我可以在同一台主机上运行客户端和服务器吗？
	3. 我可以在同一台主机上运行客户端和服务器吗？
	4. 统计数据的含义是什么？
	5. 如何测试网络带宽？推荐的初始配置
4. 高级类
	7. 如何使用多CPU核心？
	8. 如何使用多网卡？
	9. 如何使用修改后的源地址测试 DUT（例如第 4 层负载均衡器 DPVS 的 FULLNAT 模式）？
	10. 如何验证dperf是否启动成功？
5. 更多问题
	1. 如何贡献？
	2. 如何提问？
	3. 如何学习代码？
	4. 有计划支持HTTPS吗？
	5. 有计划支持DNS吗？
	6. 绩效未达到预期水平？
	7. 如何测试大象流？
	8. 错误：“没有足够的可用端口”
	9. curl/ab无法访问dperf服务器
	10. 错误：“套接字分配失败”

#### 缺少kni

安装时报错：

```bash
In file included from src/config.h:26,
                 from src/main.c:24:
src/port.h:29:10: fatal error: rte_kni.h: No such file or directory
   29 | #include <rte_kni.h>
      |          ^~~~~~~~~~~
compilation terminated.
```

这里rte的其他头文件是有的，但没有这个kni头文件

解决方法：卸载并重新安装DPDK（根据DPerf而非DPDK官网的方法安装）

#### 无法设置大页

```bash
root@msy:~/CLion/dperf/build# dpdk-hugepages.py --clear
Unable to set pages (158 instead of 0 in /sys/devices/system/node/node0/hugepages/hugepages-2048kB/nr_hugepages).
root@msy:~/CLion/dperf/build# dpdk-hugepages.py --setup 2048000K
Unable to set pages (158 instead of 0 in /sys/devices/system/node/node0/hugepages/hugepages-2048kB/nr_hugepages).
```

先检查是否已经启用了大页

```bash
$ cat /proc/meminfo | grep Huge
AnonHugePages:         0 kB
ShmemHugePages:        0 kB
FileHugePages:         0 kB
HugePages_Total:     158
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:      158
Hugepagesize:       2048 kB
Hugetlb:          323584 kB
$ cat /proc/sys/vm/nr_hugepages
```

GPT：

> 在你的情况下，你已经尝试使用`dpdk-hugepages.py --clear`命令来清除大页，但是这个命令没有成功。这可能是因为有一些DPDK进程仍在运行，占用了这些大页。
> 
> 首先，你需要找出哪些进程正在使用大页。你可以使用`fuser`或`lsof`命令来查找哪些进程正在使用特定的文件或目录。在这种情况下，你需要查找使用`/dev/hugepages`目录的进程。
> 
> `fuser -vm /dev/hugepages`
> 
> 或者
> 
> `lsof /dev/hugepages`
> 
> 这些命令将列出正在使用大页的所有进程的PID。然后，你可以使用`kill`命令来停止这些进程。
> 
> `kill -9 <PID>`
> 
> 一旦所有的DPDK进程都被停止，你就可以再次尝试使用`dpdk-hugepages.py --clear`命令来清除大页。如果这个命令仍然没有成功，你可以尝试直接修改`/sys/devices/system/node/node0/hugepages/hugepages-2048kB/nr_hugepages`文件来清除大页。
> 
> `echo 0 > /sys/devices/system/node/node0/hugepages/hugepages-2048kB/nr_hugepages`
> 
> 这个命令将会设置系统的大页数量为0，从而清除所有的大页。如果你的系统有多个NUMA节点，你可能需要为每个节点执行这个命令。
> 
> 请注意，这些操作需要root权限，所以在执行这些命令时，你可能需要使用`sudo`。

#### 当退出后再次运行失败

他会说有另一个进程在运行，找到并删掉就好

```bash
# ./dperf -c client1.conf
EAL: Detected CPU lcores: 8
EAL: Detected NUMA nodes: 1
EAL: Detected static linkage of DPDK
EAL: Cannot create lock on '/var/run/dpdk/rte/config'. Is another primary process running?
EAL: FATAL: Cannot init config
EAL: Cannot init config
rte_eal_init fail
dpdk_eal_init fail
dpdk init fail
```

删掉：ps aux 找到：

```
root       17595  2.0  0.1 67192540 13692 pts/1  Tl   07:25   0:07 ./dperf -c client1.conf
```

#### 同机器运行CS问题

参考 dPerf 的 FAQ

例如分配了4G大页，那么就要给分别给2G，

- 单NUMA系统：均 `socket_mem 2048`
- 双NUMA系统：分别 `socket_mem 2048,0`、`socket_mem 0,2048`

#### 无三层交换机问题

参考：https://dperf.org/doc/html/dperf-performance-testing-advanced

放同一网关就行
## DPDK初始化

安装完后，还需要进行一些初始化操作

### 配置大页

手动

```bash
dpdk-hugepages.py clear
dpdk-hugepages.py --setup 409600K # 2*2048*1024=4GB
modprobe vfio-pci
dpdk-devbind.py -b vfio-pci 04:00.1 --force
```

./dpdk_env_init.sh

```bash
#!/bin/bash
set -e # 非零退出状态的命令时立即终止

GRUB_FILE="/etc/default/grub"
GRUB_FILE_TEMP="/etc/default/grub.temp"
LOCK_CORE="isolcpus=1,2,3,4,5,6,7" # 系统隔离的逻辑核
RESERVED_MEMORY=3                  # 系统保留内存
is_modified=0

# (1) 检查GRUB_CMDLINE_LINUX_DEFAULT设置是否正确
echo "(1) GRUB_check"
if ! grep 'GRUB_CMDLINE_LINUX_DEFAULT="quiet splash iommu=pt intel_iommu=on"' $GRUB_FILE >/dev/null; then
  sed 's/^GRUB_CMDLINE_LINUX_DEFAULT="quiet"/GRUB_CMDLINE_LINUX_DEFAULT="quiet splash iommu=pt intel_iommu=on"/' $GRUB_FILE >$GRUB_FILE_TEMP
  mv $GRUB_FILE_TEMP $GRUB_FILE
  echo "GRUB_CMDLINE_LINUX_DEFAULT has been set to 'quiet splash iommu=pt intel_iommu=on'."
  is_modified=1
fi

# (2) 检查GRUB_CMDLINE_LINUX设置是否正确
echo "(2) GRUB_check2"
if ! grep "GRUB_CMDLINE_LINUX=\"${LOCK_CORE}\"" $GRUB_FILE >/dev/null; then
  # 替换GRUB_CMDLINE_LINUX的值
  sed "/^GRUB_CMDLINE_LINUX=/s/\"[^\"]*\"/\"${LOCK_CORE}\"/" $GRUB_FILE >$GRUB_FILE_TEMP
  # 将修改后的临时文件覆盖原始文件
  mv $GRUB_FILE_TEMP $GRUB_FILE
  echo "GRUB_CMDLINE_LINUX has been set to '${LOCK_CORE}'."
  is_modified=1
fi

# (3) 如果有修改, 更新GRUB配置文件并提示重启
echo "(3) GRUB_change"
if [ $is_modified -eq 1 ]; then
  update-grub
  echo "System will reboot in 30 seconds..."
  sleep 30
  reboot
fi

# 新增环境变量路径
export PATH=$PATH:/usr/local/PacketMaster/scripts/DPDK

# (4) 大页相关设置
echo "(4) HugePages Set"
dpdk-hugepages.py --clear # 清除大页(hugepages)
mem_free=$(grep MemFree /proc/meminfo | awk -F: '{print $2}' | tr -d ' kB') # 获取可用内存
hugepage_size=$((mem_free - (1024 * 1024) * RESERVED_MEMORY)) # hugepage_size为 (可用内存-RESERVED_MEMORY)
hugepage_size=$((hugepage_siz37e / 2048 * 2048))
dpdk-hugepages.py --setup ${hugepage_size}K # 分配大页(hugepages)

# 加载vfio-pci模块
modprobe vfio-pci

# (5) 绑定网卡
echo "(5) Bind Card"
# 找到所有的非管理口网卡(目前只适配2600以及X10硬件, 如果后续管理口不是I211或者I210就需要修改)
nics=$(dpdk-devbind.py -s | grep drv | grep -v I211 | grep -v I210 | grep -v *Active*) # grep -E '0000:(02|82|81)'
# 绑定非管理口网卡
while read -r nic_info; do
  nic=$(echo "$nic_info" | awk '{print $1}')
  if [[ -z $nic ]]; then
    continue
  fi
  # 开始解绑网卡
  echo "bind $nic"
  dpdk-devbind.py -b vfio-pci "$nic" --force
done <<<"$nics"

# (6) 其他环境检查
echo "(6) Other"
# 检查 zip 是否已安装
if ! dpkg -s zip >/dev/null 2>&1; then
  echo "zip is not installed, installing..."
  apt update
  apt install -y zip
  echo "zip was installed."
fi
# 检查 net-tools 是否已安装
if ! dpkg -s net-tools >/dev/null 2>&1; then
  echo "net-tools is not installed, installing..."
  apt update
  apt install -y net-tools
  echo "net-tools was installed."
fi

echo "env init successfully."
```

## Dperf配置


### 主要配置参数

参考：https://dperf.org/doc/html/configuration

略

### 统计查看

客户端和服务端的统计是一样的

在运行的整个过程中显示的都是实时统计，没有累计统计：

```
seconds 第几秒的统计        cpuUsage CPU使用情况
pktRx   收包数              pktTx   发包数             bitsRx   接收比特                  bitsTx  发送比特            dropTx  发送丢包

tcpRx   TCP报文            tcpTx    TCP报文             udpRx    UDP报文                 udpTx   UDP报文 
arpRx   ARP报文            arpTx    ARP报文             icmpRx   ICMP报文                icmpTx  ICMP报文

tosRx   0                  otherRx  0                  badRx    接收错包
udpRt   0                  udpDrop  udp丢包            tcpDrop  tcp丢包
skOpen  socket打开数       skClose  socket关闭数       skCon    socket连接数 (等同设置的cc项)   skErr   socket连接错误数             

ierrors 输入错误            oerrors  输出错误           imissed  0
```

累计统计会在测试结束后给出：

```
-----------------------
dperf Test Finished
Version: 1.7.0-dev
License: Apache 2.0
Author:  Jianzhang Peng
-----------------------

Total Numbers:
pktRx   21                 pktTx    1,111              bitsRx   38,696             bitsTx  13,203,696         dropTx  0                
tcpRx   0                  tcpTx    0                  udpRx    13                 udpTx   1,100
arpRx   0                  arpTx    11                 icmpRx   0                  icmpTx  0
tosRx   0                  otherRx  8                  badRx    0
udpRt   1,000              udpDrop  13                 tcpDrop  0
skOpen  100                skClose  0                  skCon    100                skErr   0
ierrors 0                  oerrors  0                  imissed  0
```

另外，前面两个是UDP的，TCP的还会再多一些统计项处理：

```
seconds 153                cpuUsage 0
pktRx   0                  pktTx    39,980             bitsRx   0                  bitsTx  19,830,080         dropTx  0

tcpRx   0                  tcpTx    39,980             udpRx    0                  udpTx   0
arpRx   0                  arpTx    0                  icmpRx   0                  icmpTx  0

tosRx   0                  otherRx  0                  badRx    0

# 这个部分不同
synRx   0                  synTx    39,980             finRx    0                  finTx   0                  rstRx   0          rstTx 0
synRt   39,980             finRt    0                  ackRt    0                  pushRt  0
tcpDrop 0                  udpDrop  0                  ackDup   0
skOpen  0                  skClose  19,990             skCon    80,020             skErr   19,990             rtt(us) 0.0 # TCP会多一个rtt，借此可以测试网络迟延
httpGet 0                  http2XX  0                  httpErr  0

ierrors 0                  oerrors  0                  imissed  0
```

## 正式测试

- server：0000:04:00.1、cpu1、port2480
- client ：0000:04:00.0、cpu0

### 快速测试

参考：https://dperf.org/doc/html/dperf-quick-start

server0.conf (亲测可用，但非双端测试)

```
mode        server
cpu         1
duration    10m
port        0000:04:00.1    6.6.241.27   6.6.241.31
client      6.6.241.31      1
server      6.6.241.27      1
listen      80 1
```

```shell
./dperf -c server0.conf
```

### 基础测试 - 新连接速率测试

参考：https://dperf.org/doc/html/dperf-performance-testing-basic

server1.conf (亲测可用)

```markdown
# daemon
mode            server
tx_burst        128
cpu             1
duration        3m
payload_size    1

# numa2
port            0000:04:00.1    6.6.247.3    6.6.247.1  b4:a9:fc:ab:7a:85

# addr_start      num
client          6.6.245.3       100

# addr_start      num
server          6.6.247.3       1

# port_start      num
listen          2480              5
```

- 服务器侦听 IP 6.6.247.3，端口范围为 80-84。
- 仅接受 6.6.245.3-6.6.245.102 范围内的客户端地址。源地址超出此范围的 TCP 数据包将被丢弃或重置。 Ping 不受影响。
- 服务器绑定到具有互连 IP 6.6.247.3（重用侦听 IP）和网关 6.6.247.1（交换机 IP）的单个网络接口。
- 新连接速率测试中无法开启Keepalive。
- 将 HTTP 响应长度设置为最小值： `payload_size 1`

client-newCC.conf  (亲测可用)

```markdown
mode            client
tx_burst        128
launch_num      10
cpu             0
payload_size    1
duration        2m
cps             2.1m

# port           pci             addr      gateway        [mac]
port            0000:04:00.0    6.6.245.3 6.6.245.1  b4:a9:fc:ab:7a:85

# addr_start      num
client          6.6.245.3       100

# addr_start      num
server          6.6.247.3       1
# port_start      num
listen          2480              5
```

- 客户端以服务器的监听地址为目标。 IP为6.6.247.3，端口范围为80-84。
- 客户端使用地址池中的IP地址：6.6.245.3-6.6.245.102。
- 客户端绑定到具有互连 IP 6.6.245.3（重用池中的地址）和网关 6.6.245.1（交换机 IP）的单个网络接口。
- 将 HTTP 响应长度设置为最小值： `payload_size 1`
- 将 CPS (每秒连接数) 目标设置为 200 万。根据CPU容量灵活调整CPS值。建议从较小的值开始，例如“10k”。

```bash
# Run the server
./dperf -c server1.conf

# Run the client
./dperf -c client1.conf
```

### 基础测试 - 并发连接测试

client-concurrentConnections.conf

```markdown
mode            client
tx_burst        128
launch_num      10
cpu             0
payload_size    1
duration        10m
cps             0.5m
cc              100m


keepalive       60s

# port           pci             addr      gateway    [mac]
port            0000:04:00.0    6.6.245.3 6.6.245.1  b4:a9:fc:ab:7a:85

# addr_start      num
client          6.6.245.3       100

# addr_start      num
server          6.6.247.3       1
# port_start      num
listen          80              32
```

- 客户端配置已针对并发连接测试进行调整。
- Keepalive 设置为 60 秒以维持长期连接。
- CPS 目标设定为 50 万。
- CC（并发连接数）设置为1亿。根据您的具体测试要求调整这些值。

### 基础测试 - 带宽测试

带宽测试建立在并发连接测试的基础上：

- 通过将 `payload_size` 设置为 1400 来增加消息长度。
- 减少并发连接数，例如将 `cc` 设置为3000。
- 提高请求发送速度，例如每 1 毫秒发送一次请求。
- 由于并发级别较低，CPS 较低。

client-bandwidth.conf

```markdown
mode            client
tx_burst        128
launch_num      10
cpu             0
payload_size    1400
duration        10m
cps             10
cc              10
keepalive       60s

# port           pci             addr      gateway    [mac]
port            0000:04:00.0    6.6.245.3 6.6.245.1  b4:a9:fc:ab:7a:85

# addr_start      num
client          6.6.245.3       5

# addr_start      num
server          6.6.247.3       1
# port_start      num
listen          2480              32
```

### 基础测试 - PPS测试

```markdown
mode            client
tx_burst        128
launch_num      10
cpu             0
payload_size    1
duration        2m
cps             400
cc              3000
keepalive       1ms

# port           pci             addr         gateway    [mac]
port            0000:01:00.0    6.6.245.3   6.6.245.1   b4:a9:fc:ab:7a:85

# addr_start      num
client          6.6.245.3        100

# addr_start      num
server          6.6.247.3       1
# port_start      num
listen          80              5
```

- 对于最小数据包长度，有效负载大小设置为 1 字节。

## 个人自用测试项

参考：https://dperf.org/doc/html/configuration

另外注意：

- 哪怕在注释里，也不能有中文，否则直接不会运行也不会报错
- 不支持行尾注释，注释只能单独一行
- 逗号后面不要加空格

### 3000并发1ms

client.conf

```yaml
# Occupy resource Settings
mode            client
cpu             0
socket_mem      1920

# General Settings
duration        2m
protocol        udp

# Client setup
tx_burst        128
launch_num      10
# payload_size  1400
packet_size     64
cps             300
cc              3000
keepalive       1ms
pipeline        0

# Network topology setting
# port          pci             addr       gateway    [mac]
port            0000:04:00.0    6.6.245.11 6.6.245.1  b4:a9:fc:ab:7a:91
# addr_start    num
client          6.6.245.11      10
# addr_start    num
server          6.6.245.1       1
# port_start    num
listen          2480            1
```

server.conf

```yaml
# Occupy resource Settings
mode            server
cpu             1
socket_mem      1920

# General Settings
duration        2m
protocol        udp

# Server setup
# send_window
keepalive       1ms

# Network topology setting
# port          pci             addr       gateway    [mac]
port            0000:04:00.1    6.6.245.2  6.6.245.1  b4:a9:fc:ab:7a:80
# addr_start    num
client          6.6.245.11      10
# addr_start    num
server          6.6.245.2       1
# port_start    num
listen          2480            1
```

### 10k并发1ms

client.conf

```yaml
# Occupy resource Settings
mode            client
cpu             0
socket_mem      1920

# General Settings
duration        2m
protocol        udp

# Client setup
tx_burst        128
launch_num      10
# payload_size  1400
packet_size     64
cps             1k
cc              10k
keepalive       1ms

# Network topology setting
# port          pci             addr       gateway    [mac]
port            0000:04:00.0    6.6.245.11 6.6.245.1  b4:a9:fc:ab:7a:91
# addr_start    num
client          6.6.245.11      10
# addr_start    num
server          6.6.245.1       1
# port_start    num
listen          2480            1
```

server.conf

```yaml
# Occupy resource Settings
mode            server
cpu             1
socket_mem      1920

# General Settings
duration        2m
protocol        udp

# Server setup
# send_window
keepalive       1ms

# Network topology setting
# port          pci             addr       gateway    [mac]
port            0000:04:00.1    6.6.245.2  6.6.245.1  b4:a9:fc:ab:7a:80
# addr_start    num
client          6.6.245.11      10
# addr_start    num
server          6.6.245.2       1
# port_start    num
listen          2480            1
```

### 200 ip x 512 port = 10k 并发

参考：https://blog.51cto.com/u_11529070/9214521，但弱化了一些参数，万用表100k就崩了

client.conf

```yaml
# Occupy resource Settings
mode            client
cpu             0
socket_mem      1920

# General Settings
duration        2m
protocol        udp

# Client setup
tx_burst        128
launch_num      10
packet_size     64
cps             1k
cc              10k
keepalive       1ms
lport_range     1 512

# Network topology setting
# port          pci             addr       gateway    [mac]
port            0000:04:00.0    6.6.245.11 6.6.245.1  b4:a9:fc:ab:7a:91
# addr_start    num
client          6.6.245.11      200
# addr_start    num
server          6.6.245.1       1
# port_start    num
listen          2480            1
```

server.conf

```yaml
# Occupy resource Settings
mode            server
cpu             1
socket_mem      1920

# General Settings
duration        2m
protocol        udp

# Server setup
# send_window
keepalive       1ms

# Network topology setting
# port          pci             addr       gateway    [mac]
port            0000:04:00.1    6.6.245.2  6.6.245.1  b4:a9:fc:ab:7a:80
# addr_start    num
client          6.6.245.11      200
# addr_start    num
server          6.6.245.2       1
# port_start    num
listen          2480            1
```

### 1488095pps

复习一下

$$
\begin{aligned}
        148809523 &*8*(64+12+8)=99999999456 &&=100G\\
(千万包)~14880952  &*8*(64+12+8)=9999999744  &&=10G\\
(百万包)~1488095   &*8*(64+12+8)=999999840   &&=1G\\
        148809    &*8*(64+12+8)=99999648    &&=100M\\
\end{aligned}
$$

### 单连接大流

client.conf

```yaml
# Occupy resource Settings
mode            client
cpu             0
socket_mem      1920

# General Settings
duration        2m
protocol        udp

# Client setup
tx_burst        128
launch_num      10
# payload_size  1400
packet_size     64
cps             1k
cc              10k
keepalive       1ms

# Network topology setting
# port          pci             addr       gateway    [mac]
port            0000:04:00.0    6.6.245.11 6.6.245.1  b4:a9:fc:ab:7a:91
# addr_start    num
client          6.6.245.11      10
# addr_start    num
server          6.6.245.1       1
# port_start    num
listen          2480            1
```

server.conf

```yaml
# Occupy resource Settings
mode            server
cpu             1
socket_mem      1920

# General Settings
duration        2m
protocol        udp

# Server setup
# send_window
keepalive       10us

# Network topology setting
# port          pci             addr       gateway    [mac]
port            0000:04:00.1    6.6.245.2  6.6.245.1  b4:a9:fc:ab:7a:80
# addr_start    num
client          6.6.245.11      10
# addr_start    num
server          6.6.245.2       1
# port_start    num
listen          2480            1
```
### 20k连接速度 tcp

参考：https://blog.51cto.com/u_11529070/9214521，但弱化了一些参数，万用表100k就崩了

```
mode            client
tx_burst        128
launch_num      10
cpu             0
socket_mem      2048

payload_size    1
duration        2m
cps             20k

#port           pci             addr      gateway        [mac]
port            0000:04:00.0    6.6.245.11 6.6.245.1  b4:a9:fc:ab:7a:91

#               addr_start      num
client          6.6.245.11		20

#               addr_start      num
server          6.6.245.2       1
#               port_start      num
listen          2480            1
```

```
#daemon
mode            server
tx_burst        128
cpu             7
socket_mem      1920

duration        3m
payload_size    1

#numa2
port            0000:04:00.1    6.6.245.2  6.6.245.1  b4:a9:fc:ab:7a:80

#               addr_start      num
client          6.6.245.11		20

#               addr_start      num
server          6.6.245.2       1

#               port_start      num
listen          2480            1
```

### 1M PPS 大象流

参考：https://dperf.org/doc/html/elephant

在之前的版本中，dperf 对于单个连接来说，单向最大 PPS 为 100K，两个方向最大 PPS 为 200K。在某些场景下，我们需要测试单流1M PPS，这种高PPS的流称为大象流。本文介绍如何配置 dperf 来测试单流 1M PPS。注意大象流仅支持UDP协议。

核心配置：

- pipeline。原来的dperf客户端需要收到服务器的响应后才能发送下一个请求；使用pipeline可以一次发送多个请求，类似于http的pipeline请求；这样PPS就可以翻倍。
- keepalive。 dperf原来的keepalive间隔只能配置为最小10us，现在可以配置为最小0。更小的间隔可以让dperf更快地发送请求。
- flood。这是单向流的开关，表示连接不需要等待响应。

#### 单向大象流配置示例

服务器配置

```
mode            server
protocol        udp
tx_burst        4
payload_size    1
keepalive       1s
cpu             1
duration        2h
```

客户端配置

```
mode            client
protocol        udp
tx_burst        4
payload_size    1
keepalive       1us
pipeline        1
cc        1
flood
cpu             0
duration        1h
```

#### 双向大象流配置示例

server configuration 服务器配置

```
mode            server
protocol        udp
tx_burst        4
payload_size    1
keepalive       1s
cpu             1
duration        2h
```

client configuration 客户端配置

```
mode            client
protocol        udp
tx_burst        4
payload_size    1
keepalive       0us
socket_mem      2048
pipeline        10
cc        1
cpu             0
duration        1h
```

### 100G带宽

参考：https://zhuanlan.zhihu.com/p/601137162

客户端 12核x10网口x65535端口 -> 12核x12网口x1端口，1450大小

cc 8000、cps2000

### 向大量 IP 发送

参考：https://dperf.org/doc/html/dperf-change-dip
### HTTP服务

参考：https://dperf.org/doc/html/dperf-http-server

```plaintext
mode            server
protocol        http # 关键设置
jumbo           9000
tx_burst        6

payload_size    1m
send_window     6

keepalive       1s
cpu             0
duration        100m
port            0000:00:06.0    192.168.4.2    192.168.4.3
client          192.168.4.3     1
server          192.168.4.2     1
listen          80              1
```
### 计算备注

$总连接数=客户端IP数*65535*服务器IP数*监听端口数$

socket数计算

- 例如：
	- $(客户端端口~65536\times客户端IP~20)\times(服务端IP~1\times服务端端口~20) = 26214000$，$*80Byte/1GB= 内存大小1.95GB$
	- $(客户端端口~65536\times客户端IP~10)\times(服务端IP~1\times服务端端口~10) = 06553500$，$*80Byte/1GB = 内存大小0.49GB$

## 性能

### Dperf标榜性能

见大象流

在之前的版本中，dperf 对于单个连接来说，单向最大 PPS 为 100K，两个方向最大 PPS 为 200K。在某些场景下，我们需要测试单流1M PPS，这种高PPS的流称为大象流。本文介绍如何配置 dperf 来测试单流 1M PPS。注意大象流仅支持UDP协议。

### 基准测试

机器参数

```
卡：
04:00.0 Ethernet controller: Intel Corporation I350 Gigabit Network Connection (rev 01)

CPU
ip:                  1.208
Model name:            Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU(s):                  8
CPU max MHz:         4000.0000
CPU min MHz:         800.0000
Caches (sum of all):
  L1d:                   128 KiB (4 instances)
  L1i:                   128 KiB (4 instances)
  L2:                    1 MiB (4 instances)
  L3:                    8 MiB (1 instance)

内存：
总大页：4194304K = 4G
配置分出：1920*2MB = 3840MB (3.75G)
```

#### UDP CC-1000k

```yaml
# 配置
# 使用资源：1000k * 80Byte * 2 = 0.08G * 2
# Occupy resource Settings
mode            client
cpu             0
socket_mem      1920
port            0000:04:00.0    6.6.245.121 6.6.245.1   b4:a9:fc:ab:7a:91
# General Settings
duration        1m
protocol        udp
packet_size     64
keepalive       1ms
client          6.6.245.11      100
server          6.6.245.2       1
listen          2480            100
lport_range     1 100
# Client setup
tx_burst        128
launch_num      10
packet_size     64
cps             10k
cc              1000k

# 发送端：发1.4Mpps(计发送丢包可5Mpps) * 64*8bpp ~= 777Mbps，收53Kpps * 64*8bpp ~= 3.4MB，连接数360k
seconds 50                 cpuUsage 100 
pktRx   53,235             pktTx    4,659,163          bitsRx   27,256,320         bitsTx  2,385,491,456      dropTx  3,254,020         
tcpRx   0                  tcpTx    0                  udpRx    53,235             udpTx   4,659,163         
arpRx   0                  arpTx    0                  icmpRx   0                  icmpTx  0                 
tosRx   0                  otherRx  0                  badRx    0                 
udpRt   4,598,815          udpDrop  0                  tcpDrop  0                 
skOpen  8,580              skClose  0                  skCon    358,240            skErr   0                 
ierrors 0                  oerrors  0                  imissed  49,808,123 

# 接收端：收发 1.4Mpps * 64*8bpp ~= 718Mbps
seconds 59                 cpuUsage 44  
pktRx   1,403,848          pktTx    1,403,848          bitsRx   718,770,176        bitsTx  718,770,176        dropTx  0                 
tcpRx   0                  tcpTx    0                  udpRx    1,403,848          udpTx   1,403,848         
arpRx   0                  arpTx    0                  icmpRx   0                  icmpTx  0                 
tosRx   0                  otherRx  0                  badRx    0                 
udpRt   0                  udpDrop  0                  tcpDrop  0                 
skOpen  0                  skClose  0                  skCon    0                  skErr   0                 
ierrors 0                  oerrors  0                  imissed  0    
```
#### UDP CC-10000k

```yaml
# 配置
# 使用资源：10000k * 80Byte * 2 = 0.75G * 2
# Occupy resource Settings
mode            client
cpu             0
socket_mem      1920
port            0000:04:00.0    6.6.245.121 6.6.245.1   b4:a9:fc:ab:7a:91
# General Settings
duration        1m
protocol        udp
packet_size     64
keepalive       1us
client          6.6.245.11      100
server          6.6.245.2       1
listen          2480            100
lport_range     1 1000
# Client setup
tx_burst        128
launch_num      10
packet_size     64
cps             10k
cc              10000k

# 结果，同上，本来就只能到350k
```

#### TCP CC-1000k

```yaml
# 配置
# 使用资源：1000k * 80Byte * 2 = 0.08G * 2
# Occupy resource Settings
mode            client
cpu             0
socket_mem      1920
port            0000:04:00.0    6.6.245.121 6.6.245.1   b4:a9:fc:ab:7a:91
# General Settings
duration        1m
protocol        tcp
packet_size     64
keepalive       1ms
client          6.6.245.11      100
server          6.6.245.2       1
listen          2480            100
lport_range     1 100
# Client setup
tx_burst        128
launch_num      10
packet_size     64
cps             10k
cc              1000k

# 发送端：收发 1.4Mpps(计发送丢包可1.5Mpps) * 64*8bpp ~= 777Mbps (满1G，他这里的统计不算前导码和帧间隙的)，连接数211k
seconds 35                 cpuUsage 49  
pktRx   1,420,809          pktTx    1,517,316          bitsRx   727,294,512        bitsTx  776,695,536        dropTx  94,611            
tcpRx   1,420,809          tcpTx    1,517,316          udpRx    0                  udpTx   0                 
arpRx   0                  arpTx    0                  icmpRx   0                  icmpTx  0                 
tosRx   0                  otherRx  0                  badRx    0                 
synRx   9,981              synTx    10,641             finRx    0                  finTx   0                  rstRx   0          rstTx 0         
synRt   641                finRt    0                  ackRt    0                  pushRt  91,301            
tcpDrop 5,393              udpDrop  0                  ackDup   0                 
skOpen  10,000             skClose  152                skCon    211,166            skErr   152               
tcpReq  1,506,675          tcpRsp   1,405,435         
ierrors 0                  oerrors  0                  imissed  34,902  

# 服务端：同上
seconds 60                 cpuUsage 49  
pktRx   1,420,782          pktTx    1,459,046          bitsRx   727,279,136        bitsTx  746,865,776        dropTx  38,793            
tcpRx   1,420,782          tcpTx    1,459,046          udpRx    0                  udpTx   0                 
arpRx   0                  arpTx    0                  icmpRx   0                  icmpTx  0                 
tosRx   0                  otherRx  0                  badRx    0                 
synRx   10,078             synTx    10,361             finRx    0                  finTx   0                  rstRx   0          rstTx 0         
synRt   410                finRt    0                  ackRt    0                  pushRt  62,280            
tcpDrop 24,299             udpDrop  0                  ackDup   0                 
skOpen  9,951              skClose  718                skCon    438,470            skErr   718               
tcpReq  1,386,405          tcpRsp   1,448,685         
ierrors 0                  oerrors  0                  imissed  0
```

#### HTTP CC-1000k

仅修改包大小和协议（非64帧长似乎有些怪）

```yaml
# 配置
# 使用资源：1000k * 80Byte * 2 = 0.08G * 2
# Occupy resource Settings
mode            client
cpu             0
socket_mem      1920
port            0000:04:00.0    6.6.245.121 6.6.245.1   b4:a9:fc:ab:7a:91
# General Settings
duration        1m
protocol        http
packet_size     128
keepalive       1ms
client          6.6.245.11      100
server          6.6.245.2       1
listen          2480            100
lport_range     1 100
# Client setup
tx_burst        128
launch_num      10
packet_size     64
cps             10k
cc              1000k

# 发送端：发 1.4Mpps(计发送丢包可1.7Mpps，接收少了，相较于tcp反而高了) * 128*8bpp = 1523MB < 817MB ，，连接数371k
seconds 52                 cpuUsage 69  
pktRx   803,396            pktTx    1,716,083          bitsRx   817,265,504        bitsTx  817,507,840        dropTx  306,787           
tcpRx   803,396            tcpTx    1,716,083          udpRx    0                  udpTx   0                 
arpRx   0                  arpTx    0                  icmpRx   0                  icmpTx  0                 
tosRx   0                  otherRx  0                  badRx    0                 
synRx   10,250             synTx    12,031             finRx    0                  finTx   0                  rstRx   0          rstTx 0         
synRt   2,171              finRt    0                  ackRt    0                  pushRt  170,892           
tcpDrop 31,499             udpDrop  0                  ackDup   0                 
skOpen  9,860              skClose  2,094              skCon    371,192            skErr   2,094             
httpGet 942,375            http2XX  761,677            httpErr  0                 
ierrors 0                  oerrors  0                  imissed  19,883 

# 服务端：同上
seconds 52                 cpuUsage 41  
pktRx   1,429,757          pktTx    828,705            bitsRx   711,520,720        bitsTx  842,996,592        dropTx  10,111            
tcpRx   1,429,757          tcpTx    828,705            udpRx    0                  udpTx   0                 
arpRx   0                  arpTx    0                  icmpRx   0                  icmpTx  0                 
tosRx   0                  otherRx  0                  badRx    0                 
synRx   10,105             synTx    10,601             finRx    0                  finTx   0                  rstRx   0          rstTx 0         
synRt   546                finRt    0                  ackRt    0                  pushRt  38,344            
tcpDrop 3,855              udpDrop  0                  ackDup   0                 
skOpen  10,055             skClose  961                skCon    362,167            skErr   961               
httpGet 0                  http2XX  818,104            httpErr  779,760           
ierrors 0                  oerrors  0                  imissed  0
```

#### 单端极限pps

修改了tx_burst、flood、pipeline、launch_num、cc

仅发送不接收

```yaml
# 配置 (尝试使pps达到最大)
# 使用资源：2000k * 80Byte = 0.15G
# Occupy resource Settings
mode            client
cpu             0
socket_mem      3840
port            0000:04:00.0    6.6.245.11  6.6.245.1   b4:a9:fc:ab:7a:91
# General Settings
duration        1m
protocol        udp
packet_size     64
client          6.6.245.11      20
server          6.6.245.2       1
listen          2480            10
lport_range     1               10
# Client setup
keepalive       1us
tx_burst        1024
launch_num      1000
#cps             10k
cc              100
flood
pipeline        100

# 发送端：udp含丢包6.2Mpps、tcp和http均5.8Mpps (由于单端，全发的syn包，非udp无法开启pipeline选项)
seconds 21                 cpuUsage 100 
pktRx   0                  pktTx    6,288,524          bitsRx   0                  bitsTx  3,219,724,288      dropTx  6,287,360         
tcpRx   0                  tcpTx    0                  udpRx    0                  udpTx   6,288,524         
arpRx   0                  arpTx    0                  icmpRx   0                  icmpTx  0                 
tosRx   0                  otherRx  0                  badRx    0                 
udpRt   0                  udpDrop  0                  tcpDrop  0                 
skOpen  0                  skClose  0                  skCon    100                skErr   0                 
ierrors 0                  oerrors  0                  imissed  0                 
```

#### 图


#### 收发形式 (抓包)







