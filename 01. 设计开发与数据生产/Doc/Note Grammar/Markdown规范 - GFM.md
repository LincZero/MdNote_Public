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






