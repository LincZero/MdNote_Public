# Python

# 目录

# sys 命令行参数

## 命令行参数

参考文档：https://docs.python.org/3/library/sys.html#module-sys

通用工具脚本经常调用命令行参数。这些命令行参数以链表形式存储于 sys 模块的 argv 变量

例如在命令行中执行 `python demo.py one two three` 后可以得到以下输出结果：

```python
>>> import sys
>>> print(sys.argv)
['demo.py', 'one', 'two', 'three']
```

[getopt](https://docs.python.org/3/library/getopt.html#module-getopt) 模块使用 Unix [getopt()](https://docs.python.org/3/library/getopt.html#module-getopt) 函数处理 *sys.argv*。更多的复杂命令行处理由 [argparse](https://docs.python.org/3/library/argparse.html#module-argparse) 模块提供

## 错误输出重定向和程序终止

[sys](https://docs.python.org/3/library/sys.html#module-sys) 还有 *stdin*， *stdout* 和 *stderr* 属性，即使在 *stdout* 被重定向时，后者也可以用于显示警告和错误信息：

```python
>>> sys.stderr.write('Warning, log file not found starting a new one\n')
Warning, log file not found starting a new one
```

大多脚本的直接终止都使用 `sys.exit()`

即类似于C++的修改错误默认行为

## 【标准】sys模块

- 官网模块文档：http://docs.python.org/library/sys
- 作用：能访问到由Python解释器使用或维护的对象，其中包括：
    - 标志、版本、整型数最大尺寸、可用的模块、hook路径、标准错误/输入/输出的位置、调用解释器的命令行参数
- demo：`$ python vuln-scanner.py vuln-banners.txt`调用python时：

```python
# python vuln-scanner.py vuln-banners.txt调用时
import sys
if len(sys.argv)==2:  # python启动的参数
	filename = sys.argv[1]  # 第二个启动的参数
```



