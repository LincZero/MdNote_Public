## 安装 酷Q on Docker

1.下载 酷Q Docker 镜像：

```bash
docker pull coolq/wine-coolq
```

2.创建一个文件夹，用来存放 酷Q 数据：

```bash
mkdir
```

3.运行 酷Q：

```bash
docker run --name=coolq -d\
 -p 8080:9000\
 -v /root/coolq-data:/home/user/coolq\
 -e VNC_PASSWD=jtdvfuQ000...\
 -e COOLQ_ACCOUNT=13822440721\
 coolq/wine-coolq
```

这个命令里有几个参数，可以自定义：

-   参数含义,  参数示例
-   远程监听端口,  8080
-   数据存放位置,  /root/coolq-data
-   远程访问密码,  12345678
-   机器人账号,  123456

## 管理酷Q

常用命令

```bash
# 查看运行日志
docker logs coolq
 
# 启动/停止服务
docker start coolq
docker stop coolq
```

酷Q 有很丰富的第三方应用，免费的收费的都有，可以非常方便的实现各种功能，可以在 [酷Q社区](https://link.zhihu.com/?target=https%3A//laowangblog.com/go/%3Furl%3Dhttps%3A//cqp.cc/b/app) 自行下载。

下载会得到一个 cpk 文件，只需要把这个文件拷贝到刚才的 /root/coolq-data 文件夹中的 app 目录下即可，之后加载应用即可，很方便。













