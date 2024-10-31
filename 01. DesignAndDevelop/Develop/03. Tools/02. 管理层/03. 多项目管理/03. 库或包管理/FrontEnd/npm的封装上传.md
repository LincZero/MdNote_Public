# npm的封装上传

## 简单流程

参考：https://juejin.cn/post/7017706309709463583

### (1) 注册npm

首先需要在npm官网注册帐号并登录，官网为 https://www.npmjs.com/

此步略

### (2) 准备本地库

#### 项目文件夹

创建文件夹，我命名为firstnpm。

#### 初始化npm

然后执行 `npm init -y`

- 其中`-y`表示，遇到选择都选择yes
- 当然也可以不 `-y`，那么选项：
  ```shell
  $ npm init
  package name: ("folderName")  # 创建的文件名，也是发布之后的报名。在npm中必须唯一
  version: (1.0.0)              # 版本号  
  description:                  # 描述
  entry point: (index.js)       # 暴露文件
  test command: 
  git repository: 
  keywords: 
  author: 
  license: (ISC) GPL3
  About to write to ...\package.json: {
      ...                       # 执行完后，会生成一个 `package.json` 文件
  }                             # 里面的内容就是刚刚交互式填的内容
  Is this OK? (yes)
  ```
- 不过这种交互式指引，哪怕不对也可以后期轻松修改，前期 `-y` 其实就好

#### 准备依赖包 (可选)

如果在我们包里面需要引入别的包

例如：引入一个 lodash 包，执行 `npm init lodash -S` -S表示在生产环境中引入并写入package.josn：

[# package.josn]

```bash
{
  "dependencies": {
    "lodash": "^4.17.21"
  }
}
```

#### 准备入口函数的暴露

用 Comman JS 暴露，例如：

[# index.js]

```js
const _ = require("loadsh");
function myChunk(arr) {
  return _.chunk(arr,2)
};
module.exports = myChunk
```

### (3) 上传npm

```shell
$ npm adduser  # 先登录，在vscode里他会让我打开浏览器来登录
Username: ...
Password: ...

$ npm publish  # 上传 (注意不要重名、npm账号可能需要邮箱验证)
```

当上传成功后，可以在npm中搜索到

## TypeScript 发布

参考：[手把手教你发布兼容TS的JS库到npmjs上](https://cloud.tencent.com/developer/article/2192280)

### (1) 编译为js、及提供类型文件

如果项目是基于TS的话，虽然可以使用，但是会提示 无法找到模块“nmgwap-time-formatting”的声明文件。那接下来继续改造，使其兼容TS

[# package.json]

```typescript
{
  "main": "dist/index.js",
  "types": "dist/index.d.ts", // 指示.d.ts的位置
  "type": "module",
  "scripts": {
    "build": "tsc" // tsc是一个typescript编译器
                   // 如果找不到，可全局安装：npm install -g typescript，
                   // 然后验证：tsc --version
                   // 有的资源让写 "tsc -p ."，就是让把生成结果放在本地路径的意思
                   // 执行该命令后，所有ts文件都会被编译成三个文件：.d.ts、.js、.js.map
    "prepublishOnly": "npm run build" // 这个可以在运行publish之前自动执行，不用每次自己build那么麻烦
  }
}
```

注意 type 的内容

- `type": "module"`：表示该包是 ES 模块
  - 引入方式：`import { member } from 'module-name';`
- `type": "commonjs"`：表示该包是 CommonJS 模块
  - 引入方式：`const module = require('module-name');`

### (2) 编写 tsconfig.js

有时可能编译失败，我们需要额外添加 tsconfig.js 文件。并且这个文件还会告诉我们编译后的文件放在哪

[# tsconfig.js]

```json
{
  "compilerOptions": {
    "target": "ESNext",
    "module": "ESNext", // commonjs, ESNext
    "lib": [
      "DOM",
      "ES5",
      "ES6",
      "ES7",
      "dom.iterable"
    ],
    "declaration": true,
    "sourceMap": true,
    "rootDir": "./src",    // 要编译的.ts位置
    "outDir": "./dist",    // .ts编译输出的.js位置
    // "": "", // .ts编译输出的.d.ts位置
    // "strict": true,
    "esModuleInterop": true
  },
  "include": [
    "**/*.ts"
  ]
}
```

注意 module 的内容：

- 有效值: "CommonJS", "AMD", "System", "UMD", "ES6", "ES2015", "ES2020", "ESNext", "None", "ES2022", "Node16", "NodeNext", "Preserve"

复习一下：

| 特点   | CommonJS (require)                       | ES 模块 (import from)                     |
| ---- | ---------------------------------------- | --------------------------------------- |
| 加载时机 | 运行时                                      | 编译时                                     |
| 模块类型 | 对象                                       | 代码块                                     |
| 语法   | `const module = require('module-name');` | `import { member } from 'module-name';` |
| 导出方式 | `module.exports = value;`                | `export const value = ...;`             |
| 循环依赖 | 支持                                       | 不支持直接循环依赖                               |
| 动态导入 | 支持                                       | 支持 `import()`                           |

### (3) 编写 .gitignore 或 .npmignore

如果是ts编译后，理应上传.js和.d.ts就足够了，上传ts源文件其实没什么必要。特别是如果你需要必源.ts的情况下

[# .npmignore]

```ts
*.ts
// 或者如果是某个特定的文件夹
src/
```

注意这两个文件不要冲突

## ESM && CJS

前面是ESM写法，如果要改成CJS：

- package.json，type: module/commonjs
- tsconfig.json，module: "ESNext/CommonJS"

## 纯ts库

https://www.npmjs.com/package/@ruan-cat/utils

## 【扩展】建设自己的npm私库

恰如可以自己创建自己的git私库 (如gitlab)，npm也可以创建自己的npm私库。

原理应该都差不多，略

## (仅个人吐槽)

> 吐槽：
> 
> 配置项太脑壳疼了，我是很久以前vue2时代学的前端，webpack是我当时认为最恶心的东西没有之一，给我搞吐了
> 现在重新搞……一堆esbuild、rollup、tsup、vite搞得我再次头痛
> 
> 个人相关项目：见我基于vuepress-theme-hope的个人网站去引用自制插件markdown-it-any-block的过程

群里大佬给的建议：

> 纯ts包，见 https://www.npmjs.com/package/@ruan-cat/utils
> 写ts发布js，见 https://github.com/lint-md/prettier-plugin
> 
> 库不建议用tsc打包，简单点的场景用tsup
> tsup比较方便的一点就是会给你自动设后缀名，然后你只要设package.json就行了

