# architecture_设计原则

参考：[解析器架构和设计原则](https://github.com/markdown-it/markdown-it/blob/master/docs/architecture.md)

## Markdown-it 设计原则

### 数据流 (Data flow)

入数据通过嵌套的规则链进行解析。有 3 个嵌套链 - `core` 、 `block` 和 `inline` ：

```js
core
    core.rule1 (normalize)
    ...
    core.ruleX

    block
        block.rule1 (blockquote)
        ...
        block.ruleX

    core.ruleX1 (intermediate rule that applies on block tokens, nothing yet)
    ...
    core.ruleXX

    inline (applied to each block token with "inline" type)
        inline.rule1 (text)
        ...
        inline.ruleX

    core.ruleYY (applies to all tokens)
    ... (abbreviation, footnote, typographer, linkifier)
```

解析的结果是一个 `list tokens`，它将被传递给 `renderer` 来生成 html 内容。

这些 tokens 能被自身解析来生成更多的 tokens。（例如：一个 `list token` 能被拆分为多个 `inline tokens`）。

一个 `env` 沙盒能被用来与 tokens 来给你的解析器和渲染器注入额外的变量。

当解析数据时，每个链（core / block / inline）会使用一个独立的 `state` 对象，所以每个解析中的操作都是独立的，并且能在运行时被禁用。

### 令牌流 (Token stream)

不像传统的 `AST`，我们使用更加底层的数据代表 `tokens`
两者区别：

- Tokens 是一个简单的序列（数组）。
- 打开的和关闭的标签是隔离的、分开的。
- 有特殊的 token 对象，比如“内联容器(inline container)”，它有嵌套的 tokens。
- 一系列内联的标签（粗体，斜体，文本等等）

参考 [token class](https://github.com/markdown-it/markdown-it/blob/master/lib/token.js) 以获得关于每个 token 内容的细节。



总之，一个 token 流是：

- 在顶层 - 是成对或单个“块” tokens 的数组：
  - 打开的/关闭的标题，列表，块引用，段落，...
  - 代码，围栏块，水平规则，html 块，内联容器
- 每个内联 token 都有一个 `.children` 属性，带有嵌套 token 流，用于内联内容：
  - 打开的/关闭的 strong 强调，em 强调，链接，代码，...
  - 文字，换行符



更多关于 tokens 的细节：

- [Renderer 源码](https://github.com/markdown-it/markdown-it/blob/master/lib/renderer.js)
- [Token 源码](https://github.com/markdown-it/markdown-it/blob/master/lib/token.js)
- [在线示例](https://markdown-it.github.io/) - 输入你的文本然后点击 `debug` tab。

### 规则（Rules）

Rules 是用解析器的 `state` 对象做 “有魔力的事情” 的函数。一个唯一的规则会与一个或多个**链**相关联。
例如，`blockquote` 标记与 `blockquote`，`paragraph`，`heading` 和 `list` 链相关联。

Rules 通过 [Ruler](https://markdown-it.docschina.org/api/Ruler.html) 实例按名称管理，并且可以被 [MarkdownIt](https://markdown-it.docschina.org/MarkdownIt.html) 方法 `enabled` / `disabled`。

你可以注意到，某些规则具有 `validation mode` - 在此模式下规则不能修改 token 流，只能查看 token 的结尾。这是一个重要的设计原则 - token 流在块和内联解析阶段是“只写的”。

解析器旨在使规则彼此独立。你可以安全地启用/禁用它们，或者添加新的。 关于如何创建新规则则没有通用的方法 —— 设计具有良好数据隔离的分布式状态机是一项棘手的业务。但是你可以调查现有规则和插件，以查看可能的方法。

此外，在复杂的情况下，你可以尝试在跟踪器 (tracker) 中寻求帮助。这种情况是很简单的 - 从你的 ticket 上可以清楚地看到，你研究过文档，源码，并尝试自己做一些事情。我们绝不会拒绝真正的开发人员。

### 渲染器（Renderer）

生成 token 流后，将其传递给 [renderer](https://github.com/markdown-it/markdown-it/blob/master/lib/renderer.js)。 然后它会遍历所有 token，将每个token 传递给与 token 的 type 属性同名的规则。

渲染器规则位于 `md.renderer.rules [name]` ，是简单的具有相同特征的函数：

```js
function (tokens, idx, options, env, renderer) {
  //...
  return htmlResult;
}
```

在许多情况下，即使在没有解析器侵入的情况下，也可以轻松地进行输出更改。 
例如，让我们将img和video的链接 替换为 播放器的iframe

```js
var md = require('markdown-it')();

var defaultRender = md.renderer.rules.image;
var vimeoRE = /^https?:\/\/(www\.)?vimeo.com\/(\d+)($|\/)/;

md.renderer.rules.image = function (tokens, idx, options, env, self) { // image标签的渲染器
  var token = tokens[idx],
      aIndex = token.attrIndex('src');

  if (vimeoRE.test(token.attrs[aIndex][1])) { // 匹配img和video的链接
    var id = token.attrs[aIndex][1].match(vimeoRE)[2];
    return '<div class="embed-responsive embed-responsive-16by9">\n' + // 并替换为播放器的iframe
           '  <iframe class="embed-responsive-item" src="//player.vimeo.com/video/' + id + '"></iframe>\n' +
           '</div>\n';
  }

  // 传递 token 给默认的渲染器。
  return defaultRender(tokens, idx, options, env, self);
};
```

这里是另一个示例，如何添加 `target="_blank"` 到所有链接：

```js
// 如果覆盖，或者是对默认渲染器的代理，则记住老的渲染器。
var defaultRender = md.renderer.rules.link_open || function(tokens, idx, options, env, self) {
  return self.renderToken(tokens, idx, options);
};

md.renderer.rules.link_open = function (tokens, idx, options, env, self) {
  // 如果你确认其他的插件不能添加 `target` - 放弃以下检查：
  var aIndex = tokens[idx].attrIndex('target');

  if (aIndex < 0) {
    tokens[idx].attrPush(['target', '_blank']); // 添加新属性
  } else {
    tokens[idx].attrs[aIndex][1] = '_blank';    // 替换已经存在的属性值
  }

  // 传递 token 到默认的渲染器。
  return defaultRender(tokens, idx, options, env, self);
};
```

注意，如果你需要添加属性，你可以不需要覆盖渲染器来做这些事。

例如，你能够在 `core` 链中更新 tokens。这比直接覆盖渲染器慢，但这更简单。

让我们使用 [markdown-for-inline](https://github.com/markdown-it/markdown-it-for-inline) 插件来做同样的事情，就像之前的例子一样：

```js
var iterator = require('markdown-it-for-inline'); // 使用插件

var md = require('markdown-it')()
            .use(iterator, 'url_new_win', 'link_open', function (tokens, idx) {
              var aIndex = tokens[idx].attrIndex('target');

              if (aIndex < 0) {
                tokens[idx].attrPush(['target', '_blank']);
              } else {
                tokens[idx].attrs[aIndex][1] = '_blank';
              }
            });
```

你也能够**编写你自己的渲染器**来生成其他除了 HTML 的格式，像 JSON/XML... 你甚至能够使用它来生成 AST。

### 总结

这在 [数据流](https://markdown-it.docschina.org/architecture.html#数据流) 中提到过，但让我们再重复序列一次：

1. 解析块，并使用块 token 填充顶层 token 流
2. 解析内联容器上的内容，填充 `.children` 属性
3. 进行渲染

介于两者之间你可以应用额外的转换。全部内容 可见于每个链的顶部 [parser_core.js](https://github.com/markdown-it/markdown-it/blob/master/lib/parser_core.js)，[parser_block.js](https://github.com/markdown-it/markdown-it/blob/master/lib/parser_block.js)[ ](https://github.com/markdown-it/markdown-it/blob/master/lib/parser_block.js) 和 [parser_inline.js](https://github.com/markdown-it/markdown-it/blob/master/lib/parser_inline.js)文件。

你也可以直接在 [renderer](https://github.com/markdown-it/markdown-it/blob/master/lib/renderer.js) 中更改输出，以解决许多简单的情况。