---
create_time: 2024-07-25
---

# README

## 转载

- 《博客搭建》冴羽
  - 作者主页
    - [GitHub - 作者主页](https://github.com/mqyqingfeng/Blog)，[InfoQ - 作者主页](https://www.infoq.cn/u/yayujs/publish)
    - 最终效果网站：[冴羽的 JavaScript 博客](https://ts.yayujs.com/)
    - 备用链接：例如 [InfoQ - markdown-it 插件如何写（一）](https://xie.infoq.cn/article/16c70bb0f0bfb972d1e5867f6) 或 [markdown-it 插件如何写（一）](https://juejin.cn/post/7055238938092371975) 或 [markdown-it 插件如何写（一）](https://github.com/mqyqingfeng/Blog/issues/253)，这几个的内容是一样的，只是作者在不同的平台发布而已

  - 其中，和vuepress开发关联的部分
    - [13. 从零实现一个 VuePress 插件](https://github.com/mqyqingfeng/Blog/issues/250)
    
    - [21. 搭建 VuePress 博客，你可能会用到的一些插件](https://www.yuque.com/yayu/blog/hc9p2i#)
    
  - 其中，和markdown-it开发关联的部分
    - [15.  markdown-it 原理解析](https://github.com/mqyqingfeng/Blog/issues/252)
    - [16. markdown-it 插件如何写（一）](https://xie.infoq.cn/article/16c70bb0f0bfb972d1e5867f6)
    - [17. markdown-it 插件如何写（二）](https://xie.infoq.cn/article/7db8be15aa5161a8f36eec348)
    - [18. markdown-it 插件如何写（三）](https://xie.infoq.cn/article/e36b2ff51c9520688be2581a7)


## 将每篇文章的头尾声明摘出来

### 前言

在 [《一篇带你用 VuePress + Github Pages 搭建博客》](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Fmqyqingfeng%2FBlog%2Fissues%2F235)中，我们使用 VuePress 搭建了一个博客，最终的效果查看：[TypeScript 中文文档](https://link.juejin.cn?target=http%3A%2F%2Fts.yayujs.com%2F)。（已经上不了了）

在搭建博客的过程中，我们出于实际的需求，在[《VuePress 博客优化之拓展 Markdown 语法》](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Fmqyqingfeng%2FBlog%2Fissues%2F251)中讲解了如何写一个 `markdown-it`插件，又在 [《markdown-it 原理解析》](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Fmqyqingfeng%2FBlog%2Fissues%2F252)中讲解了 `markdown-it`的执行原理，本篇我们将讲解具体的实战代码，帮助大家更好的写插件。

### 系列文章

博客搭建系列是我至今写的唯一一个偏实战的系列教程，预计 20 篇左右，讲解如何使用 VuePress 搭建、优化博客，并部署到 GitHub、Gitee、私有服务器等平台。全系列文章地址：[github.com/mqyqingfeng…](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Fmqyqingfeng%2FBlog)

微信：「mqyqingfeng」，加我进冴羽唯一的读者群。

如果有错误或者不严谨的地方，请务必给予指正，十分感谢。如果喜欢或者有所启发，欢迎 star，对作者也是一种鼓励。



