# README

（该笔记基于 V3.3.7491）

## 数据库文件夹的路径问题

数据库文件夹和资源文件夹可以不在同一个位置，即前者所指向的路径是绝对路径。
（虽然可以把他两放在一起，但数据库的路径依然是绝对路径，哪怕使用 “重新映射音乐文件夹” 功能也不能修改为相对路径）我认为放一起会更好

所以，每次迁移音乐文件夹，都需要对音乐文件夹进行 “重新映射”，这很难受

## 数据库文件夹的内容

先来分析下目录：

（这是我自己的音乐库，1663个文件，30.7GB）

[dir]

- < FileName,  Size,  Detail
- //,  7.33MB
  - Podcasts/,  26B,  似乎是广播
    - Subscriptions.dat,  26B
  - MusicBeeLibrary.lyrics,  3.9MB,  歌词 (一个插件的功能)
  - MusicBeeLibrary.mbl,  1.7MB,  **主要数据库**
  - ~~MusicBeeLibrary.bak~~,  1.7MB,  (上一个文件的备份)
  - ~~MusicBeeLibrary.pfidx~~,  4B,  空的，不知道干嘛用
  - MusicBeeLibrarySettings.ini,  3.71KB,  配置
  - ~~MusicBeeLibrarySettings.bak~~,  3.71KB,  (上一个文件的备份)
  - NowPlaying.mbp,  1.10KB,  记录当前正在播放的曲目和位置等

## 数据库文件的内容

前面我们看到了 MusicBeeLibrary.mbl 是主要的音乐库数据库，当我们在 MusicBee 中选择 "打开新的数据库" 时，也是让你选择 `.mbl` 扩展名的文件

这个扩展名应该是自定义的，MBL 是 **M**usic**B**ee**L**ibrary 的意思

记事本打开内容，可以发现是半明文的，可读的

不过我当前的音乐库有很多中文，而且文件较多。有空新建个新库再去分析一下内容
