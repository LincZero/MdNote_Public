# 好用的Docker镜像

## 资料

找镜像的地方

- https://hub.docker.com/

优秀镜像

- 存储类
  - nextcloud：
  - ftp (调研中)
    - ？，https://hub.docker.com/r/delfer/alpine-ftp-server
    - 清华大学ftp，tunathu/ftpsync
    - 中科大ftp，ustclug/ftp，（USTC，University of Science and Technology of China Linux User Group）
- portainer，portainer/portainer-ce，类似于Docker Desktop
- GitLab，gitlab/gitlab-ce
- Jenkins，jenkins/jenkins:lts-jdk11

## 管理类

其实进去docker里如果文档写得比较好的都有

### portainer

例如：https://hub.docker.com/r/portainer/portainer

```shell
$ docker pull portainer/portainer
#$ docker run -itd --restart=always \ 这个不行，没权限
#    -d -p 9000:9000 \
#    --name portainer_container \
#    portainer/portainer
    
#$ docker run -d --net=host \
#	--restart=unless-stopped \
#	-p 9000:9000 \
#    -v /var/run/docker.sock:/var/run/docker.sock \
#    portainer/portainer
    # -v /data/portainer_data:/data portainer/portainer:1.23.2

docker run -d -p 9000:9000\
    --name my_portainer \
    --restart=always \
    -v /var/run/docker.sock:/var/run/docker.sock portainer/portainer
```

### docker registry

以下是设置私有 Docker 镜像仓库的基本步骤：

1. 安装 Docker Registry：Docker Registry 是 Docker 的官方镜像仓库服务，你可以在你的服务器上运行它。安装 Docker Registry 的命令是 

   ```bash
   docker run -d -p 9050:5000 --restart=always --name dockerRegistry registry:2
   ```

2. 推送镜像到私有仓库：首先，你需要将你的本地镜像标记（tag）为私有仓库的地址。

   ```bash
   # 例如，如果你的私有仓库运行在 localhost 的 9050 端口，那么你可以使用以下命令标记你的镜像：
   $ docker tag msy/ubuntu:gcc48 192.168.1.208:9050/msy/ubuntu:gcc48
   # 然后，你可以使用以下命令将镜像推送到私有仓库：
   $ docker push 192.168.1.208:9050/msy/ubuntu:gcc48
   ```

3. 在 GitLab Runner 的配置文件中使用私有仓库的镜像：你可以在 .gitlab-ci.yml 文件中使用你的私有仓库的镜像，例如 `image: 192.168.1.208:9050/my-image`。

请注意，这只是一个基本的示例，实际的设置可能会更复杂。例如，你可能需要设置 SSL 证书来保护你的私有仓库，或者设置身份验证来控制谁可以访问你的私有仓库。你也需要确保你的 GitLab Runner  可以访问你的私有仓库。这可能需要在你的网络设置中进行一些调整。

其他bug：ip不是localhost时，可能需要设置 gitlab runner 的允许以http方式拉取

```bash
# 在Docker的配置文件（一般在/etc/docker/daemon.json）中添加以下内容
{
  "insecure-registries" : ["192.168.1.208:9050"]
}

# 这将告诉Docker守护进程，对于这个特定的Registry，允许使用HTTP进行连接。
# 然后，你需要重启Docker服务使配置生效：
sudo systemctl restart docker
```

## 仓库类 - ftp

### ustclug ftp

例如：https://hub.docker.com/r/ustclug/ftp

原

```bash
# docker pull ustclug/ftp 先拉镜像再创建，或像下面那样直接创建

docker run -itd --restart=always \
    -p 20-22:20-22 \
    -p 80:80 \
    -p 40000-40050:40000-40050 \
    -v $LOCAL_DIR/data:/srv/ftp \
    -v $LOCAL_DIR/log:/var/log \
    -v $LOCAL_DIR/home:/home \
    -e PRIVATE_PASSWD=secret \
    -e PASV_ADDRESS=$PUBLIC_IP_ADDRESS \
    ustclug/ftp
```

改

```bash
$ docker run -itd --restart=always \
    -p 20-22:20-22 \
    -p 8000:80 \
    -p 40000-40050:40000-40050 \
    -v $LOCAL_DIR/data:/srv/ftp \
    -v $LOCAL_DIR/log:/var/log \
    -v $LOCAL_DIR/home:/home \
    -e PRIVATE_PASSWD=secret \
    -e PASV_ADDRESS=$PUBLIC_IP_ADDRESS \
    --name ftp \
    ustclug/ftp
```

很多端口冲突，再改

```bash
$ docker run -itd --restart=always \
    -p 7020-7022:20-22 \
    -p 7000:80 \
    -p 40000-40050:40000-40050 \
    -v $LOCAL_DIR/data:/srv/ftp \
    -v $LOCAL_DIR/log:/var/log \
    -v $LOCAL_DIR/home:/home/http \
    -e PRIVATE_PASSWD=secret \
    -e PASV_ADDRESS=$PUBLIC_IP_ADDRESS \
    --name ftp \
    ustclug/ftp
```

### stilliard/pure-ftpd

https://hub.docker.com/r/stilliard/pure-ftpd

官方版

```bash
$ docker pull stilliard/pure-ftpd
$ docker run --rm -d --name ftpd_server \
	-p 21:21 -p 30000-30009:30000-30009 \
	stilliard/pure-ftpd bash /run.sh -c 30 -C 10 \
	-l puredb:/etc/pure-ftpd/pureftpd.pdb -E -j -R \
	-P localhost -p 30000:30059
```

简化版

```bash
$ docker run -d -p 21:21 -p 30000-30009:30000-30009 \
	-e "PUBLICHOST=your_public_ip" \
	-e "FTP_USER=user_name" \
	-e "FTP_PASS=user_password" \
	stilliard/pure-ftpd
```

### fauria/vsftpd

docker部署

这个docker比较简易，支持PASV被动模式，但不支持 sftp

```bash
$ docker pull fauria/vsftpd
# 参数解释
# -p 7021:21 主动端口映射
# -p 21100-21110:21100-21110 被动模式的端口映射
# -e PASV_MIN_PORT=21100 -e PASV_MAX_PORT=21110 被动模式的端口设置
# -e FTP_USER=ftpuser -e FTP_PASS=ftpuser 账密
# -e PASV_ADDRESS=192.168.1.208 应该设置为FTP服务器对外公开的地址，不要填本地回环地址
$ docker run -d \
    -v /home/msy/ftp:/home/vsftpd \
	--restart=always \
    -p 7021:21 \
    -p 21100-21110:21100-21110 \
    -e PASV_MIN_PORT=21100 -e PASV_MAX_PORT=21110 \
    -e FTP_USER=ftpuser -e FTP_PASS=ftpuser \
    -e PASV_ADDRESS=192.168.1.208 \
    --name vsftpd \
    fauria/vsftpd
```

快速验证

简单验证是否完成：（要么用测试demo，要么使用windows自带的ftp命令，话说不知道为什么FileZilla好像连接不上）

```bash
PS C:\Users\msy> ftp
ftp> open 192.168.1.208 7021
Connected to 192.168.1.208.
220 (vsFTPd 3.0.2)
200 Always in UTF8 mode.
User (192.168.1.208:(none)): ftpuser
331 Please specify the password.
Password:
230 Login successful. # successful基本就是成功了
ftp> mkdir test_xxx # 测试验证一下
ftp> quote PASV # 使用其他命令需要先开启主动或被动模式，quote PASV 或 quote PORT
ftp> ls
ftp> put D:\Git\Work\Recorder\recorder\cmake-build-debug
```

#### 权限管理

```bash
$ vi /etc/vsftpd/vsftpd.conf

anonymous_enable=NO #此处将yes改为no，禁用匿名访问
local_enable=YES #启用本地认证登陆
download_enable=NO #禁止本地用户下载文件
write_enable=YES #允许
anon_max_rate=5000000 # 限速5MBps，可以使用 anon_upload_max_rate 和 anon_upload_max_rate 分别设置上传和下载速率
#
# Default umask for local users is 077. You may wish to change this to 022,
# if your users expect that (022 is used by most other ftpd's)
local_umask=022
xferlog_enable=YES #开启日志
xferlog_file=/var/log/vsftpd.log
xferlog_std_format=YES
```

### atmoz/sftp

500M+，更新频繁

```bash
docker run -d -p 22:22 atmoz/sftp user:pass:::upload
```

注意：最后的那个是账密的设置，upload表示仅允许上传

个人用：

```bash
$ docker run -d \
    --restart=always \
    -p 7022:22 \
    -v /home/msy/ftp:/home/ftpuser/upload \
    --name sftp \
    atmoz/sftp \
    ftpuser:ftpuser:::upload
```

## 仓库类 - 静态页面

### nginx

（错误）

```bash
docker run -d \
	--restart=always \
	-p 7080:80 \
	-v /home/guest/ftp:/usr/share/nginx/html \
	--name nginx \
	nginx:latest
```

此时没有index.html大概率是403，禁止了目录索引。而我现在要弄的是ftp页，是需要索引的，要开一下：

创建一个新的Nginx配置文件。在你的宿主机上，创建一个新的文件，例如`default.conf`，并添加以下内容：

```bash
server {
    listen       80;
    server_name  localhost;

    location / {
        root   /usr/share/nginx/html;
        autoindex on; # 允许目录索引
    }

    # redirect server error pages to the static page /50x.html
    error_page   500 502 503 504  /50x.html;
    location = /50x.html {
        root   /usr/share/nginx/html;
    }
}
```

在这个文件中，我们设置了`autoindex on;`，这会开启目录索引

```bash
docker run -d \
	--restart=always \
	-p 7080:80 \
	-v /home/guest/ftp:/usr/share/nginx/html \
	-v /home/guest/default.conf:/etc/nginx/conf.d/default.conf \
	--name nginx \
	nginx:latest
```

或者直接改docker内的配置应该也行（就是不持久化）

在这里，`/path/to/your/default.conf`是你的`default.conf`文件的路径，你需要将其替换为实际的路径。注意，你需要确保这个文件的权限允许Nginx读取它。

跨域问题：

```json
server {
    listen 80;
    server_name localhost;

    location / {
        add_header 'Access-Control-Allow-Origin' '*';
        add_header 'Access-Control-Allow-Methods' 'GET, POST, OPTIONS';
        proxy_pass http://localhost:80;
        proxy_set_header Host $host:$server_port;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Host $host;
        proxy_set_header Via "nginx";
    }
}
```

顺便说一下非docker版本：

### systemd + python

适用于ubuntu：

/etc/systemd/system/httpServer.service

```ini
[Unit]
Description=My HTTP Service
After=network.target

[Service]
ExecStart=/usr/bin/python3 /root/Http/python.py
WorkingDirectory=/root/Http
User=root
Restart=always

[Install]
WantedBy=multi-user.target
```

/etc/systemd/system/httpServer2.service

```ini

[Unit]
Description=My HTTP Service
After=network.target

[Service]
ExecStart=/usr/bin/python3 /home/msy/ftp/ftpuser/python.py
WorkingDirectory=/home/msy/ftp/ftpuser/
User=root
Restart=always

[Install]
WantedBy=multi-user.target
```

/home/msy/ftp/ftpuser/python.py

```python
import http.server
import socketserver

PORT = 7080

Handler = http.server.SimpleHTTPRequestHandler
Handler.extensions_map.update({
    '.js':  'application/javascript',
})

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print("serving at port", PORT)
    httpd.serve_forever()
```

使用：

```bash
# 主要命令
sudo systemctl enable httpServer.service
# 除enable外的其他命令
stop
restart
start
```

## 仓库类 - 云盘gui

### nextcloud

略

## 仓库类 - 特殊

### gitlab

#### 部署

https://hub.docker.com/r/gitlab/gitlab-ce

注意gitlab提供了两个docker镜像：`gitlab/gitlab-ce` 和 `gitlab/gitlab-ee`

- `gitlab/gitlab-ce` 是GitLab社区版（Community Edition）的Docker镜像。这个版本是**完全开源**的，包含了GitLab的核心功能，适合个人或者小团队使用。
- `gitlab/gitlab-ee` 是GitLab企业版（Enterprise Edition）的Docker镜像。这个版本包含了所有CE版的功能，另外还有一些企业级的高级功能，如高级项目管理、审计报告等。这个版本是部分开源的，部分高级功能需要付费才能使用。

< CC版

```bash
docker run --detach \
    --hostname gitlab.example.com \
    --publish 443:443 --publish 80:80 --publish 22:22 \
    --name gitlab \
    --restart always \
    --volume /srv/gitlab/config:/etc/gitlab \
    --volume /srv/gitlab/logs:/var/log/gitlab \
    --volume /srv/gitlab/data:/var/opt/gitlab \
    gitlab/gitlab-ce:latest
```

< EE版

```bash
docker run --detach \
    --hostname gitlab.example.com \
    --publish 443:443 --publish 80:80 --publish 22:22 \
    --name gitlab \
    --restart always \
    --volume /srv/gitlab/config:/etc/gitlab \
    --volume /srv/gitlab/logs:/var/log/gitlab \
    --volume /srv/gitlab/data:/var/opt/gitlab \
    gitlab/gitlab-ee:latest
```

我主要使用的是cc版

个人端口冲突优化：（这里的hostname不是url，不加前缀和端口，端口默认是80，如修改了需要在external_url里面加，后面会说说。如果不想麻烦的话就直接映射到80端口就好）

```bash
docker run --detach \
    --hostname 192.168.1.208 \
    --publish 2443:443 --publish 80:80 --publish 2022:22 \
    --name gitlab \
    --restart always \
    --volume /srv/gitlab/config:/etc/gitlab \
    --volume /srv/gitlab/logs:/var/log/gitlab \
    --volume /srv/gitlab/data:/var/opt/gitlab \
    gitlab/gitlab-ce:latest
```

#### 其他设置

注意hostname要填和GitLab访问地址相同的地址，如果前期填错了后期的修改方式会比较麻烦（但好像没成功，最后还是删了docker重新创建）

- https://www.cnblogs.com/Irving/p/5460866.html

- https://itaken.github.io/2021/5/21/%E4%BF%AE%E6%94%B9gitlab%E7%9A%84host/

  ```bash
  $ find / -name gitlab.yml
  /opt/gitlab/embedded/service/gitlab-rails/config/gitlab.yml
  /var/opt/gitlab/gitlab-rails/etc/gitlab.yml
  
  $ find / -name gitlab.rb
  /etc/gitlab/gitlab.rb
  
  1.修改 gitlab.yml（/opt/gitlab/embedded/service/gitlab-rails/config/gitlab.yml）文件中的host地址
  2.修改 gitlab.rb（/etc/gitlab/gitlab.rb）文件中的external_url  [将`external_url = 'http://git.example.com'`修改为自己的IP地址（必须要加http://完整前缀）]
  3.客户端 git remote set-url origin <新的git地址>
  
  因为一开始我们设置了映射卷，实际上也能从这两处修改（这样一来也不需要在docker里安装nano了）：
  --volume /srv/gitlab/config:/etc/gitlab \
  --volume /srv/gitlab/data:/var/opt/gitlab \
  ```

#### 端口号bug

非默认80端口会出现这个情况

完整步骤：

```bash
先修改：external_url 'http://192.168.1.208:2080' # 但好像会导致无法访问网页
docker exec gitlab gitlab-ctl reconfigure # 重新配置
docker restart gitlab # 重启 GitLab
在clone处验证是否成功
```

但还是有bug：

```
docker run --detach \
    --hostname 192.168.1.208 \
    --publish 2443:443 --publish 2080:80 --publish 2022:22 \
    --name gitlab \
    --restart always \
    --volume /srv/gitlab/config:/etc/gitlab \
    --volume /srv/gitlab/logs:/var/log/gitlab \
    --volume /srv/gitlab/data:/var/opt/gitlab \
    gitlab/gitlab-ce:latest
```

这里clone的地址不对，如何修复这个问题

```
现在默认显示的地址是：http://192.168.1.208/LincZero/recorder-web.git
但实际上需要在后面加端口才能正常clone
```

其他的也有问题，例如runner运行时会有错误：

```
fatal: unable to access 'http://192.168.1.208/LincZero/recorder-web.git/': Failed to connect to 192.168.1.208 port 80 after 0 ms: Couldn't connect to server
ERROR: Job failed: exit code 1
```

其中修改external_url似乎无法修复这一问题。external_url默认值时，存在上述问题，此时网页还能正常打开。但若修改为'http://192.168.1.208:2080'，则网页无法打开

后来发现是这个原因：https://www.cnblogs.com/hero123/p/10559116.html，还要修改下面的Advanced setting且要改成不同的端口

#### 管理员

刚部署好的gitlab docker已经有一个默认管理员，我们需要在后台去设置这个管理员

```bash
docker exec -it <容器ID> /bin/bash # 进去容器
gitlab-rails console -e production # 进入 GitLab 控制台
user = User.where(id: 1).first # 查询第一个用户名，一般是管理员账户，且名字的root
user.password = 'msyqwe123' # 设置密码
user.password_confirmation = 'msyqwe123'
user.save!
```

### gitlab-runner

docker

- https://hub.docker.com/r/gitlab/gitlab-runner
- https://docs.gitlab.com/runner/install/docker.html

使用教程

- https://docs.gitlab.com/ee/tutorials/create_register_first_runner/
- https://docs.gitlab.com/ee/tutorials/create_register_first_runner/index.html
- https://docs.gitlab.com/runner/install/

#### 镜像版安装

~~~bash
# 1. 获取镜像
$ docker pull gitlab/gitlab-runner:latest

# 2. 运行容器
$ docker run -d --name gitlab-runner --restart always \
  -v /srv/gitlab-runner/config:/etc/gitlab-runner \
  gitlab/gitlab-runner:latest
  
# 3. 注册 GitLab Runner。你可以在 GitLab 的设置 -> CI/CD -> Runner 设置中找到这些信息。
$ docker run --rm -t -i -v /srv/gitlab-runner/config:/etc/gitlab-runner gitlab/gitlab-runner register
# 这将开始一个交互式会话，你需要提供以下信息：
    GitLab 实例的 URL
    注册令牌
    Runner 的描述和标签
    Runner 的执行器（例如 "docker"）
    Docker 镜像（例如 "alpine:latest"）

# 4. 使用 GitLab Runner
# 以下是一个 .gitlab-ci.yml 文件的例子
# 这个配置文件定义了两个阶段：构建和测试。在每个阶段，它都会运行一个脚本。
```
image: alpine:latest

stages:
  - build
  - test

build_job:
  stage: build
  script: echo "Building the application..."

test_job:
  stage: test
  script: echo "Testing the application..."
```
~~~

#### 普通版安装

后来没用docker，这个参考GitLab上他给你的install方法就行了，有各平台的安装

Linux

```bash
# Download the binary for your system
sudo curl -L --output /usr/local/bin/gitlab-runner https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-linux-amd64

# Give it permission to execute
sudo chmod +x /usr/local/bin/gitlab-runner

# Create a GitLab Runner user
sudo useradd --comment 'GitLab Runner' --create-home gitlab-runner --shell /bin/bash

# Install and run as a service
sudo gitlab-runner install --user=gitlab-runner --working-directory=/home/gitlab-runner
sudo gitlab-runner start
```

macOS

```bash
# Download the binary for your system
sudo curl --output /usr/local/bin/gitlab-runner https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-darwin-amd64

# Give it permission to execute
sudo chmod +x /usr/local/bin/gitlab-runner

# The rest of the commands execute as the user who will run the runner
# Register the runner (steps below), then run
cd ~
gitlab-runner install
gitlab-runner start
```

Windwos

```bash
# Run PowerShell: https://docs.microsoft.com/en-us/powershell/scripting/windows-powershell/starting-windows-powershell?view=powershell-7#with-administrative-privileges-run-as-administrator
# Create a folder somewhere on your system, for example: C:\GitLab-Runner
New-Item -Path 'C:\GitLab-Runner' -ItemType Directory

# Change to the folder
cd 'C:\GitLab-Runner'

# Download binary
Invoke-WebRequest -Uri "https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-windows-386.exe" -OutFile "gitlab-runner.exe"

# Register the runner (steps below), then run
.\gitlab-runner.exe install
.\gitlab-runner.exe start
```

#### 使用

在admin的Runner页面直接注册了（这个应该是在本机上进行的注册。一般在GitLab界面上也会告诉你各平台怎么去安装Runner，比较简单）

```bash
root@msy:~$ gitlab-runner register # windows第一行有所不同其他都一样：powershell先cd再：.\gitlab-runner.exe register
  # --url 192.168.1.208:2080，可以加这个简化一下
  # --token glrt-Gfhmw6ssJ8SVf3zdDQgJ，可以加这个简化一下
Runtime platform                                    arch=amd64 os=linux pid=128798 revision=d89a789a version=16.4.1
Running in system-mode.

Enter the GitLab instance URL (for example, https://gitlab.com/):
http://192.168.1.208:2080
Enter the registration token:
glrt-Gfhmw6ssJ8SVf3zdDQgJ
Verifying runner... is valid                        runner=Gfhmw6ssJ
Enter a name for the runner. This is stored only in the local config.toml file:
[msy]: root
Enter an executor: docker, virtualbox, docker+machine, instance, custom, docker-windows, parallels, shell, ssh, docker-autoscaler, kubernetes:
docker
Enter the default Docker image (for example, ruby:2.7): # 默认docker，可以被.gitlab-ci.yml所覆盖
ruby:2.7
Runner registered successfully. Feel free to start it, but if it's running already the config should be automatically reloaded!

Configuration (with the authentication token) was saved in "/etc/gitlab-runner/config.toml"
```

#### 设置

`config.toml` 是 GitLab Runner 的配置文件。其位置取决于你的 GitLab Runner 是如何安装的，以及你的操作系统。以下是一些可能的位置：

- 在 Linux 上，如果你使用的是系统级的 GitLab Runner，`config.toml` 通常位于 `/etc/gitlab-runner/` 目录下。

- 在 Windows 上，如果你使用的是系统级的 GitLab Runner，`config.toml` 通常位于 `C:\GitLab-Runner\` 目录下。

- 如果你使用的是用户级的 GitLab Runner（即你在用户目录下运行 GitLab Runner），`config.toml` 通常位于 GitLab Runner 的当前工作目录下。这可能是你运行 `gitlab-runner install` 命令时的目录。

你可以在命令行中使用 `find` 命令（在 Linux 或 macOS 上）或 `dir` 命令（在 Windows 上）来查找 `config.toml` 文件。例如，在 Windows 上，你可以使用以下命令：

```
dir config.toml /s
```

这个命令会在当前目录及其所有子目录中查找 `config.toml` 文件，并显示其完整路径。

请注意，修改 `config.toml` 文件需要管理员权限。你需要使用管理员权限运行编辑器（例如 Notepad++ 或 Visual Studio Code）来编辑这个文件。

---

这里之前用 windows 无法找到 pwsd 命令，就可以将这个文件的 pwsd 换成 powershell 来解决

## 专题 - GitLab CICD

参考：

- https://www.bilibili.com/video/BV18y4y1S7VC
- https://www.bilibili.com/video/BV1AV411A79q

### 比较Jenkins

与Jenkins相比，优点：

- 同时运行多个作业
- 对多个服务器（甚至每个项目）使用多个令牌
- 限制每个令牌的并发作业数
- 可以运行作业
  - 本地
  - 使用Docker容器
  - 使用Docker容器并通过SSH执行作业
  - 在不同的云和虚拟化管理程序上使用具有自动缩放功能的Docker容器
  - 连接到远程SSH服务器
- 用Go编写并作为单个二进制文件鲼，没有其他任何要求
- 支持Bash、PowerShell Core和Windows PowersShell
- 适用于GUN/Linux、macOS和Windows（几乎可以在任何可以运行Docker的地方）
- 允许自定义作业运行环境
- 无需重新启动即可自动重新加载配置
- 易于使用的设置，支持Docker、Docker-SSH、Parallels或SSH运行环境
- 嵌入式Prometheus指标HTTP服务器
- Referee workers监控Prometheus指标和其他特定于工作的数据并将其传递给GitLab

### 概念

GitLab Runner、CICD、DevOps的概念、区别、联系

- 概念
  1. GitLab Runner
     - 这是一个用来执行在 GitLab CI/CD 中定义的作业的程序。GitLab Runner  可以在您选择的机器上安装并执行作业。一旦作业完成，结果将返回给 GitLab。GitLab Runner 是自动化您的部署过程的关键部分。 
  2. CI/CD
     - 这是跨业务自动化和快速开发实践的一种途径。
     - CI 代表持续集成，确保**所有的代码改动都收到测试**，以尽最大可能减少软件中的错误。
     - CD  可能代表持续部署或持续交付，都涉及在开发环境中自动化代码改动的**部署**。这可以帮助开发团队更频繁、更可靠地向生产环境**交付**产品。 
  3. DevOps
     - 是一种理念和实践集合，强调软件开发人员（Dev）和运维工程师（Ops）之间的沟通和协作，以实现快速、高质量的软件**交付**。
     - DevOps 通常与工具如 GitLab、Jenkins、Docker 等一起使用，以实现其目标。 
- 关于区别
  - GitLab Runner 是一个**工具**
  - CI/CD 是一种开发**实践**
  - DevOps 是一种**理念**
  - 而 GitLab Runner 是实现 CI/CD 中自动执行作业的一个**重要工具**，CI/CD 则是实现 DevOps 理念中自动化交付部分的**实践方式**。
- 关于联系
  - 在 DevOps 理念下，开发人员和运维人员共同使用工具（如 GitLab Runner）并采取实践（如  CI/CD），从而实现更频繁和高质量的软件交付。
    因此，DevOps、CI/CD 和 GitLab Runner  是相互关联的，其目标都是提高开发效率并提升软件质量。

### 步骤 - 使用

先说使用再说注册，不过操作上是先注册再使用

其中GitLabRunner有三种类型和两种状态

- shared： 运行整个平台项目的作业（GitLab，这个需要管理员 > 系统设置 > Runnners）
- group： 运行特点group下的所有项目的作业（Group，Group > Setting > CI/CD > Runner > 展开）
- specific：运行指定的项目作业（Project，Project > Setting > CI/CD > Runner > 展开）
- locked：无法运行项目作业，刚注册完会是这种状态
- paused：不会运行作业

在对应的使用Runner的页面会看到三行信息：

1. 安装GitLab Runner (这步我不知道为什么好像已经完成过了，跳过)
2. 给了你GitLab的所在地址
3. 给了你一个 `registration token`

### 步骤 - 注册

注册需要获取runner token进行注册

注册有两种方式

- 交互式（一问一答）

  ```bash
  $ docker run -itd --rm -v ~/data/gitlab-runner/config:/etc/gitlab-runner gitlab/gitlab-runner:v12.6.0 register
  $ docker ps | grep gitlab
  $ docker exec -it aa9cae99d9f9 bash
  
  # docker里
  # > 输入Gitlab所在地址
  # > 输入注册命令
  # > 说一些描述信息
  # > 给一个标签，这个很关键
  # > 选择执行器
  #     如果选shell，下一步不用再填信息
  #     如果选docker，下一步要选一个默认镜像# 
  $ gitlab-runner register
  	--non-interactive \
      --executor "shell" \
      --url "http://gitlab.devops.com" \
      --registration-token "RjAoLah8Vp7JCGyNzZwf" \
      --description "devops-runner" \
      --tag-list "build,deploy" \
      --run-untagged="true" \
      --locked="false" \
      --access-level="not_protected"
  ```

- 非交互式（执行时顺便准备一堆参数）

  ```bash
  $ docker run -itd --rm -v ~/data/gitlab-runner/config:/etc/gitlab-runner gitlab/gitlab-runner:v12.6.0 register \
      --non-interactive \
      --executor "shell" \
      --url "http://gitlab.devops.com" \
      --registration-token "RjAoLah8Vp7JCGyNzZwf" \
      --description "devops-runner" \
      --tag-list "build,deploy" \
      --run-untagged="true" \
      --locked="false" \
      --access-level="not_protected"
  ```

注册完成后，可以在GitLab上看到注册成功的Runner

有些参数也可以在Running创建后通过GitLab设置再去修改

### 补充 - 其他参数

一些参数的介绍

- 执行器（主要是下面3种，其他的功能不是很丰富）

  - Shell （这个使用的是本机的环境，但是可以在docker里面去执行shell，从而间接使用docker环境）
  - Docker （这个的pull过程可能会稍慢，不知道能不能预先下载镜像来加速这个过程）
  - Kubernetes
  - ![image-20231018225021694](README.assets/image-20231018225021694.png)

  - | 执行器                 | Shell | Docker | Kubernetes |
    | ---------------------- | ----- | ------ | ---------- |
    | 每次构建后清除构造环境 | ❌     | ✅      | ✅          |
    | 每次检查clone是否存在  | ✅     | ✅      | ❌          |

### 补充 - 其他命令

```bash
gitlab-runner register		# 默认交互模式下使用，非交互模式添加 --non-interactive
gitlab-runner list 			# 此命令列出了保存在配置文件中的所有运行程序
gitlab-runner verify 		# 检查注册的runner是否可以连接，但不验证GitLab服务是否正在使用runner。--delete 删除
gitlab-runner unregister 	# 该命令使用GitLab取消已注册的runner

gitlab-runner unregister --url http://gitlab.example.com/ --token t0k3n # 使用令牌注销
gitlab-runner unregister --name test-runner # 使用名字注销
gitlab-runner unregister --all-runners # 注销所有
```

### 并发数设置

GitLab Runner的并发数可以在Runner的配置文件config.toml中进行设置。这个文件通常位于/etc/gitlab-runner/目录下。在config.toml文件中，你可以找到concurrent这个选项，它决定了Runner的并发数。

以下是一个config.toml的示例：

```ini
concurrent = 4 # 默认是1

[[runners]]
  name = "My Runner"
  url = "https://gitlab.com/"
  token = "TOKEN"
  executor = "shell"
  [runners.custom_build_dir]
  [runners.cache]
    [runners.cache.s3]
    [runners.cache.gcs]
```

## 其他

Docker 通常用于运行后台服务，而不是图形用户界面 (GUI) 应用程序。然而，有些 Docker 镜像确实被配置为运行桌面环境，通常是通过在 Docker 容器中运行 X 服务器或其他类型的显示服务器。

对于 Windows，情况就复杂多了。Microsoft 提供了  Windows Server Core 和 Nano Server 的 Docker  镜像，但这些都是无头的，也就是说，它们不包含图形用户界面。尽管有一些工作已经在尝试在 Docker 中运行 Windows 桌面，但这并不是  Docker 的主要用途，也不是 Microsoft Windows Docker 镜像的主要目标。

总的来说，如果你需要在 Docker 中运行带有 GUI 的 Windows 应用程序，可能需要寻找其他解决方案。例如，你可能会考虑使用 Windows 的远程桌面服务，或者使用像是 VirtualBox 或 VMware 这样的全功能虚拟机软件。

然而，如果你只是想在 Docker 中运行 Windows 应用程序，而不需要 GUI，那么 Windows Server Core 或 Nano Server 镜像可能会满足你的需求。

## 自定义DockerFile

有时单个docker满足不了我们，我们需要一些自定义的docker，这里列些常用的

### 自用gcc

#### 自用gcc4.8

- ubuntu 18.04
- gcc/g++ 4.8
- cmake 3.20.2

```dockerfile
# 包含gcc4.8, g++4.8和cmake的Ubuntu镜像

# 使用Ubuntu 18.04作为基础镜像
FROM ubuntu:18.04

# 更新apt源并安装必要的工具
RUN apt-get update && apt-get install -y software-properties-common

# 安装gcc-4.8和g++-4.8
RUN apt-get update && apt-get install -y gcc-4.8 g++-4.8

# 设置gcc-4.8和g++-4.8为默认
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50 --slave /usr/bin/g++ g++ /usr/bin/g++-4.8

# (可选) 添加cmake的官方PPA，不加的话cmake版本只有3.10太低
# RUN apt-get install -y apt-transport-https ca-certificates gnupg software-properties-common wget && \
#     wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null && \
#     apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'  
# 安装cmake
# RUN apt-get install -y cmake
# RUN apt-get update && apt-get install -y cmake=3.20.2-0kitware1ubuntu18.04.1

# 安装依赖
RUN apt-get install -y wget libssl-dev make

# 下载cmake 3.20.2
RUN wget https://github.com/Kitware/CMake/releases/download/v3.20.2/cmake-3.20.2.tar.gz

# 解压cmake源码
RUN tar -zxvf cmake-3.20.2.tar.gz

# 进入cmake源码目录
WORKDIR cmake-3.20.2

# 编译并安装cmake
RUN ./bootstrap && make && make install

# 返回到主目录
WORKDIR /

# 验证安装
RUN gcc --version && g++ --version && cmake --version
```

docker build -t msy/ubuntu:gcc48 .

#### 自用gcc11

```dockerfile
# 使用Ubuntu 20.04作为基础镜像
FROM ubuntu:20.04

# 设置环境变量，防止在安装过程中出现tzdata挂起的情况
ENV DEBIAN_FRONTEND=noninteractive

# 更换为清华大学Ubuntu镜像源
RUN echo "deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal main restricted universe multiverse" > /etc/apt/sources.list && \
    echo "deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-updates main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-backports main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-security main restricted universe multiverse" >> /etc/apt/sources.list

# 更新apt源并安装必要的工具
RUN apt-get update && apt-get install -y software-properties-common

# 安装gcc-11和g++-11
RUN apt-get update && apt-get install -y gcc-11 g++-11

# 设置gcc-11和g++-11为默认
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 50 --slave /usr/bin/g++ g++ /usr/bin/g++-11

# (可选) 添加cmake的官方PPA，不加的话cmake版本只有3.10太低
# RUN apt-get install -y apt-transport-https ca-certificates gnupg software-properties-common wget && \
#     wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null && \
#     apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'  
# 安装cmake
# RUN apt-get install -y cmake
# RUN apt-get update && apt-get install -y cmake=3.20.2-0kitware1ubuntu18.04.1

# 安装依赖
RUN apt-get install -y wget libssl-dev make

# 下载cmake 3.20.2
RUN wget https://github.com/Kitware/CMake/releases/download/v3.20.2/cmake-3.20.2.tar.gz

# 解压cmake源码
RUN tar -zxvf cmake-3.20.2.tar.gz

# 进入cmake源码目录
WORKDIR cmake-3.20.2

# 编译并安装cmake
RUN ./bootstrap && make && make install

# 返回到主目录
WORKDIR /

# 验证安装
RUN gcc --version && g++ --version && cmake --version
```

docker build -t msy/ubuntu:gcc11 .

### 自用node

- node:18-alpine

### 自用python

#### 自用conda (Debian)

- ~~miniconda3 (Debian)~~

```bash
# 使用官方的miniconda3镜像作为基础镜像
FROM continuumio/miniconda3

# 设置工作目录
WORKDIR /app

# 将当前目录下的所有文件（除了.dockerignore排除的路径）复制到容器的/app目录下
COPY . /app

# 创建一个新的conda环境并安装pip
RUN conda create --name myenv pip

# 激活新的conda环境
RUN echo "source activate myenv" >~/.bashrc
ENV PATH /opt/conda/envs/myenv/bin:$PATH

# 使用pip安装你的Python项目的依赖
# COPY requirements.txt /app/requirements.txt
# RUN pip install -r requirements.txt

# 指定容器启动时执行的命令
# CMD ["python", "your_script.py"]
```

#### 自用conda (公司)

- ubuntu 20.04
- conda3 ~~[2023.09-0-Linux-x86_64](https://repo.anaconda.com/archive/Anaconda3-2023.09-0-Linux-x86_64.sh)~~ [mini版](https://repo.anaconda.com/miniconda/Miniconda3-py39_23.9.0-0-Linux-x86_64.sh)
- python 3.9.0
- git

```dockerfile
# 使用 Ubuntu 20.04 作为基础镜像
FROM ubuntu:20.04

# 定义环境变量，用于解决他中途会让你填时区什么的
ENV TZ=Asia/Shanghai
ENV DEBIAN_FRONTEND=noninteractive

# 更新 Ubuntu 的源列表为阿里云镜像
RUN sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list
RUN sed -i 's/security.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list

# 设置工作目录
WORKDIR /usr/src/app

# 定义环境变量
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8
ENV PATH /opt/conda/bin:$PATH

# 安装必要的包
RUN apt-get update --fix-missing && \
    apt-get install -y wget bzip2 ca-certificates libglib2.0-0 libxext6 libsm6 libxrender1 git mercurial subversion && \
    apt-get clean

# 下载并安装 Anaconda
# 旧 RUN wget --quiet https://repo.anaconda.com/archive/Anaconda3-2023.09-0-Linux-x86_64.sh -O ~/anaconda.sh
RUN wget --quiet https://repo.anaconda.com/miniconda/Miniconda3-py39_23.9.0-0-Linux-x86_64.sh -O ~/miniconda.sh
RUN /bin/bash ~/miniconda.sh -b -p /opt/conda
RUN rm ~/miniconda.sh
RUN /opt/conda/bin/conda clean -tipy

# 创建一个 Python 3.9 的环境
RUN /opt/conda/bin/conda install -y python=3.9
RUN /opt/conda/bin/conda clean -tipy

# 使用新环境
RUN conda create -n HoloWAN_Recorder_Test_Env python=3.9.0
SHELL ["conda", "run", "-n", "HoloWAN_Recorder_Test_Env", "/bin/bash", "-c"]

# 更新 Conda 基础环境版本
# RUN conda update -n base -c defaults conda

# 确认 Python 和 Conda 已经安装
RUN conda --version
RUN python --version
RUN pip --version

# 暴露必要的端口（这个例子中是 Jupyter Notebook 的默认端口）
EXPOSE 8888

# 定义一个运行应用的命令
# CMD ["echo", "Dockerfile setup complete"]
CMD ["tail", "-f", "/dev/null"]
```

docker build --no-cache -t msy/conda:3 .

```bash
docker run -itd \
	-p 8888:8888 \
	--restart=always \
	--name conda_recorder_test \
	msy/conda:3
```

#### 自己用flask pyServer服务

Dockerfile

```dockerfile
# 建议使用
# docker build -t recorder_py_server .
# docker run -itd \
#     --restart=always \
#     -p 8088:8088 \
#     --name recorder_py_server
#     recorder_py_server

# 使用清华的Ubuntu镜像
# FROM ubuntu:18.04
# 设置清华的源
#RUN echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse" > /etc/apt/sources.list && \
#    echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse" >> /etc/apt/sources.list && \
#    echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse" >> /etc/apt/sources.list && \
#    echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse" >> /etc/apt/sources.list

# 使用清华的Ubuntu镜像
FROM ubuntu:20.04
# 设置清华的源
RUN echo "deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal main restricted universe multiverse" > /etc/apt/sources.list && \
    echo "deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-updates main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-backports main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-security main restricted universe multiverse" >> /etc/apt/sources.list

# 安装ca-certificates
RUN apt-get update && apt-get install -y ca-certificates

# 安装必要的工具
RUN apt-get update && apt-get install -y wget bzip2

# 安装miniconda3
RUN wget https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda.sh && \
    bash ~/miniconda.sh -b -p /opt/conda && \
    rm ~/miniconda.sh

# 将conda的bin目录添加到PATH
ENV PATH /opt/conda/bin:$PATH

# 配置conda的镜像源
RUN conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/ && \
    conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/ && \
    conda config --set show_channel_urls yes

# 复制当前目录下的所有文件到容器的/app目录
COPY . /app

# 切换工作目录
WORKDIR /app

# 根据requirements.txt安装依赖
RUN pip install -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple

# 开放7088端口
EXPOSE 7088

# 运行flask项目
CMD ["python", "app.py"]

```

### 自用android

#### 自用android (旧版本，失败)

- ubuntu 20.04
- jdk 8
- gradle 6.5

```dockerfile
# 基于 Ubuntu 20.04 LTS
FROM ubuntu:20.04

# 话说这里如果基于 gradle:8.0-jdk11 镜像可能会更方便
# FROM gradle:8.0-jdk11

# 设置非交互模式
ENV DEBIAN_FRONTEND=noninteractive

# 更新系统并安装必要的工具
RUN apt-get update && apt-get install -y \
    git \
    curl \
    unzip \
    python \
    openjdk-8-jdk \
    build-essential \
    libssl-dev \
    rsync \
    zip \
    zlib1g-dev \
    libncurses5-dev \
    libncursesw5-dev \
    libc6-dev \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# 安装 Android SDK
ENV ANDROID_HOME /opt/android-sdk
ENV PATH ${PATH}:${ANDROID_HOME}/tools/bin:${ANDROID_HOME}/platform-tools

RUN mkdir -p ${ANDROID_HOME} && cd ${ANDROID_HOME} \
    && curl -o sdk-tools.zip https://dl.google.com/android/repository/sdk-tools-linux-4333796.zip \
    && unzip sdk-tools.zip && rm sdk-tools.zip \
    && yes | sdkmanager --licenses \
    && sdkmanager "platform-tools" "platforms;android-29" "build-tools;29.0.3"

# 安装 Gradle
ENV GRADLE_HOME /opt/gradle
ENV PATH ${PATH}:${GRADLE_HOME}/bin

RUN curl -o gradle.zip https://services.gradle.org/distributions/gradle-6.5-bin.zip \
    && unzip -d /opt gradle.zip && rm gradle.zip \
    && mv /opt/gradle-* ${GRADLE_HOME}

# 设置工作目录
WORKDIR /app

# 将项目复制到 Docker 镜像中
# COPY . /app

# 编译项目
# RUN gradle assembleDebug
```

docker build -t msy/android:jdk8 .

#### 自用android (新)

- Debian-based 系统 (Open JDK)
- jdk 11
- gradle 8

```dockerfile
# 基于 gradle:8.0-jdk11 镜像
FROM gradle:8.0-jdk11

# 设置非交互模式
ENV DEBIAN_FRONTEND=noninteractive

# 阿里云镜像 (特殊仓库需要通过公钥信任仓库才能使用，docker会先安装一个公钥管理器并输入公钥然后才会去拉对应的仓库)
RUN echo "deb http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse" > /etc/apt/sources.list && \
    echo "deb http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse" >> /etc/apt/sources.list && \
    apt-get update && \
    apt-get install -y --no-install-recommends gnupg2 && \
    apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3B4FE6ACC0B21F32

# 更新系统并安装必要的工具
RUN apt-get update && apt-get install -y \
    git \
    curl \
    unzip \
    python \
    libssl-dev \
    rsync \
    zip \
    zlib1g-dev \
    libncurses5-dev \
    libncursesw5-dev \
    libc6-dev \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# 安装 Android SDK
ENV ANDROID_HOME /opt/android-sdk
ENV PATH ${PATH}:${ANDROID_HOME}/tools/bin:${ANDROID_HOME}/platform-tools

RUN mkdir -p ${ANDROID_HOME} && cd ${ANDROID_HOME} \
    && curl -o sdk-tools.zip https://dl.google.com/android/repository/sdk-tools-linux-4333796.zip \
    && unzip sdk-tools.zip && rm sdk-tools.zip \
    && yes | sdkmanager --licenses \
    && sdkmanager "platform-tools" "platforms;android-29" "build-tools;29.0.3"

# 设置工作目录
WORKDIR /app

# 将项目复制到 Docker 镜像中
# COPY . /app

# 编译项目
# RUN gradle assembleDebug
```

docker build -t msy/android:jdk11 .

#### 自用android（公司，成功但版本不对）

使用公司用的配置：

- ubuntu 20.04
- gradle-8
- jdk8 (8/15/17好像这几个都有，但似乎用的是 jdk-17，这里错了)

```dockerfile
# 基于 Ubuntu 20.04 LTS
FROM ubuntu:20.04

# 定义环境变量
ENV JAVA_HOME /usr/lib/jvm/java-8-openjdk-amd64
ENV GRADLE_HOME /opt/gradle
ENV GRADLE_VERSION 8.0

# 更新 Ubuntu 的源列表
RUN apt-get update

# 安装 OpenJDK-8
RUN apt-get install -y openjdk-8-jdk

# 安装 wget 和 unzip
RUN apt-get install -y wget unzip

# 验证 Java 版本
RUN java -version

# 下载所需的 Gradle 版本
RUN wget https://services.gradle.org/distributions/gradle-${GRADLE_VERSION}-bin.zip -P /tmp

# 解压 Gradle 并移动到指定目录
RUN unzip -d /opt/gradle /tmp/gradle-*.zip

# 配置环境变量
ENV PATH ${GRADLE_HOME}/gradle-${GRADLE_VERSION}/bin:${PATH}

# 验证 Gradle 版本
RUN gradle -v

# 清理缓存
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# 设置工作目录
WORKDIR /app

# 默认命令
CMD ["bash"]
```

docker build -t msy/android:jdk8 .

#### 自用android（公司，成功）

使用公司用的配置：

- ubuntu 20.04
- gradle-8.0 (8.1好像会正确一点，还有个Android Gradle Plugin的8.1版本)
- jdk17 (8/15/17好像这几个都有，但似乎用的是 jdk-17)

```dockerfile
# 基于 Ubuntu 20.04 LTS
FROM ubuntu:20.04

# 定义环境变量，用于解决他中途会让你填时区什么的
ENV TZ=Asia/Shanghai
ENV DEBIAN_FRONTEND=noninteractive

# 更新 Ubuntu 的源列表
# 阿里云镜像 (特殊仓库需要通过公钥信任仓库才能使用，docker会先安装一个公钥管理器并输入公钥然后才会去拉对应的仓库)
RUN sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list
RUN sed -i 's/security.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list

# 安装其他依赖
RUN apt-get update
RUN apt-get install -y wget unzip git # 安装 wget 和 unzip 和 git

# JDK部分
ENV JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64
RUN apt-get install -y openjdk-17-jdk # 安装OpenJDK-17
ENV PATH ${JAVA_HOME}/bin:${PATH} # 配置环境变量
RUN java -version # 验证 Java 版本: 17.0.8.1
RUN update-alternatives --list java # 调试查看安装路径: /usr/lib/jvm/java-17-openjdk-amd64/bin/java
    # TODO 主题查看调试查看的安装路径和一开始指定的是否一致
    # RUN echo "JAVA_HOME=$(dirname $(dirname $(readlink -f $(which java))))" >> /etc/environment # 自动获取 JAVA_HOME
    # RUN source /etc/environment # 使用新的 JAVA_HOME 环境变量
    # ENV JAVA_HOME=$(dirname $(dirname $(readlink -f $(which java)))) # 自动获取 JAVA_HOME

# SDK部分
ENV ANDROID_HOME /opt/android-sdk
RUN wget https://dl.google.com/android/repository/commandlinetools-linux-10406996_latest.zip -P /tmp # 下载
    # 应该对应的 33.0.0？ 链接可在https://developer.android.com/studio?hl=zh-cn底部找到
RUN mkdir -p ${ANDROID_HOME}/cmdline-tools/lastest/
RUN mkdir -p ${ANDROID_HOME}/tmp
RUN unzip -d ${ANDROID_HOME}/tmp/ /tmp/commandlinetools-*.zip # 解压
RUN mv ${ANDROID_HOME}/tmp/cmdline-tools/* ${ANDROID_HOME}/cmdline-tools/lastest/
	# 解压。这里有点怪，原压缩包是没latest路径的，但要解压时要多一层latest，否则sdkmanager不认
	# 原压缩包内容：/cmdline-tools/bin
	# 但sdkmanager会去找：/cmdline-tools/latest/bin
ENV PATH ${ANDROID_HOME}/cmdline-tools/lastest/bin:${PATH} # 配置环境变量
RUN yes | ${ANDROID_HOME}/cmdline-tools/lastest/bin/sdkmanager --licenses # 同意 Android SDK 许可协议
RUN ${ANDROID_HOME}/cmdline-tools/lastest/bin/sdkmanager --version # 验证 Android SDK 版本

# Gradle部分
ENV GRADLE_VERSION 8.0
ENV GRADLE_HOME /opt/gradle
RUN wget https://services.gradle.org/distributions/gradle-${GRADLE_VERSION}-bin.zip -P /tmp # 下载
RUN unzip -d /opt/gradle /tmp/gradle-*.zip # 解压
ENV PATH ${GRADLE_HOME}/gradle-${GRADLE_VERSION}/bin:${PATH} # 配置环境变量
RUN gradle -v # 验证 Gradle 版本: 8.0

# 清理缓存
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
# 设置工作目录
WORKDIR /app

# 默认命令
CMD ["bash"]
```

docker build --no-cache -t msy/android:jdk17 .

小技巧，整个过程非常长，SDK和Gradle可交换，可以将容易失败的部分往上移，快速调试。

#### 自用android（windows shell）

差不多，能用AndroidStudio的话环境基本都齐。需要特别注意的是：

/local.properties

```
sdk.dir=C\:\\Users\\msy\\Desktop\\AndroidSDK
```

这个本地的路径可能不能被 runner 访问，要添加环境：

Git Runner的环境变量可以在其配置文件中设置。Git Runner的配置文件通常位于

- `/etc/gitlab-runner/config.toml`（Linux）
- `C:\GitLab-Runner\config.toml`（Windows）。

你可以按照以下步骤来设置`ANDROID_HOME`环境变量：

1. 打开Git Runner的配置文件。你可能需要使用管理员权限来编辑这个文件。

2. 在`[[runners]]`部分添加`environment`字段，如下所示：

   ```toml
   [[runners]]
     ...
     environment = ["ANDROID_HOME=C:\\Users\\msy\\Desktop\\AndroidSDK"]
     ...
   ```

   注意你需要将`C:\\Users\\msy\\Desktop\\AndroidSDK`替换为你的Android SDK的实际路径。

3. 保存并关闭配置文件。

4. 重启Git Runner以使新的配置生效。你可以在命令行中运行以下命令来重启Git Runner：

   ```bash
   gitlab-runner restart
   ```























