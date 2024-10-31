## 选择

GPT4

---

比较这些md渲染库的优缺点：（允许补充） markdown-it、marked、remarkable、showdown、kramdown、codemirror

从性能、易用性、社区环境、与vue的匹配性、是否开源（开源地址，star数，开源地址）等

---

-   markdown-it 

    -   性能：性能不错，适用于很多场景。 

    -   易用性：易用性强，通过插件可以轻松实现符合markdown风格的排版。 

    -   社区环境：社区活跃

    -   与Vue的匹配性：可以与Vue结合工作，也可以找到第三方库（例如vue-markdown-it）进行快速集成。 

    -   是否开源：是的。开源地址：https://github.com/markdown-it/markdown-it，4.1k星（截至2021年10月）17.7k（230705）

-   marked 

    -   性能：性能很好。 

    -   易用性：易用性强，可以快速将Markdown解析成HTML。 

    -   社区环境：社区活跃

    -   与Vue的匹配性：可以与Vue结合工作。 

    -   是否开源：是的。开源地址：https://github.com/markedjs/marked ，8.5k星（截至2021年10月） 30.0k（230705）

-   remarkable 

    -   性能：性能良好。 

    -   易用性：易用性一般，配置稍显复杂。 

    -   社区环境：社区较为活跃

    -   与Vue的匹配性：可以与Vue结合工作。 

    -   是否开源：是的。开源地址：https://github.com/jonschlinkert/remarkable，2.4k星（截至2021年10月） 

-   showdown 

    -   性能：性能良好。 

    -   易用性：易用，支持自定义扩展添加功能。 

    -   社区环境：社区较为活跃

    -   与Vue的匹配性：可以与Vue结合工作。 

    -   是否开源：是的。开源地址：https://github.com/showdownjs/showdown，3.4k星（截至2021年10月） 

-   kramdown 

    -   性能：性能良好。 

    -   易用性：易用性高，配置简单。 

    -   社区环境：kramdown主要用于Ruby环境，所以社区环境以Ruby社区为主。 

    -   与Vue的匹配性：与Vue的集成可能不尽如人意，因为它主要服务于Ruby系统。 

    -   是否开源：是的。开源地址：https://github.com/gettalong/kramdown，944星（截至2021年10月） 

-   CodeMirror 

    -   性能：性能优异。 

    -   易用性：易用性较好，通过事件和API可以实现很多功能。 

    -   社区环境：社区活跃。 

    -   与Vue的匹配性：CodeMirror更侧重于为Markdown编辑器提供底层支持，有第三方的vue-codemirror组件。 

    -   是否开源：是的。开源地址：https://github.com/codemirror/CodeMirror，9.1k星（截至2021年10月） 

综上所述，根据项目需求和喜好，您可以选择合适的Markdown渲染库。

---

在markdown-it和marked里选，去除其他选择。现在需要深度对比这两者。

-   他们是哪公司还是个人研发的（背景实力）？
-   所使用到的核心技术或原理对比（我记得Kramdown还是markdown-it的渲染是先弄成一个什么tokens列表来着）？ 
-   是否能像vuepress那样支持一些md转html的特殊语法解析的插件？ 
-   有哪些耳熟能详的产品使用了他们（obsidian typora vue-press这些使用的是哪个解析器）？ 
-   以及其他有利于我在他们之间进行选择的比较项

---

markdown-it和marked都是强大的Markdown渲染库，以下是它们的深度对比：

-   背景实力

    -   markdown-it：markdown-it是由Vitaly Puzrin和Alex Kocharin编写的。他们是开发人员和开源环保工作者，有很多其他开源库在GitHub的贡献。项目成立于2014年，现已成为一个大型的开放项目。 

    -   marked：marked是开源项目，由Christopher Jeffrey创立。项目始于2011年，已发展为一个相当知名的开源项目。 

-   核心技术和原理

    -   markdown-it：支持CommonMark和GitHub Flavored  Markdown(GFM)规范。markdown-it使用递归下降解析器将纯文本格式的Markdown文件解析为tokens，并以此生成HTML代码。可以使用不同的插件和选项来处理块级(token)和行级(token)元素。 

    -   marked：支持GitHub Flavored Markdown(GFM)。它也是基于词法分析的原理工作的，将输入字符串分割为tokens，然后将tokens转换为HTML标签。marked通过设置不同的选项来控制输出格式。 

-   插件支持

    -   markdown-it：有丰富的插件 ecosystem，可以通过插件支持各种非标准的Markdown语法和语言特性，例如表格、主题、语法高亮等。这使它能够很好地支持vuepress等静态网站生成器。 

    -   marked：虽然不如markdown-it插件生态丰富，但仍然提供了扩展功能以支持自定义解析规则。可以通过相应选项设置对特殊语法进行处理。 

-   知名产品使用

    -   markdown-it：Zettlr，StackEdit 等项目使用了 markdown-it 作为 markdown 解析器。 

    -   marked：VuePress 使用 marked 作为默认的 Markdown 解析器。 

-   定制性
    -   markdown-it提供了多种可选的插件和设置，可以根据项目的需求进行定制
    -   marked也具有一定的定制能力，但相对较弱

-   社区支持和活跃度
    -   marked在GitHub上有8.5k星
    -   而markdown-it有4.1k星。在某种程度上，这反映了它们在社区中的受欢迎程度和支持程度

总之，markdown-it和marked之间的选择取决于您的具体需求，例如插件生态、定制程度以及与其他系统集成。

-   markdown-it更适合需要大量插件和定制功能的项目
-   marked则更注重简单性和速度。

---

性能差距大概有多少？vuepress我记得是支持很多插件的，我还以为是用md-it。那obsidian和typora用的什么，只知道有使用CodeMirror，但应该不完全是CM

---

性能方面，根据一些社区中提供的基准测试，marked的性能略优于markdown-it。但这两者之间的性能差距并不显著，具体取决于用例和实际项目需求。在大多数情况下，二者的性能差异对于正常使用的用户来说并不明显。

对于VuePress，您是对的。实际上，VuePress支持插件功能，并且允许用户根据需要替换默认的Markdown解析器。
VuePress使用了markdown-it作为默认的解析器。对我的误导表示歉意。

至于Obsidian和Typora，它们采用了以下技术：

-   Obsidian：使用CodeMirror作为其底层Editor核心。Markdown渲染技术则是闭源的，使用了一个名为 “mdviewer” 的内部库，具体实现细节不详。 
-   Typora：它不仅使用了CodeMirror作为文本编辑部分的底层技术，还使用了一个名为 “Pandoc” 的开源Markdown转换器来实现Markdown渲染和导出功能。 

总之，Markdown库的选择因项目需求而异。如果你需要插件丰富、高度定制化的解析器，可以选择markdown-it。如果你对性能有更高的要求，可以考虑使用marked。在实际应用中，这两个库都可以满足大多数需求。

---

其他：vditor  monaco-editor

## 使用



































