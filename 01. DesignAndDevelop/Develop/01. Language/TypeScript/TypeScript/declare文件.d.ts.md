# TypeScript

# 目录

# declare文件.d.ts

参考：

- [【博客】TypeScript入门教程 # 声明文件](https://ts.xcatliu.com/basics/declaration-files.html)
- [【B站】【前端必备】原来 TS 中 declare 的作用是这样的！](https://www.bilibili.com/video/BV1794y1S7EK)
- [【简书】一文读懂TS的(.d.ts)文件](https://www.jianshu.com/p/cd875a4a6c15)
- [【知乎】TypeScript 中的 .d.ts 文件](https://zhuanlan.zhihu.com/p/394448926)



## declare 的作用是什么？

比如使用 JS-SDK 的接口

```tsx
wx.chooseImage({ // 但wx仍然会报错：找不到名称“wx”，因为typescript不认识这个全局变量
    ……
})
```

解决方法：declare声明，让typescript编译器认识这个全局变量

```tsx
declare var wx: any;
```



那么为什么像 JSON、Math、Object 这些全局变量？因为TS内部声明过了，在 `typescript/lib/lib.es5.d.ts`



## 小工具

https://www.typescriptlang.org/dt/search?search=jquery 直接搜索第三方库的声明文件（例如jquery），就可以npm加载，不用自己写了



## 举例

例如Obsidian插件开发中，你就会看到接口文件 obsidian.d.ts，里面就有一大堆的 `declare `

例如Obsidian插件 table-extended-master 中的 `ob.d.ts` 文件

```tsx
import "obsidian";

declare module "obsidian" {
  interface Vault {
    getConfig(key: string): unknown;
  }
  interface MarkdownView {
    printToPdf(): void;
  }
}

```



模块声明（2.0支持通配符声明）

```tsx
declare module "*.css" {
	const css: string;
    export default css;
}
declare module "*.jpg" {
    const src: string;
    export default src;
}
declare module "*.ttf" {
    const src: string;
    export default src;
}

// 否则：无法识别：
import css from "./file.css"		// 找不到模块“./file.css”或其相应的类型声明
import logo from "./abao.jpg"		// 找不到模块“./abao.jpg”或其相应的类型声明
```



















