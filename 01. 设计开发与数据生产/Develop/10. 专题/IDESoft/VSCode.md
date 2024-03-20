# VSCode

# 目录

# VSCode

## 提升效率



## 快捷键

| 快捷键       | 功能                                                |
| ------------ | --------------------------------------------------- |
| F1           | 打开VSCode命令行（不是cmd命令行），往往配合插件使用 |
| Ctrl+Shift+P | 编辑器设置的命令行                                  |



## VSCode摸鱼

百度就会给你介绍很多花式摸鱼的VS插件

比如

- QQ，能让你在VSCode里聊QQ
- 小霸王
- daily anime，追番



## 大纲显示的筛选

优化大纲显示

① 首先我觉得排序依据选位置会好一点（默认是根据类型）

② 其次，如何在VS代码中配置python大纲模式以仅显示类和方法？

<kbd>CtrlShift</kbd> + <kbd>P</kbd>，输入：`Perferences: Open Settings (JSON)`（首选项：打开设置 (json) ）添加或修改代码：

```json
// 推荐屏蔽项：
"outline.showVariables": false,  	// 只显示到函数名，看不到变量（包括全局和类/函数的局部），图标是蓝色的[]中间有个cube
"outline.showProperties": false,	// {}里键值对的键就不显示了，图标是个灰色板手
"outline.showFunctions": false,     // ？包括方法内隐式定义的callback匿名函数，图标和类方法一样，是个紫色的cube
```

其他扩展选项：（但是话说怎么没有 outline.showVariables 项）

```json
outline.showArrays
outline.showBooleans
// outline.showClasses		// class 类，刚需
outline.showConstants
outline.showConstructors
outline.showEnums
outline.showEvents
outline.showFields
outline.showFiles
outline.showFunctions		// 函数，也包括匿名函数在内，按需打开。图标和类方法一样，是个紫色的cube。
// outline.showInterfaces	// interface 接口，图标是蓝色的一空一实心的，刚需
outline.showKeys
// outline.showMethods		// 类方法，刚需
outline.showModules
outline.showNamespaces
outline.showNull
outline.showNumbers
outline.showObjects
outline.showOperators
outline.showPackages
outline.showProperties		// {}里键值对的键就不显示了，图标是个灰色板手
outline.showStrings
outline.showStructs
outline.showTypeParameters
```

我的

```json
"outline.showVariables": false,     // 大纲视图只显示到函数名，按需打开
"outline.showProperties": false,    // 属性

// 只看类则删掉注释
// "outline.showFunctions": false,   // 函数，也包括匿名函数在内，按需打开
// "editor.columnSelection": false,   // 

// "outline.showMethods": false,    // 类方法，刚需
// "outline.showClasses": false,    // class 类，刚需
// "outline.showInterfaces": false, // interface 接口，刚需
```

