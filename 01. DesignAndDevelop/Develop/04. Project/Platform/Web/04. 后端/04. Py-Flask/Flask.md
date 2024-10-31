# Flask

day11 前端开发

```
目的：开发一个平台（网站）
	- 前端开发：HTML、CSS、JavaScript
	- Web框架：接收请求并处理
	- MySQL数据库：存储数据地方

快速上手：
	基于Flask Web框架让你快速搭建一个网站出来。
	
深入学习：
	基于Django框架（主要）
```

## Flask安装

```
pip install flask
```

默认模板项目

```python
from flask import Flask

app = Flask(__name__)


# 创建了网址 /show/info 和 函数index 的对应关系
# 以后用户在浏览器上访问 /show/info，网站自动执行 index
@app.route("/show/info")
def index():
    return "中国联通"


if __name__ == '__main__':
    app.run()
```

## 运行

直接运行，然后终端会给你一个网站

## 表单处理

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

## 其他

咱们网站与别人的不一样：

- 别人的好看 vs 咱们的难堪。

  ```
  浏览器可以识别很多标签+数据，例如：
  	<h1>中国</h1>   						->  浏览器看见加大加粗
  	<span style='color:red;'>联通</span>  ->  浏览器看见字体变红色
  	
  如果我们能把浏览器能识别的所有的标签都学会，我们在网站就可以控制页面到底长什么样子。
  ```

- Flask框架为了让咱们写标签方便，支持将字符串写入到文件里。

- ```python
  from flask import Flask,render_template
  
  app = Flask(__name__)
  
  @app.route("/show/info")
  def index():
      # Flask内部会自动打开这个文件，并读取内容，将内容给用户返回。
      # 默认：去当前项目目录的templates文件夹中找。
      return render_template("index.html")
  
  if __name__ == '__main__':
      app.run()
  ```

