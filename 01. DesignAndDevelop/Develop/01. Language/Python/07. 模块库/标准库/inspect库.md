# Python

# 目录

# inspect库

## 获取文档注释

一般的打印文档注释的方法

```python
"""
这里是文档注释
"""

def main():
    print(__doc__)		# 打印这个文件的文档注释
	return None

if __name__ == "main__":
    main()

# [打印结果]-------------------------------
这里是文档注释
```

用inspect库的方法

```python
import inspect

def test():
    """ 函数中的文档注释 """
    pass

def main():
    print(inspect.getdoc(test))		# 打印test函数中的文档注释
	return None

if __name__ == "main__":
    main()
    
# [打印结果]-------------------------------
 函数中的文档注释 
```

## 获取源代码

甚至可以获取源代码

```python
import inspect

def test():
    """ 函数中的文档注释 """
    pass

def main():
    print(inspect.getdoc(test))	
	return None

if __name__ == "main__":
    main()

# [打印结果]-------------------------------
def test():
    """ 函数中的文档注释 """
    pass
```

## Python迷惑行为：我的代码一被修改就不能运行了

参考：B站 BV1aP41157hu

```python
def b():
    """
    这个函数不会修改，否则会出bug
    """
    ...
    # 这里的代码写隐秘点，不要被你的同事发现
    import inspect
    content = inspect.getsource(b)
    import hashlib
    password = eval(f"0x{str(hashlib.sha256(content.encode()).hexdigest())}")%1000	# 获取这个函数源代码的hash值
    if p != 100:	# 由于这个数字发生改变时，hash值也会改变。所以要么把这个hash存储在外面，要么暴力破解。前面将hash缩小到三位数就是为了方便暴力
        			# 如果暴力无解就随便改一下
        print("都说了不要改我代码")
        return 0
    else:
        print("代码没有被修改")
    ...
    
```



























