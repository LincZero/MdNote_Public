# 比较桌面开发框架

## 常用的各语言的跨平台GUI开发工具

Java：桌面是SE，移动设备是ME，网站是EE

-   比较常用的：
    java.awt
    java.swing
    还有swt，eclipse官方封装了一套swt
-   安卓应该awt和swt多点，桌面可能swing会多点

C#

-   WPF（基于 .NET Framework 3.0。Windows only 的话就选WPF）



MFC（没饭吃，据说上手难度低，界面不太好看）
简单只支持windows平台，现在社区也不是很活跃，开发挺容易上手的，但好多地方不明不白的，只是说明只能这么用；



QT（嵌入式适合）





## QT vs WPF























## Qt vs Electron

参考：https://www.zhihu.com/question/53230344



产品一览

Qt

- wps
- yy语音
- VirtualBox
- 部分adobe的桌面工具
- Maya



Electron
（基本都在C盘，例如 C:\Users\用户\AppData\Local\Programs(不一定有这一层)\软件，然后文件夹里有个 `LICENSE.electron.txt` 的都是）

- 文本编辑类居多
  - Obsidian
  - Notion
  - VSCode
  - Typora
- 业务类
  - 钉钉
  - slack
- 和网络相关的
  - 八爪鱼
  - Fiddler Everywhere
  - Genshin_Wish_Export
  - BaiduNetdisk
  - Unity Hub
  - GitHubDesktop（不确定）
- 超轻量
  - UTools
- Bridge
- VIA
- XMind ZEN
- NeatReader
- EPUB_NeatConverter



[native方案](https://www.zhihu.com/search?q=native方案&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A134482729})（Qt，WPF等）适合于高性能的专业应用，
Electron适合想要把网页版和桌面端共享代码，同时对性能没有苛刻要求的场景。

如果不在乎成本，native一定是体验更好的（微信），
但是如果认为桌面端复用网页版的体验也能接受，那Electron成本会更低一些。



## 一些GUI和数据的模式



### mvc



### mvvc



## 补充：什么是native

原译：原生、本土出生、本地的

Native APP指的是**原生程序，一般依托于操作系统，有很强的交互，是一个完整的App，可拓展性强，需要用户下载安装使用**。





























