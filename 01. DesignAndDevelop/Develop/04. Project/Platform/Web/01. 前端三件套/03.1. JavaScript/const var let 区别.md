---
last_time: 2020.04.13
tag: 有道云
---

# const var let 区别

## const定义的变量

（1）不可以修改

（2）必须初始化，否则报错

常用于引用模块：const express = require('express')

```js
const b = 2; // 正确，const b则错误
console.log('函数外const定义b：' + b); //有输出值              
```

## var定义的变量

（1）可以修改

（2）可不初始化，会输出undefined

```js
var a = 1;
console.log('函数外var定义a：' + a);//可以输出a=1
function change(){
    a = 4;
    console.log('函数内var定义a：' + a);//可以输出a=4
} 
change();
console.log('函数调用后var定义a为函数内部修改值：' + a);//可以输出a=4        
```

## let定义的变量

（1）块级作用域定义，对函数外部无影响

```js
let c = 3;
console.log('函数外let定义c：' + c);//输出c=3
function change(){
    let c = 6;
    console.log('函数内let定义c：' + c);//输出c=6
} 
change();
console.log('函数调用后let定义c不受函数内部定义影响：' + c);//输出c=3         
```

​    