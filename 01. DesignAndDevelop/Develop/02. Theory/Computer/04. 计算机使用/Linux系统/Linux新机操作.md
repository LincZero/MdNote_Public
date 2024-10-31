# Linux新机操作 (桌面版)

## 硬件/系统类

### 安装系统

- Ubuntu
  - all_release (建议)：https://releases.ubuntu.com/
  - 一般下载 (不建议)：https://cn.ubuntu.com/download/desktop
- Arch
  - all_release：https://archlinux.org/download/
- Deepin
  - all_release：https://cdimage.deepin.com/releases/

### 检查状态

```bash
$uname
$uname -m
$cat /etc/issue

$ifconfig	# interface (include web) info
```

### 设置类

#### 设置外观

壁纸、图标大小等

#### 切换语言

如果是桌面版，设置 > 地区和语言，将语言修改成英语/中文就行了

如果是命令行版，……

#### 路径名问题

如果刚安装时是中文方式，路径会存在中文路径。

为了避免开发问题，可以：

1. 切英文 > 重启 > 修改路径名 > 切换回中文并保留原路径
2. 尽量避免用 home 的那几个默认文件夹，而是自己创建

#### 开启ssh

参考：https://blog.csdn.net/jackghq/article/details/54974141

```bash
# 安装
$dpkg -l | grep ssh						# 检查是否安装（默认只安装ssh-client服务）
$sudo apt-get install openssh-server	# 安装
$dpkg -l | grep ssh						# 再检查
openssh-client
openssh-server

# 启动
$ps -e | grep ssh						# 检查是否启动
sshd

# 配置
$ sudo vim /etc/ssh/sshd_config
然后将PermitRootLogin改为yes				# 允许root登录
```

## IO软件

### 星火应用商店

[官网下载地址](http://spark-app.store/download)
 http://spark-app.store/download

安装时, 找到下载好的安装包, 使用控制台进行安装, 注意安装时要使用`apt `命令, 不能使用`dpkg`命令, 否则会报错 !（官方说的，说法是dpkt不能自己处理依赖）

```sh
sudo apt install ./spark-store_3.0.3-13_amd64.deb
```

### 网络类 (换源、vpn)

### 文字类 (输入法、语言、路径名)

#### 输入法

详见 《Linux输入法》 笔记













































