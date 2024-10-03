# README

## 实战环境 (windows11)

### 我的环境

- 系统/软件环境
  - Windows11
  - Vagrant 2.5.1
    - 注意，这里只支持到VirtualBox 7.0，7.1不支持
  - VirtualBox 7.0.20
    - 一开始安装的7.1.2，但似乎版本太高，Vagrant不兼容，路径 `C:\Program Files\Oracle\VirtualBox\`
- 使用的镜像
  - 源是这个： https://app.vagrantup.com/ubuntu/boxes/jammy64
  - 虽然用了镜像但都是一样的： https://vagrantcloud.com/ubuntu/boxes/jammy64/versions/20240912.0.0/providers/virtualbox/unknown/vagrant.box
- 工作路径
  - `H:/Git/Private/VMProjects/VirtualBoxProject/`

### 流程 - 准备环境

安装： 安装环境，安装好Virtual和Vagrant，安装后后他会要求你重启电脑，重启

cmd中准备： 

```bash
$ vagrant -v # 1
Vagrant 2.4.1

$ VBoxManage -v # 2 如果这里没有，就去设置windows的环境变量
7.1.2r164945

$ vagrant status # 3
# 这里可能遇到多种不同的情况，见下
```

*异常补充*：

(主要是 vagrant status 命令)

```bash
# ------------------- 失败情况一 ------------------- 
# 如果环境不对，检查前面步骤。VBox是否有VBoxManage、重新用管理员权限打开终端
$ vagrant status
No usable default provider could be found for your system.

Vagrant relies on interactions with 3rd party systems, known as
"providers", to provide Vagrant with resources to run development
environments. Examples are VirtualBox, VMware, Hyper-V.

The easiest solution to this message is to install VirtualBox, which
is available for free on all major platforms.

If you believe you already have a provider available, make sure it
is properly installed and configured. You can see more details about
why a particular provider isn\'t working by forcing usage with
`vagrant up --provider=PROVIDER`, which should give you a more specific
error message for that particular provider.

# ------------------- 失败情况二 -------------------
# 这里如果只检查到了hyperv，也不对，关键看是否检测到了VirtualBox
# 至于这里为什么没检测到VirtualBox，我跳过这里执行后面的步骤才告诉我原因，估计是VirtualBox版本太高他不支持
$ vagrant status
Current machine states:

default                   not_created (hyperv)

# ------------------- 成功情况一 -------------------
$ vagrant status
Current machine states:

default                   not created (virtualbox)

The environment has not yet been created. Run `vagrant up` to
create the environment. If a machine is not created, only the
default provider will be shown. So if a provider is not listed,
then the machine is not created for that environment.
```

准备位置： Windows创建项目文件夹，打开cmd并定位到项目文件夹

### 流程 - 准备box

cmd中创建box镜像： 

```shell
$ vagrant init ubuntu/jammy64 # 第1步，暂时只用默认的镜像。这一步也可以使用自定义vagrantfile文件代替

# (可选，检查一下：dir、notepad Vagrantfile)

$ vagrant up # 第2步
# 这里可能遇到多种不同的情况，见下
```

*异常补充*：

(主要是 vagrant up 命令)

```bash
# ------------------- 失败情况一 ------------------- 
# 这里说明default值是Hyper-V，不对
$ vagrant up
Bringing machine 'default' up with 'hyperv' provider...
==> default: Verifying Hyper-V is enabled...
The Hyper-V cmdlets for PowerShell are not available! Vagrant
requires these to control Hyper-V. Please enable them in the
"Windows Features" control panel and try again.

# ------------------- 失败情况二 ------------------- 
# 这里估计是我安装的VirtualBox7.2版本太高了，Vagrant识别不了
$ vagrant up --provider=virtualbox

The provider 'virtualbox' that was requested to back the machine
'default' is reporting that it isn\'t usable on this system. The
reason is shown below:

Vagrant has detected that you have a version of VirtualBox installed
that is not supported by this version of Vagrant. Please install one of
the supported versions listed below to use Vagrant:

4.0, 4.1, 4.2, 4.3, 5.0, 5.1, 5.2, 6.0, 6.1, 7.0

A Vagrant update may also be available that adds support for the version
you specified. Please check www.vagrantup.com/downloads.html to download
the latest version.

# ------------------- 失败情况三 ------------------- 
# 这里说找不到 'ubuntu/jammy64'
$ vagrant up
Bringing machine 'default' up with 'virtualbox' provider...
==> default: Box 'ubuntu/jammy64' could not be found. Attempting to find and install...
    default: Box Provider: virtualbox
    default: Box Version: >= 0
==> default: Loading metadata for box 'ubuntu/jammy64'
    default: URL: https://vagrantcloud.com/api/v2/vagrant/ubuntu/jammy64
==> default: Adding box 'ubuntu/jammy64' (v20240912.0.0) for provider: virtualbox
    default: Downloading: https://vagrantcloud.com/ubuntu/boxes/jammy64/versions/20240912.0.0/providers/virtualbox/unknown/vagrant.box
Download redirected to host: cloud-images.ubuntu.com
    default:
An error occurred while downloading the remote file. The error
message, if any, is reproduced below. Please fix this error and try
again.

Failed to connect to cloud-images.ubuntu.com port 443 after 42112 ms: Couldn\'t connect to server

# ------------------- 成功情况一 -------------------
# 1. 要么梯子开全局
# 2. 要么尝试在配置中增加镜像源：(如果链接失效自行去镜像网站更新，一般是修改一下那个日期)
#   config.vm.box_url = "https://mirrors.tuna.tsinghua.edu.cn/ubuntu-cloud-images/jammy/20240912/jammy-server-cloudimg-amd64-vagrant.box"，用镜像源也要等挺久的
# 3. 还有一种方法，是将box文件下载到本地 (详见《Vagrant快速入门》笔记)
#   config.vm.box_url = "file://tmp/ubuntu-2204.box"
# 这里使用了方案二
$ vagrant up
Bringing machine 'default' up with 'virtualbox' provider...
==> default: Box 'ubuntu/jammy64' could not be found. Attempting to find and install...
    default: Box Provider: virtualbox
    default: Box Version: >= 0
==> default: Box file was not detected as metadata. Adding it directly...
==> default: Adding box 'ubuntu/jammy64' (v0) for provider: virtualbox
    default: Downloading: https://mirrors.tuna.tsinghua.edu.cn/ubuntu-cloud-images/jammy/20240912/jammy-server-cloudimg-amd64-vagrant.box
==> default: Box download is resuming from prior download progress
    default:
==> default: Successfully added box 'ubuntu/jammy64' (v0) for 'virtualbox'!
==> default: Importing base box 'ubuntu/jammy64'...
==> default: Matching MAC address for NAT networking...
==> default: Setting the name of the VM: VirtualBoxProject_default_1727881439007_57295
Vagrant is currently configured to create VirtualBox synced folders with
the `SharedFoldersEnableSymlinksCreate` option enabled. If the Vagrant
guest is not trusted, you may want to disable this option. For more
information on this option, please refer to the VirtualBox manual:

  https://www.virtualbox.org/manual/ch04.html#sharedfolders

This option can be disabled globally with an environment variable:

  VAGRANT_DISABLE_VBOXSYMLINKCREATE=1

or on a per folder basis within the Vagrantfile:

  config.vm.synced_folder '/host/path', '/guest/path', SharedFoldersEnableSymlinksCreate: false
==> default: Clearing any previously set network interfaces...
==> default: Preparing network interfaces based on configuration...
    default: Adapter 1: nat
==> default: Forwarding ports...
    default: 22 (guest) => 2222 (host) (adapter 1) # ! 重点
==> default: Running 'pre-boot' VM customizations...
==> default: Booting VM...
==> default: Waiting for machine to boot. This may take a few minutes...
    default: SSH address: 127.0.0.1:2222
    default: SSH username: vagrant
    default: SSH auth method: private key
    default:
    default: Vagrant insecure key detected. Vagrant will automatically replace
    default: this with a newly generated keypair for better security.
    default:
    default: Inserting generated public key within guest...
    default: Removing insecure key from the guest if it\'s present...
    default: Key inserted! Disconnecting and reconnecting using new SSH key...
==> default: Machine booted and ready!
==> default: Checking for guest additions in VM...
    default: The guest additions on this VM do not match the installed version of
    default: VirtualBox! In most cases this is fine, but in rare cases it can
    default: prevent things such as shared folders from working properly. If you see
    default: shared folder errors, please make sure the guest additions within the
    default: virtual machine match the version of VirtualBox you have installed on
    default: your host and reload your VM.
    default:
    default: Guest Additions Version: 6.0.0 r127566
    default: VirtualBox Version: 7.0
==> default: Mounting shared folders...
    default: /vagrant => H:/Git/Private/VMProjects/VirtualBoxProject # ! 重点
```

### 流程 - 连接虚拟机

```bash
$ vagrant ssh # 第3步
```

异常补充：

```bash
# ------------------- 成功情况一 -------------------
Welcome to Ubuntu 22.04.5 LTS (GNU/Linux 5.15.0-119-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/pro

 System information as of Wed Oct  2 15:11:53 UTC 2024

  System load:  0.0               Processes:               101
  Usage of /:   3.7% of 38.70GB   Users logged in:         0
  Memory usage: 20%               IPv4 address for enp0s3: 10.0.2.15
  Swap usage:   0%


Expanded Security Maintenance for Applications is not enabled.

0 updates can be applied immediately.

Enable ESM Apps to receive additional future security updates.
See https://ubuntu.com/esm or run: sudo pro status


The list of available updates is more than a week old.
To check for new updates run: sudo apt update
New release '24.04.1 LTS' available.
Run 'do-release-upgrade' to upgrade to it.


vagrant@ubuntu-jammy:~$

```

## 扩展增强

其实这里已经可以正常使用了

可以看到，除准备环境外，创建虚拟机一共只需要三步！非常方便快捷！

### 网络检查

先检查一下网络：

```bash
$ ping www.baidu.com
PING www.a.shifen.com (183.240.98.161) 56(84) bytes of data.
64 bytes from 183.240.98.161 (183.240.98.161): icmp_seq=1 ttl=53 time=15.0 ms
64 bytes from 183.240.98.161 (183.240.98.161): icmp_seq=2 ttl=53 time=15.2 ms
```

### 预安装一些环境

没问题的话，这里可以换成一些我常用的配置：

(可以先简单运行起来，再换这里的配置，不用一步到位，没什么区别 (主要是速度比较快)。分步操作在出现bug时也更容易调试)

(当然，你也可以卸载重装。`vagrant halt` 和 `vagrant destroy` 分别关闭和删除虚拟机)

```python
# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  # 镜像设置。这里使用了镜像。若链接失效则到该链接更新:
  # https://mirrors.tuna.tsinghua.edu.cn/ubuntu-cloud-images/jammy/
  config.vm.box = "ubuntu/jammy64"
  config.vm.box_url = "https://mirrors.tuna.tsinghua.edu.cn/ubuntu-cloud-images/jammy/20240912/jammy-server-cloudimg-amd64-vagrant.box"

  # 设置内存和CPU数量等
  config.vm.network "private_network", ip: "192.168.56.20"
  config.vm.provider "virtualbox" do |vb|
    vb.memory = "2048"
    vb.cpus = 2
  end

  # 在虚拟机启动时运行的 shell 命令
  config.vm.provision "shell", inline: <<-SHELL
    # 环境安装 - apt-get
    apt-get update -y # 更新包列表
    apt-get install -y software-properties-common # 安装基础工具
    
    # 环境安装 - python, pip, git
    apt-get install -y python3 python3-pip git

    # 环境安装 - nodejs、npm、pnpm
    # PPA方案
    # 为什么要执行这里的PPA：ubuntu到22也无法直接通过apt安装高版本，最多就到node12，而前端环境一般最少要node18，新一点甚至要node20。将PPA添加到配置中，就可以安装更高的版本
    # 链接失效则到该链接更新: https://deb.nodesource.com/、https://www.digitalocean.com/community/tutorials/how-to-install-node-js-on-ubuntu-22-04
    curl -fsSL https://deb.nodesource.com/setup_20.x | sudo bash -
    sudo apt install -y nodejs
    sudo apt install -y npm
    sudo npm install -g pnpm

    # 环境安装 - 版本打印
    cat /etc/issue     # Ubuntu 22.04.5 LTS
    apt --version      # apt 2.4.13 (amd64)
    git --version      # git version 2.34.1
    python3 --version  # Python 3.10.12
    node --version     # v20.17.0 (注意如果不使用PPA方案，只有12.22.9，完全不够用)
    npm --version      # 10.8.2
    pnpm --version     # 9.12.0
  SHELL
end
```

使用新vagrantfile

```bash
# 可以重新加载虚拟机并执行脚本：
vagrant reload
vagrant provision

# 也可以直接卸载重装
vagrant halt    # 关闭虚拟机
vagrant destroy # 卸载虚拟机
vagrant up      # 重新装
```

验证：我在脚本最后打印了一些环境版本。需要注意：python3的版本不要过旧、node版本最好>=18 (默认的v12完全不够用)

### 手动处理环境

这部分更多的是一些账户帐密和ssh账密的东西，不方便在vagrant脚本里写

```bash
$ sudo passwd root # 创建root账户
$ su root

# 未开启ssh时可用的几种连接方式：
$ ssh vagrant@localhost -p 2222 -i .vagrant/machines/default/virtualbox/private_key
$ ssh vagrant@192.168.56.20 -i .vagrant/machines/default/virtualbox/private_key

# 允许ssh账密连接
$ sudo echo "==> Enable ssh password authentication"
sudo sed -i 's/^PassworkAuthentication .*PasswordAuthentication yes/' /etc/ssh/sshd_config
sudo systemctl reload sshd
# 或者手动
$ sudo vi /etc/ssh/sshd_config
[修改] PasswordAuthentication yes
[添加] PermitRootLogin yes
$ sudo systemctl restart sshd
$ vagrant ssh-config
Host default
  HostName 127.0.0.1
  User vagrant
  Port 2222
  UserKnownHostsFile /dev/null
  StrictHostKeyChecking no  # 严格的主机密钥检查
  PasswordAuthentication no # 重点看这里，虽然这里是no，但似乎还是可以连上的
  IdentityFile ...
  IdentitiesOnly yes
  LogLevel FATAL
  PubkeyAcceptedKeyTypes +ssh-rsa
  HostKeyAlgorithms +ssh-rsa
```

tips，在常用的VSCode的ssh远程连接中，可以直接用这里的秘钥对，不是非得用账密

```bash
ssh vagrant@192.168.56.20 -i H:/Git/Private/VMProjects/VirtualBoxProject/.vagrant/machines/default/virtualbox/private_key
```

### 软件的高版本/多版本问题

#### Python

[list]

- apt方案： 一般够用(并不)，但版本不高(22.04.5 LTS 默认 3.10.12)
- Anaconda、虚拟环境： 需要频繁切换Python版本
- 压缩包： 略

#### Node

参考：[How To Install Node.js on Ubuntu 20.04](https://www.digitalocean.com/community/tutorials/how-to-install-node-js-on-ubuntu-20-04)，[How To Install Node.js on Ubuntu 22.04](https://www.digitalocean.com/community/tutorials/how-to-install-node-js-on-ubuntu-22-04) 这里提供了三个方案：

[list]
- apt方案： 一般够用(并不)，但版本很低(22.04.5 LTS 默认 12.22.9)
- PPA存储库： 可以使用特定的较新或较旧的Node版本，参考 https://deb.nodesource.com/
- nvm： 需要频繁切换Node版本
- 压缩包： 略

PPA方案：

```bash
curl -fsSL https://deb.nodesource.com/setup_20.x | sudo bash -
sudo apt install -y nodejs

# 或 (更多分步，以及可以查看脚本内容的)

curl -sL https://deb.nodesource.com/setup_==18.x== -o nodesource_setup.sh
sudo bash nodesource_setup.sh
sudo apt install -y nodejs

# 或

# 废弃方案：
add-apt-repository -y ppa:nodejs/ppa # 添加 Node.js 的 PPA
sudo apt install -y nodejs
```

#### 卸载

例如：`apt remove nodejs`

## (临时)

### VuePress2 使用 AnyBlock

```shell
# vuepress2
# https://vuepress.github.io/zh/guide/getting-started.html
$ pnpm create vuepress vuepress-starter # 后面引导大部分选择默认值就是了，除了blog/docs一项
english
pnpm
vite
docs # 非默认
my-vuepress-site
0.0.1
A VuePress project
MIT
n # 非默认
n
$ cd vuepress-starter
$ pnpm i
$ pnpm docs:dev
# $ pnpm add -D sass (中途报错让我手动安了个sass)

# -------------------

$ echo -e "\n[list2table]\n\n- 1\n- 2\n  - 3\n  - 4\n" >> ./docs/README.md
$ [操作1] 新增 `./pnpm-workspace.yml` 文件，里面加上：
packages:
  - 'packages/*'
$ [操作2] 在 package.json 中添加新字段：
"workspaces": ["packages/*"]
$ [操作3] 将LincZero.github.io项目中 `/src/.vuepress/plugin/ABConvertManager/` 文件夹复制到当前项目的 `/packages/ABConvertManager/` 中
$ [操作4] 修改 ./docs/.vuepress/config.js
第一行加上：import ab_mdit from "../../packages/ABConvertManager/src/index_mdit"
然后在 export default defineUserConfig {...} 里面加上：
markdown: {
  extendMarkdown: md => {
    md.use(ab_mdit)
  }
}
$ pnpm add any-block-converter-markdown-it
$ pnpm i # 需要重新安装一遍，会递归安装依赖
$ pnpm docs:dev
```



```
┌  Welcome to VitePress!
│
◇  Where should VitePress initialize the config?
│  ./docs
│
◇  Site title:
│  My Awesome Project
│
◇  Site description:
│  A VitePress Site
│
◆  Theme:
ABCDEFG
│  ● Default Theme (Out of the box, good-looking docs)
│  ○ Default Theme + Customization
│  ○ Custom Theme
ABCDEFG
└
```
