# WindowsActivate

# 目录

**参考**

[**https://bbs.kafan.cn/thread-2171120-1-1.html**](https://bbs.kafan.cn/thread-2171120-1-1.html)

# windows激活

## KMS前提

kms激活的前提是你的系统是批量授权版本，即VL版，一般企业版都是VL版，专业版有零售和VL版，家庭版旗舰版OEM版等等那就肯定不能默认直接用kms激活。一般建议从[msdn我告诉你](http://www.itellyou.cn/)上面下载系统，这里放个图举例说明哪些是VL版本：

![img](WindowsActivate.assets/clipboard-1613756248412.png)

## windows激活

三行激活

- `slmgr /skms kms.03k.org`，把kms服务器地址设置（set kms）为kms.03k.org，设置成功弹窗
- `slmgr /ato`，激活
- `wmic os get caption`，查看系统版本

一行激活

**其实一行就行（要点个确认）**

- `slmgr /skms kms.03k.org`

## 解决报错：软件授权服务报告无法激活计算机

- `win+R`，输入`services.msc`并回车，进入“服务”界面
- 确保`software protection`服务为开启
- 日期设置为当前时间

# Office激活

**以激活 Office Professional Plus 2019 版本为例，打开 cmd，输入**

- `cd C:\Program Files\Microsoft Office\Office16`，进入到 Office 目录，目的是为了找到 ospp.vbs

    注意这里不是office程序位置！而是ospp位置，没有/root/

- `cscript ospp.vbs /inpkey:NMMKJ-6RK4F-KMJVX-8D9MJ-6MWKP`，安装 KMS 秘钥

- `cscript ospp.vbs /sethst:kms.library.hk`，设置 KMS 服务器

- `cscript ospp.vbs /act`，激活

- `cscript ospp.vbs /dstatus`，查看激活状态

**注：KMS 不是永久激活，180 天后会过期，记得在到期前再重新激活下**

`cscript ospp.vbs /act`

**最新可用的 KMS 服务器，用前 ping 一下，看看能用不**

ss.byelliot.top kms.03k.org kms.chinancce.com (√) kms.lotro.cc cy2617.jios.org kms.shuax.com kms.luody.info kms.cangshui.net zh.us.to 122.226.152.230 kms.vtrois.com kms.digiboy.ir kms.library.hk kms.91ssr.top kms.bluskai.com

**更多命令，参考** [**ospp.vbs**](https://link.zhihu.com/?target=https%3A//wenku.baidu.com/view/b34254a965ce05087632135c.html)**。**

**小白用户推荐用 HEU KMS Activator 工具激活。**

## 个人的一点感想

![img](WindowsActivate.assets/clipboard-1613756319998.png)

https://bbs.kafan.cn/thread-2171120-1-1.html

![img](WindowsActivate.assets/clipboard-1613756328306.png)

![img](WindowsActivate.assets/clipboard-1613756336573.png)

感想补充：

分析看来这东西其本质也还是KMS

我本来主要是想看下是不是有其他不同的破解方法，毕竟这玩意儿从开始就没有真正意义的破解版，人家批量授权版本也只是让你故意钻的漏洞。

KMS本来就不太算是违反规则的手段，类似于批量序列号一样。

反正我怀疑微软都是在钓鱼，人家真正想封锁不让你用的话还是拿人家没办法......气抖冷

_

虽说说起来出售的合法整机本来就会帮你买windows（虽然一般不帮你买office），我也不能说自己用的是盗版，我自己刷机又是另外一回事了，那边应该也不太在意这个

 