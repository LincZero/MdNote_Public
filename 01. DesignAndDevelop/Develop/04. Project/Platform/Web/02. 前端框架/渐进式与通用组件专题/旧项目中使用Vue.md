# 旧项目中使用Vue

参考：

- https://blog.csdn.net/anyaoqi/article/details/87465970
- https://www.cnblogs.com/konghaowei/p/15524413.html
- https://www.cnblogs.com/jsonq/p/18262365 (main)

使用原生 html 写 vue 项目。**注意：是项目，而不是页面**，此方式是不推荐的，毕竟有脚手架，但在一些及其特殊场景下，可能会需要类似的方式，因此作为一个记录。

> 这种方式唯一的优点就是写完可以直接扔服务器上了－_－

## 对 html 写 vue 的认知

很多人对 在 html 中运行 vue 项目这种内容，认知只停留在引入 vue 的 cdn 文件，然后在 html 里一顿写，就觉得 html 写 vue 不是很简单嘛，但请注意用词，是**项目**，而不是**页面**，你能写一个 `.vue` 页面引入让 html 去运行吗？显然不可以，而此文章就是说这个的。

---

**正常想要在原生 html 中直接写 `.vue` 文件是不现实的**，因为 html 压根就不认识 .vue 文件，只有脚手架才能识别，那如何才能让 html 识别 `.vue` 文件呢？其实也很简单，核心就是一个包 `vue3-sfc-loader`

## vue3-sfc-loader 使用场景

因为 `vue3-sfc-loader` 可以直接解析 `.vue` 文件，所以可以使用在页面中远程加载 vue 组件的场景中

### 什么是 es 包和 umd 包

es 包支持 import 导入的写法，比如这样

```html
<script type="module">
  import { createApp, ref } from 'https://unpkg.com/vue@3/dist/vue.esm-browser.js'

</script>
```

而 umd 包是直接运行在浏览器的，比如我引入了 `vue.global.js` 这就是一个 browser 包，我可以在 window 上访问到 `Vue` 实例

使用时就是这样

```html
<script src="https://unpkg.com/vue@3/dist/vue.global.js"></script>
<script>
  const { createApp, ref } = Vue // window.Vue

</script>
```

> es 包是需要 `script` 标签添加 `type="module"`，导入方式为`import`。  
> 而 umd 包引入之后，会自动挂载到 window 上，导入方式为解构 `const {...} = Vue`

## 让 html 识别 `.vue` 文件

**需由一个前提条件，由于下载的都是生产文件，打开 html 页面时需要使用 `Live Server` 插件打开，普通打开方式无法运行**

> 这里统一用 es 文件，模仿脚手架结构进行搭建

1. 下载 `vue` 离线 es 文件： [vue.esm-browser.prod.min.js](https://cdnjs.cloudflare.com/ajax/libs/vue/3.4.29/vue.esm-browser.prod.min.js)
2. 下载 `vue3-sfc-loader` 离线 es 文件：[vue3-sfc-loader.esm.js](https://cdn.jsdelivr.net/npm/vue3-sfc-loader@0.9.5/dist/vue3-sfc-loader.esm.js)
3. 新建 `index.html`，并引入下载好的 vue 和 sfc 解析文件

这种 `Import maps` 写法在 vue 官网上有 [示例](https://cn.vuejs.org/guide/quick-start.html#enabling-import-maps)

**特性：** 其实就是一个路径映射，此时 `import {} from "vue"` 等价于 `import {} from "./lib/es/vue.esm-browser.prod.min.js"`  
**优点：**

- 可以非脚手架项目中可以支持 `import {} from "vue"`。
- 如果不使用，就需要 `import {} from "./lib/es/vue.esm-browser.prod.min.js"` 引入相对或绝对路径，冗余且意义不大
