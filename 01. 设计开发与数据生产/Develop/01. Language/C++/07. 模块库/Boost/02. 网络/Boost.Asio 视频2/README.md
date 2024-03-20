# Boost.Asio视频

参考：

- [（C++后台开发）C++网络编程：网络库 Boost.Asio入门、应用案例](https://www.bilibili.com/video/BV12X4y187gd) (1:38:46)

## 调研 - 跨平台网络库

### 调研 - 跨平台网络库

- 主要用于linux，事件回调
  - libevnet (用过)
  - libev
  - libuv
  - libhv (用过)
- 异步IO
  - boost.asio

### 同步io与异步io

#### 接口上差异

- 同步io
  - 阻塞io网络模式：read、accept、connect、write
- 异步io
  - 原生系统IO API：fcntl() 设置socket为非阻塞IO
  - libevent库：onWrite、onRead / onMessage、onConnect
  - asio库：WSARecv、AcceptEx、ConnectEx、WSASend

#### 系统 IO API

- select：**跨平台**
- poll：**跨平台**
- epoll：**Windows不支持**
- icop：**Linux不支持**

#### 网络模型

- reactor模型：又称反应器模式，基于事件回调。通常是Linux使用
- iocp (I/O Completion Port，输入/输出完成端口) 网络模型：基于事件回调。通常Windows使用
- Proactor模型

#### 库

- asio
  - 同步/异步：支持同步和异步IO
  - 网络模型：支持Reactor模型和Proactor模型
  - 系统 IO API
    - Unix/Linux，Asio使用epoll，kqueue，/dev/poll，select等系统调用
    - Windows，Asio使用IOCP
- libevent
  - 网络模型：Reactor模型
  - 系统 IO API
    - Unix/Linux/Windows，均为Reactor模型。Linux的epoll, BSD的kqueue，Windows的select
    - Windows上，虽然libevent也支持使用IOCP，但并不是作为主要的I/O模型，而是作为一种优化手段，在大量并发连接时会比select等方式效率更高

#### 原理上差异

- 阻塞io：去菜鸟驿站等货物到
- reactor io：注册一次，有货物来了就告诉我（不会送过来），货物到了后自己去取
  - epoll 检测，非阻塞io操作io，事件循环处理
- asio io、异步io：把篮子带过去，如果货物来了就驿站就将货物放篮子里并送货到家。然后需要将篮子再带过去等待下次货物

![image-20240320233534755](README.assets/image-20240320233534755.png)

![image-20240320233601799](README.assets/image-20240320233601799.png)

> ##### tips

一开始我将 reactor 看成是 react 了，要区分一下这两者

- reactor (/riˈæktər/)：reactor模型、reactor io
- react (/riˈækt/)：前端三大框架之一

### boost.asio 两个命名空间

需要知道两个命名空间：

- `boost::asio`
  - 核心类及函数：io_context
  - 同步IO函数：posix api (connect、accept、read_some、write_some)
  - 异步IO函数：(async_connect、async_accept、async_read_some、async_write_some)

- `boost::assio::ip`
  - 其中，boost::asio::ip 封装了socket、L4、L3
    - 用户态
    - 内核态
      - socket
      - L4 tcp/udp/icmp
      - L3 ip
      - L2 mac
      - L1 网卡

    - 网卡

  - 接口
    - ip地址：ip::address
    - 端点：ip::tcp::endpoint、ip::udp::endpoint
    - socket：ip::tcp::socket、ip::udp:socket
    - 套接字控制：set_option、get_option、io_control

## 开始

### 异常处理

- 同步io

  - boost同步io函数有两种结果接口：抛异常、错误码

    例如：connect(socket, boost::system::error_code err);

- 异步io

  - 例如：`async_read_some(buffer(data, length), [](boost::system::error_code err, size_t transferedBytes){});`
    这里的buffer是一个boost::asio::buffer对象

### 安装

Windows默认安装位置：C:/local/boost_1_82_0/

- boost/,  头文件
- doc/
- lib64-msvc-14.2/,  (我没有这个文件夹)，用VS时，库文件
- libs/
- more/
- status/
- tools/

要写根目录到环境变量，且不是Path里，而是BOOST_ROOT里

### 项目创建

VS创建一个CMake项目

```cmake
cmake_minimum_required (VERSION 3.8)

set(BOOST_ROOT $ENV{BOOST_ROOT})  # 获取环境变量里的路径 (可以去检查下有无设置)，存储在该文件的变量里

find_package(Boost 1.82 REQUIRED system regex)

# 链接库
set(BOSST_LIBRARY_DIR ${BOOT_ROOT}/lib64-msvc-14.2)  # 但我没有这个路径
link_directories(${BOOST_LIBRARY_DIR})

add_executable(asio "asio.cpp" "asio.h")

target_link_libraries(asio PUBLIC Boost::system Boost::regex)

# 头文件
set(BOOST_INCLUDE_DIR ${BOOT_ROOT})
target_include_directiories(asio PUBLIC ${BOOST_INCLUDE_DIR})
```

基本cpp

```cpp
#include "asio.h"
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::io;

int main() {
    io_context io_ctx;
    io_ctx.run();  // 阻塞等待，相当于reactor中的事件循环
    return 0;
}
```

补充完善

```cpp
#include "asio.h"
#include <boost/asio.hpp>
#include <memory>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::io;

class Seesion: public std::enable_shared_form_this<Session> {
public: 
    Session(tcp::socket sock): socket_(std::move(sock)) {
        
    }
    
    void Start() {
        do_read();
    }
private:
    void do_close() {
        boost::system::error_code err;
        socket_.close();
    }
    
    void do_read() {
        auto self(shared_form_this()); // 给自己的引用次数+1
        socket_.async_read_some(buffer(readBuffer_, max_packet_len), 
			[this, self](boost::system::error_code err, size_t transfered){ // 希望回调函数调用时，socket依然存在，这里需要用智能指针延长该类的生命周期
				if (err) {
                    do_close();
                    return;
                }
                
                do_read();
            });
    }
    
    void do_write() {
        auto self(shared_from_this());
        socket_.async_write_some(buffer(readBuffer_, max_packet_len),
            [this, self](boost::system::error_code err, size_t transfered){
                if (err) {
                    do_close();
                    return;
                }
                do_read();
        	}
		)
    }
    
    tcp::socket socket_;
    enum {max_packet_len = 1024};
    char buffer[max_packet_len];
}

class Server {
public:
    Server(io_context &io_ctx, short port): acceptor_(io_ctx, tcp::endpoint(tcp::v4(), port)) {
        
    }
private:
    void do_accept() {
        acceptor_.async_accept(
        	[this](boost::system::error_code err, tcp::socket_sock) {
                if (!err) {
					std::make_shared<Session>(sock)->Start();
                }
            }
        )
    }
    
    tcp::acceptor acceptor_;
}

int main() {
    io_context io_ctx;
    
    // tcp::acceptor accept_(io_ctx, 000);
    
    io_ctx.run();  // 阻塞等待，相当于reactor中的事件循环
    return 0;
}
```























