# 计算机系统  - 线性学习版

==（这里我分了三个子目录，其实是一体的：）==

- 线性版
- 专题/子系统版
- 转载 - 小林coding图解系列

## 主目录

“操作系统” 一仅仅只是一个系统，这门学问涉及的东西太多太杂了

按我的理解简单分类和线性整理一下

1. 操作系统之前（一些前置知识）
   - 计算机构成
   - 汇编
2. 操作系统原理
2. 高级语言、编译原理

## 操作系统子分类

### 子系统分类（字典型，五大子系统及细分模块）

1. 操作系统子系统、子模块
   1. 进程管理子系统
      - 调度模块
      - 任务管理模块
      - 同步模块
      - CPU模块
   2. 内存管理子系统
      - 虚拟内存模块
      - 内存映射模块
      - 页表模块
      - 物理内存模块
   3. 文件子系统
      - VFS模块
      - 缓存模块
      - 文件系统模块
   4. 网络子系统
      - 套接字模块
      - 协议栈模块
      - 网络设备模块
   5. 设备子系统
      - 字符设备模块
      - 块设备模块

### CSAPP目录（线性学习型，三大递进）

- 程序结构和执行
- 系统上运行程序
- 程序间交互和通信

### 个人分类（字典型，三大类）

1. 上层相关

  - 用户态和内核态
  - 上层管理（管理多个上层软件，如果只运行一个上层软件则理论上不需要这个）
    - 进程管理
    - 虚拟内存

2. 下层相关（管理多个下层硬件，特别是专指IO设备）

  - 设备专题
    - CPU (非IO)
    - 内存 (非IO)
    - 显卡、图形
    - 磁盘
    - 网卡、网络
    - 其他设备
  - 下层管理 (管理多个下层设备，如果下层设备只有一个则理论上不需要这个)

3. 其他抽象

   - 文件系统
- 编码问题等

## 分类优先级

底层IO分类 > 上层抽象分类


## 重点

《SCAPP》的：

- 虚拟内存 (特别是最后的动态内存分配、垃圾手机、C程序与内存有关错误)
- 网络

这些面试会容易考一些。个人的话对文件系统、系统IO会更感兴趣





















