# C++面试八股文

参考：

（尽量找个有md资料的）

- [【C++秋招面试八股文】前巨人网络后台高级架构师耗时两个月！针对技术点分析之后提取出C++面试题，刷完秋招上岸](https://www.bilibili.com/video/BV1TV411K7bb)，共60p，8:23:04
  （讲得太乱了，而且感觉很多地方讲错了。后面我真想就按着目录跳着把面试题拿一份，再自己学算了。幸好P7开始排版好一些）
  进度：P1~7、9、(10)、12~14、……
- [C++校招社招面试, 真正讲解C++八股文的视频(6小时)一键三连收藏](https://www.bilibili.com/video/BV1ZQ4y1x7Yu)，这个比上面的好一点，但似乎没更新完
- [整理了200道2023年秋招C/C++面试八股文，校招、社招都涵盖了C++面试题](https://www.bilibili.com/video/BV1NW4y1c7dA)，面试题库

## 目录

C/C++

- 语言特性相关
- 标准库 stl、boost
- C++11/14/17/20
- 面向对象
- 设计模式

## 令牌桶限流算法是什么

令牌桶算法，是增加一个大小固定的容器，也就是令牌桶，系统以恒定的速率向令牌桶中放入令牌。当令牌桶满的时候，再向令牌桶生成令牌时，令牌会被抛弃。

如果有客户端来请求，先需要从令牌桶中拿一个令牌，拿到令牌，才有资格访问系统，这时令牌桶中少一个令牌。

在令牌桶算法中，存在以下几种情况:

1. 请求速度大于令牌的生成速度：那么令牌桶中的令牌会被取完，后续再进来的请求，由于拿不到令牌，会被限流。
2. 请求速度等于令牌的生成速度：那么此时系统处于平稳状态
3. 请求速度小于令牌的生成速度：那么此时系统的访问量远远低于系统的并发能力，请求可以被正常处理，令牌桶算法，由于有一个桶的存在，可以处理短时间大流量的场景。这是令牌桶和漏桶的一个区别。（那漏桶又是什么）













