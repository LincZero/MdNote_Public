# WSL

参考

-   https://learn.microsoft.com/zh-cn/windows/wsl/install（官网文档，建议看这篇）
-   https://blog.csdn.net/FSKEps/article/details/118493578#22__WSL2_59

Win10 系统安装 Linux 子系统教程(WSL2 + [Ubuntu](https://so.csdn.net/so/search?q=Ubuntu&spm=1001.2101.3001.7020) 20.04 + Gnome 桌面 ）

## WSL 简介

什么是 WSL ？
要想使用 Linux 系统，以前通常有两种方式：

-   （1）使用虚拟机
    -   缺点：开销较大
-   （2）直接使用 Linux 系统
    -   优点：可以带来最流畅的体验
    -   缺点：与 Windows 系统之间进行切换时比较麻烦，一次只能使用一个系统

为此，微软开发了适用于 Linux 的 Windows 子系统，称为 WSL，可让开发人员按原样运行 GNU/Linux 环境 - 包括大多数命令行工具、实用工具和应用程序 - 且不会产生传统虚拟机或双启动设置开销。

简单点来说，有了 WSL，就可以在 Windows 系统中**像运行软件一样运行 Linux 系统**。

## 比较WSL1与WSL2

[2table|#T 总结：除了跨操作系统文件的性能外，WSL2均优秀于WSL1]

-   功能| WSL1| WSL2
-   Windows和LInux之间的集成 | ✅ | ✅
-   启用时间短 | ✅ | ✅
-   与传统虚拟机相比，占用的资源量少 | ✅ | ✅
-   可以与当前版本的VMware和VirtualBox一起运行 | ✅ | ✅
-   托管VM | ❌ | ✅
-   完整的Linux内核 | ❌ | ✅
-   完全的系统调用兼容性 | ❌ | ✅
-   跨OS文件系统的性能 | ✅ | ❌

## 安装WSL

### 安装WSL1

#### （1）启用“适用于 Linux 的 Windows 子系统”可选功能

同样地，可以采用图形界面的操作方式，也可以采用命令行的方式。

##### 图形界面方式

在之前的基础上，勾选【虚拟机平台】。

##### 命令行方式

以管理员身份打开 PowerShell 并运行：

```bash
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```

#### （2）重启电脑

#### （3）安装 Linux 发行版，如 Ubuntu

在 Microsoft Store 中下载并安装需要的 Linux 发行版

>   这里遇到了个个人bug：
>
>   微软商店Microsoft store打不开。“重试该操作 无法加载页面，请稍后重试”
>
>   解决方法：https://zhuanlan.zhihu.com/p/363202465的一楼
>
>   Internet选项 - 连接 - 局域网设置 勾选”自动检测设置“，并取消勾选其他选项

#### （4）启动 Linux 子系统

至此，Linux 子系统就相当于 Windows 系统上安装的一个软件，可以在开始菜单子启动。

首次启动新安装的 Linux 分发版时，将打开一个控制台窗口，系统会要求你等待一分钟或两分钟，以便文件解压缩并存储到电脑上。 未来的所有启动时间应不到一秒。

然后，需要为新的 Linux 分发版创建用户帐户和密码。

### 更新WSL2

#### （3）下载 Linux 内核更新包

下载最新包：[适用于 x64 计算机的 WSL Linux 内核更新包](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi)

然后双击运行，安装

#### （4）设置 WSL 版本

```bash
PS C:\Users\user-name> wsl --set-version Ubuntu-20.04 2
正在进行转换，这可能需要几分钟时间...
有关与 WSL 2 的主要区别的信息，请访问 https://aka.ms/wsl2
转换完成。

```

**说明：**

- 若要将分发版设置为受某一 WSL 版本支持，请运行：

  ```shell
  wsl --set-version <distribution name> <versionNumber>
  ```

​		请确保将 `<distribution name>` 替换为你的分发版的实际名称，并将 `<versionNumber>` 替换为数字“1”或“2”。
​        可以随时更改回 WSL 1，方法是运行与上面相同的命令，但将“2”替换为“1”。

- 如果要使 WSL 2 成为你的默认体系结构，可以通过此命令执行该操作：

  ```c++
  wsl --set-default-version 2
  ```

  从 WSL 1 更新到 WSL 2 可能需要几分钟才能完成，具体取决于目标分发版的大小。如果--set-default-version 未列出，则表示你的 OS 不支持它，你需要更新到版本 1903（内部版本 18362）或更高版本。

## 使用 WSL

### 启动和退出 Linux 子系统

进入 Linux 子系统有以下几种方式：
（1）和正常软件一样启动，如在开始菜单中点击其图标、双击桌面快捷方式
（2）在 Windows 中打开一个终端，如 PowerShell，输入命令wsl
（3）在终端中输入命令Linux 发行版名称.exe，如ubuntu20.04.exe

退出 Linux 子系统的方式：
（1）直接关闭终端
（2）在终端中输入命令exit，此时退出了 WSL，然后输入命令 wsl -t Ubuntu-20.04，关闭 ubuntu 子系统。

### 文件系统

...

### 换源

## 安装图形界面

### Xfce4 + VcXsrv

### Gnome + VcXsrv

## 常用命令

（这里有个很烦的点，Windows版本不同，你的命令不一定支持的）

查看WSL版本，Windows命令行：

```bash
$ wsl -help # 查看参数命令

$ wsl -l -v
  NAME            STATE           VERSION
* Ubuntu-20.04    Stopped         2
 
$ wsl.exe --list # wsl -l
适用于 Linux 的 Windows 子系统分发版:
Ubuntu-20.04 (默认)

$ wsl.exe --distribution Ubuntu-20.04 # wsl -d Ubuntu-20.04
Welcome to Ubuntu 20.04.6 LTS (GNU/Linux 5.10.16.3-microsoft-standard-WSL2 x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

  System information as of Mon Jul 31 21:23:03 CST 2023

  System load:  0.0                 Processes:             96
  Usage of /:   14.5% of 250.98GB   Users logged in:       0
  Memory usage: 9%                  IPv4 address for eth0: 172.28.82.115
  Swap usage:   0%

  => There is 1 zombie process.


Expanded Security Maintenance for Applications is not enabled.

0 updates can be applied immediately.

Enable ESM Apps to receive additional future security updates.
See https://ubuntu.com/esm or run: sudo pro status



This message is shown once a day. To disable it please create the
/home/linczero/.hushlogin file.
```





















