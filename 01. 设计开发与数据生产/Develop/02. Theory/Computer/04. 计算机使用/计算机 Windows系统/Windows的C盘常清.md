# Windows的C盘常清

# 目录

[toc]

# 如何自主分析

## 软件的分析 - 1

软件：推荐使用`TreeSizeFree`，免费软件，多语言（根据系统语言）

作用：分析文件内的所有文件夹以及文件的占用大小

下载：可到softonic中下载（纯净）：https://treesize.en.softonic.com/

使用注意项：系统隐藏文件需要以管理员身份运行`TreeSizeFree`，才能扫出来

​						扫其他盘无所谓，但扫C盘建议以管理员身份运行该软件

软件截图与语言选择：

<img src="Windows的C盘常清.assets/image-20201130124820351.png" alt="image-20201130124820351" style="zoom: 80%;" /><img src="Windows的C盘常清.assets/image-20201130124853520.png" alt="image-20201130124853520" style="zoom:80%;" />

## 软件的分析 - 2

使用其他软件也可以，例如`space sniffer`等，作用差不多，但我还是觉得`TreeSizeFree`好用

## 隐藏文件的查看

这里的显示是==不充分==的，只能看到一部分非操作系统文件相关的隐藏项目

![image-20201130124533023](Windows的C盘常清.assets/image-20201130124533023.png)

需要取选`隐藏受保护的操作系统文件`

![image-20201130125056649](Windows的C盘常清.assets/image-20201130125056649.png)

# 手动清理

## 永久性清理项

### 休眠文件（0~10+GB）

路径：C:\hiberfil.sys 
状态：系统的隐藏文件
占用：可达10+GB
内容：休眠文件
由来：系统
优化：不可直接删除、可设置不生成休眠文件

方法：

​	`powercfg -h -size 70`，可将这台计算机的 C:\Hiberfil.sys 的占用上限减小为内存大小的 70%

​	`powercfg -h off`，可关闭休眠功能，同时 Hiberfil.sys 文件也会自动删除，逆操作`powercfg -h on`

### 分页文件（10~几十GB）

路径：C:\pagefile.sys
状态：系统的隐藏文件
占用：10~几十GB
内容：虚拟内存的分页文件
由来：系统
优化：不可直接删除、可设置在其他盘符中，还可设置大小上限

## 需要偶尔清理项

### 蓝屏文件（0~10+GB）

路径：C:\Windows\LiveKernelReports
状态：管理员权限访问
占用：一般为空、或可达10+GB
内容：在正常情况下livekernelreports文件夹里面应该是空的，当电脑出现问题，比如最常见的“蓝屏”，在蓝屏之后就会生成相关的错误报告文件，即DMP文件
由来：系统
优化：可删文件，文件夹保留

### 软件临时文件（0~10+GB）

路径：C:\Users\A\AppData\Local\Temp
状态：普通
占用：10+GB
内容：存放软件的配置文件和临时文件的
由来：各类软件
优化：临时文件，可以全删了。注意：正在运行中的软件所对应的文件无法删除，跳过即可

### Installer目录（0~数G）

==（操作有风险，官方不建议。虽然我自己用没有问题，但声明我不承担任何责任，建议提前做好数据备份）==

路径：C:\Windows\Installer
状态：系统的隐藏文件夹
占用：我电脑2.7G左右，276个`.msi`文件就站2.55G（我看网上有的人甚至占了20+G）
内容：保存着所有基于Windows Installer安装的应用软件的注册信息
由来：系统
优化：**注意不能轻易删除，会导致软件无法正常恢复或运行**。但虽说不能删除所有文件，但里面有一些冗余的东西可以安全清理
具体方法详情见https://www.jianshu.com/p/20b3ac00fd7d（参考文章）

#### 微软软件


微软自己有提供软件，一开始是~~Windows Installer CleanUp Utility~~，后来提供了一个 [Program Install and Uninstall troubleshooter](https://link.jianshu.com?t=http%3A%2F%2Fsupport.microsoft.com%2Fmats%2FProgram_Install_and_Uninstall) 的新软件替代

修复无法安装或删除程序的问题
使用注意：不要都删了，否则可能就有麻烦了。
使用方法：在命令行，通过命令`msizap.exe G`可以删除一些孤儿文件：`C:>msizap.exe G`

#### wicleanup

简概：Windows Installer UnUsed Files Cleanup Tool（简称WICleanup）
软件主页：www.kztechs.com/wicleanup/（失效？）
下载主页：http://www.kztechs.com/wicleanup/wicleanup.zip（失效？）
下载地址：https://appnee.com/wicleanup/

使用：建议用cmd批量删除，不然GUI需要一个一个删。cd到对应路径，然后`WICleanupC.EXE -s`即可

### $Recycle.Bin与回收站（0~10+GB）

路径：C:\\\$Recycle.Bin
状态：系统的隐藏文件
占用：10+GB
内容：里面包含回收站，回收站：C:\\\$Recycle.Bin\回收站
由来：回收站
优化：清空回收站

---

补充：==回收站文件夹要放在最后一步来清理==，原因如下：

回收站原理：
回收站文件其实并不是在C盘的  而是每个盘里都有一个回收站 比如你有C D E F四个盘 那就是在C D E F每个盘里都有一个回收站  而那是隐藏的所以你看不到 删除的文件都在自己的盘下的回收站里 比如我删除D盘的文件 就会自动删除到D盘的回收站里  每个回收站的容量默认是所在盘的容量的10%（右键属性可以修改）
这也是为什么删除操作比跨盘复制文件要快得多
当然桌面上默认的“回收站”中的内容是统合了多个盘的回收站文件夹的内容

清C盘回收站：
当然我们在清C盘的时候当然不需要把广义上的回收站进行清空只需要清空C盘的回收站文件夹即可
（但好像右键清空回收站就只不是C盘的回收站了）
在清理前面的C盘文件时，C盘并不会真正意义上的减少
用TreeSize的时候会发现：
清理C盘其他文件时，TreeSize统计出来的文件占用在减少，但左下角显示的“剩余空间”却没有变大
刷新TreeSize重新扫描后才能扫描出C盘回收站文件
这时需要清理C盘回收站文件夹才能扩大剩余空间，这也是为什么回收站文件夹要放在最后一步清理

## 软件生成的文件，修改软件配置永久清除

### ZBrush默认（10+G）

路径：C:\Users\Public\Documents\ZBrushData2018\QuickSave
状态：普通
占用：10+G
由来：软件Zbrush，的QuickSave
优化：修改Zbrush的QuickSave路径（软件内没有修改选项，需要修改该路径上一层的ZBrushQuickSavePath.TXT配置文件）

## mkline方法

理论上可以清除Winodws Kits和SDKs

参考链接：https://liam.page/2018/12/10/mklink-in-Windows/

参考链接：https://blog.walterlv.com/post/problems-of-mklink.html

## 运行时占用，无需清理

### wireshark的运行时文件

路径：C:\Users\A\AppData\Local\Temp下的wireshark_WLAN_20200929102012_a32128.pcapng
状态：普通
占用：10+G
内容：wireshark软件捕获的分组
由来：软件wireshark
优化：无需。软件运行时产生的临时文件，关闭软件后消失

## 无法清理

### Microsoft SDKs

路径：C:\Program Files (x86)\Microsoft SDKs
状态：普通
占用：5.4G
内容：SDKs
由来：安装VS或其他IDE时安装
优化：无法。**注册表中有相当多的条目（至少在我的注册表中）指向该位置**，例如Unity3D和MSVS可能可能都用到该位置。至少移动他它会试卸载程序或依赖关系有点混乱
（mkline好像可以）

# 脚本清理

## bat脚本

自动化清理垃圾文件bat脚本：（未经实验）

```
@echo off
echo 正在清除系统垃圾文件，请稍等......
del /f /s /q %systemdrive%\*.tmp
del /f /s /q %systemdrive%\*._mp
del /f /s /q %systemdrive%\*.log
del /f /s /q %systemdrive%\*.gid
del /f /s /q %systemdrive%\*.chk
del /f /s /q %systemdrive%\*.old
del /f /s /q %systemdrive%\recycled\*.*
del /f /s /q %windir%\*.bak
del /f /s /q %windir%\prefetch\*.*
rd /s /q %windir%\temp & md %windir%\temp
del /f /q %userprofile%\cookies\*.*
del /f /q %userprofile%\recent\*.*
del /f /s /q "%userprofile%\Local Settings\Temporary Internet Files\*.*"
del /f /s /q "%userprofile%\Local Settings\Temp\*.*"
del /f /s /q "%userprofile%\recent\*.*"
sfc /purgecache '清理系统盘无用文件
defrag %systemdrive% -b '优化预读信息
echo 清除系统LJ完成！ 
echo. & pause
```

短一点的版本（经实验，但C盘内存几乎没变）

```
@echo off
echo 正在清除系统垃圾文件，请稍等......
del /f /s /q %systemdrive%\*.tmp 
del /f /s /q %systemdrive%\*._mp 
del /f /s /q %systemdrive%\*.gid 
del /f /s /q %systemdrive%\*.chk 
del /f /s /q %systemdrive%\*.old 
del /f /s /q %windir%\*.bak 
del /f /s /q %windir%\temp\*.* 
del /f /a /q %systemdrive%\*.sqm 
del /f /s /q %windir%\SoftwareDistribution\Download\*.* 
del /f /s /q "%userprofile%\cookies\*.*" 
del /f /s /q "%userprofile%\recent\*.*" 
del /f /s /q "%userprofile%\local settings\temporary internet files\*.*" 
del /f /s /q "%userprofile%\local settings\temp\*.*" 
echo 清除系统垃圾文件完成! 
echo. & pause 
```

# mklink符号链接清理

==这个我自己也不太会用==

比如

mklink /J "C:\program files\windows sdk" "D:\windows sdk"

注意：因为powershell不支持mklink命令，所以要在前面加cmd /c表示用cmd来运行该命令，路径注意引号，可以是相对路径也可以是绝对路径，硬链接只能用于文件，不能对文件夹创建硬链接，不然会提示“拒绝访问”。

# 安装避免

## Visual Studio 的安装避免

参考：https://blog.csdn.net/qq_37444533/article/details/121401284

在安装VS时虽然有选择安装位置的选项，但是就算更换了安装位置，还是会有很多部件被安装在了C盘。本文介绍了将VS安装到非C盘的步骤。

# 用于比较的状态

## 大概分布

75G（剩余25G）可以状态参考：
C:\Windows大约18G左右
C:\Users\A\AppData\大约14G左右
C:\文件大约13G
C:\Program Files10.2G
C:\ProgramData5.4G
C:\Program Files(x86)4.9G

## 截图

### 20221012 - 红了，无处可动

2020年底 清完可以65G，21年年中 清完可以72G，22年年底 清完也只能95G

![image-20221012053945072](Windows的C盘常清.assets/image-20221012053945072.png)

### 20210409

![image-20210409043610749](Windows的C盘常清.assets/image-20210409043610749.png)

### 20210119

![image-20210119221356371](Windows的C盘常清.assets/image-20210119221356371.png)

- Users 19.3G
    - A 19.0G
        - AppData 17.9G
            - Local 12.0G
                - Temp 2G（清理前10+G）
    - Public 261.8M
- Windows
    - WinSxS 6.1G
    - System 32 5.5G
        - 4675文件 2.1G
    - SysWOW 64 1.6G
        - 2972文件 1.1G
    - assembly 1.1G
    - Microsoft.NET 660.9M
    - Installer 119.3M（清理前2.7G）
    - LiveKernelReports 0（清理前10+G）
- Program File (x86) 13.6G
    - Microsoft SDKs 5.4G
    - Common Files 3.1G
    - Winodws Kits 1.9G
- Program Files 11.6G
    - Common Files 2.7G
    - Microsoft Office 1.8G
- $Recycle.Bin 420.0KB（清理前10+GB）

### 20201124

装了VS以后：（Microsoft SDKs就占了5.4G）（VS占C好多，系统驱动器就要占15.48G，没法设置其他盘）

![image-20201124170048653](Windows的C盘常清.assets/image-20201124170048653.png)

（正在装VS的状态）

![image-20201124164653601](Windows的C盘常清.assets/image-20201124164653601.png)

