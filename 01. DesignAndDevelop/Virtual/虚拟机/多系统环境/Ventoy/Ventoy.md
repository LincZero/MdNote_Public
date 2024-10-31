# Ventoy

# 目录

# Ventoy

官网：https://www.ventoy.net/cn/index.html

## 介绍

官网介绍：

- 定位

  - 简单来说，Ventoy是一个制作可启动U盘的开源工具。

- 特点

  - 免格（第一次以后，想要第一次也不格就要用其他工具）

  - 轻松部署：有了Ventoy你就无需反复地格式化U盘，你只需要把 ISO/WIM/IMG/VHD(x)/EFI 等类型的文件直接拷贝到U盘里面就可以启动了，无需其他操作。

  - 多系统：你可以一次性拷贝很多个不同类型的镜像文件，Ventoy 会在启动时显示一个菜单来供你进行选择 (参见 [截图](https://www.ventoy.net/cn/screenshot.html))。 

    你还可以在 Ventoy 的界面中直接浏览并启动本地硬盘中的 ISO/WIM/IMG/VHD(x)/EFI 等类型的文件。

- 兼容性

  - Ventoy 安装之后，同一个U盘可以同时支持 x86 Legacy BIOS、IA32 UEFI、x86_64 UEFI、ARM64 UEFI 和 MIPS64EL UEFI 模式，同时还不影响U盘的日常使用。

  - Ventoy 支持大部分常见类型的操作系统 （Windows/WinPE/Linux/ChromeOS/Unix/VMware/Xen ...）

    目前已经测试了各类超过 **1100+** 个镜像文件([列表](https://www.ventoy.net/cn/isolist.html))。    支持 [distrowatch.com](http://distrowatch.com/dwres.php?resource=popularity) 网站上收录的 **90%+** 的操作系统([列表](https://www.ventoy.net/cn/distrowatch.html))。

- 开源

  - Ventoy 是开源免费的软件。为了 Ventoy 更好的、可持续的发展，Ventoy 提供付费订阅服务。参考 [说明](https://www.ventoy.net/cn/doc_subscription.html)

- 额外提供实用功能

  - Ventoy Browser
    - Ventoy 除了可以启动U盘中的文件以外，还可以浏览、启动本地硬盘、移动硬盘中的 ISO/WIM/IMG/VHD(x)/EFI 等类型的文件。[说明](https://www.ventoy.net/cn/doc_browser.html)
  - VentoyPlugson
    - Ventoy 通过各种插件提供了非常多的功能。同时还提供了一个图形化插件配置器 —— [VentoyPlugson](https://www.ventoy.net/cn/plugin_plugson.html) 方便使用。
  - iVentoy
    -   如果你有通过网络安装操作系统（PXE）的需求，欢迎使用作者的新项目——iVentoy   https://www.iventoy.com 

- 其他特点

  - 100% 开源 [(许可证)](https://www.ventoy.net/cn/doc_license.html) 
  - 使用简单 [(使用说明)](https://www.ventoy.net/cn/doc_start.html)  
  - 快速 (拷贝文件有多快就有多快) 
  - 可以安装在 U盘/本地硬盘/SSD/NVMe/SD卡等设备上 
  - 直接从 ISO/WIM/IMG/VHD(x)/EFI 文件启动，无需解开 
  - 支持浏览并启动本地硬盘上的 ISO/WIM/IMG/VHD(x)/EFI 文件 [说明](https://www.ventoy.net/cn/doc_vlnk.html)
  - ISO/WIM/IMG/VHD(x)/EFI 文件在磁盘上无需连续 
  - 支持MBR和GPT分区格式
  - 同时支持 x86 Legacy BIOS 以及 IA32/x86_64/ARM64/MIPS64 UEFI
  - UEFI 模式支持安全启动 (Secure Boot) [说明](https://www.ventoy.net/cn/doc_secure.html)
  - 支持数据持久化 [说明](https://www.ventoy.net/cn/plugin_persistence.html) 
  - 支持 Windows 系统的自动安装部署 [说明](https://www.ventoy.net/cn/plugin_autoinstall.html)
  - 支持 Linux 系统的自动安装部署 [说明](https://www.ventoy.net/cn/plugin_autoinstall.html)
  - Windows/Linux 自动安装脚本中支持变量扩展 [说明](https://www.ventoy.net/cn/plugin_autoinstall.html)
  - 镜像分区支持 FAT32/exFAT/NTFS/UDF/XFS/Ext2(3)(4) 文件系统
  - 支持超过4GB的 ISO 文件 

  - 支持菜单别名、菜单提示信息显示
  - 支持启动密码保护
  - 保留ISO原始的启动菜单风格(Legacy & UEFI)
  - 支持大部分常见操作系统, 已测试 1100+ 个ISO文件 
  - 不仅仅是能启动ISO文件，而是支持启动后完整的安装过程
  - 菜单可以在列表模式和目录树模式之间随时切换 [说明](https://www.ventoy.net/cn/doc_treeview.html)
  - 提出 "Ventoy Compatible" 概念 
  - 支持插件扩展，提供图形化插件配置器
  - Linux vDisk(vhd/vdi/raw...) 启动解决方案 [说明](https://www.ventoy.net/cn/plugin_vtoyboot.html)
  - 支持向运行环境中注入文件 [说明](https://www.ventoy.net/cn/plugin_injection.html)
  - 支持动态替换ISO文件中的原始启动配置文件 [说明](https://www.ventoy.net/cn/plugin_bootconf_replace.html)
  - 高度可定制化的主题风格和菜单 [说明](https://www.ventoy.net/cn/plugin_theme.html)
  - U盘硬件写保护开启时不影响基本功能
  - 不影响U盘日常普通使用
  - 版本升级时数据不会丢失
  - 无需跟随操作系统升级而升级Ventoy

## 0