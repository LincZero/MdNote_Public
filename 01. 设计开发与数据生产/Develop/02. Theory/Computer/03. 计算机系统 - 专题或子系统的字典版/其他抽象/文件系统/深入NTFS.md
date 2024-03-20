# 计算机文件系统

# 目录

# 深入NTFS

参考

- 主要参考：[维基](https://en.wikipedia.org/wiki/NTFS) / [中文维基](https://zh.wikipedia.org/wiki/NTFS)（该词条挺全的，像个文档似的。感觉这个维基**中文版写得更好**）以及底部的参考文献与外部链接
- 微软文档：[Windows Server/NTFS如何为去主文件表保留空间（MFT）](https://learn.microsoft.com/zh-cn/troubleshoot/windows-server/backup-and-storage/ntfs-reserves-space-for-mft)

## 概念类

### 概念

> [!wiki] NTFS（中文wiki）
>
> **NTFS（<ruby>新技术文件系统<rt>New Technology File System</rt></ruby>）**，是Microsoft公司开发的专用文件系统，从Windows NT 3.1开始成为Windows NT家族的默认文件系统。（Mac也是用的）
>
> NTFS 取代 **FAT（<ruby>文件分配表<rt>File Allocation Table</rt></ruby>）**和 **HPFS（<ruby>高性能文件系统<rt>High Performance File System</rt></ruby>）**并进行一系列改进成为更加完善的安全系统，例如增强对元数据的支持，使用更高级的数据结构以提升性能、可靠性和磁盘空间利用率，并附带一系列增强功能，如访问 **ACL（<ruby>控制列表<rt>Access Control List</ruby>）**和文件系统日志。
>
> 其他台式机和服务器操作系统也支持NTFS。Linux和windows提供代码的软件NTFS-system，可用于读写NTFS文件。Mac OS X内核不能对NTFS进行读操作。 



> [!wiki] NTFS文件系统 
>
> 从 Windows NT 3.1 开始，它是 Windows NT 家族的默认文件系统。 [11] 它取代 文件分配表 (FAT) 作为 Windows 上的首选文件系统，并且在 Linux 和 BSD 中也受支持。 NTFS 读写支持是使用 免费和开源 称为 NTFS3， 内核实现提供的，在Linux 中 中称为NTFS-3G 驱动程序 在BSD 。 [12] [13] 通过使用 convert命令，Windows 可以将 FAT32 /16/12 转换为 NTFS，而无需重写所有文件。 [14] NTFS 使用通常对用户隐藏的几个文件来存储有关存储在驱动器上的其他文件的元数据，这有助于提高读取数据时的速度和性能。 [1] 与 FAT 和 高性能文件系统 (HPFS) 不同，NTFS 支持 访问控制列表 (ACL)、文件系统加密、透明压缩、 稀疏文件 和 文件系统日志 。 NTFS 还支持 卷影复制 以允许在系统运行时对其进行备份，但卷影复制的功能因 Windows 的不同版本而异。



> [!wiki] 日志文件系统
>
> 文件 日志文件系统 是一种 系统 ）的数据结构中记录此类更改的目标来跟踪尚未提交到 文件系统 ，它通过在称为“ 日志 ”（通常是 循环日志 主要部分的更改。 在系统崩溃或电源故障的情况下，此类文件系统可以更快地恢复在线，并且损坏的可能性更低。 [1] [2]
>
> 根据实际实现，日志文件系统可能只跟踪存储的 元数据 ，从而以增加数据损坏的可能性为代价提高性能。 或者，日志文件系统可以跟踪存储的数据和相关的元数据，而一些实现在这方面允许可选择的行为。



> [!wiki] 日志文件系统/基本原理
>
> 存在问题：
>
> 更新文件系统以反映对文件和目录的更改通常需要许多单独的写操作。
> 这使得写入之间的中断（如电源故障或系统 崩溃 ）有可能使数据结构处于无效的中间状态。 
>
> 例如，在 Unix 文件系统上删除文件涉及三个步骤：
>
> 1. 删除其目录条目。
> 2. 释放 将inode 到空闲 inode 池中。
> 3. 将所有磁盘块返回到空闲磁盘块池。
>
> 可能会产生以下错误： 
>
> - 如果在步骤 1 之后和步骤 2 之前发生崩溃，则会有一个孤立的 inode，因此会发生**存储泄漏**；
> - 如果在步骤 2 和步骤 3 之间发生崩溃，则文件之前使用的块不能用于新文件，从而有效降低文件系统的存储容量。 重新安排步骤也无济于事。
> - 如果第 3 步先于第 1 步，则它们之间的崩溃可能会允许文件的块重新用于新文件，这意味着部分删除的文件将包含另一个文件的部分内容，并且对任一文件的修改都会显示在两个文件中。
> - 如果第 2 步先于第 1 步，则它们之间的崩溃将导致文件无法访问，尽管文件看似存在。
>
> 检测此类不一致并从中恢复通常需要完整 遍历 其数据结构，例如使用 fsck （文件系统检查程序）等工具。 这通常必须在下一次安装文件系统以进行读写访问之前完成。 如果文件系统很大并且 I/O 带宽相对较小，这可能会花费很长时间，如果它阻止系统的其余部分重新联机，则会导致更长的停机时间。
>
> 
>
> 修复方案：
>
> 为了防止这种情况，日志文件系统分配了一个特殊的区域——**日志**——它在其中记录了它将提前进行的更改。
> 崩溃后，恢复只涉及从文件系统读取日志并重放该日志的更改，直到文件系统再次一致。 
> 因此，这些更改被称为 **<ruby>原子<rt>不可分割</ruby>** 的，因为它们要么成功（最初成功或在恢复期间完全重放），要么根本不重放（被跳过，因为它们在发生崩溃）。 



### wiki目录

> [!wiki]- NTFS/目录
>
> - [1 历史](https://zh.wikipedia.org/wiki/NTFS#歷史)
> - [2 版本](https://zh.wikipedia.org/wiki/NTFS#版本)
> - 3 功能
>   - [3.1 可伸缩性](https://zh.wikipedia.org/wiki/NTFS#可伸缩性)
>   - [3.2 日志](https://zh.wikipedia.org/wiki/NTFS#日志)
>   - [3.3 硬链接](https://zh.wikipedia.org/wiki/NTFS#硬链接)
>   - [3.4 可选数据流（ADS）](https://zh.wikipedia.org/wiki/NTFS#可选数据流（ADS）)
>   - [3.5 文件压缩](https://zh.wikipedia.org/wiki/NTFS#文件压缩)
>   - [3.6 稀疏文件](https://zh.wikipedia.org/wiki/NTFS#稀疏文件)
>   - [3.7 卷影复制](https://zh.wikipedia.org/wiki/NTFS#卷影复制)
>   - [3.8 事务](https://zh.wikipedia.org/wiki/NTFS#事务)
>   - [3.9 安全](https://zh.wikipedia.org/wiki/NTFS#安全)
>   - [3.10 加密](https://zh.wikipedia.org/wiki/NTFS#加密)
>   - [3.11 限额](https://zh.wikipedia.org/wiki/NTFS#限额)
>   - [3.12 重解析点](https://zh.wikipedia.org/wiki/NTFS#重解析点)
>   - [3.13 卷加载点](https://zh.wikipedia.org/wiki/NTFS#卷加载点)
>   - [3.14 目录连接](https://zh.wikipedia.org/wiki/NTFS#目录连接)
>   - [3.15 符号链接](https://zh.wikipedia.org/wiki/NTFS#符号链接)
>   - [3.16 分层存储管理（HSM）](https://zh.wikipedia.org/wiki/NTFS#分层存储管理（HSM）)
>   - [3.17 本机结构存储（NSS）](https://zh.wikipedia.org/wiki/NTFS#本机结构存储（NSS）)
>   - [3.18 分布链接跟踪（DLT）](https://zh.wikipedia.org/wiki/NTFS#分布链接跟踪（DLT）)
>   - [3.19 单实例存储（SIS）](https://zh.wikipedia.org/wiki/NTFS#单实例存储（SIS）)
> - 4 内部实现
>   - [4.1 分区引导扇区](https://zh.wikipedia.org/wiki/NTFS#分区引导扇区)
>   - [4.2 主文件表（MFT）](https://zh.wikipedia.org/wiki/NTFS#主文件表（MFT）)
>   - [4.3 元文件](https://zh.wikipedia.org/wiki/NTFS#元文件)
>   - [4.4 从MFT到属性、属性表和流](https://zh.wikipedia.org/wiki/NTFS#从MFT到属性、属性表和流)
>   - [4.5 常驻文件和非常驻文件](https://zh.wikipedia.org/wiki/NTFS#常驻文件和非常驻文件)
>   - [4.6 机会锁](https://zh.wikipedia.org/wiki/NTFS#机会锁)
>   - [4.7 时间](https://zh.wikipedia.org/wiki/NTFS#时间)
> - 5 互操作性
>   - [5.1 Microsoft Windows](https://zh.wikipedia.org/wiki/NTFS#Microsoft_Windows)
>   - [5.2 Mac OS X](https://zh.wikipedia.org/wiki/NTFS#Mac_OS_X)
>   - [5.3 Linux](https://zh.wikipedia.org/wiki/NTFS#Linux)
>   - [5.4 其他](https://zh.wikipedia.org/wiki/NTFS#其他)
>   - [5.5 调整大小](https://zh.wikipedia.org/wiki/NTFS#调整大小)
> - [6 另请参阅](https://zh.wikipedia.org/wiki/NTFS#另请参阅)
> - [7 参考文献](https://zh.wikipedia.org/wiki/NTFS#参考文献)
> - [8 外部链接](https://zh.wikipedia.org/wiki/NTFS#外部链接)



## 功能类

### 可伸缩性



### 日志

这点详见 [wiki/日志文件系统](https://zh.wikipedia.org/wiki/日志文件系统)
注意区分：NTFS日志 与 USN日志

> [!wiki] NTFS/日志
>
> NTFS是一个[日志文件系统](https://zh.wikipedia.org/wiki/日志文件系统)，使用 **NTFS日志（$Logfile）**记录卷更改元数据。这是NTFS一个非常关键的功能（FAT/FAT32不提供此项功能）。
> 作用是可确保其内部的**复杂数据结构**和**索引**即使在系统崩溃后仍然能保证一致性，而当在卷被重新加载后，可以非常容易地回滚这些关键数据的意外修改。
>
> （复杂数据结构：如比较重要的如卷分配图、磁盘碎片整理API产生的数据转移操作、MFT（主文件表）记录的更改情况（包括移动MFT记录中存储的变长属性和属性表等））
> （索引：在目录和安全描述符中使用）
>
> **[USN日志](https://zh.wikipedia.org/wiki/USN日志)（<ruby>更新序列号码日志<rt>Update Sequence Number Journal</ruby>，或称 <ruby>更改日志<rt>Change Journal</ruby>）**是一项系统管理功能（注意不要与NTFS文件系统的日志设计混淆）。
> 作用为记录卷中所有文件、数据流、目录的内容、属性以及各项安全设置的更改情况。应用程序可以利用日志追踪卷的更改。对于非系统卷，可以选择打开或关闭日志。当添加一个新卷后，默认情况下日志功能处于打开状态。 



## Everything

> https://www.zhihu.com/question/292538150
>
> 很多国内的，都觉得everything开源，毕竟像 utools、wox、火萤酱 等软件，都内置的everything内核
>
> 但事实上我并没有找到任何有关everything开源的代码，应该是闭源的。
> 但是官网有针对各类编程语言的API，已经相应的许可协议，可以使用其内核作为应用的一部分



> https://www.voidtools.com/zh-cn/support/everything/everything_service/
>
> 官网这里面说了其原理：
>
> Everything 服务可以索引 NTFS 分卷和监控 USN 日志。
> 这将可以让 Everything 以标准用户方式运行。
>
> https://www.voidtools.com/zh-cn/support/everything/sdk/
>
> 这个是官方的 Everything SDK，可以用各种语言来使用他



> https://github.com/search?q=everything
>
> 既然他不开源，那我尝试去看看有没有人实现了类似的功能
> 这两个有点像，有空再来研究
>
> - https://github.com/yuzhengyang/Everything：探索Everything背后的技术（USN和MFT）
> - https://github.com/LeiHao0/Fake-Everything：Everything 的原理猜想与实现       



## MP3tag

> https://baike.baidu.com/item/MP3tag/10473015
>
> 原理：Mp3tag可以以文件名批量 **添加媒体元信息**，根据媒体元信息批量重命名文件，执行批量文字替换、导入导出文件信息、创建播放列表等任务



## 原理类

### 内部实现

> [!wiki] NTFS/内部实现
>
> 在内部，NTFS使用[B+树](https://zh.wikipedia.org/wiki/B%2B树)索引文件系统数据。这种数据结构的方式实现比较复杂，但能够在大多数情况下提高文件的查找速度。
> [文件系统日志](https://zh.wikipedia.org/wiki/日志文件系统)用于确保文件的元数据完整，不存在孤立的文件内容。相比于FAT文件系统，NTFS文件系统的可靠性更高。
>
> NTFS允许对名称（包括文件名称、流名称、索引名称等）使用除了0x0000以外的任意16位值序列进行编码。这意味着支持NTFS支持UTF-16码位，但文件系统并不会检查某个[UTF-16](https://zh.wikipedia.org/w/index.php?title=UTF-16/UCS-2&action=edit&redlink=1)序列是否有效（也即允许NTFS内部任意16位整数序列，不受Unicode标准的限制）。



### 分区引导扇区（PBS）

> [!wiki] NTFS/分区引导扇区
>
> | 字节<br />偏移 | 字段长度<br />(字节) | 典型值             | 字段名           | 描述                                                         |
> | -------------- | -------------------- | ------------------ | ---------------- | ------------------------------------------------------------ |
> | 0x00           | 3                    | 0xEB5290           | JMP 指令         | 用于命令处理器继续执行引导扇区后的内容                       |
> | 0x03           | 8                    | `NTFS____`         | OEM 标识         | 单词“NTFS”，以及后续四个空格（0x20）<br />用于标记当前分区使用NTFS文件系统 |
> | 0x0B           | 2                    | 0x0200             | 每扇区字节数     | 说明每个扇区的字节数                                         |
> | 0x0D           | 1                    | 0x08               | 每簇扇区数       | 说明每个簇包含的扇区数                                       |
> | 0x0E           | 2                    | 0x0000             | 保留扇区数       | 被操作系统保留的扇区数，参考文献中未说明保留扇区的位置       |
> | 0x10           | 3                    | 0x000000           | 未使用           | 该字段的内容始终为零                                         |
> | 0x13           | 2                    | 0x0000             | NTFS 未使用      | 该字段的内容始终为零                                         |
> | 0x15           | 1                    | 0xF8               | 介质描述符       | 参考文件中未说明详细信息                                     |
> | 0x16           | 2                    | 0x0000             | 未使用Unused     | 该字段的内容始终为零                                         |
> | 0x18           | 2                    | 0x003F             | 每磁道扇区数     | 说明每个磁道的扇区数                                         |
> | 0x1A           | 2                    | 0x00FF             | 磁头数           | 该驱动器包含的读写磁头数                                     |
> | 0x1C           | 4                    | 0x0000003F         | 隐藏扇区数       | 隐藏的扇区数目。参考文献中未说明隐藏扇区位置                 |
> | 0x20           | 4                    | 0x00000000         | 未使用           | NTFS未使用                                                   |
> | 0x24           | 4                    | 0x80008000         | 未使用           | NTFS未使用                                                   |
> | 0x28           | 8                    | 0x00000000007FF54A | 总扇区数         | 该分区包含的总扇区数目                                       |
> | 0x30           | 8                    | 0x0000000000000004 | \$MFT 簇编号     | \$MFT 所在的簇的编号                                         |
> | 0x38           | 8                    | 0x000000000007FF54 | \$MFTMirr 簇编号 | \$MFT镜像（备份）所在的簇的编号                              |
> | 0x40           | 1                    | 0xF6               | 文件记录段字节数 | 每个文件记录段的包含的字节数目。如果该值为负数，则实际值为 2^-value^<br />例如值 0xF6 表示记录长度为 2^10（10==-0xf6） |
> | 0x41           | 3                    | 0x000000           | 未使用           | NTFS未使用该字段                                             |
> | 0x44           | 1                    | 0x01               | 索引缓冲簇数     | 每个索引缓冲占据的簇数目，算法和文件记录段相同               |
> | 0x45           | 3                    | 0x000000           | 未使用           | NTFS未使用该字段                                             |
> | 0x48           | 8                    | 0x1C741BC9741BA514 | 卷序列数         | 该分区的唯一随机编号，用于确保内容一致性                     |
> | 0x50           | 4                    | 0x00000000         | 校验和           | 表中上述所有项目的校验和。文献中未说明校验算法               |
> | 0x54           | 426                  |                    | 启动指令码       | 用于加载操作系统其它部分的指令码，该字段位置正是引导扇区前三个字节指向的位置 |
> | 0x01FE         | 2                    | 0xAA55             | 扇区结束标记     | 该字段用于标记一个正常扇区的结束                             |
>
> 操作系统首先通过0x30位置的8个字节找到 \$MFT 所在的簇编号，然后将其和每簇扇区数（0x0D位置的1字节）以及每扇区字节数（0x0B位置的2字节）相乘，获得\$MFT的字节偏移量。



### ==主文件表（MFT）==

NTFS文件系统的核心

> [!wiki] NTFS/主文件表（MFT）
>
> 在NTFS中，所有文件数据——文件名、创建日期、访问权限，以及内容 —— 都作为 [**<ruby>元数据<rt>Metadata</ruby>**](https://zh.wikipedi>a.org/wiki/元数据) 储存在 **MFT（<ruby>主文件表<rt>Master File Table</ruby>）**中。
> 其中访问权限使用 **ACL（<ruby>访问控制列表<rt>Access Control List</rt></ruby>）**实现
>
> 这种抽象的实现方式能够大大简化为文件系统添加功能的成本。例如，**<ruby>活动目录<rt>Active Directory</ruby>** 服务可以很容易在文件系统中为文件添加索引字段。这种设计方式也使得 **[Everything](https://zh.wikipedia.org/wiki/Everything_(软件)) 或者 Ultrasearch** 一类的软件可以不依赖于Windows Search实现对文件和文件夹名称的实时搜索。
>
> **MFT（<ruby>主文件表<rt>Master File Table</ruby>）结构** 支持最小化磁盘碎片的算法。一个目录项同时包含“文件名”和“文件ID”，后者是用于在主文件表中标识文件的记录编号。文件ID也包含“重用次数”信息，可用于检测对文件的过期引用。这点设计非常类似于Files-11文件系统的W_FID，和NTFS的其他部分迥然不同。 



其他参考：[【百度百科】主控文件表](https://baike.baidu.com/item/主控文件表/8971573)



### ==元文件==

再次补充：[**<ruby>元数据<rt>Metadata</ruby>**](https://zh.wikipedi>a.org/wiki/元数据) 储存在 **MFT（<ruby>主文件表<rt>Master File Table</ruby>）**中



> [!wiki] NTFS/元文件
>
> NTFS包含若干用于定义和组织文件系统的文件。总体来说，这些文件中的绝大多数结构和其它用户文件类似（只有“$Volume”比较特殊），但不能被文件系统客户端直接访问。
> 这些元文件为定义文件、备份文件系统的关键数据、缓存文件系统的更改、管理空闲空间的分配、满足BIOS的要求、跟踪坏扇区单元，以及储存安全信息和磁盘空间使用情况等等多种不同需求提供支持。
>
> | 区块<br />编号 | 文件名             | 作用                                                         |
> | -------------- | ------------------ | ------------------------------------------------------------ |
> | 0              | `$MFT`             | 描述卷上的所有文件，包括**文件名**、**时间戳**、流名称<br />和数据流所在的簇的编号列表、索引、安全标识符，<br />以及**文件属性**（如“只读”、“压缩”、“加密”等）。 |
> | 1              | `$MFTMirr`         | \$MFT的最开始的几个关键项的副本，通常是4项（4[KiB](https://zh.wikipedia.org/wiki/Kibibyte)）。 |
> | 2              | `$LogFile`         | 文件系统更改的事务日志，用于保护元数据的稳定性。             |
> | 3              | `$Volume`          | **卷的相关信息**，如卷对象标识符、[卷标](https://zh.wikipedia.org/w/index.php?title=卷标&action=edit&redlink=1)、文件系统版本，以及若干卷标志（包括：“正在加载”、“需要扫描”、“需要调整\$LogFile大小”、“在NT4上加载”、“正在更新卷序列号”、“需要升级结构”等）。这些数据不直接在数据流中存储，而是存储于特殊的 MFT 属性中。如果卷对象标识符存在，则将会在一个 \$OJBECT_ID 记录中；卷标存储在 \$VOLUME_NAME 记录中；其它数据存储在 \$VOLUME_INFORMATION 记录中；卷序列号储存在\$Boot文件中（请参见下文）。 |
> | 4              | `$AttrDef`         | 所有NTFS项目使用到的**属性的定义表**，包含属性名称、属性编号和属性描述等。 |
> | 5              | `.`                | [根目录](https://zh.wikipedia.org/wiki/根目录)。目录数据存储在两个名称均为 \$I30 的 \$INDEX_ROOT 和 \$INDEX_ALLOCATIOn 属性中 |
> | 6              | `$Bitmap`          | 一个[位图](https://zh.wikipedia.org/wiki/位图)，每一位按顺序指示卷上的对应簇正在被使用（1）或空闲（0）。 |
> | 7              | `$Boot`            | [卷引导记录](https://zh.wikipedia.org/w/index.php?title=卷引导记录&action=edit&redlink=1)，该文件始终位于卷的第一个簇，其中包含[引导代码](https://zh.wikipedia.org/w/index.php?title=引导代码&action=edit&redlink=1)（用于定位并启动[NTLDR](https://zh.wikipedia.org/wiki/NTLDR)/[BOOTMGR](https://zh.wikipedia.org/w/index.php?title=Windows_Vista启动过程&action=edit&redlink=1)）、[BIOS参数块](https://zh.wikipedia.org/w/index.php?title=BIOS参数块&action=edit&redlink=1)（其中包含[卷序列号](https://zh.wikipedia.org/w/index.php?title=卷序列号&action=edit&redlink=1)），以及$MFT和$MFTMirr所在的簇编号。 |
> | 8              | `$BadClus`         | 包含所有标记为“有[坏扇区](https://zh.wikipedia.org/wiki/坏扇区)”的簇的一个文件。该文件通常被chkdsk（磁盘扫描）工具使用，用于管理所有簇状态，记录坏扇区，以及标记空白簇。该文件包含两个数据流（无论卷是否有坏道）：一个包含所有坏扇区编号的无名称流（如果卷没有坏扇区则该流长度为零），以及名称为$Bad的流，包含所有包含记录在第一个流中的簇。 |
> | 9              | `$Secure`          | **[访问控制列表](https://zh.wikipedia.org/wiki/访问控制列表)（ACL）数据库**，NTFS将所有ACL信息集中存储于该数据库（而非每个文件独立存储各自的ACL）以节省磁盘占用并提高执行效率。此部分包含两个索引，分别是：“\$SII”——可能是[[来源请求\]](https://zh.wikipedia.org/wiki/Wikipedia:列明来源)*安全ID索引*，以及“\$SDH”——*安全描述符哈希*。注意大部分ACL列表通常都很长，因此这个部分只是索引，记录的是实际存储ACL数据的\$SDS流的位置。[[1\]](https://zh.wikipedia.org/wiki/NTFS#cite_note-insidewin2kntfs-1) |
> | 10             | `$UpCase`          | [Unicode](https://zh.wikipedia.org/wiki/Unicode)大写字母表，用于确保在Win32和DOS名字空间下大小写不敏感。 |
> | 11             | `$Extend`          | 文件系统目录，用于包含若干操作系统或其它软件所需要的扩展数据，如\$Quota、\$ObjId、\$Reparse、\$UsnJrnl等。 |
> | 12...23        |                    | 保留为 $MFT 扩展项使用。扩展项目是一系列附加MFT记录，用于描述未在主记录中包含的属性。例如，当卷需要磁盘清理，包含太多流，具有长文件名或者非常复杂的安全设定，以及其它特殊情况时，可能会用到保留项目 |
> | 24             | `$Extend\$Quota`   | 磁盘限额设置。包含两个索引根目录，名称分别为\$O和\$Q。       |
> | 25             | `$Extend\$ObjId`   | [分布链接跟踪](https://zh.wikipedia.org/w/index.php?title=分布链接跟踪&action=edit&redlink=1)数据。包含一个索引根目录，名称为\$O。 |
> | 26             | `$Extend\$Reparse` | 卷上所有[重解析点](https://zh.wikipedia.org/wiki/重解析点)（如[符号链接](https://zh.wikipedia.org/wiki/符号链接)）数据。包含一个索引根目录，名称为$R。 |
> | *27 ...*       | `*file.ext*`       | 常规文件系统项目的起始位置。                                 |
>
> Windows对这些元文件的处理方式较为特殊，直接由NTFS.SYS进行处理，因此**难以直接查看**，需要使用特殊工具进行提取。
> **从Windows 7开始，NTFS驱动程序完全阻挡了用户访问权限，任何尝试访问元文件的请求都会直接进入[蓝屏死机](https://zh.wikipedia.org/wiki/蓝屏死机)界面**。
>
> 解决方案：
>
> - 微软 “OEM支持工具” 中的 “nfi.exe”（NTFS文件扇区信息实用工具）” 是一个可查看这些文件的工具。
>   例如，要查看 “$MFT” 的内容，只需使用下列命令行：`nfi.exe c:\$MFT`。
> - 另一个绕过操作系统保护限制的方法是使用[7-Zip](https://zh.wikipedia.org/wiki/7-Zip)文件管理器工具并输入低级NTFS路径`\\.x:\`，此时将会出现三个新的文件夹：`$extend`、`$[DELETED]`以及`[SYSTEM]`。
>   这个操作可以用于任何可移动设备，但如果需要访问当前活动分区，则需要进入离线模式（也即[WinRE](https://zh.wikipedia.org/wiki/WinRE)）。



### 从MFT到属性、属性表和流













### 常驻文件和非常驻文件

### 机会锁

### 时间

### 【总结】捋一下



## 互操作性































