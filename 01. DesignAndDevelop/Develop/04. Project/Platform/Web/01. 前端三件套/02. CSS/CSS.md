# CSS3

# 目录

# CSS布局测试

## 传统布局（盒状模型）



## Flex 弹性布局（新方案）

### 概述

参考：http://www.ruanyifeng.com/blog/2015/07/flex-grammar.html

布局的传统解决方案，基于[盒状模型](https://developer.mozilla.org/en-US/docs/Web/CSS/box_model)，依赖 [display](https://developer.mozilla.org/en-US/docs/Web/CSS/display) 属性 + [position](https://developer.mozilla.org/en-US/docs/Web/CSS/position)属性 + [float](https://developer.mozilla.org/en-US/docs/Web/CSS/float)属性。它对于那些特殊布局非常不方便，比如，[垂直居中](https://css-tricks.com/centering-css-complete-guide/)就不容易实现。

2009年，W3C 提出了一种新的方案----Flex 布局，可以简便、完整、响应式地实现各种页面布局。目前，它已经得到了所有浏览器的支持，这意味着，现在就能很安全地使用这项功能。

Flex 布局将成为未来布局的首选方案。本文介绍它的语法，[下一篇文章](http://www.ruanyifeng.com/blog/2015/07/flex-examples.html)给出常见布局的 Flex 写法。网友 [JailBreak](http://vgee.cn/) 为本文的所有示例制作了 [Demo](http://static.vgee.cn/static/index.html)，也可以参考。

以下内容主要参考了下面两篇文章：[A Complete Guide to Flexbox](https://css-tricks.com/snippets/css/a-guide-to-flexbox/) 和 [A Visual Guide to CSS3 Flexbox Properties](https://scotch.io/tutorials/a-visual-guide-to-css3-flexbox-properties)。

### Flex 布局是什么？

Flex 是 Flexible Box 的缩写，意为"弹性布局"，用来为盒状模型提供最大的灵活性。

任何一个容器都可以指定为 Flex 布局（包括行内元素）。

注意，设为 Flex 布局以后，子元素的float、clear和vertical-align属性将失效。

### 基本概念

采用 Flex 布局的元素，称为 Flex 容器（flex container），简称"容器"。它的所有子元素自动成为容器成员，称为 Flex 项目（flex item），简称"项目"。

![img](CSS.assets/clipboard.png)

容器默认存在两根轴：水平的主轴（main axis）和垂直的交叉轴（cross axis）。主轴的开始位置（与边框的交叉点）叫做main start，结束位置叫做main end；交叉轴的开始位置叫做cross start，结束位置叫做cross end。

项目默认沿主轴排列。单个项目占据的主轴空间叫做main size，占据的交叉轴空间叫做cross size。

```css
.box{display:flex;}
```

### 容器的属性

以下6个属性设置在容器上。

```css
flex-direction // 决定主轴的方向（即项目的排列方向）
flex-wrap // 定义，如果一条轴线排不下，如何换行
flex-flow // 是flex-direction属性和flex-wrap属性的简写形式
justify-content // 定义了项目在主轴上的对齐方式
align-items // 定义项目在交叉轴上如何对齐
align-content // 定义了多根轴线的对齐方式。如果项目只有一根轴线，该属性不起作用
```

**3.1 flex-direction属性**

决定主轴的方向（即项目的排列方向）

```css
row（默认值）：主轴为水平方向，起点在左端。
row-reverse：主轴为水平方向，起点在右端。
column：主轴为垂直方向，起点在上沿。
column-reverse：主轴为垂直方向，起点在下沿。
```

**3.2 flex-wrap属性**

定义，如果一条轴线排不下，如何换行

```css
nowrap（默认）：不换行
wrap：换行，第一行在上方
wrap-reverse：换行，第一行在下方
```

**3.3 flex-flow属性**

是flex-direction属性和flex-wrap属性的简写形式

**3.4 justify-content属性**

定义了项目在主轴上的对齐方式

```css
flex-start（默认值）：左对齐
flex-end：右对齐
center： 居中
space-between：两端对齐，项目之间的间隔都相等。
space-around：每个项目两侧的间隔相等。所以，项目之间的间隔比项目与边框的间隔大一倍。
```

**3.5 align-items属性**

定义项目在交叉轴上如何对齐

```css
flex-start：交叉轴的起点对齐。
flex-end：交叉轴的终点对齐。
center：交叉轴的中点对齐。
baseline: 项目的第一行文字的基线对齐。
stretch（默认值）：如果项目未设置高度或设为auto，将占满整个容器的高度。
```

**3.6 align-content属性**

定义了多根轴线的对齐方式。如果项目只有一根轴线，该属性不起作用

```css
flex-start：与交叉轴的起点对齐。
flex-end：与交叉轴的终点对齐。
center：与交叉轴的中点对齐。
space-between：与交叉轴两端对齐，轴线之间的间隔平均分布。
space-around：每根轴线两侧的间隔都相等。所以，轴线之间的间隔比轴线与边框的间隔大一倍。
stretch（默认值）：轴线占满整个交叉轴。
```

### 项目的属性

以下6个属性设置在项目上。

```css
order // 定义项目的排列顺序。数值越小，排列越靠前，默认为0。
flex-grow // 定义项目的放大比例，默认为0，即如果存在剩余空间，也不放大
flex-shrink // 定义了项目的缩小比例，默认为1，即如果空间不足，该项目将缩小
flex-basis // 定义了在分配多余空间之前，项目占据的主轴空间，浏览器根据这个属性，计算主轴是否有多余空间
flex // 是flex-grow, flex-shrink 和 flex-basis的简写，默认值为0 1 auto。后两个属性可选
align-self // 允许单个项目有与其他项目不一样的对齐方式，可覆盖align-items属性
```

## Grid 网格布局（新方案）

https://www.baidu.com/link?url=gByXFBeDJmnert69ThmkQTzMGzWeu0fDU8rF5R_2Kfg8rPK88QEqTOFxcnWJsktRA2RL5K9DCx96BCEljwuuG5eYWe3U5UfCFeXPX31IBru&wd=&eqid=83dcdea10004d0bb000000065f9a61e1

# CSS适配

## 相对单位与自适配单位

- 绝对长度单位。 绝对长度单位表示为一个固定的值，不会改变。不利于页面渲染
    - `in`，英寸
    - `cm`，里面
    - `mm`，毫米
    - `pt`
    - `pc`
- 相对长度单位。 其长度单位会随着它的参考值的变化而变化
    - 非适应单位
        - `px`，像素
    - 自适应单位
        - `%`，百分比
        - `em`，元素的字体高度，父元素的font-size
        - `rem`，根元素的font-size
        - `vm`，视窗宽度，1vw=视窗宽度的1%
        - `vh`，视窗高度，1vh=视窗高度的1%

## 字体单位（px、em、rem和%）

- `px`（像素）

- `em`（==相对==长度单位）

    - 描述：相对于父级元素的字体大小，当父级元素字体大小改变时，会重新计算。（`1em`表示字体大小与父元素大小相同）

    - 应用：TyporaMarkdown中的`行内代码`若想要在标题等位置使用（父级元素字体大小不同），就需要使用`em`，以进行自适应

- `rem`（==相对==长度单位）（css3新增的相对长度单位）

    - 名字：css3新增的一个相对长度单位，即`root-em`
    - 描述：相对于根元素的字体大小。（其中根元素默认字体大小为16px）
    - `em和rem`区别：**rem只相对于根目录**，即HTML元素。所以只要在html标签上设置字体大小，文档中的字体大小都会以此为参照标准

    - 应用：一般用于自适应布局。

- `%`（==相对==长度单位）（百分比）

## 屏幕单位（px、rem）

# CSS选择器

## 正则匹配

原文链接：https://blog.csdn.net/u012955801/article/details/87696514

> #### 1.attribute属性中包含value:　
>

```css
1、[attribute~="value"] 属性中包含独立的单词为value
    eg:[title~=flower]  <img src="/i/eg_tulip.jpg" title="tulip flower" />
    
2、[attribute*=value] 属性中做字符串拆分，只要能拆出来value这个词就行
    eg:[title*=flower]  <img src="/i/eg_tulip.jpg" title="ffffflowerrrrrr" />
```

> #### 2.attribute属性以value开头:
>

```css
1、[attribute|=value] 属性中必须是完整且唯一的单词，或者以-分隔开
    eg:[lang|=en]  <p lang="en">  <p lang="en-us">
    
2、[attribute^=value] 属性的前几个字母是value就可以
    e.g:[lang^=en]  <p lang="ennn">
```

> #### 3.attribute属性以value结尾:
>

```css
1、[attribute$=value] 属性的后几个字母是value就可以
    eg:[src$=".pdf"] <img src="test.pdf">
```

# CSS对齐

## 绝对定位居中的四种实现方法

css绝对定位居中的实现方法有很多，下面将给大家介绍css绝对定位居中的四种方法。

> #### 兼容性不错的主流css绝对定位居中的用法：

注意：这种方法有一个很明显的不足，就是需要提前知道元素的尺寸。否则margin负值的调整无法精确。此时，往往要借助JS获得。

```css
.conter{
    width: 600px; height: 400px;
    position: absolute; left: 50%; top: 50%;
    margin-top: -200px;    /* 高度的一半 */
    margin-left: -300px;    /* 宽度的一半 */
}
```

> ####  transform: translate方法

css3的出现，使得有了更好的解决方法，就是使用transform代替margin.

transform中translate偏移的百分比值是相对于自身大小的，可以这样实现css绝对定位居中：

```css
.conter{
    width: 600px; height: 400px;
    position: absolute; left: 50%; top: 50%;
    transform: translate(-50%, -50%);    /* 50%为自身尺寸的一半 */
}
```

> #### margin:auto实现绝对定位元素的居中(上下左右均0位置定位；margin: auto)

```css
.conter{
    width: 600px; height: 400px;
    position: absolute; left: 0; top: 0; right: 0; bottom: 0;
    margin: auto;    /* 有了这个就自动居中了 */
}
```

> #### 使用css3盒模型:flex布局实现css绝对定位居中

这种情况是在不考虑低版本浏览器的情况下可以使用

## 垂直对齐的12种方式

原文地址 https://juejin.im/post/5a5ca65a6fb9a01ca3254537

> #### 父子元素均使用绝对大小方案

> #### 使用padding实现子元素的垂直居中

```css
#box {
    width: 300px;
    background: #ddd;
    padding: 100px 0;
}
#child {
    width: 200px;
    height: 100px;
    background: orange;
}
```

> #### 子元素使用百分比大小方案

> #### 另外一种使用绝对定位和负外边距进行垂直居中的方式

```css
#box {
    width: 300px;
    height: 300px;
    background: #ddd;
    position: relative;
}
#child {
    width: 50%;
    height: 30%;
    background: orange;
    position: absolute;
    top: 50%;
    margin: -15% 0 0 0;
}

```

> #### 子元素使用绝对大小方案

> #### 使用绝对定位和负外边距对块级元素进行垂直居中

```css
#box {
    width: 300px;
    height: 300px;
    background: #ddd;
    position: relative;
}
#child {
    width: 150px;
    height: 100px;
    background: orange;
    position: absolute;
    top: 50%;
    margin: -50px 0 0 0; 
}
```

> #### 子元素尺寸任意

> #### 使用绝对定位和transform

```css
#box {
    width: 300px;
    height: 300px;
    background: #ddd;
    position: relative;
}
#child {
    background: orange;
    position: absolute;
    top: 50%;
    transform: translate(0, -50%);
}
```

> #### 绝对定位结合margin: auto

```css
#box {
    width: 300px;
    height: 300px;
    background: #ddd;
    position: relative;
}
#child {
    width: 200px;
    height: 100px;
    background: orange;
    position: absolute;
    top: 0;
    bottom: 0;
    margin: auto;
    line-height: 100px;
}
```

> #### 设置第三方基准

```css
#box {
    width: 300px;
    height: 300px;
    background: #ddd;
}
#base {
    height: 50%;
    background: orange;
}
#child {
    height: 100px;
    background: rgba(131, 224, 245, 0.6); 
    margin-top: -50px;
}
```

> #### 使用flex布局

```css
#box {
    width: 300px;
    height: 300px;
    background: #ddd;
    display: flex;
    align-items: center;
}
```

> #### 第二使用flex布局方式

```css
略
```

# 其他

## CSS继承性

CSS哪些属性可以继承哪些不可继承

### 可继承属性

- 字体系列属性
    - font:组合字体
    - font-family:规定元素的字体系列
    - font-weight:设置字体的粗细
    - font-size:设置字体的尺寸
    - font-style:定义字体的风格
    - font-variant:偏大或偏小的字体

- 文本系列属性
    - text-indent:文本缩进
    - text-align:文本水平对刘
    - line-height:行高
    - word-spacing:增加或减少单词间的空白
    - letter-spacing：增加或减少字符间的空白
    - text-transform:控制文本大小写
    - direction:规定文本的书写方向
    - color:文本颜色

- 元素可见性
    - visibility

- 表格布局属性
    - caption-side定位表格标题位置
    - border-collapse合并表格边框
    - border-spacing设置相邻单元格的边框间的距离
    - empty-cells单元格的边框的出现与消失
    - table-layout表格的宽度由什么决定<automatic.fixed.inherit>

- 列表布局属性
    - list-style-type文字前面的小点点样式
    - list-style-position小点点位置
    - list-style以上的属性可通过这属性集合

- 引用
    - quotes设置嵌套引用的引号类型

- 光标属性
    - cursor:箭头可以变成需要的形状

### 不可继承属性

- displey

- 文本属性
    - vertical-align:垂直文本对齐
    - text-decoration:规定添加到文本的装饰
    - text-shadow:文本阴影效果
    - white-space:空白符的处理

- 盒子模型属性
    - width、height、margin 、margin-top、margin-right、margin-bottom、margin-left、border、border-style、border-top-style、border-right-style、border-bottom-style、border-left-style、border-width、border-top-width、border-right-right、border-bottom-width、border-left-width、border-color、border-top-color、border-right-color、border-bottom-color、border-left-color、border-top、border-right、border-bottom、border-left、padding、padding-top、padding-right、padding-bottom、padding-left

- 背景属性
    - background、background-color、background-image、background-repeat、background-position、background-attachment

- 定位属性
    - float、clear、position、top、right、bottom、left、min-width、min-height、max-width、max-height、overflow、clip、z-index

## CSS优先级算法

- 原则
    - 使用就近原则，同权重情况下样式定义最近者为准
    - 载入样式以最后载入的定位为准

- 权重：规则

    - ```
        // 从0开始计算
        // !import > id > class >tag
        <>		// 一个行内样式+1000
        #		// 一个id+100
        . 		// 一个属性选择器/class+10
        :		// 一个伪类+10
        li		// 一个元素名+1
        ::		// 伪元素+1
        ```

- 同权重下：内联样式(标签内部) > 嵌入样式表(当前文件中) > 外部样式表(外部文件中)

# BUG

## calc中符号的两边要空格，及其他注意项

（在加号(“+”)和减号(“-”)两边要留空格，而乘号(“*”)和除号(“/”)没有这个要求）

%不能被除以，只能除以

```css
calc(50% / 3);								// 合法
calc(1000 / 50%);							// 不合法
```

calc中符号的两边要空格，否则不起作用

```css
min-height: calc(100vh-$navbarHeight);		/* 不对，不生效 */
min-height: calc(100vh - $navbarHeight);	/* 正确写法 */
```

calc计算scss属性时要改成

```scss
min-height: calc(100vh - $navbarHeight);	// 不对，不生效
min-height: calc(100vh - #{$navbarHeight});	// 正确写法
```







































