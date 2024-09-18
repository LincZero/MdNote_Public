# Redis

## 资料	

参考：

- 官网
  - https://redis.io/docs/ui/insight/
- 查文档
  - 中文文档
    - https://redis.com.cn/documentation.html，这个还行
    - ~~https://www.redisio.com/~~ (要关注公众号的，差评)
  - 官网文档
    - https://redis.io/docs/latest/
    - https://cndoc.github.io/redis-doc-cn/cn/documentation.html，内容是官网文档，有很多技巧，推荐阅读
  
- 学习
  - https://www.bilibili.com/video/BV1Jj411D7oG
    - 0:57:51。进度：19/19，完成。
    - 带动画不错，内嵌字幕，比较新，从视频内容可知是货真价实的2023-06产

  - https://www.bilibili.com/video/BV1cr4y1671t
    - 42:48:51
    - 黑马的


## 课程目录

- 基本概念
- 安装配置
- 常用命令
- 十大数据类型
- 事务
- 数据持久化
- 主从复制
- 哨兵模式

## 比较：redis 和 mongodb

转载：https://redis.com.cn/redis-vs-mongodb.html

Redis和MongoDB是两种不同类型的数据库，它们在数据存储和查询方式、数据模型以及适用场景等方面有一些明显的区别。下面是Redis和MongoDB之间的一些比较：

1. 数据模型：                            
   - Redis：Redis是一个**键值**存储系统，支持多种数据结构如字符串、哈希、列表、集合和有序集合。数据以键值对的形式存储，可以通过键快速访问数据。Redis适合用于缓存、会话存储和快速查询等场景。
   - MongoDB：MongoDB是一个**面向文档**的数据库，数据以类似JSON的BSON文档格式存储。每个文档都有一个唯一的ID，并且文档可以嵌套。MongoDB适合存储和查询复杂的数据结构和大规模数据集。
2. 数据持久化：                            
   - Redis：Redis支持持久化，可以将数据保存到磁盘上，以防止数据丢失。它提供了**快照**（snapshotting）和**AOF**（Append-only file）两种持久化方式。
   - MongoDB：MongoDB也支持持久化，将数据写入磁盘文件中。它使用**写时复制**（write-ahead logging）机制来保证数据的一致性和持久性。
3. 查询功能：                            
   - Redis：Redis提供了一些查询功能，如对字符串的模糊匹配、对集合的交并差等操作。然而，它并不是一个完整的查询语言，不支持复杂查询和索引，适合用于简单的数据检索。
   - MongoDB：MongoDB提供了强大的查询功能，支持丰富的查询语法和索引，可以进行复杂的查询操作，包括范围查询、正则表达式、聚合管道等。
4. 扩展性：                            
   - Redis：Redis采用单线程模型，通过异步I/O来实现高性能。它可以通过主从复制和分片来扩展读性能和存储容量。
   - MongoDB：MongoDB采用分布式架构，支持水平扩展和分片。它可以在集群中添加更多的节点来扩展存储和处理能力。
5. 事务支持：                            
   - Redis：Redis支持事务，可以将多个操作组合成一个原子性的操作序列。但是，Redis的事务是非严格的，即事务中的某个操作失败不会回滚其他操作。
   - MongoDB：MongoDB支持多文档事务，可以对多个文档进行原子性操作，保证事务的一致性。
6. 数据一致性：                            
   - Redis：Redis默认情况下是单机数据库，数据复制和故障恢复依赖于主从复制和Sentinel哨兵机制。在主节点故障时，可能会出现一段时间的数据不一致。
   - MongoDB：MongoDB支持复制集和分片集群，在故障时可以实现数据的自动备份和故障转移，提供更高的数据一致性和可用性。

总体来说，Redis适用于高性能的键值存储和缓存场景，而MongoDB适用于更复杂的数据存储和查询需求，特别是对复杂数据结构和丰富查询功能的支持。具体选择应根据实际应用需求和数据模型的特点进行评估。

## 分布式缓存和分布式锁

Q：为什么要用Redis（Redis VS 数据库）（Redis VS 程序map等）

A1：性能，内存操作而非磁盘操作

A2：分布式缓存而非本地缓存，生命周期与持久化





