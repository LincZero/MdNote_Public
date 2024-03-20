# nDPI

# 目录

# nDPI

## 资料

### DPI

- 文章（确实少）
  - [深度数据包检测DPI开发解析](https://cloud.tencent.com/developer/article/1079817)
  - [漫谈DPI工具](https://www.sdnlab.com/17370.html)

### nDPI

- github：https://github.com/ntop/nDPI
  - ~~Github Wiki：https://github.com/ntop/nDPI/wiki~~，没啥内容，大概说了下支持协议
- Doxygen文档
  - 网站文档：https://www.ntop.org/support/documentation/documentation/
    除了其他nTop的产品都能在上面这个页面中找到：如nProbe、nProbe Cento、n2disk、nEdge、nScrub、nBox、nTab、PF_RING
  - **【主要文档】**nDPI：https://www.ntop.org/guides/nDPI/
  - 这个文档也能自己构建，官方README里有他教的方法。我最开始没看到上面那个文档，我还自己构建了一次
- 作者：ntop
  - 相关产品：开源网络流量监控软件
  - tg群：http://t.me/ntop_community（但不知道为什么我刚join进去就被拉黑了？）
  - discord：https://discord.gg/frTanSPy6w
  - 官网论坛：https://www.ntop.org/support/faq/howto-join-public-ntop-discussions/
- 文章
  - 感觉这玩意国内文章比国外的还多……国外的反而少了


### ntopng

- 官方资料，见上 nDPI，都是ntop维护的
- 文章
  - https://blog.csdn.net/HongkeTraining/article/details/108447830


## 介绍

### 什么是 nDPI？

nDPI® 是一个用于深度数据包检测的开源 LGPLv3 库。基于 **OpenDPI**，它包含 ntop 扩展。
*我们尝试将它们推送到 OpenDPI 源代码树中，但没有人回复电子邮件，因此我们决定创建自己的源代码树*

### 如何编译 nDPI

#### ,编译

- 完整编译

  ```bash
  ./autogen.sh
  make
  ```

- 或编译没有任何工具或测试的库

  ```bash
  ./autogen.sh --with-only-libndpi
  make
  ```

#### 运行测试程序

- 要运行测试，请另外执行以下操作：

  ```bash
  ./tests/do.sh # 生成并检查 PCAP 文件中的差异
  ./tests/do-unit.sh # 运行单元测试
  ./tests/do-dga.sh # 运行DGA检测测试
  ```


- 或全部运行： 

  ```bash
  make check
  ```

#### 环境

请注意，编译的（最低）先决条件包括

-   GNU 工具（autoconf automake libtool pkg-config gettext flex bison）
-   GNU C 编译器 (gcc) 或 Clang

各操作系统操作：

在 Debian/Ubuntu 系统上执行以下操作：

```bash
sudo apt-get install build-essential git gettext flex bison libtool autoconf automake pkg-config libpcap-dev libjson-c-dev libnuma-dev libpcre2-dev libmaxminddb-dev librrd-dev
```

在 Arch Linux 上：

```bash
sudo pacman -S gcc git gettext flex bison libtool autoconf automake pkg-config libpcap json-c numactl pcre2 libmaxminddb rrdtool
```

在 FreeBSD 上：（请记住在 FreeBSD 上使用 `gmake` 而不是 `make`）

```bash
sudo pkg install gcc git gettext flex bison libtool autoconf automake devel/pkgconf gmake libpcap json-c pcre2 libmaxminddb rrdtool
```

On MacOS: 在 MacOS 上：

```bash
brew install coreutils gcc git gettext flex bison libtool autoconf automake pkg-config libpcap json-c pcre2 libmaxminddb rrdtool
```

在 Windows 上：（注意：所有 Windows 版本都需要 npcap 并启用 WinPcap 兼容模式）

```bash
# 支持三种构建 nDPI 的方法：

# 1. MSYS2（假设MSYS2已安装）
msys2 -c "pacman --noconfirm -S --needed --overwrite '*' git mingw-w64-x86_64-toolchain automake1.16 automake-wrapper autoconf libtool make mingw-w64-x86_64-json-c mingw-w64-x86_64-crt-git mingw-w64-x86_64-pcre mingw-w64-x86_64-libpcap"

# 2. Mingw-w64

# 3. Visual Studio (详见 windows/nDPI.sln)
```

### 如何构建文档

~~这个官方有点懒，可能人手不够……居然要自己构建doxygen文档~~。自己有文档又不在这标注一下……相应的文档：https://www.ntop.org/guides/nDPI/（和自己构建出来的是一样的，都是v4.1）

```bash
pip install --upgrade pip
pip install -r doc/requirements.txt
make doc
```

使用内置的python3网络服务器查看文档：

```bash
make doc-view
```

可能的错误：

```bash
git/public/nDPI$ make doc
make -C doc html
make[1]: Entering directory '/home/linczero/git/public/nDPI/doc'
doxygen Doxyfile.cfg
make[1]: doxygen: Command not found
make[1]: *** [Makefile:58: html] Error 127
make[1]: Leaving directory '/home/linczero/git/public/nDPI/doc'
make: *** [Makefile:970: doc] Error 2

# 这是由于没有安装doxygen导致的，解决方法：
$ apt-get update && sudo apt-get install doxygen
```

编译完成后，在 `/doc/_build/html` 路径

补充：

> 这里顺便说一下文档构造完后，一个简单的开启http访问服务的方法：
>
> ```bash
> # （安装了python就行，不需要额外安装其他东西）
> python -m http.server 8000 # python3
> ```
>
> 这里我WSL遇到了一个问题：
>
> > 主机无法访问wsl开放的8000端口的服务（该服务通过 python -m http.server 8000 开启）
> >
> > 一些调试：
> > 1. wsl2自己是能访问，wsl2中：`curl http://localhost:8000`，能正常响应html
> > 2. 主机能通过 `ssh name@localhost` 正常连接wsl2，也能通过 `ping 172.28.82.115` ping通wsl|
> > 3. 主机通过 `http://172.28.82.115:8000/` 无法正常访问wsl中的http服务，体现为一直等待响应
>
> 不过我没折腾，直接拷出来主机上了

### 如何添加新的协议解析器

添加新协议的整个流程详细：

1. 将新协议及其唯一 ID 添加到： `src/include/ndpi_protocol_ids.h`
2. 在以下位置创建新协议： `src/lib/protocols/`
3. 在整个流程期间保留的变量（作为状态变量）需要放置在： `ndpi_flow_tcp_struct` 中的 `src/include/ndpi_typedefs.h` （仅适用于 TCP）、 `ndpi_flow_udp_struct` （仅适用于 UDP），或 `ndpi_flow_struct` （适用于两者）。
4. 在以下位置添加新协议的搜索功能条目： `src/include/ndpi_protocols.h`
5. 从以下位置选择（不更改任何内容）选择位掩码： `src/include/ndpi_define.h`
6. 在 `ndpi_init_protocol_defaults` 中设置协议默认端口： `src/lib/ndpi_main.c`
7. 确保有 nBPF 支持，将 `PF_RING` 克隆到克隆 `nDPI` 的同一目录中： `git clone https://github.com/ntop/PF_RING/ && cd PF_RING/userland/nbpf && ./configure && make`
8. 从 `nDPI` 根目录， `./autogen.sh --with-pcre` （nBPF 和 PCRE 通常是可选的，但需要它们来运行/更新所有单元测试）
9. `make`
10. `make check`
11. 更新文档，将此新协议添加到 `doc/protocols.rst`

### 如何使用 nDPI 阻止选定的流量

您可以使用 nDPI 通过将选定的 Internet 流量嵌入到应用程序中来选择性地阻止该流量（请记住，nDPI 只是一个库）。 ntopng 和 nProbe cento 都可以做到这一点。

### nDPI 论文引用

Deri, Luca, et al. [nDPI: Open-source high-speed deep packet inspection](http://luca.ntop.org/nDPI.pdf) 2014 International Wireless Communications and Mobile Computing Conference (IWCMC). IEEE, 2014.

### 视频和演示

- [使用 nDPI 进行监控和安全](https://archive.fosdem.org/2021/schedule/event/nemondpi/)
- [用于网络安全和监控的网络流量分类](https://fosdem.org/2022/schedule/event/using_ndpi_to_efficiently_classify_network_traffic/)

### nDPI 相关项目

- [nfstream](https://github.com/aouinizied/nfstream)
- [nDPId](https://github.com/utoni/nDPId)

### 免责声明

虽然我们尽最大努力检测网络协议，但我们不能保证我们的软件在协议检测方面没有错误且 100% 准确。请确保您尊重用户的隐私，并且您拥有监听、捕获和检查网络流量的适当授权。

nDPI 是在美国和欧盟的注册商标。















