# Reactor vs Proactor模式2

参考：[高性能IO模型分析-Reactor模式和Proactor模式（二）](https://blog.csdn.net/lpf463061655/article/details/103403881)

上一章内容是本章内容的理论基础和底层依赖。本章内容则是在上章内容作为底层的基础，经过巧妙的设计和前赴后继的实践，得出的一套应用层的“最佳实践”。虽不是开箱即用，但也为我们提供了很大的便利，让我们少走很多弯路。下面我们就看看有哪些不错的架构模型、模式值得我们去参考。 

在web服务中，处理web请求通常有两种体系结构，分别为：

- thread-based architecture（基于线程的架构）
- event-driven architecture（事件驱动模型）

## thread-based architecture（基于线程的架构）

thread-based architecture（基于线程的架构），通俗的说就是：[多线程](https://so.csdn.net/so/search?q=多线程&spm=1001.2101.3001.7020)并发模式，一个连接一个线程，服务器每当收到客户端的一个请求， 便开启一个独立的线程来处理。

![多线程并发](https://img-blog.csdnimg.cn/20191205142035183.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xwZjQ2MzA2MTY1NQ==,size_16,color_FFFFFF,t_70)

一定程上极大地提高了服务器的吞吐量，由于在不同线程中，之前的请求在read阻塞以后，不会影响到后续的请求。

但是，仅适用于于并发量不大的场景，如果连接数太高，系统将无法承受。因为：

- 线程**存在**需要占用一定的内存资源
- **创建和销毁**线程也需一定的代价
- 操作系统在**切换**线程也需要一定的开销
- 线程处理I/O，在等待输入或输出的这段时间处于**空闲**的状态，同样也会造成cpu资源的**浪费**

## event-driven architecture（事件驱动模型）

事件驱动体系结构是目前比较广泛使用的一种。这种方式会定义一系列的事件处理器来响应事件的发生，并且将服务端接受连接与对事件的处理分离。其中，事件是一种状态的改变。比如，tcp中socket的new incoming connection、ready for read、ready for write。

如果对event-driven architecture有深入兴趣，可以看下维基百科对它的解释：传送门

Reactor模式和Proactor模式都是是event-driven architecture（事件驱动模型）的实现方式，下面聊一聊这两种模式。

### Reactor模型

维基百科对`Reactor pattern`的解释

> 反应器设计模式是一种事件处理模式，用于处理通过一个或多个输入并发地传递给服务处理程序的服务请求。
> 然后，服务处理程序将传入的请求解复用，并将它们同步地分派给相关的请求处理程序

从这个描述中，我们知道Reactor模式首先是事件驱动的，有一个或多个并发输入源，有一个Service Handler，有多个Request Handlers；
Service Handler会对输入的请求（Event）进行多路复用，并同步地将它们分发给相应的Request Handler。

下面的图将直观地展示上述文字描述：

![Reactor_Simple](https://img-blog.csdnimg.cn/20191205142204185.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xwZjQ2MzA2MTY1NQ==,size_16,color_FFFFFF,t_70)

Reactor模式也有三种不同的方式，下面一一介绍：

#### Reactor模式 - 单线程模式

Java中的NIO模式的Selector网络通讯，其实就是一个简单的Reactor模型。可以说是单线程的Reactor模式

![Reactor-单线程模式](https://img-blog.csdnimg.cn/2019120514232136.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xwZjQ2MzA2MTY1NQ==,size_16,color_FFFFFF,t_70)

单线程模式的单线程主要是针对于I/O操作而言，也就是所以的I/O的accept()、read()、write()以及connect()操作都在一个线程上完成的。

但在目前的单线程Reactor模式中，不仅I/O操作在该Reactor线程上，连非I/O的业务操作也在该线程上进行处理了，这可能会大大延迟I/O请求的响应。所以我们应该将非I/O的业务逻辑操作从Reactor线程上卸载，以此来加速Reactor线程对I/O请求的响应。

#### Reactor模式 - 工作者线程池模式

与单线程模式不同的是，添加了一个**工作者线程池**，并将非I/O操作从Reactor线程中移出转交给工作者线程池（Thread Pool）来执行。这样能够提高Reactor线程的I/O响应，不至于因为一些耗时的业务逻辑而延迟对后面I/O请求的处理。

![Reactor工作者线程模式](https://img-blog.csdnimg.cn/20191205143707668.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xwZjQ2MzA2MTY1NQ==,size_16,color_FFFFFF,t_70)

在工作者线程池模式中，虽然非I/O操作交给了线程池来处理，但是**所有的I/O操作依然由Reactor单线程执行**，在高负载、高并发或大数据量的应用场景，依然较容易成为瓶颈。所以，对于Reactor的优化，又产生出下面的多线程模式。

#### Reactor模式 - 多线程模式

对于多个CPU的机器，为充分利用系统资源，将Reactor拆分为两部分：mainReactor和subReactor

![Reactor多线程模式](https://img-blog.csdnimg.cn/20191205143733380.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xwZjQ2MzA2MTY1NQ==,size_16,color_FFFFFF,t_70)

mainReactor负责监听server socket，用来处理网络新连接的建立，将建立的socketChannel指定注册给subReactor，通常一个线程就可以处理 ；

subReactor维护自己的selector, 基于mainReactor 注册的socketChannel多路分离I/O读写事件，读写网络数据，通常使用多线程；

对非I/O的操作，依然转交给工作者线程池（Thread Pool）执行。

此种模型中，每个模块的工作更加专一，耦合度更低，性能和稳定性也大量的提升，支持的可并发客户端数量可达到上百万级别。关于此种模型的应用，目前有很多优秀的框架已经在应用了，比如mina和netty 等。Reactor模式-多线程模式下去掉工作者线程池（Thread Pool），则是Netty中NIO的默认模式。

- mainReactor对应Netty中配置的BossGroup线程组，主要负责接受客户端连接的建立。一般只暴露一个服务端口，BossGroup线程组一般一个线程工作即可
- subReactor对应Netty中配置的WorkerGroup线程组，BossGroup线程组接受并建立完客户端的连接后，将网络socket转交给WorkerGroup线程组，然后在WorkerGroup线程组内选择一个线程，进行I/O的处理。WorkerGroup线程组主要处理I/O，一般设置2*CPU核数个线程

### Proactor模型

流程与Reactor模式类似，区别在于proactor在IO ready事件触发后，**完成IO操作再通知应用回调**。

虽然在linux平台还是基于epoll/select，但是内部实现了异步操作处理器(Asynchronous Operation Processor)以及异步事件分离器(Asynchronous Event Demultiplexer)将IO操作与应用回调隔离。经典应用例如boost asio异步IO库的结构和流程图如下：

![Proactor](https://img-blog.csdnimg.cn/20191205143949109.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xwZjQ2MzA2MTY1NQ==,size_16,color_FFFFFF,t_70)

再直观一点，就是下面这幅图：

![Proactor模式](https://img-blog.csdnimg.cn/20191205143842183.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xwZjQ2MzA2MTY1NQ==,size_16,color_FFFFFF,t_70)

再再直观一点，其实就回到了五大模型-异步I/O模型的流程，就是下面这幅图：

![proactor2](https://img-blog.csdnimg.cn/20191205144014675.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xwZjQ2MzA2MTY1NQ==,size_16,color_FFFFFF,t_70)

针对第二幅图在稍作解释：

Reactor模式中，用户线程通过向Reactor对象注册感兴趣的事件监听，然后事件触发时调用事件处理函数。而Proactor模式中，用户线程将AsynchronousOperation（读/写等）、Proactor以及操作完成时的CompletionHandler注册到AsynchronousOperationProcessor。

AsynchronousOperationProcessor使用Facade模式提供了一组异步操作API（读/写等）供用户使用，当用户线程调用异步API后，便继续执行自己的任务。AsynchronousOperationProcessor 会开启独立的内核线程执行异步操作，实现真正的异步。当异步IO操作完成时，AsynchronousOperationProcessor将用户线程与AsynchronousOperation一起注册的Proactor和CompletionHandler取出，然后将CompletionHandler与IO操作的结果数据一起转发给Proactor，Proactor负责回调每一个异步操作的事件完成处理函数handle_event。虽然Proactor模式中每个异步操作都可以绑定一个Proactor对象，但是一般在操作系统中，Proactor被实现为Singleton模式，以便于集中化分发操作完成事件。

### 两种模型的总结

- 主动和被动

  以主动写为例：

  - Reactor将handler放到select()，等待可写就绪，然后调用write()写入数据；写完处理后续逻辑；

  - Proactor调用aoi_write后立刻返回，由内核负责写操作，写完后调用相应的回调函数处理后续逻辑
  - Reactor模式是一种被动的处理，即有事件发生时被动处理。而Proator模式则是主动发起异步调用，然后循环检测完成事件。

- 实现

  - Reactor实现了一个被动的事件分离和分发模型，服务等待请求事件的到来，再通过不受间断的同步处理事件，从而做出反应；
  - Proactor实现了一个主动的事件分离和分发模型；这种设计允许多个任务并发的执行，从而提高吞吐量。
  - 所以涉及到文件I/O或耗时I/O可以使用Proactor模式，或使用多线程模拟实现异步I/O的方式。

- 优点

  - Reactor实现相对简单，对于链接多，但耗时短的处理场景高效；

    - 操作系统可以在多个事件源上等待，并且避免了线程切换的性能开销和编程复杂性；

    - 事件的串行化对应用是透明的，可以顺序的同步执行而不需要加锁；

    - 事务分离：将与应用无关的多路复用、分配机制和与应用相关的回调函数分离开来。

  - Proactor在理论上性能更高，能够处理**耗时长的并发场景**。为什么说在理论上？请自行搜索Netty 5.X版本废弃的原因。

    > 废弃原因：使⽤ForkJoinPool后复杂度提升了，但是性能⽅⾯并没有明显的优势，反⽽给项⽬的维护带来了很⼤的⼯作量，因此还有到发布新版本的时机，所以将5.x废弃

- 缺点

  - Reactor处理耗时长的操作会造成事件分发的阻塞，影响到后续事件的处理；
  - Proactor实现逻辑复杂；依赖操作系统对异步的支持，目前实现了纯异步操作的操作系统少，实现优秀的如windows IOCP，但由于其windows系统用于服务器的局限性，目前应用范围较小；而Unix/Linux系统对纯异步的支持有限，应用事件驱动的主流还是通过select/epoll来实现。

- 适用场景

  - Reactor：同时接收多个服务请求，并且依次同步的处理它们的事件驱动程序；
  - Proactor：异步接收和同时处理多个服务请求的事件驱动程序。
    ux系统对纯异步的支持有限，应用事件驱动的主流还是通过select/epoll来实现。

- 适用场景

  - Reactor：同时接收多个服务请求，并且依次同步的处理它们的事件驱动程序；
  - Proactor：异步接收和同时处理多个服务请求的事件驱动程序。





























