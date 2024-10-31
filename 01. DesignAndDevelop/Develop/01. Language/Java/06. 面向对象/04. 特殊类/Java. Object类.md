# Java

# 目录

# Object类 - 所有类的超类

## 概念

- 概念

  - Object类是Java中所有类的始祖，在Java中每个类都是由它扩展而来的。但是并不需要这样写

    ```java
    public class Employee extends Object	// 如果没有明确地指出超类，Object就被认为是这个类的超类
    ```

- 范围

  - 在Java中，只有基本类型（primitive types）不是对象。例如：数值、字符和布尔类型的值都不是对象。
  - 所有的数组类型，不管是对象数组还是基本类型的数组都扩展了Object类

- 用途

  - 可以使用Object类型的变量引用任何类型的对象

    ```java
    Object obj = new Emplyee("Harry Hacker", 35000);
    ```

  - Object类内置了几个方法，以便所有类都能用这几个方法



---

==与C++不同==

其他语言

- java：Object类是Java中所有类的始祖
- js：原型链的终点是object
- QT：QObject类是所有QT类的始祖
- C++：没有所有类的根类，不过，每个指针都可以转换成void*指针

## 对象比较

### 常用方法

#### equals方法

Object类中的equals方法用于检测一个对象是否等于另外一个对象

```java
a.equals(b)
// 在Object类中，这个方法将判断两个对象**是否具有相同的引用**。如果两个对象具有相同的引用，它们一定是相等的。
// 然而，对于多数类来说，equals的默认判断没什么意义。经常需要检测两个对象**状态的相等性**，若状态相等，就认为这两个对象是相等的
```

- ==和equals区别：`==`比较的是内存地址，多用于值类型的比较
- equals方法特性
  Java语言规范要求equals方法具有下面的特性：
  - 1）自反性：对于任何非空引用x，x.equals（x）应该返回true。
  - 2）对称性：对于任何引用x和y，当且仅当y.equals（x）返回true，x.equals（y）也应该返回true
    从而避免了类库实现者在数据结构中定位一个元素时还要考虑调用x.equals（y），还是调用y.equals（x）的问题
  - 3）传递性：对于任何引用x、y和z，如果x.equals（y）返回true，y.equals（z）返回true，x.equals（z）也应该返回true。
  - 4）一致性：如果x和y引用的对象没有发生变化，反复调用x.equals（y）应该返回同样的结果。
  - 5）对于任意非空引用x，x.equals（null）应该返回false。

#### Objects.equals(a, b) 方法

```java
Objects.equals(a，b)
// 1. 如果两个参数都为null，返回true；
// 2. 如果其中一个参数为null，返回false；
// 3. 如果两个参数都不为null，则调用a.equals(b)
```

#### getClass方法

```java
getClass()
// 返回一个对象所属的类
```

#### instanceof方法

```java
？？？
```

### 应用举例 - 重写equals方法

```java
public class Employee
{
    ...
    public boolean equals(Object otherObject)					// 重写equals方法
    {
        if(this == otherObject) return true;					// 引用是否相同
        if(otherObject == null) return false;
        if(getClass() != otherObject.getClass()) return false;	// 类是否相同
        Employee other = (Employee) otherObject;
        //return name.equals(other.name)						// 状态是否相同 - 有缺陷版本
        //    && salary == other.salary
        //    && hireDay.ewquals(other.hireDay);*/
        
        // 提示：为了防备name或hireDay可能为null的情况，需要使用Objects.equals方法
        // 因为null不是object，null不可调用equals方法
        return Objects.equals(name, other name)					// 状态是否相同
            && salary == other.salary
            && Object.equals(hireDay, other.hireDay);
    }
}
```

### 相等测试与继承 [暂略]，没懂

API：`java.util.Arrays 1.2`
API：`java.util.Objects 7`

如果隐式和显式的参数不属于同一个类，equals方法将如何处理呢？

在前面的例子中，如果发现类不匹配，equals方法就返回false。但是，许多程序员却喜欢使用instanceof进行检测：

```java
if (!(otherObject instanceof Employee)) return false
```

这样做不但没有解决otherObject是子类的情况，并且还有可能会招致一些麻烦。这就是建议不要使用这种处理方式的原因所在。



然而，就对称性来说，当参数不属于同一个类的时候需要仔细地思考一下。请看下面这个调用：

```java
e.equals(m);	// 返回true
// e是一个Employee对象，m是一个Manager对象，并且两个对象具有相同的姓名、薪水和雇佣日期。
// 如果在Employee.equals中用instanceof进行检测，则返回true。然而这意味着反过来调用
m.equals(e);	// 返回true。对称性不允许这个方法调用返回false，或者抛出异常。
```

### hashCode方法 [此略]

API：`java.util.Object 1.0`
API：`java.util.Objects 7`
API：`java.lang.（Integer|Long|Short|Byte|Double|Float|Character|Boolean）1.0`
API：`java.util.Arrays 1.2`



散列码（hash code）是由对象导出的一个整型值

散列码是没有规律的。如果x和y是两个不同的对象，x.hashCode（）与y.hashCode（）基本上不会相同

## toString方法（书略）

API：`java.lang.Object 1.0`
API：`java.lang.Class 1.0`

在Object中还有一个重要的方法，就是toString方法，它用于返回表示对象值的字符串























