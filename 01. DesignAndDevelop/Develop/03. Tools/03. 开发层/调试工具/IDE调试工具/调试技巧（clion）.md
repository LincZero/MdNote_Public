- 随时暂停以查看线程树
- 一些断点技巧
	- add to watches 以随时查看单例模式


## add to watches 以随时查看单例模式

中途踩了个坑：

### 坑一

```cpp
RecorderControl* RecorderControl::getInstance(){
    if(!instance) {
        instance = new RecorderControl();  // 我在这里设置断点，但是看不到instance的值
    }
    return instance;
}
```

解决方法：

请确保在 `Variables` 窗口中找到并展开 `instance` 变量。如果你无法找到`instance`变量，请在`Watches`窗口中添加一个表达式`instance`，以便在调试过程中实时查看它的值。

### 坑二

我 add to watches 后，在程序中途pause后，变量查看不了。显示红色的：-var-create: unable to create vaiable object

解决方法：

之前 add to watch 的不对，应该直接在 `Watches` 窗口打：`RecorderControl::instance` 追踪，而不是在断点时打 `instance`。
另外其实并不需要额外断点

## clion五种运行模式

- 普通运行
	- 提示：Run 'ProjectName'
	- 图标：三角形
- 普通调试
	- 提示：Debug 'ProjectName'
	- 图标：虫子
- 0
	- 提示：Run 'ProjectName' with Coverage
	- 图标：盾牌+三角
- 0
	- 提示：Profile 'ProjectName'
	- 图标：时钟+三角
- 0
	- 提示：Run 'ProjectName' with Valgrind Memcheck
	- 图标：内存+三角
	- 功能：可以帮助检测内存错误

## clion的git栏

右上角一共五个图标，还有左下角的一个git页面展开

## clion交叉编译（wsl）

### clion准备

clion中打开 File -> Settings -> Build, Execution, Deployment -> 设置WSL的工具链

刚开始可能会发生一些问题，找不到对应的东西

- 找不到 Toolset，则需要在windows上安装一个wsl。教程见后文
- 找不到 CMake，则需要在WSL里面安装一个。教程见后文
- 找不到 Build Tool、C编译器、C++编译器。同理在WSL里面安装
- 找不到 Debugger GDB。同理在WSL里面安装

设置页面工具都找到了，也可能会遇到编译不了的问题

- 例如版本不对，需要升级cmake版本

### 安装WSL

略，上网找教程

### WSL上安装CMake

```bash
$ sudo passwd root # 创建root用户 
$ su # 切换成root用户（回车后填密码）

$ sudo apt-get update # 最好先更新一下apt版本，不然后面的安装可能会报错
```

> Ubuntu Linux 有一个与众不同的特点，那就是初次使用时，你无法作为 root 来登录系统，为什么会这样？这就要从系统的安装说起。对于其他 Linux 系统来说，一般在安装过程就设定 root 密码，这样用户就能用它登录 root 帐户或使用 su [**su - root**] 命令转换到超级用户身份。
> 
> 与之相反，Ubuntu 默认安装时，并没有给 root 用户设置口令，也没有启用 root 帐户。问题是要想作为 root 用户来运行命令该怎么办呢？没关系，我们可以使用 sudo 命令达此目的。 
> 
> sudo 是 linux 下常用的允许普通用户使用超级用户权限的工具，该命令为管理员提供了一种细颗粒度的访问控制方法，通过它人们既可以作为超级用户又可以作为其它类型的用户来访问系统。这样做的好处是，管理员能够在不告诉用户 root 密码的前提下，授予他们某些特定类型的超级用户权限，这正是许多系统管理员所梦寐以求的。

```bash
$ camke --version # 查看下版本，顺便获取安装提示
$ apt install cmake # 安装cmake
```

### WSL上安装 Build Tool、C编译器、C++编译器

c编译器和c++编译器通常为gcc.exe和g++.exe

```shell
$ gcc --version
$ apt install gcc
$ g++ --version
$ apt install g++
```

### WSL上安装gdp

```shell
$ gdb --version # 查看下版本，顺便获取安装提示
$ apt install gdb
```

### WSL升级cmake

cmake官网：https://cmake.org/files/（可找对应版本的二进制）

```shell
$ cmake --version
$ rm -rf /usr/bin/cmake # 卸载cmake。不要用 `apt-get autoremove cmake`，可能会将之前安装的ros很多库都删除了
$ wget https://cmake.org/files/v3.16/cmake-3.16.8-Linux-x86_64.tar.gz # 下载cmake的安装包
# https://cmake.org/files/v3.23/cmake-3.23.0-linux-x86_64.tar.gz，备用，3.23版本的
$ tar zxvf cmake-3.16.8-Linux-x86_64.tar.gz # 解压，注意压缩包内容编译过了，解压即可用
$ sudo ln /home/shl/tools/cmake-3.16.8-Linux-x86_64/bin/cmake /usr/bin/cmake # 建立硬链接，不要加-s变成软链接，clion好像识别不到
$ cmake --version
```

更新cmake以后可能有个bug：c工具报错：`Test CMake run finished with error`。应该是版本不对的原因

### WSL升级其他

```shell
# 首先，确保你使用的是 WSL2 ，而不是 WSL1。如果你没有安装或更新到 WSL2，请按照[微软官方文档](https://docs.microsoft.com/zh-cn/windows/wsl/install-win10)进行配置。

sudo apt update
sudo apt upgrade

sudo apt install build-essential # 安装或更新 GCC 和 G++

gcc --version
g++ --version
cmake --version
```

## 高效断点技巧

参考：B站“聊聊编程”

1. 条件断点，在断点的红点上右键，可以输入例如 `i==5`，这样可以在循环的某个part快速断点
2. 根据线程断点，断点Config为 `Thread.currentThread().getName().equals("Thread1)"`
```java
Thread thread1 = new Thread(myThread, "Thread1");
...
System.out.println(Thread.currentThread().getName()+"进入=====") // 断点行
```
3. 集合的Stream，
   在开始调试后，可以点击 `IJ`(idea) 下面的一个按钮 `Trace Current Stream Chain`，会弹出一个窗口。然后会呈现出这个流的各种操作
   **（可以看到 map、filter、map、collect 的每一步的过程）**
```java
List<string> clooect = list.stream() // 断点行
	.map(Interger::parseInt)
	.filter(map::containsKey)
	.map(map::get)
	.collect(Collectors.toList());
System.out.println(collect);
```

## WSL



我将他们都手动指定路径了：

```
Name: WSL
Toolset: Ubuntu-20.04
CMake: /usr/bin/cmake
Build Tool: /usr/bin/make
C Compiler: /usr/bin/gcc
C++ Compiler: /usr/bin/g++
Debugger: /usr/bin/gbd
```

但是会有错误：Test CMake run finished with errors

尝试手动安装cmake：https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4-linux-x86_64.tar.gz


```
wget https://github.com/Kitware/CMake/releases/download/v3.23.0/cmake-3.23.0-linux-x86_64.tar.gz
tar -zxvf cmake-3.23.0-linux-x86_64.tar.gz
sudo mv cmake-3.23.0-linux-x86_64 /opt/cmake-3.23.0
sudo ln -s /opt/cmake-3.23.0/bin/* /usr/local/bin
```




