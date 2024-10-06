# README_HyperV

优势：

- 我最开始接触的是VMware
- 后来为了Vagrant选择了VirtualBox (Vagrant也支持VMware，但对VirtualBox支持最好，况且这时我是弄Linux虚拟机，VM很多功能用不上)
- 再后来搞AI需要显卡直通虚拟机尝试使用HyperV (其他也有，但弄起来似乎麻烦点)

参考：[最强虚拟机！ Hyper-V 显卡直通教程，vGPU虚拟化，用途广，速度贼快！支持秒开！| 零度解说](https://www.bilibili.com/video/BV1Fu41177Xj)

## 流程 - 安装

1. 开启Hyper-V

`Win+I` > 应用 > 可选功能 > 更多Windows功能 > 勾选Hyper-V以及两个子项、勾选虚拟机平台
（如果没有这两选项，Windows版本不对或没激活）

如果中间缺失某个环节，使用另一个入口：
`Win+I` > 搜索并进入 `控制面板` > 程序 > 启用或关闭Windows功能 > 勾选指定项

然后可能会要你重启电脑

2. 使用Hyper-V

`Win+S` > 搜索并进入 `Hyper-V管理器`

## 流程 - 创建

软件面板左侧选中主机 > 右侧操作面板 > 新建 > 虚拟机 >

根据引导一步一步填写资料：虚拟机名称、位置、引导方式、虚拟内存 是否动态内存、虚拟硬盘、ISO文件

## 我的Vagrant

最新版的还得去翻Vagrant笔记，然后把里面的 `config.vm.provider` 修改一下

```python
# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  # 镜像设置。这里使用了镜像。若链接失效则到该链接更新:
  # https://mirrors.tuna.tsinghua.edu.cn/ubuntu-cloud-images/jammy/
  config.vm.box = "ubuntu/jammy64"
  config.vm.box_url = "https://mirrors.tuna.tsinghua.edu.cn/ubuntu-cloud-images/jammy/20240912/jammy-server-cloudimg-amd64-vagrant.box"

  # 设置内存和CPU数量等
  config.vm.network "private_network", ip: "192.168.56.2"
  config.vm.provider "..." do |vb|
    ...
  end

  。。。
  。。。
end
```

