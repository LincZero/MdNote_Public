# 源码阅读

## 技巧

（个人版）

1. 必须先熟悉业务，熟悉每个功能
2. 查看有无最小demo，如一些源码中的demo/example文件夹
3. 借助工具阅读，查看调用关系

## 工具

- 支持注释管理类

  - C/C++/Java：建议Doxygen
  - Python：有几个工具：
    - Pydocs，自带，效果：https://blog.51cto.com/mouday/3041655
    - Sphinx，老牌，效果：https://bbs.huaweicloud.com/blogs/255646，用的人似乎比较多
    - MkDocs，新的
  - TSDoc / JSDoc：官网：tsdoc.org，参考：https://juejin.cn/post/7140337202097029133

- 支持查看调用关系

  - （前面提到的基本支持）

  - Source Insign：老牌，主要读C语言的，收费，试用30天

- 其他冷门未详细调研的

  - Sourcetrail：开源
  - calltree
  - Code2Flow：适合读 Python/Js/Ts 这种动态语言，试用15天。但只能单文件，有些简陋，不好用
  - www.coderead.cn（内测，主要是Java，之前逛B站看过，但没具体用过）

- vscode 读源码插件（未详细调研）

  - CodeTour：独立于源码外添加注释，不污染源码
  - 「Go to Definition」和「Peek Definition」：定位到定义
  - Sourcetrail：编辑区右键使用
  - Call Graph：可以查看一个函数的call in和call out，CS+P callgrapht 或编辑区右键都能使用
  - 不是读源码的但顺便记一下：
    - EditorConfig for VS Code：.editorconfig 让每个人使用相同的代码风格，有些类似 .clang-format

