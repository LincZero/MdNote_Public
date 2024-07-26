# README

## 参考资料

- ##### 开发无关

  -   通用资料
      -   [Github开源地址](https://github.com/markdown-it/markdown-it)
      -   [Github文档](https://github.com/markdown-it/markdown-it/tree/master/docs)
      -   中文文档
          - 主页文档：https://markdown-it.docschina.org/
          - 在主页上方还有其他页：[构造](https://markdown-it.docschina.org/architecture.html)、[开发者建议](https://markdown-it.docschina.org/development.html)、[安全](https://markdown-it.docschina.org/security.html)、[DocsChina主页](https://docschina.org/)、[【Github】markdown-it](https://github.com/markdown-it/markdown-it)

  -   使用资料
      -   中文文档：https://markdown-it.docschina.org/

- ##### 插件开发者资料

  - 工具：[Markdown-it 官方演示及调试页面](https://markdown-it.github.io/)

    （注意演示页面的右侧标签栏有 html、source、debug 三个选项，分别是 html展示、html源码、*TokensStream结构*。这能很方便地帮助我们开发）

  - 中文文档：https://markdown-it.docschina.org/

  -   [Github文档](https://github.com/markdown-it/markdown-it/tree/master/docs)，Github里有针对插件开发的文档，该链接包含对插件开发人员有用的信息。如果您仅在应用中使用 `markdown-it` ，请参阅 README 和 API 文档。
      
      -   [解析器架构和设计原则](https://github.com/markdown-it/markdown-it/blob/master/docs/architecture.md)
      -   [插件开发者的一些指南](https://github.com/markdown-it/markdown-it/blob/master/docs/development.md)
      
  - ~~[【知乎】markdown-it 原理解析](https://zhuanlan.zhihu.com/p/4595547650)~~

  -   [【简书】markdown-it解析](https://www.jianshu.com/p/39ed59f610d4)

- ##### 《博客搭建》冴羽

  - 作者主页
    - [GitHub - 作者主页](https://github.com/mqyqingfeng/Blog)，[InfoQ - 作者主页](https://www.infoq.cn/u/yayujs/publish)
    - 最终效果网站：[冴羽的 JavaScript 博客](https://ts.yayujs.com/)
    - 备用链接：例如 [InfoQ - markdown-it 插件如何写（一）](https://xie.infoq.cn/article/16c70bb0f0bfb972d1e5867f6) 或 [markdown-it 插件如何写（一）](https://juejin.cn/post/7055238938092371975) 或 [markdown-it 插件如何写（一）](https://github.com/mqyqingfeng/Blog/issues/253)，这几个的内容是一样的，只是作者在不同的平台发布而已
  - 其中，和markdown-it关联的部分
    - [markdown-it 原理解析](https://github.com/mqyqingfeng/Blog/issues/252)
    - [markdown-it 插件如何写（一）](https://xie.infoq.cn/article/16c70bb0f0bfb972d1e5867f6)
    - [markdown-it 插件如何写（二）](https://xie.infoq.cn/article/7db8be15aa5161a8f36eec348)
    - [markdown-it 插件如何写（三）](https://xie.infoq.cn/article/e36b2ff51c9520688be2581a7)
  - 个人吐槽
    - 话说他这个Github文章居然是写在issue里的，神奇……也许是为了方便使用评论功能吧
    - 注意，有一些文章内部链接跳转到 markdown-it Github 源码并出现404的，需要将末尾的 .js 替换成 .mjs

## 优秀的mdit插件

这里主要列举开源的，以便可以去参考源码和学习

- Github比较高Star的几个：（有专门的主题，可以在 https://github.com/topics/markdown-it-plugin 里看）
  - [markdown-it/markdown-it-emoji](https://github.com/markdown-it/markdown-it-emoji)， 表情符号语法插件markdown-it markdown解析器
  - [waylonflinn/markdown-it-katex](https://github.com/waylonflinn/markdown-it-katex)， 添加数学到您的Markdown与KaTeX插件Markdown-it
  - [markdown-it/markdown-it-container](https://github.com/markdown-it/markdown-it-container)， markdown-it markdown解析器的隔离容器插件
  - [executablebooks/markdown-it-py](https://github.com/executablebooks/markdown-it-py)， Markdown解析器，做得对。100% CommonMark支持，扩展，语法插件和高速。现在在Python中!
  - [valeriangalliat/markdown-it-anchor](https://github.com/valeriangalliat/markdown-it-anchor)， 一个markdown-it插件，为标题和可选的永久链接添加' id '属性。
  - [markdown-it-collapsible](https://github.com/Bioruebe/markdown-it-collapsible)，用 `+++` 标记代替 HTML `<details>` and `<summary>` 来设置可折叠区域
  - [markdown-it-color](https://github.com/nkjmsss/markdown-it-color)，内联颜色
  - [markdown-it-markmap](https://github.com/deiv/markdown-it-markmap)，脑图
  - (个人研究推荐)
    - [markdown-it-multimd-table](https://www.npmjs.com/package/markdown-it-multimd-table)， 扩展表格
    - [markdown-it-link-to-card](https://github.com/luckrya/markdown-it-link-to-card)，将链接转换为卡片
    - [markdown-it-obsidian-callouts](https://github.com/ebullient/markdown-it-obsidian-callouts)，Obsidian的callout语法
- Npmjs比较高分的几个：
  - 略，npm自己搜

- 其他
  - [adam-p/markdown-here](https://github.com/adam-p/markdown-here)， 谷歌Chrome, Firefox和雷鸟扩展，让您在Markdown中编写电子邮件并在发送前渲染它。
  - [hexojs/hexo-renderer-markdown-it](https://github.com/hexojs/hexo-renderer-markdown-it)， Markdown-这是一个Markdown解析器，操作正确。一个更快和CommonMark兼容替代Hexo。

## 优秀的mdit插件 (旧)

### 可参考

#### table-extended

Obsidian插件：[aidenlx/table-extended](https://github.com/aidenlx/table-extended)

里面提到：

> 由于当前黑曜石 API 的限制，内置的 markdown解析器 不可配置。相反，这个插件包括一个独立的 Markdown 解析器 [markdown-it](https://markdown-it.github.io/) 和插件 [markdown-it-multimd-table](https://github.com/RedBug312/markdown-it-multimd-table)，表格部分和带有语言标签 `tx` 的代码块内的文本被传递给 `markdown-it` 。
>
> 然而，内部链接和嵌入被提取并传递给黑曜石，因此黑曜石的核心特征保持不变。
>
> 请注意，该插件的行为可能与官方的 MultiMarkdown 编译器和黑曜石的解析器不同，如果合理的输入出现意外结果，请提出问题。

### 不符合需求

### keep-it-markdown

[djsudduth/keep-it-markdown](https://github.com/djsudduth/keep-it-markdown)

> 使用非官方的Keep API将 **Google Keep笔记动态转换为** 黑曜石，Logseq，Joplin和Concept的markdown。此外，将简单的markdown笔记导入回Google Keep。

#### markdown-it-obsidian-plus

Markdown-it插件：[klequis/markdown-it-obsidian-plus](https://github.com/klequis/markdown-it-obsidian-plus)

>  markdown-it插件将 obsidian markdown 转换为HTML

不过似乎和 Obsidian 没有什么关系

#### markdown-it-obsidian

[alexjv89/markdown-it-obsidian](https://github.com/alexjv89/markdown-it-obsidian)

>  将 Obsidian 的 wiki 链接转化为 markdown链接



































