# (idea) 设计：AnyBlock 节点与多层菜单

## 介绍

### 应用场景

一是表单、二是节点转用表单

### 对比

- json类型
  - 类型(8): Number、String、Boolean、Array/Object、null、Value(any)、Whitespace
  - 但最后两种没怎么见过，只适配6种应该也行
- 请求表单 - json
  - 类型(8)：string、integer/number、boolean、array **/object、null/any**
- 请求表单 - params
  - 类型(6): string、integer/number、boolean、array、**file**
- 请求表单 - 表单实体
  - 基本同上，但输入框类型还分：数字类型(是否密码)/文本单多行属性/约束等等
- 节点表单类型
  - 新增节点输入、节点输出类型
    (特点：允许给一个字符串作为二次类型、通常没有Key名字，取之替代的是二次类型名)
- 简化 - Schema码类型
  - 删除了嵌套功能，节点类型删除Object/Array
  - 删除了约束 (范围、必填等)
  - 主要属性："type"、"default"

### 相似产品

我记得 plantuml 有一个东西可以用于 UI 页面的绘制，甚至能着色、绘制按钮、显示菜单的展开状态等

但我这里并不需要，更需要的是稳定的格式

### AnyBlock 用 card+dir 模拟节点

之前是用 card + dir 来模拟节点，例如：

[card|addClass(ab-col2)]

#### Load Checkpoint

中文：Checkpoint加载器(简易)
作用：加载扩散模型

- Checkpoint名称: 加载大模型
- (O) 模型
- (O) CLIP
- (O) VAE

#### CLIP Text Encode (Prompt)

中文：CLIP文本编码器 (提示词) (正面)
作用：CLIP (ContrastiveLanguageImagePretraining) 理解输入文字的意思

- (I) CLIO
- 文本
- (O) 条件

#### CLIP Text Encode (Prompt)

中文：CLIP文本编码器 (提示词) (负面)

- (I) CLIO
- 文本
- (O) 条件

#### Empty Latent Image

中文：空Laten
作用：潜空间，内部流程中的图像格式 (例如图生图时，先VAE编码转化为Laten数据，然后处理完再解码回图像)，可以用于设置图片大小

- 宽度
- 高度
- 批次大小

#### KSampler

中文：K采样器

[dir]

- (I) 模型
- (I) 正面条件
- (I) 负面条件
- (I) Latent
- seed        | 种子
  - fixed     | 固定
  - increment | 生成后自增
  - decrement | 生成后自减
  - randomize | 随机
- control_after_generate | 运行后操作
- steps 步数
- CFG
- sampler_name| 采样器,采样方法
- scheduler   | 调度器
- denoise     | 降噪
- (O) Latent

#### VAE Decode

中文：VAE (变分自编码器) 解码器，用于将 Latent 格式转 Images 格式

- I samples
- I vae
- O Image

#### Save Image

中文：图片保存

- I images
- filename_prefix

## 设计方案

### 杂记

新语法：card要不还是表示不变吧

然后里面的内容修改：

建议声明顺序：先O再I

每个表单项的属性：

- 类型 & ~~约束~~、默认值、描述

感觉基于table要比基于dir容易理解……毕竟其实不需要dir的嵌套功能

- 优点：
  - 非json化，易写 (底层还是转json)
  - 可以非列表，而是表格选择器
  - 其实在像 apifox 这种schema可视化定义软件中，呈现的也是表格（默认这个表格是没约束条件的，约束条件有一个单独的展开面板）
- 缺点
  - 适用于不可嵌套的结果，例如表单

```anyblock
[listroot(KSampler)|list2card|addClass(ab-col2)]

中文：K采样器

[nodeform]

- < name | description | type | default
```

### 类型问题

类型上，我们总体使用（请求表单 - params）。“表格简化” 中主要是apifox-params的界面。

但是需要注意那个无法生成 json-schema，我们一般还是要在 json 页面进行节点的定义。

先复习一下：

- 请求表单 - json
  - 类型(8)：string、integer/number、boolean、array **/object、null/any**
- 请求表单 - params
  - 类型(6): string、integer/number、boolean、array、**file**

如何表示节点的IO类型？由于 “请求表单 - params” 是没有object/null/any类型的，但json定义中却有，我们用object来表示节点输入类型、用null来表示节点输出类型 (**但这里属于是无理定义了**)

### Schema Demo


```json
{
    "type": "object",
    "properties": {
        "Latent": {
            "type": "string"
        },
        "model": {
            "type": "string",
            "description": "模型"
        },
        "positive": {
            "type": "string",
            "description": "正面条件"
        },
        "negative": {
            "type": "string",
            "description": "负面条件"
        },
        "Latent_image": {
            "type": "string",
            "description": "潜空间"
        },
        "seed": {
            "type": "string",
            "description": "种子"
        },
        "control_after_generate": {
            "type": "string",
            "description": "运行后操作"
        },
        "steps": {
            "type": "string",
            "description": "步数"
        },
        "CFG": {
            "type": "string"
        },
        "sampler_name": {
            "type": "string",
            "description": "采样器,采样方法"
        },
        "scheduler": {
            "type": "string",
            "description": "调度器"
        },
        "denoise": {
            "type": "string",
            "description": "降噪"
        }
    },
}
```

### 需要实现接口

1. 表格转Schema
2. Schema生成表单
3. 扩展：节点的 (I/O) Flag




