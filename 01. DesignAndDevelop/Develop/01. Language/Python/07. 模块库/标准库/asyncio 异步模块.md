# Python

# 目录

# asyncio模块

参考文章：http://www.ruanyifeng.com/blog/2019/11/python-asyncio.html

## 简概

### 简概

Python 的异步编程，其他人可能觉得很难，但是 JavaScript 程序员应该特别容易理解，因为两者的概念和语法类似

[JavaScript 的异步模型](http://es6.ruanyifeng.com/#docs/async)更简单直观，很适合作为学习 Python 异步的基础

本文解释 Python 的异步模块 [`asyncio`](https://docs.python.org/3/library/asyncio.html) 的概念和基本用法，并且演示如何通过 Python 脚本操作无头浏览器[pyppeteer](https://github.com/miyakogi/pyppeteer)

### 历史由来

- 多线程与多进程
    - 历史上，Python 并不支持专门的异步编程语法，因为不需要
    - 有了[多线程（`threading`）和多进程（`multiprocessing`）](https://timber.io/blog/multiprocessing-vs-multithreading-in-python-what-you-need-to-know/)，就没必要一定支持异步了
    - 如果一个线程（或进程）阻塞，新建其他线程（或进程）就可以了，程序不会卡死
- 异步编程
    - 但是，多线程有"线程竞争"的问题，处理起来很复杂，还涉及**加锁**。对于简单的异步任务来说（比如与网页互动），写起来很麻烦
    - Python 3.4 引入了 `asyncio` 模块，增加了异步编程，跟 JavaScript 的`async/await` 极为类似，大大方便了异步任务的处理
    - 它受到了开发者的欢迎，成为从 Python 2 升级到 Python 3 的主要理由之一

## asyncio 的设计

### 简概

- 特点
    - `asyncio` 模块最大特点就是，只存在一个线程，跟 JavaScript 一样
- 原理
    - 由于只有一个线程，就不可能多个任务同时运行。asyncio 是`多任务合作`模式（*cooperative multitasking*），允许异步任务交出执行权给其他任务，等到其他任务完成，再收回执行权继续往下执行，这跟 JavaScript 也是一样的
    - 由于代码的执行权在多个任务之间交换，所以看上去好像多个任务同时运行，其实底层只有一个线程，多个任务分享运行时间
- 优点、与多线程比较
    - 表面上，这是一个不合理的设计，明明有多线程多进程的能力，为什么放着多余的 CPU 核心不用，而只用一个线程呢？
    - 但是就像前面说的，单线程简化了很多问题，使得代码逻辑变得简单，写法符合直觉

### 原理

asyncio 模块在单线程上启动一个事件循环（event loop），时刻监听新进入循环的事件，加以处理，并不断重复这个过程，直到异步任务结束。事件循环的内部机制，可以参考 [JavaScript 的模型](https://wangdoc.com/javascript/async/general.html)，两者是一样的

![img](https://www.wangbase.com/blogimg/asset/201911/bg2019112005.jpg)

## asyncio API

下面介绍 `asyncio` 模块最主要的几个API==（注意，必须使用 Python 3.7 或更高版本，早期的语法已经变了）==

### 基本流程

- 第一步，`import` 加载 `asyncio` 模块
    - `import asyncio`
- 第二步，函数前面加上 `async` 关键字。就变成了 async 函数。**这种函数最大特点是执行可以暂停，交出执行权**
    - `async def main():`
- 第三步，在 async 函数内部的异步任务前面，加上`await`命令
    - `await asyncio.sleep(1)`
        - 上面代码中，`asyncio.sleep(1)` 方法可以生成一个异步任务（异步函数包含异步任务），休眠1秒钟然后结束。
        - 执行引擎遇到`await`命令，就会在异步任务开始执行之后，暂停当前 async 函数的执行，把执行权交给其他任务
        - 等到异步任务结束，再把执行权交回 async 函数，继续往下执行
- 第四步，`async.run()` 方法加载 async 函数，启动事件循环
    - `asyncio.run(main())`
        - 上面代码中，`asyncio.run()` 在事件循环上监听 async 函数`main`的执行。等到 `main` 执行完了，事件循环才会终止。
- 实例

```python
#!/usr/bin/env python3
# async.py

import asyncio

async def count():				# 手动定义异步函数
    print("One")
    await asyncio.sleep(1)		# 停止，并交出执行权。等其他处理完再回来
    print("Two")

async def main():
    await asyncio.gather(count(), count(), count())
    print("Three")

asyncio.run(main())

'''
One
One
One（等待1s）
Two
Two
Two
Three
'''
```

### 其他API

#### asyncio.run()

运行异步函数

#### asyncio.sleep(n)

与`time.sleep()`方法不同的是，这个方法是`异步任务`，而且多个这种方法只会计时一次？不会叠加？

#### asyncio.gather()

`asyncio.gather()` 方法将多个异步任务包装成一个新的异步任务，必须等到内部的多个异步任务都执行结束，这个新的异步任务才会结束

## pyppeteer 模块实战实例

无头浏览器 Puppeteer 的 Python 移植，API 跟 JavaScript 版本基本一致

- 安装：`$ python3 -m pip install pyppeteer`

### 写一个网页截图脚本`screenshot.py`

```python
#!/usr/bin/env python3
# screenshot.py

import asyncio
from pyppeteer import launch

async def main():
    browser = await launch()						# 启动浏览器
    page = await browser.newPage()					# 异步任务 - 打卡新Tab
    await page.goto('http://example.com')			# 访问网址
    await page.screenshot({'path': 'example.png'})	# 截图
    await browser.close()							# 关闭浏览器

asyncio.run(main())
```

## ==大坑【jupyter中运行异步函数报错】==

jupyter 已经运行了loop，无需自己激活，采用上文中的await()调用即可

如果按上面的`screenshot.py`来写会报错，应改为

```python
#!/usr/bin/env python3
# screenshot.py

# import asyncio									# 【改动】
from pyppeteer import launch

async def main():
    browser = await launch()						# 启动浏览器
    page = await browser.newPage()					# 异步任务 - 打卡新Tab
    await page.goto('http://example.com')			# 访问网址
    await page.screenshot({'path': 'example.png'})	# 截图
    await browser.close()							# 关闭浏览器

# asyncio.run(main())								# 【改动】
await main()										# 【改动】
```



































