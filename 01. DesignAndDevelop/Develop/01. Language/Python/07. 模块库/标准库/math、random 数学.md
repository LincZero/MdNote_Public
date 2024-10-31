# Python

# 目录

# math、random 数学

[math](https://docs.python.org/3/library/math.html#module-math) 模块为浮点运算提供了对底层C函数库的访问:

```python
>>> import math
>>> math.cos(math.pi / 4.0)
0.70710678118654757
>>> math.log(1024, 2)
10.0
```

[random](https://docs.python.org/3/library/random.html#module-random) 提供了生成随机数的工具:

```python
>>> import random
>>> random.choice(['apple', 'pear', 'banana'])
'apple'
>>> random.sample(range(100), 10)   # sampling without replacement
[30, 83, 16, 4, 8, 81, 41, 50, 18, 33]
>>> random.random()    # random float
0.17970987693706186
>>> random.randrange(6)    # random integer chosen from range(6)
4
```

SciPy <http://scipy.org> 项目提供了许多数值计算的模块。

