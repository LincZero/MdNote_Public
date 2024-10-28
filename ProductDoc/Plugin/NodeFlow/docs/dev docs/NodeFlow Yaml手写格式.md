# NodeFlow Yaml手写格式设计过程

## 介绍

yaml语法：

1. 扩展部分
  1. `key: value`
  2. 换行缩进表示层级
  3. `value` 前面加 `|换行`，则value可以写多行
2. json的部分
  - `{}` 和 `[]`
    yaml是json的超集，有时我们使用混合语法会比纯用无 `{}` 和无 `[]` 的写法更简单，用这两个语法来压缩多行到一行
  - `""` 哪怕混合使用，也不建议使用引号了

相关工具：在线编辑Yaml并实时矫正

- https://www.bejson.com/validators/yaml_editor/
- https://yaml.cn/
- https://toolgg.com/yaml-validator.html
- json2yaml： https://www.bejson.com/json/json2yaml/

## 语法设计

### 摸索过程

#### 最简单的yaml

```yaml
nodes:
- id: a
  title: abc
- id: b
  title: cba
edges:
- source: a
  target: b
```

#### 多socket的节点

```yaml
nodes:
  - id: 8
    type: '8, VAEDecode'
    inputs:
      - name: samples
        type: LATENT
        link: 7
      - name: vae
        type: VAE
        link: 8
    outputs:
      - name: IMAGE
        type: IMAGE
        links:
          - 9
        slot_index: 0
    properties:
      Node name for S&R: VAEDecode
    widgets_values: []
  - id: 9
    type: '9, SaveImage'
    inputs:
      - name: images
        type: IMAGE
        link: 9
    outputs: []
    properties: {}
    widgets_values:
      - ComfyUI
links:
  - - 1
    - 8
    - 0
    - 9
    - 0
    - IMAGE
groups: []
config: {}
```

#### 按行简化

（类似json line，一行是一个节点/socket/线）

- nodes
  - id, name, type
    - id, name, type(i/o/attr), value
    - id, name, type(i/o/attr), value
  - id, name, type
    - id, name type(i/o/attr), value
    - id, name type(i/o/attr), value
- edges
  - from node-socket to node-socket

示例：

```ts
nodes
  1:name1
    1:sdf type:value
    2:df type:value
  2, sdfs
    1, dsf type:value
    2, dsf type:value
edges
  1.1, 2.1
  1.2, 2.2
```

#### yaml混合json语法简化

name特殊规则: 第一个下划线及以前的内容不作为名字的组成部分，通过该方式设计 `可选id`

（无组）口诀：第二可括号是

```ts
nodes: [
  [node_id, node_title,
    [socket_id, socket_title, type?, value?],
    [id, socket_title, type?, value?],
  ],
  [
    node_id, node_title,
      [socket_id, socket_title, type?, value?],
      [id, socket_title, type?, value?],
  ]
]
edges: [
]
```

叫：**无引号, yaml混json**

再优化下：

### V1

#### 经典childen写法、去除children字段

```ts
nodes3:
  children:
    node_id1:
      self: [node_name]
      children:
        socket_id1: [socket_name, socket_type, socket_value]
        socket_id2: [socket_name, socket_type, socket_value]
    node_id2:
      self: [node_name]
      children:
        socket_id1: [socket_name, socket_type, socket_value]
        socket_id2: [socket_name, socket_type, socket_value]
    group:
      children:
        node_id3:
          self: [node_name]
          children:
            socket_id1: [socket_name, socket_type, socket_value]
            socket_id2: [socket_name, socket_type, socket_value]
edges3:
  children:
    edge_id1: [from_node, from_socket, to_node, to_socket]
    edge_id2: [from_node, from_socket, to_node, to_socket]
```

- 优点：经典写法
- 缺点：由于children标识过于臃肿，我们将所有的children去掉。用self表示节点自身属性，非self节点视为children属性：

#### yaml-json

- 优点：没那么臃肿
- 缺点：不符合**一行一个项**的设计，还可以再优化

```ts
nodes:
  node_id1:
    self: [node_name]
    socket_id1: [socket_name, socket_type, socket_value]
    socket_id2: [socket_name, socket_type, socket_value]
  node_id2:
    self: [node_name]
    socket_id1: [socket_name, socket_type, socket_value]
    socket_id2: [socket_name, socket_type, socket_value]
  group:
    node_id3:
      self: [node_name]
      socket_id1: [socket_name, socket_type, socket_value]
      socket_id2: [socket_name, socket_type, socket_value]
edges:
  edge_id1: [from_node, from_socket, to_node, to_socket]
  edge_id2: [from_node, from_socket, to_node, to_socket]
```

#### yaml-json-fake (特殊语法糖，后续会再转yaml的)

- 优点：这样可以少几个 `self` 行，且满足**一行一个项**的设计
- 缺点：但不合法

```ts
nodes4:
  node_id1: [node_name]
    socket_id1: [socket_name, socket_type, socket_value]
    socket_id2: [socket_name, socket_type, socket_value]
  node_id2: [node_name]
    socket_id1: [socket_name, socket_type, socket_value]
    socket_id2: [socket_name, socket_type, socket_value]
edges4: [
  edge_id1: [from_node, from_socket, to_node, to_socket],
  edge_id2: [from_node, from_socket, to_node, to_socket]
]
```

也可以让他合法：但逗号就多起来了，而且yml和json的过度混合容易混乱

```ts
nodes4:
  node_id1: { self: node_name,
    socket_id1: [socket_name, socket_type, socket_value],
    socket_id2: [socket_name, socket_type, socket_value]}
  node_id2: { self: node_name,
    socket_id1: [socket_name, socket_type, socket_value],
    socket_id2: [socket_name, socket_type, socket_value]}
```

#### yaml-array

- 优点：这样依然可以少几个 `self` 行，且满足**一行一个项**的设计，也能合法
- 缺点：但是尾部的 `]` 随着叠层增加，臃肿，且逗号也多起来了

```ts
nodes2: [
  [node_id1, node_name,
    [socket_id1, socket_name, socket_type, socket_value],
    [socket_id2, socket_name, socket_type, socket_value]],
  [node_id2, node_name,
    [socket_id1, socket_name, socket_type, socket_value],
    [socket_id2, socket_name, socket_type, socket_value]],
  [group_name,
    [node_id2, node_name,
      [socket_id1, socket_name, socket_type, socket_value],
      [socket_id2, socket_name, socket_type, socket_value]]],
]
edges2: [
  [edge_id1, from_node, from_socket, to_node, to_socket],
  [edge_id2, from_node, from_socket, to_node, to_socket]
]
```

或者这样：

```ts
nodes4:
  node_id1: [node_name,
    socket_id1: [socket_name, socket_type, socket_value],
    socket_id2: [socket_name, socket_type, socket_value]
  ]
  node_id2: [node_name,
    socket_id1: [socket_name, socket_type, socket_value],
    socket_id2: [socket_name, socket_type, socket_value]
  ]
```

#### 纯列表

(大体和yaml-array的结构是一样的，但少了 `[]` 和结束尾)

- nodes
  - node_id1, node_name
    - socket_id1, socket_name, socket_type, socket_value
    - socket_id2, socket_name, socket_type, socket_value
  - node_id2, node_name
    - socket_id1, socket_name, socket_type, socket_value
    - socket_id2, socket_name, socket_type, socket_value
  - **group_name**
    - node_id3, node_name
      - socket_id1, socket_name, socket_type, socket_value
      - socket_id2, socket_name, socket_type, socket_value
- edges
  - edge_id1, from_node, from_socket, to_node, to_socket
  - edge_id2, from_node, from_socket, to_node, to_socket

列表判断原理：

- nodes：除根部，单元素群组，双元素节点，四元素socket
- edges：五元素正常，三元素为串联id语法糖

#### 字符串表示的yml

- 缺点：无法通过json解析函数一次性进行解析，还不如全部重新文本解析。没啥用

```ts
node_id1, node_name
  socket_id1, socket_name, socket_type, socket_value
  socket_id2, socket_name, socket_type, socket_value
node_id2, node_name
  socket_id1, socket_name, socket_type, socket_value
  socket_id2, socket_name, socket_type, socket_value
group_name
  node_id3, node_name
    socket_id1, socket_name, socket_type, socket_value
    socket_id2, socket_name, socket_type, socket_value
edge_id1, from_node, from_socket, to_node, to_socket
edge_id2, from_node, from_socket, to_node, to_socket
```

### V2

#### 结构解释 - 根部

方案一：nodes和edges的根元素可以去掉，真正完全做到：**一行一个项**

（可选：edge可以被一个空group包起来）

- node_id1, node_name
  - socket_id1, socket_name, socket_type, socket_value
  - socket_id2, socket_name, socket_type, socket_value
- node_id2, node_name
  - socket_id1, socket_name, socket_type, socket_value
  - socket_id2, socket_name, socket_type, socket_value
- **group_name**
  - node_id3, node_name
    - socket_id1, socket_name, socket_type, socket_value
    - socket_id2, socket_name, socket_type, socket_value
- edge_id1, from_node, from_socket, to_node, to_socket
- edge_id2, from_node, from_socket, to_node, to_socket

方案二：把最外部的nodes和edges视为一个**特殊的组**，这样也能做到：**一行一个项**

还是选择==方案二==吧

#### 结构解释 - self项

将self看作是一个特殊的socket！并且使之可选！

就像是Python/js类方法里的 `init` 或 `construct` 方法代表的是给自己用的，而不是给别人的。

这样也能符合：**一行一个项**

#### JSONLN

**一行一个项**的灵感来机器学习常用的 `JSONL` 格式，而这里我们在此基础上使用缩进增加了对嵌套的支持。

所以我把这种结构叫：`JSONLN` (JSON-LINE-NEST)

#### 简化合法格式

就保留两个：

1. yaml-json
2. 纯列表
  - 可以把self item往下写，也可以往上写
  - 写多行内容时较yaml更方便

### V3

可选字段列表，socket_name, socket_type、socket_value有时不是必须填的。简化数组数量。

语法糖：用input/output来代替socket类型的输入和输出！

- node_id1, node_name
  - socket_id0, name (value，可选) (type, 可选，未支持，或许可以通过value判断type)
  - socket_id1, name input
  - socket_id2, name output
  - socket_id3, k value
- node_id2, node_name
  - socket_id1, name (value，可选) (type, 可选，未支持)
  - socket_id2, name (value，可选) (type, 可选，未支持)
- **group_name**
  - node_id3, node_name
    - socket_id1, name (value，可选) (type, 可选，未支持)
    - socket_id2, name (value，可选) (type, 可选，未支持)
- edge_id1? from_node, from_socket to_node, to_socket
- edge_id2? from_node, from_socket to_node, to_socket

解释：等同传统做法中的：

```ts
- self: node_id1 node_name
  children:
  - self: socket_id0 name (value，可选) (type, 可选，未支持，或许可以通过value判断type)
    children:
  - self: socket_id1 name (value，可选) (type, 可选，未支持，或许可以通过value判断type)
    children:
  - self: socket_id2 name (value，可选) (type, 可选，未支持，或许可以通过value判断type)
    children:
- self: node_id2 node_name
  children: 
  - self: socket_id0 name (value，可选) (type, 可选，未支持，或许可以通过value判断type)
    children:
  - self: socket_id1 name (value，可选) (type, 可选，未支持，或许可以通过value判断type)
    children:
  - self: socket_id2 name (value，可选) (type, 可选，未支持，或许可以通过value判断type)
    children:
- self: edge_id1 from_node, from_socket to_node, to_socket
  children:
- self: edge_id2 from_node, from_socket to_node, to_socket
    children:
```

即：每个object固定有且只有两个项

- 我们省略了self项，用不缩进表示
- 我们省略了children项，用缩进表示

在开发时，为了灵活性，我们增加了parent项。每一个树节点都有父子指针！

## 语法确定

### V1

```nodeflow-list2
- nodes
  - 1, name1
    - s11, name, input
    - s12, name, output
    - s13, name, value
  - 2, name2
    - s21, name, input
    - s22, name, output
    - s23, name, value
  - 3, name3
    - s31, name, input
    - s32, name, output
    - s33, name, value
- edges
  - 1,source-0, 2,target-0
  - 2,source-0, 3,target-0
```

```nodeflow-list-demo-old
```


(默认类型为node)

```nodeflow-list-demo2
- nodes
  - 1, name1
    - s11, name: input
    - s12, name: output
    - s13, name: value
  - 2, name2
    - s21, name: input
    - s22, name: output
    - s23, name: value
  - 3, name3
    - s31, name: input
    - s32, name: output
    - s33, name: value
- edges
  - 1, s12, 2, s21
  - 2, s22, 3, s31
```

### 配合anyblock

[code(nodeflow-list-old)]

- nodes
  - 1, name1
    - s11, name, input
    - s12, name, output
    - s13, name, value
  - 2, name2
    - s21, name, input
    - s22, name, output
    - s23, name, value
  - 3, name3
    - s31, name, input
    - s32, name, output
    - s33, name, value
- edges
  - 1,source-0, 2,target-0
  - 2,source-0, 3,target-0

### v2 id:name, value:name

[code(nodeflow-list-old)]

- nodes
  - node1
    - s11:name, input
    - s12:name, output
    - s13:name, value
  - node2
    - s11:name, input
    - s12:name, output
    - s13:name, value
  - node3
    - s11:name, input
    - s12:name, output
    - s13:name, value
- edges
  - node1, source-0, node2, target-0
  - node2, source-0, node3, target-0

### v3 简化、默认socket

```
- nodes
  - node1:重名测试
    - i1:重名测试, input
    - o1:重名测试, output
    - v1, value
  - node2:重名测试
    - i1, input
    - o1, output
    - v1, value
  - Group1
    - node3
    - node4
- edges
  - node1,o1, node2,i1
  - node2,o1, node3,l
  - node2,o1, node4,l
  - node1,o1, node3,b
```

