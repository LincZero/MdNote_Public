# 进程基础知识

先强调一下，我们本篇讲的主要都是操作系统理论知识，偏大学计算机专业课上的那种，并不是讲解 Linux 或 Windows 操作系统的实现方式，所以大家要区别一下。

想让了解 Linux 或 Windows 操作系统的具体实现，得去看这些操作系统的实现原理或者源码书籍。

## 总

### 概念类比

我们写好的一行行代码，为了让其工作起来，我们还得把它送进城**（进程）**里，那既然进了城里，那肯定不能胡作非为了。

城里人有城里人的规矩，城中有个专门管辖你们的城管**（操作系统）**，人家让你休息就休息，让你工作就工作，毕竟摊位不多，每个人都要占这个摊位来工作，城里要工作的人多着去了。

所以城管为了公平起见，它使用一种策略**（调度）**方式，给每个人一个固定的工作时间**（时间片）**，时间到了就会通知你去休息而换另外一个人上场工作。

另外，在休息时候你也不能偷懒，要记住工作到哪了，不然下次到你工作了，你忘记工作到哪了，那还怎么继续？

有的人，可能还进入了县城**（线程）**工作，这里相对轻松一些，在休息的时候，要记住的东西相对较少，而且还能共享城里的资源。

## 【比较】线程与进程的比较

不管是时间效率，还是空间效率线程比进程都要高

### 比较

- 核心
  - 进程是 **资源分配的单位**（资源包括内存、打开的文件等）
  - 线程是 **CPU 调度的单位**
- 资源
  - 进程拥有一个**完整的资源平台**（独立的虚拟内存）
  - 线程**只独享必不可少的资源，如寄存器和栈**
- 性能
  - 线程能减少并发执行的时间和空间开销
- 相同点
  - 线程同样具有就绪、阻塞、执行三种基本状态，同样具有状态之间的转换关系；

### 为什么线程比进程开销少（体现在）

- 资源少所以快
  - 创建快： 线程的创建时间比进程快，因为进程在创建的过程中，还需要资源管理信息，比如内存管理信息、文件管理信息，而线程在创建的过程中，不会涉及这些资源管理信息，而是共享它们；
  - 终止快： 线程的终止时间比进程快，因为线程释放的资源相比进程少很多；
  - 切换快： 同一个进程内的线程切换比进程切换快，因为线程具有相同的地址空间（虚拟内存共享），这意味着同一个进程的线程都具有同一个页表，那么在切换的时候不需要切换页表。而对于进程之间的切换，切换的时候要把页表给切换掉，而页表的切换过程开销是比较大的；
- 共享快： 由于同一进程的各线程间共享内存和文件资源，那么在线程之间数据传递的时候，就不需要经过内核了，这就使得线程之间的数据交互效率更高了；







