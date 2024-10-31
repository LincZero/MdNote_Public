# VIA教程

参考：https://www.bilibili.com/video/BV1YV4y1X7j2

网站：https://docs.qmk.fm/#/keycodes

## VIA简介和键盘识别

## 改键页面 Configure

## 宏 Macros

## 切层Layer

-   MO（Momentary On）
    -   临时切换到某层，默认返回0层。最常用的是Fn的出厂自带功能
-   OSL（One Shot Layer）
    -   一次性切层。按下后切换到第n层，触发一个键后自动返回原来的层
-   Fn1/Fn2
    -   Fn1/Fn2单独使用和MO(1)/MO(2)类似，两个同时长按会切换到第三层
-   space
    -   短按空格，长按第1层松开回0层（同MO1）。技巧：如果想要连续长按原来的键怎么办？例如原来的键是空格。短按两次再长按即可
-   LK（Layer, KC）
    -   （下一节Any再讲）
-   TG（Toggle）
    -   永久切层，不同于前面的临时切层。常用于开关RGB灯光、工作/游戏模式切换等。怎么返回0层？设置一个倒三角键用于退出即可。
-   TO
    -   短按永久切换，直到切换到其他层。例如可以0-->4-->2层这样进行切换

## Any键

**注意事项**

1.   汉化版的VIA可能没有Any功能
2.   花哨的键盘可能没有Any
3.   多模键盘可能没有Any，有些双模键盘可以



Any作用

1.   短按输出KC，长按切层，即LT（Layer Tab）
2.   短按输出KC，长按切换为Modifier，即MT（）
3.   弥补宏的数量限制，宏最多设置16个组合键，Any可以无数个



使用

-   LT
    -   英文：Layer Tab
    -   语法：LT(layer, kc)
    -   例如：LT(2, KC_D)
-   MT
    -   英文：Modifier Tab
    -   语法：MT(mod, kc)



修饰键组合，mod+kc，有两种方法

1.   宏：{KC_LALT, KC_A}

2.   Any：A(KC_A)。这个可以去官网查

     比较常见的有：

     -   C(kc)，ctrl+kc
     -   S(kc)，shift+kc
     -   A(kc)，alt+kc
     -   G(kc)，GUI+kc

     可以嵌套使用（会被自动修改成正常的语法），例如：S(G(KC_4)) 保存后会自动变成 LSG(KC_4)



## VIAL改键教程

（VIA落伍啦。VIAL改键教程__以Ow Spring为例__牛B的Tap Dance和Combos）

？？？？？？你TMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMD。你能不能把这个放第一章啊啊啊啊啊啊，我笔记都做完了！@！！

