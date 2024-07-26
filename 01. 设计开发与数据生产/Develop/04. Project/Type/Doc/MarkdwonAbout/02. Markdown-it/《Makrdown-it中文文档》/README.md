# Markdown-it 介绍

## 资料

-   通用资料
    -   [Github开源地址](https://github.com/markdown-it/markdown-it)
    -   [Github文档](https://github.com/markdown-it/markdown-it/tree/master/docs)
    -   中文文档
        - 主页文档：https://markdown-it.docschina.org/
        - 在主页上方还有其他页：[构造](https://markdown-it.docschina.org/architecture.html)、[开发者建议](https://markdown-it.docschina.org/development.html)、[安全](https://markdown-it.docschina.org/security.html)、[DocsChina主页](https://docschina.org/)、[【Github】markdown-it](https://github.com/markdown-it/markdown-it)
-   使用资料
    -   中文文档：https://markdown-it.docschina.org/
-   插件开发者资料：
    -   中文文档：https://markdown-it.docschina.org/
    -   [Github文档](https://github.com/markdown-it/markdown-it/tree/master/docs)，Github里有针对插件开发的文档，该链接包含对插件开发人员有用的信息。如果您仅在应用中使用 `markdown-it` ，请参阅 README 和 API 文档。
        -   [解析器架构和设计原则](https://github.com/markdown-it/markdown-it/blob/master/docs/architecture.md)
        -   [插件开发者的一些指南](https://github.com/markdown-it/markdown-it/blob/master/docs/development.md)
    -   ~~[【知乎】markdown-it 原理解析](https://zhuanlan.zhihu.com/p/4595547650)~~
    -   [【简书】markdown-it解析](https://www.jianshu.com/p/39ed59f610d4)

## 插件系统

markdown-it 只做纯粹的 markdown 解析，但我们们可以通过提供插件来实现不同的功能。通过 `MarkdownIt.use` 便可以将指定的插件加载到当前的解析器实例中：

```js
var md = require('markdown-it')()
            .use(require('markdown-it-container'), name [, options]);
```

## 架构图

![webp](README.assets/webp.webp)









