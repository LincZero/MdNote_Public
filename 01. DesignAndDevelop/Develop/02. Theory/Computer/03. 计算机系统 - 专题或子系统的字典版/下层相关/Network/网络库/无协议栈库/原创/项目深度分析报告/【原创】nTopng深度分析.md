---
tags:
  - 源码
---

# nTopng实现分析

## 目录

- 实现分析
  - 这个软件是如何利用nDPI库对不同的协议进行分类和分析的
  - 用了什么依赖库
  - 数据是怎么存储的
  - 源码分析、架构分析（重点为涉及 nTop 与 eBPF 的部分）
- 功能分析
  - nDPI具体能对报文分析都一个什么样的底部，能够从报文中挖出什么样的信息
  - 有哪些好用实用的功能
- 性能分析
  - 多维度测试：大流、多并发、多协议类型 的性能

## 环境准备

### 编译、安装

略，见 nTopng 那边的笔记

目前不需要搭第二个环境，我在 192.168.1.208:3000 中创建了一个，可以直接去用。有可能没开或试用期需要重置，再联系我

### 试用期重置

检查做得一塌糊涂。

这玩意有社区版和付费的几个版本，社区版图像都没有，基本没什么用。而社区版会有试10min的试用期，试用期过了就没法显示图像。但是：

1. 如果前端不像后端询问是否过期，后端是不知道自己已经过期了。理论上纯前端就能破解这个东西

2. 如果不刷新前端……哪怕不采取任何操作，也不会过期

3. 哪怕过期了，也是可以重置的……重置方法如下

   ```bash
   root@msy:/home/msy/installer# systemctl stop ntopng && systemctl start ntopng
   ```

## 实现分析

### 项目结构

吐个槽：这个结构前后端混在一起了，而且/cpp/和/h/文件夹里各有近200个.cpp和.h，真就完全不分层的

[dir]

- /assets/,  【前端】asserts
- /attic/
- /chickhouse/
- /contrib/
- /doc/,  可以在这里使用doxygen构建文档，官方也教你怎么去构建，应该是给使用旧版本的用户用的。
  用最新版的话官网有：[ntopng Documentation — ntopng 5.7 documentation](https://www.ntop.org/guides/ntopng/)
- /docker/,  给了个docker链接，无其他内容
- /fuzz/
- /grafana/
- /hooks/
- /http_src/,  【前端】应该是应用程序的前端程序
- /httpdocs/,  【前端】应该是构建文档页的前端程序
- /include/,  主程序，全是头文件
- /kibana/
- /m4/
- /packages/,  这个是检查你使用的是什么系统并给你安装对应系统的依赖包（包括这些系统的依赖包：ubuntu macos freeBSD  debian 等）
- /python/
- /scripts/,  主要是lua脚本
- /src/,  主程序，主要使用cpp，头文件在 /include/ 那边
- /tests/e2e/,  一个包含端到端测试的ntopng子模块
- /third-party/,  该目录包含ntopng中使用的第三方工具
  - j18n.lua-master
  - json-c
  - lua-5.4.3
  - lua-resty-template-master
  - mongoose
  - rrdtool-1.4.8
  - snmp
- /tools/
- autogen.sh
- package.json,  【前端】依赖包列表
- README.md
- ……

### 数据库实现借鉴

#### 基本调试 - 数据库快照

```bash
$ systemctl status ntopng # 先保证ntopng已开启
$ systemctl status redis-server # 这时redis服务器应该是开启中的状态。这也是看端口的方法，我这里端口是默认端口6379

$ redis-cli # 现在要和redis-cli交互
127.0.0.1:6379> keys * # 查看所有键值。若要获取特定键（请替换your_key）的值，请输入：get your_key

$ redis-cli bgsave # 可以创建一个数据库快照，来导出Redis中的数据。此命令将在后台创建一个Redis数据库快照。通过默认配置，在/var/lib/redis/dump.rdb文件中会生成一个名为dump.rdb的数据文件
# 若要导入数据，请确保Redis服务器未运行。然后将dump.rdb文件复制到Redis服务器的工作目录（默认为/var/lib/redis/），然后启动Redis服务器。
$ redis-cli CONFIG GET dir # 如果在默认工作没找到，就用该命令查看配置文件。Windows也是：PS D:\Soft\Redis> ./redis-cli.exe CONFIG GET dir
```

要查看更多Redis CLI命令和选项，请查看Redis命令参考文档： https://redis.io/commands/

#### 可视化连接查看 redis 数据

快照后怎么查看呢？这边个人的做法：

1. Windows上 下载 Redis Desktop Manager (Windows, macOS and Linux)

   - 网站：https://redisdesktop.com
   - Github：
     - （需要区分这三者：RedisInsight、RedisDesktopManager、AnotherRedisDesktopManager）
     - https://github.com/RedisInsight/RedisDesktopManager/releases（不仅是UWP版本的还得付费21美刀）
     - https://github.com/RedisInsight/RedisDesktopManager/releases
     - https://github.com/qishibo/AnotherRedisDesktopManager/releases（这个有二进制发布，**我用这个下的**）

2. 如果想要连接Linux上正在运行的Redis：

   - 打开软件并新建一个Connection，需要输入Redis的端口和账密

   - 技巧：

     ```bash
     $ systemctl status redis-server # 端口可以用这个查看
     
     # 账密可以用这个来找（Linux）
     $ cd /
     $ find -name "redis.conf" # 我的在这个位置：./etc/redis/redis.conf
     $ nano /etc/redis/redis.conf # 然后进里面搜索关键词：requirepass，可以搜：vim：/搜，n连续搜。或nano：^W搜，alt+W连续搜
     
     # 账密可以用这个来找（Windows）
     $ cd /
     $ dir /s /a redis.conf
     ```

3. BUG问题

   - 我这边遇到的一个问题是：`Client On Error: Error: connect ECONNREFUSED 192.168.1.208:6379 Config right?`

     解决方法：Linux 的 Redis 限制了外部访问，需要解除。方法：

     ```bash
     $ nano /etc/redis/redis.conf
     # 依次设置下面两个项（bind后面可能会跟一个::1，那个不用改也没事）。另外注意这种方法仅调试时用，可能会带来攻击安全隐患
     # bind 0.0.0.0
     # protected-mode no
     
     # 然后重启redis服务
     $ systemctl stop redis-server && systemctl start redis-server
     ```


#### 查看保存的 dump.rdb 数据库文件

如果想要查看之前的dump.rdb文件

1. 先解除读写权限，然后用FileZilla移到Windows本地

   - ```bash
     $ chmod 644 /home/msy/data/dump.rdb
     ```

2. Windows需要下载上一节提到的 Redis Desktop Manager 之外，还要下载Redis。

   必须在本地跑一个Redis才加载dump.rdb才能够查看这个数据库文件。

   下载后分别双击打开 redis-serveice.exe、redis-server.exe、redis-cli.exe 来运行Redis。之后应该能打开一个Redis/redis-cli.exe命令窗口：

   如果服务没正常跑起来：（比如你没开server直接打开 redis-cli.exe）

   ```bash
   Could not connect to Redis at 127.0.0.1:6379: Unknown error
   not connected>
   ```

   如果运行server成功后：

   ```bash
   redis 127.0.0.1:6397>
   ```

   此时 Redis Desktop Manager 应该成功连接到：`127.0.0.1@6379`，但目前里面依然是 “暂无数据”

3. 然后需要将原来的 dump.rdb 放进去。要打开文件 `Redis/conf/redis.conf`，这个是默认的配置：

   ```bash
   # 注意下面的两行内容不是挨在一起的，你要分别去这两个内容
   dir "D:/Soft/Redis/data"
   dbfilename dump.rdb
   ```

   然后将数据文件位置在这：`D:\Soft\Redis\data\dump.rdb`

   但此时 Redis Desktop Manager 应该依然是  “暂无数据”

4. BUG解决

   重启Redis服务器

   在修改完配置或将数据库文件放到指定路径后，可能需要重启 Redis Desktop Manager，否则 Redis Desktop Manager 应该依然是  “暂无数据”

   ```bash
   > cd D:\Soft\Redis
   > ./redis-cli.exe shutdown
   > ./redis-server redis.conf
   ```

   而重启后，开启时自动加载或按“加载所有”时可能报错：Scan命令执行异常（可能已被禁用），无法显示Key列表

   还是不行，后来发现应该是Redis版本太低。原来的Redis版本是2.4好像，是安装ntopng for windows给我装的，然后我从官网重新下载，是5.0.14.1版本，就可以了。

   三种查看版本方法：1. 在刚点开redis-server.exe时可以看、2. 在 Redis Desktop Manager 连接成功后可以看到、3. 命令行敲 `redis-cli --version` 也可以

   注意更新后配置文件变成了 `redis.windows.conf`（前面的命令也需要改变），同时dump.rdb的路径也变了


#### 正式分析

…… emmm，Redis是键值对数据库，key比较多，只筛选一些有效信息较多的键进行记录

大部分是text值，少部分是Json值和表值

下面挑着来记，没多大用的就不记了：

- 文件夹那快， 感觉是跟hash、索引有关的东西
- ntopng.assert.xxxx， 后面的xxxx通常是ip
- ntopng.cache.xxx， json值、text值、表值都有
- ntopng.cache.checks.ifid_8.macs_disconnected， 这个是记录mac地址的，好像Table值里条数最多就是这一项了
- ntopng.cache.servicemap
- ntopng.dns.cache.xxx， 这个应该是 <ip - 主机名>
- ntopng.prefs.iface_id， 这个是网络接口
- ntopng.sort.table.admin
- ntopng.trace， 

总结：

>  其实没有太多有效的东西，都是基于连接的一些存储。也没有大表，而且数据库设计得并不是很优雅与高效。
> 没太大的参考价值

### 库统计

#### 后端库统计

库有两个方面：

一方面是前面提到的 /third-party/ 里的库，直接在源代码中会有一份

[dir]

- /third-party/
  - j18n.lua-master
  - json-c
  - lua-5.4.3
  - lua-resty-template-master
  - mongoose
  - rrdtool-1.4.8
  - snmp

另一个方面是借助脚本进行依赖的安装，比如 nDPI 和 Redis 的部分

关于后者，请查看 “源码分析” 章节的内容

#### 前端库统计

提前总结：

- 旧的那套技术栈，无参考价值

精简化：

- vue：版本3.2.37
- jquery：很少见到用了Vue还带个jQuery的项目
- bootstrap：前端UI库（随便，代替品很多）
- webpack：打包（估计用Vite代替）
- ?：画图库未知（估计用eChart代替）

完整列表：

```json
"devDependencies": {
    "@babel/preset-env": "^7.16.11",
    "@rollup/plugin-babel": "^5.3.1",
    "@rollup/plugin-node-resolve": "^13.3.0",
    "@squoosh/lib": "^0.4.0",
    "autoprefixer": "^10.4.2",
    "babel-loader": "^8.2.3",
    "clean-webpack-plugin": "^4.0.0",
    "copy-webpack-plugin": "^10.2.4",
    "css-loader": "^6.6.0",
    "css-minify": "^2.0.0",
    "css-minimizer-webpack-plugin": "^3.4.1",
    "cubism": "^1.6.0",
    "eslint": "^8.9.0",
    "eslint-config-google": "^0.14.0",
    "file-loader": "^6.2.0",
    "i": "^0.3.7",
    "image-minimizer-webpack-plugin": "^3.2.3",
    "image-webpack-loader": "^8.1.0",
    "imagemin-gifsicle": "^7.0.0",
    "imagemin-mozjpeg": "^10.0.0",
    "imagemin-pngquant": "^9.0.2",
    "imagemin-svgo": "^10.0.1",
    "install": "^0.13.0",
    "mini-css-extract-plugin": "^2.5.3",
    "minimist": "^1.2.6",
    "node-sass": "^7.0.1",
    "onchange": "^7.1.0",
    "postcss": "^8.4.6",
    "postcss-cli": "^9.1.0",
    "postcss-loader": "^6.2.1",
    "postcss-scss": "^4.0.3",
    "regenerator-runtime": "^0.13.9",
    "rollup": "^2.79.1",
    "rollup-plugin-alias": "^2.2.0",
    "rollup-plugin-postcss": "^4.0.2",
    "rollup-plugin-replace": "^2.2.0",
    "rollup-plugin-terser": "^7.0.2",
    "rollup-plugin-vue": "^6.0.0",
    "rollup-watch": "^4.3.1",
    "sass-loader": "^12.5.0",
    "source-map-loader": "^3.0.1",
    "stylelint": "^14.5.0",
    "webpack": "^5.68.0",
    "webpack-cli": "^4.9.2"
},
"dependencies": {
    "@babel/core": "^7.18.2",
    "@googlemaps/markerclusterer": "^1.0.24",
    "@popperjs/core": "^2.11.2",
    "apexcharts": "^3.33.1",
    "bootstrap": "^5.3.0",
    "bootstrap-loader": "^3.0.4",
    "crossfilter2": "^1.5.4",
    "d3": "^3.5.17",
    "d3-array": "^3.1.1",
    "d3-chord": "^3.0.1",
    "d3-collection": "^1.0.7",
    "d3-sankey": "^0.12.3",
    "d3-shape": "^3.1.0",
    "d3v7": "npm:d3@^7.6.1",
    "datatables.net-buttons-dt": "^2.3.4",
    "datatables.net-colreorder-dt": "^1.6.1",
    "datatables.net-dt": "^1.11.5",
    "datatables.net-responsive-dt": "^2.4.0",
    "dc": "^4.2.7",
    "dygraphs": "^2.2.1",
    "flatpickr": "^4.6.11",
    "jquery": "^3.6.0",
    "jquery-ui-bundle": "^1.12.1-migrate",
    "jquery.are-you-sure": "^1.9.0",
    "leaflet": "^1.6.0",
    "leaflet.markercluster": "^1.5.3",
    "madge": "^5.0.1",
    "moment": "^2.29.1",
    "moment-timezone": "^0.5.34",
    "nvd3": "^1.8.6",
    "peity": "^3.3.0",
    "popper.js": "^1.16.1",
    "select2": "^4.1.0-rc.0",
    "store-js": "^2.0.4",
    "vis-network": "^9  .1.0",
    "vue": "3.2.37"
}
```

### 后端源码分析

先不会细致地去看，只看个大概。先不看具体实现，只看依赖结构

主要程序：



eBPF部分：

[dir]

- /doc/
  - README.eBPF.md
- /src/
  - ParsedeBPF.cpp
  - NetworkInterface.cpp
  - ParsedFlow.cpp
  - ZMQParseInterface.cpp
- /http_src/utilties/
  - ebpf-utils.js
- /include/
  - Flow.h
  - NetworkInterface.h
  - ntop_flow.h
  - ParsedeBPF.h
  - ParsedFlow.h



nDPI部分：

[dir]

- .gitignore， 这里忽略了一个nDPI文件夹，不知道干嘛的

- Makefile.in | 

  ```makefile
  NDPI_LIB = @NDPI_LIB@
  NDPI_INC = @NDPI_INC@
  NDPI_LIB_DEP = @NDPI_LIB_DEP@
  ```

- /attic/include/

  - FLow.,h
  - ntop_includes.h

- /doc/

  - README.compilation
  - README.developers.flow_state.md
  - README.FlowHashEntry_FSM.dot
  - README.fuzz.md
  - README.leaks_detector.md
  - README.quotas.md
  - /src/
    - example_api.lua

- /doc/src/api/lua_c/ntop/

  - interface_ndpi.rst
  - ntop_misc.lua

- /fuzz/README.md

- /include/， (#include "ndpi_api.h")

  - nDPIStats.h
  - NetworkInterface.h
  - ntop_includes.h
  - Ntop.h
  - ……

- /src/

  - ……

- ……



## 功能设计

### 界面路径

- /快捷键/

  - SNMP： (专业版功能)
  - Active Monitoring
  - 池
  - 通知

- /仪表盘/

  - 流量仪表盘 **(部分专业版功能)**
  - 网络发现
  - 流量报告 **(专业版功能)**
    - 数据保存时间：仪表盘这边，这个页面的数据都是永久性存储的
    - 内容包括：总体、各接口、各主机、各应用程序 的流量

- /警告/

  - Explorer
  - Flow Alerts Analyser **(专业版功能)**

- /流/

  - 活动流

- /主机/： 可以根据各种项来筛选主机，筛选主机后

  - 主机
  - MAC地址
  - 网络
  - 主机池
  - 自治系统
  - 国家
  - 操作系统
  - VLANs
  - 本地HTTP服务器
  - Local Hosts Traffic Rules **(专业版功能)**

- /地图/

  - Analysis
    - 服务地图： 路由追踪
    - Service Table
    - 周期图
    - Periodicity Table
    - Assert Map
    - Asser Table
  - 地理地图
  - 主机 **(专业版功能)**： 这个图表不会看

- /接口/

  - Details

  - Server Ports Analysis **(专业版功能)**

    - 这个页面挺炫酷的……能可视化看出各种连接的对比关系，但最多35个链接与最多的流量将被显示。

      图表中表示每个VLAN上使用的顶级服务器端口。如果启用了流存储，可以上报历史流端口。

      vlan、端口和应用协议是可点击的，将用户发送到相应的实时或历史流页面。

- /设置/

  - 用户
  - 首选项
  - License
  - 检查
  - Behavioural Check Exclusions
  - 管理配置
  - 管理数据
  - 流量概况 **(专业版功能)**
  - 应用程序和类别
  - 类别列表
  - 设备应用程序

- /开发者/

  - Analyse Pcap File： 可以在线打开PCap文件并进行分析，**但超过25MB就上载不了了**
  - 检查： 查看和检查程序内部的脚本，看脚本类型和耗时等
  - 警告和流状态定义： 类似于错误码解释，用来看 “警告码字符串” 对应一些属性的
  - 目录： 查看一些对应文件的存储路径，如：数据、脚本、Flow、Host、网络、接口、警告
  - Lua/C API

- /帮助/

  - 关于
  - ntop博客
  - Help and News
  - 用户手册
  - 报告问题
  - Suggest a Feature

有部分是需要在主页左上将`接口`切换为`系统`后，才有的独占菜单和选项：

- /健康状态/
  - 系统： 负荷、对每个接口的存储容量做统计、日志查看
  - 接口： 流数与警告流数、本地与远端主机、流量与包数统计
  - Redis： 获取的RAM内存、key数
- /轮询器/
  - 基础设施
  - SNMP
  - Active Monitoring： 这里好像有bug，“No data available in table”
- /池/： 不太明白干啥用的，感觉是可以将主机分成了多个组。例如自己公司单独一个组，与外部网络区分，方便筛选
  - 池
  - 主机池成员
- 通知

### 报文的分析程度

总结一下各个页面，统计能对报文分析到什么地步。虽然用了DPI但感觉没有进行太深入的分析

对每个Connect的统计：

- 通用统计
  - 基本流量统计。包括收发实时流量、总流量、流量比、流量曲线
  - 五元组统计。其中协议是有限支持。只支持tcp udp、ipv4 ipv6（其实是支持多种协议的，但没有基于Connect进行这些协议的统计，其他协议的统计是基与端口分析的……具体见后）
  - 主机设备统计。包括MAC地址、设备名，与开始、持续、结束时间
  - 接口统计
  - 应用程序统计
- VLAN
- DSCP
- 广播方向

对每个接口的统计：

- 通用统计
  - 基本流量统计。包括收发实时流量、总流量、流量比、流量曲线
  - 主机设备统计。包括MAC地址、设备名，与开始、持续、结束时间
  - 应用程序统计
- Capture
- 包大小分布
- DSCP

对端口 + 虚拟局域网的统计（这个对应 “Server Ports Analysis”，基与端口统计的）：

- 协议支持：（我那台环境应该比较纯净，没太多类型）

  HTTP.ntop、MDNS、HTTP、WSD、MDNS、SSDP、DHCPV6、LLMNR、DNS……

## 性能测试

多维度测试：

- 大流： 这个测过了，纯大流没用。

  主要是他这个不会逐包分析，只基于连接的统计用不了多少性能，我怎么测他都是满的。

  我建了3条udp 100的包的大流，十几G都是满正常的。需要不同流量不同种类的高并发的流量，才能测出结果。

- 多并发
- 多协议类型

（目前进度：正在收集具有代表性的流量数据）

