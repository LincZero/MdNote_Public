# C++

# 目录

# 调用WindowsAPI

接口

```c++
#include<Windows.h>

int WINAPI MessageBox(
    HWND hWnd,			// 窗口句柄
    LPCTSTR lpText,		// 字符串描述
    LPCTSTR lpCaption,	// 字符串标题
    UINT uType			// 窗口类型。为0就有确定按钮，为1则有确定和取消按钮
);
```

 使用举例

```c++
MessageBoxA(0, "Content", "Title", 0);	// 注意方法加了个后缀“A”
```

API支持

```properties
# QT中要在pro文件中加一句：
LIBS += User32.LIB
# 提供windows.h的实现，否则报错：无法解析的外部指令的解决方法 1104
```

