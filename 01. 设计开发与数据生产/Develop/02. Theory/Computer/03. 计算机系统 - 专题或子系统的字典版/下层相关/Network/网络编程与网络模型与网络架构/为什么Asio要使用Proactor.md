# 为什么Asio要使用Proactor

参考：

- [为何 Boost 的 Asio 要使用 Proactor 模式实现？](https://www.cnblogs.com/my_life/articles/5329955.html)
  - https://www.zhihu.com/question/22064431

## Proactor和Reactor的跨平台问题

一般来说Linux用Reactor更友好，Windows用Proactor更友好。但库为了兼容性，目前是这样的：

- Libevent
  - Linux：Libevent优先选择 **epoll** 作为其事件通知机制。**Reactor** 模型
  - Windows：如果系统不支持epoll，那么Libevent会选择poll或者select。在Windows平台上，Libevent使用 **select** 作为事件通知机制。**Reactor** 模型
- Asio
  - Windows：**IOCP**。**Reactor** 模型
  - Linux：Asio使用 **epoll** 作为其事件通知机制。如果系统不支持epoll，那么Asio也可以选择使用poll或者select。
    Asio同时还提供了一个 **模拟的 Proactor** 模式（与reactor模式相对），可以在不支持异步操作的平台上模拟异步操作，从而提供统一的API。

### Linux用Proactor存在的问题

**Linux**下高性能的网络库中大多使用的 **Reactor模式** 去实现
Boost Asio在 Linux 下用epoll和select去 **模拟proactor模式** ，影响了它的效率和实现复杂度,

看陈硕的自己的Linux下Reactor网络库和ASIO的性能对比，大概比asio性能(吞吐量)高1/5.既然Linux下网络库用Reactor性能才高,为什么Boost ASIO Linux下要用模拟的Proactor模式?
或者说为什么ASIO不在win和linux都用Reactor模式?这样的选择是不是可以性能更好？和更加适应市场？服务器端毕竟大量都是Linux.

### Windows用Reactor存在的问题

Windows 下很难实现高效可伸缩的 Reactor。

- 首先，Win32 API 里 WaitForMultipleObjects 只能同时等待 64 个 handle  (MAXIMUM_WAIT_OBJECTS)；
- 其次 WinSock 的 select() 实现又很  buggy，特别是在错误处理方面有很多奇葩行为（具体见各种跨平台网络库代码中对此的注释）；
- 最后，Windows Vista 新增的  WSAPoll() 函数与 POSIX 的 poll() 又不尽兼容（ [http://daniel.haxx.se/blog/2012/10/10/wsapoll-is-broken/](http://link.zhihu.com/?target=http%3A//daniel.haxx.se/blog/2012/10/10/wsapoll-is-broken/) ）。

### 总结

那么现在有两种方案，分别是Libevent和Asio的所用方案。

Asio方案的优点：（详见后面的大章）

- 文件和网络IO
  - Windows 有自己的一套高效异步IO模型（几乎等同于Proactor），同时支持**文件IO和网络IO**；
  - 但 Linux 只有高效的**网络同步IO**（epoll 之类的 io multiplexing 是同步的Reactor，且不支持磁盘文件）。
- 二者的高效IO编程模型从根本上**不兼容**（Windows 可以把网络事件发到 GUI 线程的事件队列中，有点类似 Reactor，但是似乎一个进程只能有一个 GUI 线程，因此在多核系统上其伸缩性受限）。
- Proactor的编程模型相比Reactor要更自然一些,而且在操作系统有支持的情况下，能获得更好的性能。所以一个通用网络库，选择Proactor作为接口语义并不奇怪。只是他们没想到，Linux社区对于填上aio的坑并没太大的动力 (或则足够的实力?)，这基于epoll的模拟Proactor实现一用就是数十年~

## Linux aio的坑

https://cnodejs.org/topic/4f16442ccae1f4aa270010a7

 

在高性能的服务器编程中，IO 模型理所当然的是重中之重，需要谨慎选型的，对于网络套接字，我们可以采用epoll 的方式来轮询，尽管epoll也有一些缺陷，但总体来说还是很高效的，尤其来大量套接字的场景下；但对于Regular File 来说，是不能够用采用 poll/epoll 的，即O_NOBLOCK 方式对于传统文件句柄是无效的，也就是说我们的 open ,read, mkdir 之类的Regular File操作必定会导致阻塞. 

 

Linux AIO 早就被提上议程，目前比较知名的有 Glibc 的 AIO  与 Kernel Native AIO 
Glibc AIO: http://www.ibm.com/developerworks/linux/library/l-async/ 
Kernel Native AIO: http://lse.sourceforge.net/io/aio.html 

我们用Glibc 的AIO 做个小实验，写一个简单的程序：异步方式读取一个文件，并注册异步回调函数： 

### 代码

略

## Why Proactor ?

在给 c++ 老人会的引荐信里，asio 之父仔细阐述了asio的设计抉择回答了围绕 asio 的设计提出的很多问题。

为什么 Proactor 会是最佳模型？

- 优点

  - **跨平台**。许多操作系统都有异步API，即便是没有异步API的Linux, 通过 epoll 也能模拟 Proactor 模式。

  - **支持回调函数组合**。将一系列异步操作进行组合，封装成对外的一个异步调用。这个只有Proactor能做到，Reactor 做不到。意味着如果asio使用Reactor模式，就对不起他“库” 之名。

  - **零拷贝**。相比 Reactor 可以实现 Zero-copy

  - **和线程解耦**。长时间执行的过程总是有系统异步完成，应用程序无需为此开启线程

- 缺点

  - 内存占用比 Reactor 大。Proactor 需要先分配内存而后处理IO，而  Reactor 是先等待 IO  而后分配内存。相对的Proactor却获得了Zero-copy好处。因为内存已经分配好了，因此操作系统可以将接受到的网络数据直接从网络接口拷贝到应用程序内存，而无需经过内核中转。
    Proactor 模式需要一个 loop ,这个 loop asio 将其封装为 io_service.他不仅是 asio的核心，更是一切基于asio设计的程序的核心。

## 宇宙级异步核心

io_service 脱胎于 IO 但不仅用于 IO. Christopher Kohlhoff 在给委员会的另一份编号 N3747  的信上上说它是 ~~宇宙级异步模型~~ Universal Asynchronous Model。在宇宙级异步模型里，一个异步操作由三部分构成

1. 发起。按照 asio 的编码规范，所有的发起操作都使用 async_ 前缀，使用 async_动词 的形式作为函数名。
2. 执行。异步过程在发起的时候被executor执行（系统可以是支持 AIO 的内核，不支持 AIO 的系统则是 aiso 用户层模拟）
3. 完成并回调。在发起 async_* 操作的时候，总是携带一个回调的闭包。**asio使用闭包作为异步事件完成的处理回调，而不是C式的回调函数**。asio的宇宙异步模型里，回调总是在执行 io_service::run 的线程里执行。asio绝不会在内部线程里调用回调。

在回调里发起新的异步操作，一轮套一轮。整个程序就围绕着 io_service::run 运转起来了。
io_service 不仅仅能用于异步 IO ,还可以用来投递任意闭包,实现作为线程池的功能。这一通用型异步模型彻底击败微软 PPL 提案，致使微软转而研究协程。然而微软在协程上同样面临 asio 的绞杀。

## 闭包和协程

宇宙级 asio 使用闭包作为回调，而 C 库只能使用函数+void*, ACE 虽然使用的 C++语言，却不知道闭包为何物，使用的是 虚函数作为回调，需要大量的从 ACE 的对象继承。

以闭包为回调，asio更是支持了一种叫“无栈协程”的强悍武器。【**不用栈保存状态，用闭包通过不停的拷贝更新状态**】
asio的**无栈协程**，仅仅通过库的形式，不论是在性能上，还是易用性上，还是简洁性上，甚至是B格上，都超过了微软易于修改语言而得的 await提案。

微软、乃至 ACE ，并不是不知道闭包，而是在c++里实现闭包的宇宙级executor —— 也就是 io_service，需要对模板技术的精通。
asio “把困难留给自己，把方便带给大家”，以地球人无法理解的方式硬是在 c++98 上实现了宇宙级异步核心。
当然，如果 c++11 早点出现，如果 c++17 早点出现，实现 asio 的宇宙模型会更加的简单 —— 其实这也是 c++ 的理念，增加语言特性，只是为了让语言用起来更简单。

## buffers

有了闭包的支持，内存管理也变得轻轻松松起来。
ASIO **本身并不管理内**存，所有的IO操作，只提交对用户管理的内存的引用，称 Buffers。asio::buffers 引用了用户提交的内存，保持整个 IO 期间，这块内存的有效性是用户的责任。然而这并不难！

因为回调是一个闭包。通过闭包持有内存，只要 asio 还未回调，闭包就在，闭包在，内存在。asio 在调用完回调后才删除相应的闭包。因此资源管理的责任可以丢给闭包，而闭包可以通过智能指针精确的控制内存。
不是 GC , 胜于 GC 千百倍！益于c++的 RAII机制，再无内存泄漏之忧！





















