---
last_time: 2020.06.13
tag: 有道云
---

# 高阶for函数

## 一般的for

```js
for (let index =0; i<this.books.lebgth; index++) {}
```

## for in

```js
for (let index in this.books) {}
```

## for of

```js
for (let item of this.books) {}
```

## for each

```js
……
```

## filter、map、reduce

数组高阶函数方法

**注意：不会改变原有数组！要赋给新值！**

编程范式：命令式编程（js）、声明式编程（vue）

编程范式：面向对象编程（第一公民：对象）、函数式编程（第一公民：函数）

这里的高阶函数就是函数式编程

据说和java8的lambda表达式类似？

### filter过滤。回调返回布尔

```js
let arr2 = arr.filter(function (item) { return item % 2 })
```

### map映射。回调返回新值

```js
let arr2 = arr.map(function (n) { return n *2 })
```

### reduce汇总（减少）

用ts写的，因为重载，回调函数可传1/2个参而不会覆盖

```js
let total = arr.reduce(function (preValue, n) { return preValue+n }, 0) // 这里preValue表示前一次，n表示遍历的当前项，reduce第二个参是初始值 
```

### 综合

```js
let total = arr.filter(n => n<100).map(n => n*2).reduce((pre,n) => pre+n)
```

