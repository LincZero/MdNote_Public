---
type: comfyui
---
# ComfyUI_ProjectNote_README

## 该文件夹下只看到此文件？其他文件无法显示？

注意，该项目文件夹主要是Comfyui导出的.json文件

- 如在 Obsidian 环境，识别和打开json文件需要借助插件 NodeFlow
- 如在 VuePress 环境，**识别和打开json文件的插件正在开发中**，暂不支持

## 学习与笔记方式

学习时多用注释节点

然后使用新版UI的内部工作流保存工具（无需导出），命好名。通过这种方式的保存，是进入到 “工作流管理器中”，对应路径：`软件安装路径/ComfyUI/user/default/workflows`
（也许可以设置该文件路径的位置，直接保存到ob中，但我没研究）
%%`H:\Soft\SoftDev\Plane\ComfyUI_windows_portable\ComfyUI\user\default\workflows`%%

还有一个类似的路径：`软件安装路径/workflow.json`，但这个路径保存的应该是那些使用拖拽方式放进去的工作流，不要弄混

## 学习方式扩展

因为这里是单文件项目管理，且源码纯文本，用笔记方式管理还是方便的

单文件编程项目也可以，但多文件项目或有多文件依赖 (又没有单文件依赖说明的) 一般不建议

只是后缀可能有所约束
