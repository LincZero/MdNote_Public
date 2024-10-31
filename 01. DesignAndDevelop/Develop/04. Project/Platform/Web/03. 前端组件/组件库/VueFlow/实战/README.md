---
create_time: 2024-10-19
Author: LincZero
---
# README_实战

这次实战是在VuePress上使用VueFlow

详见个人仓库

## VuePress插件开发

```bash
pnpm add @vue-flow/core
```

### 自定义组件

:::tabs

@tab .vuepress/config.ts

```ts
import plugins from "./config_plugins.ts";

export default defineUserConfig({
  plugins,
})
```

@tab .vuepress/config_plugin.ts
```ts
import vueflowPlugin from "./plugin/VueFlowPlugin"
type PluginConfig = any;

const plugins: PluginConfig = [
  vueflowPlugin
]

export default plugins
```

@tab .vuepress/plugin/VueFlowPlugin/index.ts
```ts
import { getDirname, path } from "@vuepress/utils"

export default (options, ctx) => {
  return {
    name: 'vuepress-plugin-vue-flow',
    clientConfigFile: path.resolve(__dirname, 'clientConfig.ts'),
  }
}
```

@tab .vuepress/plugin/clientConfig.ts
```ts
import { defineClientConfig } from 'vuepress/client';

import VueFlow from "./VueFlow.vue";

export default defineClientConfig({
  enhance: ({ app, router, siteData }) => {
    app.component("VueFlow", VueFlow);
  },
})
```

:::

注意，由于我这里需要管理多个插件，这里的文件多了几个，其实都可以合并起来的。合并起来看着可能会简洁一些。合并起来可能是这个样子：（没验证）

```ts
import plugins from "./config_plugins.ts";

export default defineUserConfig({
  plugins: [
    (options, ctx) => {
      return {
        name: 'vuepress-plugin-vue-flow',
        clientConfigFile: path.resolve(__dirname, 'clientConfig.ts'),
    },
  ],
})
```

然后就可以使用 `<VueFlow />` 来使用了

### VueFlow.vue定义

#### 最小组件

VueFlow.vue

```html
<script setup>
import { ref, onMounted } from 'vue'
import { VueFlow, Panel } from '@vue-flow/core'

const nodes = ref([
  {
    id: '1',
    position: { x: 50, y: 50 },
    data: { label: 'Node 1', },
  }
]);
</script>

<template>
  <VueFlow :nodes="nodes">
  </VueFlow>
</template>

<style>
/* import the necessary styles for Vue Flow to work */
@import '@vue-flow/core/dist/style.css';

/* import the default theme, this is optional but generally recommended */
@import '@vue-flow/core/dist/theme-default.css';

.vue-flow {
  height: 400px;
}
</style>
```

特別需要注意：在vuepress中使用时，得给他加一个默认高度，否则不显示

#### 按钮补充

```html
import { VueFlow, Panel } from '@vue-flow/core'

<script setup lang="ts">
function addNode() {
  const id = Date.now().toString()
  
  nodes.value.push({
    id,
    position: { x: 150, y: 50 },
    data: { label: `Node ${id}`, },
  })
}
</script>

<template>
  <VueFlow :nodes="nodes" :edges="edges">
    <Panel>
      <button type="button" @click="addNode">Add a node</button>
    </Panel>
  </VueFlow>
</template>
```

#### 我的默认配置

### 动态渲染json

略，详见项目

## Obsidian插件开发

```bash
pnpm add @vue-flow/core
```

详见： https://github.com/LincZero/obsidian-node-flow

项目README以及src/README里面我都习惯写挺全的

### 创建模板

1. generated

generated from [guopenghui/obsidian-vue-starter](https://github.com/guopenghui/obsidian-vue-starter)

但他这个依赖很旧，编译不稳定，我给改了下，见修改历史：22c2a9c2ad9eac8e0ce1abfb0b4484358eb0e28b

然后尝试安装依赖和构建，并在obsidian中查看是否能正常使用

2. vue file

见修改历史：22c2a9c2ad9eac8e0ce1abfb0b4484358eb0e28b 的下一次commit

vue file: VueTest.vue

```vue
<template>
  <h2>Hello,Developer!</h2>
</template>

<script setup lang="ts">
</script>

<style scoped>
h2 {
    color: lightcoral;
}
</style>
```

3. 在主程序中使用 Vue UI

main.ts

```ts
import type {MarkdownPostProcessorContext} from "obsidian"
import { factoryVueDom } from './vueAdapt'
...
this.registerMarkdownCodeBlockProcessor("vue-test",
  (
    src: string,                                // 代码块内容
    blockEl: HTMLElement,                       // 代码块渲染的元素
    ctx: MarkdownPostProcessorContext           // 上下文
  ) => {
    const root_div = document.createElement("div");  blockEl.appendChild(root_div); root_div.classList.add("vue-shell");
    factoryVueDom(root_div, "vue-test")
  }
)
```

vueAdapt.ts

```ts
import { createApp, App as VueApp } from 'vue';
import VueTest from './component/VueTest.vue';

// 在div内创建指定的 Vue UI
export function factoryVueDom(div:HTMLElement, vueUI:string = "vue-test"):void {
  const _app = createApp(VueTest, {});
  _app.mount(div);
}
```

### 加入vueflow

略，详见项目

## 一些Vue学习经验

### Vue父组件引用子组件的方法

一些学习笔记：
1. `const RefChild = ref<{...}>()` 定义了一个 `{...}` 类型的值为 `undefined` 的 `ref` 对象
2. `<NodeFlow ref="RefChild" :jsonData="jsonData" />` 在初始化时，会将自身导出的东西赋值给`RefChild`
3. 此时父组件就拥有了指向 “子组件所导出东西” 的Ref对象

目的是父组件引用子组件的方法
主要是这里是 `setup+ts`，和网上资料中较多的 `this.$refs` 用法不同

这是 Composition API 与 Options API 的区别: 
- this.$refs 是 Options API 中用于获取 DOM 元素或组件实例的属性
- 而在 Composition API 中，我们更倾向于使用 ref 和 reactive 来管理状态，以及通过 setup 函数来定义组件的逻辑






