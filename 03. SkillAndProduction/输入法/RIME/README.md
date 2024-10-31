# RIME/中州韵/小狼毫/鼠须管

## 资料

参考：

- 官网：https://rime.im/
- 官方文档：https://rime.im/docs/ 或 [github wiki](https://github.com/rime/home/wiki) (是一样的)
- 一些博客：https://docs.nopdan.com/rime/
- 推荐教程：https://www.bilibili.com/video/BV1d64y1a7tS，27:16

说一下这个名字：

- RIME／中州韵输入法引擎。RIME 是一个跨平台的输入法框架
- librime－输入法引擎
- ibus-rime－Linux发行版
- weasel／小狼毫－Windows发行版
- squirrel／鼠须管－Mac发行版
- plum／东风破－配置管理器及输入方案仓库
- essay／八股文－预设词典及语言模型



参考：

- https://docs.nopdan.com/rime/RimeUserGuide.html
  - **建议阅读**
  - 或者直接看会比较好，内容同官方文档，但是经过了层次和顺序整理。看起来更舒服
- https://github.com/rime/home/wiki，不关事的东西有点多，只看Configuration页就可以了
  - 不建议阅读
- 官网目录 (又杂又没顺序)
  - (仅使用)
    - SharedData
    - UserData
    - UserGuide： 用户指南
    - ……
  - (自定义配置用)
    - **Configuration**： 配置相关
    - **CustomizationGuide**： 高级配置相关
    - DictionaryPack： 字典包
    - ……
  - (代码理解用)
    - RimeWithTheCode： 代码
    - RimeWithTheDesign： 设计和实现
    - ……
  - (特殊)
    - SpellingAlgebra： 拼寫運算
    - ……
  - (没啥用)
    - Home
    - ComboPinyin： 宫保拼音
    - ComboPinyinKBCon： 宫保拼音
    - Downloads： 下载输入法
    - FAQ
    - GerringStarted
    - Introduction
    - ……

## 快速入门

https://www.bilibili.com/video/BV1d64y1a7tS

### 安装教程及注意事项

会在这个位置找到链接形式的目录索引：C:\ProgramData\Microsoft\Windows\Start Menu\Programs\小狼毫输入法
（补充1：也可以通过安装后右键程序图标打开所在位置的方式定位到）
（补充2：之所以要找这个**链接索引路径**，是因为他们的物理路径是分散的）
（补充3：虽然通过右键右下角的图标也能够定位，但没这个方便）

- (主要，自定义过程中会一直使用)
  - **【小狼毫】输入法设定**： 比较重要
  - **【小狼毫】用户文件夹**： 会备份到备份文件夹里
  - 【小狼毫】重新部署： 修改完配置需要用
- (低频，平时不用)
  - 【小狼毫】用户资料同步： (不知道)
  - 【小狼毫】程序文件夹： 程序位置
  - 【小狼毫】用户词典管理： 自定义词库一般用不到
  - 【小狼毫】检查新版本
  - 【小狼毫】说明书：没什么内容，不如看文档
  - 【小狼毫】安装选项： 就安装用一次
  - 小狼毫算法服务： (不知道)
  - 卸载小狼毫

### 配置自定义短语

{用户文件夹}/Custom_phrase.txt

```bash
# 注意一定要用tab间隔而不能是空格，否则会有bug：首候选时只会显示首选
test@gmai.com	e	1
test@qq.com	e	2
sougou	s	1
```

### 配置同步文件夹

{用户文件夹}/installation.yaml： 设置里面的 sync_dir 字段

```bash
sync_dir: 'E:\Backup\xxx' # 不支持中文
```

### 添加自定义词库/词典

例如新建一个输入法，名为：luna_pinyin，那么：

1. 新建配置文件：{用户文件夹}/luna_pinyin.custom.yaml

   ```yaml
   path:
     engine/translators:
       - punct_translator
       - reverse_lookup_translator
       - script_translator
       - table_translator@custom_phrase
       - table_translator
     "translator/dictionary": eddywang # 最主要是这行，引入一个词典文件，例如这里引入同路径下的 eddywang.dict.yaml
   ```

2. 新建词典文件：{用户文件夹}/eddywang.custom.yaml

   ```yaml
   ---
   name: eddywang
   version: "2017.03.31"
   sort: by_weight
   use_preset_vocabulary: true
   import_tables: # 词典可以嵌套引入词典
     - luna_pinyin
     - sougou_eddy
     - SougouStandard
     - SougouOnlineNewWords
   ...
   ```

举例：{用户文件夹}/default.custom.yaml

```yaml
customization:
  distribution code name: Weasel
  distribution version: 0.14.3
  generator: "Rime::SwitcherSettings"
  modified time:"Sun Aug 29 19:30:10 2021"
  rime version: 1.5.3
patch:
  "ascii composer/switch key":
    Caps Lock: commit code
    Control L: commit code
    Control R: noop
    Shift L: noop
    Shift R: noop
  "menu/page size": 9
  schema list:
    - {schema: luna pinyin}
    - {schema: terra pinyin}
```

## 实例 - 配置小鹤





















