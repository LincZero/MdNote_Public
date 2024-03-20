# Flask

# 目录

## 2.浏览器能识别的标签



### 2.1 编码（head）

```html
<meta charset="UTF-8">
```



### 2.2 title（head）

```html
<head>
    <meta charset="UTF-8">
    <title>我的联通</title>
</head>
```

![image-20211119091846208](day11 前端开发.assets/image-20211119091846208.png)



### 2.3 标题

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>我的联通</title>
</head>
<body>
    <h1>1级标题</h1>
    <h2>2级标题</h2>
    <h3>3级标题</h3>
    <h4>4级标题</h4>
    <h5>5级标题</h5>
    <h6>6级标题</h6>
</body>
</html>
```



### 2.4 div和span

```html
<div>内容</div>

<span>asdfa</span>
```

- div，一个人占一整行。【块级标签】

  ```html
  <!DOCTYPE html>
  <html lang="en">
  <head>
      <meta charset="UTF-8">
      <title>我的联通</title>
  </head>
  <body>
      <div>山东蓝翔</div>
      <div>挖掘机哪家强</div>
  </body>
  </html>
  ```

- span，自己多大占多少。【行内标签、内联标签】

  ```html
  <!DOCTYPE html>
  <html lang="en">
  <head>
      <meta charset="UTF-8">
      <title>我的联通</title>
  </head>
  <body>
      <span>山东蓝翔</span>
      <span>挖掘机哪家强</span>
  </body>
  </html>
  
  ```

  

注意：这两个标签比较素 + CSS样式。



### 练习题

![image-20211119093603188](day11 前端开发.assets/image-20211119093603188.png)



### 2.4.5 超链接

```html
跳转到其他网站
<a href="http://www.chinaunicom.com.cn/about/about.html">点击跳转</a>
```

```html
跳转到自己网站其他的地址

<a href="http://127.0.0.1:5000/get/news">点击跳转</a>
<a href="/get/news">点击跳转</a>
```



```html
# 当前页面打开
<a href="/get/news">点击跳转</a>

# 新的Tab页面打开
<a href="/get/news" target="_blank">点击跳转</a>
```





### 2.4.6 图片

```html
<img src="图片地址" />
```

```html
直接显示别人的图片地址（防盗链）：
<img src="https://pic4.zhimg.com/v2-b23f984c2aeaa7bed12e890b4338d499_720w.jpg" />
```

```html
<img src="自己图片的地址" />
显示自己的图片：
	- 自己项目中创建：static目录，图片要放在static
	- 在页面上引入图片
	    <img src="/static/wbq.png" />
```

关于设置图片的高度和宽度

```html
<img src="图片地址" style="height:100px; width:200px;" />
<img src="图片地址" style="height:10%; width:20%;" />
```



### 小结

- 学习的标签

  ```html
  <h1></h1>
  <div></div>
  <span></span>
  <a></a>
  <img />
  ```

- 划分

  ```
  - 块级标签
  	<h1></h1>
  	<div></div>
  - 行内标签
  	<span></span>
      <a></a>
      <img />
  ```

- 嵌套

  ```html
  <div>
      <span>xxx</span>
      <img />
      <a></a>
  </div>
  ```

  

案例：商品列表

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<h1>商品列表</h1>

<a href="https://www.mi.com/redmiwatch2" target="_blank">
    <img src="/static/a1.jpeg" style="width: 150px">
</a>

<a href="https://www.mi.com/shouhuan6/nfc" target="_blank">
    <img src="/static/a2.jpeg" style="width: 150px">
</a>

<a href="https://www.mi.com/xiaomibuds3pro" target="_blank">
    <img src="/static/a3.jpeg" style="width: 150px">
</a>

</body>
</html>
```



### 2.4.7 列表

```html
<ul>
    <li>中国移动</li>
    <li>中国联通</li>
    <li>中国电信</li>
</ul>
```

```html
<ol>
    <li>中国移动</li>
    <li>中国联通</li>
    <li>中国电信</li>
</ol>
```

![image-20211119104421373](day11 前端开发.assets/image-20211119104421373.png)

### 2.4.8 表格

```html
<table>
    <thead>
    	<tr>  <th>ID</th>  <th>姓名</th>   <th>年龄</th>  </tr>
    </thead>
    <tbody>
    	<tr>  <td>10</td>  <td>武沛齐</td>  <td>19</td>   </tr>
        <tr>  <td>11</td>  <td>吴阳军</td>  <td>19</td>   </tr>
        <tr>  <td>12</td>  <td>刘东</td>  <td>19</td>    </tr>
        <tr>  <td>13</td>  <td>郭智</td>  <td>19</td>    </tr>
        <tr>  <td>14</td>  <td>电摩</td>  <td>19</td>    </tr>
    </tbody>
</table>
```



### 案例

![image-20211119112204753](day11 前端开发.assets/image-20211119112204753.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
    <h1>用户列表</h1>
    <table border="1">
        <thead>
            <tr>
                <th>ID</th>
                <th>头像</th>
                <th>姓名</th>
                <th>邮箱</th>
                <th>更多信息</th>
                <th>操作</th>
            </tr>
        </thead>

        <tbody>
            <tr>
                <td>1</td>
                <td>
                    <img src="/static/a1.jpeg" alt="" style="height: 50px">
                </td>
                <td>武沛齐</td>
                <td>休息@live.com</td>
                <td>
                    <a href="http://www.chinaunicom.com.cn/about/leaders.html" target="_blank">查看详细</a>
                </td>
                <td>
                    编辑
                    删除
                </td>
            </tr>

             <tr>
                <td>1</td>
                <td>
                    <img src="/static/a1.jpeg" alt="" style="height: 50px">
                </td>
                <td>武沛齐</td>
                <td>休息@live.com</td>
                <td>
                    <a href="http://www.chinaunicom.com.cn/about/leaders.html" target="_blank">查看详细</a>
                </td>
                 <td>
                    编辑
                    删除
                </td>
            </tr>

             <tr>
                <td>1</td>
                <td>
                    <img src="/static/a1.jpeg" alt="" style="height: 50px">
                </td>
                <td>武沛齐</td>
                <td>休息@live.com</td>
                <td>
                    <a href="http://www.chinaunicom.com.cn/about/leaders.html" target="_blank">查看详细</a>
                </td>
                 <td>
                    编辑
                    删除
                </td>
            </tr>

             <tr>
                <td>1</td>
                <td>
                    <img src="/static/a1.jpeg" alt="" style="height: 50px">
                </td>
                <td>武沛齐</td>
                <td>休息@live.com</td>
                <td>
                    <a href="http://www.chinaunicom.com.cn/about/leaders.html" target="_blank">查看详细</a>
                </td>
                 <td>
                    编辑
                    删除
                </td>
            </tr>
        </tbody>
    </table>
</body>
</html>
```



### 2.4.9 input系列（7个）

```html
<input type="text" />
<input type="password">    
<input type="file"> 

<input type="radio" name="n1">男
<input type="radio" name="n1">女

<input type="checkbox">篮球
<input type="checkbox">足球
<input type="checkbox">乒乓球
<input type="checkbox">棒球

<input type="button" value="提交">  -->普通的按钮
<input type="submit" value="提交">  -->提交表单
```



### 2.4.10 下拉框

```html
<select>
    <option>北京</option>
    <option>上海</option>
    <option>深圳</option>
</select>

<select multiple>
    <option>北京</option>
    <option>上海</option>
    <option>深圳</option>
</select>
```



### 2.4.11 多行文本

```html
<textarea></textarea>
```



### 案例：用户注册

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>


<h1>用户注册</h1>
<div>
    用户名：<input type="text"/>
</div>
<div>
    密码：<input type="password"/>
</div>

<div>
    性别：
    <input type="radio">男
    <input type="radio">女
</div>

<div>
    爱好：
    <input type="checkbox">篮球
    <input type="checkbox">足球
    <input type="checkbox">乒乓球
</div>

<div>
    城市：
    <select>
        <option>北京</option>
        <option>上海</option>
        <option>深圳</option>
    </select>
</div>

<div>
    擅长领域：
    <select multiple>
        <option>打游戏</option>
        <option>睡觉</option>
        <option>吃饭</option>
        <option>刷抖音</option>
    </select>
</div>

<div>
    备注：<textarea></textarea>
</div>

<div>
    <input type="button" value="button按钮">
    <input type="submit" value="submit按钮">
</div>
</body>
</html>
```



### 知识点回顾和补充

1. 网站请求的流程
   ![image-20211119140524753](day11 前端开发.assets/image-20211119140524753.png)

2. 一大堆的标签

   ```
   h/div/span/a/img/ul/li/table/input/textarea/select
   ```

3. 网络请求

   - 在浏览器的URL中写入地址，点击回车，访问。

     ```
     浏览器会发送数据过去，本质上发送的是字符串：
     "GET /explore http1.1\r\nhost:...\r\nuser-agent\r\n..\r\n\r\n"
     
     浏览器会发送数据过去，本质上发送的是字符串：
     "POST /explore http1.1\r\nhost:...\r\nuser-agent\r\n..\r\n\r\n数据库"
     ```

   - 浏览器向后端发送请求时

     - GET请求【URL方法 / 表单提交】

       - 现象：GET请求、跳转、向后台传入数据数据会拼接在URL上。

         ```
         https://www.sogou.com/web?query=安卓&age=19&name=xx
         ```

         注意：GET请求数据会在URL中体现。

     - POST请求【表单提交】

       - 现象：提交数据不在URL中而是在请求体中。







### 案例：用户注册

- 新创建项目

- 创建Flask代码

  ```python
  from flask import Flask, render_template, request
  
  app = Flask(__name__)
  
  
  @app.route('/register', methods=['GET', "POST"])
  def register():
      if request.method == "GET":
          return render_template('register.html')
  
      else:
          user = request.form.get("user")
          pwd = request.form.get("pwd")
          gender = request.form.get("gender")
          hobby_list = request.form.getlist("hobby")
          city = request.form.get("city")
          skill_list = request.form.getlist("skill")
          more = request.form.get("more")
          print(user, pwd, gender, hobby_list, city, skill_list, more)
          # 将用户信息写入文件中实现注册、写入到excel中实现注册、写入数据库中实现注册
  
          # 2.给用户再返回结果
          return "注册成功"
  
  
  if __name__ == '__main__':
      app.run()
  
  ```

- HTML代码

  ```html
  <!DOCTYPE html>
  <html lang="en">
  <head>
      <meta charset="UTF-8">
      <title>Title</title>
  </head>
  <body>
  <h1>用户注册</h1>
  
  <form method="post" action="/register">
      <div>
          用户名：<input type="text" name="user"/>
      </div>
      <div>
          密码：<input type="password" name="pwd"/>
      </div>
      <div>
          性别：
          <input type="radio" name="gender" value="1">男
          <input type="radio" name="gender" value="2">女
      </div>
      <div>
          爱好：
          <input type="checkbox" name="hobby" value="10">篮球
          <input type="checkbox" name="hobby" value="20">足球
          <input type="checkbox" name="hobby" value="30">乒乓球
          <input type="checkbox" name="hobby" value="40">棒球
      </div>
  
      <div>
          城市：
          <select name="city">
              <option value="bj">北京</option>
              <option value="sh">上海</option>
              <option value="sz">深圳</option>
          </select>
      </div>
  
      <div>
          擅长领域：
          <select name="skill" multiple>
              <option value="100">吃饭</option>
              <option value="101">睡觉</option>
              <option value="102">打球</option>
          </select>
      </div>
  
      <div>
          备注：<textarea name="more"></textarea>
      </div>
  
      <input type="submit" value="submit按钮">
  </form>
  
  </body>
  </html>
  
  ```

  



### 案例：登录()

见代码示例。





页面上的数据，想要提交到后台：

- form标签包裹要提交的数据的标签。
  - 提交方式：`method="get"`
  - 提交的地址：`action="/xxx/xxx/xx"`
  - 在form标签里面必须有一个submit标签。
- 在form里面的一些标签：input/select/textarea
  - 一定要写name属性 `<input type="text" name="uu"/>`





### 总结

1. 称呼

   ```
   - 浏览器能够识别的标签（不专业）
   - HTML标签。
   
   什么是是HTML？超文本传输语言（与浏览器搭配）。
   ```

2. HTML标签（默认格式样式、以后通过手段可以修改）

3. HTML标签与编程语言无关

   - java + HTML
   - c# + HTML
   - php + HTML
   - python + HTML

4. 提醒：HTML标签比较多，标签还有很多很多，不必逐一学会。



































