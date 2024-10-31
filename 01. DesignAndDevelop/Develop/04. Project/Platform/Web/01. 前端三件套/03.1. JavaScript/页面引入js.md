---
last_time: 2020.01.19
tag: 有道云
---

# 页面引入js

**在页面中引入js有两种基本方式：在页面中嵌入js、引用外部js文件。**

## 在页面中嵌入js

这是在页面使用js最简单的方式了，一般我在写个小测试的情况下会用这种方式。

把script元素写在前面，script元素的内容就是js代码。

## 引用外部js文件

引用外部js文件，可以使js文件和HTML文件相分离、一个js文件可被多个HTML文件使用、维护起来也更方便等等。

用法是把script元素的src属性，设置为js文件的URL即可，

## script元素在HTML文件中的位置

如果把script元素放在head元素里，就像这样：

这样做的话，待浏览器经过下载、解析、执行完js文件之后，才会呈现页面内容。如果一个页面需要很多个js文件，那么浏览器可能会出现短暂的“白板”，用户体验不好。

所以，我们应该把js文件放在的前面，这样浏览器会先展现页面给用户。

## 在js中通过html插入js(原贴上新加)

   var script=document.createElement("script");

​    script.type="text/javascript";

​    script.src="js/translate.js";

​    document.getElementsByTagName('head')[0].appendChild(script);