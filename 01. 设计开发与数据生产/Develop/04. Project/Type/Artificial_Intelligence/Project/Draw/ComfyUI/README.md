# ComfyUI

参考：

- 官方
  - [Github仓库](https://github.com/comfyanonymous/ComfyUI)
    - [安装部分](https://github.com/comfyanonymous/ComfyUI#installing)
  - [官网、安装方式](comfy.org)
- [秋葉aaaki大佬的空间](https://space.bilibili.com/12566101)
  - [【AI绘画】ComfyUI整合包发布！解压即用 一键启动 工作流版界面 秋叶整合包](https://www.bilibili.com/video/BV1Ew411776J/)
  - [【AI绘画】阿里云免费 一键ComfyUI！SVD (StableVideoDiffusion) 图生视频 工作流和教程](https://www.bilibili.com/video/BV1Tz421f7p9/)
- 其他
  - [CSDN - 在Ubuntu22.04上部署ComfyUI](https://blog.csdn.net/chengxuquan/article/details/136089175)
    (这里额外使用conda创建了虚拟环境，还弄了N卡驱动，预安装了cuda和cuDNN，基本使用tar包安装)
  - [ComfyUI部署流程](https://blog.csdn.net/u011450629/article/details/129813954)
    (这里另外安装了Pytorch)

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
- Jupyter
- 手动安装 (Windows、Linux)

运行方式

`python main.py`

## 细节

> "自 2024 年 8 月 15 日起，我们已过渡到新的前端，该前端现在托管在一个单独的存储库中：[ComfyUI Frontend](https://github.com/Comfy-Org/ComfyUI_frontend)。此存储库现在将编译后的 JS（来自 TS/Vue）托管在目录下`web/`。"

