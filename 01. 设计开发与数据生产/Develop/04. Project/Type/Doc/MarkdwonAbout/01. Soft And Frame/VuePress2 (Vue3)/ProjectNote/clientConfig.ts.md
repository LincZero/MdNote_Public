```ts
/**
 * @file clientConfig.ts
 * 
 * study:
 * - https://vuepress.github.io/advanced/cookbook/usage-of-client-config.html
 * - https://vuepress.github.io/zh/advanced/cookbook/usage-of-client-config.html
 * 
 * 比较
 * deineUserConfig的输出都是在编译期，在终端窗口
 * defineClientConfig的输出都在客户端，在浏览器控制台
 */

import { defineClientConfig } from 'vuepress/client';

// import MyVueFlow from "./MyVueFlow.vue";

export default defineClientConfig({
  /**
   * 时机：在客户端应用创建后被调用，后续切换页面不再触发
   * @param app 由 createApp 创建的 Vue 应用实例
   *   可用于注册全局组件
   * @param router 由 createRouter 创建的路由实例
   *   可用于添加导航钩子
   * @param siteData 根据用户配置生成的 Ref 对象，包含 base, lang, title, description, head 和 locales
   */
  enhance: ({ app, router, siteData }) => {},
  /**
   * 时机：客户端 Vue 应用的 setup Hook 中被调用，包括加载新页面时会被调用
   * 作用：可延时后做一些操作
   */
  setup() {},
  /**
   * 作用：用于设置布局组件
   */
  layouts: {},
  /**
   * 组件数组
   * 作用：放置一些全局的 UI 组件，比如全局弹窗等
   */
  rootComponents: [],
})
```
