# Fiddler（旧版）

# 目录

# Fiddler

## 简介

简概

- Fiddler是位于客户端和服务器端的HTTP代理
- 目前最常用的http抓包工具之一
- 功能非常强大，是web调试的利器
    - 监控浏览器所有的HTTP/HTTPS流量
    - 查看、分析请求内容细节
    - 伪造客户端请求和服务器响应
    - 测试网站的性能
    - 解密HTTPS的web会话
    - 全局、局部断点功能
    - 第三方插件
- 使用场景
    - 接口调试、接口测试、线上环境调式、web性能分析
    - 判断前后端bug、开发环境hosts配置、mock、弱网断网测试

## 软件安装

- 旧版

    - 下旧版的好处：有汉化，不强制安装在C盘，使用前无需登录，网络资源暂时比较多

- 新版

    - 和旧版的界面区别有点大
    - 官网下就好，不过强制安装在C盘了

    - 免费，另有付费版，但使用前都需要登录（可使用谷歌账号）

# 知识点

## B/S架构

Web Client（Browsers）——————HTTP Server

## Fiddler原理

简概

- 监听原理：软件启动时设置了系统代理，而浏览器读的就是系统代理

- 浏览器使用的系统代理

    - 火狐浏览器 > 选项 > 常规 > 网络设置 > 设置 > 配置访问互联网的代理服务器 > 默认选项为使用系统代理设置

    - 谷歌浏览器 > 设置 > 高级 > 系统 > 打开您计算机的代理设置

        （话说我这里为了看B站港澳台，这里显示的是 “chrome使用的是由某款扩展程序制定的代理设置”）

    - 系统代理

        - 控制面板看：控制面板\所有控制面板项\网络和共享中心 > Internet选项 > 连接 > 局域网设置
        - win10设置看：可以直接从谷歌浏览器跳转进入

- 代理服务器

    - 软件开启后，可以在系统代理中看到勾选了启用代理服务器

        默认代理服务器地址127.0.0.1，端口8888（但我的电脑不是，而是8866端口，可能8888被占用了，也可能是新版的Fiddler默认端口不同）

    - 另外，当我使用ssr代理时，自动配置使用了端口25378

    - 注意代理服务器好像会覆盖掉自动配置？

## HTTP协议

简概

- Hyper Text Transfer Protocol（超文本传输协议）
- 用于从万维网服务器传输超文本到本地浏览器的传送协议
- HTTP是基于TCP的应用层协议，它不关系数据传输的细节，主要用来规定客户端和服务器的数据传输格式。最初是用来想客户端传输HTML页面的内容。默认端口是80
- http是基于请求和响应模式的、无状态的、应用层的协议

抓包会话的内容

- 请求报文

    - 请求行

        | 请求方法 | 说明                                 |
        | -------- | ------------------------------------ |
        | GET      | 请求资源                             |
        | POST     | 提交资源                             |
        | Head     | 获取响应头                           |
        | PUT      | 替换资源                             |
        | DELETE   | 删除资源                             |
        | OPTIONS  | 允许客户端查看服务器性能             |
        | TRACE    | 回显服务器收到的请求，用于测试或诊断 |

    - 请求头 / 首部行（Request Header）

        | 请求头          | 说明                                                         |
        | --------------- | ------------------------------------------------------------ |
        | Host            | 主机ip地址或域名                                             |
        | User-Agent      | 客户端相关信息，如操作系统、浏览器等信息                     |
        | Accept-Charset  | 指定客户端接收信息类型，如：image/jpg, text/html, application |
        | Accept-Encoding | 客户端接收的字符集，如gb2312, ios-8859-1                     |
        | Accept-Language | 可接受的内容编码，如gzip                                     |
        | Authorization   | 接受的语言，如Accept-Language: zh-cn                         |
        | Cookie          | 携带的cookie信息                                             |
        | Referer         | 当前的文档的URL，即从哪个连接来的（可防止盗链）              |
        | Content-Type    | 请求体内容类型，如Content-Type: application/x-www-form-url   |
        | Content-Length  | 数据长度                                                     |
        | Cache-Control   | 缓存机制，如Cache-Control: no-cache                          |
        | Pragma          | 防止页面被缓存，和Cache-Control: no-cache作用一样            |

    - 空一行

    - 请求正文（请求体，get没有请求体）

- 响应报文

    - 状态行（包含状态码）

        | 状态码 | 说明                          | 举例 |
        | ------ | ----------------------------- | ---- |
        | 1XX    | 提示信息，请求被成功接收      |      |
        | 2XX    | 请求被成功处理                | 200  |
        | 3XX    | 重定向相关（已缓存 / 重定向） | 304  |
        | 4XX    | 客户端错误                    | 404  |
        | 5XX    | 服务端错误                    | 500  |

    - 响应头 / 首部行（Response Header）

        | 响应头         | 描述                                                         |
        | -------------- | ------------------------------------------------------------ |
        | Server         | HTTP服务器的软件信息                                         |
        | Date           | 响应报文的时间                                               |
        | Expires        | 指定缓存过期时间                                             |
        | Set-Cookie     | 设置Cookie                                                   |
        | Last-Modified  | 资源最后修改时间                                             |
        | Content-Type   | 响应的类型和字符集，如：COntent-Type：text/html，charset=utf-8 |
        | Content-Length | 内容长度                                                     |
        | Connection     | 如KEep-Alive，表示保持tcp连接不关闭，不会永久保持连接，服务器可设置 |
        | Location       | 指明重定向的位置，新的URL地址，如304的情况                   |

    - 空行

    - 响应体

状态码URL

- Uniform Resource Locator同一资源定位符

# 软件

## 软件界面

### 菜单栏

- File
- Edit
- Rules规则
    - 可以隐藏304和隐藏CONNECTs
    - Customize Rules自定义规则，`Ctrl+R`，打开后是一个C#脚本，可以黏贴网上找的脚本进去。如添加ip列
- Tool工具
    - Options选项 > 可以修改监听端口
    - WinNETOptions
- View
- Help

### 工具栏

- WinConfig
- 备注
- Replay重放，`R`重放一次，`Shift+R`设置连续重放多少次
- Remove清除，Remove all等，`Ctrl+X`清除全部
- Go，配合断点使用，下一步
- Stream，流模式，原来是缓冲模式，一般不用
- Decode，解码，解码所有Traffic。也可以不点这里，点报文上面的提示按钮，单独界面一个响应
- Keep: All sessions，保持会话的数量，默认保持全部
- Any Process，选择监听的程序。可以拖拽到指定程序上，如只监听某浏览器
- Find查找，`Ctrl+F`快捷键，常用且实用
- Save保存，保存为saz格式的文件，是可用Fiddler打开的工程文件
- 截图，就是截屏幕，小工具，没啥用
- 计时器，小工具，没啥用
- Browse，浏览器，可以打开浏览器，没啥用
- Clear Cache，清除ie缓存
- TextWizard，解码编码窗口
- Tearoff，分离窗口
- MSDN Search，在MSDN中搜索
- Online在线，本机的一些信息

### 监控面板 / 会话列表（Session List）

可排序标记等，还可以右键保存所选会话到文本文件 

- `#`，id和类型图标
- Result，结果，即状态码
- Protocol，协议
- Host，主机名
- URL，统一资源定位符
- Body，大小
- Caching，缓存
- Content-Type，内容类型
- Process，哪个进程抓包来的
- Comments，注释
- Custom，自定义

### 命令行

`Alt+Q`快速执行命令，输入help会打开官网文档

- `dpu keyword`，断点指定traffic
- `dpu`（第二次），结束断点
- `?keyword`，高亮显示指定traffic
- `>number`，高亮显示文件大小大于指定值的traffic

### 状态栏

- Capturing，捕获状态开启/关闭
- 断点状态，不断点 / 请求前断点 / 响应后断点
    - 对应菜单功能：Rules > Automatic Beakpoints自动断点 > Before Requests / After Responsets
- All Processes，选择监听的进程，所有进程 / 浏览器进程 / 非浏览器进程
- 选择了多少个session/共多少个session
- 附加信息

### 辅助标签 + 工具

#### statistics 统计信息

统计时间、吞吐量等

#### Inspectors 检查器【常用】

查看请求头请求体内容，可以用多种的形式去查看内容

- Headers标头，分类
- TextView文本视图
- SyntaxView语法视图，带格式和着色
- WebForm表单
- HexView十六进制视图
- Auth认证
- Cookies
- Raw原始
- JSON
- XML
- Transformer
- Caching缓存

#### AutoResponder 自动响应器【常用】

应用，例如：替换图片、替换修改过的js以钓鱼

使用

- (1) 勾选启用规则

- (2) AddRule添加规则 > RuleEditor规则编辑器 > 填写原traffic和替换traffic

    后者可以是url/本地资源，也可以是软件内置的traffic，如404
    
    也可以直接从SessionsList拖拽进来，再进行修改

#### Composer 组合器【常用】

作用：自定义请求/响应报文，简单的接口测试工具。类似于postman那种

使用

- 手动设置报文内容

    也可以直接从SessionsList拖拽进来，再进行修改

- Execute执行

视图

- Parsed解析
- Raw原生
- Scratchpad多个请求
- Options选项

#### Filters 过滤器【常用】

使用

- 勾选Use Filters，启用过滤器

选项

- Host 主机
    - 不带过滤 / 只显式广域网 / 只显式局域网
    - 不带主机过滤 / 隐藏以下主机 / 仅显示以下主机 / 标记下列主机
- Client Process 客户端进程
    - 仅显示通信：电脑上运行软件的进程
    - 仅显示IE通信
- Request Headers 请求头
    - 筛选指定URL
    - 隐藏指定URL
    - 标记指定URL
    - 删除指定URL
    - 设置请求头（新加请求头）
- Breakpoints 断点
    - 在POST中断请求
    - 中断请求的查询字符串
    - 中断对XML HTTP请求
    - 中断响应的内容类型
- Response Status Code 响应状态码
    - [略]
- Response Type and Size 响应类型和大小
    - [略]
- Response HEaders 响应头
    - [略]

#### Fiddler Orchestra Beta

新出的功能（Beta版本）

#### 画廊

#### ECode

#### FiddlerScript 脚本

#### Log 日志

#### Timeline 时间轴

# 实战

## 断点

使用

- 全局断点
    - 菜单工具设置Automatic Beakpoints 自动断点
    - 状态栏点击对应位置快速设置断点
- 局部断点
    - 命令行：`bpu keyword`/`dpafter keyword`断点指定通信，再次输入`bpu`/`dpafter`取消

作用

- 修改内容
- 模拟网络中断

## 模拟弱网状态

菜单Rules规则 > Rerformance性能 > Simulate Modem Speeds模拟调制解调器速度

菜单Rules规则 > 自定义规则 > 搜索simulate > 修改参数可以自定义延迟的量，值是每1kb延迟多少毫秒

## HTTPS证书问题

原理

- https其实能捕捉到，但问题在于无法解码
- https加密：http + ssl + TLS，存在一个证书

---

安装证书

- 菜单Tools工具 > Options选项 > HTTPS > 里面有两个勾选项和一个按钮

    Capture HTTPS CONNECTs 捕获HTTPS连接，默认勾选了

    Decrypt HTTPS traffic 解密HTTPS通信，需要勾选，即可

- 如果不行

    Actions > Reset All Certificates重置证书

---

火狐的解决方案

- 火狐不使用

    先在Actions处导出证书到桌面

    然后打开火狐浏览器 > 隐私与安全 > 证书 > 查看证书 > 导入 > 全部勾选 > 确定

---

火狐问题的原理

- Actions用于配置，可以从中打开Windows证书管理器，即根证书
- 谷歌是使用的Windows证书管理器中的根证书
- 但火狐不是，他使用自己的证书，需要手动导入

## 抓手机设备APP包

- (1) 先设置代理，手机设置：wifi设置 > 代理 > 手动 > 
    - 主机名：`电脑的局域网ip`（可以在工具栏的Online中查看）
    - 端口：`Fiddler监听的端口`（可在工具 > 选项 > 连接中查看监听的端口）

- (2) Fiddler设置

    - 工具 > 选项 > 连接 > 要勾选Allow remote computers to connect（允许远程计算机连接）

- (3) 下载根证书

    - 此时头条 / 浏览器等有的APP能直接抓到，而有的软件抓不到，因为证书有问题。需要安装根证书

    - 方法：浏览器访问：`http://电脑的局域网ip:Fiddler监听的端口/`会进入一个页面

        点击you can download thi FiddlerRoot certificate下载根证书

- (4) 安装根证书

    - 手机设置 > 更多/高级设置 > 系统安全  > 加密与凭据 > 从存储设备安装 > 安装前面下载来的根证书

不保证都可以进行抓包，有的软件会防止抓包，抓包越来越困难了

## Willow插件

Fiddler插件网站：www.telerik.com/fiddler/add-ons

虽然Willow不在该插件网站上

Willow插件作用：工具 > Host管理，的加强版，用来管理规则的

# 补充 / 踩坑

## 乱码问题

要单击工具栏上的Decode（解码）按钮，以启用解码功能

## 默认的8888端口被占用

![image-20210126101426385](Fiddler.assets/image-20210126101426385.png)

这个端口是被ipython notebook的默认端口`8888`给占用了

但如果这里点 “是” 的话，不太好

- 每次生成的随机端口都是随机的
- 生成的随机端口不可修改
- 每次都会弹出这个对话框

这给调试带来不便，所以应该点否，然后进去以后再修改默认端口。修改一次再重启软件后就指定默认端口了

![image-20210126101533126](Fiddler.assets/image-20210126101533126.png)

## 网络安全启示

- 加密：防止断点轻易修改数据
- 后端做好校验：防止绕过前端向后端发起非法请求而导致后端崩溃

## Fiddler和Wireshark区别

### 原理不同

- Fiddler：系统代理
- Wireshark：网卡数据复制

### 局限性

- Fiddler：手机设备需要安装证书，而且Firefox无法抓到https，而且有的App别说解密，连包都抓不到（不走你的系统代理）

### 手机上的一些无法被抓包的内容

比如支付宝、腾讯

参考链接：https://www.zhihu.com/question/54900955

原因

你在手机上设置代理，应用可以不使用的。比如在安卓上使用一些第三方的http/https库，它们是不会使用系统代理的
但是，要抓的话也还是可以的，安卓上root了的话，可以使用proxydroid，它会识别出数据协议然后转发到你指定的代理那里过去。





























