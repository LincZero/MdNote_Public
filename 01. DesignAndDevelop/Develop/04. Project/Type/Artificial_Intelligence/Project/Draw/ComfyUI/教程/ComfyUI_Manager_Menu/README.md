# ComfyUI_Manager_Menu_README

## 介绍

repo： github.com/ltdrdata/ComfyUI-Manager

作用：

在前面的 “节点” 一章中，我们介绍了节点的安装方式 —— 需要在 `ComfyUI/custom_nodes` 文件夹下去clone对应节点的仓库。但这有些麻烦了，于是就有了这个工具，能用于方便地管理 ComfyUI 的节点

注意：

这玩意其实也是一个 “节点”，但提供了一系列下载、更新、管理其他自定义节点乃至 ComfyUI 本体功能

## 设置面板

- 左侧部分
  - Preview method 预览方法
    enum:
    - None (very fast, default)
    - Auto (采样器实时预览过程)
    - TAESD (slow)
    - Latent2RGB (fast)
- 中间部分
  - Install Custom Nodes (安装自定义节点）
    会显示一个包含几乎所有开发者开发的自定义节点列表（应该是从Github中爬的？）
    可以搜索、安装。本质还是在命令行执行clone的过程
    安装完需要重启，提供了快速重启的按钮
  - Install Missing Custom Nodes (安装缺失的节点)
  - 安装模型
  - 通过 Git URL 安装
  - 更新全部
  - 更新 ComfyUI
  - 检查更新
- 右侧部分
  - 社区手册
  - Workflow Gallery
  - 第三方节点信息

