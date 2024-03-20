# Python

# 目录

# Python “反射”

## ==与Java不同点==

- Java
  - 有一个专门的包处理反射
- python
  - python作为脚本语言，根据类名字符生成类实例非常简单，类似java的Class.forName
  - python是一个脚本语言，它不像java一样有一个专门的包来处理**反射**
  - Python的内置函数提供了强大的反射机制

## 内置函数的反射机制

内置函数提供了强大的反射机制

```python
__import__()	# 加载模块
dir()			# 列表形式返回属性和方法
hasattr()		# 检测是否含有某属性
getattr()		# 获取属性
setattr()		# 设置属性
delattr()		# 删除属性
```

举例

```python
""" text2.py """
class C2():
    def __init__(self):
        print("init_C1")

""" text1.py """
class C1():
    def __init__(self):
        print("init_C1")

if __name__ == "__main__":
    # globals() 方法
    print("_______")
    class1 = globals()['C1']()  # init_C1
    class2 = globals()['C2']()

    # __import__ 方法
    print("_______")
    package = __import__('test2')
    class3 = package.C2()       # init_C2

    # __import__ 方法 + getattr() 方法
    print("_______")
    package = __import__('test2')
    temp_class = getattr(package, 'C2')
    class4 = temp_class()       # init_C2

    # __class__ 方法
    print("_______")
    class1.__class__()          # init_C1
    class2.__class__()          # init_C2

    print("_______")
    # <object> 对象
    print(class1)  				# <__main__.C1 object at 0x000001349AB76A08>
    print(class2)  				# <examples.genshin_calc.test2.C2 object at 0x000001349AB76C08>
    # <module> 对象
    print(package)              # <module 'main_test' from '...\\test2.py'>
    # <class> 对象
    print(temp_class)           # <class 'main_test.C2'>
    print(C1)                   # <class '__main__.C1'>
    print(C2)                   # <class 'examples.genshin_calc.test2.C2'>
    print(class1.__class__)     # <class '__main__.C1'>
    print(class2.__class__)     # <class 'examples.genshin_calc.test2.C2'>
    print(type(class1))         # <class '__main__.C1'>
    print(type(class2))         # <class 'examples.genshin_calc.test2.C2'>

```

## 深入 - 用9种方法来生成新的对象

参考：原文链接：https://blog.csdn.net/xiemanR/article/details/77922917

绝大多数是获取<class>对象的方法，与在 Java 中通过反射获取class类的逻辑相同

```python
point1 = Point(1, 2)										# 普通方法
point2 = eval("{}({}, {})".format("Point", 1, 2))  			# eval方法执行字符串
point6 = copy.deepcopy(point1)  							# 深拷贝方法

# 获取<class>对象的方法 - 字符串
point3 = globals()["Point"](1, 2)  							# globals()方法
point4 = locals()["Point"](1, 2)  							# locals()方法
point5 = getattr(sys.modules[__name__], "Point")(1, 2)		# getattr()方法+modules方法（也可用__import__）（需要导入sys模块）

# 获取<class>对象的方法 - 其他
point7 = point1.__class__(1, 2)  							# __class__方法
point8 = type('Point', (Point, ), {})(1, 2)					# type方法
point9 = types.new_class('Point', (Point, ), {})(1, 2)		# types模块（需要导入types模块）

# 获取<module>对象
point10 = __import__('test2').Point

```

### 效率测试（还不错）

```python
import time

def get_time(f):
    def inner(*arg, **kwarg):
        s_time = time.time()
        res = f(*arg, **kwarg)
        e_time = time.time()
        print('耗时：{}秒'.format(e_time - s_time))
        return res

    return inner

@get_time
def reflect():
    for i in range(10000000):
        globals()["Node"]

dict1 = {
	'Node': Node
}
@get_time
def get_from_register():
    for i in range(10000000):
        dict1["Node"]
        
@get_time
def only_use():
    for i in range(10000000):
        Node

reflect()				# 耗时：0.7427828311920166秒
get_from_register()		# 耗时：0.32065248489379883秒
only_use()				# 耗时：0.2612471580505371秒
```









































