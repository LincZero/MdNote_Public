# DLL Compiled By All Language

# 目录

# VS_Cpp_Dll_Build

VS > 创建新项目 > 动态链接库

## 工程模板

工程结构

> Dll1
>
> - 头文件
>   - framework.h
>   - pch.h
> - 源文件
>   - dllmain.cpp		【不同】
>   - pch.cpp
>

framework.h

```c++
#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>

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
// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


```

pch.cpp（完全一样）

```c++
// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

```

## 工程模板编译

菜单 > 生成 > (重新)生成解决方案

生成文件：在同级目录下有的Debug文件夹

- Debug
  - Dll1.dll
  - Dll1.ilk
  - Dll1.pdb

## 工程修改（Microsfot Demo）

library.h

```c++
// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef LIBRARY_EXPORTS  //【关键字声明】
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif

// The Fibonacci recurrence relation describes a sequence F
// where F(n) is { n = 0, a
//               { n = 1, b
//               { n > 1, F(n-2) + F(n-1)
// for some initial integral values a and b.
// If the sequence is initialized F(0) = 1, F(1) = 1,
// then this relation produces the well-known Fibonacci
// sequence: 1, 1, 2, 3, 5, 8, 13, 21, 34, ...

// Initialize a Fibonacci relation sequence
// such that F(0) = a, F(1) = b.
// This function must be called before any other function.
extern "C" LIBRARY_API void fibonacci_init(
    const unsigned long long a, const unsigned long long b);

// Produce the next value in the sequence.
// Returns true on success and updates current value and index;
// false on overflow, leaves current value and index unchanged.
extern "C" LIBRARY_API bool fibonacci_next();

// Get the current value in the sequence.
extern "C" LIBRARY_API unsigned long long fibonacci_current();

// Get the position of the current value in the sequence.
extern "C" LIBRARY_API unsigned fibonacci_index();

```

library.cpp

```c++
// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include "library.h"    //【】

// DLL internal state variables:
static unsigned long long previous_;  // Previous value, if any
static unsigned long long current_;   // Current sequence value
static unsigned index_;               // Current seq. position

// Initialize a Fibonacci relation sequence
// such that F(0) = a, F(1) = b.
// This function must be called before any other function.
void fibonacci_init(
    const unsigned long long a,
    const unsigned long long b)
{
    index_ = 0;
    current_ = a;
    previous_ = b; // see special case when initialized
}

// Produce the next value in the sequence.
// Returns true on success, false on overflow.
bool fibonacci_next()
{
    // check to see if we'd overflow result or position
    if ((ULLONG_MAX - previous_ < current_) ||
        (UINT_MAX == index_))
    {
        return false;
    }

    // Special case when index == 0, just return b value
    if (index_ > 0)
    {
        // otherwise, calculate next sequence value
        previous_ += current_;
    }
    std::swap(current_, previous_);
    ++index_;
    return true;
}

// Get the current value in the sequence.
unsigned long long fibonacci_current()
{
    return current_;
}

// Get the current index position in the sequence.
unsigned fibonacci_index()
{
    return index_;
}
```

## 工程修改编译

菜单 > 生成 > (重新)生成解决方案

生成文件：在同级目录下有的Debug文件夹

- Debug

  - Dll1.dll（话说我看了两次，显示结果不同，难道是同一次我vs还在运行中的原因？）

    - ```c++
      // Dependencies查看
      // 在导出时extern “C"了，这里没名称修饰
      |DLL     |Name              |Ordinal|Type|Name type     |
      |--------|------------------|-------|----|--------------|
      |Dll1.dll|_fibonacci_current|0      |code|Name,no prefix|
      |Dll1.dll|_fibonacci_index  |1      |code|Name,no prefix|
      |Dll1.dll|_fibonacci_init   |2      |code|Name,no prefix|
      |Dll1.dll|_fibonacci_next   |3      |code|Name,no prefix|
      ```
      
    - ```c++
      // Dependencies查看
      |Name             |Ordinal|VA   |
      |-----------------|-------|-----|
      |fibonacci_current|0      |0x612|
      |fibonacci_index  |1      |0x58b|
      |fibonacci_init   |2      |0x44b|
      |fibonacci_next   |3      |0x707|
      ```
  
  - Dll1.ilk
  
  - Dll1.pdb
  
  - Dll1.lib
  
  - Dll1.exp





















