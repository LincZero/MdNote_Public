# C++

# 目录

# C/C++中调用Python

参考：
（C/C++中调用Python）

- [【Python官网文档】Python/C API 参考手册](https://docs.python.org/zh-cn/3.7/c-api/index.html)，编写扩展模块并将 Python 解释器嵌入其应用程序中的 C 和 C++ 程序员可用的 API
- [【Python官网文档】Python/C API 概述](https://docs.python.org/zh-cn/3.7/c-api/intro.html)，C 和 C++ 程序员可以在多个层级上访问 Python 解释器
- [【CSDN】QT——调用Python脚本](https://blog.csdn.net/wzyaiwl/article/details/115298127)
- ==部分内容详见《QT》笔记中《调用Python脚本》==
- c和c++调用Python，https://www.xzhongwei.com/post/127，好总结，重要参考

扩展参考：
（Python中使用C/C++）

- [【Python官网】扩展和嵌入 Python 解释器](https://docs.python.org/zh-cn/3.7/extending/index.html)，如何使用 C 或 C++ 编写模块以使用新模块来扩展 Python 解释器的功能
- [【Python官网文档】使用 C 或 C++ 扩展 Python](https://docs.python.org/zh-cn/3.7/extending/extending.html)

## 简概

- 定义
  - Python 的应用编程接口（API）使得 C 和 C++ 程序员可以在多个层级上访问 Python 解释器。

    该 API 在 C++ 中同样可用，但为简化描述，通常将其称为 `Python/C API`。

- 应用。使用 Python/C API 有两个基本的理由
  - 第一个理由是为了特定目的而编写 扩展模块；它们是扩展 Python 解释器功能的 C 模块。这可能是最常见的使用场景。
  - 第二个理由是将 Python 用作更大规模应用的组件；这种技巧通常被称为在一个应用中 embedding Python。



编写可包含于 CPython 的 C 代码

## 基本操作

包含文件

```c++
#define PY_SSIZE_T_CLEAN
#include <Python.h>
```



## 重要部分

参考：c和c++调用Python，https://www.xzhongwei.com/post/127，好总结，重要参考

### 一、使用python提供给C/C++的API

#### 包含头文件

#include "Python.h"

注：因为python可能定义一些影响某些系统标准头的预处理器定义，所以必需在包含标准头文件（<stdio.h>,  <string.h>, <errno.h>, <limits.h>, <assert.h>  and <stdlib.h>）之前包含Python.h。

#### API介绍

以下是一些API的介绍：

```c++
void Py_Initialize(void);
// 初始化Python解释器。如果初始化失败，继续下面的调用会出现各种错误，可惜的是此函数没有返回值来判断是否初始化成功，如果失败会导致致命错误。

int Py_IsInitialized(void);
// 检查是否已经进行了初始化。如果返回0，表示没有进行过初始化。

void Py_Finalize();
// 反初始化Python解释器。包括子解释器，调用此函数同时会释放Python解释器所占用的资源。


int PyRun_SimpleString(const char *command);
// 实际上是一个宏，执行一段Python代码。

PyObject* PyImport_ImportModule(char *name);
// 导入一个Python模块，参数name可以是*.py文件的文件名。类似Python内建函数import。

PyObject* PyModule_GetDict( PyObject *module);
// 相当于Python模块对象的dict属性，得到模块名称空间下的字典对象。

PyObject* PyRun_String(const char* str, int start,PyObject* globals, PyObject* locals);
// 执行一段Python代码。


int PyArg_Parse(PyObject* args, char* format, …);
// 把Python数据类型解析为C的类型，这样C程序中才可以使用Python里面的数据。

PyObject* Py_BuildValue(char* format, …);
// 和PyArg_Parse刚好相反，构建一个参数列表，把C类型转换为Python对象，使得Python里面可以使用C类型数据。

PyObject* PyObject_GetAttrString(PyObject *o, char*attr_name);
// 返回模块对象o中的attr_name 属性或函数，相当于Python中表达式语句，o.attr_name。

PyObject* PyEval_CallObject(PyObject* pfunc, PyObject*pargs);
// 此函数有两个参数，而且都是Python对象指针，其中pfunc是要调用的Python 函数，一般说来可以使用PyObject_GetAttrString()获得，pargs是函数的参数列表，通常是使用Py_BuildValue()来构建。
```

### 二、C++ 向 Python 传递参数

==**Python 的参数实际上是元组，因此传参实际上就是构造一个合适的元组**==

常用的有两种方法：

#### 方法一：使用 PyTuple_New 创建元组， PyTuple_SetItem 设置元组值

```c++
PyObject* args = PyTuple_New(3);
PyObject* arg1 = Py_BuildValue("i", 100); // 整数参数
PyObject* arg2 = Py_BuildValue("f", 3.14); // 浮点数参数
PyObject* arg3 = Py_BuildValue("s", "hello"); // 字符串参数
PyTuple_SetItem(args, 0, arg1);
PyTuple_SetItem(args, 1, arg2);
PyTuple_SetItem(args, 2, arg3);
```

#### 方法二：直接使用Py_BuildValue构造元组

```C++
PyObject* args = Py_BuildValue("(ifs)", 100, 3.14, "hello");
PyObject* args = Py_BuildValue("()"); // 无参函数
```

### 三、PyArg_ParseTuple函数

```c++
//作用：
    此函数其实相当于 sscanf(str,format,…) ，是Py_BuildValue的逆过程，这个函数将PyObject参数转换成C/C++数据类型，传递的是指针，
//区别：
    但这个函数与Py_BuildValue有点不同，这个函数只能解析Tuple元组，而Py_BuildValue函数可以生成元组，列表，字典等。
//原型：
    PyAPI_FUNC(int) PyArg_ParseTuple(PyObject *args, const char *format,...)
	//Args：
    	一般为Python程序返回的元组。
    //Foramt：
    	同Py_BulidValue类型，就不在累述咯
```

### 四、 Py_BuildValue()函数

PyObject* Py_BuildValue(char* format, …)

参数解释：format及转换格式，类似与C语言中%d,%f，后面的不定参数对应前面的格式，具体格式如下：
 "s"(string) [char *] ：将C字符串转换成Python对象，如果C字符串为空，返回NONE。

```c++
"s#"(string) [char *, int];
// 将C字符串和它的长度转换成Python对象，如果C字符串为空指针，长度忽略，返回NONE。

"z"(string or None) [char *];
// 作用同"s"。

"z#" (stringor None) [char *, int];
// 作用同"s#"。

"i"(integer) [int];
// 将一个C类型的int转换成Python int对象。

"b"(integer) [char];
// 作用同"i"。

"h"(integer) [short int];
// 作用同"i"。

"l"(integer) [long int];
// 将C类型的long转换成Pyhon中的int对象。

"c"(string of length 1) [char];
// 将C类型的char转换成长度为1的Python字符串对象。

"d"(float) [double];
// 将C类型的double转换成python中的浮点型对象。

"f"(float) [float];
// 作用同"d"。

"O&"(object) [converter, anything];
// 将任何数据类型通过转换函数转换成Python对象，这些数据作为转换函数的参数被调用并且返回一个新的Python对象，如果发生错误返回NULL。

"(items)"(tuple) [matching-items];
// 将一系列的C值转换成Python元组。

"[items]"(list) [matching-items];
// 将一系列的C值转换成Python列表。

"{items}"(dictionary) [matching-items];
// 将一系类的C值转换成Python的字典，每一对连续的C值将转换成一个键值对。
```

举例

```c++
// 后面为PyObject的返回值

Py_BuildValue("")  // None

Py_BuildValue("i",123)  // 123

Py_BuildValue("iii",123, 456, 789)  // (123, 456, 789)

Py_BuildValue("s","hello")  // 'hello'

Py_BuildValue("ss","hello", "world")  // ('hello', 'world')

Py_BuildValue("s#","hello", 4)  // 'hell'

Py_BuildValue("()")  // ()

Py_BuildValue("(i)",123)  // (123,)      

Py_BuildValue("(ii)",123, 456)  // (123, 456)

Py_BuildValue("(i,i)",123, 456)  // (123, 456)

Py_BuildValue("[i,i]",123, 456)  // [123, 456]
    
Py_BuildValue("{s:i,s:i}", "abc",123, "def", 456)  // {'abc': 123, 'def': 456}

Py_BuildValue("((ii)(ii))(ii)", 1, 2, 3, 4, 5, 6)  // (((1, 2), (3, 4)), (5, 6))
```

### 五、元组操作函数：

```c++
因为程序之间传递的参数，大多数为Tuple类型，所以有专门的函数来操作元组：

PyAPI_FUNC(PyObject *)PyTuple_New(Py_ssize_t size);

解释：新建一个参数列表（调试了下，发现其实是用链表实现的），size列表为长度的宽度

PyAPI_FUNC(Py_ssize_t)PyTuple_Size(PyObject *);

解释：获取该列表的大小

PyAPI_FUNC(PyObject *)PyTuple_GetItem(PyObject *, Py_ssize_t);

解释：获取该列表某位置的值

PyAPI_FUNC(int) PyTuple_SetItem(PyObject *,Py_ssize_t, PyObject *);

解释：设置该列表此位置的值。如PyTuple_SetItem(pyParams,1,Py_BuildValue("i",2));设置第2个位置的值为2的整数。
```

### 方法一：主流方法将python程序编程文本形式的动态链接库，在c/c++程序中调用其中定义的函数

#### 1. 链接到Python调用库

Python 安装目录下已经包含头文件( include 目录)和库文件 ( Windows 下为 python27.lib)。
 使用之前需要链接到此库。

#### 2. 直接调用 Python 语句

```
#include "python/Python.h"

int main()
{
    Py_Initialize();    ## 初始化

    PyRun_SimpleString("print 'hello'");

    Py_Finalize();      ## 释放资源
}
```

#### 3. 加载 Python 模块并调用函数

​	test.py :
 ​

```
def test_add(a, b):
    print 'add ', a, ' and ', b
    return a+b


#include "python/Python.h"
#include <iostream>
using namespace std;

int main()
{
    Py_Initialize();    // 初始化

    // 将Python工作路径切换到待调用模块所在目录，一定要保证路径名的正确性
    string path = "~/test";
    string chdir_cmd = string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);

    // 加载模块
    PyObject* moduleName = PyString_FromString("test"); //模块名，不是文件名
    PyObject* pModule = PyImport_Import(moduleName);
    if (!pModule) // 加载模块失败
    {
        cout << "[ERROR] Python get module failed." << endl;
        return 0;
    }
    cout << "[INFO] Python get module succeed." << endl;

    // 加载函数
    PyObject* pv = PyObject_GetAttrString(pModule, "test_add");
    if (!pv || !PyCallable_Check(pv))  // 验证是否加载成功
    {
        cout << "[ERROR] Can't find funftion (test_add)" << endl;
        return 0;
    }
    cout << "[INFO] Get function (test_add) succeed." << endl;

    // 设置参数
    PyObject* args = PyTuple_New(2);   // 2个参数
    PyObject* arg1 = PyInt_FromLong(4);    // 参数一设为4
    PyObject* arg2 = PyInt_FromLong(3);    // 参数二设为3
    PyTuple_SetItem(args, 0, arg1);
    PyTuple_SetItem(args, 1, arg2);

    // 调用函数
    PyObject* pRet = PyObject_CallObject(pv, args);

    // 获取参数
    if (pRet)  // 验证是否调用成功
    {
        long result = PyInt_AsLong(pRet);
        cout << "result:" << result;
    }

    Py_Finalize();      ## 释放资源

    return 0;
}
```

### 方法二：完整调用python脚本文件及参数的方法。

以下是测试用的python脚本文件，功能是输出命令行参数：sample.py

```
# !/usr/bin/env python2.6
import sys
def test():
    for arg in sys.argv:
        print arg

if __name__=='__main__':
    test()
```

以下是测试用的c程序文件：test.c

```
#include "python2.6/Python.h"
int main()
{
    //第一步：初始化Python
    //在调用Python的提供的给C的API之前，通过执行初始化
    //来添加Python的内建模块、__main__、sys等
    Py_Initialize();

    //检查初始化是否完成
    if (!Py_IsInitialized())
    {
        return -1;
    }

    //第二步：导入sys模块
    PyRun_SimpleString("import sys");

    //第三步：导入执行脚本时的命令行参数，如：./sample.py int argc = 2;   
	char *argv[2];  
	argv[0] = "arg1";   
	argv[1] = "arg2";
	PySys_SetArgv(argc, argv);

    //第四步：执行调用脚本文件命令,注意文件的路径
    if (PyRun_SimpleString("execfile('./sample.py')") == NULL)
    {
        return -1;
    }

    //第五步：关闭Python解释器
    Py_Finalize();
    return 0;
}

编译指令:

g++ -g -W -o test test.cpp -I /usr/include/ -L /usr/lib64/ -l python2.
执行指令：./test
输出：

arg1
arg2
```





























# Python中使用C/C++

扩展参考：
（C/C++中调用Python）

- [【Python官网文档】Python/C API 参考手册](https://docs.python.org/zh-cn/3.7/c-api/index.html)，编写扩展模块并将 Python 解释器嵌入其应用程序中的 C 和 C++ 程序员可用的 API
- [【Python官网文档】Python/C API 概述](https://docs.python.org/zh-cn/3.7/c-api/intro.html)，C 和 C++ 程序员可以在多个层级上访问 Python 解释器
- [【CSDN】QT——调用Python脚本](https://blog.csdn.net/wzyaiwl/article/details/115298127)
- ==部分内容详见《QT》笔记中《调用Python脚本》==

参考：
（Python中使用C/C++）

- [【Python官网】扩展和嵌入 Python 解释器](https://docs.python.org/zh-cn/3.7/extending/index.html)，如何使用 C 或 C++ 编写模块以使用新模块来扩展 Python 解释器的功能
- [【Python官网文档】使用 C 或 C++ 扩展 Python](https://docs.python.org/zh-cn/3.7/extending/extending.html)

## 简概

本文档描述了如何使用 C 或 C++ 编写模块以使用新模块来扩展 Python 解释器的功能。  这些模块不仅可以定义新的函数，还可以定义新的对象类型及其方法。 该文档还描述了如何将 Python  解释器嵌入到另一个应用程序中，以用作扩展语言。  最后，它展示了如何编译和链接扩展模块，以便它们可以动态地（在运行时）加载到解释器中，如果底层操作系统支持此特性的话。

本文档假设你具备有关 Python 的基本知识。有关该语言的非正式介绍，请参阅 [Python 教程](https://docs.python.org/zh-cn/3.7/tutorial/index.html#tutorial-index) 。 [Python语言参考](https://docs.python.org/zh-cn/3.7/reference/index.html#reference-index) 给出了更正式的语言定义。 [Python 标准库](https://docs.python.org/zh-cn/3.7/library/index.html#library-index) 包含现有的对象类型、函数和模块（内置和用 Python 编写）的文档，使语言具有广泛的应用范围。

关于整个 Python/C API 的详细介绍，请参阅独立的 [Python/C API 参考手册](https://docs.python.org/zh-cn/3.7/c-api/index.html#c-api-index) 。

## 重要注意项

### c文件命名规范

（传统上，如果一个模块叫 `spam`，则对应实现它的 C 文件叫 `spammodule.c`；如果这个模块名字非常长，比如 `spammify`，则这个模块的文件可以直接叫 `spammify.c`。）

### Python.h函数名规范

所有在 `Python.h` 中定义的用户可见的符号都具有 `Py` 或 `PY` 前缀，已在标准头文件中定义的那些除外。

 考虑到便利性，也由于其在 Python 解释器中被广泛使用，`"Python.h"` 还包含了一些标准头文件: `<stdio.h>`，`<string.h>`，`<errno.h>` 和 `<stdlib.h>`。 
如果后面的头文件在你的系统上不存在，它还会直接声明函数 `malloc()`，`free()` 和 `realloc()`。

## 基本操作

spammodule.c

```c++
#define PY_SSIZE_T_CLEAN
#include <Python.h>  // 导入 Python API



static PyObject *
spam_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return PyLong_FromLong(sts);
}





```













