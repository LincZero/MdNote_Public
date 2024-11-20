# NodeFlow 列表语法

## 一种基于Markdown列表的便于输入的节点描述语法

新增一种能手写的格式，说真的有时设计语法比开发成就感还强……大家讨论讨论语法，看有没有什么可以优化的地方

1. 该语法可以和AnyBlock插件配合，从列表进行声明
2. 参考了：JSON、JSONL、YAML、Mermaid/Mehrmaid 流程图语法

### 示例

::: tabs

@tab Plugin effect (插件效果)

```nodeflow-list
- nodes
  - node1: KSample
    - Latent, o
    - model, i
    - positive, i
    - negative, i
    - Latent, i
    - seed, v
    - control_after_generate, randomize:v
    - steps , 20:v
    - CFG, 8.0:v
    - sampler_name, euler:v
    - scheduler, normal:v
    - denoise, 1.00:v
    - io defaultTest, test:i
    - io defaultTest, test:o
    - t1:noValueTest, v
    - t2: , noKeyTest:v
  - node2: KSample
    - 潜空间, 0
    - 模型, i
    - 正面条件, i
    - 负面条件, i
    - 潜空间, i
    - 种子, v
    - 运行后操作, v
    - 步数, v
    - CFG, v
    - 采样器/采样方法, v
    - 调度器, v
    - 降噪, v
  - translate
- edges
  - node1,Latent, translate,l
  - translate,r, node2,模型
```

@tab md source code (md源码)

````md
```nodeflow-list
- nodes
  - node1: KSample
    - Latent, o
    - model, i
    - positive, i
    - negative, i
    - Latent, i
    - seed, v
    - control_after_generate, randomize:v
    - steps , 20:v
    - CFG, 8.0:v
    - sampler_name, euler:v
    - scheduler, normal:v
    - denoise, 1.00:v
    - io defaultTest, test:i
    - io defaultTest, test:o
    - t1:noValueTest, v
    - t2: , noKeyTest:v
  - node2: KSample
    - 潜空间, 0
    - 模型, i
    - 正面条件, i
    - 负面条件, i
    - 潜空间, i
    - 种子, v
    - 运行后操作, v
    - 步数, v
    - CFG, v
    - 采样器/采样方法, v
    - 调度器, v
    - 降噪, v
  - translate
- edges
  - node1,Latent, translate,l
  - translate,r, node2,模型
```
````

:::

::: tabs

@tab Plugin effect (插件效果)

```nodeflow-list

- nodes
  - node1:重名测试
    - o1:重名测试, output
    - o2:重名测试, output
  - node2:重名测试
    - i, input
    - o, output
    - v, value
  - Group1
    - node3
      - i, input
      - i2, input
    - node4
- edges
  - node1,o1, node2,i
  - node2,o, node3,i
  - node2,o, node4,b
```

@tab md source code (md源码)

````md
```nodeflow-list

- nodes
  - node1:重名测试
    - o1:重名测试, output
    - o2:重名测试, output
  - node2:重名测试
    - i, input
    - o, output
    - v, value
  - Group1
    - node3
      - i, input
      - i2, input
    - node4
- edges
  - node1,o1, node2,i
  - node2,o, node3,i
  - node2,o, node4,b
```
````

:::

### 示例 - 结合anyblock

```md
[code(nodeflow-list)]

- nodes
  - node1:重名测试
    - o1:重名测试, output
    - o2:重名测试, output
  - node2:重名测试
    - i, input
    - o, output
    - v, value
  - Group1
    - node3
      - i, input
      - i2, input
    - node4
- edges
  - node1,o1, node2,i
  - node2,o, node3,i
  - node2,o, node4,b
```

### 通用规则

1. **一行一个项**，“项” 有四种：节点、节点上I/O Socket或属性项、线、节点组，他们的声明方式：
    - 节点/组：`id:name, type`，不写冒号表示id和节点名是一样的，type可以不写，默认为 "node"
    - socket：`id:name, type`，type为input/output表述输入或输出节点，value表示节点的内部属性
    - 线：从哪个节点id，的哪个socket id，到哪个节点id，的哪个socket id
2. 缩进关系表示包含关系。例如节点组可以包含节点，节点可以包含节点组

### 特殊规则 (进阶)

1. 最外层是两个特殊组，nodes和edges，固定的。
    - 当然，有一个写法变形可以去掉最外层，用如果该项有四个参数就是edges组，否则则为nodes组，但我觉得虽然能写少了，但可能更容易造成混乱？待定
2. 当不声明节点socket时，会默认声明四个隐藏节点：left、right、top、bottom

## 超简化

```nodeflow-list

- nodes
  - GroupA
    - a1
    - a2
  - b
  - GroupC
    - GroupC1
      - c11
  - d
- edges
  - a1,r, b,l
  - a1,r, c11,l
  - a1,r, d,l
```

## 实际用例参考

```nodeflow-list
- nodes
  - node1: KSample
    - Latent, o
    - model, i
    - positive, v
    - negative, v
    - Latent_image, v
    - seed, v
    - control_after_generate, v
    - steps , v
    - CFG, v
    - sampler_name, v
    - scheduler, v
    - denoise, v
  - node2: KSample
    - 潜空间, 0
    - 模型, i
    - 正面条件, v
    - 负面条件, v
    - 潜空间, v
    - 种子, v
    - 运行后操作, v
    - 步数, v
    - CFG, v
    - 采样器/采样方法, v
    - 调度器, v
    - 降噪, v
  - 翻译
- edges
  - node1,Latent, 翻译,l
  - 翻译,r, node2,模型
```


