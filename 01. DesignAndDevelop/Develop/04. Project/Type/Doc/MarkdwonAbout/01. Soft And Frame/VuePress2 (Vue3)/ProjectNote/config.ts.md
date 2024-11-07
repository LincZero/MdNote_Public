```ts
/**
 * @file config.ts
 * 
 * study:
 * - https://vuepress.github.io/zh/reference/plugin-api.html
 * - https://vuepress.github.io/zh/reference/node-api.html
 * 
 * 比较
 * deineUserConfig的输出都是在编译期，在终端窗口
 * defineClientConfig的输出都在客户端，在浏览器控制台
 */

/// VuePress 相关的设置

import { defineUserConfig } from "vuepress";                  // vuepress
import { createPage } from 'vuepress/core'

import theme from "./theme.ts";                               // hope主题 - 默认部分
import alias from "./config_alias.ts";                        // hope主题 - 别名扩展
import extendsMarkdown from "./config_extendsMarkdown.ts";    // hope主题 - mdit扩展
import plugins from "./config_plugins.ts";                    // hope主题 - 插件扩展

export default defineUserConfig({
  
  // ------------------ 导航类 ------------------
  base: "/",
  locales: {
    "/": {
      lang: "zh-CN",
      title: "Linc 的小站",
      description: "Linc 的个人小站",
    },
  },
  markdown: {
    headers: {
      level: [1, 2, 3, 4, 5, 6] // 不然的话toc会受限
    },
  },

  // ------------------ 扩展类 ------------------
  theme,
  alias,
  extendsMarkdown,
  plugins,

  // ------------------ 扩展类 - 钩子 ------------
  /**
   * 插件API
   * 这里是在config.ts文件的defineUserConfig里写
   * 
   * - 插件需要在初始化之前使用。基础配置项会在使用插件时立即被处理：
   *   - name
   *   - multiple
   * - 下列 Hooks 会在初始化 App 时处理：
   *   - extendsMarkdownOptions
   *   - extendsMarkdown
   *   - extendsPageOptions
   *   - extendsPage
   *   - onInitialized
   * - 下列 Hooks 会在准备文件时处理：
   *   - clientConfigFile
   *   - onPrepared
   * - 下列 Hooks 会在 dev / build 时处理：
   *   - extendsBundlerOptions
   *   - alias
   *   - define
   *   - onWatched
   *   - onGenerated
   * 
   * 调试：注释第一个字符表示输出顺序
   */
  onInitialized() { console.log("=====onInitialized") } // 1 VuePress App 初始化后被立即调用
  onPrepared() { console.log("=====onPrepared"); },     // 2 VuePress App 完成文件准备后被立即调用
  onGenerated() { console.log("=====onGenerated"); },   // x VuePress App 完成静态文件生成后被立即调用
  onWatched() { console.log("=====onWatched"); },       // 3 VuePress App 启动开发服务器并开始监听文件修改后被调用

  // ------------------ 其他 ---------------------
  // 使网页成为PWA
  // shouldPrefetch: false, // 是否预获取
});
```

直接支持json

```ts
async onInitialized(app) {
  /**
   * 可以在这里创建没有对应md的页面
   */
  // if (app.pages.every((page) => page.path !== '/MdNote_Public/FLUX.json')) {
  //   const newPage = await createPage(app, {
  //     path: '/MdNote_Public/FLUX/',
  //     frontmatter: {
  //       layout: 'Layout',
  //     },
  //     content: `# 欢迎来到 FLUX`,
  //   })
  //   app.pages.push(newPage)
  // }
  /**
   * 也可以在这里对符合条件的页面做一些处理
   * 例如这里我对.json后缀进行处理 (需要先设置pagePatterns允许解析json，否则找不到json文件)
   * 甚至可以不修改，而用一个新页面替换掉
   */
  for (let i = 0; i < app.pages.length; i++) {
    const page = app.pages[i];
    if (!page.path.endsWith(".json")) continue
    // console.log("旧页面信息----------------------------------------\n", page)
    // console.log("新页面信息----------------------------------------\n", newPage)
    {
      page.path = page.path+"/"
      // page.frontmatter = newPage.frontmatter    // 保证能够打开
      page.frontmatter.layout = 'Layout'
      page.content = "```nodeflow-comfyui\n" + page.content + "\n```"
      // page.routeMeta.e = "<p>7890</p>"
      // page.contentRendered = "<p>0090lk</p>"
      // page.filePath                          // 不能换，否则侧边栏不正常
      // page.filePathRelative                  // 不能换，否则侧边栏不正常
      // if(page.sfcBlocks.template?.content) page.sfcBlocks.template.content = ""
      if(page.sfcBlocks.template?.contentStripped) page.sfcBlocks.template.contentStripped = // HTML内容以这个为准
        app.markdown.render(page.content)       // 重渲染了
    }
  }
},
```

直接支持pdf

```ts
async onInitialized(app) {
  for (let i = 0; i<app.pages.length; i++) {
      const page = app.pages[i]
      if (page.path.endsWith(".json")) {
        // console.log("旧页面信息---\n", page)
        // console.log("新页面信息---\n", newPage)
        page.path = page.path+"/"
        page.frontmatter.layout = 'Layout'
        page.content = "```nodeflow-comfyui\n" + page.content + "\n```"
        if(page.sfcBlocks.template?.contentStripped) page.sfcBlocks.template.contentStripped = // HTML内容以这个为准
          app.markdown.render(page.content) // 重新渲染该页
      }
      else if (page.path.endsWith(".pdf")) {
        const newPage = await createPage(app, {
          path: page.path+"/",
          frontmatter: {
            layout: 'Layout',
          },
          content: `# PDF测试`,
        })
        app.pages[i] = newPage // 即删掉旧的pdf页，更换成一个引用pdf内容的md页
      }
    }
},
```

