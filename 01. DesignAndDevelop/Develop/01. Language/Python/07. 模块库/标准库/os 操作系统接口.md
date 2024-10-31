# Python

# 目录

# os 操作系统接口

参考文档：https://docs.python.org/zh-cn/3/library/os.html#module-os

在使用一些像 `os` 这样的大型模块时内置的 dir() 和 help() 函数非常有用:

```python
>>> import os
>>> dir(os)								# dir，返回所有模块功能的列表
...
>>> help(os)							# help，返回从模块的文档字符串创建的详细手册页
...
```

提供了很多与操作系统交互的函数

```python
>>> import os
>>> os.getcwd()      					# 返回当前工作目录
'C:\\Python35'
>>> os.chdir('/server/accesslogs')   	# 改变当前工作目录
>>> os.system('mkdir today')   			# 在系统shell中运行命令'mkdir today'
0
```

针对日常的文件和目录管理任务，`shutil` 模块提供了一个易于使用的高级接口：（有点像shell）

```python
>>> import shutil
>>> shutil.copyfile('data.db', 'archive.db')		# 复制文件
'archive.db'
>>> shutil.move('/build/executables', 'installdir')	# 移动
'installdir'
```

