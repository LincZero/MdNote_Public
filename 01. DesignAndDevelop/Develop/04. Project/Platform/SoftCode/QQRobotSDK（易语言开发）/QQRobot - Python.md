# QQRobot

# 目录

[TOC]

# **悲报：2020，QQ施压、CoolQ停运**

![img](QQRobot - Python.assets/F2723DN{%6NBWJXT$CAPGZ0.jpg)

还能用的：

- sq
- mini
- oq
- 小栗子

# 基本程序

## 安装酷Q及环境

> 安装酷Q软件本体
>
> 下载CQHttp，并把文件放到：酷Q Air\app目录下
>
> pip install nonebot

## 生成机器人文件目录（结构树）

```
QQbot.py
config.py
awesome
plugins
	插件1
		__init__.py
		work.py
    插件2
```

## 配置酷Q

酷Q Air\data\app\io.github.richardchien.coolqhttpapi\config\QQ.json 内容改为

```json
{
    "$schema": "https://cqhttp.cc/config-schema.json",
    "host": "0.0.0.0",
    "port": 5700,
    "use_http": true,
    "ws_host": "0.0.0.0",
    "ws_port": 6700,
    "use_ws": false,
    "ws_reverse_url": "",
    "ws_reverse_api_url": "ws://127.0.0.1:8080/ws/api/",       // 重点修改
    "ws_reverse_event_url": "ws://127.0.0.1:8080/ws/event/",   // 重点修改
    "ws_reverse_reconnect_interval": 3000,
    "ws_reverse_reconnect_on_code_1000": true,                 // 重点修改
    "use_ws_reverse": true,
    "post_url": "",
    "access_token": "",
    "secret": "",
    "post_message_format": "string",
    "serve_data_files": false,
    "update_source": "global",
    "update_channel": "stable",
    "auto_check_update": false,
    "auto_perform_update": false,
    "show_log_console": true,
    "log_level": "info"
}
```

机器人目录\config.py

```python
from nonebot.default_config import *

HOST = "0.0.0.0"
PORT = 8080                                                   // 要和前面配置一样

DEBUG = False
SUPERUSERS = {}
COMMAND_START = {""}
```

机器人目录\QQbot.py （程序入口）

```python
import nonebot
import config
from os import path

if __name__ == "__main__":
    nonebot.init(config)
    nonebot.load_plugins(path.join(path.dirname(__file__), "awesome", "plugins"), "awesome.plugins")
    nonebot.run()
```

## 正式脚本部分

机器人目录`\awesome\plugins\脚本1\__init__.py`

```python
from nonebot import on_command,CommandSession
from nonebot import get_bot

bot = get_bot()
@on_command("hello", only_to_me = False,  aliases = ("在吗？"))
async def hello(session: CommandSession):
    await session.send("在")
```

# 脚本编写

## 正式脚本部分

机器人目录`\awesome\plugins\脚本1\__init__.py`

```python
from nonebot import on_command,CommandSession
from nonebot import get_bot

bot = get_bot()
@on_command("hello", only_to_me = False,  aliases = ("在吗？"))
async def hello(session: CommandSession):
    await session.send("在")

@bot.on_message("private")   # 修饰符，用on_message注册就只会处理私聊信息，group同理
async def private(ctx):    # 这里的ctx就是上面的session
    pass
```

## Config配置

```
GROUP = [群号]    # 可选
```

# 抓包对象

## session对象

```json
{
    ctx: {
        'font': 对方id
        'message_type': 'private'  # 私有，这里表示私聊信息，群发是group
        'raw_message': '你好'      # 消息内容
        'self_id': 自己id
        'sub_type': 'friend'
        'time': 时间戳
        'user_id': 对方QQ号        # 群发模式下就变成了"group_id" 
        'sender': {               # 发送者
            'age': 对方年龄
            'nicknme': '对方Q名'
            'sex': '对方性别'
            'user_id': 对方QQ号
        }
        'message' [
            {                     # 序列0
                'data': {
                    'text': '对方发送消息内容'
                }
                'type': 'text'   # 消息类型：text
            }
        ]
    }
    self_id: 自己id
}
```

![img](QQRobot.assets/clipboard.png)![img](QQRobot.assets/clipboard-1597730643020.png)

用修饰器时，ctx相当于上面的`session.ctx`

## ctx对象（private修饰器下）

![img](QQRobot.assets/clipboard-1597730668766.png)![img](QQRobot.assets/clipboard-1597730673137.png)

## ctx对象（group修饰器下）

![img](QQRobot.assets/clipboard-1597730690304.png)![img](QQRobot.assets/clipboard-1597730694507.png)

## group无管理员，无to_me

![img](QQRobot.assets/clipboard-1597730758410.png)![img](QQRobot.assets/clipboard-1597730762009.png)

# 自然语言处理NLP

## gensim-自然语言处理（NLP）

> 用于从原始的非结构化文本中，无监督地学习到文本隐居的主题向量表达

## 使用

```python
import jieba
from gensim import corpora, models, similarities
from os import getcwd
```

## 自然语言处理流程

> 遍历字典 > split分隔问题与答案
>
> jieba把语句分隔为词

# 图灵机器人插件（没用）

## 机器人 API

编辑 Code\QQRobot\ 目录下的 QQbot.py，修改其第34行，加入刚刚申请到的图灵机器人 APIkey。

```
tulingkey='图灵 API'
```

## 群监控

编辑 Code\QRobot\ 目录下的 groupfollow.txt，将需要机器人监控、回复的群的名字写入，每行一个群名。(注意 : 中文群名格式为 utf-8。)

## 启动

在 Code\QQRobot\ 目录下执行命令，：

```
$ sudo nohup python2 QQBot.py >qbot.log&
```

如果没有问题，会在当前目录下生成一个名为 v.png 的二维码图片，通过手机 QQ 扫描该图片，完成登陆。

```
$ cat log.log
```

执行可以输出运行 LOG，查看程序运行过程

> 个人api：ed18c4c6271b4a4ab766de15ebf8eb2f

















