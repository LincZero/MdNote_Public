# pnpm monorepo

参考：

- [基于pnpm workspace，超清楚简单的monorepo项目创建与基础演示](https://www.bilibili.com/video/BV1hp4y1L7Mr)，10min
- [使用 pnpm workspace 管理 monorepo](https://www.bilibili.com/video/BV1qg4y157dv)，40min 有字幕

## 介绍 pnpm

- 快速：pnpm 会将包缓存到本地，减少二次安装需要的时间
- 节省磁盘空间：它会把包软链到项目本地，不需要反复安装
- 节省网络带宽：同样的道理
- 更好的依赖处理逻辑

## 介绍 monorepo

### 介绍

在一个代码仓库中管理多个不同的项目

举个例子

- Webpack 及其插件
- 同时包含前后端的大型项目
- Chrome 扩展等有多个入口的项目

### 使用 monorepo 的优劣

使用 Monorepo 的优势

- 便于管理多个互相依赖的项目
- 便于团队共享知识库
- 减少项目管理的成本

使用 Monorepo 的劣势

- 版本管理混乱
- 代码质量参差不齐，且互相影响
- 技术栈升级困难
- 难以进行权限管理

浅尝 Monorepo
https://blog.meathill.com/tech/some-basic-experience-about-monorepo.html

### 什么时候使用 monorepo

- 充分条件
  - 多个项目互相依赖
  - 功能、版本之间存在强关联
  - 项目中存在多个编译入口，且构建条件存在差异
- 次要条件
  - 希望在团队中共享知识
  - 降低项目管理的成本

### 为什么使用 pnpm 管理 monorepo

为什么要用pnpm来进行mono管理

- 速度快
- 磁盘占用少
- 项目依赖彼此独立、隔离
- 有各种命令方便操作

其他例如yaml等，似乎不是很好

## 项目实操

### 项目结构

- /api/
- /packages/
  - background/
  - content/
  - core/： 核心
  - popup/： 单页面应用
  - global.d.ts
- /supabase/
- /...

### 创建 pnpm-workspace.yaml

```yml
packages:
  - 'packages/*'
  - 'api'
  - 'supabase'
```

### 互相引用

- /api/
- /packages/
  - background/
  - content/
  - core/： 核心
    ```json
    // package.json
    {
        "name": "@wooka/core"
    }
    ```
  - popup/： 单页面应用
    ```json
    // package.json
    {
        "name": "@wooka/popup",
        // ...
        "dependencies": {
            "@wooka/core": "workspace:*" // 告诉pnpm使用工作空间里面的的另一个模块
        }
    }
    ```
  - global.d.ts
- /supabase/
- /...

### 安装依赖

```bash
$ cd packages/popup
$ pnpm i
$ pnpm i lodash
$ ll node_modules/@wooka/core # 这时会发现实际上这是一个软链接
```

## 常见问题解决

基本原则：各司其职

- pnpm：只负责生成依赖目录 node modules
- 脚手架：负责在工作目录内构建开发环境、打包项目
- lock 文件：负责记录依赖版本号
- package.json：负责记录依赖和脚本

FAQ

- 需要每个项目文件夹配置单独的入口文件么?
  - 是的，需要。每个项目文件夹都是独立的项目
- 怎么安装依赖?
  - 我建议在每个项目文件夹下面执行pnpm i
- 怎么引用依赖?
  - 该怎么引用就怎么应用。
- 怎么打包?怎么启动开发环境?
  - 对每个项目而言，跟以前一样。对整个项目，你可以自己写脚本
- 单个项目需要发布到NPM 么?
  - 不需要。对同一个 monorepo 下的项目，它们就相当于已经发布了
- 怎么处理端口?
  - 以前怎么处理，现在还是。workspace 并不会帮你处理端口。

Monorepo的好处在于自身
pnpm 只是帮我们管理

扩展阅读：工作空间 (Workspace) 的pnpm官方文档

## 答疑











