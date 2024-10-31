# SSR搭建

# 目录

# SSR搭建

## 基本流程

### 先连接服务器

### 一键搭建SS/SSR多用户环境

主用地址：（把`&amp`删了）（这个好像不行了）

```shell
yum -y install wget
wget -N --no-check-certificate https://softs.fun/Bash/ssr.sh &amp;&amp; chmod +x ssr.sh &amp;&amp; bash ssr.sh
```

```shell
yum -y install wget
wget -N --no-check-certificate https://softs.fun/Bash/ssr.sh  chmod +x ssr.sh  bash ssr.sh
```

备用地址：（把`&amp`删了）（还可以用）

```shell
yum -y install wget
wget -N --no-check-certificate https://raw.githubusercontent.com/ToyoDAdoubi/doubi/master/ssr.sh &amp;&amp; chmod +x ssr.sh &amp;&amp; bash ssr.sh
```

```shell
yum -y install wget
wget -N --no-check-certificate https://raw.githubusercontent.com/ToyoDAdoubi/doubi/master/ssr.sh  chmod +x ssr.sh  bash ssr.sh
```

### 向导配置

#### 查看配置

```
bash ssr.sh
```

![img](SSR搭建.assets/clipboard.png)

#### 向导配置

| 选项                                 | 参数                                              |
| ---------------------------------- | ----------------------------------------------- |
| 要进行的操作：(数字输入)                      | 1                                               |
| I P                                | 这个不用配置                                          |
| 端口 : (默认2333)                      | (Enter)                                         |
| 账户密码 : (默认doub.io)                 | 762699299 uhxylosol  Linc0                      |
| 加密方式 : (默认5.ase-128-ctr)           | 10(aes-256-ctr)                                 |
| 协议 : (默认2.auth_sha1_v4_compatible) | (Enter)                                         |
| 是否设置协议插件兼容原版                       | Y                                               |
| 混淆插件：(默认1.plain)                   | (Enter)<br />`#？？tls1.2_ticket_auth_compatible` |
| 设备数限制：0(无限)                        | (Enter)                                         |
| 单线程限速 : 0 KB/S                     | (Enter)                                         |
| 端口总限速 : 0 KB/S                     | (Enter)                                         |

### 完成

安装完成后，保存好SS账号信息就可以使用了

依然是`bash ssr.sh`，状态显示 “已安装 并 已启动” 则表示成功

![img](SSR搭建.assets/clipboard-1597667534650.png)

## 安装谷歌BBR加速来优化VPS的速度

（如果你用的是搬瓦工的VPS它的CentOS 6系统有自带的BBR加速，如果是其它系统或是别家VPS可以继续看下面给你的VPS安装谷歌BBR加速）

## 其他

### 报错（pid被锁住）

报错：another app is currently holding the yum lock......pid: 2724

原因：是因为开了一个ssr服务了，你再安装就会被锁

解决：`kill -9 2724`，后面那个pid视报错的pid而定

