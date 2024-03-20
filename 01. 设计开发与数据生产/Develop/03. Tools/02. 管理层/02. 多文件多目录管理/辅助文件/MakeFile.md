# MakeFile

# 目录

# 比较 make、cmake、qmake、nmake

## makefile

- 其他语言关联编译的方法（与C/C++不同）
    - 如果熟悉UNIX的 “**make**”工具（或者是Windows中的“**nmake**”等工具），可以认为**Java编译器内置了“make”功能**
    - C++一般是使用makefile，即**qmake** (QT) 或 **cmake** (通用) 来辅助编译
- 详细过程
    - 没有显式地编译Employee.java。然而，当Java编译器发现EmployeeTest.java使用了Employee类时会查找名为Employee.class的文件
    - 如果没有找到这个文件，就会自动地搜索Employee.java，然后，对它进行编译

## qmake vs cmake

- cmake获取：http://www.cmake.org
- 选用比较
    - qmake 是为 Qt 量身打造的，使用起来非常方便
    - cmake 使用上不如qmake简单直接，但复杂换来的是强大的功能
- 如何选择？
    - [Using CMake to Build Qt Projects](http://developer.qt.nokia.com/quarterly/view/using_cmake_to_build_qt_projects) 一文中说：
    - 对简单的Qt工程，采用 qmake
    - 对复杂度超过 qmake 处理能力的，采用 cmake
- 项目区别
    - 需要创建一个CMakeLists.txt文件，该文件很像是一个qmake.pro文件 

# CMake

## 介绍与准备

### 资料

-   官网：https://cmake.org/

-   官网文档（有点丑）：https://cmake.org/documentation/

-   官网教程（有点丑）：https://cmake.org/cmake/help/latest/guide/tutorial/index.html

-   .

-   [【B站】软件构建: CMake 快速入门](https://www.bilibili.com/video/BV1rR4y1E7n9)

-   0

### IDE的构建系统

平时使用的IDE大多都内置了构建系统，只是我们可能没有留意罢了。
他们都各有擅长的领域

-   .| GUN Make
-   .| Apache Ant
-   (万用)| Bazel| 能完成不同语言在不同环境的构建
-   (万用)| Buck| 能完成不同语言在不同环境的构建
-   C/C++较常用| CMake
-   Android| Gradle
-   .| Maven
-   VS| MSBuild
-   Qt| QMake

### 安装CMake

-   官网
-   操作系统自带的包管理工具（例如Linux的yum，winget的choco）
-   其他包管理工具，笔者使用的是 cygwin

安装后cmd看一下

```bash
cmake --version
```

### 安装编译工具

CMake 自身不带编译工具，要另外下clang、gcc、g++这些

然后需要指定工具链

## 使用

VSCode 为例

### 配置

原理：编写CMakeList.txt，该文件可以用来自动生成各目标平台下的工程文件。该过程在CMake中叫 `配置（Configure）`

例如：

-   VS| *.sln
-   Makefile
-   *.xcodeproj
-   ...



配置方法：

项目根目录下创建 CMakeLists.txt

```makefile
cmake_minimum_required(VERSION 3.10)	# 指定所需最低的CMake版本

project(Example)						# 工程名，输入的可执行文件同该名称

add_executable(Example main.cpp)		# 构建一个可执行文件，并指定源文件（这里只编译单个文件）
```



VSCode打开项目时会自动提示你进行项目 “配置”

VSCode命令：`Select a Kit for cmake`，选择一个平台原生的C++构建工具然后等配置即可

### 构建

F7，或VSCode命令：`cmake build`

## 使用 - 较复杂的例子

```makefile
cmake_minimum_required(VERSION 2.7)		# 指定所需最低的CMake版本

project(Blackhole)						# 工程名，输入的可执行文件同该名称

# 寻找第三方库
find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

# 匹配所有的源文件，存放于变量 SRC_FILES 中
file(GLOB SRC_FILES
	"${PROJECT_SOURCE_DIR}/src/*.h",
    "${PROJECT_SOURCE_DIR}/src/*.cpp",
    "${PROJECT_SOURCE_DIR}/src/*.c",
    "${PROJECT_SOURCE_DIR}/src/*.cc")

# 构建可执行文件，用之前匹配到的源文件来构建
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

# 第三方库
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm)

# 支持C++17
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)

add_custom_command(
	TARGET ${CMAKE_PROJECT_NAME}
	POST_BUILD							# 构建以后要做的事，这里将 <项目根目录>/assets 拷贝到 <项目根目录>/build/Debug/assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			"${PROJECT_SOUREC_DIR}/assets"
			"$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets")

```

## 第三方库的安装

常见的安装方式

1.   手动下载库的源文件。
     然后手动构建并指定CMake库的路径，`cd glfw`+`cmake -S . -B build`

2.   对于Linux和Mac，可以使用包管理工具安装
     例如 `sudo apt-get install libpng-dev`

     另外推荐：微软的开源工具：**vcpkg**（用于在Windows、Linux、MacOS上管理C和C++库）

## 一些其他常用的指令

```makefile
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DIR_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/core/src DIR_CORE)
```

用于在指定的目录中查找所有的源文件，并将文件名列表存储在变量中

```makefile
list(APPEND DIR_SRCS ${DIR_CORE})
list(APPEND DIR_SRCS ${DIR_UTILS})
list(APPEND DIR_SRCS ${DIR_ZIP})
list(APPEND DIR_SRCS ${DIR_IXWS})
list(APPEND DIR_SRCS ${DIR_ICMP})
list(APPEND DIR_SRCS ${DIR_UDP})
list(APPEND DIR_SRCS ${DIR_TRACEROUTE})
add_executable(${PROJECT_NAME} ${DIR_SRCS})
```

这是一个CMake命令，用于向一个列表变量中追加元素

```makefile
CMAKE_SOURCE_DIR # 源代码树的顶层目录，即包含顶层CMakeLists.txt文件的目录。
CMAKE_CURRENT_SOURCE_DIR # 当前处理的CMakeLists.txt文件所在的目录。（用得最多的）
CMAKE_BINARY_DIR # 构建树的顶层目录，即运行cmake命令的目录。
CMAKE_CURRENT_BINARY_DIR # 当前处理的CMakeLists.txt文件对应的构建目录。
PROJECT_SOURCE_DIR # 当前项目的源代码树的顶层目录，即包含project命令的CMakeLists.txt文件所在的目录。
projectName_SOURCE_DIR # 指定项目名（projectName）的源代码树的顶层目录。
```

一些路径的宏，这里还有更多：https://johnnado.com/cmake-directory-variables/









































