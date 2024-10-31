# TyporePlugin

参考：https://github.com/obgnail/typora_plugin

## 有哪些插件

见：https://github.com/obgnail/typora_plugin

标签栏功能感觉不错

## 插件是如何实现的？

这个就比较有意思了，我之前 Typora 转 Obsidian 的一个原因是因为 Obsidian 有插件，可以更好地自定义

Typora 相较 Obsidian 并没有官方提供的一个 插件API，并不能很好地实现插件。那上面那些插件是怎么实现的？

链接中也说明了实现方法：https://github.com/obgnail/typora_plugin?tab=readme-ov-file#%E5%AE%9E%E7%8E%B0%E5%8E%9F%E7%90%86

这里转一下：

### 前端

`window.html` 是 Typora 的初始文件，可以写入一个 `<script>` 标签实现功能，就和 Tampermonkey 脚本一样。

### 后端

1. 因为 Typora 暴露了 `reqnode` 函数（require 的别名），所以可以使用 CommonJS 的 `reqnode('path')` 导入 Node.js 的 path 库，其他库同理。
2. 因为 Typora 使用了 electron 不太安全的 `executeJavaScript` 功能，所以可以用此注入 JS 代码，从而劫持后端关键对象，进而实现 electron 的后端功能注入。理论上劫持了 electron 对象，你甚至可以在 Typora 里斗地主。

```typescript
// 控制台输入下面命令:

// 让第二个窗口打印消息
JSBridge.invoke("executeJavaScript", 2, `console.log("i am logging")`);

// 让所有窗口打印消息
ClientCommand.execForAll(`console.log("i am logging")`);

// 获取到本窗口的BrowserWindow对象
global.reqnode('electron').remote.require('electron').BrowserWindow;

// 获取到所有窗口的BrowserWindow对象
ClientCommand.execForAll(`console.log(global.reqnode('electron').remote.require('electron').BrowserWindow)`);

// 让窗口1执行语句_myValue=123，然后将变量_myValue传给窗口2
JSBridge.invoke('executeJavaScript', 1, "_myValue=123; JSBridge.invoke('executeJavaScript', 2, `console.log(${_myValue})`)");
```

## 补充

虽然通过这种方法可以实现 typora 插件，但总感觉开发起来会比较麻烦，也会比较容易踩坑。

开发难度和开发插件的社区氛围依然不能达到 Obsidian 的地步

















