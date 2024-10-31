# Mozilla版Firefox下载方法

## 【先看】两版本冲突问题、覆盖安装问题

参考：https://blog.littlefox.me/archives/233

据说是不能覆盖安装的，可能会有bug。而不覆盖安装会有另一个问题：书签、插件、密码等，几本所有的东西都无法同步。
也可以理解为：国内和国际版的Firefox就tmd不是同一个浏览器

所以在这里我的方法是：不同步了，东西太多。保留手机上的国际版Firefox，要查东西就用手机查（但手机上访问网站可能会被墙就很烦……不过基本不会用手机去浏览很多的网站，如有必要就用Chrome）

## 下载国际版Firefox (电脑)

这个还是有点难度的，单纯上外网无法下载。

参考：https://blog.littlefox.me/archives/233

去 [官网](https://www.mozilla.org/zh-CN/firefox/) 或者 [ftp](https://ftp.mozilla.org/pub/firefox/releases/)，注意域名一定要是mozilla.org，但是直接访问mozilla.org不行的，会跳转到特供版。或者用PowerShell命令（感谢评论区@yogaskung）：

```bash
Invoke-WebRequest -o ./ff-installer.exe 'https://download.mozilla.org/?product=firefox-latest&os=win64&lang=zh-CN'
./ff-installer.exe
```

使用winget的同学，正确授权的winget下载的版本是Mozilla中文版，可以直接使用

```bash
winget install firefox
```

## 手机版

略，为了有时从手机拿国内版浏览器保存的书签数据或密码，就先不装了

