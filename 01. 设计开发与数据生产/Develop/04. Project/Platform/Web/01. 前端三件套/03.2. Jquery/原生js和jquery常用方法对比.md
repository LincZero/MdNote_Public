---
last_time: 2020.01.10
tag: 有道云
---

# 原生js和jquery常用方法对比

## 元素获取

```js
/*******************原生js**************************/
var ele = document.getElementById('idName');
var eleArr = document.getElementsByClassName('className');
var eleArr = document.getElementsByTagName('div');
var ele = document.querySelector('#idName');//('.className')//('tagName'); //取第一个满足条件的元素
var eleArr = document.querySelectorAll('.className');//('tagName');

/*******************jQuery**************************/
var ele = $('#idName');
var ele = $('.className:eq(0)'); //取第一个元素
var eleArr = $('tagName');
```

## class选择器操作

```js
/*******************原生js**************************/
//className 属性
ele.className = 'newClassName';
//classList操作
ele.classList.contains('className'); //受否有该类
ele.classList.add('newClassName1,newClassName2...'); //添加类
ele.classList.remove('oldClassName1,newClassName2...'); //删除类
ele.classList.toggle('className'); //如果元素中有该className，则删除并返回false，否则添加并返回true

/*******************jQuery**************************/
ele.hasClass(className);
ele.addClass('newClassName1,newClassName2...');
ele.removeClass('newClassName1,newClassName2...');
ele.toggleClass('className');
```

## 元素节点操作

```js
/*******************原生js**************************/
//创建节点
    var newNode = ele.createElement('<div>创建</div>');
//插入节点
    ele.appendChild(newNode); //在ele的子节点的末尾插入newNode
    ele.insertBefore(newNode,targetNode); //在ele的子节点targetNode前面插入newNode
//删除节点
    ele.removeChild(ele.childNodes[i]); //删除ele第i+1个子节点
//替换节点
    ele.replaceChild(newNode, oldNode); //替换ele中的子节点
//克隆节点
    var copyNode = ele.cloneNode(deep); //deep为true时，深拷贝（包括其子孙节点），为false时只复制本身节点

/*******************jQuery**************************/
//创建节点
    var newNode = $('<div>创建</div>');
//插入节点
    //在元素子节点末尾插入
    ele.append(newNode); //在ele的子节点的末尾插入newNode
    newNode.appendTo(ele); //在ele的子节点的末尾插入newNode
    //在元素子节点前端插入
    ele.prepend(newNode); //在ele的子节点的前端插入newNode
    newNode.prependTo(ele); //在ele的子节点的前端插入newNode

    //在元素后面添加
    ele.after(newNode);
    newNode.insertAfter(ele);
    //在元素前面添加
    ele.before(newNode);
    newNode.insertBefore(ele);

//删除节点
    ele.remove(); //移除ele及其所有文本、子孙节点、数据和事件
    ele.detach(); //移除ele及其所有文本、子孙节点，但是保留数据和事件
    ele.empty(); //清除ele所有的内容和子孙元素，但是ele节点本身和其属性事件等还在

//替换节点
    ele.replaceWith(newNode); //替换ele为新的内容(可以是html元素，dom元素，jQuery元素)
    newNode.replaceAll(ele); //替换ele为新的html元素
//克隆节点
    ele.clone(deep); //deep为true时，深拷贝（包括其事件处理函数），为false时只复制本身，默认false
```

## 元素节点遍历

```js
/*******************原生js**************************/
// 子节点
var eleArr = ele.childNodes; // 所有子节点
var eleArr = ele.children; //所有子节点数组，用得较多

var firstEle = ele.firstChild; //第一个子节点 低版本浏览器firstElementChild
var lastEle = ele.lastChild; //最后一个子节点 低版本浏览器lastElementChild
// 父节点
var parentEle = ele.parentNode;
// 兄弟节点
var nextEle = ele.nextSibling; //下一个节点
var previousEle = ele.previousSibling; //上一个节点

/*******************jQuery**************************/
// 子节点
var eleArr = ele.children(); //所有子节点数组

var firstEle = ele.first(); //第一个子节点
var lastEle = ele.last(); //最后一个子节点
// 父节点
var parentEle = ele.parent(); //直接父元素
var parentEleArr = ele.parents(); //所有祖先元素
var parentEle = ele.offsetParent(); // 第一个有定位的父元素
var parentEleArr = ele.parentsUntil(stop, filter); // 满足条件之间的父节点

// 兄弟节点
var nextEle = ele.next(); //下一个节点
var nextEleArr = ele.nextAll(); //ele后面所有同级节点
var previousEle = ele.prev(); //上一个节点
var previousEle = ele.prevAll(); //ele之前所有同级节点
var siblingsArr = ele.siblings(); //所有同级元素节点
```

## 属性操作

```js
/*******************原生js**************************/
// 属性数组
var attrArr = ele.attributes;
// 判断属性
var bool = ele.hasAttribute('attrName'); //是否有指定属性
var bool = ele.hasAttributes(); //是否有属性
// 获取属性值
var attrValue = ele.getAttribute('attrName');
// 设置属性值
ele.setAttribute('attrName','attrValue');
// 删除属性
ele.removeAttribute('attrName');

/*******************jQuery**************************/
//在设置disabled、selected、checked等这些Boolean类型自带属性时，我们需要用prop()方法；
// 其他字符串类型自带属性时，我们使用attr()方法即可;DOM节点可见的自定义属性我们也使用attr()方法。
// 获取属性值
var attrValue = ele.attr('attrName');
var propValue = ele.prop('propName');//
// 设置属性值
ele.attr('attrName','attrValue'); //自定义的一些属性
ele.prop('propName','propValue'); //disabled等一些属性，HTML元素的固有属性
// 删除属性
ele.removeAttr('attrName');
```

## 事件

```js
/*******************原生js**************************/
//事件绑定及解绑
ele.addEventListener('click',func,false);
ele.removeEventListener('click',func,false);
ele.onclick = func;
ele.onclick = null;
ele.attachEvent('onclick',func); //ie8以下
ele.detachEvent('onclick',func); //ie8以下

/*******************jQuery**************************/
/*多种事件绑定和解绑方法*/
/**方法1
 * 1、直接绑定事件方法mouseenter()...等等
 * 2、这样的方式，下面两个事件不会被层叠，都会执行
 * 3、只能一个一个绑定
 */
$("div:eq(0)").click(function () {
    alert(1);
});
$("div:eq(0)").click(function () {
    alert(2);
});

/**方法2
 * 1、bind("event1 event2 ... eventx",fn)
 * 2、同时绑定多个事件触发条件，执行同一个函数
 */
$("div:eq(1)").bind("click mouseenter",function () {
    alert("bind绑定法");
});
//解绑
$("div:eq(1)").unbind("click"); //解绑指定的
//$("div:eq(1)").unbind();  //解绑所有的

/**方法3
 * 1、delegate("selector","event1 event2 ... eventx",fn)
 * 2、可以绑定父盒子里的子盒子触发事件，执行函数
 */
$("div:eq(2)").delegate("button","click mouseleave",function () {
    alert("delegate绑定法");
});
//解绑
$("div:eq(2)").undelegate();
/**方法4
 * 重点使用！！！
 * 1、on("event1 event2 ... eventx","selector",data,fn)
 * 2、可以绑定父盒子里的后代盒子触发事件，执行函数
 * 3、参数data由event.data带入函数中
 */

$("div:eq(3)").on("click mouseleave","button",{"name":"mjm","age":24},function (event) {
    alert("on绑定法"+event.data.name);

});
//解绑
$("div:eq(3)").off();
```

