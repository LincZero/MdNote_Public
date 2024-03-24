# PyQt_Node_Editor

参考

- github有个https://github.com/paceholder/nodeeditor，但是用了CMake，我不会CMake......跑不起来（2024的我：hhhh，我当年居然不会，笑死了，明明跑起来这个东西就能走少很多弯路了，不过也好，一步一步开发理解也更深了）

- [【Youtube】Node Editor Tutorial](https://www.youtube.com/watch?v=YV1mEYd7nyM&list=PLZSNHzwDCOggHLThIbCxUhWTgrKVemZkz)（目前学习进度：P51end/62，跳过：34~39。这里的数字是分p而非章节名））
  不过这个教程使用的是 PyQt，但换成PySide无伤大雅
  作者的网站：https://www.blenderfreak.com/tutorials/node-editor-tutorial-series/

  My Watched Note：

  - 32，不可用action变灰色
  - 52，点击节点高亮 (自动选择) 所有连接边
  - 53，拖拽线方式创建节点（创建节点的三种：右键/拖拽菜单/拖拽线）
  - 54，自动生成文档和使用文档注释，pip install Sphinx
  - 55，提高可复用性和修复bug，版本管理的可视化（Version Control窗口、Event Log窗口）
  - 56，同上
  - 57，同上
  - 58，修复边缘的问题
  - **59，体系结构概述，总结（还分章节了）**
  - **60，教程总结（还分章节了）**
  - 61，添加重路由边的功能（同blender效果）
  - 62，向Socket添加捕捉（同blender效果）
  - 国内观后笔记：https://blog.csdn.net/mahuatengmmp/article/details/118070362

- Qt Example 中有个比较类似的示例，叫 “elasticnodes”，使用的类

  ```c++
  #include <QGraphicsItem>
  #include <QGraphicsView>
  #include <QGraphicsScene>
  #include <QGraphicsSceneMouseEvent>
  #include <QPainter>
  #include <QtMath>
  ```

  

