# README

内容来自官网文档：

参考：

- [VuePress v2 官网](https://v2.vuepress.vuejs.org/zh/)
  -   插件
      -   [插件使用](https://v2.vuepress.vuejs.org/zh/guide/plugin.html)

      -   [插件开发](https://v2.vuepress.vuejs.org/zh/advanced/plugin.html)

      -   [插件API](https://v2.vuepress.vuejs.org/zh/reference/plugin-api.html)

  -   主题
      -   [主题使用](https://v2.vuepress.vuejs.org/zh/guide/theme.html)
      -   [主题开发](https://v2.vuepress.vuejs.org/zh/advanced/theme.html)
      -   [主题API](https://v2.vuepress.vuejs.org/zh/reference/theme-api.html)
  -   [API](https://v2.vuepress.vuejs.org/zh/reference/plugin-api.html)
      -   [插件API](https://v2.vuepress.vuejs.org/zh/reference/plugin-api.html)
      -   [主题API](https://v2.vuepress.vuejs.org/zh/reference/theme-api.html)
      -   [客户端API](https://v2.vuepress.vuejs.org/zh/reference/client-api.html)
      -   [NodeAPI](https://v2.vuepress.vuejs.org/zh/reference/node-api.html)

## 使用

除了VuePress插件，还可以开发和应用Markdown-it插件。关于Markdown-it的开发和使用不在此处，详见 [Markdwon-it](../../../02. Parse and Render/Markdwon-it)

参考：

- 官网插件开发介绍：https://v2.vuepress.vuejs.org/zh/advanced/plugin.html
- 插件API：https://v2.vuepress.vuejs.org/zh/reference/plugin-api.html
  - 其中，插件API > 开发Hooks > extendsMarkdown 这里可以扩展 Markdown-it 插件
  - 其中， Alias 的介绍也在这里……毕竟Alias替换成自定义组件的行为也可以认为是一种插件
- 另外，还有几篇我放错了，放在了 [[../../../../02. Parse and Render/Markdown-it/《博客搭建》冴羽]] 里了

注意：

- Markdown-it插件其实是一种特殊的VuePress插件
- 主题也其实是一种特殊的VuePress插件

## 使用实例

见：https://ecosystem.vuejs.press/zh/plugins/features/copy-code.html

注意一般这种是自带的，应该关了自带的后再来尝试。例如封装度比较高的 vuepress-theme-hope 中：

```ts
plugins: {
    copyCode: false,
}
```

## 插件 API

### 概览

插件需要在初始化之前使用

> #### 按架构分类

（查看 [深入 > 架构 > 核心流程与 Hooks](https://vuepress.github.io/zh/advanced/architecture.html#核心流程与-hooks) 来更好地理解该流程）

- 基础配置项，会在使用插件时立即被处理：

  - [name](https://vuepress.github.io/zh/reference/plugin-api.html#name)， 插件的名称

  - [multiple](https://vuepress.github.io/zh/reference/plugin-api.html#multiple)， 插件是否能够被多次使用

- 下列 Hooks 会在初始化 App 时处理：

  - [extendsMarkdownOptions](https://vuepress.github.io/zh/reference/plugin-api.html#extendsmarkdownoptions)

  - [extendsMarkdown](https://vuepress.github.io/zh/reference/plugin-api.html#extendsmarkdown)

  - [extendsPageOptions](https://vuepress.github.io/zh/reference/plugin-api.html#extendspageoptions)

  - [extendsPage](https://vuepress.github.io/zh/reference/plugin-api.html#extendspage)

  - [onInitialized](https://vuepress.github.io/zh/reference/plugin-api.html#oninitialized)

- 下列 Hooks 会在准备文件时处理：

  - [clientConfigFile](https://vuepress.github.io/zh/reference/plugin-api.html#clientconfigfile)， 配置文件路径。接收文件绝对路径，或者一个返回路径的函数

  - [onPrepared](https://vuepress.github.io/zh/reference/plugin-api.html#onprepared)

- 下列 Hooks 会在 dev / build 时处理：

  - [extendsBundlerOptions](https://vuepress.github.io/zh/reference/plugin-api.html#extendsbundleroptions)

  - [alias](https://vuepress.github.io/zh/reference/plugin-api.html#alias)， 定义路径别名

  - [define](https://vuepress.github.io/zh/reference/plugin-api.html#define)， 定义全局常量

  - [onWatched](https://vuepress.github.io/zh/reference/plugin-api.html#onwatched)

  - [onGenerated](https://vuepress.github.io/zh/reference/plugin-api.html#ongenerated)


> #### 按其他分类

- 基础配置项

  - [name](https://vuepress.github.io/zh/reference/plugin-api.html#name)

  - [multiple](https://vuepress.github.io/zh/reference/plugin-api.html#multiple)

- 开发 Hooks

  - alias
  - clientConfigFile
  - define
  - extendsBundlerOptions
  - extendsMarkdownOptions
  - extendsMarkdown
  - extendsPageOptions
  - extendsPage

- 生命周期 Hooks

  - onInitialized
  - onPrepared
  - onWatched
  - onGenerated

## 插件 API - 从v1迁移，旧教程问题

> 注意，很多旧教程的API是过时的，这让我早期踩了点坑。详见：
>
> https://v2.vuepress.vuejs.org/zh/guide/migration.html#%E6%8F%92%E4%BB%B6-api-%E5%8F%98%E6%9B%B4

### 给用户

（一些配置变更）

### 给插件作者、插件API变更

一些主要的 Breaking Changes ：

- 你不能再在你的插件中使用其他插件了，这避免了很多由于插件嵌套引发的问题。如果你的插件依赖于别的插件，你可以在文档中列出他们，并让用户手动引入。或者，你也可以向用户提供一个插件数组以方便使用。
- 大部分 v1 Hook 都在 v2 中存在等效的 Hook 或实现方式。唯一的例外是 `extendsCli` ，它被移除了。
- Webpack 相关的 Hook 都被移除了，因为 VuePress Core 已经和 Webpack 解耦了。你可以尝试使用 [extendsBundlerOptions](https://v2.vuepress.vuejs.org/zh/reference/plugin-api.html#extendsbundleroptions) Hook 来进行相似的操作，但要注意应适配所有不同的打包工具。

你可以参考 [深入 > 开发插件](https://v2.vuepress.vuejs.org/zh/advanced/plugin.html) 来了解如何开发一个 v2 插件。

插件 API 变更

- `plugins`：移除
- `ready`：重命名为 `onPrepared`
- `updated`：重命名为 `onWatched`
- `generated`：重命名为 `onGenerated`
- `additionalPages`：移除，改为在 `onInitialized` Hook 中使用 `app.pages.push(createPage())`
- `clientDynamicModules`：移除，改为在 `onPrepared` Hook 中使用 `app.writeTemp()`
- `enhanceAppFiles`：移除，使用 `clientConfigFile` Hook
- `globalUIComponents`：移除，使用 `clientConfigFile` Hook
- `clientRootMixin`：移除，使用 `clientConfigFile` Hook
- `extendMarkdown`：重命名为 `extendsMarkdown`
- `chainMarkdown`：移除
- `extendPageData`：重命名为 `extendsPage`
- `extendsCli`：移除
- `configureWebpack`：移除
- `chainWebpack`：移除
- `beforeDevServer`：移除
- `afterDevServer`：移除

参考 [插件 API](https://v2.vuepress.vuejs.org/zh/reference/plugin-api.html) 

### 给主题作者、主题API变更





## 其他

### defineUserConfig与defineClientConfig

- defineUserConfig
  - 通常定义在： .vuepress/config.ts
  - 导入： `import { defineUserConfig } from "vuepress";`
  - 场景： 正常使用vuepress时的用户配置
- defineClientConfig
  - 通常定义在： .vuepress/client.ts，其他地方也行
  - 导入： `import { defineClientConfig } from '@vuepress/client或vuepress/client'`
  - 场景： 客户端配置，插件开发会用到
  - 内容： enhance、setup、layouts、rootComponents

### 常用

> 我比较常用的：
>
> - name
> - define
> - enhanceAppFiles，// 移除，使用 clientConfigFile Hook
> - clientRootMixin，// 移除，使用 clientConfigFile Hook
> - alias

