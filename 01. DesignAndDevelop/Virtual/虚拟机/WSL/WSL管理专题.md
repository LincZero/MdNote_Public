# WSL管理专题

## 特性需求

我使用虚拟机时，有一些需要的特性：

[list2ut]

- 多个不同环境的虚拟机，
  可以支持灵活且频繁地创建、销毁他们
  - 虚拟机：可以
  - WSL：……
- 环境的稳定性、易迁移性
  - 虚拟机：Docker可以用镜像文件、其他虚拟机可以用Vagrant
  - WSL：……
- 性能、显卡直连
  - 虚拟机：……
  - WSL：更强，允许显卡直连

关于虚拟机的部分，在其他位置的笔记中。这里只将WSL

## **多系统管理**

仅参考：[在 Windows 中通过 WSL 2 高效使用 Docker](https://juejin.cn/post/7273026558398660648)

### 多个wsl版本管理

在开始之前惯例先检查下环境，如果没wsl环境，先去下载

```shell
# 版本
>wsl -v
WSL 版本： 2.0.9.0
内核版本： 5.15.133.1-1
WSLg 版本： 1.0.59
MSRDC 版本： 1.2.4677
Direct3D 版本： 1.611.1-81528511
DXCore 版本： 10.0.25131.1002-220531-1700.rs-onecore-base2-hyp
Windows 版本： 10.0.22631.4169

# v1和v2版本的切换
$ wsl --set-default-version 2
# 如果需要，wsl版本更新
$ wsl --update
```

注意，由于我安装了docker desktop，默认wsl不是我一开始装的ubuntu了。此时如果运行 `wsl` 会存在问题，docker desktop那个版本最好别动，要 `-d` 指定进入ubuntu那个版本

### 多个wsl系统管理

```bash
# 已经存在的wsl子系统
>wsl -l -v
  NAME                   STATE           VERSION
* docker-desktop-data    Stopped         2
  Ubuntu                 Stopped         2
  docker-desktop         Stopped         2

# 可以在线安装的列表
# 安装分发系统也可通过 Microsoft Store 搜索下载安装
$ wsl --list --online
以下是可安装的有效分发的列表。
使用 'wsl.exe --install <Distro>' 安装。

NAME                            FRIENDLY NAME
Ubuntu                          Ubuntu
Debian                          Debian GNU/Linux
kali-linux                      Kali Linux Rolling
Ubuntu-18.04                    Ubuntu 18.04 LTS
Ubuntu-20.04                    Ubuntu 20.04 LTS
Ubuntu-22.04                    Ubuntu 22.04 LTS
Ubuntu-24.04                    Ubuntu 24.04 LTS
OracleLinux_7_9                 Oracle Linux 7.9
OracleLinux_8_7                 Oracle Linux 8.7
OracleLinux_9_1                 Oracle Linux 9.1
openSUSE-Leap-15.6              openSUSE Leap 15.6
SUSE-Linux-Enterprise-15-SP5    SUSE Linux Enterprise 15 SP5
SUSE-Linux-Enterprise-15-SP6    SUSE Linux Enterprise 15 SP6
openSUSE-Tumbleweed             openSUSE Tumbleweed

# 登录到对应实例
$ wsl -d <Distribution Name>
```

只安装配置内核包即可使用 Docker Desktop，但如果条件允许的情况下，最好还是装一个完整的 Linux 分发版本的子系统

### 多个Docker管理 (docker desktop)

需要注意：

> 我一开始的理解：
> 
> - docker desktop 是 “虚拟机/子系统" 上运行 “虚拟机/docker” 吗？
>   - docker desktop 本质还是在wsl上运行（可以通过 `wsl -l -v` 命令验证，存在专门用于管理docker desktop的wsl系统）
>   - 但是却可以在不进入wsl环境的情况下直接执行docekr相关命令，就像docker直接安装在windows上
>   - 那为什么不直接在wsl环境下安装docker环境？而是要使用docker desktop？
>     （待补充）
> 
> 问GPT：
> 
> Docker Desktop 在 Windows 上如何工作？
> 
> 在 Windows 上，Docker Desktop 实际上是在一个轻量级的 Linux 虚拟机 (VM) 内部运行 Docker 引擎。这个 VM 通常使用的是 Hyper-V 技术，而不是 WSL（Windows Subsystem for Linux）直接运行。这意味着 Docker Desktop 在 Windows 上的工作方式是通过创建并管理一个虚拟机，在这个虚拟机中运行 Docker 引擎。
> 
> 虽然 Docker Desktop 不是直接在 WSL 中运行的，但它确实可以与 WSL 一起工作。从 Windows 10 开始，Microsoft 引入了 WSL 2，WSL 2 使用了类似于 Docker Desktop 所用的 Hyper-V 后端技术。因此，如果你的系统支持并且启用了 WSL 2，那么你可以选择在 WSL 2 分布式环境中安装 Docker 引擎（如通过 Docker Engine for WSL），这样就可以在 WSL 2 环境中直接使用 Docker 功能，而不需要安装完整的 Docker Desktop。
> 
> 为什么使用 Docker Desktop？
> 
> 尽管可以在 WSL 中安装 Docker，但使用 Docker Desktop 有几个优点：
> 
> - 集成度高：Docker Desktop 提供了一个统一的界面来管理 Docker 和 Kubernetes 环境。
> - 易用性：对于初学者来说，Docker Desktop 提供了一个简单的方式来开始使用 Docker。
> - 特性丰富：除了基本的容器管理外，Docker Desktop 还包括了像自动更新、团队协作工具集成等功能。
> - 支持广泛：Docker Desktop 跨平台支持 Windows 和 macOS，提供了一致的体验。

下载完后，在非wsl环境 (在windows上) 也可以完美使用docker命令

```shell
# 版本检查
$ docker -v
Docker version 24.0.6, build ed223bc

# docker列表检查
$ docker ps -a
CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES

$ docker images [-q]
REPOSITORY             TAG       IMAGE ID       CREATED         SIZE
gitlab/gitlab-ce       latest    0943abb03ebc   11 months ago   2.87GB
gitlab/gitlab-runner   latest    982f26ce4e50   11 months ago   760MB
```

### 管理 与挂载点设置

## 转 - 如何创建和管理多个WSL

### 环境安装

参考：[在WSL2中安装多个Ubuntu实例](https://blog.csdn.net/zhyh1986/article/details/134292636)

#### 第一步：在 WSL2 中安装最新的 Ubuntu

```shell
wsl --install
```

这将实现所有必需的步骤，比如：

- 在 Windows 上启用所需的可选组件（Windows Virtualisation Platform 等）
- 启用 Windows Subsystem for Linux 2（WSL2）
- 将 Linux 内核更新到最新版本
- 安装默认的 Linux 发行版，比如最新版的 Ubuntu

#### 第二步：下载适用于 WSL2 的 Ubuntu 压缩包

Ubuntu官方镜像（可手动下载，不使用以下命令）：https://cloud-images.ubuntu.com/releases

可以从 Ubuntu WSL镜像 中下载适用于 WSL2 的 Ubuntu 镜像压缩包保存到本地。
使用 Windows Terminal 或者 Powershell 来下载，在下载之前先运行以下命令移除 curl 别名：

```shell
Remove-Item alias:curl
```

接着运行以下命令下载Ubuntu镜像，一定要将整个命令复制到 Windows Terminal 或者 Powershell 中并运行：

```shell
curl (("https://cloud-images.ubuntu.com",
"releases/hirsute/release",
"ubuntu-21.04-server-cloudimg-amd64-wsl.rootfs.tar.gz") -join "/") `
--output ubuntu-21.04-wsl-rootfs-tar.gz
```

### 如何创建和管理多个WSL - 多个WSL

#### 第三步：在 WSL2 中安装第二个 Ubuntu 实例

以下命令即可实现：

```bash
wsl --import <Distribution Name> <Installation Folder> <Ubuntu WSL2 Image Tarball path>
```

1. 将 `<Distribution Name>` 改成自己想要的名字，比如ubuntu-2，以后启停会用到
2. 使用 Ubuntu 实例目标安装路径（文件夹）替换掉 `<Installation Folder>`
3. 最后用上一步下载的 Ubuntu 镜像存储位置替换掉 `<Ubuntu WSL2 Image Tarball path>`
   以上命令运行成功后可以使用 `wsl -l -v` 查看已安装的发行版。

#### 第四步：登录到第二个Ubuntu实例




