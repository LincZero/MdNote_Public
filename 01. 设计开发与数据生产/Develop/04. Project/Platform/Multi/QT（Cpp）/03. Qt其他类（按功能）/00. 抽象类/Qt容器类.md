# Qt

# 目录

# 容器类

## 简概

复习一下C++标准模板库的一些常见容器

- 序列容器类
    - vector - 计算机矢量，deque - 双端队列，list - 链表（单向or双向），forward_list - 向前链表（C++11）
- 适配器类
    - queue - 队列，priority_queue - 优先队列，stack
- 关联容器
    - set，multimap
- 无序关联容器
    - unordered_set，unordered_multiset，unordered_map，unordered_multimap



Qt容器类对比C++标准库中的容器类

- 更轻量、更安全、更易用。速度、内存消耗和内联（inline）代码等方面进行了优化
- 存储在Qt容器中的数据必须是可赋值数据类型。即这种数据类型必须提供默认构造函数、复制构造函数、赋值操作运算符
- Qt的Object及其子类必能够存储在容器中，但可以存储他们的指针
- Qt的容器类可以嵌套，例如`QHash<QString, QList<double> >`



Qt容器类的遍历有两种方法

- Java风格的迭代器（*Java-style iterators*），使用起来更简单方便，但以轻微性能损耗为代价的
- STL风格的迭代器（*STL-style iterators*），能够同Qt和STL通用算法一起使用，效率上略胜一筹

## QList、QLinkedList、QVector

| 容器类      | 查找 | 插入 | 头部添加   | 尾部添加   |
| ----------- | ---- | ---- | ---------- | ---------- |
| QList       | O(1) | O(n) | Amort.O(1) | Amort.O(1) |
| QLinkedList | O(n) | O(1) | O(1)       | O(1)       |
| QVector     | O(1) | O(n) | O(n)       | Amort.O(1) |

其中，Amort.O(1)表示如果仅完成一次操作，可能会有O(n)行为，但如果完成多次操作（如n次），平均结果将会是O(1)

### QList类

- 简概：`QList<T>`是迄今为止最常用的容器类
- 子类：QItemSelection、QQueue、QSignalSpy、QStringList、QTestEventList
- 函数：`QList::append()`、`QList::prepend()`、`QList::insert()`
- 性质：对于不同数据类型，`QList<T>`采用不同的存储策略
    - (1) 如果T是一个指针类型或指针大小的基本类型，会将数值直接存储在它的数组中
    - (2) 如果T是存储对象的指针，则该指针指向实际存储的对象
    - 例子：
    ```c++
  #include <QDebug>
  int main(int argc,char *argv[]){
      QList<QString> list;						// 声明一个QList<QString>栈对象
      {
        QString str("This is a test string");
        list << str;								// 将字符串存储在该列表中
      }											// 使用花括号，为验证这里是复制了对象
      qDebug()<<list[0]<<"How are you!";
  }
  // 输出结果："This is a test string" How are you!
  ```

### QLinkedList类

- 简概：`QLinkedList<T>`是一个链式列表，以非连续的内存块保存数据

### QVector类

- 简概：`QVector<T>`在相邻的内存中存储给定数据类型T的一组数值（不太懂）
- 子类：QPloygon、QPolygonF、QStack

### Java风格迭代器遍历容器

- 只读迭代器和读写迭代器
    - 两种类型的Java风格迭代器数据类型，只读更快所以应尽可能使用只读迭代器
    - | 容器类                              | 只读迭代器类             | 读写迭代器类                    |
        | ----------------------------------- | ------------------------ | ------------------------------- |
        | `QList<T>`、`QQueue<T>`             | `QListIterator<T>`       | `QMutableListIteraotr<T>`       |
        | `QLinkedList<T>`                    | `QLinkedListIterator<T>` | `QMutableLinkedListIterator<T>` |
        | `QVector<T>`、`<QStack<T>`          | `QVectorIterator<T>`     | `QMutableVectorIterator<T>`     |
        | `QMap<Key,T>`、`QMultiMap<Key,T>`   | `QMapIteraotr<Key,T>`    | `QMutableMapIterator<Key,T>`    |
        | `QHash<Key,T>`、`QMultiHash<Key,T>` | `QHashIterator<Key,T>`   | `QMutableHashIterator<Key,T>`   |
- 迭代点补充
  
    - 不同于STL风格的迭代器，Java风格迭代器的`迭代点`（*Java-style iterators point*）位于列表项的**中间**，而不是直接指向某个列表项
- 只读迭代器例程
    - ```c++
    #include <QCoreApplication>
    #include <QDebug>					// 包括了QList头文件，不需要 #include <QList>
    int main(int argc, char *argv[])
    {
        QCoreApplication a(argc, argv);
        QList<int> list;					// 声明容器类对象
        list<<1<<2<<3<<4<<5;
        QListIterator<int> i(list);			// 以list为参数初始化一个QListIterator只读迭代器对象i
        for(;i.hasNext();)
            qDebug()<<i.next();
        return a.exec();
    }
      ```
- 只读迭代器函数
    - `QListIterator<T>::toBack()`，将迭代点移动到最后一个列表项后面
    - `QListIterator<T>::next()`，返回后一个列表项的内容**并**将迭代点移动到前一个列表项之前
    - `QListIterator<T>::previous()`，返回前一个列表项的内容**并**将迭代点移动到前一个列表项之前
    - `QListIterator<T>::hasNext()`，检查当前迭代点之后是否具有列表项
    - `QListIterator<T>::hasPrevious()`，检查当前迭代点之前是否具有列表项
    - `toFront()`，移动迭代点到列表的前端（第一个列表项前面）
    - `peekNext()`，返回下一个列表项，但不移动迭代点
    - `peekPrevious()`，返回前一个列表项，但不移动迭代点
    - `findNext()`，从当前迭代点向后查找的列表项。若找到则返回true且迭代点位于匹配项后面，否则false且迭代点在列表的后端
    - `findPrevious()`，与findNext类似，向前查找
- 读写迭代器例程
    - ```c++
        #include <QCoreApplication>
        #include <QDebug>
        int main(int argc, char *argv[])
        {
            QCoreApplication a(argc, argv);
            QList<int> list;					// 声明容器类对象
            QMutableListIterator<int> i(list);	// 根据容器类list创建读写迭代器
            for(int j=0;j<10;++j)				// 插入，填充容器类内容
                i.insert(j);
            for(i.toFront();i.hasNext();)		// 向后遍历，并打印，输出：0 1 2 3 4 5 6 7 8 9
                qDebug()<<i.next();
            for(i.toBack();i.hasPrevious();) 	// 向前遍历，并移除和修改值
            {
                if(i.previous()%2==0)
                    i.remove();
                else
                    i.setValue(i.peekNext()*10);
            }
            for(i.toFront();i.hasNext();)		// 向后遍历，并打印，输出：10 30 50 70 90
                qDebug()<<i.next();
            return a.exec();
        } 
        ```
- 读写迭代器函数（新增）
    - `insert()`，插入操作函数
    - `remove()`，删除操作函数
    - `setValue()`，修改数据函数

### STL风格迭代器遍历容器

- 只读迭代器和读写迭代器
    - 两种类型的STL风格迭代器数据类型，只读更快所以应尽可能使用只读迭代器

    - STL风格迭代器的API建立在指针操作基础上

    - | 容器类                              | 只读迭代器                       | 读写迭代器                    |
        | ----------------------------------- | -------------------------------- | ----------------------------- |
        | `QList<T>`、`QQueue<T>`             | `QList<T>::coust_iterator`       | `QList<T>::iterator`          |
        | `QLinkedList<T>`                    | `QLinkedList<T>::coust_iterator` | `QLinkedList<T>::iterator`    |
        | `QVector<T>`、`QStack<T>`           | `QVector<T>::const_iterator`     | `QVector<T>::iterator`        |
        | `QMap<Key,T>`、`QMultiMap<Key,T>`   | `QMapIteraotr<Key,T>`            | `QMutableMapIterator<Key,T>`  |
        | `QHash<Key,T>`、`QMultiHash<Key,T>` | `QHashIterator<Key,T>`           | `QMutableHashIterator<Key,T>` |

- 迭代点补充

    - 不同于Java风格的迭代器，STL风格迭代器的迭代点直接指向列表项

- STL迭代器例程

    - ```c++
        #include <QCoreApplication>
        #include <QDebug>
        int main(int argc, char *argv[])
        {
            QCoreApplication a(argc, argv);
            QList<int> list;						// 初始化一个空的QList<int>列表
            for(int j=0;j<10;j++)					// 填充容器
                list.insert(list.end(),j);
            QList<int>::iterator i;					// 初始化一个QList<int>::iterator读写迭代器（未赋值）
            for(i=list.begin();i!=list.end();++i)	// 往后遍历并调试输出并修改值
            {
                   qDebug()<<(*i);					// 输出：0 1 2 3 4 5 6 7 8 9
                   *i=(*i)*10;
            }
            QList<int>::const_iterator ci;			// 初始化一个QList<int>:: const_iterator读写迭代器
            for(ci=list.constBegin();ci!=list.constEnd();++ci)
                    qDebug()<<*ci;					// 在控制台输出列表的所有值：0 10 20 30 40 50 60 70 80 90
            return a.exec();
        }
        ```

- STL迭代器函数

    - `*QList<T>::iterator`，迭代器本质是指针，可以通过迭代器指向列表项并修改列表项
    - 返回`QList<T>::iterator`迭代器的函数
        - `QList<T>::begin()`，返回指向第一个列表项的迭代器
        - `QList<T>::end()`，返回指向最后一个列表项的迭代器
        - `QList<T>::insert()`，第一个参数是迭代器`QList<T>::iterator`
    - 返回`QList<T>::const_iterator`迭代器的函数
        - `QList<T>::constBegin()`，返回指向第一个列表项的迭代器
        - `QList<T>::constEnd()`，返回指向最后一个列表项的迭代器

## QMap、QHash

### QMap类

### QHash类

### Java风格迭代器遍历容器

### STL风格迭代器遍历容器













