# IntelliJ IDEA

# 目录

# IntelliJ IDEA

## 基本操作

### IDEA基本操作

类的操作

大纲右键 > 新建类

大纲右键 > 删除类

大纲右键 > 修改类名



项目的操作

略

## 界面

### 图标

> | 文件夹  | ----   | （根部）   |
> | ------- | ------ | ---------- |
> | 蓝色 C  | Class  | 类         |
> | 橙色 f  | field  | 字段       |
> | 红色 m  | method | 方法       |
> | 红色  λ | lambda | lambda方法 |

## 技巧

### 其他

若用IDEA打开java文件时会问你：“文件在LightEdit中打开。是否在项目中打开”

- 选否则使用轻量化的编辑器打开
- 选项目，则让你选择项目根目录（默认位置在你java文件所在的位置）
  项目资源如下：
  - .idea
    - .gitignore文件
    - javaFileName.iml，原java文件相关的iml文件
    - modules.xml，模块
    - runConfigurations.xml，运行时配置文件
    - workspace.xml，工作空间
  - **javaFileName.java**
  - 该文件夹下本来就有的其他文件

### 快捷键

略

### 小技巧

#### 使用实时模板插入频繁使用的代码结构

```java
// psvm + Tab：
public static void main(String[] args) {
}
// soun + tab
System.out.println("");
```

#### 选择多段文本并对其进行修改

> 按住Shift+Alt（Winodws/Linux）/？？（macOS），然后在文本上拖动鼠标

#### 批量重命名

> Shift+F6（重构|重命名）

## 一些设置

### 自动导入包

Settings > Editor > General > Auto Import > 勾选 Add unambiguous imports on the fly 和 Optimmize imports on the fly

即可实现自动导入包（自动写 import xxx）

























