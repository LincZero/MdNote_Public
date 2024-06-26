# 计算机文件系统

# 目录

# 计算机文件系统

## 多种文件系统

参考：https://baijiahao.baidu.com/s?id=1611840649609906115

### FAT32

> 大多说用户使用的U盘格式都是FAT32格式，因为它的兼容性相对好一些，几乎可以完美应对所有操作系统，并且快速的进行读写工作。但是它的缺点是是不能设置权限，安全等级较低。并且最关键的一点就是它最高只能支持4G以下的单个文件传输。随着文件越来越大，一个高清的电影就已经达到了好几个G的大小，相比之下FAT32已经属于落后“产品”。

### NTFS

> 目前来说，NTFS格式的U盘或者硬盘来说，都是使用最广泛的一种。相比之下我们可以对此格式的U盘进行设置权限，并且可以做出FAT32不能实现的功能。在互换性和实用性来说，NTFS远高于FAT3。并且在支持文件上最大可以拓展为256T。看清楚，是256TB！只要是U盘或者硬盘能放得下的文件几乎可以读写。小编使用的U盘PE中也是使用NTFS格式，存储和读写方便快捷。刷系统分区时建议使用NTFS类型。

### exFAT

> 最后这类也可以说是FAT64，从ID上看也是能看出，是FAT32的升级版。主要目的就是为了解决FAT32不能存储单个文件高于4G的问题。最大支持256GB拓展。并且在WIN和MAC均可使用，跨平台能力十分出众，也是微软为了闪存设备特地设计的文件系统。作为U盘等移动设备是最好的选择之一。

### 最后总结

> 以上三种格式的选择相信大家都已经有了一定的认识。主要是用的就是NTFS和FAT64两种。机械硬盘和固态硬盘使用NTFS较为合适，存储能力强和通用性好。而作为移动端，U盘或者移动硬盘等设备使用FAT64较为合适，读写速度相对较快。



## Desktop.ini 文件

https://github.com/piratf/windows-folder-remark

该脚本会修改文件夹下隐藏的 Desktop.ini 文件，并为文件夹修饰系统属性



## 文件元数据



























