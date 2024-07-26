# 如何在VuePress中使用mdit插件

VuePress 可以选用 md-it 引擎进行渲染

## VuePress中 - 使用vuepress插件

参考

- 官方文档中对使用和开发插件的描述：https://v2.vuepress.vuejs.org/zh/guide/plugin.html
- 例子：https://ecosystem.vuejs.press/zh/plugins/analytics/google-analytics.html

依赖

```bash
$ npm i -D @vuepress/plugin-google-analytics@next
```

配置

```typescript
import { googleAnalyticsPlugin } from '@vuepress/plugin-google-analytics'

export default {
  plugins: [
    googleAnalyticsPlugin({
      // 配置项
    }),
  ],
}
```

## 通用 - mdit插件的使用

参考

- 以 markdown-it-multimd-table 为例

  - Github：https://github.com/redbug312/markdown-it-multimd-table

  - npmjs：https://www.npmjs.com/package/markdown-it-multimd-table

## VuePress中 - 使用mdit插件

前面讲了他们的各自使用方法，但结合在一起用的话不一样的。可以将 VuePress 插件分成两种：

- 一种是 VuePress 自身插件
  - 使用 `export default {  plugins: [`

- 一种是 mdit 插件，也叫做 Markdown 扩展
  - 其中VuePress版和我所用的Hope主题版在使用上略有差异。原理上似乎是预留了一个钩子函数


### VuePress版

参考

- https://vuepress.vuejs.org/zh/guide/markdown.html# 进阶配置

依赖

```bash
$ npm install markdown-it-xxx
```

配置 (.vuepress/config.js)

```js
module.exports = {
  markdown: {
    // markdown-it-anchor 的选项
    anchor: { permalink: false },
    // markdown-it-toc 的选项
    toc: { includeLevel: [1, 2] },
    extendMarkdown: md => {
      // 使用更多的 markdown-it 插件!
      md.use(require('markdown-it-xxx'))
    }
  }
}
```

### Hope主题版

参考

- https://theme-hope.vuejs.press/zh/faq/common-question.html#%E6%B7%BB%E5%8A%A0-markdown-%E6%89%A9%E5%B1%95 Hope主题版

依赖

```bash
pnpm install markdown-it-multimd-table
```

配置 (.vuepress/config.ts)

```typescript
import { defineUserConfig } from "vuepress";
import MarkdownIt from "markdown-it-multimd-table"

export default defineUserConfig({
  // 站点配置
  // ...

  extendsMarkdown: (md) => {
    md.use(MarkdownIt);
  },
});
```

### 插件源码版 (非npm方式)

以 **markdown-it-emoji-3.0.0** 插件为例，npm 方式是 `$ npm install i markdown-it-emoji`，其他和上面的基本一致。接下来看源码方式

安装依赖并编译

```bash
$ npm i
$ npm run build

# 构建产物：





```

加载

```typescript

```

测试

```
Hello from mars :satellite:
```







