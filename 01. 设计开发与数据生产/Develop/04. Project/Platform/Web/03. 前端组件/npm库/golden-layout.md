# Golden-layout

## 简概

### 资料

- 官方文档：https://golden-layout.github.io/golden-layout/ 或 https://golden-layout.com/docs/（过时）
- 官网demo：https://golden-layout.com/（过时）
- github：https://github.com/golden-layout/golden-layout
- npm：https://www.npmjs.com/package/golden-layout
- 协同Vue/Angular等框架的方法：https://golden-layout.github.io/golden-layout/frameworks/
    https://github.com/emedware/vue-golden-layout（只能Vue2）
    https://github.com/chyj4747/vue3-golden-layout-virtualcomponent/blob/master/README-CN.md（Vue3，似乎不可用）
    https://github.com/emedware/v3-gl-ext（Vue3，用的golden-layout而非vue-golden-layout）

### 作用

Golden Layout 是一个 Javascript 布局管理器，它使您能够在网页中布局组件并通过拖放重新排列它们。

重要提示：这是主要的Golden Layout网站。另一个 Golden Layout 网站是 https://golden-layout.com。该其他网站描述了 Golden Layout 的版本  1。 https://golden-layout.com 上的信息可能有助于初步了解黄金布局，但请注意，它现已过时。

### 特点

- 原生弹出窗口
- 触摸支持
- 支持Angular、Vue等应用框架
- 虚拟组件
- 全面的API
- 加载和保存布局
- 焦点组件
- 完全主题化
- 适用于现代浏览器（Firefox、Chrome）
- 响应式设计

## 安装/使用

库

```shell
npm i golden-layout
```

### 编译

源码

```
clone https://github.com/golden-layout/golden-layout
cd ..
npm install
npm run build
```

您可以构建并启动 `apitest` （演示）应用程序以查看运行中的库

- `npm run apitest:build` 来构建它
- `npm run apitest:serve` 构建并启动开发服务器

### 构建单文件包

我们提供不同类型的单文件包，以便在没有工具链的情况下更轻松地使用。为此，请运行 `npm run build:bundles` ，然后在 `dist/bundle/` 中找到捆绑的文件。默认情况下不会构建 Bundle，也不包含在 NPM 包中，我们建议大家通过 NPM 和 webpack 使用该库。

### 调试

`apitest` 应用程序可用于调试黄金布局库。其 `webpack` 配置将导入 Golden Layout 库源映射，允许调试器单步执行库源代码并放置**断点**。

如果您希望使用其他应用程序测试该库，您可以链接到 Golden Layout 存储库，而无需从 NPM 将其安装到应用程序中。这是通过 `npm link` 命令完成的。使用以下步骤：

1. 从黄金布局源存储库顶级文件夹中的 shell 运行 `npm link` 。
2. 从应用程序顶级文件夹中的 shell 运行 `npm link golden-layout` 。

然后，您的应用程序将使用 Golden Layout 存储库 `dist` 子文件夹中的发行版。如果您希望对黄金布局库进行更改，则需要运行 `build:api` 来重新生成 `dist` 文件夹。

## 学习

### 资料

以下信息源可用于学习如何使用黄金布局

- https://golden-layout.com 记录了 Golden Layout 的第 1 版。虽然版本 2 中进行了实质性更改，但仍然可以使用此网站来初步了解 Golden Layout。
- ReadMe 文件
- CodePen examples CodePen 示例：https://codepen.io/pbklink/pen/dyWJNNm，一个基本示例

### 结构

黄金布局对象的结构由其 `LayoutManager` 对象和定义布局本身的 `ContentItem` 对象组成。

有关详细信息，请参阅 [结构](https://golden-layout.github.io/golden-layout/structure/)

### 绑定组件

黄金布局绑定到组件，然后控制它们的位置、大小和可见性（定位），以便它们适合布局。黄金布局可以通过多种不同的方式绑定到组件。最简单的方法是注册一个组件类型，然后在组件的配置中指定该组件类型。

有关黄金布局组件绑定如何工作的完整说明，请参阅 [绑定组件](https://golden-layout.github.io/golden-layout/binding-components/)

### 框架

Golden Layout 旨在与 Angular 和 Vue 等 JavaScript 应用程序框架配合使用。通常，这些类型的框架用它们自己的组件包装  HTML 元素。应用程序不是 HTML 元素树，而是框架组件树，每个框架组件都包装一个 HTML 元素。

为了支持这些框架，Golden Layout 实现了“虚拟组件”。这允许框架组件嵌入到黄金布局中，而无需使用高级框架技术来允许相关框架组件HTML元素显示在布局中。

详细信息，请参阅 [框架](https://golden-layout.github.io/golden-layout/frameworks/)

### 调整组件尺寸

在布局结构中，需要指定 `RowOrColumn` 内容项及其子项的大小

详情见 [调整组件尺寸](https://golden-layout.github.io/golden-layout/sizing-components/)

### 组件焦点

组件可以有焦点。这类似于具有焦点的 HTML 元素。任何时候只有一个组件可以获得焦点

详见 [组件焦点](https://golden-layout.github.io/golden-layout/component-focus/)

### 位置选择器

LocationSelectors 根据父级和索引指定组件的位置。以编程方式添加组件时可以使用它们

详见 [位置选择器](https://golden-layout.github.io/golden-layout/location-selectors/)

### 弹出窗口

布局中的组件可以“弹出”到单独的浏览器窗口中。然后可以将其与主布局分开查看

详见 [弹出窗口](https://golden-layout.github.io/golden-layout/popouts/)































