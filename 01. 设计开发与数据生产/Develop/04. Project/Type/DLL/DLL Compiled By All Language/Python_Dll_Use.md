# DLL Compiled By All Language

# 目录

# Python_Dll_Use

参考：

- [【CSDN】python调用dll方法](https://blog.csdn.net/lf8289/article/details/2322550)
- [【博客园】Python调用windows下DLL详解 - ctypes库的使用](https://www.cnblogs.com/baihuitestsoftware/articles/5345089.html)

## 原理

### ctypes模块

调用约定：加载的时候要根据你将要调用的函数是符合什么调用约定的。

stdcall调用约定：两种加载方式 

```python
Objdll = ctypes.windll.LoadLibrary("dllpath") 
Objdll = ctypes.WinDLL("dllpath")  
```

cdecl调用约定：也有两种加载方式 

```python
Objdll = ctypes.cdll.LoadLibrary("dllpath") 
Objdll = ctypes.CDLL("dllpath") 
/*其实windll和cdll分别是WinDLL类和CDll类的对象。*/  
```

加载dll的时候会返回一个DLL对象，利用该对象就可以调用dll中的方法

### 注意Python位数

可使用IDLE或者CMD查看

- 打开IDLE,看第一行提示

  例如64位（**不要看win32，看MSC后面的！**被坑过一次了）：
  Python 3.7.8 (tags/v3.7.8:4b47a5b6ba, Jun 28 2020, 08:53:46) [MSC v.1916 **64 bit** (**AMD64**)] on ~~win32~~

- CMD，输入python。也会显示上述命令

要编译与之对应的dll位数

## 使用

### 参考案例

```python
import  ctypes
dll  =  ctypes.windll.LoadLibrary( 'test.dll')
# 或 dll  =  ctypes.WinDll('test.dll')
# 然后通过dll对象调用dll文件

```

### 使用之前开发的cpp_dll

（注意位数要对应）

```c++
import ctypes
dll  =  ctypes.windll.LoadLibrary( 'Dll1.dll')

# nRst = dll.fibonacci_current(5)
dll.fibonacci_init(1,1);
for i in range(50):
    print(str(dll.fibonacci_index())+":"+str(dll.fibonacci_current()))
    dll.fibonacci_next();

```

体外话：

原c程序是返回unsigned long long类型，python3没有long类型（python2有），python3中int类型是动态内存，理论支持无限大的数字

这个dll在cpp程序中被调用时，能打印到：92: 12200160415121876738，93溢出了

而在python中被调用时，能打印到：45:1836311903，46:-1323752223，46溢出变为负数。也就是说，python在使用dll时返回类型是个4字节的signed int？

个人猜测长整型可能需要使用字符串来传递

## Bug逐步调试

如果出bug的话非常麻烦，建议一步一步来检查

### C语言对python环境的链接

这个测试和C++调用Python程序的测试也是一样的

pythonIniti.c

```c++
#include "stdafx.h"
#include <python.h>

int main()
{
    Py_Initialize();  //调用Py_Initialize()进行初始化
    PyRun_SimpleString("print('Hello World!!')");
    Py_Finalize(); //调用Py_Finalize，和Py_Initialize相对应的.
    system("pause");
    return 0;
}
```

#### 编译报错：无法解析的外部符号

```shell
pythonIniti.obj : error LNK2019: 无法解析的外部符号 __imp___Py_NegativeRefcount，该符号在函数 "public: __thiscall boost::python::api::object_base::~object_base(void)" (??1object_base@api@python@boost@@QAE@XZ) 中被引用
pythonIniti.obj : error LNK2001: 无法解析的外部符号 __imp___Py_RefTotal
```

解决方法忘了

#### 运行报错：有未经处理的异常: 请求了严重的程序退出

执行到`Py_Initialize()`时报错：
0x00007FFE0337286E (ucrtbase.dll) (c_testdll.exe 中)处有未经处理的异常: 请求了严重的程序退出。

和之前在QT用c++调用Python环境崩溃是同一个问题，解决方法如下

```c++
/* 不加则运行时崩溃：
 * initfsencoding: unable to load the file system codec
 * 参考：https://www.cnblogs.com/2008nmj/p/8027430.html
 * 两个方法:
 * 一个就是补全python的环境变量。但不知道为什么我的环境变量设置没用，还是报错
 * 另一个就是手动设置初始化函数的搜寻路径(也就是加载路径)
 */
Py_SetPythonHome(L"D:\\Soft\\Dev\\All\\Python_Anaconda"); // 方法二
/** Python系统初始化 */
Py_Initialize();
```

#### 编译报错：无法打开pyconfig.h

对比了一下我下载的Python源码的Include文件和Anaconda目录下的Include文件

发现前者比后者少了5个项目（分别是101和106个项目）

- 文件夹 greenlet
- 文件夹 LIEF
- json.hpp，578KB
- pyconfig.h，20KB
- sip.h，68KB

> 1249,623-569,289 = 591,107+20,054+69,143+(30)
> 应该还有一个文件是不同的，但只相差30B太难要判断是哪个文件有区别太困难了，而且没意义，应该就是修bug了

结论：用Anaconda的那个就行，32/64位，debug和release都是用的同一个Include文件夹

#### 编译报错：LNK2019	无法解析的外部符号 `__imp__Py_Initialize`，函数 _main 中引用了该符号

这是由于调用的python版本与活动解决方案平台的版本不一致导致的

将项目设置 > 包含库设置为32位的python37.lib所在的路径即可

重新生成解决方案会得到下面的报错

#### 运行弹窗：程序应用无法正常启动0xc000007b。请点击确定关闭程序

debug/x64、release/x64 都能运行但 debug/x86、release/x86 不能运行

然后报错前最后一个加载的dll为：
debug： C:\Windows\SysWOW64\msvcp140d.dll
release：C:\Windows\SysWOW64\ucrtbase.dll

> ##### 尝试1 —— 替换dll文件

刚开始参考了https://blog.csdn.net/kone0611/article/details/79238139，把这个dll文件换成了下面这两个位置的文件
D:\Soft\Dev\All\Edit_Microsoft_VS\IDE\VC\Redist\MSVC\14.28.29325\onecore\debug_nonredist\x86\Microsoft.VC142.DebugCRT
D:\Soft\Dev\All\Edit_Microsoft_VS\IDE\VC\Redist\MSVC\14.28.29325\debug_nonredist\x86\Microsoft.VC142.DebugCRT
但没有解决

> ##### 尝试2 —— 查看dll位数

参考https://blog.csdn.net/qq_41350775/article/details/119935088

```shell
dumpbin /headers C:\Windows\SysWOW64\msvcp140d.dll  # x86
dumpbin /headers C:\Windows\SysWOW64\ucrtbase.dll	# x86
```

都是32位的，没有解决问题





尚未修复





### 生成的C语言文件是否能运行















### 调用DLL

#### 运行错误：无法找到指定DLL库文件...中的输出命令...

先检查前面的有没有错，不要嫌麻烦、多建个工程用一下这个dll。首先要排除DLL文件是否出错

























