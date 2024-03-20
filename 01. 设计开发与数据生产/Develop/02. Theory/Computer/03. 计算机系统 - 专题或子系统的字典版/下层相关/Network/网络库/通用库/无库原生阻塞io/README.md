# 原生阻塞io

## select、poll、epoll、icop 区别

- 多路复用
  - **select**
    - 平台：**跨平台**
    - 每次都要从用户空间拷贝到内核空间
    - 遍历整个fd_set, 0(n)
    - 最大可监听的fd数量不能超过FD_SETSIZE
  - **poll**
    - 平台：**跨平台**
    - 类似于select，无FD_SETSISE限制
  - **epoll**
    - 平台：**Windows不支持**
    - 内核态、红黑树
    - 内存共享交互mmap
    - 不需要全部复制、返回双向链表
    - LT(level triggered) 水平触发。事件没有处理，一直触发。epoll_wiat
    - ET(edge triggered) 边缘触发。每当状态变化时触发一个事件
  - **icop** (I/O Completion Port，输入/输出完成端口)
    - 平台：**Linux不支持**
    - 线程池

