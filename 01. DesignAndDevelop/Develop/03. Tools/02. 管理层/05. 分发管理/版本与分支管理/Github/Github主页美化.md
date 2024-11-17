# Github主页美化

## github.io网站模板

参考：https://blog.csdn.net/qd1813100174/article/details/128604858



比如你可以在 [Jekyll Themes](http://jekyllthemes.org/) 中找到很多美丽的模板。

但是我们这里着重细致地教一个简单的，如果你对模板没什么特殊的偏好并且不太想大费周章，这篇文章将会很好地满足你的需求



例如：点击网址 https://github.com/academicpages/academicpages.github.io  这个就是我们即将使用的模板

## Github首页模板

### 方法

首先在 GitHub 上建立一个与自己 GitHub 账户同名的仓库，勾选 README

创建仓库后可以看到 readme文件，可修改

### 模板

- https://github.com/kautukkundan/Awesome-Profile-README-templates

  这个仓库收集了很多有创意的README 模板，我们可以参考着自己修改

  使用指引：里面有一层文件夹分类，再往下就是非常非常多的 `.md` ，每个md文件都是一个模板

  例如：https://github.com/kautukkundan/Awesome-Profile-README-templates/blob/master/elaborate/JoeyBling.md

### 记录一些优秀片段

图标链接

```html
[![Github](https://img.shields.io/badge/-Github-000?style=flat&logo=Github&logoColor=white)](https://github.com/FernandoRoldan93)
[![Linkedin](https://img.shields.io/badge/-LinkedIn-blue?style=flat&logo=Linkedin&logoColor=white)](https://www.linkedin.com/in/froldanzafra/)
[![Gmail](https://img.shields.io/badge/-Gmail-c14438?style=flat&logo=Gmail&logoColor=white)](mailto:Fernando.Roldan.Zafra@gmail.com)
```

语言图标链接

```html
#### Software:

![Python](http://img.shields.io/badge/-Python-3776AB?style=flat-square&logo=python&logoColor=ffff4a)
![Ruby](http://img.shields.io/badge/-Ruby-CC342D?style=flat-square&logo=ruby&logoColor=ffe8e8)
![Java](http://img.shields.io/badge/-Java-007396?style=flat-square&logo=java&logoColor=ffffff)
![Spring](http://img.shields.io/badge/-Spring-6DB33F?style=flat-square&logo=spring&logoColor=ffffff)

#### Front-end:

![Sass](https://img.shields.io/badge/-Sass-%23CC6699?style=flat-square&logo=sass&logoColor=ffffff)
![JavaScript](https://img.shields.io/badge/-JavaScript-%23F7DF1C?style=flat-square&logo=javascript&logoColor=000000&color=d1b01f)
![Nodejs](https://img.shields.io/badge/-Nodejs-black?style=flat-square&logo=Node.js&logoColor=00d632)
![React](https://img.shields.io/badge/-React-%23282C34?style=flat-square&logo=react)
![Rails](http://img.shields.io/badge/-Ruby%20on%20Rails-CC0000?style=flat-square&logo=ruby-on-rails&logoColor=ffffff)
![Jekyll](http://img.shields.io/badge/-Jekyll-CC0000?style=flat-square&logo=jekyll&logoColor=ffffff)


#### Back-end:

![Redis](https://img.shields.io/badge/-Redis-DC382D?style=flat-square&logo=redis&logoColor=ffffff)
![PostgreSQL](https://img.shields.io/badge/-PostgreSQL-336791?style=flat-square&logo=postgresql)
![GraphQL](https://img.shields.io/badge/-GraphQL-E10098?style=flat-square&logo=graphql&logoColor=ffffff)
![Heroku](https://img.shields.io/badge/-Heroku-430098?style=flat-square&logo=heroku&logoColor=ffffff)
![Docker](https://img.shields.io/badge/-Docker-black?style=flat-square&logo=docker)
![NGINX](http://img.shields.io/badge/-NGINX-269539?style=flat-square&logo=nginx&logoColor=ffffff)


#### Editors and Operating Systems:

![IntelliJ IDEA](http://img.shields.io/badge/-IntelliJ%20IDEA-000000?style=flat-square&logo=intellij-idea&logoColor=ffffff)
![VS Code](http://img.shields.io/badge/-VS%20Code-007ACC?style=flat-square&logo=visual-studio-code&logoColor=ffffff)
![LaTeX](http://img.shields.io/badge/-LaTeX-008080?style=flat-square&logo=latex&logoColor=ffffff)
![Debian](http://img.shields.io/badge/-Debian-A81D33?style=flat-square&logo=debian&logoColor=ffffff)
![FreeBSD](http://img.shields.io/badge/-Free%20BSD-AB2B28?style=flat-square&logo=freebsd&logoColor=ffffff)
![GNU Emacs](http://img.shields.io/badge/-GNU%20Emacs-7F5AB6?style=flat-square&logo=gnu-emacs&logoColor=ffffff)
![GNU Bash](http://img.shields.io/badge/-GNU%20Bash-000000?style=flat-square&logo=gnu-bash&logoColor=ffffff)

另一种写法：

<code><img width="10%" src="https://www.vectorlogo.zone/logos/python/python-ar21.svg"></code>
<code><img width="10%" src="https://www.vectorlogo.zone/logos/numpy/numpy-ar21.svg"></code>
<code><img width="10%" src="https://www.vectorlogo.zone/logos/pytorch/pytorch-ar21.svg"></code>
<br />
<code><img width="10%" src="https://www.vectorlogo.zone/logos/tensorflow/tensorflow-ar21.svg"></code>
<code><img width="10%" src="https://www.vectorlogo.zone/logos/jupyter/jupyter-ar21.svg"></code>
<code><img width="10%" src="https://www.vectorlogo.zone/logos/json/json-ar21.svg"></code>
<br />
<code><img width="10%" src="https://www.vectorlogo.zone/logos/mysql/mysql-ar21.svg"></code>
<code><img width="10%" src="https://www.vectorlogo.zone/logos/google_cloud/google_cloud-ar21.svg"></code>
<code><img width="10%" src="https://www.vectorlogo.zone/logos/docker/docker-ar21.svg"></code>
<br />
<code><img width="10%" src="https://www.vectorlogo.zone/logos/git-scm/git-scm-ar21.svg"></code>
<code><img width="10%" src="https://www.vectorlogo.zone/logos/github/github-ar21.svg"></code>
<code><img width="10%" src="https://www.vectorlogo.zone/logos/visualstudio_code/visualstudio_code-ar21.svg"></code>
```

居右图片

```html
<img align="right" alt="GIF" src="https://raw.githubusercontent.com/JoeyBling/JoeyBling/master/pic/pusheencode.gif" />
```

Github Star统计

```html
<img width="50%" align="right" src="https://github-readme-stats.vercel.app/api?username=FernandoRoldan93&show_icons=true&hide_border=true" />

也可是是黑色的
![Hrishikesh's github stats](https://github-readme-stats.vercel.app/api/?username=hrishikesh-coder&show_icons=true&title_color=fff&icon_color=79ff97&text_color=9f9f9f&bg_color=151515)
```

语言统计（这些的显示效果有些区别，不是官方的，是第三方爬虫）

```html
[![Top Langs](https://github-readme-stats.vercel.app/api/top-langs/?username=TamimEhsan)](https://github.com/anuraghazra/github-readme-stats)

<img alt="Jha-Vineet69's Top Languages Stats" src="https://github-readme-stats.vercel.app/api/top-langs/?username=jha-vineet69&hide=smalltalk&theme=buefy&layout=compact&hide_border=true" width="500"/>

  [![Top Langs](https://github-readme-stats.vercel.app/api/top-langs/?username=sachinchaturvedi93&hide=jupyter%20notebook&show_icons=true&layout=compact&hide_border=true)](https://github.com/anuraghazra/github-readme-stats)
```

项目卡片

```html
[![ReadMe Card](https://github-readme-stats.vercel.app/api/pin/?username=ShanjinurIslam&repo=BUET-CSE-Moodle-Web-Scraping&show_owner=true)](https://github.com/ShanjinurIslam/BUET-CSE-Moodle-Web-Scraping) <br />
```

Buy me a coffe（别人的片段，不是我的，请勿付款）

```html
<div align="center"><img width="300" src="https://ghproxy.com/https://raw.githubusercontent.com/cumany/cumany/main/pic/202209192228895.png" />
</div>

<div align="center"><a href="https://www.buymeacoffee.com/Cuman"><img src="https://img.buymeacoffee.com/button-api/?text=Buy me a coffee &emoji=&slug=Cuman&button_colour=BD5FFF&font_colour=ffffff&font_family=Poppins&outline_colour=000000&coffee_colour=FFDD00" /></a>
</div>
```

### 除README外的配置项

除了 README.md，还有一些其他的配置项

### Github标签 (常用于在github外显示github信息)

```js
// 赞助
[![Sponsor me](https://img.shields.io/badge/%E2%9D%A4%20Like%20this%20plugin%3F-Sponsor%20me!-ff69b4)](https://github.com/sponsors/scambier)  

// 下载量
![Obsidian plugin](https://img.shields.io/endpoint?url=https%3A%2F%2Fscambier.xyz%2Fobsidian-endpoints%2Fomnisearch.json)
// 这里如果没转义，对应：https://scambier.xyz/obsidian-endpoints/omnisearch.json
// 改成自己的：
// ![Obsidian plugin](https://img.shields.io/endpoint?url=https%3A%2F%2Fscambier.xyz%2Fobsidian-endpoints%2Fany-block.json)

// 最近下载量
![GitHub release (latest by date and asset)](https://img.shields.io/github/downloads/scambier/obsidian-omnisearch/latest/main.js)  

// 版本
![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/scambier/obsidian-omnisearch)

// beta版本
![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/scambier/obsidian-omnisearch?include_prereleases&label=BRAT%20beta)
```

案例：
AnyBlock：![Obsidian plugin](https://img.shields.io/endpoint?url=https%3A%2F%2Fscambier.xyz%2Fobsidian-endpoints%2Fany-block.json) ![GitHub release (latest by date and asset)](https://img.shields.io/github/downloads/LincZero/obsidian-any-block/latest/main.js) ![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/LincZero/obsidian-any-block)
NodeFlow：AnyBlock：![Obsidian plugin](https://img.shields.io/endpoint?url=https%3A%2F%2Fscambier.xyz%2Fobsidian-endpoints%2FNodeFlow.json) ![GitHub release (latest by date and asset)](https://img.shields.io/github/downloads/LincZero/obsidian-node-flow/latest/main.js) ![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/LincZero/obsidian-node-flow)





