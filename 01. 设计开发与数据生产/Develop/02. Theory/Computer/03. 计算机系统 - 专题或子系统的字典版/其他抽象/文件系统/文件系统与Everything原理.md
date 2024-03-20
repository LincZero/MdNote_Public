# Hardware

可能需要数据结构的基础

# 目录

# 文件系统与Everything原理

## 文件系统

### 简概

文件系统

> wikipedia
>
> - 概念
>
>   [计算机](https://zh.wikipedia.org/wiki/计算机)的**文件系统**是一种存储和组织计算机数据的方法，它使得对其访问和查找变得容易
>
> - 抽象封装
>
>   文件系统使用**文件**和**树形目录**的抽象**逻辑概念**代替了硬盘和光盘等物理设备使用**数据块**的概念。
>   用户使用文件系统来保存数据不必关心数据实际保存在硬盘（或者光盘）的地址为多少的数据块上，只需要记住这个文件的所属目录和文件名。
>   在写入新数据之前，用户不必关心硬盘上的那个块地址没有被使用，硬盘上的存储空间管理（分配和释放）功能由文件系统自动完成，用户只需要记住数据被写入到了哪个文件中。
>
> - 载体
>
>   文件系统通常使用[硬盘](https://zh.wikipedia.org/wiki/硬盘)和[光盘](https://zh.wikipedia.org/wiki/光盘)这样的[存储设备](https://zh.wikipedia.org/wiki/存储设备)，并维护文件在设备中的**物理位置**。
>
> - 严格定义
>
>   但是，实际上文件系统也可能仅仅是一种访问资料的界面而已，实际的数据是通过网络协议（如[NFS](https://zh.wikipedia.org/wiki/NFS)、[SMB](https://zh.wikipedia.org/wiki/SMB)、[9P](https://zh.wikipedia.org/wiki/9P)等）提供的或者内存上，甚至可能根本没有对应的文件（如[proc文件系统](https://zh.wikipedia.org/wiki/Procfs)）。
>   文件系统是一套实现了[数据](https://zh.wikipedia.org/wiki/数据)的存储、分级组织、访问和获取等操作的[抽象数据类型](https://zh.wikipedia.org/wiki/抽象數據類型)（Abstract data type）。









### 















## Everything

### Everything和Windows搜索

#### 区别

Everything和Windows搜索是有区别的，以下列几点：

1. Everything只能搜索文件名和文件夹名，Windows搜索可以搜索文件名和文件内容；
2. Everything只能搜索NTFS格式的文件系统，Windows搜索可以搜索任意文件系统（例如FAT32，exFAT，NTFS）；

但有时我们需要的恰好就是快速搜索文件名

#### 原理

程序启动时，扫描系统所有NTFS卷（磁盘）的MTF表，将文件名称以一种利于字符串检索的算法形式存储在Everything的index索引数据库中。

系统运行过程中，Everything还会监控NTFS卷的journal日志文件，如果文件系统中的文件发生改变，Everything会更新它的index索引数据库。

当用户搜索文件时，Everything利用字符串查找算法，在index索引数据库中查找，可以直接搜索到文件。

#### 问答QA

Q：Search Everything 这款软件如何做到如此快速的搜索的？
A：因为Everything在搜索时，根本没有遍历文件系统，它检索的是自己组织好的索引数据库，因此搜索速度飞快；

Q：Windows搜索时什么原理？
A：Windows搜索用的是普通的文件系统遍历查找。用的应该是标准WIN32 API，例如FindFirstFile/FindNextFile之类。当然，Windows7之后的版本现在已经内置带索引的搜索功能，这项功能非常复杂，不仅可以搜索文件名，还可以搜索文件内容，而且适用任意文件系统。但缺点就是需要一个后台服务爬虫不停的对文件系统进行索引，比较耗资源。

Q：为何微软不使用这种原理？
A：个人觉得是因为这种方法不具备普适性，无法应用与非NTFS文件系统，所以无法集成到Windows中。

Q：为何微软不收购这家公司?
A：个人感觉还是技术含量不太高，而且微软自家的ActiveDirectory早就在使用MTF快速检索文件了。

## TreeSize











## Reference

文件系统参考

- [【维基百科】文件系统](https://zh.wikipedia.org/wiki/%E6%96%87%E4%BB%B6%E7%B3%BB%E7%BB%9F)
- 《数据结构与算法分析（C语言描述）》
- 《深入理解计算机系统》第10章 - 系统级I/O

Everything原理参考

- https://bbs.csdn.net/topics/390280495
- https://www.cnblogs.com/xust/articles/3616940.html
- https://www.zhihu.com/question/22862246























































