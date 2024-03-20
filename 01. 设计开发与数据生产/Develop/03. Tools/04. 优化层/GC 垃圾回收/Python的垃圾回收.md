# GC 垃圾回收

# 目录

# Python的垃圾回收

参考：

- [【博客园】Python垃圾回收机制（转）](https://www.cnblogs.com/chickenwrap/p/10473124.html)

## 简概 Garbage collection(GC)

现在的高级语言如java，c#等，都采用了垃圾收集机制，而不再是c，c++里用户自己管理维护内存的方式。
自己管理内存极其自由，可以任意申请内存，但如同一把**双刃剑**，为大量**内存泄露，悬空指针**等bug埋下隐患。

对于一个字符串、列表、类甚至数值都是对象，且定位简单易用的语言，自然不会让用户去处理如何分配回收内存的问题。

python里也同java一样采用了垃圾收集机制，不过不一样的是:
python采用的是`引用计数`机制为主，`标记-清除`和`分代收集`两种机制为辅的策略

## 引用计数机制

python里每一个东西都是对象，它们的核心就是一个结构体：`PyObject`

```python
typedef struct_object {
	int ob_refcnt;				# 引用计数。当一个对象有新的引用时。它的ob_refcnt就会增加，当引用它的对象被删除，它的ob_refcnt就会减少
	struct_typeobject *ob_type;
} PyObject;  					# PyObject是每个对象必有的内容
```

方法

```c++
#define Py_INCREF(op)						// 增加计数
	((op)->ob_refcnt++)
#define Py_DECREF(op)  						// 减少计数
    if (--(op)->ob_refcnt != 0) \
    	; \
    else \
    	__Py_Dealloc((PyObject *)(op))		// 引用计数为0时删除对象，对象生命就结束了
```

### 引用计数机制的优点

1. 简单
2. 实时性：一旦没有引用，内存就直接释放了。不用像其他机制等到特定时机。实时性还带来一个好处：处理回收内存的时间分摊到了平时。

### 引用计数机制的缺点

1. 维护引用计数消耗资源

2. 循环引用

   ```python
   list1 = []
   list2 = []
   list1.append(list2)
   list2.append(list1)
   ```

   list1与list2相互引用，即便不存在其他对象对它们的引用，list1与list2的引用计数也仍然为1，**所占用的内存永远无法被回收**，这将是致命的。

   对于如今的强大硬件，缺点1尚可接受，但是循环引用导致内存泄露，注定python还将引入新的回收机制。(标记清除和分代收集)

## 画说 Ruby 与 Python 垃圾回收

## 使用GC模块

### 打印类的实例

参考：[【CSDN】python输出类的实例_打印类的所有实例](https://blog.csdn.net/weixin_39951419/article/details/113991530)

#### 方法一，利用静态成员手动计数

```python
count = 0

def __init__():
    type(self).count += 1

def __del__(self):
    type(self).count -= 1
```

#### 方法二，使用GC类

常用方法（参考官网文档：https://docs.python.org/zh-cn/3/library/gc.html?highlight=gc#module-gc）

```python
gc.enable()			# 启用自动垃圾回收
gc.disable()		# 停用自动垃圾回收
gc.isenabled()		# 返回是否启用了自动回收

gc.get_objects(generation=None)		# 返回一个收集器所跟踪的所有对象的列表
gc.get_count()						# 将当前回收计数以形为(count0, count1, count2)的元组返回

gc.is_tracked(obj)	# 当对象正在被垃圾回收器监控时返回 True。一般来说，原子类的实例不会被监控，原子类（如容器、用户自定义的对象）会被监控
gc.is_finalized(obj)# 如果给定对象已被垃圾回收器终结则返回 True，否则返回 False
```

应用

- 用来检查漏析构对象很方便
- 发现漏析构对象用，可以通过`print(gc.get_referents(obj))`发现循环引用、remove属性不彻底的问题

举例

```python
import gc

for obj in gc.get_objects():
    if isinstance(obj, Node):
        print("GC_Node", obj, gc.isenabled(), gc.get_referents(obj))
    elif isinstance(obj, Edge):
        print("GC_Edge", obj)
    elif isinstance(obj, Socket):
        print("GC_Socket", obj)
```

## 手动析构问题（与C++不同）

参考：http://c.biancheng.net/view/2371.html

- Python中
  - 不要误认为，只要为该实例对象调用 `__del__()` 方法，该对象所占用的内存空间就会被释放。
  - 举个例子：

  ```python
  class CLanguage:
      def __init__(self):
          print("调用 __init__() 方法构造对象")
          
      def __del__(self):
          print("调用__del__() 销毁对象，释放其空间")
          
  clangs = CLanguage()
  #添加一个引用clangs对象的实例对象
  cl = clangs
  del clangs  # 手动析构失败。对象没被析构，cl也不会变成空悬指针
  print("***********")
  
  """ 程序运行结果为：
  调用 __init__() 方法构造对象
  ***********
  调用__del__() 销毁对象，释放其空间
  """
  ```
- C++中
  - 调用析构函数、对象所占用的内存空间必然会被释放。上面的例子中，cl会变成 `空悬指针`

























