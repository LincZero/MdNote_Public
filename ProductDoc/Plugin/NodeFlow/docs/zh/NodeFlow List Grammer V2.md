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
  - Load Checkpoint
    - only name, i
    - i2, i, *i2
    - i3, i, mul line
      i3-2
      i3-3
    - i4, i, *i4
    - only name, o
    - o2, o, *o2
    - o3, o, *o3
    - o4, o, mul line
      o4-2
      o4-3
    - v2, v, *v2
    - v4, , mul line
      v4-2
      v4-3
    - v3, , *v3
    - only name, 
    - v5:, , only value
      v5-1
      v5-2
- edges
```

@tab md source code (md源码)

````md
```nodeflow-list
- nodes
  - Load Checkpoint
    - only name, i
    - i2, i, *i2
    - i3, i, mul line
      i3-2
      i3-3
    - i4, i, *i4
    - only name, o
    - o2, o, *o2
    - o3, o, *o3
    - o4, o, mul line
      o4-2
      o4-3
    - v2, v, *v2
    - v4, , mul line
      v4-2
      v4-3
    - v3, , *v3
    - only name, 
    - v5:, , only value
      v5-1
      v5-2
- edges
```
````

:::

### 通用规则

1. **一行一个项**，“项” 有四种：节点、节点上I/O Socket或属性项、线、节点组，他们的声明方式：
    - 节点/组 `id(:name)?, ()="node"`
        不写冒号表示id和节点名是一样的，type可以不写，默认为 "node"
    - 接口 `id(:name), (i|o|v|""), (value)=""`
        type为 `input`/`output `表述输入或输出接口，`value` 表示并非这两种之一属性
    - 线条 `from, from socket, to, to socket, (name)?`
        从哪个节点id，的哪个socket id，到哪个节点id，的哪个socket id
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

::: tabs

@tab Plugin effect (插件效果)

```nodeflow-list
- nodes
  - node1:KSample
    - Latent, o
    - model, i
    - positive, i
    - negative, i
    - Latent, i
    - seed,
    - control_after_generate,, randomize
    - steps,, 20
    - CFG,, 8.0
    - sampler_name,, euler
    - scheduler,, normal
    - denoise,, 1.00
    - io defaultTest, i , test
    - io defaultTest, o, test
    - t1:noValueTest,
    - t2:,, noKeyTest
      mul lines test
  - node2:KSample
    - 潜空间, o
    - 模型, i
    - 正面条件, i
    - 负面条件, i
    - 潜空间, i
    - 种子,
    - 运行后操作,
    - 步数,
    - CFG,
    - 采样器/采样方法,
    - 调度器,
    - 降噪,
  - translate
- edges
  - node1,Latent, translate,l
  - translate,r, node2, 潜空间
```

@tab md source code (md源码)

````md
```nodeflow-list
- nodes
  - node1:KSample
    - Latent, o
    - model, i
    - positive, i
    - negative, i
    - Latent, i
    - seed,
    - control_after_generate,, randomize
    - steps,, 20
    - CFG,, 8.0
    - sampler_name,, euler
    - scheduler,, normal
    - denoise,, 1.00
    - io defaultTest, i , test
    - io defaultTest, o, test
    - t1:noValueTest,
    - t2:,, noKeyTest
      mul lines test
  - node2:KSample
    - 潜空间, o
    - 模型, i
    - 正面条件, i
    - 负面条件, i
    - 潜空间, i
    - 种子,
    - 运行后操作,
    - 步数,
    - CFG,
    - 采样器/采样方法,
    - 调度器,
    - 降噪,
  - translate
- edges
  - node1,Latent, translate,l
  - translate,r, node2, 潜空间
```
````

:::


