# Vagrant

参考：

- 官网： https://www.vagrantup.com/
- 教程： https://developer.hashicorp.com/vagrant/tutorials
- Vagrant中文文档： https://tangbaoping.github.io/vagrant_doc_zh/v2/
- 《Vagrant官方中文文档》： https://www.modb.pro/db/89231
- 视频教程： [bilibili - 【Vagrant快速入门】让虚拟机像容器一样方便！](https://www.bilibili.com/video/BV1me411f7sU)
  - 共9p 28min
  - 配套课件： https://www.yuque.com/wukong-zorrm/xmk0v0

感觉中文资料不是很多

## 介绍

### Vagrant是什么

Vagrant是一个软件，可以自动化虚拟机的安装和配置流程。目前市面上个人PC的主流操作系统不是Windows就是MacOS。对于这些用户，如果需要用Linux环境进行开发或学习，使用虚拟机无疑是最方便的选择。

而Vagrant更进一步，可以让你通过编写一个Vagrantfile来控制虚拟机的启动、虚拟机网络环境的配置、虚拟机与主机间的文件共享，以及启动后自动执行一些配置脚本，比如自动执行一个shell  script来安装一些必备的开发工具，如Mysql。

**这意味着，当你需要在多台机器间同步开发进度时，只需要同步Vagrantfile，就可以保证各台机器拥有一致的开发环境。**

另外，即便对于计算机小白用户，Vagrant也是一个利器。以前我们为了学习一门语言，必须先手动安装这门语言的编译环境。这期间的各种痛苦想必各位深有体会。有了Vagrant后，我们可以下载别人写好的Vagrantfile，然后运行`vagrant up`，vagrant就会自动下载虚拟机镜像，自动加载镜像并配置虚拟机，然后交给我们一个即开即用的学习环境。

这样，由于使用了教师调试好的学习环境，小白们就可以免受环境相关的各种Bug的困扰，这无疑会提高学习效率。

这个教程总结了Vagrant的基本使用方法。

### Vagrant的依赖程序

既然是配置虚拟机，那么自然需要虚拟机程序和被虚拟的操作系统镜像（Image）。

前者常用的选择有VirtualBox和VMWare，后者则包括Ubuntu、FreeBSD等等。
Vagrant称前者为`provider`，称后者为`box`。

原则上，我们可以自由搭配`provider`和`box`，但由于VirtualBox开源且免费，Vagrant将其作为默认的provider。所以，一般会先安装VirtualBox，再安装Vagrant。

### Vagrant的基本概念

假设我们使用VirtualBox作为provider。

安装好Vagrant后，新建一个空文件夹，将其路径视作项目的根路径。然后运行终端并进入这个路径，键入`vagrant init`，此文件夹中会多出一个Vagrantfile。用文本编辑器打开后，会发现该文件由ruby语言编写，且大部分行都被注释掉。一般未注释的内容如下：

```bash
Vagrant.configure("2") do |config|
    config.vm.box = "base"
end 
```

解释如下：

1.  `do...end`结构在ruby中称为块（block），可以简单理解为`Vagrant.configure("2")`执行到某一步时程序被挂起，并将一个需要配置的对象交给块，由块内的语句进行具体配置，当块内的语句依次执行完后，配置好的对象又被交回给`Vagrant.configure("2")`，之前被挂起的程序则继续执行直到完毕。
2.  `.configure("2")`中的`2`是指配置文件的语法规则的版本。虽然是基于ruby，Vagrantfile仍然有一套自己的语法细则。按照时间先后来说，目前（2016年7月）有V1与V2两套配置语法。自然新的语法更先进。所以目前最新版本的Vagrant（1.8.4）默认使用V2规则。也许未来还会有V3、V4……
3.  `config.vm.box`直译过来即“配置虚拟机盒子”，因此这一步指定将要使用哪个虚拟机镜像（box）。接下来详细解释下Vagrant如何管理boxes。

## 对比

### vagrant vs docker

参考：https://kinsta.com/blog/vagrant-vs-docker/

DevOps 团队面临着越来越大的压力，需要快速向客户提供更强大的功能。云提供商通过具有出色 CLI 和 API  集成的可扩展平台提供解决方案。不幸的是，云提供商公开的接口可能不兼容。但一些云原生工具可帮助 DevOps  团队为任何云提供商构建自定义解决方案。

Vagrant 和 Docker 是两个这样的工具。了解它们的作用以及它们如何协同工作是充分利用云环境的关键。

Vagrant 是一个用于在单个工作流程中构建和管理虚拟机 (VM) 环境的工具。无论您是构建本地虚拟机以与虚拟机管理程序一起运行还是仅构建云虚拟机，Vagrant 都提供一致的配置格式、单一 CLI 和共享配置程序来安装软件和更改配置。

Docker 提供了将软件和支持配置打包成跨多个平台一致运行的映像的能力。 Docker 让 DevOps 团队确信软件将在本地工作站上运行，就像在托管云平台上运行一样。

### 为什么使用 Docker（相对于 Vagrant）

DevOps 团队通常使用 Docker 来交付和运行 Web 应用程序，包括与消息队列集成或托管在响应基于云的触发器和事件的功能即服务 (FaaS) 平台上的云原生应用程序

Kubernetes 等平台构建在 Docker 之上，允许大规模编排容器。此外，每个云提供商都支持在其平台即服务 (PaaS) 产品中运行 Docker 容器的功能。现在很难找到不支持 Docker 的 PaaS。

Docker 还可以分发和执行基于 CLI 的工具，所有流行的云原生工具都提供嵌入其 CLI 的 Docker 映像。

### 对比 (gpt)

GPT4

比较VMWare、VirtualBox（跨平台、开源、兼容性、使用人数）。以及比较Docker、Vagrant。并给出选用建议

---

首先我们来比较 VMWare 和 VirtualBox：

- 跨平台
    - VMWare：提供 Workstation（适用于 Windows 和 Linux） 和 Fusion（适用于 Mac） 方案，具有较好的跨平台支持。 
    - VirtualBox： 支持 Windows、Mac、Linux 以及 Solaris 等操作系统，也具有较好的跨平台支持。 
- 开源
    - VMWare：部分产品需要付费授权，例如 Workstation Pro 和 Fusion Pro。 
    - VirtualBox：完全开源，可以免费使用。 
- 兼容性
    - VMWare：支持众多操作系统，兼容性较好。 
    - VirtualBox：同样支持多种操作系统，但可能在特定操作系统上的虚拟化表现略逊于 VMWare。 
- 使用人数
    - VMWare：因其强大的功能和性能，尤其在商业领域得到广泛使用。 
    - VirtualBox：开源免费，对个人开发者以及教育领域等更具吸引力。 

接下来比较 Docker 和 Vagrant：

- Docker 
    - 容器化技术：运行在一致的环境中，避免了类似“在我机器上可以运行”的问题。 
    - 轻量级：轻量级的虚拟化技术，资源消耗较低，启动速度快。 
    - 可扩展性：非常适合用于微服务架构； 
    - 社区活跃，主流操作系统上均有支持。 
- Vagrant
    - 基于虚拟机技术，应用运行环境更加隔离，安全性更高。 
    - 使用简单，可跨平台支持，Vagrantfile 配置可实现一致的开发、测试环境。 
    - 可与其他虚拟化平台（如 VirtualBox, VMWare 等）结合使用。 

选用建议：

1. 如果需要在多种操作系统中运行操作系统级别的虚拟化，根据预算及使用场景，可以选择 VMWare（商业需求较高）或 VirtualBox（开源免费，个人开发者及教育领域）。 
2. 对于开发环境的一致性要求较高，或者需要构建、部署微服务架构的场景，推荐使用 Docker。 
3. 如果希望快速构建一个跨平台的虚拟开发环境，选择 Vagrant 是比较方便的。 

## 使用

### 常用命令

```bash
# box相关
vagrant box add ubuntu/xenial64（介绍几个官方推荐）
vagrant box list

# vargrant init
vargrant init # 会在当前目录生成一个Vagrantfile文件

# 虚拟机相关
vargrant up
vargrant ssh # 虚拟机连接
vargrant halt
vagrant suspend
vagrant destory
vagrant reload
vagrant reload --provision
```

### Vargrant文件

大部分选项都是默认注释的，**我这里取消一部分注释只是为了高亮看起来方便，并不意味着你需要去取消这些注释**

```bash
# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure("2") do |config|
  # The most common configuration options are documented and commented below.
  # For a complete reference, please see the online documentation at
  # https://docs.vagrantup.com.

  # Every Vagrant development environment requires a box. You can search for
  # boxes at https://vagrantcloud.com/search.
  config.vm.box = "base" # 虚拟机所使用的镜像，需要自行提供box

  # Disable automatic box update checking. If you disable this, then
  # boxes will only be checked for updates when the user runs
  # `vagrant box outdated`. This is not recommended.
  config.vm.box_check_update = false # 定义box是否去查找更新

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine. In the example below,
  # accessing "localhost:8080" will access port 80 on the guest machine.
  # NOTE: This will enable public access to the opened port
  config.vm.network "forwarded_port", guest: 80, host: 8080 # 定义网络专属转发1

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine and only allow access
  # via 127.0.0.1 to disable public access
  config.vm.network "forwarded_port", guest: 80, host: 8080, host_ip: "127.0.0.1" # 定义网络专属转发2

  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  config.vm.network "private_network", ip: "192.168.33.10" # 定义网络专属转发3

  # Create a public network, which generally matched to bridged network.
  # Bridged networks make the machine appear as another physical device on
  # your network.
  config.vm.network "public_network" # 定义网络专属转发4

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  config.vm.synced_folder "../data", "/vagrant_data" # 虚拟机的同步目录

  # Disable the default share of the current code directory. Doing this
  # provides improved isolation between the vagrant box and your host
  # by making sure your Vagrantfile isn't accessable to the vagrant box.
  # If you use this you may want to enable additional shared subfolders as
  # shown above.
  # config.vm.synced_folder ".", "/vagrant", disabled: true

  # Provider-specific configuration so you can fine-tune various
  # backing providers for Vagrant. These expose provider-specific options.
  # Example for VirtualBox:
  #
  config.vm.provider "virtualbox" do |vb| # VirtualBox相关的配置
    # 在开启机器时显示VirtualBox的UI界面
    vb.gui = true
  
    # 自定义虚拟机内存大小
    vb.memory = "1024"
  end
  #
  # View the documentation for the provider you are using for more
  # information on available options.

  # Enable provisioning with a shell script. Additional provisioners such as
  # Ansible, Chef, Docker, Puppet and Salt are also available. Please see the
  # documentation for more information about their specific syntax and use.
  config.vm.provision "shell", inline: <<-SHELL # 适配器，虚拟机在第一次启动时需要进行一些什么操作
    apt-get update
    apt-get install -y apache2
  SHELL
end

```

### 实践

eBPF环境配置那里有些笔记

















