---
create_time: 2024-10-08
---
# ComfyUI

## 相关链接资源

### 文档类

- 官方
  - [Github仓库](https://github.com/comfyanonymous/ComfyUI)
    - [安装部分](https://github.com/comfyanonymous/ComfyUI#installing)
  - [官网、安装方式](https://www.comfy.org/)
- [Comfyui-wiki](https://comfyui-wiki.com/zh-CN/)

### 安装部署类

- Nenly同学
  - [01. 入门](https://www.bilibili.com/video/BV1D7421N7xN)
  - [01.2 史诗级更新！ComfyUI“改头换面”](https://www.bilibili.com/video/BV1X8xFeCERn)，包含安装方式 (**官方版本，新UI安装版，选用**)
  - [配套笔记](https://gf66fxi6ji.feishu.cn/wiki/UzFfwaOx3iY3ZAksErvcBbrpnPb)
- [Comfyui-wiki - 如何在Linux上安装ComfyUI](https://comfyui-wiki.com/zh-CN/install/install-comfyui/install-comfyui-on-linux) (官方版本)
- [秋葉aaaki大佬的空间](https://space.bilibili.com/12566101) (整合包版本)
  - [【AI绘画】ComfyUI整合包发布！解压即用 一键启动 工作流版界面 秋叶整合包](https://www.bilibili.com/video/BV1Ew411776J/)
  - [【AI绘画】阿里云免费 一键ComfyUI！SVD (StableVideoDiffusion) 图生视频 工作流和教程](https://www.bilibili.com/video/BV1Tz421f7p9/)

- 其他
  - [CSDN - 在Ubuntu22.04上部署ComfyUI](https://blog.csdn.net/chengxuquan/article/details/136089175)
    (这里额外使用conda创建了虚拟环境，还弄了N卡驱动，预安装了cuda和cuDNN，基本使用tar包安装)
  - [ComfyUI部署流程](https://blog.csdn.net/u011450629/article/details/129813954)
    (这里另外安装了Pytorch)

### 教程类

见教程部分的README

### 资源类

#### 模型、工作流等

- 官方示例：https://comfyanonymous.github.io/ComfyUI_examples/ (虽然github url不是comfyui前缀，但似乎说是官方开发者的)
- Comfy UI Manager (插件)
- 国内：[eSheep](https://www.eshepp.com/app)、[AIGodLike](https://wwww.aigodlike.com)
- 国外：[Comfy Workflows](https://comfyworkflows.com)、[Openart.AI](https://openart.ai/workflows/home)、[ComfyICU](https://comfy.icu/)、[C站工作流分区](https://civitai.com/models)

#### 插件或节点

[视频](https://www.bilibili.com/video/BV1pZ421b7t7/) 中介绍的所有节点的仓库链接： 

- ComfyUI Manager： github.com/ltdrdata/ComfyUI-Manager
- ComfyUI汉化节点： github.com/AIGODLIKE/AIGODLIKE-COMFYUI-TRANSLATION
- ComfyUI提示词反推： github.com/pythongosssss/ComfyUI-WD14-Tagger
- Impact节点包： github.com/ltdrdata/ComfyUI-Impact-Pack
- Efficiency Nodes效率节点包： github.com/jags111/efficiency-nodes-comfyui
- 自定义脚本包（含提示词补全）： github.com/pythongosssss/ComfyUI-Custom-Scripts

更多没有介绍详细的节点：

- One Button Prompt（简易负面词）： github.com/AIrjen/OneButtonPrompt
- CR节点包： github.com/Suzie1/ComfyUI_Comfyroll_CustomNodes
- WAS节点套件： github.com/WASasquatch/was-node-suite-comfyui
- RG3节点包： github.com/rgthree/rgthree-comfy
- AnimateDiff Evolved： github.com/Kosinkadink/ComfyUI-AnimateDiff-Evolved
- IPAdapter Plus： github.com/cubiq/ComfyUI_IPAdapter_plus
- ReActor： github.com/Gourieff/comfyui-reactor-node
- Catcat： github.com/jw782cn/ComfyUI-Catcat
- ComfyPets： github.com/nathannlu/ComfyUI-Pets

## 秋叶视频笔记

ComfyUI 而非 SD-WebUI，SD看另一个笔记

缺点：

- 开源社区通病
- 极快的迭代速度、不兼容更新
- 国内 Github 访问不畅、节点难以安装
- ComfyUI 的官方打包方式可能导致安装问题

秋叶的整合包，试图解决这些问题

## 官方README

安装方式

- Windows
  - 预构建
  - 手动安装
- Jupyter
- 手动安装 (Windows、Linux)

运行方式

`python main.py`

### 前端开发

"自 2024 年 8 月 15 日起，我们已过渡到新的前端，该前端现在托管在一个单独的存储库中：[ComfyUI Frontend](https://github.com/Comfy-Org/ComfyUI_frontend)。此存储库现在将编译后的 JS（来自 TS/Vue）托管在目录下`web/`。"

#### 使用最新的前端

新前端现在是 ComfyUI 的默认前端。但请注意：

1. ComfyUI 主存储库中的前端每周更新一次。
2. 每日版本可在单独的前端存储库中获取。

要使用最新的前端版本：

1. 对于最新的每日版本，请使用以下命令行参数启动 ComfyUI：
    ```bash
    --front-end-version Comfy-Org/ComfyUI_frontend@latest
    ```
2. 对于特定版本，请将最新版本替换为所需的版本号：
    ```bash
    --front-end-version Comfy-Org/ComfyUI_frontend@1.2.2
    ```

这种方法使您可以轻松地在稳定的每周发布和前沿的每日更新之间切换，甚至可以在用于测试目的的特定版本之间切换。

#### 访问旧版前端

如果您出于任何原因需要使用旧版前端，可以使用以下命令行参数访问它：

```bash
--front-end-version Comfy-Org/ComfyUI_legacy_frontend@latest
```

这将使用 ComfyUI 旧版前端存储库中保存的旧版前端的快照。

#### 主要新增功能

1. 双击画布搜索优化
2. 设置面板优化
  - ComfyUI > Menu > 使用新版菜单 > Disable改为Top，感觉界面更现代化也更好用了！
