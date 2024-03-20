# Command 命令行相关

# 目录

[TOC]

# bat

```
rn *.jpg *.png // 批量修改后缀
```

# CMD

## About User

| 命令  | 说明 |
| ----- | ---- |
| cd /d |      |
| help  |      |
| dir   |      |
| tree  |      |

## About Web

| 命令          | 说明 |
| ------------- | ---- |
| ipconfig /all |      |
| ping          |      |
| ssh           |      |
| ftp           |      |

## About Folder

| 命令            | 说明     |
| --------------- | -------- |
| mkdir NewFolder | 创建目录 |
| rmdir NewFolder | 删除目录 |

## Windows环境变量

> 计算机属性(系统) > 高级系统设置(系统属性)
>
> \> 高级 > 环境变量 > Path包

# 运行

## 常用工具

|指令|说明|
| --- | --- |
|calc|计算器|
|cmd|命令提示行|
|powershell|终端|
|control|控制面板|
|notepad|记事本|
|snippingtool|截图工具|
|stikynot|便签|
|taskmgr|任务管理器|
|explorer|资源管理器|

## ms系列

|指令|说明|
| --- | --- |
|mspaint|画图|
|mstsc|远程桌面|

## 搞事常用

|指令|说明|
| --- | --- |
|regedit|注册表|
|services.msc|服务|
|fsmgmt.msc|共享文件夹|

## 其他

|指令|说明|
| --- | --- |
|winver|关于windows版本|

# HackNet【杂记】

## 命令列表-1/3页：

```
scp [filename] [OPTIONAL: destination]
```

从远程计算机复制文件[ filename至指定本地文件夹U/bin为就认

```
scan
```

在已连接计算机上扫描链接并加入服务器地图

```
ps
```

列出正在运行的程序以及它们的PIDs

```
kill [PID]
```

Kills Process number [PID]

```
connect [ip]
```

连接到外部计算机

```
disconnect
```

终止当前连接ALT:"dc“

## 命令列表-2/3页：

```
probe/nmap
```

扫描已连接计算机的活动端口及保安级别

```
exe
```

列出所有可用可执行文件在local/bin目录/文件夹(包括隐藏和嵌入式可执行文件)

```
openCDTray
```

打开已连接计算机的CD托盘

```
closeCDTray
```

关闭已连接计算机的cD托盘

```
reboot [OPTIONAL: -i]
```

重启已连接计算机。使用-i 选项以直接重启

```
replace [filename] "target" "replacement"
```

要替换的文本替换文件中的目标文本

```
analyze
```

对目标计算机的防火墙执行分析

```
solve [FIREWALL SOLUTION]
```

试图解决目标计算机的防火墙以允许UDP流量

## 命令列表-3/3页：

```
login
```

要求用户名及密码以登录已连接系统

```
upload [LOCAL FILE PATH]
```

上传在本地计算机上指定的文件到当前连接的目录

```
addNote [NOTE]
```

添加笔记

```
append [FILENAMEl [DATA]
```

把包台DATA]的行添加到 FILENAME]中

```
shell
```

Opens a remote acccss shell on target machine with Proxy overload andiE trap capabilities

## 基础类

```
help [PAGE NUMBER]
```

显示命令所捐定的页面

```
clear
```

清除终端

```
ls
```

Lists all files in current directory

```
cd [foldcrnamc]
```

移动当前目录至指定文件夹

```
mv [FILE] [DESTINATION]
```

移动或重命名 [FILE] 至 [DESTINATION]，(i c: mv hi. txt. /bin/hi. txt)

```
rm [filename (or use* for all files in folder)]
```

删除指定文件

```
cat [filename]
```

显示文件内容





































