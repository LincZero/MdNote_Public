# 文字描述图表

## 工具调研

文字描述图表

- 常见的 Graphviz、Mermaid、PlantUML、Markmap、数学引擎，这些详见该文件夹内的笔记

非文字描述的，这里也顺带记一下：

- [gojs](https://gojs.net/latest/index.html)
  - 代表关系类
    - Org charts
    - Genograms
    - Family trees
  - Security Diagrams
  - State charts
  - Industrial Diagrams
  - Flowcharts
  - Process Visualizations
  - Network Design and Monitoring
  - Dynamic Grouping
- [visjs](https://visjs.org/)
- [gramps](https://gramps-project.org/blog/contact/)

## 共同点抽象总结

1. svg

   语法很少，很原始
   元素就那几个：画圆/矩形(circle/polygon)、画文字(title)、画线(path)。然后有时要一个容器(g)，就没了
   然后大概了解下定位、宽高、填充等，和css有些类似的属性（你不搞复杂的记个宽高和定位就完全够用了，不要看着有的svg非常复杂就感觉他很复杂，其他的需要再查）

2. graphviz简化一点

   元素大致是一样的：画图元、文字、线、有时要一个容器。

   主要是简化了：图元的 “定位、宽高” 属性自动填，画线的定位和曲线设置也是自动填的 (会根据两端的节点自动设置线的两端位置，以及自动 "绕开节点")。

   主要是定位和宽高自动化了以后精简非常多

3. mermaid和plantuml中

   “节点 - 连接关系” 这一种架构的描述，其实和上面是一样的，没有再多做什么优化了。

   只是他们额外使用了 “模板”，扩展了很多图，如流程图、甘特图、序列图、等。

   在这一步中，用户不再需要考虑 “节点 - 节点之间的连接关系”，反正就是对着预设好的模板填


你会发现，其实mermaid和plantuml的 “非模板图”，和底层的东西并差不了太多


