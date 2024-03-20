# Qt

# 目录

# QML 设计器

## 简概

### 创建

创建QML见：简概 > 开发流程 - 创建，有两种创建方式

- QML File (Qt Quick 2)，创建`.qml`QML文件
- QtQuick UI File，创建两个文件 `xxx.qml` `xxxFrom.ui.qml`



### 编辑

编辑QML：

- 双击`xxx.qml`文件是文本编辑（**QMLJS 编辑器**），右键 > 用…打开 > **Qt Quick Designer 编辑器**，是可视化编辑
- 或者在文本编辑状态下，按 Qt Creator 左侧的 “设计”
- 双击`xxxForm.ui.qml`文件倒是直接可视化编辑



### QML Designer

不能放入 Qt Designer 中编辑，需要开启一个插件（默认已经开启了），帮助 > 插件 > Qt Quick > QmlDesigner



Qt Quick Designer 界面有八个大窗格：左侧三个，中间三个，右侧两个。功能分别是：

- 左上，Library，QML控件资源库
- 左中，Projects，项目资源管理器
- 左下，Navigator，控件层次导航
- 中上（这个东西不见了 !!!）
  - Text Editor，文本编辑器
  - Form Editor，可视化编辑器
- 正中
  - States，状态
  - Timeline，时间线
- 中下，Output Pane，应用程序输出
- 左上，Properties，属性编辑
- 左下，Connection View，连接视图



如果你需要修改他们：菜单 View > 视图 > 



## 编辑demo

### QML File

(Qt Quick 2)



Demo.qml

```js
import QtQuick 2.0

Item {

}

```



### QtQuick UI File

(Qt Quick 2.4)



Demo.qml

```js
import QtQuick 2.4

DemoForm {
}

```

DemoFrom.ui.qml（主要编辑这个文件）

```js
import QtQuick 2.4

Item {
    width: 400
    height: 400
}

```



## Bug

### Window Root 时无法显示

下面的方法都没用，后来我是直接更新软件解决的

- 更新前：4.14.0，Based on Qt 5.15.2 (MSVC 2019, 64bit)，Built on Dec 17 2020 07:57:20
- 更新后：9.0.0，Based on Qt 6.4.0 (MSVC 2019, x86_64)，Built on Nov 9 2022 13:01:49

> 解决方法：https://forum.qt.io/topic/124259/item-could-not-be-created/28，https://stackoverflow.com/questions/67369304/how-to-fix-line-1-qt-quick-emulation-layer-crashed
>
> 菜单 工具 > 选项 窗口 > Qt Quick > Qt Quick Designer / Qt Quick 设计器 > QML Emulation Layout / QML 仿真层 > 切换到第二个单选项，并复制第一个选项的路径下来
> 然后要重启QT
>
> “这不是解决办法。  它将为您提供有关仿真崩溃发生原因的调试信息。  您通常可以根据调试输出找出如何停止崩溃。  我应该使用任何版本的 Qt。 ” – [大卫·K·赫斯 ](https://stackoverflow.com/users/1055722/david-k-hess)                
>
> 我切换之后的再启用设计页面，会有红色字：
> the qml emulation layer cannot be build. the failback emulation layer, which does not support all feature, will be used
>
> Open error output file 后：
>
> ```
> 
> jom 1.1.3 - empower your cores
> 
> jom: C:\Users\A\AppData\Local\Temp\QtCreator-lfXijL\qml-puppet-build.jkawuH\Makefile.Release [release\qt5previewnodeinstanceserver.obj] Error 2
> jom: C:\Users\A\AppData\Local\Temp\QtCreator-lfXijL\qml-puppet-build.jkawuH\Makefile [release] Error 2
> 
> ```
>
> _
>



















































