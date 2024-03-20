# VuePress2 (Vue3)

## 资料

- 官网 (支持中文)

  -   [VitePress官网](https://vitepress.dev/)
  -   [VuePress v2 官网](https://v2.vuepress.vuejs.org/zh/)

  -   [VuePress v1 官网文档](https://vuepress.vuejs.org/zh/guide/getting-started.html)
  -   VuePress2官网文档
      -   [指南](https://vuepress.github.io/zh/guide/)
      -   [参考](https://vuepress.github.io/zh/reference/cli.html)
      -   [插件参考](https://vuepress.github.io/zh/reference/plugin/back-to-top.html)
      -   [深入 - 架构、插件和主题的开发](https://vuepress.github.io/zh/advanced/architecture.html)

- 插件开发 - Markdown-it插件

  - 详见Markdwon-it相关笔记

- 插件开发 - VuePress插件

  - ……

- 其他

  - [一篇带你用 VuePress + Github Pages 搭建博客](https://juejin.cn/post/7041134607869149215)


## 比较专题

### vuepress2 && vuepress1

### vitepress && vuepress

## 踩坑相关

### 一个版本冲突问题

#### #1

```js
node_modules\webpack\hot\dev-server.js

i ｢wds｣: Project is running at http://0.0.0.0:8080/
i ｢wds｣: webpack output is served from /
i ｢wds｣: Content not from webpack is served from G:\Git\Public\LincZero.github.io\docs\.vuepress\public
i ｢wds｣: 404s will fallback to /index.html
node:internal/crypto/hash:71
  this[kHandle] = new _Hash(algorithm, xofLen);
                  ^

Error: error:0308010C:digital envelope routines::unsupported
```

当时，我的node.js版本18.14.0，openssl版本 1.1.1g 10 Sep 2019
然后我尝试升级了node.js和opensll
升级后，我的node.js版本18.15.0，openssl版本 OpenSSL 3.1.0 14 Mar 2023 (Library: OpenSSL 3.1.0 14 Mar 2023)
但还是报同样的错

#### #2

https://github.com/vuejs/vuepress/issues/3095

windows在命令提示符中输入以下命令设置环境变量：

```
set NODE_OPTIONS=--openssl-legacy-provider
```

然后在相同的命令提示符窗口中运行 `npm run dev`。这样一来，`NODE_OPTIONS` 环境变量就会在当前的命令提示符会话中生效。

#### #3

然后又报了另一个错，这次降级webpack版本

```json
"vuepress": "^1.5.3",
"webpack": "^4.42.0"
```













