# Boost

参考：

- 官网资料
  - 官网：https://www.boost.org/
  - 官网文档：(以1_83_0 为例)
    - GettingStarted：https://www.boost.org/doc/libs/release/more/getting_started/index.html
      没有大纲、排版也很糟糕，搞得我还以为没内容，原来内容在右下的一下行超链接：
      Next: [Getting Started on Microsoft Windows](https://www.boost.org/doc/libs/1_83_0/more/getting_started/windows.html) or [Getting Started on Unix variants (e.g. Linux, MacOS)](https://www.boost.org/doc/libs/1_83_0/more/getting_started/unix-variants.html)
    - Reference：https://www.boost.org/doc/libs/1_83_0
    
  - 官网下载：https://boostorg.jfrog.io/artifactory/main/release/
  - 编译说明文档：https://boostorg.github.io/build/manual/master/index.html
  
- 新文档（官网文档太丑辣）
  - http://zh.highscore.de/cpp/boost/（还不错，虽然还是有点丑，但大纲整齐，相比原文档好很多了）
  - https://groups.google.com/g/boost_doc_translation/c/iZdiPl8T-78?pli=1

- 视频：好像没什么比较好的
  - [【C++】C++组件库Boost](https://www.bilibili.com/video/BV1hG411i7XR)
  - [Boost深入剖析之使用技巧](https://www.bilibili.com/video/BV1C5411a74F)

## 目录

首先说明：

1. Boost项目的**Git子模块**非常多，或者说里面的子库几乎都是子模块，可以根据子模块对目录进行进一步拆解
2. 从官网直接下载的压缩包，和Github上的源码路径有略微不同



个人整理：

boost_1_83_0

- (bin.v2/)，运行b2.exe后生成，文件夹非常大
- boost/，**按子库再细分**。所有Boost头文件，即里面的各种子库。**在源代码里是没有这一项的，直接下载则是有的**
  - any
  - any.hpp
  - ……
- (lib/)，编译后才有，预编译的二进制库文件
- libs/，**按子库再细分**。包括：测试程序、cpp源码、文档等
- status/，~~运行b2.exe后生成~~，“Boost-wide test suite”
- tools/，一些公用的东西，例如：Boost.Build, quickbook, bcp
  - build/src/engine/b2.exe，这两个exe文件是一样的，但和根的那个b2.exe不同
  - build/src/engine/bjam.exe，这两个exe文件是一样的，但和根的那个b2.exe不同
- (b2.exe)，运行booststrap之后才会出现这个文件，默认安装再点击这个Build Boost C++ Libraries.
- boost-build.jam
- boostcpp.jam
- bootstrap.bat，Windows运行这个编译 bjam
- (boot)
- strap.sh，Linux运行这个 bjam
- INSTALL
- Jamroot
- (project-config.jam)，运行b2.exe后生成
- (文档类)
  - doc/，所有Boost库文档的子集
  - more/，一些额外的Policy文档等。这是Git子模块来的
  - boost.css
  - boost.png
  - index.htm，www.boost.org 的拷贝
  - index.html，www.boost.org 的拷贝
  - LICENSE_1_0.txt
  - README.md
  - rst.css

## 编译

官方说法是：

> 许多人想知道的第一件事是，“我该如何构建 Boost？好消息是，通常没有什么可构建的。
>
> 没什么可建的？
>
> 大多数 Boost 库都是仅标头的：它们完全由包含模板和内联函数的头文件组成，在链接时不需要单独编译库二进制文件或特殊处理。

## 初始项目

这种库的使用只有两个要点

1. 找到头文件。在 `boost源码/boost/` 里
2. 能链接

只要能达到这两点，方法非常多（见GPT小节）

### Git子模块 + 编译方式

Git方式

1. 终端

   ```bash
   git submodule add https://github.com/boostorg/boost.git ./3rdparty/boost
   
   # 首次递归拉取。boost子项目很多，这一步耗时比较久，但编译却意外地不怎么耗时间
   git submodule update --init --recursive
   
   # 后续更新
   git submodule status
   git submodule update --recursive --remote
   ```

2. CMakeList.txt增加

   ```cmake
   add_subdirectory(3rdparty/boost)
   include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/boost)
   ```

3. 然后按理说正常使用就行了。父项目能正常使用头文件，也能正常编译了



遇到的问题：

- 子项目依赖的拉取、项目庞大
- 源码没有boost文件夹，无法直接 include 源文件

### 使用标头的库

即只使用纯 .hpp 的部分，只有个别库需要单独构建

参考：https://www.boost.org/doc/libs/1_84_0/more/getting_started/windows.html



### windows - bat安装方式

1. 不要直接双击bootstrap.bat，要在MSVC命令行中调用bat文件。
   VS：开始菜单 > Visual Studio 2019 > 找到**Developer Command Prompt...**打开
   QT：找到**Qt 6.0.3 (MSVC 2019 64-bit)**打开
   命令行中cd到boost解压路径并执行 `bootstrap.bat`
   （我个人放在了 D:\Soft\Dev\Language\C++\boost_1_78_0）
2. 然后依然是在MSVC命令行中调用`bjam.exe`

### （GPT）

如何在工程中优雅地使用boost？

1. 直接在官网下载后安装，然后使用里面/boost下的头文件
2. 通过github的submodule方式引入（但具体不知道怎么做，源码没有/boost路径，头文件分散在各个子库中），并且通过CMakeList.txt形成依赖，编译时自动install boost
3. 其他你认为优雅的方案

---

Boost库是一个C++的扩展库，它为C++提供了许多强大的功能，包括智能指针、泛型编程、并行计算等。在工程中使用Boost库，可以极大地提高编程效率和程序的性能。下面是一些在工程中优雅地使用Boost的方法：

1. **直接下载并安装**：这是最直接的方法。你可以从Boost官网下载最新的源码包，然后按照官方的安装指南进行安装。安装完毕后，你就可以在你的程序中直接包含Boost的头文件，并使用Boost提供的各种功能了。

2. **通过包管理器安装**：如果你的系统有包管理器（如Ubuntu的apt，CentOS的yum，或者macOS的brew），你也可以通过包管理器来安装Boost。这样做的好处是，包管理器会自动处理Boost的依赖关系，并且可以自动更新Boost到最新版本。

3. **使用CMake和git submodule**：如果你的项目使用了git作为版本控制系统，并且使用CMake作为构建系统，你可以把Boost作为一个git submodule添加到你的项目中。然后你可以在CMakeLists.txt文件中添加一些命令，让CMake在构建你的项目时自动构建Boost。这样做的好处是，你可以确保你的项目总是使用相同版本的Boost，而不需要担心系统中的Boost版本与你的项目不兼容。

   具体操作如下：

   - 在你的项目根目录下，执行`git submodule add https://github.com/boostorg/boost.git`，添加Boost作为你的项目的一个子模块。

   - 在你的CMakeLists.txt文件中，添加以下命令：

     ```cmake
     add_subdirectory(boost)
     include_directories(${CMAKE_CURRENT_SOURCE_DIR}/boost)
     ```

   - 然后你就可以在你的代码中直接包含Boost的头文件了。

4. **使用vcpkg**：vcpkg是一个跨平台的C++包管理器，它支持大量的C++库，包括Boost。使用vcpkg安装Boost非常简单，只需要执行`vcpkg install boost`就可以了。然后你可以在你的CMakeLists.txt文件中添加以下命令，让CMake自动找到vcpkg安装的Boost：

   ```cmake
   find_package(Boost REQUIRED)
   include_directories(${Boost_INCLUDE_DIRS})
   ```

5. **使用conan**：conan也是一个跨平台的C++包管理器，它的使用方法与vcpkg类似。你可以执行`conan install boost`来安装Boost，然后在你的CMakeLists.txt文件中添加以下命令，让CMake自动找到conan安装的Boost：

   ```cmake
   include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
   conan_basic_setup()
   ```

以上就是一些在工程中优雅地使用Boost的方法，你可以根据你的实际需求和环境选择最适合你的方法。











