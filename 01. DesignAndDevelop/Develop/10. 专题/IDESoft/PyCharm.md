# PyCharm

# 目录

# PyCharm

## 运行与调试

### 进入venv的方法

两行代码：

```shell
cd venv/scripts
activate
```

然后就可以在终端中：

```shell
python xxx.py
```

该方法不能进入调试，最好使用 设置run时使用虚拟环境 的方法

### 设置run时使用虚拟环境

其实就是设置run时，自动使用venv/Scripts中的python.exe

![setPyCharmRun](PyCharm.assets/setPyCharmRun.png)

或者，将在setting > Project xxx 里改

![image-20220423015544407](PyCharm.assets/image-20220423015544407.png)



#### 四种解释器环境

Add Python Interpreter 有四个选项

| 选项                   | 翻译        | 大小                    | 作用                                                         |
| ---------------------- | ----------- | ----------------------- | ------------------------------------------------------------ |
| Virtualenv Environment | 虚拟环境    | 虚拟环境<br />6MB左右   | 默认路径：`工程路径\venv`，<br />基于解释器路径：`任一python.exe路径` |
| Conda Environment      | Conda环境   | 虚拟环境<br />100MB左右 | 默认路径：`Anaconda安装路径\envs\项目名`，<br />exe路径：`Anaconda安装路径\Scripts\conda.exe` |
| System Interpreter     | 系统解释器  | 系统环境                | 默认路径：`MicrosoftVS安装路径\SDK_and_Tools\……\python.exe`  |
| Pipenv Enviroment      | Pip虚拟环境 | 虚拟环境                | 基于解释器路径：`任一python.exe路径`，<br />exe路径：`可能是Pipenv.exe吧？没用过不清楚` |

补充

> 其中，`任一python.exe路径`，可以是
>
> - Anaconda安装路径\python.exe
> - MicrosoftVS安装路径\SDK_and_Tools\Python37_64\python.exe
> - C:\Program Files\python\python.exe

选择

> 虽然没有都用过，但是选项1将虚拟环境放在工程内部，分享起来是比较方便的。而且默认没东西，比较快，（选项二有点慢，而且会混杂一些东西）



## 界面窗口

### 编辑框窗口

Override的方法在左边会有一个提示

![image-20220425064348080](PyCharm.assets/image-20220425064348080.png)

### 其他窗口

左下角悬浮后能打开一些窗口，像常用的比如：

> | Project        | 项目结构                         |
> | -------------- | -------------------------------- |
> | Structure      | 当前文件的结构（类 - 对象/成员） |
> | Run            | 调试窗口                         |
> | TODO           | 找到所有有TODO注释的代码         |
> | Terminal       | 终端，略                         |
> | Python Console | Python终端，略                   |
> | Event Log      |                                  |
> | Favorites      |                                  |



![image-20220426050840868](PyCharm.assets/image-20220426050840868.png)

PyCharm窗口上面有四个选项：全部展开、全部折叠、设置、隐藏

- 设置：可以将窗口移动到其他区域，用受拖拽不行
- 隐藏，隐藏后可以在左下角中重新召唤出来，也可以点旁边的那个旋转了90度的小标签

![image-20220426051023579](PyCharm.assets/image-20220426051023579.png)

#### Structure 结构窗口

其中工具栏有五个控件，依次是：
（个人习惯只选择）

- 按定义顺序排序 or 按字母排序 (选中)
- 是否显示继承的内容（继承的部分是灰色）
- 是否要显示变量成员（否则就进显示方法成员）
- 在导航中选中后，在代码窗口自动定位
- 在代码窗口选中后，在导航中自动定位

小图标含义

- 图标主体

  | 标志   | 英文      | 翻译 | 含义               |
  | ------ | --------- | ---- | ------------------ |
  | 黄色 V | Variable  | 变量 | 变量               |
  | 蓝色 C | Class     | 类   | 类                 |
  | 粉色 F | Function  | 函数 | 函数               |
  | 红色 m | Method    | 方法 | 类方法             |
  | 紫色 p | Property  | 属性 | 类方法 (@property) |
  | 黄色 f | Field     | 字段 | 类变量             |
  | 黄色 p | Parameter |      |                    |

- 左上角

  - 黄色锁：private，私有成员
  - 灰色钥匙：protected，保护成员（单下划线保护，双下划线私有，但感觉单下划线居多）
  - 红色锁：伪私有
  - 绿色解锁：public（但一般不显示）
  - 蓝色圆：特殊函数，例如`__dict__()`

- 右上角

  - 右箭头。@property会造成
  - 左箭头。@xxx.setter会造成

![image-20220521103829193](PyCharm.assets/image-20220521103829193.png)

#### TODO 面板窗口

```python
# @TODO: Fix ME!!!
```

和普通注释的样式和有所不同，会==金色高亮==

PyCharm中，左下角TODO或双Shift搜索TODO，可以弹出TODO窗口

TODO窗口可以查看所有有TODO注释的代码

## KeyShot

运行快捷键：Shift+F10

## Skill

按住Ctrl再指向变量等，会出现提示（这个变量的所属类等等）

按住Ctrl再单击类，可跳转过去看类方法





































