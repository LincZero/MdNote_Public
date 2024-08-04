# Markdown-it 插件开发

参考：[插件开发者的一些指南](https://github.com/markdown-it/markdown-it/blob/master/docs/development.md)


在继续之前，请确保您已阅读：

-   [README](https://github.com/markdown-it/markdown-it#markdown-it)
-   [API文档](https://markdown-it.github.io/markdown-it/)
-   [架构说明](https://github.com/markdown-it/markdown-it/blob/master/docs/architecture.md)

## 插件的一般注意事项

1. 尝试为您的插件规则找到正确的位置：

   - 
     它会与现有标记（按优先级）冲突吗？
     - 如果是 - 您需要编写 inline or block rule
     - 如果没有 - 您可以改变 core chains 的 Tokens

   - 请记住，如果您不复制现有规则，那么
     - 核心链中的令牌变形总是比编写块或内联规则更简单
     - 然而，块规则和内联规则通常更快。

   - 有时，仅修改渲染器就足够了。例如，为链接添加标头 ID 或 `target="_blank"` 。

   - 插件不应要求 `markdown-it` 包作为 `package.json` 中的依赖项。如果您需要访问内部结构，可以通过解析器实例获取这些内部结构，并在插件加载时传递。查看主类和嵌套对象的属性。

2. 搜索现有  [插件](https://www.npmjs.org/browse/keyword/markdown-it-plugin) 或 [规则](https://github.com/markdown-it/markdown-it/tree/master/lib)，执行类似的操作。修改现有代码可以更简单，而不是从头开始编写。

3. 如果您已完成上述所有步骤，但仍有疑问 - 在跟踪器中提问。但是请注意：

   - 请明确点。不接受 “如何做插件” 和 “如何学习编程” 之类的通用问题。
   - 不要要求我们违反  [CommonMark](http://commonmark.org/) 规范。此类事情应该首先在 [CommonMark forum](http://talk.commonmark.org/) 上讨论。

## NPM 包的注释

为了简化搜索：

- 为插件添加 `package.json` 关键字 `markdown-it` 和 `markdown-it-plugin` 。
- 为任何其他相关包添加关键字 `markdown-it` 。

## FAQ

### 我需要异步规则，该怎么做？

对不起。你不能直接这样做。所有复杂的解析器本质上都是同步的。但您可以使用解决方法：

1. 在解析阶段，用随机数替换内容并将其存储在 `env` 中。
2. 对收集的数据进行异步处理。
3. 渲染内容并用文本替换这些随机数字；或者先替换，然后渲染。

或者，您可以渲染 HTML，然后将其解析为 DOM 或 [cheerio](https://github.com/cheeriojs/cheerio) AST，并以更方便的方式应用转换。

### 如何用链接替换部分文本标记？

正确的顺序是将文本拆分为多个标记并在其间添加链接标记。结果将是： `text` + `link_open` + `text` + `link_close` + `text` 。

请参阅  [linkify](https://github.com/markdown-it/markdown-it/blob/master/lib/rules_core/linkify.js) 和 [emoji](https://github.com/markdown-it/markdown-it-emoji/blob/master/lib/replace.js) 的实现 - 它们进行文本标记分割。

笔记：不要尝试用 HTML 标记替换文本！那不安全。

### 为什么我的内联规则没有执行？

内联解析器会跳过文本片段以优化速度。它仅在 [一小部分字符](https://github.com/markdown-it/markdown-it/blob/master/lib/rules_inline/text.js) 上停止，这些字符可以是标记。出于性能原因，我们也没有使该列表可扩展。

如果您绝对确定那里缺少一些重要的东西 - 创建一个票证，我们将考虑将其添加为新的字符代码。

### 为什么你会拒绝一些有用的东西？

我们做了一个 Markdown 解析器。它应该保持“markdown精神”。其他东西应该分开保存，例如在插件中。抱歉，我们没有明确的标准。也许，您会发现 [CommonMark forum](http://talk.commonmark.org/) 是一本有用的读物，可以更好地了解我们。

当然，如果您发现此解析器的体系结构对其他类型的标记感兴趣，欢迎您在另一个项目中重用它。

















