# README

这部分都是API，就不转了，自己去看：https://markdown-it.docschina.org/api/Core.html#core-new

## 总结常用的

基本使用流程：

```
// (1) md变量的获取，有node.js方式和非AMD浏览器方式，详见官网
var md = ...;

// (2) 解析规则的配置
...

// (3) 渲染规则的配置
...

// (4) 渲染
md.render('')	// 将字符串渲染成结果
```

### 解析规则的配置

### 渲染规则的配置

```
// 渲染规则的配置
const oldFence = md.renderer.rules.fence
md.renderer.rules.fence = (...args) => { // 围栏代码块的渲染规则
    if (不是要匹配的) return oldFence(...args)
    else 自定义处理
}
md.renderer.rules.image = function (tokens, idx, options, env, self) { // 图片渲染规则
    var token = tokens[idx], aIndex = token.attrIndex('src'); // 获取图片的src属性
    return return '<div>'+src+'</div>'
}

// 渲染
md.render('')	// 将字符串渲染成结果
```

常用属性

```
// 规则的修改，避免修改token
const fence = md.renderer.rules.fence
  md.renderer.rules.fence = (...args) => {
    const [tokens, idx] = args
    const token = tokens[idx]
    const rawCode = fence(...args)		// rawCode是原内容，下面在原内容的外面包一一个div
    return `<!--beforebegin--><div class="language-${token.info.trim()} extra-class">` +
    `<!--afterbegin-->${rawCode}<!--beforeend--></div><!--afterend-->`
  }
```

```
const fence = md.renderer.rules.fence
  md.renderer.rules.fence = (...args) => {
    let rawCode = fence(...args);		// rawCode是原内容，下面将原内容的span标签替换成a标签
    rawCode = rawCode.replace(/<span class="token comment">\/\/ try-link https:\/\/(.*)<\/span>\n/ig, '<a href="$1" class="try-button" target="_blank">Try</a>');
    return `${rawCode}`
  }
```

## Core

### Core.new

### Core.process

### Core#ruler

## MarkdownIt

### MarkdownIt.new

### MarkdownIt.configure

### MarkdownIt.disable

### MarkdownIt.enable

### MarkdownIt.parse

### MarkdownIt.parseInline

### MarkdownIt.render

### MarkdownIt.renderInlinne

### MarkdownIt.set

### MarkdownIt.use

### MarkdownIt#normalizeLink

### MarkdownIt#normalizeLinkText

### MarkdownIt#validateLink

### MarkdownIt#block

### MarkdownIt#core

### MarkdownIt#helpers

### MarkdownIt#inline

### MarkdownIt#inkify

### MarkdownIt#renderer

### MarkdownIt#utils

## ParserBlock

### ParserBlock

### ParserBlock.new

### ParserBlock.parse

### ParserBlock#ruler

## ParserInline

### ParserInline

### ParserInline.new

### ParserInline.parse

### ParserInline#ruler

### ParserInline#ruler2

## Renderer

### Renderer

### Renderer.new

### Renderer.render

### Renderer.renderAttrs

### Renderer.renderInline

### Renderer.renderLinlineAsText

### Renderer.renderToken

### Renderer#rules

## Ruler

### Ruler

### Ruler.new

### Ruler.after

### Ruler.at

### Ruler.before

### Ruler.disable

### Ruler.enable

### Ruler.enableOnly

### Ruler.getRules

### Ruler.push

## Token

### Token

### Token.new

### Token.attrGet

### Token.attrIndex

### Token.attrJoin

### Token.attrPush

### Token.attrSet

### Token#attrs

### Token#block

### Token#children

### Token#content

### Token#hidden

### Token#info

### Token#level

### Token#map

### Token#markup

### Token#meta

### Token#nesting

### Token#tag

### Token#type











