# 如何在VuePress中使用mdit插件

VuePress 可以选用 md-it 引擎进行渲染，注意 markdown-it 插件大多 -D 依赖就行了

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
$ npm install -D markdown-it-xxx
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
      md.use(require('markdown-it-xxx'))	// 注意这里的md类型为 markdownit
    }
  }
}
```

### Hope主题版

参考

- https://theme-hope.vuejs.press/zh/faq/common-question.html#%E6%B7%BB%E5%8A%A0-markdown-%E6%89%A9%E5%B1%95 Hope主题版

依赖

```bash
pnpm install -D markdown-it-multimd-table
```

配置 (.vuepress/config.ts)

```typescript
import { defineUserConfig } from "vuepress";
import MarkdownIt from "markdown-it-multimd-table"

export default defineUserConfig({
  // 站点配置
  // ...

  extendsMarkdown: (md) => {	// 注意这里的md类型为 markdownit ()
    md.use(MarkdownIt);
  },
});
```

### 简单 markdown-it demo

> 刚开始我不知道为什么，很多项目都不能 `npm i` 成功。后来发现是我傻了 ——
>
> markdown-it 并不像 obsidian 插件那样需要编译一遍再放入ob的沙盒环境里使用，mdit插件很简单，甚至优势几行代码就可以是一个插件了（见下面的示例）

#### use用法

```typescript
interface Options {
  multiline: boolean;
  rowspan: boolean;
  headerless: boolean;
  multibody: boolean;
  autolabel: boolean;
}

function demo2(md: MarkdownIt, options?: Partial<Options>): void {
  //md.inline.ruler.before('emphasis', 'demo', demo1)

  const fence = md.renderer.rules.fence
  md.renderer.rules.fence = (...args) => {
    const [tokens, idx] = args
    const token = tokens[idx]
    const rawCode = fence(...args)		// rawCode是原内容，下面在原内容的外面包一一个div
    return `<!--beforebegin--><div class="mdit-test language-${token.info.trim()} extra-class">` +
    `<!--afterbegin-->${rawCode}<!--beforeend--></div><!--afterend-->`
  }
}
...
extendsMarkdown: (md: markdownit) => {
	md.use(demo2)
},
```

#### 非use用法

参考：https://github.com/element-plus/element-plus/blob/7a1d0c305121a189442feb8b8e47ec1b3cb59d02/docs/.vitepress/plugins/tag.ts#L4（这个是直接在github中搜索代码：`md.inline.ruler.before(` 这样搜出来的）

```typescript
function demo1(state, silent){
  console.log(state);
  console.log(silent);
  return true
}
...
extendsMarkdown: (md: markdownit) => {
	//md.use(mdit_plugin_multimd_table_plugin);
	md.inline.ruler.before('emphasis', 'demo', demo1);
},
```

这种方式似乎写得有问题，出现报错了，自己调一下吧，反正应该也是可以的，大概就这么个原理

```bash
✖ Initializing and preparing data - failed in 91ms
Error: inline rule didn't increment state.pos
……
```

## 注意项：mdit 和 mdit-container 的导入问题

原 API 详见 “《markdwon-it 中文文档》/仅使用” 一章

一共有四种方式：

1. node.js环境，用 requires 函数
2. 非AMD环境方式
3. Vue环境，用 npm install + import from
4. VuePress环境，用 extendsMarkdown 重定义回调函数



注意项1：require方式，在VuePress中会报错

```typescript
// 不能在vuepress中用这种
var md = require('markdown-it')()
            .use(require('markdown-it-container'), name [, options]);
// 报错：
Error: Dynamic require of "markdown-it" is not supported
Error: Dynamic require of "markdown-it-container" is not supported
```



注意项2：使用 extendsMarkdown 重定义的化，里面的类型 markdownit 和你用 npm install + import from 导入的 MarkdownIt 有一些细微区别，例如可能版本不匹配，导致一些属性找不到，可能需要加 `@ts-ignore`。另一种方式是用 npm install + import from 代替 extendsMarkdown 里的类型定义



注意项3：extendsMarkdown 只提供了 mdit 变量，像我们前面例子中需要用到 markdown-it-container，这也还是需要结合 npm install + import from 来导入。混合使用

