---
create_time: 20230502 16:44
---

# 构建管理

# 目录

# CMakeLists.txt

LincZero：在这一篇笔记开始之前，首先声明：我个人更倾向与使用小写的CMakeLists指令，所以笔记中会以小写为主

## 各语言的关键管理器

CMakeLists.txt和Makefile都是用来管理和自动化编译、构建C/C++项目的文件。它们可以指定编译器设置、链接库依赖和构建目标等信息。

- Cpp

  - `CMakeLists.txt`：这是CMake构建系统用的配置文件。CMake是一个跨平台的自动化建构系统，可以产生 Makefile 或其他构建工具所需的配置文件，以在多种平台上构建项目。 

  - `Makefile`：这是GNU Make的配置文件。GNU Make是一个普遍用于自动化构建的工具，可以自动决定哪些文件需要被重新编译，哪些文件需要被重新链接，并自动处理这些任务。 
  - 其他：QT的`.pro`，其实本质上也会生成make文件，可以使用QMake/CMake

- Python：在Python中使用`setup.py`文件，用于管理项目的包依赖和构建过程。

- Node.js/JavaScript：使用`package.json`文件，管理项目的模块依赖、运行脚本和项目元数据等

- Java：使用`pom.xml`（Maven）或 `build.gradle`（Gradle）文件，进行项目构建和依赖管理 

- Ruby：使用`Gemfile`（Bundler），进行依赖管理和构建Ruby项目

- .NET/C#: 使用`.csproj`、`.vbproj`或者`.fsproj`文件，用于指定项目设置、依赖和构建过程

## 0

参考：https://www.cnblogs.com/ybqjymy/p/13409050.html

### 单个源文件

- Demo1/
  - main.cc

```cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo1)

# 指定生成目标
add_executable(Demo main.cc)
```

### 同一目录，多个源文件

- Demo2/
  - main.cc
  - MathFunctions.cc
  - MathFunctions.h

```cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo2)

# 指定生成目标
add_executable(Demo main.cc MathFunctions.cc)
```

或

```cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo2)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo ${DIR_SRCS})
```

### 多个目录，多个源文件

- Demo3/
  - main.cc
  - math/
    - MathFunctions.cc
    - MathFunctions.h
    - **(NEW)** CMakeLists.txt

```cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo3)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加 math 子目录
add_subdirectory(math) # 这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处理

# 指定生成目标
add_executable(Demo main.cc)

# 添加链接库
target_link_libraries(Demo MathFunctions)
```

子目录的 CMakeLists.txt

```cmake
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library (MathFunctions ${DIR_LIB_SRCS})
```

### 自定义编译选项

/Demo4

```cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo4)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)

# 是否使用自己的 MathFunctions 库
option (USE_MYMATH
	"Use provided math implementation" ON)

# 是否加入 MathFunctions 库
if (USE_MYMATH)
	include_directories ("${PROJECT_SOURCE_DIR}/math")
	add_subdirectory (math)
	set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo ${DIR_SRCS})
target_link_libraries (Demo ${EXTRA_LIBS})
```

……未完



## 其他

### INSTALL与COPY

1. cmakelist中，copy和INSTALL files的区别和选用 
2. 如果我想要生成一个只有头文件没有源文件的include文件夹应该使用哪种，为什么？ 

---

- 在cmakelist中，copy和INSTALL files的功能很相似，它们都可以将文件从源目录复制到目标目录。主要区别在于他们的使用场景和时机：

  - copy命令：会在构建（build）阶段，复制文件或目录到某个具体的位置（但我实测好像在cmake的时候就会复制）
  - INSTALL：则是在安装（install）阶段执行的，可以将文件复制到安装目录下，或者制定具体的位置。它通常会结合CPACK相关命令一起使用，用于生成发布包。 

  对于开发者来说，通常在开发或调试阶段使用copy命令，而在准备发布软件的时候则使用INSTALL命令。

- 如果想要生成一个只包含了头文件的include文件夹，通常建议是使用INSTALL命令。

  因为只有头文件的库通常是被设计为可以被其他应用或库引用的，所以往往需要安装到一个公共的或者标准的位置，而INSTALL命令在制作软件发布包或者进行软件安装时更为适用。

  但是，如果你只是在开发阶段需要复制头文件，那么使用copy命令也是可行的。 

### CMake构建系统阶段

在CMake生成的构建系统中，有几个重要的阶段：

1. CMake 配置生成阶段：CMake根据CMakeLists.txt及其子目录中的所有CMakeLists.txt生成Makefile或者其他形式的构建项目文件。 
2. Make 构建阶段：使用Make或相当于Make的其他工具（如Ninja、Visual Studio）根据CMake生成的项目文件执行编译、链接等操作，生成最终的可执行程序、库文件等。 
3. Install 阶段：这个阶段是在make构建阶段后面的，使用 `make install` 或者等效的命令执行。在此阶段，根据CMakeLists.txt中的INSTALL命令，将构建的结果（比如可执行文件、库文件、头文件等）复制或者安装到指定的目标路径，这个目标路径可以是系统的库路径、include路径，也可以是某个自定义的目录。 

因此，INSTALL阶段通常是在程序或库的编译链接后面的，它是把编译结果分发到指定位置的阶段。在搭建开发环境，或者生成程序发布包的时候，往往会执行这个阶段。

简单精炼总结版：

- CMake：多个CMakeLists.txt -> Makefile等
- Make：Makefile -> 构建结果（可执行文件、库等）
- Install：将构建结果 -> 复制或安装到目标路径

### CLion执行Install

参考：https://blog.csdn.net/qq_30326609/article/details/127995878

< GPT

我使用CLion时，如何执行Install阶段，我点击cmake和编译按钮后，库文件.a都生成出来了，但似乎没有执行Install相关的内容

---

在CLion中，执行Install阶段的操作一般不会在默认的构建操作中出现，需要通过设置额外的目标来实现。

1. 首先打开"Run/Debug Configurations"对话框，可以通过"Run"菜单，或者工具栏上的下拉按钮来打开。 
2. 在弹出的对话框中，点击左上角的+号，然后在弹出的菜单中选择"CMake Application"。 
3. 新建的配置默认的Target是"all"，该Target对应的是整个项目的构建。你需要更改Target为"install"，这样这个配置就会执行install阶段。 
4. 完成上述设置后，你可以通过点击右上角的运行按钮，或者在"Run"菜单中选择对应的配置来启动，CLion会自动执行对应的构建和install过程。 

请注意，如果你的CMakeLists.txt中没有设置安装路径，可能会出现权限问题，因为默认可能会安装到系统目录下。你可以通过设置CMAKE_INSTALL_PREFIX变量来制定安装路径，例如：

```makefile
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/output)
```

#### cmake install命令

> install命令才会把这些库添加到环境变量中，与这个有关的变量是：CMAKE_INSTALL_PREFIX。
> **CMAKE_INSTALL_PREFIX默认值在linux系统中位置是/usr/local，windows则是C:/Program Files (x86)**

install默认点击debug/run的时候并不会触发，需要一点手动操作。

详情可以参考官网install说明：[cmake install clion官网操作说明](https://www.jetbrains.com/help/clion/using-cmake-install.html?keymap=secondary_visual_studio)

对应图像界面位置：

![在这里插入图片描述](CMakeLists.assets/9655ebb5d7364b1886258a151b408931.png)

下图位置可以设置run/debug的时候自动install，具体操作参考上面给出的官网。
 ![在这里插入图片描述](CMakeLists.assets/29ca84969180494ca27f3de171c824c0.png)

#### install中的findPackage

作用：在环境变量下查找某个包，查找后的包可以用到后面。

原理：执行FindXXX.cmake程序，这个程序在cmake2.x的时候需要手写，3.x后可以使用自动生成的XXXConfig.cmake来配置找到程序包，XXX是库的名字。

#### install中的configure_file

该命令将 `<input>` 指定的文件拷贝为` <output>` 指定的文件，并将 `<input>` 文件中 @VAR@ 或 ${VAR} 的位置替换为使用 configure_file() 命令的当前 CMakeLists.txt 中变量 VAR 的值。该命令用于外部文件获取 CMakeLists.txt 文件中变量的值。

    configure_file(<input> <output) 中的 <output> 指定的文件名必须是 xxxConfig.cmake 或 xxx-config.cmake（xxx必须为小写）。

#### cmake install文件demo

完整项目地址：[my_oatpp](https://gitee.com/tang_world/my_oatpp)

```makefile
#######################################################################################
# 生成Target文件，将目标文件 targets 的可导出信息存储在 <export_name> 中（内存），用于生成可导出文件。
install(
    TARGETS ${OATPP_THIS_MODULE_TARGETS}
    EXPORT "${OATPP_MODULE_NAME}Targets"
    ARCHIVE
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/oatpp-${OATPP_MODULE_VERSION}"
        COMPONENT Devel
    LIBRARY
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/oatpp-${OATPP_MODULE_VERSION}"
        COMPONENT Library
    RUNTIME
        DESTINATION "${CMAKE_INSTALL_BINDIR}/oatpp-${OATPP_MODULE_VERSION}"
        COMPONENT Library
    INCLUDES
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/oatpp-${OATPP_MODULE_VERSION}/${OATPP_MODULE_NAME}"
)
# 安装hpp类型文件到include文件夹下
install(DIRECTORY ${OATPP_DIRS_TO_INSTALL}
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/oatpp-${OATPP_MODULE_VERSION}/${OATPP_MODULE_NAME}"
        COMPONENT Devel
        FILES_MATCHING PATTERN "*.hpp"
)
# 使用生成的导出信息，生成导出目标文件
install(EXPORT "${OATPP_MODULE_NAME}Targets"
        FILE "${OATPP_MODULE_NAME}Targets.cmake"
        NAMESPACE oatpp::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${OATPP_MODULE_NAME}-${OATPP_MODULE_VERSION}"
        COMPONENT Devel
)
###################################################
# packaging Config
include(CMakePackageConfigHelpers)

write_basic_package_version_file("${OATPP_MODULE_NAME}ConfigVersion.cmake"
        VERSION ${OATPP_MODULE_VERSION}
        COMPATIBILITY ExactVersion ## Use exact version matching.
)

## Take module-config.cmake.in file in this direcory as a template

configure_package_config_file(
            "${CMAKE_CURRENT_LIST_DIR}/module-config.cmake.in"
            "${OATPP_MODULE_NAME}Config.cmake"
        INSTALL_DESTINATION
            "${CMAKE_INSTALL_LIBDIR}/cmake/${OATPP_MODULE_NAME}-${OATPP_MODULE_VERSION}"
        PATH_VARS
            OATPP_MODULE_NAME
            OATPP_MODULE_VERSION
            OATPP_MODULE_LIBRARIES
            OATPP_MODULE_LIBDIR
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
###################################################

# 安装Config文件
install(
        FILES
            "${CMAKE_CURRENT_BINARY_DIR}/${OATPP_MODULE_NAME}Config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/${OATPP_MODULE_NAME}ConfigVersion.cmake"
        DESTINATION
            "${CMAKE_INSTALL_LIBDIR}/cmake/${OATPP_MODULE_NAME}-${OATPP_MODULE_VERSION}"
        COMPONENT Devel
)
```

## 实战经验 - 多层CMakeLists







# 系统教程

参考：[【Bilibili】从零开始详细介绍CMake](https://www.bilibili.com/video/BV1vR4y1u77h)，有自动字幕，带md笔记资料，总长01:10:50，进度10p_s/10p

## 准备

### 说明

cmake的定义是什么 ？-----高级编译配置工具

当多个人用不同的语言或者编译器开发一个项目，最终要输出一个可执行文件或者共享库（dll，so等等）这时候神器就出现了-----CMake！

所有操作都是通过编译CMakeLists.txt来完成的—简单

官方网站是 [www.cmake.org](http://www.cmake.org/)，可以通过访问官方网站获得更多关于 cmake 的信息

学习CMake的目的，为将来处理大型的C/C++/JAVA项目做准备

### CMake安装

1、绝大多数的linux系统已经安装了CMake

2、Windows或某些没有安装过的linux系统，去[http://www.cmake.org/HTML/Download.htm](http://www.cmake.org/HTML/Download.html)l  可以下载安装

### CMake一个HelloWord

1、步骤一，写一个HelloWord

```cpp
#main.cpp

#include <iostream>

int main(){
std::cout <<  "hello word" << std::endl;
}
```

2、步骤二，写CMakeLists.txt

```cpp
#CMakeLists.txt
PROJECT (HELLO)
SET(SRC_LIST main.cpp)
MESSAGE(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir "${HELLO_SOURCE_DIR})
ADD_EXECUTABLE(hello ${SRC_LIST})
```

3、步骤三、使用cmake，生成makefile文件

```bash
$ cmake . # 当前目录用cmake编译

输出：
[root@localhost cmake]# cmake .
CMake Warning (dev) in CMakeLists.txt:
  Syntax Warning in cmake code at

    /root/cmake/CMakeLists.txt:7:37

  Argument not separated from preceding token by whitespace.
This warning is for project developers.  Use -Wno-dev to suppress it.

-- The C compiler identification is GNU 10.2.1
-- The CXX compiler identification is GNU 10.2.1
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- This is BINARY dir /root/cmake
-- This is SOURCE dir /root/cmake
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake
```

目录下就生成了这些文件-CMakeFiles, CMakeCache.txt, cmake_install.cmake 等文件，并且生成了Makefile.
现在不需要理会这些文件的作用，以后你也可以不去理会。最关键的是，它自动生成了Makefile.

4、步骤4、使用make命令编译

```bash
root@localhost cmake]$ make
Scanning dependencies of target hello
[100%] Building CXX object CMakeFiles/hello.dir/main.cpp.o
Linking CXX executable hello
[100%] Built target hello
```

5、最终生成了Hello的可执行程序

## 【字典】CMakeLists常用命令

以上一章的HelloWord为例

### 项目管理类

一个最简单的demo：

```cmake
cmake_minimum_required(VERSION 3.16)
project(ProjectName1)
set(CMAKE_CXX_STANDARD 23)

add_executable(ppp1 main.cpp)
```

#### `project` 指定工程名与语言

可以用来指定工程的名字和支持的语言，默认支持所有语言

PROJECT (HELLO)   指定了工程的名字，并且支持所有语言—建议

PROJECT (HELLO CXX)      指定了工程的名字，并且支持语言是C++

PROJECT (HELLO C CXX)      指定了工程的名字，并且支持语言是C和C++

该指定隐式定义了两个CMAKE的变量

`<projectname>_BINARY_DIR`，本例中是 HELLO_BINARY_DIR

`<projectname>_SOURCE_DIR`，本例中是 HELLO_SOURCE_DIR

MESSAGE关键字就可以直接使用者两个变量，当前都指向当前的工作目录，后面会讲外部编译

问题：如果改了工程名，这两个变量名也会改变

解决：又定义两个预定义变量：PROJECT_BINARY_DIR和PROJECT_SOURCE_DIR，这两个变量和HELLO_BINARY_DIR，HELLO_SOURCE_DIR是一致的。所以改了工程名也没有关系

#### `add_executable` 生成可执行文件

生成可执行文件

```makefile
add_executable(hello ${SRC_LIST})
```

生成的可执行文件名是hello，源文件读取变量SRC_LIST中的内容

也可以直接写

```makefile
add_executable(hello main.cpp)
```

上述例子可以简化的写成

```makefile
PROJECT(HELLO)
add_executable(hello main.cpp)
```

注意：工程名的 HELLO 和生成的可执行文件 hello 是没有任何关系的

#### `add_library` 生成静态/动态编译库

例如

```makefile
add_library(TSDB ./TSDB.c)
```

#### `add_subdirectory` 添加子项目

例如

```makefile
# 添加子项目
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)
```

#### `include_directories` 搜索头文件

- `include_directories`，一般使用
- `target_include_directories`，有时会用

增加头文件搜索路径，可以用于简化缩短工程内部或系统中的头文件路径

也可以用于指定在工程的某个外部文件夹中寻找头文件

例如

```makefile
include_directories(/usr/include/hello)
```

#### `link_libraries` 搜索 (链接) 库

- `link_libraries`
- `target_link_libraries`，一般用的是这个

例如

```makefile
target_link_libraries(main libhello.a) # 注意这个只能写在 add_executable 的后面
```

### 常用、通用类

#### `set` 指定变量

用来显示的指定变量的

SET(SRC_LIST main.cpp)    SRC_LIST变量就包含了main.cpp

也可以 SET(SRC_LIST main.cpp t1.cpp t2.cpp)

#### `message` 输出自定义信息

向终端输出用户自定义的信息

主要包含三种信息：

- SEND_ERROR，产生错误，生成过程被跳过。
- SATUS，输出前缀为—的信息。
- FATAL_ERROR，立即终止所有 cmake 过程.

也可以不加这个信息类别，例如：

```cmake
# 编译信息
message("Compile Info")
message("    Compile Platform")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message("        Linux")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    message("        Windows")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    message("        MacOS")
else()
    message(WARNING, "        Other")
endif()
message("    Compile ToolChain")
if (MINGW)
    message("        MINGW")
elseif (MSVC)
    message("        MSVC")
else ()
    message(WARNING, "        Other")
endif ()
message("    Compiler Version")
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    message("        MSVC ${CMAKE_CXX_COMPILER_VERSION}")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    message("        GCC ${CMAKE_CXX_COMPILER_VERSION}")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    message("        Clang ${CMAKE_CXX_COMPILER_VERSION}")
else()
    message(WARNING, "        Other ${CMAKE_CXX_COMPILER_VERSION}")
endif()
```

### 路径类

#### `XXX_SOURCE_DIR` 工程路径、或CMakeLists所在路径

**修改**：固定，不可修改

PROJECT_SOURCE_DIR 或 HELLO_SOURCE_DIR (HELLO是当前项目名)，工程路径，是 “/root/cmake01”

#### `XXX_BINARY_DIR` 执行cmake的路径

**修改**：固定，不可修改

PROJECT_BINARY_DIR 或 HELLO_BINARY_DIR (HELLO是当前项目名)，编译路径，比如在下面 “外部构建” 的例子中，是 “/root/cmake01/bulid”

#### `EXECUTABLE_OUTPUT_PATH` 构建的可执行文件的路径

**修改**：XXX_OUTPUT_PATH 可以使用 `SET` 进行设置 重定向

#### `LIBRARY_OUTPUT_PATH` 构建的库文件的路径

**修改**：XXX_OUTPUT_PATH 可以使用 `SET` 进行设置 重定向

#### `CMAKE_INSTALL_PREFIX` CMake路径的前缀

用处：

- `CMake Install` 命令中，相对路径执行的前缀

**修改**：

- 默认值：在 /usr/local/

- CLion默认值及设置：在CLion中可以在设置 > 构建执行部署 > CMake 中看到和设置CMake选项

  默认CMake选项：`-G Ninja -DCMAKE_BUILD_TYPE=Debug "-DCMAKE_INSTALL_PREFIX=D:/CLion 2022.2.4/bin/ninja/win/ninja.exe"`

  可以改这个CMake选项也可以改他下面的缓存变量

- cmake时设置：cmake -D CMAKE_INSTALL_PREFIX=/usr    在cmake的时候指定CMAKE_INSTALL_PREFIX变量的路径

- CMakeLists文件中设置：set(CMAKE_INSTALL_PREFIX "../")

#### `CMAKE_INCLUDE_PATH` 和 `CMAKE_LIBRARY_PATH`

**修改**：

- 这两个是环境变量而不是 cmake 变量，cmake中无法修改，但可以在linux的bash中进行设置

  例如使用环境变量

  ```bash
  export CMAKE_INCLUDE_PATH=/usr/include/hello
  ```

### 其他

#### `set_target_properties`

这条指令可以用来设置输出的名称，对于动态库，还可以用来指定动态库版本和 API 版本

#### `install` 安装共享库和头文件

#### `find_package` 寻找库

#### `check_header`

例如

```cmake
check_header("stdbool.h")
check_header("stdint.h")
```

#### `check_function`

例如

```cmake
check_function("gettid" "unistd.h")
check_function("strlcpy" "string.h")
```

#### `file` 各种文件操作

文件操作，根据参数一的不同有多种不同的用法

例如

```cmake
file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/web/)  	# 递归移动?
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/web/)  	# 创建文件夹
file(COPY ${PROJECT_SOURCE_DIR}/web/release/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/web/)  # 复制
file(GLOB_RECURSE SRCS src/*.cpp src/*.c)  				# 包含文件路径到对应变量
```

## 【字典】CMake常用指令

### -D CMake_install_prefix

```bash
cmake -DCMAKE_INSTALL_PREFIX=/usr
```

### -D CMake_build_type

```bash
cmake -DCMAKE_BUILD_TYPE=debug
```

## 入门

### 语法的基本原则

- 变量使用 `${}` 方式取值，但是在 IF 控制语句中是直接使用变量名

- `指令(参数 1 参数 2...)` 参数使用括弧括起，参数之间使用**空格或分号**分开。 以上面的 ADD_EXECUTABLE 指令为例，如果存在另外一个 func.cpp 源文件

  就要写成：`ADD_EXECUTABLE(hello main.cpp func.cpp)` 或者 `ADD_EXECUTABLE(hello main.cpp;func.cpp)`

- 指令是**大小写无关**的，参数和变量是大小写相关的。但，推荐你全部使用大写指令（LincZero：我喜欢用小写）

语法注意事项

- SET(SRC_LIST main.cpp) 可以写成 SET(SRC_LIST “main.cpp”)，如果源文件名中含有**空格**，就必须要加**双引号**
- ADD_EXECUTABLE(hello main) 后缀可以不写，他会自动去找.c和.cpp，最好不要这样写，可能会有这两个文件main.cpp和main

### 内部构建和外部构建

- 上述例子就是内部构建，他生产的临时文件特别多，不方便清理
- 外部构建，就会把生成的临时文件放在build目录下，不会对源文件有任何影响强烈使用外部构建方式

外部构建方式举例：

```bash
# 例子目录，CMakeLists.txt和上面例子一致
[root@localhost cmake]$ pwd
/root/cmake
[root@localhost cmake]$ ll
total 8
-rw-r--r--. 1 root root 198 Dec 28 20:59 CMakeLists.txt
-rw-r--r--. 1 root root  76 Dec 28 00:18 main.cpp
```

1. 建立一个build目录，可以在任何地方，建议在当前目录下
2. 进入build，运行cmake ..    当然..表示上一级目录，你可以写CMakeLists.txt所在的绝对路径，生产的文件都在build目录下了
3. 在build目录下，运行make来构建工程

```bash
$ mkdir build
$ cd build/
$ cmake .. # 从上一级目录构建
```

注意外部构建的两个变量

1. HELLO_SOURCE_DIR  还是工程路径
2. HELLO_BINARY_DIR   编译路径 也就是 /root/cmake/bulid

## 多CMakeLists管理 —— 让Hello World看起来更像一个工程

- 为工程添加一个子目录 src，用来放置工程源代码
- 添加一个子目录 doc，用来放置这个工程的文档 hello.txt
- 在工程目录添加文本文件 COPYRIGHT, README
- 在工程目录添加一个 [runhello.sh](http://runhello.sh/) 脚本，用来调用 hello 二进制
- 将构建后的目标文件放入构建目录的 bin 子目录
- 将 doc 目录 的内容以及 COPYRIGHT/README 安装到/usr/share/doc/cmake/

### 将目标文件放入构建目录的 bin 子目录

每个目录下都要有一个CMakeLists.txt说明

```bash
[root@localhost cmake]$ tree
.
├── build
├── CMakeLists.txt
└── src
    ├── CMakeLists.txt
    └── main.cpp
```

外层 CMakeLists.txt

```makefile
project(HELLO)
add_subdirectory(src bin)
```

src下的 CMakeLists.txt

```makefile
add_executable(hello main.cpp)
```

### `add_subdirectory` 添加子项目

ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])

- 这个指令用于向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置

- EXCLUDE_FROM_ALL函数是将写的目录从编译中排除，如程序中的example

- ADD_SUBDIRECTORY(src bin)

  将 src 子目录加入工程并指定编译输出(包含编译中间结果)路径为bin 目录

  如果不进行 bin 目录的指定，那么编译结果(包括中间结果)都将存放在build/src 目录

### 用 SET 更改二进制的保存路径

SET 指令重新定义 EXECUTABLE_OUTPUT_PATH 和 LIBRARY_OUTPUT_PATH 变量 来指定最终的目标二进制的位置

```makefile
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
```

思考：加载哪个CMakeLists.txt当中

哪里要改变目标存放路径，就在哪里加入上述的定义，所以应该在src下的CMakeLists.txt下写

## Install 安装

- 一种是从代码编译后直接 make install 安装
- 一种是打包时的指定 目录安装。
  - 简单的可以这样指定目录：make install DESTDIR=/tmp/test
  - 稍微复杂一点可以这样指定目录：./configure –prefix=/usr

### 如何安装HelloWord

使用CMAKE一个新的指令：INSTALL

INSTALL的安装可以包括：二进制、动态库、静态库以及文件、目录、脚本等

使用CMAKE一个新的变量：CMAKE_INSTALL_PREFIX

```bash
// 目录树结构
[root@localhost cmake]$ tree
.
├── build
├── CMakeLists.txt
├── COPYRIGHT
├── doc
│   └── hello.txt
├── README
├── runhello.sh
└── src
    ├── CMakeLists.txt
    └── main.cpp

3 directories, 7 files
```

### (1) 安装 文件COPYRIGHT和README

这里安装三个文件到指定路径

```cpp
/**
 * @param FILES后面 文件
 * @param DESTINATION后
 *   1. 写绝对路径
 *   2. 可以写相对路径，相对路径实际路径是：${CMAKE_INSTALL_PREFIX}/<DESTINATION 定义的路径>
 */
install(FILES COPYRIGHT README DESTINATION share/doc/cmake/)
```

CMAKE_INSTALL_PREFIX 问题

- 默认值：在 /usr/local/
- cmake时设置：cmake -DCMAKE_INSTALL_PREFIX=/usr    在cmake的时候指定CMAKE_INSTALL_PREFIX变量的路径
- CMakeLists文件中设置：set(CMAKE_INSTALL_PREFIX "../")

### (2) 安装脚本 runhello.sh

PROGRAMS：非目标文件的可执行程序安装(比如脚本之类)

```makefile
INSTALL(PROGRAMS runhello.sh DESTINATION bin)
```

说明：实际安装到的是 /usr/bin

### (3) 安装 doc 中的 hello.txt

- 一、是通过在 doc 目录建立CMakeLists.txt ，通过install下的file

- 二、是直接在工程目录通过

  INSTALL(DIRECTORY doc/ DESTINATION share/doc/cmake)


DIRECTORY 后面连接的是所在 Source 目录的相对路径

注意：abc 和 abc/有很大的区别

目录名不以/结尾：这个目录将被安装为目标路径下的

目录名以/结尾：将这个目录中的内容安装到目标路径

### 安装过程

命令

```bash
cmake ..
make
make install
```

最终成果

```bash
$ make install
[100%] Built target hello
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/share/doc/cmake/COPYRIGHT
-- Installing: /usr/local/share/doc/cmake/README
-- Installing: /usr/local/bin/runhello.sh
-- Installing: /usr/local/share/doc/cmake
-- Installing: /usr/local/share/doc/cmake/hello.txt
```

## 静态库和动态库的构建

任务：

１，建立一个静态库和动态库，提供 HelloFunc 函数供其他程序编程使用，HelloFunc 向终端输出 Hello World 字符串。 

２，安装头文件与共享库。

静态库和动态库的区别

- 扩展名

  - 静态库：一般为“.a”或“.lib”
  - 动态库：一般为“.so”或“.dll”

- 是否编译入可执行文件

  - 静态库：是。静态库在编译时会直接整合到目标程序中，编译成功的可执行文件可独立运行

  - 动态库：否。在编译时不会放到连接的目标程序中，即可执行文件无法单独运行

### 构建实例

```bash
[root@localhost cmake2]$ tree
.
├── build
├── CMakeLists.txt
└── lib
    ├── CMakeLists.txt
    ├── hello.cpp
    └── hello.h
```

hello.h中的内容

```cpp
#ifndef HELLO_H
#define Hello_H

void HelloFunc();

#endif
```

hello.cpp中的内容

```cpp
#include "hello.h"
#include <iostream>
void HelloFunc(){
    std::cout << "Hello World" << std::endl;
}
```

项目中的cmake内容

```makefile
PROJECT(HELLO)
ADD_SUBDIRECTORY(lib bin)
```

lib中CMakeLists.txt中的内容

```makefile
SET(LIBHELLO_SRC hello.cpp)
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
```

### ADD_LIBRARY

```cpp
/**
 * @param arg1 hello：就是正常的库名，生成的名字前面会加上lib，最终产生的文件是libhello.so
 * @param arg2 SHARED，动态库    STATIC，静态库
 * @param arg3 ${LIBHELLO_SRC} ：源文件
 */
add_library(hello SHARED ${LIBHELLO_SRC})
```

### 同时构建静态和动态库

> #### 同名冲突问题

一般来说，同名的话，只会生成一个

```makefile
# 如果用这种方式，只会构建一个动态库，不会构建出静态库，虽然静态库的后缀是.a
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
ADD_LIBRARY(hello STATIC ${LIBHELLO_SRC})
```

> #### 不同名解决冲突

一个解决方法是让他们不同名，这样比较简单粗暴

```makefile
# 修改静态库的名字，这样是可以的，但是我们往往希望他们的名字是相同的，只是后缀不同而已
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})
```

> #### `set_target_properties` 设置输出名以解决冲突

另一种解决方法是使用 `SET_TARGET_PROPERTIES`，这条指令可以用来设置输出的名称，对于动态库，还可以用来指定动态库版本和 API 版本

同时构建静态和动态库

```makefile
SET(LIBHELLO_SRC hello.cpp)

# 静态库
ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC}) # 这里的名字依然是不弄冲突，但下面可以设置输出名来让他们输出名相同
# 静态库 - 设置一些属性
SET_TARGET_PROPERTIES(hello_static PROPERTIES  OUTPUT_NAME "hello")
SET_TARGET_PROPERTIES(hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# 动态库
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
# 动态库 - 设置一些属性
SET_TARGET_PROPERTIES(hello PROPERTIES  OUTPUT_NAME "hello")
SET_TARGET_PROPERTIES(hello PROPERTIES CLEAN_DIRECT_OUTPUT 1)
```

常见设置属性

```makefile
# 输出名，OUTPUT_NAME，对hello_static的重名为hello
SET_TARGET_PROPERTIES(hello_static PROPERTIES  OUTPUT_NAME "hello")

# 清理同名库，CLEAN_DIRECT_OUTPUT
# cmake 在构建一个新的target 时，会尝试清理掉其他使用这个名字的库，因为，在构建 libhello.so 时， 就会清理掉 libhello.a
SET_TARGET_PROPERTIES(hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# 版本号，VERSION
SET_TARGET_PROPERTIES(hello PROPERTIES VERSION 1.2 SOVERSION 1)
```

### 动态库版本号

一般动态库都有一个版本号的关联，静态库没有也不需要

```cpp
libhello.so.1.2
libhello.so ->libhello.so.1
libhello.so.1->libhello.so.1.2
```

CMakeLists.txt 插入如下

```makefile
SET_TARGET_PROPERTIES(hello PROPERTIES VERSION 1.2 SOVERSION 1)
```

VERSION 指代动态库版本，SOVERSION 指代 API 版本。

### `install` 安装共享库和头文件

本例中我们将 hello 的共享库安装到 `<prefix>/lib` 目录，

将 hello.h 安装到 `<prefix>/include/hello` 目录

```makefile
# 头文件，FILES
# 文件放到该目录下
install(FILES hello.h DESTINATION include/hello)

# 二进制，静态库，动态库安装，TARGETS
# ARCHIVE 特指静态库，LIBRARY 特指动态库，RUNTIME 特指可执行目标二进制。
install(TARGETS hello hello_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
```

参数：

```cpp
/**
 * arg1 arg2 "arg3 DESTINATION arg4"xn
 * @param arg1
 *     TARGETS，二进制，静态库，动态库安装
 *     FILES，单纯的文件复制，如头文件
 * @param args2 要被复制文件
 * @param arg3
 *     ARCHIVE，特指静态库
 *     LIBRARY，特指动态库
 *     RUNTIME，特指可执行目标二进制
 * @param arg4 要被复制到的路径，前缀是 `-DCMAKE_INSTALL_PREFIX` 的值 (可设置)
 */
install(
    TARGETS
    hello hello_static
    LIBRARY DESTINATION lib # 这里表示
    ARCHIVE DESTINATION lib
)
```

注意：

安装的时候，指定一下路径，放到系统下：`cmake -D CMAKE_INSTALL_PREFIX=/usr ..`（这里的-D后面空格可加可不加）

### 使用外部共享库和头文件

准备工作，新建一个目录来使用外部共享库和头文件

```bash
[root@MiWiFi-R4CM-srv cmake3]$ tree
.
├── build
├── CMakeLists.txt
└── src
    ├── CMakeLists.txt
    └── main.cpp
```

main.cpp

```cpp
#include <hello.h>

int main(){
	HelloFunc();
}
```

总结

- install在 /usr/include/ 后，直接include就能找到头文件
- install在 /usr/lib/ (也可能是/usr/lib64/或/usr/lib32/) 后，直接在CMakeLists中加入 `target_link_libraries(main libhello.a)` 就能找到库文件

### 常见bug解决

> #### 解决：make后头文件找不到的问题

PS：include <hello/hello.h>  这样include是可以，这么做的话，就没啥好讲的了

关键字：INCLUDE_DIRECTORIES    这条指令可以用来向工程添加多个特定的头文件搜索路径，路径之间用空格分割

在CMakeLists.txt中加入头文件搜索路径

```makefile
include_directories(/usr/include/hello)
```

感谢：网友：zcc720的提醒

另一个解决方案是：

> 我们上面例子中使用了绝对路径 INCLUDE_DIRECTORIES(/usr/include/hello) 来指明include路径的位置
>
> 我们还可以使用另外一种方式，使用环境变量 export CMAKE_INCLUDE_PATH=/usr/include/hello

> #### 解决：找到引用的函数问题

报错信息：undefined reference to `HelloFunc()'

关键字：LINK_DIRECTORIES     添加非标准的共享库搜索路径

指定第三方库所在路径，LINK_DIRECTORIES(/home/myproject/libs)

关键字：TARGET_LINK_LIBRARIES    添加需要链接的共享库

TARGET_LINK_LIBRARIES的时候，只需要给出动态链接库的名字就行了。

在CMakeLists.txt中插入链接共享库，主要要插在executable的后面

查看main的链接情况

```bash
[root@MiWiFi-R4CM-srv bin]$ ldd main 
	linux-vdso.so.1 =>  (0x00007ffedfda4000)
	libhello.so => /lib64/libhello.so (0x00007f41c0d8f000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f41c0874000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f41c0572000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f41c035c000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f41bff8e000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f41c0b7c000)
```

链接静态库

`TARGET_LINK_LIBRARIES(main libhello.a)`

## 技巧

### 头文件递归包含

这里本质上是递归调用：include_directories

```cmake
# 递归包含头文件的函数。本质上是递归调用：include_directories
function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})               # 当前路径是一个目录吗，是的话就加入到包含目录
        #        if (${root_dir} MATCHES "include")
        message("include dir: " ${root_dir})
        include_directories(${root_dir})
        #        endif()
    endif ()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
    foreach (sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            include_sub_directories_recursively(${root_dir}/${sub}) # 对子目录递归调用，包含
        endif ()
    endforeach ()
endfunction()

# 将目录下的所有头文件包含进PROJECT_BINARY_DIR中
include_sub_directories_recursively(${PROJECT_SOURCE_DIR}/src)
```

### 源文件递归包含

这里本质上是将对应的cpp/c文件全部存储在一个变量里

```cmake
# 将目录下的所有源文件包含进SRCS中
file(GLOB_RECURSE SRCS src/*.cpp src/*.c)
add_executable(${PROJECT_NAME} main.cpp ${SRCS})
```































