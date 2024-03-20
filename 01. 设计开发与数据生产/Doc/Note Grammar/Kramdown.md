# kramdown

# 目录

官网文档：https://kramdown.gettalong.org/quickref.html

# kramdown基本语法

## kramdown基本语法

参考：[【知乎】kramdown基本语法](https://zhuanlan.zhihu.com/p/60838339)

### atx 风格标题  {#header}

```markdown
~~~
#         一级
##
###
####
#####
######    六级
~~~
```

### 指定标头ID（`{#head_id}`） 

```markdown
~~~

###### I can help you  {#head_1}

HTML 内代码：
<h6 id="head_1">I can help you</h6>
~~~
```

### 引用  \{#Blockquotes}

```markdown
~~~
> 引用文本
~~~

#### kramdown中 | 会被渲染，需要转义

> 引用文本\|单行

> 使用 `<br>` or 两个空格可  
> 以换行
```

### 空行 {# blank_line}

```markdown
`<br>` or 两个空格
```

### Code  {#code}

```markdown
~~~
# Code
~~~

> 若Code内含有 "~" 符号，则只需要将 三个 **启动符号 "~"** 号多写几个就可以：
```

### 清单 {#Definition_Lists}

```markdown
~~~
* kram
+ down
- now

1. kram
2. down
3. now
~~~

> 注意缩进
```

### 表格  {#Tables}

```markdown
~~~
| Header One     | Header Two     |
| :------------- | :------------- |
| Item One       | Item Two       |
~~~
```

### 分割线  {#Horizontal_Rules}

```markdown
~~~
* * *

---

  _  _  _  _

---------------
~~~
```

### HTML块  {#html_blocks}

```markdown
> 如果HTML标记具有属性markdown="0"，则标记将被解析为原始HTML块。  
> 如果HTML标记具有属性markdown="1"，则使用此标记中用于解析语法的默认机制。  
> 如果HTML标记具有属性markdown="block"，则标记的内容将被解析为块级元素。  
> 如果HTML标记具有属性markdown="span"，则标记的内容将被解析为span级别元素

~~~ html
script style math option textarea pre code kbd samp var
~~~

> 解析为原始 HTML

~~~ html
applet button blockquote body colgroup dd div dl fieldset form iframe li
map noscript object ol table tbody thead tfoot tr td ul
~~~

> 解析为块级元素

~~~ html
a abbr acronym address b bdo big cite caption code del dfn dt em
h1 h2 h3 h4 h5 h6 i ins kbd label legend optgroup p pre q rb rbc
rp rt rtc ruby samp select small span strong sub sup th tt var
~~~

> 解析为 span 级元素

~~~ html
<div markdown="1">This is the first part of a para,
which is continued here.
</div>
~~~
```

### 链接和图像  {#link_img} （含扩展语法）

```markdown
~~~
# 自动链接(尖括号)
<me.example@example.com>

# 内联链接
[link](http://xxx.com)


# 图片
![img](http://xxx/1.img)

# 由于可以通过span和块IAL添加其他属性，因此可以指定图像宽度和高度
![smiley](http://xxx/1.img){:height="36px" width="36px"}
~~~
```

Typora、Obsidian不支持样式，要用img标签

### 重点  {#Emphasis}

```markdown
~~~
*some text*
_some text_
**some text**
__some text__
~~~

# kramdown中单个 * 会被渲染，需要转义 \*
```

### 单行代码  {#line_code}（含扩展语法）

```python
~~~
`code`
~~~

~~~
# 与代码块一样，可以使用IAL设置代码范围的语言

This is a Ruby code fragment `x = Class.new`{:.language-ruby}

`import re`{:.language-python}
~~~
```

### 脚注  {#Footnotes}

```text
~~~
人有悲欢离合，月有阴晴圆缺.[^1]

[^1]: 《水调歌头》
~~~
```

### 缩略语  {#Abbreviations} （含扩展语法）

```text
~~~
*[another language]: It's called Markdown

*[WTF]: What the fuck
~~~
```

Typora、Obsidian不支持

### 属性定义

#### 属性列表定义（ALD）  {#Attribute-List-Definitions}（扩展语法）

```markdown
> 用于向块和 span级元素添加属性

~~~
# 例子:
{:ref-name: #myid .my-class}
{:other: ref-name #id-of-other title="hallo you"}
{:test: key="value \" with quote" and other='quote brace \}'}
~~~

~~~
# ALD行具有以下结构：

左括号，可选前面最多三个空格，
然后是冒号，引用名称和另一个冒号，
然后是属性定义（允许的字符是反斜杠转义关闭括号或除了未转义的右括号之外的任何字符），
然后是一个右括号和可选空格，直到行尾
~~~

> 引用名称需要以单词字符或数字开头，可选地后跟其他单词字符，数字或短划线  
> 有四种不同类型的属性定义，必须用一个或多个空格分隔

> 如果不存在具有此引用名称的属性定义列表，则在收集属性时将忽略引用名称

~~~
# 以下ALD都是等效的：

{:id: .cls1 .cls2}
{:id: class="cls1" .cls2}
{:id: class="something" class="cls1" .cls2}
{:id: class="cls1 cls2"}
~~~
```

#### 内联属性列表（IAL）  {#Inline-Attribute-Lists} （扩展语法）

```markdown
> 此块级元素用于将属性附加到另一个块级元素  
> 块内联属性列表（块IAL）具有与ALD相同的结构

> 块IAL（或两个或多个块IAL）必须直接放在属性应附加到的块级元素之前或之后。  
> 如果块IAL直接在块级元素之后和之前，则将其应用于前一元素。在所有其他情况  
> 下，块IAL被忽略，例如，当块IAL被空行包围时

> 在引用的ALD中，IAL的键值对 **优先于同名的键值对**


~~~
# 以下是块IAL的一些示例：

A simple paragraph with an ID attribute.
{: #para-one}

> A blockquote with a title
{:title="The blockquote title"}
{: #myid}

{:.ruby}
    Some code here
~~~
```

#### Span 内联属性列表  {#span_ial}

```markdown
> span 级元素的块内联属性列表的一个版本

> 它具有与块IAL相同的结构，除了不允许前导和尾随空格  
> 跨度IAL（或两个或更多跨度IAL）必须直接放在应该应  
> 用它的span-level元素之后，之间不允许有其他字符，否则它将被忽略并仅从输出中删除


~~~
This *is*{:.underline} some `code`{:#id}{:.class}.
A [link](test.html){:rel='something'} and some **tools**{:.tools}.
~~~
```

### 扩展  {#Extensions}

```markdown
> 扩展提供了其他功能，但使用相同的语法。它们既可以作为块也可以作为跨度级元素使用   
>扩展的语法与ALD的语法非常相似

~~~
# 示例

{::comment}
This text is completely ignored by kramdown - a comment in the text.
{:/comment}

Do you see {::comment}this text{:/comment}?
{::comment}some other comment{:/}

{::options key="val" /}
~~~

- 一个左大括号，
- 接着是两个冒号和扩展名，
- 可选地后跟空格和属性定义（允许的字符是反斜杠转义关闭括号或除了未转义的右括号之外的任何字符|同ALD
- 然后是斜线和右大括号（如果扩展没有正文）或只有右大括号（如果扩展有正文）

~~~
# kramdown可以使用以下扩展名：

comment
将正文文本视为未在输出中显示的注释

nomarkdown
不要使用kramdown处理主体，而是按原样输出。该属性type指定哪些转换器应输出正文：如果缺少该属性，则所有转换器都应输出该属性。否则，属性值必须是以空格分隔的转换器名称列表，并且这些转换器应输出正文。

options
由于正文被忽略，应该在没有正文的情况下使用。用于设置kramdown处理器的全局选项（例如，禁用自动标头ID生成）。请注意，解析器使用的选项立即生效，而所有其他选项都不是！这意味着，例如，不能仅为kramdown文档的某些部分设置转换器选项
~~~
```

