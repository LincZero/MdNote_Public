# JavaScript 扩展

## 扩展舒适的客户端

Comfy 可以通过扩展机制进行修改。要添加扩展，您需要：

- 从 Python 模块导出 `WEB_DIRECTORY`
- 将一个或多个 `.js` 文件放入该目录
- 用 `app.registerExtension` 注册您的扩展

这三个步骤如下。一旦您知道如何添加扩展，请查看可以调用您代码的 [钩子](https://docs.comfy.org/essentials/javascript_hooks)、您可能需要的各种 [Comfy 对象](https://docs.comfy.org/essentials/javascript_objects_and_hijacking) 的描述，或者直接跳转到一些 [示例代码片段](https://docs.comfy.org/essentials/javascript_examples)。

### 导出 `WEB_DIRECTORY`

Comfy Web 客户端可以通过在自定义节点目录中创建一个子目录（通常称为 `js`）并导出 `WEB_DIRECTORY` 来扩展 - 因此您的 `__init_.py` 将包含类似以下内容的内容：

```python
WEB_DIRECTORY = "./js"
__all__ = ["NODE_CLASS_MAPPINGS", "NODE_DISPLAY_NAME_MAPPINGS", "WEB_DIRECTORY"]
```

### 包含 `.js` 文件

> [!tip]
> 所有 `Javascript.js` 文件将在 Comfy 网页加载时由浏览器加载。您不需要指定扩展程序所在的文件。

*仅* `.js` 文件会添加到网页。其他资源（如 `.css` 文件）可以在 `extensions/custom_node_subfolder/the_file.css` 中访问并以编程方式添加

> [!warning]
> 该路径*不*包含子文件夹的名称。`WEB_DIRECTORY` 的值由服务器插入

### 注册扩展

扩展的基本结构如下：导入主 Comfy `app` 对象，然后调用 `app.registerExtension`，传递一个包含唯一 `name` 的字典，以及由 Comfy 代码中的钩子调用的一个或多个函数

一个完整的、繁琐的、烦人的扩展可能看起来像这样：

```Javascript
import { app } from "../../scripts/app.js";
app.registerExtension({ 
	name: "a.unique.name.for.a.useless.extension",
	async setup() { 
		alert("Setup complete!")
	},
})
```

