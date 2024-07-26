# MarkdownAbout

## 该目录路径下的导航

- (1) md软件或框架
- (2) md渲染引擎
- (3) md部件
- （md方法与技巧）
  - （这部分不在 "设计开发与数据生产/Develop/Doc"，详见 "设计开发与数据生产/Doc"）

## 部件构成

一个Md编辑/渲染器往往由几个部件构成：

- 主要的md解析器+渲染器
  - 解析器负责将文本转化AST或Tokens，渲染器将他们转化成html。这两个工作通常使用一个md引擎完成
  - 举例：Markdown-it (VuePress使用)、Kramdown、R_Markdown
- md文档的一些部分在底层会由一些常见库完成
  - 举例：
    - 代码高亮：CodeMirror、PrismJS (VuePress-Hope-Theme)
    - 公式渲染：katex、mathjax (在VuePress中均可选)
    - mermaid：mermaid

























