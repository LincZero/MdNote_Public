# Github SSH Key

## 检查是否生成过

在开始菜单中打开git下的git bash（当然，在其他目录下打开git bash也是一样的），然后执行

```bash
ls -al ~/.ssh
```

如果能进入到.ssh文件目录下 ，则证明，之前生成过.ssh秘钥，可以直接使用里面的秘钥（看有无 id_rsa.pub 文件）

注意：这里的 .ssh 目录实际位置在：`C:\Users\用户名\.ssh`

## 生成本地 Key

> #### 先配置

如果不能进入到.ssh文件目录下，则：

检测下自己之前有没有配置：

```lua
git config user.name 和 git config user.email（直接分别输入这两个命令）
```

如果之前没有创建，则执行以下命令：

```verilog
git config –global user.name ‘xxxxx’ 
git config –global user.email ‘xxx@xx.xxx’
```

此时会完善 .ssh/config 文件

> #### 然后生成秘钥

```bash
$ ssh-keygen -t rsa -C ‘上面的邮箱’                             # 执行完这个后敲三次回车
Enter file in which to save the key (/c/Users/A/.ssh/id_rsa): # <== 密钥文件默认存放位置，按Enter即可
Enter passphrase (empty for no passphrase):					  # <== 输入密钥锁码，或直接按 Enter 留空
Enter same passphrase again:                                  # <== 再输入一遍密钥锁码，继续 Enter为空

Your identification has been saved in /root/.ssh/id_rsa.      # <== 生成的私钥
Your public key has been saved in /root/.ssh/id_rsa.pub.      # <== 生成的公钥
The key fingerprint is:
SHA256:K1qy928tkk1FUuzQtlZK+poeS67vIgPvHw9lQ+KNuZ4 root@localhost.localdomain
The key's randomart image is:
+---[RSA 2048]----+
|           +.    |
|          o * .  |
|        . .O +   |
|       . *. *    |
|        S =+     |
|    .    =...    |
|    .oo =+o+     |
|     ==o+B*o.    |
|    oo.=EXO.     |
+----[SHA256]-----+

$ ls -al ~/.ssh												  # (可选) 检查下新增的文件
total 27
drwxr-xr-x 1 A 197121    0 10月 24 21:40 ./
drwxr-xr-x 1 A 197121    0 10月 17 21:43 ../
-rw-r--r-- 1 A 197121   52  7月 27 08:59 config
-rw-r--r-- 1 A 197121 2602 10月 24 21:40 id_rsa               # 私有秘钥
-rw-r--r-- 1 A 197121  570 10月 24 21:40 id_rsa.pub           # 公有密钥
-rw-r--r-- 1 A 197121  359  7月 25 00:07 known_hosts
```

补充一下命令的参数解释：

```bash
-t 指定密钥类型，默认是 rsa ，可以省略。
-C 设置注释文字，比如邮箱。
-f 指定密钥文件存储文件名。
```

## Github中注册 Key

如果想登陆远端，则需要将rsa.pub里的秘钥添加到远端。

首先，去.ssh目录下找到 id_rsa.pub 这个文件夹打开复制全部内容。

接着：

1. 登录GitHub，进入你的Settings
2. 会看到左边这些目录，点击SSH and GPG keys会看到左边这些目录，点击SSH and GPG keys
3. 点击Add SSH key
4. 再弹出窗口，输入你的GitHub密码，点击确认按钮。
5. 到此，就大功告成了。













