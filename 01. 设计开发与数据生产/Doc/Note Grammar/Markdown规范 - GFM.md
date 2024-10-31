---
create_time: 2024-10-21
---
# Markdown规范 - GFM

## Alert

> [!note]
> content

but can't with title

## 代码高亮

（diff格式专用，不是什么扩展）

```diff
 // .vuepress/config.js
 module.exports = {
   plugins: ['schema2md', {
+    write: true,
     pages: {
       '/config/': {
         schemaPath: '/path/to/your/schema.json'
+        outputPath: 'docs/config/README.md', // You shouldn't commit this file.
       }
     }
   }]
 }
```

## 样式限制

参考：https://segmentfault.com/q/1010000042618482

出于安全原因，GitHub 不允许 CSS 通过 CSS 影响 `README.md` 文件（就像您可以将 CSS 注入自述文件中一样，您可以轻松发起网络钓鱼攻击）。这包括通过 `<link rel>` 引用的样式表和与 `<style>` 一起使用的内联样式





