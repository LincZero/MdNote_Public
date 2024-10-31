## 准备

使用方法：CLion直接点击有内存图标的调试按钮（通过 Valgrind Memcheck 运行 'xxxProject'），即可

环境准备：需要使用Linux环境编译安装，且Linux环境需要安装valgrind。Linux环境可以用wsl、虚拟机、或远程，valgrind安装方法如下：

### apt方式

```bash
sudo apt-get update
sudo apt-get install valgrind
valgrind # 验证是否安装成功
```

### 安装包方式

```bash
wget http://sourceware.org/pub/valgrind/valgrind-3.15.0.tar.bz2
tar -jxvf valgrind-3.15.0.tar.bz2
cd valgrind-3.15.0
./configure
make
make install
```

## 配置

```bash
$ which valgrind # 查看路径
/usr/bin/valgrind # 一般是这个路径
```

远程的Clion配置也是差不多的，对于WSL，你设置了远程后可以直接图形化选择路径，例如：

```bash
\\wsl$\Ubuntu-20.04\usr\bin\valgrind
```

对于远程Linux，直接填路径就行，图形化选不了

```bash
/usr/bin/valgrind
```

























