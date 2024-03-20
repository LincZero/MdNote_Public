### 部署gpt

```bash
# 检查
docker ps # 查看原有容器，没有对应的容器
docker image ls # 查看原有镜像，没有对应的镜像，要自己下载

# 准备镜像
docker pull node:latest # 下载node镜像，该命令通过 docker hub 获取
docker search node # 查看是否安装成功
docker image # 查看是否安装成功

# 准备容器
# docker run -itd --name gpt node # 使用node镜像创建gpt容器
docker run -p 4000:4000 -itd --name gpt node # (最好在这一步暴露端口先)
docker ps # 查看是否创建新容器成功（加-a可以看到已停止的容器）
docker exec -it gpt /bin/bash # 测试:进入容器
								# -it 是 -i交互式 -t终端 的意思
								# /bin/bash 是在容器中执行的命令，bash允许与容器进行交互
								# 还有一种更简短的写法：docker attach gpt，但这个不易于进行交互操作
exec # 或Ctrl+D，测试:退出容器

# docker中运行程序
docker cp 'PatrikZeros-ChatGPT-API-UI 230511' gpt:/home/gpt # 拷贝代码到容器中 (宿主机到docker)
... # 进入代码位置
npm i pm2 -g # 先下载pm2
pm2 start e... # 运行程序
pm2 list # 检查运行情况


# 暴露端口
# 多种方法
# 1. 创建容器时可以指定，但我们已经创建过了。后来还是选择删除容器重新创建
#     docker rm gpt
#     docker run -p 4000:4000 -itd --name gpt node
# 2. dockerfile配置，EXPOSE，但我们没用dockerfile文件
# 3. 好像不管用
#     iptables -t nat -A DOCKER -p tcp --dport 4000 -j DNAT --to-destination 172.17.0.5:4000 # 添加端口映射
#     iptables -t nat -A POSTROUTING -j DOCKER
#     iptables -t nat -vnL # 检查是否映射成功

# 开机自启
pm2 save # 这是将pm2正在运行的列表设置为开机自启项，如果是非pm2要用其他方法。不过好像无效就是了
```

### 公司的几个服务

```bash
portainer # Image: portainer/portainer-ce. port: 9000. 相当于web版的docker desktop
Jenkins # Image: jenkins/jenkins:lts-jdk11. port: 50000,8999
gitlab # Image: gitlab/gitlab-ce. port: 222 443 80
gpt # Image: node. port: 4000
```

### 自启动相关

linux开机自启动指定docker，制定docker开机自启动 `pm2 start ee.cjs` 命令

首先，确保 Docker 守护进程已设置为开机自启动。在大多数 Linux 发行版上，这可以通过以下命令实现：

```bash
sudo systemctl enable docker
```

使用 `docker run` 命令来创建您的 Docker 容器。在此命令中包含 `--restart=always` 选项，以便容器在每次系统启动时自动启动。另外，使用 `-d` 选项以分离模式运行容器：

```bash
sudo docker run -d --name your_container_name --restart=always your_image_name
# 用您的实际容器名和镜像名替换 your_container_name 和 your_image_name
```

在 Docker 容器内部设置 `ee.cjs` 的开机自启动。要绑定容器内的 PM2 与宿主机的开机启动进程，您可以使用以下命令：

```bash
docker exec your_container_name pm2 start ee.cjs
docker exec your_container_name pm2 save
docker exec your_container_name pm2 startup
```

这些命令将在容器内部使用 `pm2` 来运行 `ee.cjs` 文件集合、保存当前进程列表，以及生成系统服务的启动脚本。

现在，每次您的 Linux 系统启动时，Docker 容器应自动启动，容器内的 PM2 进程也会自动运行 `ee.cjs` 命令。

### DockerFile 方式

新

```dockerfile
# 运行建议：
# 1. docker build -t gpt-next-web3 .
# 2. docker run -d --restart=always -p 8000:3000 --name gpt-next-web gpt-next-web3

# 基础镜像
FROM node:18-alpine

# 安装pm2
RUN npm install -g pm2

# 设置工作目录
WORKDIR /app

# 复制项目文件
COPY . .

# 安装依赖
RUN npm install

# 暴露端口（如果你的应用需要的话）
EXPOSE 3000

# 运行应用
CMD ["pm2-runtime", "npm", "--", "run", "dev"]
```

老

```dockerfile
FROM node:18-alpine AS base

FROM base AS deps

RUN apk add --no-cache libc6-compat

WORKDIR /app

COPY package.json yarn.lock ./

RUN yarn config set registry 'https://registry.npmmirror.com/'
RUN yarn install

FROM base AS builder

RUN apk update && apk add --no-cache git

ENV OPENAI_API_KEY=""
ENV CODE=""

WORKDIR /app
COPY --from=deps /app/node_modules ./node_modules
COPY . .

RUN yarn build

FROM base AS runner
WORKDIR /app

RUN apk add proxychains-ng

ENV PROXY_URL=""
ENV OPENAI_API_KEY=""
ENV CODE=""

COPY --from=builder /app/public ./public
COPY --from=builder /app/.next/standalone ./
COPY --from=builder /app/.next/static ./.next/static
COPY --from=builder /app/.next/server ./.next/server

EXPOSE 3000

CMD if [ -n "$PROXY_URL" ]; then \
        export HOSTNAME="127.0.0.1"; \
        protocol=$(echo $PROXY_URL | cut -d: -f1); \
        host=$(echo $PROXY_URL | cut -d/ -f3 | cut -d: -f1); \
        port=$(echo $PROXY_URL | cut -d: -f3); \
        conf=/etc/proxychains.conf; \
        echo "strict_chain" > $conf; \
        echo "proxy_dns" >> $conf; \
        echo "remote_dns_subnet 224" >> $conf; \
        echo "tcp_read_time_out 15000" >> $conf; \
        echo "tcp_connect_time_out 8000" >> $conf; \
        echo "localnet 127.0.0.0/255.0.0.0" >> $conf; \
        echo "localnet ::1/128" >> $conf; \
        echo "[ProxyList]" >> $conf; \
        echo "$protocol $host $port" >> $conf; \
        cat /etc/proxychains.conf; \
        proxychains -f $conf node server.js; \
    else \
        node server.js; \
    fi

```

使用

```bash
docker build -t gpt-next-web .
# 后面好像有bug，说权限问题，要新增这个：--network host

docker run -d -p 4000:3000 \
	--restart=always \
	--name gpt \
   -e OPENAI_API_KEY=sk-xxxx \
   -e CODE=页面访问密码 \
   yidadaa/chatgpt-next-web
```









