# Docker

参考：https://www.bilibili.com/video/BV1s54y1n7Ev

docker的出现，让应用环境的配置、发布、测试变得轻松

像 Kubernetes (k8s)、Docker Swarm、Podman 等都与Docker有关

课程介绍Docker基本概念、安装、使用，以及如何用 docker compose 来同时管理多个容器

## 介绍

### 解决什么问题？

本地调试没问题，那么需要给云服务器一个相同的环境（比如Linux发行版不同、或同一个发行版的小版本不同）

模拟完全相同本地环境，Windows通常会用虚拟机（VMware、VirtualBox、Hyper-V、QEMU），但较臃肿且性能不高

Docker在概念上相当于虚拟机，但更轻量。提供隔离的环境

（介于虚拟机和沙盒 Sandbox 之间？anaconda？java？）

### 概念

三个概念

- Dockerfile
- Image / 镜像
  - 理解成虚拟机的快照（Snapshot），包含要部署的应用程序和相关库
  Docker Hub 上也提供了很多高质量的操作系统镜像
- Container / 容器
  - 镜像可以创建多个不同的容器（通过Dockerfile完成），每个容器都是独立运行
    类比于多个虚拟机使用同一个镜像去创建，类比于多个实例使用一个类来创建

### 安装

#### Windows/Mac

官网下载 `Docker Desktop` 的应用。
这个图形化界面可以查看应用在后台的所有输出以便调试，同时也可以看到一些状态（cpu内存等）
以及可以图形化管理所有创建的容器。

Windows 10 以上也可以使用 WSL2 子系统来运行

#### Linux

使用包管理工具

按官网一步一步按



不同的Linux操作系统有不同的包管理工具

- Ubuntu：apt
- Fedora：dnf

也有针对于不同语言的包管理工具

- nginx
- redis
- node
- python
- tomcat

#### VSCode插件

提供Dockerfile的语法检测和补全

### 部署

这里是一个python flash的自动记账的demo：

应用的根目录创建一个 `Dockerfile` 文件

```dockerfile
FROM python:3.8-slim-buster
WORKDIR /app
COPY <本地路径> <目标路径>
RUN pip install -r requirements.txt # RUN创建镜像时使用的
CMD ["python3", "app.py"] 			# CMD是运行容器时使用的
```

然后在命令行运行

```shell
# 创建镜像
docker build -t my-finance . # 第一次调用 docker build 会较慢，第二次就快很多

# 启动容器
docker run -p 80:5000 -d my-finance # 然后就可以在浏览器访问这个docker应用了
```

## 常用命令

```shell
docker ps    						# 列举所有容器
docker stop <容器 ID>					# 停止容器
docker restart <容器 ID>				# 重启容器
docker rm <容器 ID>					# 删除容器
docker exec -it <容器 ID> /bin/bash	# 启动一个远程Shell
```

## 数据卷相关





































