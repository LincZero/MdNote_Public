## 简单调研

不想深度学，仅作为了解其原理简单调研一下，参考：https://juejin.cn/post/7169020147590496292

然后发现也有一定的可视化操作空间，可以在uTools中找到 "uTools开发者工具" 进行项目的创建

以一个简单的网页快开为例，插件代码文件也不多。核心代码就两个

- index.html， 前端展示页面
- preload.js， 调用到nodejs,electron,还有utools提供的api
- (配置)
  - logo.png， logo
  - plugin.json， 基本配置信息

## 资料

- API文档，https://www.u.tools/docs/developer/api.html#%E4%BA%8B%E4%BB%B6
- API，https://github.com/uTools-Labs/utools-api-types （开发模式和Obsidian还是比较相似的）
  - utools.api.d.ts， 一个711行的接口，比ob轻量些，全部有中文注释这点还是不错的！
  - package.json
  - (非核心)
    - index.d.ts
    - LICENSE
    - README.md

## API 接口