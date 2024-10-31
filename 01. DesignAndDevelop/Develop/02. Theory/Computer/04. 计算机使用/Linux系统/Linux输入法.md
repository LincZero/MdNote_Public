# Linux中文输入法

==（Linux的输入法太坑了，特别是Ubuntu，坑多，感觉和中文输入兼容不好……）==

（另外就是20版本和22版本的操作也有所区别。

1. 20更麻烦点，还要在语言设置里逐个添加语言
2. 22有Fcitx4，更方便）

## 三大框架

- ibus
  - 自带，传统
- fcitx
  - 功能较多，扩展更强
- fcitx5
  - fcitx super

### 查看与切换输入法框架

桌面版的话（需要输入法的应该都是桌面版的），右上角设置 > 区域和语言 > 管理已安装的语言 > 语言面板的 “键盘输入法系统”

默认应该是 `IBus` (似乎是中文状态下进入这个面板自动安装的)，可以切换成：XIM 和 fcitx（忘了fcitx在安装之前有没有这个选项了）

### IBus

### XIM

### fcitx

安装方式见：https://fcitx-im.org/wiki/Install_Fcitx_5/zh-cn，有三种方式：

- 从Linux发型版安装Fcitx5
- 从Flatpak安装Fcitx5
- 从源码安装Fcitx5

这里一般我们使用第一种方式，另两种自行了解



链接原文：

> 您需要从自己的软件包列表中搜索指定的Fcitx包。Fcitx 5软件包的名称中通常包含“fcitx5”。
>
> 截至今天，除了一些滚动发行版，fcitx5尚未在发行版存储库中普遍可用。
>
> 下面是一些在您使用的发行版中搜索 Fcitx5 软件包的示例。 您还可以使用桌面提供的 GUI 软件中心，例如 gnome-software（GNOME）或Plasma-discover（KDE）发现。
>
> ```bash
> yum search fcitx5 # CentOS
> dnf search fcitx5 # Fedora
> pacman -Ss fcitx5 # Archlinux
> zypper search fcitx5 # OpenSUSE
> apt-cache search fcitx5 # Debian/Ubuntu
> ```
>
> 或者 [pkgs.org](https://pkgs.org/search/?q=fcitx5) 提供一个在不同发行版中搜索软件包的简单方法。 请注意可能有一些版本为0.0～git这样的包，这种版本是一些相当老的版本，比最老的Fcitx5稳定发布版本还要老。通常不建议使用这种版本的Fcitx5.
>
> pkgs.org 也会提供针对不同发行版的特定安装命令。
>
> 一个基本的fcitx5安装包括：
>
> - [fcitx5](https://pkgs.org/search/?q=fcitx5), 主程序
> - [fcitx5-gtk](https://pkgs.org/search/?q=fcitx5-gtk), [fcitx5-qt](https://pkgs.org/search/?q=fcitx5-qt), 针对最受欢迎的几种UI开发工具包的输入法模块。
> - [fcitx5-configtool](https://pkgs.org/search/?q=fcitx5-configtool), GUI配置程序。
> - 对于不同语言，有许多的输入法引擎
>   - 参见 [输入法引擎](https://fcitx-im.org/wiki/Special:MyLanguage/Input_method_engines)
>
> 一些额外的插件和主题支持：
>
> - [fcitx5-lua](https://pkgs.org/search/?q=fcitx5-lua), 提供lua脚本支持
> - [fcitx5-material-color](https://pkgs.org/search/?q=fcitx5-material-color), 一个Fcitx5漂亮主题的合集
>



版本问题：（尝试）

- ubuntu20 好像 `apt install fcitx` 就只是fcitx版本
- ubuntu22 我下载搜狗和百度输入法后好像是fcitx4
- ubuntu22 好像 `apt install fcitx5 fcitx5-rime` 后则是fcitx5版本（ubuntu20好像会找不到 `fcitx5-rime`）

这几个版本之间似乎会互相冲突

## 输入法

### 自带 (iBus)

切换中文语言环境后，打开 (设置 > 区域和语言 > 管理已安装的语言 > 语言面板的 “键盘输入法系统”) 那块，会自动安装。

BUG：不知道为什么，自带的总是不管用。

### 搜狗 (基于fcitx4)

`uname -m` 看是什么架构的，然后去搜狗官网下对应的 `.deb`，然后双击或命令行安装便是

不过我安装搜狗的时候似乎出现bug，不知道为什么

> 1. “搜狗是给16.04做的，后来是没更新过还是很敷衍来的，bug多正常。用rime和pinyin就不会了”
> 2. “用搜狗输入法同样遇到这个问题。最后装了谷歌输入法。”



官方教程：https://shurufa.sogou.com/linux/guide

可以使用命令行方式：

```bash
sudo dpkg -i sougoupinyin_版本号_amd64.deb
# 如果安装过程中提示缺少相关依赖，则执行如下命令解决：
sudo apt -f install
```



**（前面的方案都不行，最后我的解决方案是：切换到ubuntu22版本，用火星应用下载，然后切换成fcitx4，再重启电脑）**

### RIME

通用下载链接：https://rime.im/download/

其中 Linux 有几种，官方说明：

> - ibus-rime
>  - 基於 IBus 輸入法框架。
>     請 [查看](https://github.com/rime/home/wiki/RimeWithIBus) 各 Linux 發行版安裝說明，或從源碼編譯安裝。
> - fcitx-rime
>  - *（第三方軟件）* 基於 Fcitx 輸入法框架的 [fcitx-rime](https://github.com/fcitx/fcitx-rime)，由 Fcitx 團隊開發和維護。
> - fcitx5-rime
>  - *（第三方軟件）* 基於 Fcitx5 輸入法框架的 [fcitx5-rime](https://github.com/fcitx/fcitx5-rime)，由 Fcitx 團隊開發和維護。查看 [安裝方式](https://fcitx-im.org/wiki/Install_Fcitx_5/zh-cn) 

#### ibus-rime

这个比较简单

参考：

- [VLOG 93 | 如何在Linux系统下安装RIME中州韻輸入法？(Ubuntu) | 开源免费中文输入法推荐](https://www.bilibili.com/video/BV1LJ411U78i)
- [跨平台、无隐私追踪的开源输入法Rime定制指南: 聪明的输入法懂我心意!](https://www.bilibili.com/video/BV12M411T7gf/)



Rime 已收錄於 [Ubuntu 12.10 (Quantal Quetzal)](http://old-releases.ubuntu.com/releases/12.10/) 及以上版本

```bash
sudo apt-get install ibus-rime
```

安裝更多輸入方案：（推薦使用 [/plum/](https://github.com/rime/plum) 安裝最新版本）

```bash
# 朙月拼音（預裝）
sudo apt-get install librime-data-luna-pinyin
# 雙拼
sudo apt-get install librime-data-double-pinyin
# 宮保拼音
sudo apt-get install librime-data-combo-pinyin
# 注音、地球拼音
sudo apt-get install librime-data-terra-pinyin librime-data-bopomofo
# 倉頡五代（預裝）
sudo apt-get install librime-data-cangjie5
# 速成五代
sudo apt-get install librime-data-quick5
# 五筆86、袖珍簡化字拼音、五筆畫
sudo apt-get install librime-data-wubi librime-data-pinyin-simp librime-data-stroke-simp
# IPA (X-SAMPA)
sudo apt-get install librime-data-ipa-xsampa
# 上海吳語
sudo apt-get install librime-data-wugniu
# 粵拼
sudo apt-get install librime-data-jyutping
# 中古漢語拼音
sudo apt-get install librime-data-zyenpheng
```

安装完后，依然是回到 设置 > 区域和语言，点管理检查是否iBus框架，点加号选择刚安装的输入法。如果没有看到尝试重启电脑

#### fcitx5-rime

参考：[Fcitx5 rime安装记录](https://www.bilibili.com/video/BV1Gb4y1V7FS)

```bash
# 卸载之前的ibus-rime版本，排除干扰。若之前没装过可忽略
sudo apt purge ibus ibus-rime
sudo apt autoremove

sudo pxy apt install fcitx5 fcitx5-rime
```

## Bug

### 安装和使用输入法后，还是英文

解决：可以尝试切换输入法框架到对应的iBus、fcitx，再重启。还有就是20我都没弄成功，22的搜狗、百度、fcitx5-rime才弄成功了

### fcitx冲突

搜狗、百度 似乎基于 fcitx4，然后我安装完是可以用的。

再后来我安装了fcitx5-rime，然后在切换输入法框架那里fcitx4选项就消失不见了，搜狗和百度输入法也用不了了

## AutoHotKey问题

我个人输入法高度定制，还会依赖AutoHotKey，但问题在于这个东西只支持Windows版本……

似乎有是有其他代替品，但脚本什么的都要重新写……崩溃



