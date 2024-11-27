# Plugin_ComfyUI_开发

首先，我们需要了解ComfyUI的自定义节点的开发，以及可以作为典型demo的开源插件

## 参考资料

- 官方教程/文档
  - [github - 官方开发案例](https://github.com/comfyanonymous/ComfyUI/blob/master/script_examples/basic_api_example.py)
  - [官方文档](https://docs.comfy.org/get_started/introduction)
    - [官方文档 - 自定义节点](https://docs.comfy.org/essentials/custom_node_overview) (**推荐**)
- 教程调研：
  - [在5分钟内创建自定义节点！（ComfyUI自定义节点入门指南）](https://quail.ink/op7418/p/create-custom-node-in-5-minutes-comfyui-custom-node-getting-started-guide)
  - [一份ComfyUI 自定义节点指南](https://developer.volcengine.com/articles/7399549896778317833)
  - [手把手教你写COMFYUI 节点，自定义comfyui节点，封装comfyui插件](https://blog.csdn.net/qq_45957132/article/details/135916799)
  - [ComfyUI自定义节点开发](http://www.hubwiz.com/blog/create-custom-nodes-in-comfyui/)
  - [创建 ComfyUI 自定义节点的基本指南](https://blog.csdn.net/jjs15259655776/article/details/140318584)
- 优秀学习用开源demo：
  - ……

## 杂项 - 对比其他插件开发

其实大部分js插件只有客户端插件，像这里分客户端插件和服务端插件这种行为，很少。
和VuePress插件很像，VuePress插件也有这样的区分。

例如：

- VuePress的服务端插件 (nodejs)
  - Markdown-it类别插件；细分为parse阶段和render阶段的插件
  - defineClientConfig类别；细分为name、setup、slots等
- VuePress的客户端插件 (client)
  - defineUserConfig的钩子；细分为onInitialized、onGenerated、onPrepared、onWatched等

不过VuePress插件那边是两端都是用ts/js写的，而comfyui则是客户端用js、服务端用的python




