---
create_time: 2024-10-13
---

# Markdown规范

（注意：本篇笔记具有时效性，编辑于 2024-10-13）

关于md标准

有个东西叫 CommonMark，最原始最基础的，见 https://spec.commonmark.org/0.31.2/ (最新的24年1月)

然后又有个东西叫 GFM（Github Flavored Markdown），见 https://github.github.com/gfm/ 或 https://gfm.docschina.org/zh-hans/ (19年标准)
官方介绍：`GFM is a strict superset of CommonMark.` (GFM是CommonMark的严格超集)

callout语法在 GFM 规范 (22年后实际支持，但并没有修改规范文档，最新规范依然是19年的V0.29版本) 里叫 GFM Alert，ComonMark 没有这个东西

然后obsidian的callout又不相当于 GFM Alert，例如 GFM Alert 不允许在 `[!note]` 后面添加加标题，或者添加是否折叠的标志，也不允许嵌套。callout是ob创造的语法，ob似乎也没有去写什么规范文档

mermaid 和 latex 也并不是markdown的标准，只是这两分别使用的mermaid库，以及katex/mathjax，轻巧快速，被大多数md编辑器所内置（并非全部内置，vscode/github/gitee有，但clion(jetbrant)/一些非md软件的md编辑器(trello/飞书)不内置）

还有诸如上下标、高亮等，都是非标准的语法。虽然像高亮支持得比较广泛了，但也没有被添加到文档标准当中。

除了这些小修小补的扩展外，还有一些改动较多的，也需要借助自己的md解释器来渲染的。例如 kramdown 等

---

总之，已有的规范文档虽然也有更新，但基本不新增任何语法，都是在原有规范的基础上进一步讨论细节或其他。

而这些旧规范无法满足现代很多需求，但似乎由于历史遗留问题或者为了追求稳定性和易实现性，没有添加很多东西。

另外，其实不需要追求纯原生，有些东西哪怕99%的md软件都支持，他也是非标准的。


