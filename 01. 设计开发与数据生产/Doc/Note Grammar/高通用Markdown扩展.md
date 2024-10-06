# 高通用Markdown扩展

一般是 markdown-it 插件，会比较通用

## 代码行高亮

- Obsidian方案: https://github.com/mugiwara85/CodeblockCustomizer
- VitePress方案: https://vitepress.dev/zh/guide/markdown#line-highlighting-in-code-blocks
- VuePress方案: https://vuejs.press/zh/guide/markdown.html#%E4%BB%A3%E7%A0%81%E5%9D%97
- VuePress-Theme-Hope方案： https://theme-hope.vuejs.press/zh/cookbook/vuepress/markdown.html#%E4%BB%A3%E7%A0%81%E5%9D%97
- 其中VuePress/VuePress-Theme-Hope的底层支持为：
  - shiki支持： https://ecosystem.vuejs.press/zh/plugins/markdown/shiki.html#highlightlines
  - prismjs支持： https://ecosystem.vuejs.press/zh/plugins/markdown/prismjs.html#highlightlines

代码块标注语法：

### 行高亮

**（为了更丰富的高亮，这里的示例我用三个波浪线代替三个反引号）**

支持：vitepress、vuepress/vuepress-theme-hope

````js
~~~js{4,7,9}                   // 多个单行
~~~js{5-8}                     // 多行
~~~js{4,7-13,16,23-27,40}      // 多行与单行
````

支持：obsidian插件

````js
~~~js hl:1,3,5,7               // 多个单行
~~~js hl:2-5                   // 多行
~~~js hl:test                  // 高亮`test`单词
~~~js hl:5|test,5-7|test2      // 行数+|+关键字
~~~js info:2 warn:4-6 error:8  // 更多类型 (原来的hl表示高亮)
(还允许用通配符等)
````

支持：vitepress (在注释中，而非在代码类型中，标注行高亮的信息)

````js
~~~js
...  // [!code highlight]
...  // [!code focus:<lines>]
...  // [!code --]
...  // [!code ++]
...  // [!code warning]
...  // [!code error]
~~~
````

### 启用行号

支持：vitepress

````js
~~~ts {1}                // 默认禁用
~~~ts:line-numbers {1}   // 启用行号
~~~ts:line-numbers=2 {1} // 从第2行开始
````

支持：vuepress/vuepress-theme-hope

````js
~~~ts                   // 默认启用
~~~ts:no-line-numbers   // 禁用
````

### 其他

支持：vuepress/vuepress-theme-hope

````js
~~~ts title=".vuepress/config.ts" // 标题
~~~md:no-v-pre                    // 这里会被 Vue 编译
````

支持：obsidian插件

````js
~~~cpp file:test.cpp
~~~cpp title:test.py
~~~cpp file:"long filename.cpp"

~~~cpp fold // 折叠
````

