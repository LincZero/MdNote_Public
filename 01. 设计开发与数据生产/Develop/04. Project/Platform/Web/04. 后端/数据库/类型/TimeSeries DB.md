# TimeSeries Datebase

参考：

- 官网：https://www.influxdata.com/

- https://jasper-zhang1.gitbooks.io/influxdb/content/Introduction/getting_start.html

- https://zhuanlan.zhihu.com/p/80062750

  InfluxDB技术交流群（QQ）：663274123

## 时序数据库选型

参考：[时序数据库选型](https://zhuanlan.zhihu.com/p/401091093)，**建议看原文**

参考：[什么是时序数据库？我们为什么需要时序数据库？](https://www.taosdata.com/tdengine/time-series-database/what-is-a-time-series-database)

### 数据特征：

1. **时间戳：**每个数据点都带有时间戳，这个时间戳对于数据的计算和分析十分重要。
2. **结构化：**与来自网络爬虫、微博、微信的海量数据不同，联网设备或监控系统生成的数据都是结构化的。这些数据都具有预定义的数据类型或固定长度，比如智能电表采集的电流、电压就可以用 4 字节的标准的浮点数来表示。
3. **流式：**数据源以近似恒定速率生成数据，如音频或视频流。这些数据流彼此独立。
4. **流量平稳可预测：**与电商平台或社交媒体网站的数据不同，时序数据的流量在一段时间内是稳定的，并且可以根据数据源的数量和采样周期来进行计算和预测。
5. **不变性：**时序数据一般都是 append-only，类似于日志数据，一般不容许而且也没有修改的必要。很少有场景，需要对采集的原始数据进行修改。
6. **量级大：**
   - 产生频率快（每一个监测点一秒钟内可产生多条数据）
   - 测点多信息量大（常规的实时监测系统均有成千上万的监测点，监测点每秒钟都产生数据，每天产生几十GB的数据量）

### 挑战

时序数据通常用于比较当前数据与历史数据、检测异常、生成实时警报以及预测未来趋势。时序数据解决方案一般考虑以下问题：

- 时序数据量通常很大，因此在执行存储、索引、查询、分析等操作时变得更加困难。
- 时序数据需要实时计算和分析，以便于实时检测异常并告警。 延迟可能会导致故障和业务影响。
- 通常需要关联来自不同传感器和其他源的数据，这使情况变得更复杂。
- 不管是原始数据查询、还是聚合数据查询，时序数据的查询一般都会带上查询时间范围，一方面是根据时间范围计算聚合时间窗口，另一方面是为了更高效的检索数据，提高查询效率，避免大量无效数据的扫描。
- 数据在一段时间内的变化趋势比单个数据点重要得多。例如，考虑到网络不可靠性或传感器读数异常，我们可能会在一段时间内的某个平均值超过阈值时设置警报，而不是在单个数据点上这样做。

[TDengine](https://www.taosdata.com/) 这类时序数据库，是基于时序数据的特点以及应用的特点进行优化和设计的，专为解决上述问题而生。这类专业的数据库使时序数据的处理变得更加高效，性能也比通用数据库更好。

### 时序点结构

每个时序点结构如下：

- timestamp: 数据点的时间，表示数据发生的时间。
- metric: 指标名，当前数据的标识，有些系统中也称为name。
- value: 值，数据的数值，一般为double类型，如cpu使用率，访问量等数值，有些系统一个数据点只能有一个value，多个value就是多条时间序列。有些系统可以有多个value值，用不同的key表示
- tag: 标签，一般为字符串类型，如主机名、设备名等维度信息，用于分类和聚合计算

### 可选范围

选数据库，当然要先去DB-ENGINE上看看排名。有这么几款时序数据库，进入了我们的选择范围。

首先是遥遥领先的InfluxDB，行业内最广泛应用的。然后是两款刚进入业内视野的国产时序数据库DophinDB和TDengine。最后是两款副业是时序数据库的：自带监控体系的Prometheus和分布式搜索引擎ElasticSearch。

参考资料：[https://db-engines.com/en/ranking/time+series+dbms](https://link.zhihu.com/?target=https%3A//db-engines.com/en/ranking/time%2Bseries%2Bdbms)

### 对比

- 数据库
  - 开源/商业/受欢迎程度
  - 性能
- influxdb
  - https://github.com/influxdata/influxdb 26.1k，单机版开源免费，集群版不开源收费，DB-ENGINES rank1
  - 性能测试报告：[https://www.influxdata.com/blog/influxdb-markedly-elasticsearch-in-time-series-data-metrics-benchmark/](https://link.zhihu.com/?target=https%3A//www.influxdata.com/blog/influxdb-markedly-elasticsearch-in-time-series-data-metrics-benchmark/)
- TDengine
  - https://github.com/taosdata/TDengine/tree/main 21.7k， 开源，DB-ENGINES rank9
  - https://www.taosdata.com/downloads/TDengine_Testing_Report_cn.pdf
  - 官网：https://www.taosdata.com/
- DolphinDB
  - 虽然有社区免费版，但会限制CPU数量和内存大小，功能上也有阉割
- ES
  - 无
  - 性能测试报告参考这两篇报告：[https://www.influxdata.com/blog/influxdb-markedly-elasticsearch-in-time-series-data-metrics-benchmark/](https://link.zhihu.com/?target=https%3A//www.influxdata.com/blog/influxdb-markedly-elasticsearch-in-time-series-data-metrics-benchmark/)、https://zhuanlan.zhihu.com/p/56092404
- Prometheus
  - DB-ENGINES rank3
  - 在场景方面：PTSDB 适合数值型的时序数据。不适合日志型时序数据和用于计费的指标统计。InfluxDB面向的是通用时序平台，包括日志监控等场景。而Prometheus更侧重于指标方案。两个系统之间有非常多的相似之处，包括采集，存储，报警，展示等等



基于上述各数据库的特点分析，总结如下：

| 数据库     | 优势                                                         | 劣势                                                     |
| ---------- | ------------------------------------------------------------ | -------------------------------------------------------- |
| Influxdb   | 应用最广泛，认可度最高，成功案例丰富                         | 集群版收费，单机版适用于小数据集                         |
| TDengine   | 性能强悍，国产自主研发，集群版免费，也有附加功能的收费版     | 缺少大厂的最佳实践案例，还在持续迭代开发                 |
| DolphinDB  | 高性能、分布式，支持快速存储、检索、分析及计算提供一站式解决方案 | 完全**收费**，适用于金融领域                             |
| ES         | 集群化、易于使用，适合多种分析查询应用场景                   | 功能和性能上与专业时序数据库有很大的差距                 |
| Prometheus | 独立地开源监控系统和告警工具，广泛应用于Kubernetes生态       | 目前监控体系基于zabbix，不便于再部署一套同类型的监控系统 |

## 结构原理

参考：https://www.cnblogs.com/MWCloud/p/11475347.html



## 自研

难点 

难实现功能

1. 数据压缩，https://heapdump.cn/article/2268808
2. 内存中的倒排索引
3. 查询语法封装
   - SQL支持
   - 正则支持
4. WAL（预写日志）、内存映射
5. 负载均衡

可以参考的点

- ~~盐值（Salt）~~





## TDengine

### 资料

- 性能测试报告：https://www.taosdata.com/downloads/TDengine_Testing_Report_cn.pdf

- 白皮书：https://portal-data-cn.obs.cn-north-4.myhuaweicloud.com/marketplace/public/app/attachment/20220527/89d001fc-d489-45d4-b37b-efa3bd704236/2204100327307016.pdf，包括数据结构、原理、亮点等

- 官方文档：https://docs.taosdata.com/

- 另一个官网？：http://www.tdengine.cn/cn/

- Github：https://github.com/taosdata/TDengine 

- 大致原理：https://docs.taosdata.com/concept/

- 架构：https://docs.taosdata.com/tdinternal/arch/

- 其他技术细节

  - [深入解析 TDengine 中的缓存技术](https://www.taosdata.com/tdengine-engineering/3118.html)
  - [负载均衡](https://docs.taosdata.com/tdinternal/load-balance/)

- 落地

  - https://www.cnblogs.com/taosdata/p/16521841.html

    - 协鑫能源科技股份有限公司
    - 规模：55 张超级表，子表数量达到 11 万张
    - 场景：最主要的入库数据是车辆传感器（如：车辆里程、经纬度等）以及换电站电池相关的传感器（电池的各种指标）数据
    - 在 TDengine、TiDB、MySQL 中存储的数据量比例大概为 6:3:1，仅仅使用了三台 4C+16G 的服务器，TDengine 便挑起了整个系统数据存储的大头，轻松支撑起了我们的服务

  - https://www.taosdata.com/tdengine-user-cases/5030.html

    - 蔚来能源系统
    - 规模 (低)：换电站 777 座，超充桩 3,404 根，目充桩 3,461 根，为用户安装家充桩 96,000+ 根。模拟 10,000 个设备上报数据，消息并发约 4k 左右。

  - https://www.taosdata.com/tdengine-user-cases/12705.html

    - 中天钢铁 GPS、 AIS 调度
    - 规模：平均每周收录 3000 多辆车辆表与 100 多条船只表。每张表中数据或多或少，累计数量已达百万，业务的实际效果也达到了预期
      TDengine 1477208 c/s，InfluxDB 273820 c/s

  - https://www.taosdata.com/tdengine-user-cases/7815.html

    - 韵达。（顺丰、中通、韵达、货拉拉：https://www.jianshu.com/p/70e775af8488）
    - 规模：在三台 16C 64G 的服务器上部署了集群，数据写入速度大概为每秒 5000 行。根据“**一个扫描枪一张表**”的模型建表，把设备的地点和站点类型设置为标签“。
      超级表下面已经有了近百万子表，经过 1 个多月的正式使用，保存了大约 200 亿行的数据量。值得一提的是，基于 TDengine 常用的查询基本可以在 1 秒之内完成，一些特定查询甚至可以达到毫秒级
      超级表是 20 个字段，大部分是 int 类型，有 5 个左右是 varchar 类型，最大的字段是一个用来存储中文的 500 长度的 nchar ，**大约占用 300GB 不到的磁盘（单副本）。而此前使用 MySQL 时，光硬盘使用就需要几个 TB（主从），**这还没有算上内存和 CPU 等资源，由此可见 TDengine 带来的降本增效是多么显著。

  - https://my.oschina.net/u/4248671/blog/4995153?_from=gitee_rec

    - 得物App

    - 规模：互联网电商公司，拥有数千 Sentinel Resources，而 Sentinel 的监控数据时间粒度按照秒来统计，那么一天理论上就能够产生   **数亿**   的数据，**理论写入数据的速度也将达到万 TPS**。统计数据：统计了所有资源的流量数据，例如通过 QPS、拒绝 QPS、响应时间等

      数百亿数据。写入性能：满足 4H16G 14Thread 400 c/10ms (4wc/s) 的使用需求

      查询的超级表数据量级在百亿，以下给出了几个典型场景的耗时情况：

      - last_row 函数：8.6ms 8.8ms 5.6ms
      - 查询单个应用 + 资源某五分钟的所有数据：3.4ms 3.3ms 3.3ms
      - 查询单个应用 + 资源某 3 小时内每 2 分钟的平均通过 qps：1.4ms 1.3ms 1.4ms
      - 以服务维度分组查询一天内每两分钟的平均通过 qps：2.34s 2.34s 2.35s
        （值得一提的是，在 2.0.7.0 版本的 TDengine 中进行该查询效率在十几秒左右，当时认为是不可接受的，经过几个版本后优化效果显著）
      - 以服务维度分组查询三天内每一小时的平均通过 qps：2.17s 2.16s 2.17s

  - 其他

    - [TDengine 在蔚来能源系统的落地实践_涛思数据（TDengine）的博客-CSDN博客](https://blog.csdn.net/taos_data/article/details/123790937?spm=1001.2014.3001.5502)
    - [解决两大难题，TDengine 助力亿咖通打造自动驾驶技术典范_涛思数据（TDengine）的博客-CSDN博客](https://blog.csdn.net/taos_data/article/details/124036013?spm=1001.2014.3001.5502)
    - [为什么说 MongoDB 和 HBase 不适用于汽车行业的时序数据处理？_涛思数据（TDengine）的博客-CSDN博客_influxdb与mongodb](https://blog.csdn.net/taos_data/article/details/124738383?spm=1001.2014.3001.5502)
    - [苏州大学：从PostgreSQL到TDengine_涛思数据（TDengine）的博客-CSDN博客](https://blog.csdn.net/taos_data/article/details/126120085?spm=1001.2014.3001.5502)
    - [TDengine在理想汽车物联网业务场景的落地实践 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/413089425)
    - [毫秒级返回数据，TDengine 在大疆车载智能驾驶云端平台上的应用 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/542109306)
    - [TDengine极简实战：从采集到入库，从前端到后端，体验物联网设备数据流转 - 掘金 (juejin.cn)](https://juejin.cn/post/7104263110323617800)

### 选型总结

官方文档真的非常详尽













































