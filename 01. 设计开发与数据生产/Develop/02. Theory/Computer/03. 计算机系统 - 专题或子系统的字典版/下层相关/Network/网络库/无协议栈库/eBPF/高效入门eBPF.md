# eBPF

# 目录

# 高速入门eBPF

视频：https://www.bilibili.com/video/BV1LX4y157Gp

## 技术介绍

### 来源

1992 年论文：“The BSD pakcet filter: A New architecture for user-level packet capture”，即《BSD数据包过滤器：一种用于用户级数据包捕获的新体系结构》

最初，BPF是在BSD内核实现的，后来，由于其出色的设计思想，其他操作系统也将欺引入，包括Linux

### BPF的实现有哪些

![image-20230719210702569](高效入门eBPF.assets/image-20230719210702569.png)

### 技术架构图

![image-20230719212107531](高效入门eBPF.assets/image-20230719212107531.png)

### BPF运行时结构

![image-20230719213641786](高效入门eBPF.assets/image-20230719213641786.png)

### eBPF相较于BPF的扩展内容

![image-20230719214158179](高效入门eBPF.assets/image-20230719214158179.png)



![image-20230719214405537](高效入门eBPF.assets/image-20230719214405537.png)

## BPF 虚拟机与执行

### 编译、指令集

#### BPF不仅是一个指令集，还提供了一些工具

![image-20230719214518980](高效入门eBPF.assets/image-20230719214518980.png)

#### BPF指令集

![image-20230719214613503](高效入门eBPF.assets/image-20230719214613503.png)

字节码对虚拟机，相当于,机器码对X86或arm

#### BPF虚拟机与BPF指令集

![image-20230719215846646](高效入门eBPF.assets/image-20230719215846646.png)

#### BPF指令集与BPF字节码

![image-20230719215935022](高效入门eBPF.assets/image-20230719215935022.png)



![image-20230719220548910](高效入门eBPF.assets/image-20230719220548910.png)



![image-20230719220755695](高效入门eBPF.assets/image-20230719220755695.png)

#### eBPF指令格式

![image-20230719223631399](高效入门eBPF.assets/image-20230719223631399.png)

#### BPF虚拟机（内核解释器）

![image-20230719224815723](高效入门eBPF.assets/image-20230719224815723.png)

### 编译、加载、运行

![image-20230720214133555](高效入门eBPF.assets/image-20230720214133555.png)

注意这里的 `BPF_PROG_LOAD型bpf()系统调用`，后面要考

### 用户空间的BPF程序如何载入内核

![image-20230720214819600](高效入门eBPF.assets/image-20230720214819600.png)



![image-20230720221249165](高效入门eBPF.assets/image-20230720221249165.png)



![image-20230720223021407](高效入门eBPF.assets/image-20230720223021407.png)



![image-20230720223455134](高效入门eBPF.assets/image-20230720223455134.png)

### BPF虚拟机执行的时机

![image-20230720223658848](高效入门eBPF.assets/image-20230720223658848.png)

## BPF 系统调用：bpf()

![image-20230720214532028](高效入门eBPF.assets/image-20230720214532028.png)

## BPF 描述符 (bpf_prog)、BPF程序类型、BPF存储类型

### BPF描述符（bpf_prog）

![image-20230720214700053](高效入门eBPF.assets/image-20230720214700053.png)

### BPF程序类型（Hook点）

![image-20230720224025836](高效入门eBPF.assets/image-20230720224025836.png)

### BPF存储类型（Map）

![image-20230720224152260](高效入门eBPF.assets/image-20230720224152260.png)

## BPF辅助函数

![image-20230720224303473](高效入门eBPF.assets/image-20230720224303473.png)

## 如何使用BPF：BPF编程

### 三种方式

![image-20230720224432524](高效入门eBPF.assets/image-20230720224432524.png)

### BPF指令集编程

![image-20230720224704333](高效入门eBPF.assets/image-20230720224704333.png)

### BPF C编程

![image-20230720224820134](高效入门eBPF.assets/image-20230720224820134.png)

### BPF前端编程 - BCC

![image-20230720224944831](高效入门eBPF.assets/image-20230720224944831.png)



![image-20230720225402882](高效入门eBPF.assets/image-20230720225402882.png)

## BPF学习资料

![image-20230720225535360](高效入门eBPF.assets/image-20230720225535360.png)

# LMP

![image-20230720225815565](高效入门eBPF.assets/image-20230720225815565.png)



![image-20230720230918962](高效入门eBPF.assets/image-20230720230918962.png)



![image-20230720231128842](高效入门eBPF.assets/image-20230720231128842.png)



![image-20230720231339419](高效入门eBPF.assets/image-20230720231339419.png)



![image-20230720231714042](高效入门eBPF.assets/image-20230720231714042.png)



![image-20230720231728706](高效入门eBPF.assets/image-20230720231728706.png)



![image-20230720232959712](高效入门eBPF.assets/image-20230720232959712.png)

























