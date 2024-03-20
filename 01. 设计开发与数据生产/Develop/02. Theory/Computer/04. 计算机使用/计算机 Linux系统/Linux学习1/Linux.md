# Linux

# 目录

[TOC]

# Linu终端

## Linux发展历史

- **Unix**

  `1968`Multics项目（MIT，Bell，美国通用电气有限公司）

  `1970`Unix诞生（汇编语言）

  `1973`C语言重写Unix

- **Linux**

  `1991`Linux之父——Linus

- **Linux与GNU协议**

  GNU开源协议 Linux特点

  开源、多用户(同时)，多任务，稳定性好

- **Linux分支**

  Ubuntu，debian，centOS(redhat分支)，redhat，suse等

- **Linux其他**

  “Linux一切皆文件”

## 虚拟机相关

虚拟机备份

> `快照`又称还原点，侧重短期，无需关闭Linux)
>
> `克隆`侧重长期，要关闭Linux

## Linux文件目录1

计算机

> 驱动器
>
> 文件系统

文件系统

| 目录名称 | 英文全拼 | 说明 |
| ---- | ---- | ---- |
|**bin -> usr/bin**|binary|二进制文件|
|boot||启动Linux时使用的一些核心文件，包括一些链接文件以及镜像文件|
|**dev**|device|外接设备|
|**etc**||配置文件|
|**home**||家，类似windows的`C:\User`|
|**lib -> usr/bin**||有着系统最基本的动态链接共享库，其作用类似于Windows里的DLL文件|
|**lib64 -> usr/bin64**|||
|lost+found||一般情况下是空的，当系统非法关机后，这里就存放了一些文件|
|media|||
|misc|||
|**mnt**||有四个目录，外接设备挂载的地方。如将光驱挂载在`/mnt/cdrom`上，然后就可以查看里面内容|
|net|||
|opt|||
|**proc**|process|进程|
|**root**||roor用户的“home”|
|**sbin -> usr/sbin**|super binary|super权限的二进制文件|
|selinux||安全策略/防火墙|
|srv|||
|sys|||
|**tmp**|temporary|临时文件，类似windows的`C:\Windows\Temp`|
|**usr**||用户安装的软件，类似windows的`C:\Program Files`|
|**var**||系统日志|

## Linux文件目录2

![img](Linux.assets/clipboard-1597625906777.png)

> **bin**
>
> boot
>
> data
>
> dev
>
> etc
>
> home
>
> **lib** -> usr/lib
>
> **lib64** -> usr/lib64
>
> lost+found
>
> media
>
> mnt
>
> opt
>
> proc
>
> root
>
> run
>
> **sbin** -> usr/sbin
>
> srv
>
> sys
>
> **tmp** -> 多个/tmp
>
> usr
>
> var

## 软件安装路径

- 图1

![img](Linux.assets/clipboard-1597625925931.png)

- 图2

![img](Linux.assets/clipboard-1597625929958.png)

- 图3

![img](Linux.assets/clipboard-1597625934498.png)

# Linux指令

通用格式：指令主体 [选项] [操作对象]

指令网站：man.linuxde.net

## 基础命令

### 终端操作

| 指令         | 说明            | 参数 |
| ------------ | --------------- | ---- |
| clear/ctrl+L | 伪·清除终端信息 |      |

### 系统操作

关机（很少用）

| 指令     | 说明                                |
| -------- | ----------------------------------- |
| shutdown | 关机(正常关机)，或`shutdown -h now` |
| halt     | 关机(关闭内存)                      |
| inito    | 关机(一般不用)                      |

### 路径操作

| 命令 | 英语 | 说明 | 参数 |
| ---- | ---- | ---- | ---- |
|ls [-lah] [路径]|list|查看当前目录<br />技巧：ls -l可简写为ll<br />路径可接筛选文件名！|`-l`以列表形式显示<br />`-a`包含隐藏文件<br />`-h`可读性优化显示|
|pwd|print working directory|查看当前路径||
|cd [路径]|change directory|定位到路径||

### 文件操作

| 命令 | 英语 | 说明 | 参数 |
| ---- | ---- | ---- | ---- |
| mkdir [-p] [路径1 路径2] | make directory | 创建目录 | `-p`一次创建多层目录 |
|touch [路径n]|touch|创建文件||
|cp [-r] [原路径 目标路径]|copy |复制|`-r`递归复制(recursion) |
|mv [原路径 目标路径]|move |移动 / 重命名 | 话说这个没有递归 |
|rm [-rf] [路径n]|remove |删除 | `-r`递归(recursion)<br />`-f`不提示-强制删除(force) |

补充：`chmod 000 文件名`，设置文件权限为最高级（常用其他权限参数：777、754）

### 文件内容操作

| 命令 | 说明 | 参数 |
| ---- | ---- | ---- |
|vim [路径]<br /> <br />简写：<br />vi [路径]|查看文件<br />文件可以有也可以没有<br />`vim`是进入文件读取内容<br />`cat`是在终端显示文件内容<br />前者一般用来编辑，后者用来查看|`esc`退出阅读模式 / 命令模式<br />`Shift + :`进入编辑模式<br />`q + Enter`执行退出命令<br />`wq + Enter`保存退出<br />`q! + Enter`强制退出|
|cat [路径]|查看文件||

Vim更多退出操作（以下操作要先按`esc`退出某些状态（编辑）后才能输入）

- `i`，插入模式，即编辑模式
- `:w`，保存文件但不退出vi
- `:w file`，将修改另外保存到file中，不退出vi
- `:w!`，强制保存，不推出vi
- `:wq`，保存文件并退出vi
- `:wq!`，强制保存文件，并退出vi
- `:q`，不保存文件，退出vi
- `:q!`，不保存文件，强制退出vi
- `:e!`，放弃所有修改，从上次保存文件开始再编辑命令历史

### 辅助操作

| 指令            | 说明                                     |
| --------------- | ---------------------------------------- |
| [指令] > [路径] | 输出重定向 —— 覆盖输出，文件不存在则新建 |
| [指令] >>[路径] | 输出重定向 —— 追加输出，文件不存在则新建 |

## 进阶指令

### 系统操作

| 指令                    | 说明                      | 参数                                                         |
| ----------------------- | ------------------------- | ------------------------------------------------------------ |
| df [-h]                 | 查看磁盘空间              | `-h`可读性优化显示                                           |
| free [-h-m-g]           | 查看内存空间              | `-h`可读性优化（旧版不能）<br />`-m`兆字节<br />`-g`吉字节   |

### 文件内容高级操作

| 指令                    | 说明                      | 参数                                                         |
| ----------------------- | ------------------------- | ------------------------------------------------------------ |
| head [-数字] [路径]     | 查看文件的前n行，默认10行 |                                                              |
| tail [-数字-f-F] [路径] | 查看文件的后n行，默认10行 | `-f`查看文件的动态变化<br />但这个变化内容不能是用户手动修改<br />一般用来查看系统日志 |
| less                    | 查看文件并以较少内容输出  | 辅助键：数字+Enter、空格+上下方向键                          |
| wc [-lwc]               | 统计文件内容信息          | `-l`行数`line`<br />`-w`单词数`words`<br />`-c`字节数`bytes` |

### 日期编辑类【重点】

| 指令                                            | 说明                                                         | 参数                                                         |
| ----------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| data ["+%F %T"]<br />data -d  "+1 day" "+%F %T" | 操作时间和日期<br />可现实当前 / 指定某刻的数据<br />`+%F %T`等价于`+%Y-%m-%d %H:%M:%S` | `%F`年月日`%T`时分秒<br />`%Y`年`%m`月`%d`日`%H`时`%M`分`%S`秒<br />`+`前`-`后`day`日`month`月`year`年 |
| cal [-数字-y 年份]                              | 操作日历                                                     | `-1`当月，`-3`上本下月，`-y`一年12个月<br />`-s`周日开始`-m`周一开始 |

### 管道符 "|"

| 功能     | 例子           | 作用                                             |
| -------- | -------------- | ------------------------------------------------ |
| 过滤     | ls /           | 过滤为有'y'的文件，grep为过滤指令                |
| 特殊     | cat 路径\|less | 实现less的等价效果                               |
| 扩展处理 | ls/ \|wc -l    | 统计某个目录下文档个数，前面的输出作为后面的输入 |

## 高级指令

### 文件高级操作

| 指令               | 说明                                               | 参数                                                         |
| ------------------ | -------------------------------------------------- | ------------------------------------------------------------ |
| du [-sh]           | 查看目录真实大                                     | `-s`只显示汇总大小(summaries)<br />`-h`高可读性显示          |
| find [路径] [选项] | 查找文件<br />例：`find /etc -name *.conf | wc -f` | 有55个参数，常用：<br />`-name`按文件名(模糊搜索)<br />`-type`(-/f是文件,d是文件夹) |

### 系统与进程操作

| 指令                    | 说明                                                      | 参数                                                         |
| ----------------------- | --------------------------------------------------------- | ------------------------------------------------------------ |
| hostname [-f]           | 操作服务器主机名                                          | `-f`输出主机名中的FQDN(全限定域名)                           |
| id [用户名]             | 查看用户的一些基本信息                                    | 用户id,用户组id,附加组id<br />验证用户信息：/etc/passwd<br />验证用户组信息：/etc/group |
| whoami                  | who am i<br />显示当前用户名，一般用于shell脚本来记录日志 |                                                              |
| ps [-ef]                | 【重点】查看服务器进程信息<br />具体见下                  | `-e`列出前部进程，等价于`-A`<br />`-f`显示全部列(字段)       |
| top                     | (动态显示)进程状态<br />具体见下                          | `按M`(MEM)内存排序<br />`按P`(CPU)CPU排序<br />`按1`CPU分核显示<br />`按q`退出 |
| service [服务名] [操作] | 【重要】控制软件服务<br />例：`service httpd start`       | start启动，stop停止，restart重启                             |
| kill [进程PID]          | 杀死进程，配合ps -ef使用                                  |                                                              |
| killall [进程名称]      | 杀死进程                                                  |                                                              |

- ps [-ef] 的额外补充

> `UID`用户id
>
> `PID`进程id
>
> `STMIE`启动时间
>
> `PPID`进程的父级进程(父级没了就是僵尸进程)
>
> `C`CPU占用率
>
> `TTY`发起进程的终端设备(?表示非终端发起的)
>
> `TIME`执行时间
>
> `CMD`进程名称
>
> 案例：`ps -ef | grep gnome-panel` 

- top的额外补充

> `sleeping`睡眠进程
>
> `zombie`僵尸进程(plants vs zombies里的zombie)
>
> `S/R`进程状态(`S`睡眠,`R`运行)
>
> `PR`优先级(权重)
>
> `VIRT`虚拟内存
>
> `RES`常驻(虚拟)内存
>
> `SHR`共享内存(和依赖相关)
>
> 注：一个进程实际使用的内存 = `RES`常驻内存 - `SHR`共享内存
>
> `%CPU`是CPU占用
>
> `%MEM`是内存占用比
>
> `TIME+`是执行时间
>
> `COMMAND`进程名或路径

# Linux下的包管理

## Node篇

安装Nodejs

```shell
yum install -y nodejs
node-v
```

###   Node.js保持后台运行

#### 【方案1】forever

```shell
// 安装forever
sudo npm install -g forever
// 使用forever开启nodejs程序
forever start xxx.js
// 【或】使用forever开启npm程序
forever start -c "npm start" 路径
```

#### 【方案2】【更高级】pm2

```shell
// 安装
npm install -g pm2

// 运行
pm2 start app.js

// 一些命令
pm2 list  查看应用运行状态
pm2 monit  追踪资源运行情况
pm2 describe [app id]  查看应用详细部署状态
pm2 logs  查看日志
pm2 restart [app id]  重启应用
pm2 stop [app id]  停止应用
pm2 web  开启api访问
```

#### 更新Node && 处理pm2报错：spawning pm2 daemon with pm2

1. 查看报错内容

   > vim pm2.log
   >
   > 有可能是node版本过低

2. 安装新版node

   ```shell
   ~$ wget https://npm.taobao.org/mirrors/node/v10.13.0/node-v10.13.0-linux-x64.tar.xz  //下载nodejs
   ~$ tar -xvf node-v10.13.0-linux-x64.tar.xz  //下载nodejs安装文件node-v10.13.0-linux-x64.tar.xz
   ~$ cd node-v10.13.0-linux-x64/bin && ls  //测试是否安装成功
   	node  npm  npx
   bin$ ./node -v  //./的意思是当前文件夹下，现在 node 和 npm 还不能全局使用
   	v10.13.0
   bin$ pwd  //pwd查看当前目录，记住这个目录，我们下面要用
   	/root/node-v10.13.0-linux-x64/bin
   ```

3. 全局使用node、npm

   ```shell
   bin$ cd ~  //回到~目录
   ~$ vim .bashrc  //打开.bashrc文件夹
       i  //进入编辑模式
       export PATH=/root/node-v10.13.0-linux-x64/bin/:$PATH  // 插入该语句
       编辑完成后，按esc键退出编辑状态，再输入(shift):wq保存并退出文件
   ~$ source .bashrc  // 使环境变量生效
   ```

4. 检查

   ```shell
   ~$ node -v
   	v10.13.0
   ~$ npm -v
   	6.4.1
   ~$ pm2 -v
   ```

#### 方案比较

![img](Linux.assets/clipboard-1597632058944.png)

![img](Linux.assets/clipboard-1597632064542.png)

### 踩坑Nodejs - Fs路径问题

问题所在

> fs模块读取文件的相对路径是以`启动server.js的位置`为基准的，而不是以server.js文件的位置！
>
> 即在本地调试时使用`npm run server`时，`./public/video`是指向`public`的静态资源里的
>
> 而在服务器中使用`pm2 start www`时，需要`../public/video`来指向`public`

解决方案：使用绝对路径

nodejs官方也推荐在使用fs模块读取文件时使用绝对路径，而不是相对路径

```javascript
const path = require('path') // 先引path包，这包还可以获取扩展名path.extname()
let PUBLIC_PATH = path.resolve(__dirname, '../public');
```

## Yum篇

### Apache的使用

```shell
// 安装Apache
yum install -y httpd
apachectl -v

// 启动Apache
apachectl start

// 测试Apache
curl -l localhost

// 其他命令
apachectl stop  停止Apache

// 如果apache安装成为linux的服务的话，可以用以下命令操作：
service httpd start 启动
service httpd restart 重新启动
service httpd stop 停止服务

// 一键安装Lamp环境
yum install -y mysql* httpd* php*
```

### yum命令报错File "/usr/bin/yum", line 30 except KeyboardInterrupt, e:

两种解决方案

![img](Linux.assets/clipboard-1597632367227.png)

## Pip与Python篇

### Python

```shell
wget https://www.python.org/ftp/python/3.7.2/Python-3.7.2.tgz  # 下载
tar  -xf    ***.gz  # 解压
./configure && make && make install  # 编译

# 这个时候要删除之前 装好的软连接，再添加的软连接里

ln -s /usr/local/bin/python3.7 /usr/bin/python  # 创建软连接

# 【【会有BUG】】yum用python2编写，这样改会导致yum不可用。方案：这里用python3软连接或改yum配置

ln -s /usr/local/bin/python3.7-config /usr/bin/python-config

python -V  # 再次查看py的版本号
```

### pip
```shell
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py   # 下载安装脚本
sudo python get-pip.py    # 运行安装脚本
```

# 杂记

## linux下/bin和/usr/bin和/usr/local/bin的区别

> /bin 是所有用户都可以访问并执行的可执行程序。包括超级用户及一般用户
>
> /usr/bin 是系统安装时自带的一些可执行程序。即系统程序，轻易不要去动里面的东西，容易入坑
>
> /usr/local/bin 是用户自行编译安装时默认的可执行程序的安装位置，这个不小心误删点什么，不会影响大局























