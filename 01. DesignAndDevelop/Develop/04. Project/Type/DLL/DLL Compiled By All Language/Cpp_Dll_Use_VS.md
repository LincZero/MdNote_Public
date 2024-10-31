# DLL Compiled By All Language

# 目录

# VS_Cpp_Dll_Use

## 项目配置方法

### 工程模板

ConsoleApplication1.cpp

```c++
// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

```

### 工程配置

以VS2019为例去配置

1. 项目右键 > 属性 > 配置属性 > C/C++ > 附加包含目录 > 添加静态库头文件的路径

   （项目工程的地方，可以改成相对路径）

   缺失则编译时下步报错：`无法打开 源文件 "library.h"`

2. 项目右键 > 属性 > 配置属性 > 链接器 > 输入 > 附加依赖项 > 输入lib文件的文件名

   （无需路径、需扩展名，例如 Dll1.lib）

   缺失则编译时报错：`LNK2019	无法解析的外部符号 __imp__fibonacci_init`

3. 项目右键 > 属性 > 配置属性 > 链接器 > 常规 > 附加库路径 > 添加静态库lib文件的路径

   （Debug/Release文件夹内，例如 ..\\..\\Dll1\\$(IntDir)）

   缺失或路径不正确则编译时报错：`LNK1104	无法打开文件“Dll1.lib”`

4. 两种方法

   - 将Dll文件复制到当前项目路径下

     （前面配置的是lib文件路径而不是dll文件路径，dll文件默认都是在项目的根路径下查找的）

   - 或者配置：项目右键 > 属性 > 配置属性 > 构建事件 > 后期生成事件 > 命令行输入：

     `xcopy /y /d "..\..\Dll1\$(IntDir)Dll1.dll" "$(OutDir)"`

     其实原理不变，这里是自动复制dll文件到当前路径下，不需要手动复制，而并没有真正地修改dll路径
   
   - 缺失运行时弹出报错：`ConsoleApplication1.exe 系统错误，由于找不到Dll1.dll，无法继续执行代码。重新安装程序可能会解决此问题`

以上配置过程中注意一下Debug/Release和平台的选择，修改完要保存

### 工程修改

```c++
// MathClient.cpp : Client app for MathLibrary DLL.
// #include "pch.h" Uncomment for Visual Studio 2017 and earlier
#include <iostream>
#include "library.h"

int main()
{
    // Initialize a Fibonacci relation sequence.
    fibonacci_init(1, 1);
    // Write out the sequence values until overflow.
    do {
        std::cout << fibonacci_index() << ": "
            << fibonacci_current() << std::endl;
    } while (fibonacci_next());
    // Report count of values written before overflow.
    std::cout << fibonacci_index() + 1 <<
        " Fibonacci sequence values fit in an " <<
        "unsigned 64-bit integer." << std::endl;
}
```

### 补充：外部依赖项

此时，可以在VS解决方案的 “外部依赖项” 中的末尾找到文件 “library.h”

## LoadLibrary 方法

```c++
#include <Windows.h>
#include <iostream>
#include <tchar.h>
using namespace std;
int main()
{
	typedef int(*pAdd)(const char * a, const char * b);
	HINSTANCE hDLL = LoadLibrary(_T("python_to_DLL.dll"));
	cout << "hDLL:" << hDLL << endl;
	if (hDLL)
	{
		// 获取DLL中需要调用的函数的地址
		pAdd pFun = (pAdd)GetProcAddress(hDLL, "_str_add");
		cout << "pFun:" << pFun << endl;
		const char* stra = "12";
		const char* strb = "22";
		if (pFun)
		{
			int i = pFun(stra, strb);
			cout << "i = " << i << endl;
		}
	}
	// 调用dll测试
	//将字符变成int然后相加
	system("pause");
	return 0;
}

```























