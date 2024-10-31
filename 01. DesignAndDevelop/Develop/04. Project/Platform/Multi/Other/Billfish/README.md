# Billfish

仅进行软件分析

## 资源文件夹

首先要将文件夹选项设置一下：

1. 显示隐藏的文件、文件夹和驱动器
2. 不隐藏受保护的操作系统文件(推荐)

然后就能在资源文件夹中看到有隐藏文件

（以我自己的图片库为例，我顺便把大小列出来了，方便查看其重要程度）

[list2dt]

- < folderName,  size,  description
- .bf/,  8.67GB， 标签、数据库、缩略图等配置，至于日志等配置在C盘
  - .backup/,  142MB， 看起来是备份文件夹
	  - backup.json
	  - billfish\_backup\_~.db
	  - billfish\_upgrade\_~.db
  - .preview/,  8.18GB,  缩略图，存放策略和tencent有点像但没他那个路径那么恶心
	  - 00~ff/,  ,  共256个文件夹，这里应该是使用图片计算hash后分别存放，话说我看到很多重复图片都放一起了
		  - xxx.small.webp
  - .recycle/,  189MB,  这个是回收站
  - .recycle2/,  0
  - .temp/,  80.2MB
	  - plugin_cache/,  0
	  - ...,  ,  一些杂乱的临时文件
  - .ui_config/,  624B
	  - lib_info.json
	  - library.ini
	  - library_config.ini
  - billfish.db,  78.1MB,  应该是主要的数据库，后面看看能不能打开分析一下
  - folder.ico,  162KB,  仅图标
  - summary_v2.db， 17.5MB
- ...,  82.6GB,  主要存放资源，文件数为110,990个，应该也差不多
- desktop.ini,  208B,  修改文件夹图标的Windows通用文

### desktop.ini

这个就是用来修改文件夹图标的

```ini
[.ShellClassInfo]
IconFile=.bf/folder.ico
IconIndex=0
[ViewState]
Mode=
Vid=
FolderType=Generic
```

## Eagle的做法

Eagle 备受 Billfish 用户吐槽的一点就是他的库：

![](assets/Pasted%20image%2020240809000723.png)



