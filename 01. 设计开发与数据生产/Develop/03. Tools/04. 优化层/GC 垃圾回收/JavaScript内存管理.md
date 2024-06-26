# JavaScript内存管理

参考：https://juejin.cn/post/6844903869525262349

## 内存生命周期

像C语言这样的底层语言一般都有底层的内存管理接口，比如 malloc()和free()用于分配内存和释放内存。 

而对于JavaScript来说，会在创建变量（对象，字符串等）时分配内存，并且在不再使用它们时“自动”释放内存，这个自动释放内存的过程称为垃圾回收。 

因为自动垃圾回收机制的存在，让大多Javascript开发者感觉他们可以不关心内存管理，所以会在一些情况下导致内存泄漏。

JS 环境中分配的内存有如下声明周期：

1. 内存分配：当我们申明变量、函数、对象的时候，系统会自动为他们分配内存
2. 内存使用：即读写内存，也就是使用变量、函数等
3. 内存回收：使用完毕，由垃圾回收机制自动回收不再使用的内存

### 内存分配

为了不让程序员费心分配内存，JavaScript 在定义变量时就完成了内存分配。

```js
// 基本变量分配
var n = 123;		// 给数值变量分配内存
var s = "azerty";	// 给字符串分配内存
var o = {
  a: 1,
  b: null
};					// 给对象及其包含的值分配内存
var a = [1, null, "abra"];  // 给数组及其包含的值分配内存（就像对象一样）

// 函数 (可调用的对象) 内存
function f(a) {		// 给函数（可调用的对象）分配内存
  return a + 2;
}
someElement.addEventListener('click', function() { 
  someElement.style.backgroundColor = 'blue';
}, false);			// 函数表达式也能分配一个对象

// 有些函数调用结果是分配对象内存、新变量、或者新对象
var d = new Date(); // 分配一个 Date 对象
var e = document.createElement('div'); // 分配一个 DOM 元素

var s = "azerty";
var s2 = s.substr(0, 3); 	// s2 是一个新的字符串
                            // 因为字符串是不变量，
                            // JavaScript 可能决定不分配内存，
                            // 只是存储了 [0-3] 的范围。

var a = ["ouais ouais", "nan nan"];
var a2 = ["generation", "nan nan"];
var a3 = a.concat(a2); 		// 新数组有四个元素，是 a 连接 a2 的结果
```

### 内存使用

使用值的过程实际上是对分配内存进行读取与写入的操作。 读取与写入可能是写入一个变量或者一个对象的属性值，甚至传递函数的参数。

```js
var a = 10;		// 分配内存
console.log(a); // 对内存的使用
```

### 内存回收

JS 有自动垃圾回收机制，那么这个自动垃圾回收机制的原理是什么呢？ 其实很简单，就是**找出那些不再继续使用的值**，然后释放其占用的内存。

大多数内存管理的问题都在这个阶段。 在这里最艰难的任务是找到不再需要使用的变量。

不再需要使用的变量也就是生命周期结束的变量，是局部变量，局部变量只在函数的执行过程中存在， 当函数运行结束，没有其他引用 (闭包)，那么该变量会被标记回收。

全局变量的生命周期直至浏览器卸载页面才会结束，也就是说全局变量不会被当成垃圾回收。

因为自动垃圾回收机制的存在，开发人员可以不关心也不注意内存释放的有关问题，但对无用内存的释放这件事是客观存在的。 不幸的是，即使不考虑垃圾回收对性能的影响，目前最新的垃圾回收算法，也无法智能回收所有的极端情况。

接下来我们来探究一下 JS 垃圾回收的机制。

## 垃圾回收

### 引用

垃圾回收算法主要依赖于引用的概念。

在内存管理的环境中，一个对象如果有访问另一个对象的权限（隐式或者显式），叫做一个对象引用另一个对象。

例如，一个Javascript对象具有对它原型的引用（隐式引用）和对它属性的引用（显式引用）。

在这里，“对象”的概念不仅特指 JavaScript 对象，还包括函数作用域（或者全局词法作用域）。

### 算法1: 引用计数垃圾收集

这是最初级的垃圾回收算法。

引用计数算法定义“内存不再使用”的标准很简单，就是看一个对象是否有指向它的引用。 如果没有其他对象指向它了，说明该对象已经不再需了。

```js
var o = { // 对象obj1
  a: { // 对象obj2
    b:2
  }
}; 
// 计数：obj1:1(o), obj2:1(obj1)，一个作为另一个的属性被引用，另一个被分配给变量o

var o2 = o;
// 计数：obj1:2(o,o2), obj2:1(obj1)

o = 1;
// 计数: obj1:1(o2), obj2:1(obj1)

var oa = o2.a; // 引用“这个对象”的a属性。现在，“这个对象”有两个引用了，一个是o2，一个是oa
// 计数：obj1:1(o2), obj2:2(obj1,oa)

o2 = "yo";
// 计数：obj1:0, obj2:1(oa)。此时obj1被垃圾回收

oa = null;
// 计数: obj1:0, obj2:0.此时obj2也被垃圾回收
```

由上面可以看出，引用计数算法是个简单有效的算法。但它却存在一个致命的问题：**循环引用**。

如果两个对象相互引用，尽管他们已不再使用，垃圾回收不会进行回收，导致内存泄露。

循环引用的例子1：

```js
function f(){
  var o = {};
  var o2 = {};
  o.a = o2; // o 引用 o2
  o2.a = o; // o2 引用 o
  return "azerty";
}

f();
```

上面我们申明了一个函数 f ，其中包含两个相互引用的对象。 在调用函数结束后，对象 o1 和 o2 实际上已离开函数范围，因此不再需要了。 但根据引用计数的原则，他们之间的相互引用依然存在，因此这部分内存不会被回收，内存泄露不可避免了。

循环引用的例子2：

```js
var div = document.createElement("div");
div.onclick = function() {
    console.log("click");
};
```

上面这种 JS 写法再普通不过了，创建一个DOM元素并绑定一个点击事件。 **此时变量 div 有事件处理函数的引用，同时事件处理函数也有div的引用**！（div变量可在函数内被访问）。 一个循序引用出现了，按上面所讲的算法，该部分内存无可避免的泄露了。

为了解决循环引用造成的问题，现代浏览器通过使用**标记清除算法**来实现垃圾回收。

### 算法2: 标记清除算法

标记清除算法将 **“不再使用的对象”** 定义为 **“无法达到的对象”**。 简单来说，就是从根部（在JS中就是全局对象）出发定时扫描内存中的对象。 凡是能从根部到达的对象，都是还需要使用的。 那些无法由根部出发触及到的对象被标记为不再使用，稍后进行回收。

从这个概念可以看出，无法触及的对象包含了没有引用的对象这个概念（没有任何引用的对象也是无法触及的对象）。 但反之未必成立。

工作流程：

1. 垃圾收集器会在运行的时候会给存储在内存中的所有变量都加上标记。
2. 从根部出发将能触及到的对象的标记清除。
3. 那些还存在标记的变量被视为准备删除的变量。
4. 最后垃圾收集器会执行最后一步内存清除的工作，销毁那些带标记的值并回收它们所占用的内存空间。

![img](JavaScript内存管理.assets/16b637393a752456tplv-t2oaga2asx-jj-mark3024000q75.png)

循环引用不再是问题了

再看之前循环引用的例子：

```js
function f(){
  var o = {};
  var o2 = {};
  o.a = o2; // o 引用 o2
  o2.a = o; // o2 引用 o

  return "azerty";
}

f();
```

函数调用返回之后，两个循环引用的对象在垃圾收集时从全局对象出发无法再获取他们的引用。 因此，他们将会被垃圾回收器回收。

## 内存泄漏

### 什么是内存泄漏

程序的运行需要内存。只要程序提出要求，操作系统或者运行时（runtime）就必须供给内存。

对于持续运行的服务进程（daemon），必须及时释放不再用到的内存。 否则，内存占用越来越高，轻则影响系统性能，重则导致进程崩溃。

本质上讲,内存泄漏就是由于疏忽或错误造成程序未能释放那些已经不再使用的内存，造成内存的浪费。

### 内存泄漏的识别方法

经验法则是，如果连续五次垃圾回收之后，内存占用一次比一次大，就有内存泄漏。 这就要求实时查看内存的占用情况。

#### Chrome 浏览器的方法

我们可以这样查看内存占用情况

1. 打开开发者工具，选择 Performance 面板
2. 在顶部勾选 Memory
3. 点击左上角的 record 按钮
4. 在页面上进行各种操作，模拟用户的使用情况
5. 一段时间后，点击对话框的 stop 按钮，面板上就会显示这段时间的内存占用情况

来看一张效果图：

![img](JavaScript内存管理.assets/16b6373703dd6747tplv-t2oaga2asx-jj-mark3024000q75.png)

我们有两种方式来判定当前是否有内存泄漏：

1. 多次快照后，比较每次快照中内存的占用情况，如果呈上升趋势，那么可以认为存在内存泄漏
2. 某次快照后，看当前内存占用的趋势图，如果走势不平稳，呈上升趋势，那么可以认为存在内存泄漏

#### Node 服务器环境的方法

使用 Node 提供的 process.memoryUsage 方法查看内存情况

```js
console.log(process.memoryUsage());
// { 
//     rss: 27709440,
//     heapTotal: 5685248,
//     heapUsed: 3449392,
//     external: 8772 
// }
```

process.memoryUsage返回一个对象，包含了 Node 进程的内存占用信息。

该对象包含四个字段，单位是字节，含义如下:

- rss（resident set size）：所有内存占用，包括指令区和堆栈。
- heapTotal："堆"占用的内存，包括用到的和没用到的。
- heapUsed：用到的堆的部分。
- external： V8 引擎内部的 C++ 对象占用的内存。

判断内存泄漏，以heapUsed字段为准。

### 常见的内存泄露案例

#### 意外的全局变量

```js
function foo() {
    bar1 = 'some text'; // 没有声明变量 实际上是全局变量 => window.bar1
    this.bar2 = 'some text' // 全局变量 => window.bar2
}
foo();
```

在这个例子中，意外的创建了两个全局变量 bar1 和 bar2

#### 被遗忘的定时器和回调函数

在很多库中, 如果使用了观察者模式, 都会提供回调方法, 来调用一些回调函数。 要记得回收这些回调函数。举一个 setInterval的例子：

```js
var serverData = loadData();
setInterval(function() {
    var renderer = document.getElementById('renderer');
    if(renderer) {
        renderer.innerHTML = JSON.stringify(serverData);
    }
}, 5000); // 每 5 秒调用一次
```

如果后续 renderer 元素被移除，整个定时器实际上没有任何作用。 但如果你没有回收定时器，整个定时器依然有效, 不但定时器无法被内存回收， 定时器函数中的依赖也无法回收。在这个案例中的 serverData 也无法被回收。

#### 闭包

在 JS 开发中，我们会经常用到闭包，一个内部函数，有权访问包含其的外部函数中的变量。 下面这种情况下，闭包也会造成内存泄露:

```js
var theThing = null;
var replaceThing = function () {
  var originalThing = theThing;
  var unused = function () {
    if (originalThing) // 对于 'originalThing'的引用
      console.log("hi");
  };
  theThing = {
    longStr: new Array(1000000).join('*'),
    someMethod: function () {
      console.log("message");
    }
  };
};
setInterval(replaceThing, 1000);
```

这段代码，每次调用 replaceThing 时，theThing 获得了包含一个巨大的数组和一个对于新闭包 someMethod 的对象。 同时 unused 是一个引用了 originalThing 的闭包。

这个范例的关键在于，闭包之间是共享作用域的，尽管 unused 可能一直没有被调用，但是 someMethod 可能会被调用，就会导致无法对其内存进行回收。 当这段代码被反复执行时，内存会持续增长。

#### DOM 引用

很多时候, 我们对 Dom 的操作, 会把 Dom 的引用保存在一个数组或者 Map 中。

```js
var elements = {
    image: document.getElementById('image')
};
function doStuff() {
    elements.image.src = 'http://example.com/image_name.png';
}
function removeImage() {
    document.body.removeChild(document.getElementById('image'));
    // 这个时候我们对于 #image 仍然有一个引用, Image 元素, 仍然无法被内存回收.
}
```

上述案例中，即使我们对于 image 元素进行了移除，但是仍然有对 image 元素的引用，依然无法对齐进行内存回收。

另外需要注意的一个点是，对于一个 Dom 树的叶子节点的引用。 举个例子: 如果我们引用了一个表格中的td元素，一旦在 Dom 中删除了整个表格，我们直观的觉得内存回收应该回收除了被引用的 td 外的其他元素。 但是事实上，这个 td 元素是整个表格的一个子元素，并保留对于其父元素的引用。 这就会导致对于整个表格，都无法进行内存回收。所以我们要小心处理对于 Dom 元素的引用。

### 如何避免内存泄漏

记住一个原则：不用的东西，及时归还。

1. 减少不必要的全局变量，使用严格模式避免意外创建全局变量。
2. 在你使用完数据后，及时解除引用（闭包中的变量，dom引用，定时器清除）。
3. 组织好你的逻辑，避免死循环等造成浏览器卡顿，崩溃的问题。

## 参考

- [MDN-内存管理](https://link.juejin.cn?target=https%3A%2F%2Fdeveloper.mozilla.org%2Fzh-CN%2Fdocs%2FWeb%2FJavaScript%2FMemory_Management)
- [JavaScript高级程序设计](https://link.juejin.cn?target=https%3A%2F%2Fbook.douban.com%2Fsubject%2F10546125%2F)
- [JavaScript权威指南](https://link.juejin.cn?target=https%3A%2F%2Fbook.douban.com%2Fsubject%2F10549733%2F)
- [JavaScript 内存泄漏教程](https://link.juejin.cn?target=http%3A%2F%2Fwww.ruanyifeng.com%2Fblog%2F2017%2F04%2Fmemory-leak.html)
- [一种有趣的JavaScript内存泄漏](https://link.juejin.cn?target=https%3A%2F%2Fblog.meteor.com%2Fan-interesting-kind-of-javascript-memory-leak-8b47d2e7f156)

## 系列文章推荐

- [「前端进阶」单页路由解析与实现](https://juejin.cn/post/6844903890278694919)
- [「前端进阶」彻底弄懂函数柯里化](https://juejin.cn/post/6844903882208837645)
- [「前端进阶」JS中的栈内存堆内存](https://juejin.cn/post/6844903873992196110)
- [「前端进阶」数组乱序](https://juejin.cn/post/6844903863812620296)



















































