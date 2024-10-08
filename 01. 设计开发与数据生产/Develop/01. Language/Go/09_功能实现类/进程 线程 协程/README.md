# README

## 【概念】进程 线程 协程

### 介绍

- 程序 (Program)：用某种语言写的为了完成特定任务的一组指令集合，静态的
- 进程 (Process)：程序一次执行过程。每个进程有不同的内存区域（虚拟内存），有产生、存在、消亡的生命周期
  - 系统相关：**计算机系统资源的分配单位**
  - 上下文切换需要保存和恢复
    - (都要部分，见下总结)
    - 内存管理信息：页表、内存分段信息等
    - I/O状态信息：打开的文件描述符、网络连接等
    - 系统资源信息：CPU使用时间、内存使用量等
    - CPU调度信息：如进程优先级、调度队列等，确保调度策略的一致性

- 线程 (Thread)：进程可细分为线程。可同一时间执行（并发）
  - 系统相关：**CPU调用的单位**
  - 上下文切换需要保存和恢复
    - (都要部分，见下总结)
    - 线程栈
    - 线程栈 状态：包括线程的优先级、线程标识符（TID）、线程的状态（运行、就绪、阻塞等）等
    - 线程栈帧 特有的同步数据

- 协程 (Goroutine)：又称微线程，纤程、轻量级线程。本质还是一个线程
  - 系统相关：无关，**纯用户态的**
  - 上下文切换需要保存和恢复
    - (都要部分，见下总结)
    - 协程栈
    - 协程栈 通道和调度信息
    - 协程栈帧 用户定义的数据

- 总结
  - 上下文切换需要保存和恢复：“都要” 指：
    - 寄存器：程序计数器（PC）、堆栈指针（SP）、状态寄存器、通用寄存器等。
    - 状态信息：包括进程或线程的优先级、标识符、状态等


### 选用

- 指导版
  - 越往上隔离越好，越往下则上下文的切换消耗越小
- 具体版
  - 进程
    - CPU密集型 (充分利用多核)
    - 用户操作权限高 (利用隔离与崩溃不影响，如Linux多用户、Docker多容器)
  - 线程 / 协程
    - I/O密集型 (因为IO处理主要为等待时间，而处理时间极短。即切换频繁，减少切换损耗是重中之重)
    - 高并发 (高并发也意味着切换次数多，1s内的切换次数非常高。即切换频繁，减少切换损耗是重中之重)
    - 快速响应 (快速响应需要上下文开销小)
- 落地版
  - 多进程：Web服务器（如 Apache HTTP Server，支持多种)、某些数据库服务器（如PostgreSQL的早期版本）、传统的UNIX系统服务、Linux的多用户、Docker、云主机
  - 多线程：Web服务器（如 Apache HTTP Server，支持多种)、某些数据库服务器（如MySQL）
  - 多协程：Python的Tornado、asyncio库，Node.js的Express、事件循环
- GPT版
  - 服务器对于多个客户端，有的选择多进程/线程/协程。 分别是哪些服务或库选择 多进程/线程/协程，为什么？
  - 多进程：每个进程拥有独立的内存空间，这使得它们在稳定性上具有优势。如果一个进程崩溃，它不会影响到其他进程的运行
  - 多线程：创建和上下文切换的开销较小。线程共享进程的内存空间，这使得线程间的数据交换更加高效。多线程模型适用于I/O密集型应用，因为线程可以在等待I/O操作完成时让出CPU给其他线程
  - 多协程：适合于高并发、低延迟的网络应用，因为它们可以在等待一个操作完成时执行其他协程，从而提高资源利用率

### 冲突解决

原子变量在底层可能使用的一些技术

- 原语类

  - 原子原语：由CPU直接支持，例如，通过使用特定的原子指令集，如x86架构中的 `LOCK` 前缀指令。这些指令可以确保当前指令执行期间，CPU不会执行其他内存操作，从而保证操作的原子性。

  - 原子指令：现代CPU通常提供了一系列**原子指令**，如比较并交换（Compare-And-Swap，CAS）、加载并链接（Load-Link）、存储并条件（Store-Conditional）等。

    与原子原语有相似的地方：原子指令是一组封装了原子操作的指令，它们通常是**由CPU原语**构成的

  - 同步原语

    软件层面上实现线程间同步的一种机制。它们通常是**由原子指令组成**的，但提供了更高层次的抽象

- 内存屏障：（Memory Barrier）是一种硬件级别的同步机制，它可以确保屏障之前和之后的操作按照预期的顺序执行。在实现原子操作时，内存屏障可以**防止编译器和CPU对指令进行重排序**，确保操作的顺序性。

- 编译器支持：（非手动解决冲突）编译器也可能在生成代码时考虑到原子性。例如：通过插入适当的内存屏障或使用特定的CPU指令来确保操作的原子性

- 锁机制：虽然原子操作通常不使用传统的锁机制，但在某些情况下，硬件和操作系统可能使用一种特殊的锁（例如，总线锁或缓存锁）来确保只有一个处理器可以访问特定的内存区域