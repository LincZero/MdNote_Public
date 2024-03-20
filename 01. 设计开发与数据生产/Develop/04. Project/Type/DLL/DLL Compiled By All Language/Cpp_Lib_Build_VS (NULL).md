# DLL Compiled By All Language

# 目录

# VS_Cpp——Lib_Build

VS > 创建新项目 > 静态库

## 工程模板

### 工程结构

Dll1

- 头文件
  - framework.h
  - pch.h
- 源文件
  - StaticLib1.cpp	【不同】
  - pch.cpp

### 代码

framework.h

```c++
#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容

```

pch.h（完全一样）

```c++
// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"

#endif //PCH_H

```

dllmain.cpp【核心】

```c++
// StaticLib1.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"

// TODO: 这是一个库函数示例
void fnStaticLib1()
{
}

```

pch.cpp（完全一样）

```c++
// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

```

# 