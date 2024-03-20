# Wireshark

[^wireshark怎么抓包、wireshark抓包详细图文教程]: https://blog.csdn.net/holandstone/article/details/47026213

# 目录

[toc]

# 工具

## 介绍

> wireshark是非常流行的网络封包分析软件，功能十分强大。可以截取各种网络封包，显示网络封包的详细信息。
>
> 使用wireshark的人必须了解网络协议，否则就看不懂wireshark了。
>
> 为了安全考虑，wireshark只能查看封包，而不能修改封包的内容，或者发送封包。

## 抓包协议

> wireshark能获取HTTP，也能获取HTTPS，但是不能解密HTTPS，所以wireshark看不懂HTTPS中的内容
>
> 如果是处理HTTP,HTTPS 还是用Fiddler
>
> 其他协议比如TCP,UDP 就用wireshark

## 使用

**wireshark是捕获机器上的某一块网卡的网络包**，当你的机器上有多块网卡的时候，你需要选择一个网卡。

## 窗口介绍

![2013050217125642416](Wireshark.assets/2013050217125642416.png)

## 过滤器

过滤器有两种：

> - 一种是显示过滤器，就是主界面上那个，用来在捕获的记录中找到所需要的记录
> - 一种是捕获过滤器，用来过滤捕获的封包，以免捕获太多的记录。 在Capture -> Capture Filters 中设置

保存过滤：

> - 在Filter栏上，填好Filter的表达式后，点击Save按钮， 取个名字。新版本点表达式左侧的标签图标

表达式规则：

> - 协议过滤
>
>   ​	如：`TCP`
>
> - IP过滤
>
>   ​	如：`ip.src ==192.168.1.102`和`ip.dst==192.168.1.102`分别为源地址和目标地址
>
> - 端口过滤
>
>   ​	如：`tcp.port ==80`和`tcp.srcport == 80`，后者只显示TCP协议的源端口为80的
>
> - Http模式过滤
>
>   ​	如：`http.request.method=="GET"`,  只显示HTTP GET方法的
>
> - 逻辑运算符
>
>   ​	如：`AND`、`OR`

# 知识点

## 原理

### wireshark对应OSI七层模型

这里只有五层，因为它对应的是现代的因特网协议栈（详见《计算机网络 - 自顶向下方法》，而国内大学一般都是按七层教，但实际上只有五层）

![2013050217125736394](Wireshark.assets/2013050217125736394.png)

## TCP

### TCP包具体内容

![2013050217125787134](Wireshark.assets/2013050217125787134.png)

### 分析TCP三次握手

![2013050217125714223](Wireshark.assets/2013050217125714223.png)

这图我都看过很多遍了， 这次我们用wireshark实际分析下三次握手的过程。

打开wireshark, 打开浏览器输入 http://www.cr173.com

在wireshark中输入http过滤， 然后选中GET /tankxiao HTTP/1.1的那条记录，右键然后点击"Follow TCP Stream",

这样做的目的是为了得到与浏览器打开网站相关的数据包，将得到如下图

![2013050217125854801](Wireshark.assets/2013050217125854801.png)

图中可以看到wireshark截获到了三次握手的三个数据包。第四个包才是HTTP的， 这说明HTTP的确是使用TCP建立连接的。

#### 第一次握手数据包

客户端发送一个TCP，标志位为SYN，序列号为0， 代表客户端请求建立连接。 如下图

![2013050217125843584](Wireshark.assets/2013050217125843584.png)

#### 第二次握手的数据包

服务器发回确认包, 标志位为 SYN,ACK. 将确认序号(Acknowledgement Number)设置为客户的I S N加1以.即0+1=1, 如下图

![2013050217125855065](Wireshark.assets/2013050217125855065.png)

#### 第三次握手的数据包

客户端再次发送确认包(ACK) SYN标志位为0,ACK标志位为1.并且把服务器发来ACK的序号字段+1,放在确定字段中发送给对方.并且在数据段放写ISN的+1, 如下图:

![2013050217125894588](Wireshark.assets/2013050217125894588.png)

就这样通过了TCP三次握手，建立了连接

## 一些其他协议

### HTTP

要注意缓存问题

#### 着色

- 一般而言全是绿底黑字
- 偶尔出现黑底红字表示`Bad TCP`
- 偶尔出现红底黄字表示`TCP RST`或`SCTP ABORT`

#### 协议

- 网络层：IP，不显示为包，而是会显示在传输层和应用层的头部
- 传输层：TCP（三次握手，四次挥手）
- 应用层：HTTP

#### 抓包结果

- (1) 第一次握手

    - Protocol：TCP
    - Info：[SYN]
    - inspector
        - 三次握手少了应用层

- (2) 第二次握手

    - Protocol：TCP
    - Info：[SYN，ACK]
    - inspector
        - 三次握手少了应用层

- (3) 第三次握手

    - Protocol：TCP
    - Info：[ACK]
    - inspector
        - 三次握手少了应用层

- (4) HTTP响应

    - Protocol：HTTP

    - inspector

        - 帧：Frame 187，这里是表示wireshark抓取的id

            `Frame 187: 1036 bytes on wire (8288 bits), 1036 bytes captured (8288 bits) on interface \Device\NPF_{C52ECB1F-B415-4A45-B5FF-FACD70E0F629}, id 0`

        - 链路层：Ethernet II，这里的Dst是网关的，我这里抓到的是个人路由器名称和物理地址（可通过`arp -a`查证）

            `Ethernet II, Src: IntelCor_43:27:b8 (54:8d:5a:43:27:b8), Dst: Tp-LinkT_c4:a7:b2 (54:a7:03:c4:a7:b2)`

        - 网络层：**I**nternet **P**rotocol **V**ersion **4**，IPv4协议

            `Internet Protocol Version 4, Src: 192.168.1.107, Dst: 140.143.51.136`

        - 传输层：**T**ransmission **C**ontrl **P**rotocol，传输控制协议

            `Transmission Control Protocol, Src Port: 5168, Dst Port: 80, Seq: 1, Ack: 1, Len: 982`

        - 应用层：**H**yper**t**ext **T**ransfer **P**rotocol，超文本传输协议

            `Hypertext Transfer Protocol`

### ICMP

在CMD里`Ping`的过程使用的就是这个

`Info`信息一般是`Echo (ping) request`（请求）和`Echo (ping) reply`（响应）

Windows中CMD的Ping命令一般是四次请求和四次响应，交替出现，一共8个包

（但我试出来是两次请求（第一次是no response found，第二次才是reply in），一次响应，共12个包）

### SMPP

short message peer to peer，短消息对等协议，TCP流

刚开始我以为是对应的QQ的短信息，但后来看了下是TCP流，应该不是

隐约能看到进行QQ通信的QQ号信息

特征

- 最顶层结果中的Password字符串里面隐含了QQ号信息
- Info是Outbind
- 目标ip不对，定位到了天津的服务器
- 有多次握手
- 发信息无需对方应答
- 有的字节看不到，但切换搜索模式为`分组字节流`后能搜到

![image-20210126144444965](Wireshark.assets/image-20210126144444965.png)

### SSDP

Simple Service Discovery Protocol，简单服务发现协议，UDP流

### TLSv1.2

UDP流 + TLS流

TLS的作用三个作用

- （1）身份认证
    通过证书认证来确认对方的身份，防止中间人攻击
- （2）数据私密性
    使用对称性密钥加密传输的数据，由于密钥只有客户端/服务端有，其他人无法窥探。
- （3）数据完整性
    使用摘要算法对报文进行计算，收到消息后校验该值防止数据被篡改或丢失。

# 过滤器 Filter

## 善用补全提示

例如`ip.`，然后什么都不用按，就有各种补全选项

## 常用的过滤器

用双方ip筛选

- `ip.src == ip地址`，源地址
- ` ip.dst == ip地址`，目标地址
- `ip.addr == ip地址`，地址（源/目标），等同于`ip.src == ip地址 or ip.dst == ip地址`

布尔

# 实操



# 实战

## 干扰项太多的问题

尽量选用副Q以减少干扰，而且虚拟机也能很好地解决这个问题！

**kali自带wireshark**，在09-嗅探/欺骗一分类中，不用下载Linux版本和安装！！！挺干净的

## QQ的iocq协议

可获得对方的ip？

但是这里的QQ只能看到自己的，看不到别人的

Filter: `iocq`

![5465416+](Wireshark.assets/5465416+.png)

## 利用QQ电话获取对方ip地址

- (1) 打开wireshark捕获
- (2) 给对方QQ电话
    - 是否需要对方接通：有的版本的QQ不需要，20210126测得需要接通才行
- (3) ctrl+f在信息流中搜索，`分组列表`改为`分组详情`，搜索内容为`020048`（其实是以该字符串开头的Data数据），搜索到的就是
- (4) Internet Protocol Version（网络层）中查看
    - Source（自己的ip，内网中会显示为内网ip）
    - Destination（目标ip，有内网和外网ip，忽略前者，找外网ip，得到的便是对方的ip地址）

![image-20210126141330881](Wireshark.assets/image-20210126141330881.png)

## 抓取手机数据报

### 坑：支付宝

暂时还没有哪个手机模拟器能够登陆上支付宝

放弃了使用手机模拟器，直接电脑开热点抓手机包

### 坑：电脑热点

- 踩坑一：刚开始我试了很多的移动wifi软件，包括360wifi、捷豹wifi、wifi共享精灵等，都不行。wifi共享精灵报错：开启失败，无线网卡不支持WiFi
- 解决一：后来发现1709版本自带了`移动热点`，可以在消息栏（对应快捷键`Win+A`）中开启
- 踩坑一：win10移动热点，手机无法连接或连接超时
- 解决二：在`控制面板\所有控制面板项\网络连接`的页面中，发现开启后多出来`本地连接*2`。然后设置：WLAN > 属性 > 共享 > 勾选允许共享，且`家庭网络连接`中选择新增的网络连接，这里是`本地连接*2`

### 信息所属ip

- 结论

    - 手机连上电脑热点以后，刚开始我为了避免电脑的通话干扰，屏蔽了电脑ip，只抓手机ip

    - 可惜什么都没抓到，后来用被访问的ip过滤发现抓到的都是电脑ip的包，即用电脑ip来抓即可，不用管手机ip

- 原因分析

    - 不太懂手机难道不传包给电脑吗？我猜测原因可能是路由器需要分配给局域网ip，而手机连电脑热点的ip不在局域网内
    - 如果ip协议中使用的是手机的ip，那么家庭路由器可能就不知道应该把这个通信包发给谁
    - 所以这个通信包一开始就是使用电脑的ip

- 难题

    - 但如果是这样的话，手机的通信包和电脑的通信包混在一起了，只用ip就很难过滤了
    - 如果是使用http协议的话，可以通过`http contains "User-Agent:"`的方式进行过滤，或者在分组详细里搜索
    - 如`User-Agent: Mozilla/5.0 (Android 10; Mobile; rv:85.0) Gecko/85.0 Firefox/85.0\r\n`筛选Android设备

## 支付宝App抓包总结

踩坑

- 亲测Fiddler无效，Fiddler原理是设置系统代理，但支付宝会绕开系统代理进行通信
- 为排除干扰使用虚拟机，但Linux无法安装手机模拟器
    - Genymotion：但后来了解了下是VirtualBox平台的，不支持VMWare平台
    - anbox：好像也不行
    - xdroid：理论上支持Kali系统，但安装过程中出错，可能和虚拟机环境有关
- 之所以用Linux是因为Kali自带了Wireshark，不用安装那么麻烦，后来没办法，只能在虚拟机用Windows7
    - Windows7下Wireshark安装后打开显示没有找到接口：应该是无法检测到网卡
    - 解决方案：https://blog.csdn.net/littlle_yan/article/details/79403680，手动安装Winpcap
- 然后发现目前网上的所有手机模拟器均无法进行支付宝的登录，后来只能进行手机联电脑热点，走电脑网卡进行抓包

































