# Debounced防抖

# 目录

# Debounced防抖

参考：

-   [【稀土掘金】javascript函数防抖Debounce](https://juejin.cn/post/6844903749429919758#heading-1)（这篇文章很不错，还有很多额外的东西）
-   [【CSDN】JavaScript 防抖、节流：限制事件回调函数的调用次数](https://blog.csdn.net/qq_39706777/article/details/121975197)（这个简易版，不能处理有返回值的情况）

## 简易版（不能处理有返回值的情况）

```js
function debounce(fn,delay){
  let timer
  return function(){
    let _this = this
    let args = arguments
    if(timer){
      clearTimeout(timer)
    }
    timer = setTimeout(()=>{
      fn.apply(_this,args)
    },delay)
  }
}
let debounceSayHi = debounce(sayHi,1000)
window.addEventListener('resize',()=>{
  debounceSayHi('lucy')
})

```



## 完整版

### 函数防抖最终版

```js
function debounce(method, wait, immediate) {
  let timeout
  // debounced函数为返回值
  // 使用Async/Await处理异步，如果函数异步执行，等待setTimeout执行完，拿到原函数返回值后将其返回
  // args为返回函数调用时传入的参数，传给method
  let debounced = function(...args) {
    return new Promise (resolve => {
      // 用于记录原函数执行结果
      let result
      // 将method执行时this的指向设为debounce返回的函数被调用时的this指向
      let context = this
      // 如果存在定时器则将其清除
      if (timeout) {
        clearTimeout(timeout)
      }
      // 立即执行需要两个条件，一是immediate为true，二是timeout未被赋值或被置为null
      if (immediate) {
        // 如果定时器不存在，则立即执行，并设置一个定时器，wait毫秒后将定时器置为null
        // 这样确保立即执行后wait毫秒内不会被再次触发
        let callNow = !timeout
        timeout = setTimeout(() => {
          timeout = null
        }, wait)
        // 如果满足上述两个条件，则立即执行并记录其执行结果
        if (callNow) {
          result = method.apply(context, args)
          resolve(result)
        }
      } else {
        // 如果immediate为false，则等待函数执行并记录其执行结果
        // 并将Promise状态置为fullfilled，以使函数继续执行
        timeout = setTimeout(() => {
          // args是一个数组，所以使用fn.apply
          // 也可写作method.call(context, ...args)
          result = method.apply(context, args)
          resolve(result)
        }, wait)
      }
    })
  }

  // 在返回的debounced函数上添加取消方法
  debounced.cancel = function() {
    clearTimeout(timeout)
    timeout = null
  }

  return debounced
}

```

需要注意的是，如果需要原函数返回值，调用防抖后的函数的外层函数需要使用Async/Await语法等待执行结果返回

使用方法见代码：

```js
function square(num) {
  return Math.pow(num, 2)
}

let debouncedFn = debounce(square, 1000, false)

window.addEventListener('resize', async () => {
  let val
  try {
    val = await debouncedFn(4)
  } catch (err) {
    console.error(err)
  }
  // 停止缩放1S后输出：
  // 原函数的返回值为：16
  console.log(`原函数返回值为${val}`)
}, false)

```

具体的实现步骤请往下看

### Debounce 的实现

#### 1. 《JavaScript高级程序设计》（第三版）中的实现

```scss
function debounce(method, context) {
  clearTimeout(method.tId)
  method.tId = setTimeout(() => {
    method.call(context)
  }, 1000)
}

function print() {
  console.log('Hello World')
}

window.onresize = debounce(print)
复制代码复制代码
```

我们不停缩放窗口，当停止1S后，打印出Hello World。

**有个可以优化的地方**: 此实现方法有副作用（Side Effect），改变了输入值（method），给method新增了属性

#### 2. 优化第一版：消除副作用，将定时器隔离

```scss
function debounce(method, wait, context) {
  let timeout
  return function() {
    if (timeout) {
      clearTimeout(timeout)
    }
    timeout = setTimeout(() => {
      method.call(context)
    }, wait)
  }
}
复制代码复制代码
```

#### 3. 优化第二版：自动调整this正确指向

之前的函数我们需要手动传入函数执行上下文`context`，现在优化将 this 指向正确的对象。

```javascript
function debounce(method, wait) {
  let timeout
  return function() {
    // 将method执行时this的指向设为debounce返回的函数被调用时的this指向
    let context = this
    if (timeout) {
      clearTimeout(timeout)
    }
    timeout = setTimeout(() => {
      method.call(context)
    }, wait)
  }
}
复制代码复制代码
```

#### 4. 优化第三版：函数可传入参数

即便我们的函数不需要传参，但是别忘了JavaScript 在事件处理函数中会提供事件对象 event，所以我们要实现传参功能。

```javascript
function debounce(method, wait) {
  let timeout
  // args为返回函数调用时传入的参数，传给method
  return function(...args) {
    let context = this
    if (timeout) {
      clearTimeout(timeout)
    }
    timeout = setTimeout(() => {
      // args是一个数组，所以使用fn.apply
      // 也可写作method.call(context, ...args)
      method.apply(context, args)
    }, wait)
  }
}
复制代码复制代码
```

#### 5. 优化第四版：提供立即执行选项

有些时候我不希望非要等到事件停止触发后才执行，我希望立刻执行函数，然后等到停止触发n毫秒后，才可以重新触发执行。

```scss
function debounce(method, wait, immediate) {
  let timeout
  return function(...args) {
    let context = this
    if (timeout) {
      clearTimeout(timeout)
    }
    // 立即执行需要两个条件，一是immediate为true，二是timeout未被赋值或被置为null
    if (immediate) {
      // 如果定时器不存在，则立即执行，并设置一个定时器，wait毫秒后将定时器置为null
      // 这样确保立即执行后wait毫秒内不会被再次触发
      let callNow = !timeout
      timeout = setTimeout(() => {
        timeout = null
      }, wait)
      if (callNow) {
        method.apply(context, args)
      }
    } else {
      // 如果immediate为false，则函数wait毫秒后执行
      timeout = setTimeout(() => {
        // args是一个类数组对象，所以使用fn.apply
        // 也可写作method.call(context, ...args)
        method.apply(context, args)
      }, wait)
    }
  }
}
复制代码复制代码
```

#### 6. 优化第五版：提供取消功能

有些时候我们需要在不可触发的这段时间内能够手动取消防抖，代码实现如下：

```scss
function debounce(method, wait, immediate) {
  let timeout
  // 将返回的匿名函数赋值给debounced，以便在其上添加取消方法
  let debounced = function(...args) {
    let context = this
    if (timeout) {
      clearTimeout(timeout)
    }
    if (immediate) {
      let callNow = !timeout
      timeout = setTimeout(() => {
        timeout = null
      }, wait)
      if (callNow) {
        method.apply(context, args)
      }
    } else {
      timeout = setTimeout(() => {
        method.apply(context, args)
      }, wait)
    }
  }

  // 加入取消功能，使用方法如下
  // let myFn = debounce(otherFn)
  // myFn.cancel()
  debounced.cancel = function() {
    clearTimeout(timeout)
    timeout = null
  }
}
复制代码复制代码
```

至此，我们已经比较完整地实现了一个underscore中的debounce函数。

### 遗留问题

需要防抖的函数可能是存在返回值的，我们要对这种情况进行处理。
`underscore`的处理方法是将函数返回值在返回的`debounced`函数内再次返回，但是这样其实是有问题的。如果参数`immediate`传入值不为`true`的话，当防抖后的函数第一次被触发时，如果原始函数有返回值，其实是拿不到返回值的，因为原函数是在`setTimeout`内，是异步延迟执行的，而`return`是同步执行的，所以返回值是`undefined`。

第二次触发时拿到的返回值其实是第一次执行的返回值，第三次触发时拿到的返回值其实是第二次执行的返回值，以此类推。

##  使用回调函数处理函数返回值

```scss
function debounce(method, wait, immediate, callback) {
  let timeout, result
  let debounced = function(...args) {
    let context = this
    if (timeout) {
      clearTimeout(timeout)
    }
    if (immediate) {
      let callNow = !timeout
      timeout = setTimeout(() => {
        timeout = null
      }, wait)
      if (callNow) {
        result = method.apply(context, args)
        // 使用回调函数处理函数返回值
        callback && callback(result)
      }
    } else {
      timeout = setTimeout(() => {
        result = method.apply(context, args)
        // 使用回调函数处理函数返回值
        callback && callback(result)
      }, wait)
    }
  }

  debounced.cancel = function() {
    clearTimeout(timeout)
    timeout = null
  }

  return debounced
}
复制代码复制代码
```

这样我们就可以在函数防抖时传入一个回调函数来处理函数的返回值，使用代码如下：

```javascript
function square(num) {
  return Math.pow(num, 2)
}

let debouncedFn = debounce(square, 1000, false, val => {
  console.log(`原函数的返回值为：${val}`)
})

window.addEventListener('resize', () => {
  debouncedFn(4)
}, false)

// 停止缩放1S后输出：
// 原函数的返回值为：16
复制代码复制代码
```

## 2. 使用Promise处理返回值

```scss
function debounce(method, wait, immediate) {
  let timeout, result
  let debounced = function(...args) {
    // 返回一个Promise，以便可以使用then或者Async/Await语法拿到原函数返回值
    return new Promise(resolve => {
      let context = this
      if (timeout) {
        clearTimeout(timeout)
      }
      if (immediate) {
        let callNow = !timeout
        timeout = setTimeout(() => {
          timeout = null
        }, wait)
        if (callNow) {
          result = method.apply(context, args)
          // 将原函数的返回值传给resolve
          resolve(result)
        }
      } else {
        timeout = setTimeout(() => {
          result = method.apply(context, args)
          // 将原函数的返回值传给resolve
          resolve(result)
        }, wait)
      }
    })
  }

  debounced.cancel = function() {
    clearTimeout(timeout)
    timeout = null
  }

  return debounced
}
复制代码复制代码
```

**使用方法一**：在调用防抖后的函数时，使用`then`拿到原函数的返回值

```javascript
function square(num) {
  return Math.pow(num, 2)
}

let debouncedFn = debounce(square, 1000, false)

window.addEventListener('resize', () => {
  debouncedFn(4).then(val => {
    console.log(`原函数的返回值为：${val}`)
  })
}, false)

// 停止缩放1S后输出：
// 原函数的返回值为：16
复制代码复制代码
```

**使用方法二**：调用防抖后的函数的外层函数使用Async/Await语法等待执行结果返回

使用方法见代码：

```javascript
function square(num) {
  return Math.pow(num, 2)
}

let debouncedFn = debounce(square, 1000, false)

window.addEventListener('resize', async () => {
  let val
  try {
    val = await debouncedFn(4)
  } catch (err) {
    console.error(err)
  }
  console.log(`原函数返回值为${val}`)
}, false)

// 停止缩放1S后输出：
// 原函数的返回值为：16复制代码
```







































