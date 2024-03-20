

# Markdown

# 目录

# plantUML by Gravize

参考：

- [【CSDN】Markdown中使用plantuml的探索](https://blog.csdn.net/Honnyee/article/details/115243923)
- [Gravizo官网](http://www.gravizo.com/)
- [plantuml官网文档](https://plantuml.com/zh/)
- [plantuml官网在线](http://www.plantuml.com/plantuml/uml/SyfFKj2rKt3CoKnELR1Io4ZDoSa70000)

## 教程

教程看plantuml官网文档就行

## UML

- 很多程序员采用UML（Unified Modeling Language，统一建模语言）绘制类图，用来描述类之间的关系。
  - ![img](plantUML by Gravizo.assets/01905.jpeg)

## Gravize引擎渲染实战

### 流程图

内部的写法和plantuml写法不一致

<img src='https://g.gravizo.com/svg?
@startuml;
(*) --> if "Some Test" then;
  -->[true] "activity 1";
  if "" then;
    -> "activity 3" as a3;
  else;
    if "Other test" then;
      -left-> "activity 5";
    else;
      --> "activity 6";
    endif;
  endif;
else;
  ->[false] "activity 2";
endif;
a3 --> if "last test" then;
  --> "activity 7";
else;
  -> "activity 8";
endif;
@enduml
'>

### 时序图

内部的写法和plantuml写法不一致

<img src='https://g.gravizo.com/svg?
@startuml;
actor User;
participant "First Class" as A;
participant "Second Class" as B;
participant "Last Class" as C;
User -> A: DoWork;
activate A;
A -> B: Create Request;
activate B;
B -> C: DoWork;
activate C;
C --> B: WorkDone;
destroy C;
B --> A: Request Created;
deactivate B;
A --> User: Done;
deactivate A;
@enduml
'>

### 类图

#### 踩坑：不能加载左尖括号

无法被认为是img：

```
<img src='https://g.gravizo.com/svg?
@startuml;
Class01 <|-- Class02;
@enduml
'>
```

encode：能认为是img，但是无法解析

```
<img src='https://g.gravizo.com/svg?
%40startuml%3B%0AClass01%20%3C%7C--%20Class02%3B%0A%40enduml
'>
```

没有左尖括号的都能顺利打

最终解决方法：在官网发现了有替代写法

```
用
Class29 ^-- Class30;
代替
Class29 <|-- Class30;
```

<img src='https://g.gravizo.com/svg?
@startuml;
Class03*-- Class04;
Class05 o-- Class06;
Class07 .. Class08;
Class09 -- Class10;
Class21 %23-- Class22;
Class23 x-- Class24;
Class25 }-- Class26;
Class27 +-- Class28;
Class29 ^-- Class30;@enduml
'>

### 思维导图













## 注意

上面的写法中，每个语句后面要接上 `;` ，否则会解析失败。报错no @startuml

后来在github上找到了原因：https://github.com/TLmaK0/gravizo/issues/50
 这里的`;`，相当于一个回车断句





```plantuml
@startuml;
Class03*-- Class04;
Class05 o-- Class06;
Class07 .. Class08;
Class09 -- Class10;
@enduml
```

