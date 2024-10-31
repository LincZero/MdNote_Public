# README

## 资料

参考：

- Github：https://github.com/PrismJS/prism
- 官网：https://prismjs.com/
  - 插件相关：https://prismjs.com/#plugins

## 【比较】PrismJS、CodeMirror、Shiki

都可以用来处理代码块高亮

区别：

- 落地
  - CodeMirror：Typora
  - PrismJS：VuePress-Hope-Theme的旧版
  - Shiki：VuePress-Hope-Theme的新版
- 其他
  - ……


## 插件示例

### normalize-whitespace

- 源码：https://github.com/PrismJS/prism/blob/master/plugins/normalize-whitespace/prism-normalize-whitespace.js
- 官网：https://prismjs.com/plugins/normalize-whitespace/

## 需求实战

### 制表符渲染成N空格

这个我稍微研究过，当时有个需求：将制表符渲染成四空格而不是二空格

#### CodeMirror

CodeMirror的相关设置：

```js
var myCodeMirror = CodeMirror(doucment.body);
myCodeMirror.setOption("indentUnit", 4)
```

![img](README.assets/710b8c92ccc1d06c0f85b3a6f05860a1.png)

![img](README.assets/07dbcf3cbbcc6f95cd963e3ec5182173.png)

#### Prism.js

刚开始我以为是没有该功能的，后来发现是在插件里。

normalize-whitespace

- 源码：https://github.com/PrismJS/prism/blob/master/plugins/normalize-whitespace/prism-normalize-whitespace.js
- 官网：https://prismjs.com/plugins/normalize-whitespace/
- 使用示例：https://github.com/PrismJS/prism/blob/master/plugins/normalize-whitespace/demo.html

但这里有些坑，他的使用案例是直接在html里用script标签分别引入 prism.js 和 插件js 的。

但我的需求是在 VuePress 里修改该项，需要调整 `@vuepress/plugin-prismjs`，方法见下：

#### @vuepress/plugin-prismjs

具体修改：

1. 安装并启用，参考 VuePress 文档：https://ecosystem.vuejs.press/zh/plugins/prismjs.html

```bash
pnpm i -D @vuepress/plugin-prismjs@next
```





















