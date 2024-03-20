# wsl使用systemd

## 资料

- 这里直接找官方的方案：[WSL 现已提供 Systemd 支持！](https://devblogs.microsoft.com/commandline/systemd-support-is-now-available-in-wsl/)（~~仅win11，原文没说这点，但评论和笔记下面的链接都会提到这点~~。upDate 2023：后来又更新了，win10也支持了）
- 里面的细节比较多，觉得太干了就看国内博文：[WSL 2 上启用微软官方支持的 systemd](https://www.cnblogs.com/wswind/p/wsl2-official-systemd.html)，倒不如说这篇反而更全面，更推荐

## 方案类型

本文首先会介绍如何安装和配置 wsl systemd，并用两个小节去拿它去对比现有的 wsl systemd 解决方案：[genie](https://github.com/arkane-systems/genie) 和 [distrod](https://github.com/nullpo-head/wsl-distrod)。
如果你是win 10用户，目前(2022/9/30)官方支持的systemd特性还不支持此系统。你仍旧可以使用这两个开源解决方案。

### 三种方式的比较

#### 和genie的对比

genie的使用通过`genie -s`进入运行着systemd的bottle环境，通过`genie -u`退出，此处需要手动处理或额外配置`~/.bashrc`。但通过wsl直接运行的shell命令默认又不是位于systemd的bottle之中，这为vscode使用带来了一些问题，需要额外处理: [1. code命令找不到](https://github.com/arkane-systems/genie/wiki/Command-"code"-not-found-for-VScode-remote-in-bottle%3F-Here's-a-solution) ，[2. vscode server 未运行在bottle中](https://github.com/arkane-systems/genie/wiki/Running-VS-Code-server-for-WSL-inside-genie-bottle)

此外genie首次运行时，会需要等待240秒并显示出无法启动的service，用户需要手动禁用这些有问题的service，才能再下次运行时正常使用。试图[通过配置缩短等待时间，发现只是徒劳](https://github.com/arkane-systems/genie/issues/297)。

总体而言genie的使用还是较为复杂的，使用前需要完整[阅读wiki](https://github.com/arkane-systems/genie/wiki)。相比之下官方支持的systemd的使用更为简单。通过简单配置后，是开箱即用，用户无感的。这一点genie无法媲美。

#### 和distrod的对比

和官方systemd一样，distrod systemd也是开箱即用的。

distrod通过修改你的默认shell，来实现运行触发。安装启用distrod时，它自动处理了需要不支持的service。这些都无需用户进行任何额外配置。

distrod基于ruby编写运行性能很好，运行也很稳定。它还支持基于lxc社区镜像安装多个发行版，且都经过了测试，如：centos / arch / fedora / debian / ubuntu 等等。

而官方支持的systemd还是有一点是优于distrod的，那就是启用了官方systemd的wsl2实例，在用户停止操作后，会自动关闭，和未启用 systemd 时的特性一样，这有利于节约电脑的计算资源。

### win10 genie

wsl

```bash
sudo apt update
sudo apt install snapd

sudo snap install --edge --classic --channel=edge/classic systemd-genie
```

windows

```bash
wsl --shutdown
```

wsl

```bash
genie -s # 启动genie守护进程
genie -c bash # 进入genie bottle
ps --no-headers -o comm 1 # 再次运行以下命令，检查systemd是否已启动为PID 1。此时输出的结果应该是systemd
systemctl list-units # 接下来，检查您是否可以与systemd后端通信。这应该会列出systemd管理的所有单元
```



补丁：

```bash
# snap安装报错：error: Please specify a single channel
# 解决方法：用apt安装
wget -O- https://packages.arkane-systems.net/arkane.key | sudo gpg --dearmor -o /usr/share/keyrings/arkane-keyring.gpg
echo "deb [signed-by=/usr/share/keyrings/arkane-keyring.gpg arch=$(dpkg --print-architecture) components=main] https://packages.arkane-systems.net/ubuntu/ $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/arkane-systems.list > /dev/null
sudo apt update
sudo apt install -y systemd-genie
```

### win10 distrod

……

### 原生支持方案 (wsl systemd，需要window11)

启用最新的wsl systemd特性前，可先阅读微软和Canonical提供的文档：
 https://devblogs.microsoft.com/commandline/systemd-support-is-now-available-in-wsl/
 https://ubuntu.com/blog/ubuntu-wsl-enable-systemd
 https://devblogs.microsoft.com/commandline/a-preview-of-wsl-in-the-microsoft-store-is-now-available

如果需要使用微软官方支持的systmed，在目前来说你需要满足这些前置条件： 

1. ~~操作系统为windows 11~~ Update：Win10最新版也支持了
2. wsl 版本为 0.67.6 或以上（目前均为预览版本）

先查看WSL版本，Windows命令行：

```bash
$ wsl.exe --list
适用于 Linux 的 Windows 子系统分发版:
Ubuntu-20.04 (默认)

$ wsl.exe --distribution Ubuntu-20.04
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





```bash
# 检查 是否启用了systemd。输出 systemd=true 表示成功
$ echo -e "[boot]\nsystemd=true" | sudo tee -a /etc/wsl.conf
[boot]
systemd=true

# 如果命令返回的是init说明systemd未启用，如果是systemd那么你的systemd已启用成功了
$ ps --no-headers -o comm 1
init

$ systemd
Trying to run as user instance, but the system has not been booted with systemd.
```





































