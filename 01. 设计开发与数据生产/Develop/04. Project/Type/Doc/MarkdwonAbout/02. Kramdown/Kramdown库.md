# kramdown

# 目录

# kramdown

参考

- [官网](https://kramdown.gettalong.org/)
- [官网文档](https://kramdown.gettalong.org/documentation.html)



[官网介绍](https://kramdown.gettalong.org/)

> **kramdown**  （原文如此，不是 Kramdown 或 KramDown，只是 kramdown）
> 是一个 *免费*  [的MIT ](https://github.com/gettalong/kramdown/blob/master/COPYING)许可  [Ruby ](http://www.ruby-lang.org) 用于解析和转换 Markdown 超集的 ==库==。  这是   完全用 Ruby 编写，支持标准的 Markdown（有一些小的修改）和各种   由 [PHP Markdown Extra ](http://michelf.com/projects/php-markdown/extra/)包和 [Maruku ](http://maruku.rubyforge.org)流行的扩展。 
>
> 它可能是可用的最快的纯 Ruby Markdown 转换器（2019 年 1 月），比 [Maruku ](http://maruku.rubyforge.org)快约为 3 倍，比 [BlueFeather ](http://ruby.morphball.net/bluefeather/index_en.html)快 6.2 倍。 



## Kramdown 关键概念

参考：[【简书】Kramdown 关键概念](https://www.jianshu.com/p/8f59420fd866)

kramdown元素分为 **Block-level Elements**（块级元素） 和 **Span-Level Elements**（内联/段落元素）

**Block-level Elements** 包括

- Paragraphs，段落
- Headers，头
- Blockquotes，引用块
- Code Blocks，代码块
- Horizontal Rules
- Lists，列表
- Definition Lists
- Tables，表格
- 其它

**Span-Level Elements** 包括

- Emphasis
- Links and Images，链接和图片
- Inline Code，内联代码
- Footnotes
- Abbreviations



## Kramdown 介绍

### 概述 

kramdown 首先是一个库，用于将以 Markdown 超集编写的文本转换为 HTML。  然而，由于其模块化架构，它能够支持额外的输入和输出 格式。  目前支持以下输入输出格式： 

- 输入： [ kramdown ](https://kramdown.gettalong.org/parser/kramdown.html) （Markdown 的超集），  [ Markdown ](https://kramdown.gettalong.org/parser/markdown.html) , [ Github 风格的 Markdown ](https://kramdown.gettalong.org/parser/gfm.html) , [ HTML ](https://kramdown.gettalong.org/parser/html.html)
- 输出： [ HTML ](https://kramdown.gettalong.org/converter/html.html) , [ LaTeX ](https://kramdown.gettalong.org/converter/latex.html) ,  [ kramdown ](https://kramdown.gettalong.org/converter/kramdown.html) , [ RemoveHtmlTags ](https://kramdown.gettalong.org/converter/remove_html_tags.html) （一个特殊的   移除 HTML 标签的转换器，通常与 LaTeX 或 kramdown 结合使用   转换器） 

kramdown [ syntax page ](https://kramdown.gettalong.org/syntax.html)详细描述了支持的内容和不同之处   来自标准的 Markdown。 

对于所有可用选项，请查看 [选项文档 ](https://kramdown.gettalong.org/options.html)或查看   解析器/转换器页面，查看它们支持哪些选项！ 



### 用法

kramdown 包提供了两种使用方式： 

- **作为图书馆** 

  基本相同的 API [kramdown 使用与RedCloth ](http://redcloth.org/) 、 [ BlueCloth ](http://deveiate.org/projects/BlueCloth)和 [Maruku ](http://maruku.rubyforge.org) ： 

  ```
  require 'kramdown'
  
  puts Kramdown::Document.new(text).to_html
  ```

  的第二个参数 `new`call 是用于（取消）激活某些功能的选项散列。  为了 例如，要禁用自动标头 ID 生成，您可以执行以下操作： 

  ```
  puts Kramdown::Document.new(text, :auto_ids => false).to_html
  ```

  使用的默认解析器是 `kramdown`，但是，您可以使用 `:input` 选项： 

  ```
  puts Kramdown::Document.new(text, :input => 'html').to_latex
  ```

  您还可以重用创建的文档对象来生成多个输出： 

  ```
  doc = Kramdown::Document.new(text, :input => 'html')
  puts doc.to_html
  puts doc.to_latex
  ```

  有关如何使用或扩展 kramdown 的更多信息，请参见 [API    文档 ](https://kramdown.gettalong.org/rdoc/index.html)！ 

- **作为应用** 

  与库文件一起，一个名为 `kramdown`已发货，可用于转换 任何支持的输入格式的文本到任何支持的输出格式。  它要么从文件中读取 指定为命令行参数或来自标准输入。  例如： 

  ```
  kramdown path/to/kramdown/doc/syntax.page
  ```

  通过支持输入和输出格式以及所有可用的 kramdown 选项 命令行开关。 

### 测试 

kramdown 使用各种测试套件来验证解析器和转换器的正确工作。   为了   更多信息，请查看 [测试文档 ](https://kramdown.gettalong.org/tests.html)。 



## 解析器

目前支持以下输入输出格式： 

- 输入： [ kramdown ](https://kramdown.gettalong.org/parser/kramdown.html) （Markdown 的超集），  [ Markdown ](https://kramdown.gettalong.org/parser/markdown.html) , [ Github 风格的 Markdown ](https://kramdown.gettalong.org/parser/gfm.html) , [ HTML ](https://kramdown.gettalong.org/parser/html.html)
- 输出： [ HTML ](https://kramdown.gettalong.org/converter/html.html) , [ LaTeX ](https://kramdown.gettalong.org/converter/latex.html) ,  [ kramdown ](https://kramdown.gettalong.org/converter/kramdown.html) , [ RemoveHtmlTags ](https://kramdown.gettalong.org/converter/remove_html_tags.html) （一个特殊的   移除 HTML 标签的转换器，通常与 LaTeX 或 kramdown 结合使用   转换器） 

### kramdown 解析器 

这是 kramdown 库的主要解析器（顾名思义）。   它解析 kramdown 中的文本   基于 Markdown 的语法，一种非常易于编写、易于阅读的用于编写 HTML 的标记   纯文本文件。   由于基本的 Markdown 语法有一些缺点，实现   （特别是 [PHP Markdown Extra ](http://michelf.com/projects/php-markdown/extra/)包）试图克服这个缺点   额外的语法。   kramdown 解析器支持原始 Markdown 语法的所有特性（尽管   有一些小的更正）以及 [PHP Markdown Extra ](http://michelf.com/projects/php-markdown/extra/)中实现的新功能  包和 [丸子 ](http://maruku.rubyforge.org)。 



### GFM 解析器

这个解析器在 kramdown 2.0 之前是内置的，从那时起就可以通过 [`kramdown-parser-gfm` gem ](https://github.com/kramdown/parser-gfm)。 

它可以解析 [“Github Flavored    降价” ](https://help.github.com/articles/github-flavored-markdown) 。   这是Markdown的一种格式   在 Github.com 上用于大多数需要文本输入的地方，例如问题和   注释。   一些扩展，特别是“反引号围栏代码块”也用于其他   站点，例如 StackOverflow。 

有关文档，请参阅 [https://github.com/kramdown/parser-gfm ](https://github.com/kramdown/parser-gfm) ！ 



### Markdwon 解析器 

此解析器解析 [Markdown ](http://daringfireball.net/projects/markdown/)格式的文本。   它基于 [kramdown 解析器 ](https://kramdown.gettalong.org/parser/kramdown.html)  并且只是删除了解析 kramdown 语法的附加标记的功能   支持。   由于 kramdown 解析器处理某些事情的方式不同（比如决定何时   列表项只包含文本），这个解析器在一些小的方面与真正的 Markdown 解析器不同   尊重。 

但是请注意，解析器基本上只失败了一个 Markdown 测试用例（其他一些也 失败，但这些失败可以忽略不计）。 



### HTML 解析器 

此解析器假定输入文档是 HTML 文档。  它会自动转换 HTML 标签 对它们的原生表示具有原生元素表示——所有其他标签也是如此 作为处理指令和 HTML 注释按原样解析。 

 

## 转化器

### HTML 转换器 

介绍 

此转换器将 **kramdown 元素树转换为 HTML 片段**并支持所有可用的 元素类型。  下面列出了 HTML 转换器的附加功能以及一些 附加信息。 



### LaTeX 转化器

此转换器将 kramdown 元素树转换为 LaTeX。  它支持所有可用的元素类型 除了 HTML 特定的。  例如，LaTeX 文档可以进一步转换为 PDF 文件以生成高质量的可打印版本。 

由于 LaTeX 转换器仅输出转换后的元素树而不是整个 LaTeX 文档 默认情况下，应该始终使用 `template`选项（见下文）以包括必要的   “框架”。   还有一些 [其他选项 ](https://kramdown.gettalong.org/converter/latex.html#options)可用于自定义   生成 LaTeX 输出。 



### 手册页 转化器（Man Page Converter）

该转换器采用 kramdown 文档并将其转换为 groff 格式的 [手册页 ](http://man7.org/linux/man-pages/man7/man-pages.7.html)。   一些   不支持像图像这样的元素，因为 groff 不支持它们。 



### kramdown 转化器 

此转换器将 kramdown 元素树转换为 kramdown 文档并支持所有可用的   元素类型。   此转换器与 [HTML 解析器 ](https://kramdown.gettalong.org/parser/html.html)一起可用于   将 HTML 文档转换为 kramdown 文档。 

另一种用途是格式化样式错误的 kramdown 文档（即带有换行的文档， 一个列表中使用了多个不同的缩进，……）。 



### 删除HTML标签 转化器

此转换器修改 kramdown 元素树并有条件地删除所有块和/或跨 HTML 元素、XML 处理指令和 `style`也 `script`从它的标签。   所结果的   元素树在大多数情况下应该只包含“原生”kramdown 元素，因此更好   适用于不输出 HTML 的转换器（如 [kramdown 转换器 ](https://kramdown.gettalong.org/converter/kramdown.html)或  [ Latex转换器 ](https://kramdown.gettalong.org/converter/latex.html)）。 



## 语法高亮

### Rouge 语法高亮

[Rouge ](https://github.com/jneen/rouge) （麻省理工学院许可）是一种快速的语法高亮器，它是   与为 Pygments 设计的样式表兼容。 

要使用 Rouge，请将选项 [“syntax_highlighter” ](https://kramdown.gettalong.org/options.html#option-syntax-highlighter)设置为   'rouge' 并确保 Rouge 可用。   可以安装 Rouge 库，例如，通过   通过运行 Rubygems `gem install rouge`. 



### 使用 Coderay 进行语法高亮

这个语法高亮器在 kramdown 2.0 之前是内置的，从那时起可以通过 [`kramdown-syntax-coderay`宝石 ](https://github.com/kramdown/syntax-coderay)。 

[Coderay ](http://coderay.rubychan.de) （麻省理工学院许可）可用作代码的语法高亮器   转换为 HTML 时的块和代码跨度。 

有关文档，请参阅 [https://github.com/kramdown/syntax-coderay ](https://github.com/kramdown/syntax-coderay) ！ 



## 数学引擎

### MathJax 

[MathJax ](http://www.mathjax.org)是一个 javascript 库，它使用 TeX 算法和字体来显示数学公式   HTML 页面。   它允许非常细粒度的配置，被广泛使用并适用于所有现代   浏览器。 

该引擎使用标准的 MathJax 语法标记数学公式 `\(...\)`对于内联数学和 `\[...\]`用于块数学（适用于 MathJax 的 2.x 和 3.x 版本）。  唯一要做的另一件事 是在 HTML 页面上包含 MathJax 库本身。 

请注意，kramdown 不 *随* MathJax 库一起提供，因此“默认”   模板不 *包含* 指向它的链接！   这  [ MathJax 文档 ](http://docs.mathjax.org/en/latest/start.html)描述了如何添加链接   到 MathJax 到你的页面



### KaTeX

这个数学引擎在 kramdown 2.0 之前是内置的，从那时起可以通过 [`kramdown-math-katex`宝石 ](https://github.com/kramdown/math-katex)。 

该引擎 [使用KaTeX ](https://khan.github.io/KaTeX/)通过 [katex rubygem ](https://github.com/glebm/katex-ruby)将 TeX 数学公式转换为 KaTeX   HTML，在底层使用 ExecJS。   这消除了对客户端数学渲染的需要   Javascript。   这个引擎有点类似于 [SsKaTeX ](https://kramdown.gettalong.org/math_engine/sskatex.html)数学引擎，但是更简单   使用并适合来自不受信任用户的 kramdown 输入。 



### SsKaTeX 

这个数学引擎在 kramdown 2.0 之前是内置的，从那时起可以通过 [`kramdown-math-sskatex`宝石 ](https://github.com/kramdown/math-sskatex)。 

的服务器端安装 [这个数学引擎使用KaTeX ](https://khan.github.io/KaTeX/)来   将 TeX 数学公式转换为 HTML+MathML。   这消除了对客户端数学渲染的需要   Javascript。 的一种灵活的仅供受信用户使用的替代方案 [  将其视为 KaTeX 数学    引擎 ](https://kramdown.gettalong.org/math_engine/katex.html)的轻量级高效替代品 [和Mathjax-Node ](https://kramdown.gettalong.org/math_engine/mathjaxnode.html)。 

有关文档，请参阅 [https://github.com/kramdown/math-sskatex ](https://github.com/kramdown/math-sskatex) ！ 



### Mathjax-Node 

这个数学引擎在 kramdown 2.0 之前是内置的，从那时起可以通过 [`kramdown-math-mathjaxnode`宝石 ](https://github.com/kramdown/math-mathjaxnode)。 

[Mathjax-Node ](https://github.com/mathjax/MathJax-node)将 TeX 数学公式转换为 MathML 和   可以与 [HTML 转换器 ](https://kramdown.gettalong.org/converter/html.html)一起使用。 

有关文档，请参阅 [https://github.com/kramdown/math-mathjaxnode ](https://github.com/kramdown/math-mathjaxnode) ！ 



### Ritex 

这个数学引擎在 kramdown 2.0 之前是内置的，从那时起可以通过 [`kramdown-math-ritex`宝石 ](https://github.com/kramdown/math-ritex)。 

Ritex 将 TeX 数学公式转换为 MathML 并可与 [HTML 一起使用   转换器 ](https://kramdown.gettalong.org/converter/html.html)。 

有关文档，请参阅 [https://github.com/kramdown/math-ritex ](https://github.com/kramdown/math-ritex) ！ 



### itex2MML 

这个数学引擎在 kramdown 2.0 之前是内置的，从那时起可以通过 [`kramdown-math-itex2mml`宝石 ](https://github.com/kramdown/math-itex2mml)。 

[itex2MML ](https://golem.ph.utexas.edu/~distler/blog/itex2MML.html)将 TeX 数学公式转换为  可以一起使用 [ MathML 和HTML 转换器 ](https://kramdown.gettalong.org/converter/html.html)。 

有关文档，请参阅 [https://github.com/kramdown/math-itex2mml ](https://github.com/kramdown/math-itex2mml) ！ 











