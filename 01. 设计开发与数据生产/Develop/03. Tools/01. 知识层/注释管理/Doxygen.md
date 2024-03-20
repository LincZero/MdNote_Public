# Doxygen

# 目录

# Doxygen

安装和使用教程：https://www.jianshu.com/p/1191b0cc6ae2（配合软件面的截图翻译，应该都能懂）

# 专题

## 画图技巧

参考：

- GrapViz类图和函数调用图： [Windows下使用Doxygen+GrapViz生成类图和调用图](https://blog.csdn.net/u014213012/article/details/123064358)
- 函数调用图： [Doxygen 终于可以正确生成函数调用图了！](https://whatacold.io/zh-cn/blog/2021-02-16-doxygen-cpp-correct-callgraphs/)
- UML类图： [使用 Doxygen 从源代码生成 UML 类图](https://zhuanlan.zhihu.com/p/571965687)



踩坑：如果需要GrapViz要另外安装，否则无法生成图。函数调用图GrapViz可以画，而原生的不能

## 样式技巧





## Markdown技巧





# DoxyFile && 使用流程

个人常用流程：

## 使用需知

（该Doxygen生成流程基于Windows平台上，其他平台可能需要自行调整，但有Doxyfile应该能保持一致性，问题不大）

1. 安装Windows Doxygen，然后导入Doxyfile
2. 安装GrahViz (不使用默认的Diagram，为了能画更复杂的调用图)
3. 修改Wizard>Project里的 `Source code directory`、`Destination directory`，分别是源码目录和输出目录
4. 切换到Run选项卡，按Run doxygen就可以了。结束后可在输出目录或按Show HTML进行查看

## 一些修改过的选项

想要查看 Doxyfile文件 修改过的内容，更推荐借助Doxygen软件的Expert查看。实时性更强
（防止修改者修改内容后忘了更新.md）

```python
# 画图类
HAVE_DOT = YES        # 告诉 Doxygen ，您的系统已经安装了Graphviz。Graphviz是一套提供了dot语言解释的开源图形可视化软件
UML_LOCK = YES        # 改变所生成的类图的外观，使其更像UML风格。其主要改变内容包括：隐藏非公有的属性和方法，展示类间的继承和包含关系等。
CALL_GRAPH = YES     # 是否绘制函数的调用图
CALLER_GRAPH = YES # 是否绘制函数的被调用图

# 其他类
JAVADOC_AUTOBRIEF = YES # 会在类的Member Functions和Attributes表格处显示 Brief
EXTRACT_PRIVATE = YES # 获取私有方法和成员。默认关闭，如果打包库确实不需要，但这个文档的目的是方便开发，看私有是需要的
EXCLUDE_PATTERNS = */src/utils # 排除的文件夹的路径
```

# 注释补充

## 文件注释

文件头部加上以下代码

```cpp
/**
 * @file CTestBase.h
 * @author L
 * @brief 测试基类
 * @date 2023-5-31
 */
```

## 文件夹注释

可以写在文件夹中的任何文件中，但通常建议在文档文件或者文件夹中的主文件中添加 ("README"或"documentation"或与文件夹同名的文件?)，以帮助其他人更容易地找到它。

```cpp
/**
 * @dir /path/to/folder
 * @brief A brief description of the folder.
 * @details A more detailed description of the folder.
 */
```

## 类注释或代码注释

```cpp
1. 普通注释
/**
 * 检测通信联通状态.
 * @param timeout (int)
 *   单位(ms), 等待超时时间.
 * @return (double)
 *   - On success, latency, unit(ms).
 *   - On failure, -1.
 */
int check_comm(int timeout);

2. brief省略版（下面两个等价）
    
/// start function
virtual void start(); 
    
/// \brief start function
virtual void start();

3. brief与detail省略版（下面两个等价）。
需要注意需要有一个空行，否则都将视为brief，内容过长不规范。除非下面有@标识，则不需要空行

/**
 * This is the brief description for the function.
 * 
 * This is more detailed description about the function, which provides further
 * information about its purpose, usage, and behavior. You can continue writing
 * this detailed description for as long as needed.
 */
virtual void someFunction();

/**
 * @brief This is the brief description for the function.
 * 
 * @detail This is more detailed description about the function, which provides further
 * information about its purpose, usage, and behavior. You can continue writing
 * this detailed description for as long as needed.
 */
virtual void someFunction();
```





























