# 区分 JS JSX TS TSX

# 目录

# 区分 JS JSX TS TSX

参考：https://blog.csdn.net/shifang07/article/details/105371268

## JSX

就是Javascript和XML结合的一种格式。React发明了JSX，利用HTML语法来创建虚拟DOM。当遇到<，JSX就当HTML解析，遇到{就当JavaScript解析。JSX 只是为 React.createElement(component, props, …children) 方法提供的语法糖。React 自创了JSX语法，是一个 JavaScript 的语法扩展，官方建议在 React 中配合使用 JSX 来替代原始的 JS。因为JSX 可以更好的描述 UI 应该呈现出它应有交互的本质形式。JSX 看起来有点类似模版语言，但它具有 JavaScript 的全部功能。



## .js和.jsx的区别

.js可以用来做为模块来使用

.jsx一般作为组件来使用，但是js也可以用来作为组件使用也是没问题的

.js就是前端开发语言,jsx是React框架下用的,要在React框架中的编译器编译成js语言才能使用的



## TS

用 TypeScript 语法写的 .ts .tsx 等后缀的程序是不能直接运行的，而是会被 tsconfig.json 配置中的 “target”: “es6”, 这项配置转换为 es6 语法的 .js 文件。

TypeScript 中的 import 只会加载 .ts .tsx 后缀的文件，而 Javascript 中的 import 只能加载 .js 等后缀的文件

**TypeScript的优势**

- 规避静态类型出错：TS通过静态类型检查，能把错误从运行时提前至编译时，避免了一些基本bug。
- 应对接口改变 快速准确
   假如后端改变了一些接口字段，可以通过直接改变编译出错的地方，快速替换。而不需要一个一个字段地寻找



## ts js 区别

TypeScript 和 JavaScript 是目前项目开发中较为流行的两种脚本语言。
JavaScript 是轻量级的解释性脚本语言，可嵌入到 HTML 页面中，在浏览器端执行。而TypeScript 是JavaScript 的超集，即包含JavaScript 的所有元素，能运行JavaScript 的代码，并扩展了JavaScript 的语法。相比于JavaScript ，它还增加了静态类型、类、模块、接口和类型注解方面的功能，更易于大项目的开发。

经过查阅资料，TypeScript 相比于JavaScript 的优势总结为以下几点:

1.便于开发人员做注释。
2.能帮助开发人员检测出错误并修改。
3.TypeScript工具使重构更变的容易、快捷。
4.TypeScript 引入了 JavaScript 中没有的“类”概念。
5.TypeScript 中引入了模块的概念，可以把声明、数据、函数和类封装在模块中。
6.。类型安全功能能在编码期间检测错误，这为开发人员创建了一个更高效的编码和调试过



## ts和tsx区别

tsx大家默认含模板代码



使用`.ts`纯TS文件

使用`.tsx`了含有JSX文件



例如，一个 React 组件应该是`.tsx`，但是一个包含辅助函数的文件应该是`.ts`















