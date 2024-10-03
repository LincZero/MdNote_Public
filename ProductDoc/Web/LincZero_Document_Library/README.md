# LincZero_Document_Library

这是 https://github.com/LincZero/LincZero.github.io 开源项目的在线文档 (这不仅仅只是网站框架，还包含一组工具集：组件/插件/工具的集合)

如果你在网络博客上看到这篇文章，那么对应的网络博客就是这个项目啦。不然的话，可以访问： https://linczero.github.io/

可能也会在其他网站上部署，例如为中国大陆提供访问环境的 https://linczero-github-io.pages.dev/

## 更多文档

由于该部分的绝大部分文档，是面对开发而非面对用户的（开发文档而非用户文档）。

一般我习惯将面对用户的单独抽出来以便展示，而面对开发的文档更多地是放在项目所在的位置，即前面提到的开源地址处。详见对应链接。

等我什么时候有空把网站通用逻辑抽出来，能够方便小白用户快速部署时，那会儿再在此处进行 “用户文档” 的补充。

## 相关技术

- 主要框架：VuePress-Hope-Theme
- 在此基础上，使用VuePress的Alias别名系统替换了多个组件，也自己写了一些相关的插件
- 实现本地编辑与博客预览体验的一致性：
  - Obsidian插件迁移到VuePress，以在VuePress上使用
    - 如 AnyBlock，重写为Markdown-it插件的版本
    - 如 [Markdown-it-obisidian-callout](https://github.com/ebullient/markdown-it-obsidian-callouts) 的修改，替换掉自带的 alert 插件，使其更适应ob语法
  - VuePress插件迁移到Obsidian，以在Obsidian上使用
    - 如 Markdown-it-container 语法，重写为Obsidian插件的版本
  - 其他插件和组建
    - 仿文件资源管理的侧边栏组件
    - 一个钩子组的VuePress插件，用来和 AnyBlock 插件配合
  - 修改了部分样式和逻辑等



