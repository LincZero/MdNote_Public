# 《Effective C++》

参考

- 实体书，中文版，第三版，候捷
- 跟读视频
  - [[鲨哥带你读] Effective C++](https://www.bilibili.com/video/BV1B14y1f7fw)
  - [《Effective C++》2023（上部完整版） C++进阶看这个](https://www.bilibili.com/video/BV1QX4y1W7Ya)，更详细，还有上机，但没更完

共有55个条款

# 让自己习惯C++

## (01) 视C++为一个语言联邦

## (02) 尽量以const, enum, inline 替换 `#define`

优先选择编译器而不是预处理器

> ##### 预处理器的坏处

举例：

```c++
#define ASPECT_RATIO 1.653
```

发生错误时，编译器给出的错误信息是1.653，而不是ASPECT_RATIO，你可能难以定位，特别是目标代码中，可能出现多个1.653副本

> ##### C++11的常量表达式补充

另外，第三版时还没有C++11的constexpr，现在有更好的写法：

```c++
const double AspectRatio = 1.653;
```

> ##### 另外需要区分多种"常量"

- 编译期常量 (Compile-time constants)

  - 举例
    - 数组：如果我们想要创建一个不是动态分配内存的数组，那么我们就必须给他设定一个size——这个size必须在编译期间就知道，因此静态数组的大小是编译期常量
    - switch的case标签
    - 模板
    - `constexpr`
    - `#define` (倒不如说是预处理常量)
  - 优点
    - 安全、编译优化(快)

- 运行期常量

  - 举例

    - **const** (但有时可被优化成编译期常量)

      ```cpp
      // 因为他的值在编译期可能无法确定，例如：
      const int x = 10; // 编译期常量
      int y;
      cin >> y;
      const int z = y; // 运行期常量
      ```

  - 但需要注意的是，某些情况下，编译器可能会对运行期常量进行优化，将其视为编译期常量进行处理

> ##### 两个特殊情况

- 常量指针

  ```cpp
  // 错误示例
  // #define AUTHORNAME "11"
  const char* authorName = "11";
  const char* authorName2 = "22";
  authorName = authorName2; // 结果authorName的值变了
  
  // 正常示例
  const std::string authorName("11");
  ```

- 类的常量

  ```cpp
  class C {
  private:
      // #define NUMTURNS 5 			// 宏无法作用域在类的内部
      static const int NumTurns = 5;	// 每个类都有一个常量副本
      int scores[NumTurns];			// 这里可以在声明前进行定义 (神奇的特殊规则)
  }
  
  // 另一种写法是：
  class C {
  private:
      // #define NUMTURNS 5 			// 宏无法作用域在类的内部
      // static const int NumTurns = 5;	// 每个类都有一个常量副本
      enum { NumTurns = 5};
      int scores[NumTurns];			// 这里可以在声明前进行定义 (神奇的特殊规则)
  }
  ```

> ##### 函数宏 & 内联函数模板

缺点：容易被误用

例如

```cpp
int f (int num) {return num;}
#define CALL_WITH_MAX (a,b) f((a)>(b)?(a):(b))

std::cout << CALL_WITH_MAX(++a, b) << std::endl; // 存在问题，++a会被执行两次
```

替代方案：内联函数模板

```cpp
template<typename T>
inline T callWithMax(const T& a, const T& b) {
    return f(a > b ? a : b);
}
```

> ##### 总结

考虑到const、枚举、内联的可用性，对预处理器的需求减少了，但没有完全消除。

- `#include` 仍然必不可少
- `#ifdef/#ifndef` 在控制编译方面发挥重要作用
- 对于简单常量，首选const对象或枚举，而不是#define
- 对于类似函数的宏，优先选择内联函数

## (03) 尽可能使用const

> ##### const指针

const用于指针时，用途非常广泛

- const出现在`*`左侧：指向的是常量

- const出现在`*`右侧：指针本身是常量

- const在类型左右侧无区别

  ```cpp
  // 这两种写法等价：
  void f1(const Widget* pw);
  void f1(Widget const* pw);
  ```

- 总结

  ```cpp
  char* p = greeting;				// 非常量指针、非常量数据
  const char* p  = greeting;		// 非常量指针、常量数据
  char const* p  = greeting;		// (上)
  char* const p = greeting;		// 常量指针、非常量数据
  const char* const p = greeting;	// 常量指针、常量数据
  ```

- 个人记法：以星号为区分点，左侧是是指向类型，右侧是指针类型

  ```cpp
  ((char)*) p = greeting;			// 非常量指针、非常量数据
  ((const char)*) p  = greeting;	// 非常量指针、常量数据
  ((char const)*) p  = greeting;	// (上)
  ((char)* const) p = greeting;	// 常量指针、非常量数据
  ((const char)* const) p = greeting;	// 常量指针、常量数据
  ```

> ##### const 迭代器

我觉得有点奇怪

例如

```cpp
std::vector<int> vec;
// ...

// iter 的行为像 T* const
const std::vector<int>::iterator iter = vec.begin();
*iter = 10;		// 正确，非常量数据
++iter;			// 错误，常量指针

// cIter 的行为像 const T*
std::vector<int>::const_iterator cIter = vec.begin();
*cIter = 10;	// 错误，常量数据
++cIter;		// 正确，非常量指针
```

> ##### 函数声明

```cpp
const Rational operator*(const Rational& lhs, const Rational& rhs);

// operator*的结果应该是一个const对象，可以避免下面的写法：
(a*b) = c; 		// 错误写法
if (a*b=c);		// 错误写法
```

> ##### const限定成员函数

能使接口更加明确

```cpp
class TextBlock {
public:
    const char& operator[](std::size_t position) const {} 	// 只读版，无法修改
    char& operator[](std::size_t position) {}				// 可写版，能够赋值
}

TextBlock tb("Hello");
std::cout<<tb[0]<<std::endl;	// 调用non-const版
tb[0] = 'x';					// 正确

const TextBlock ctb("Hello");
std::cout<<ctb[0]<<std::endl;	// 调用const版
ctb[0] = 'x';					// 错误
```

> ##### 位常量与逻辑常量

成员函数成为const是什么意思？有两种流行概念：

- 位常量 (bitwise constness)：也叫物理常量
- 逻辑常量 (logical constness)：当你用一个特定的值创建一个常量对象，并且只调用 它的const成员函数时，你仍然改变它的值，这有些不对劲。这就引出了逻辑常量的概念

const成员函数不能修改它的对象的任何**非静态**数据成员

```cpp
class CTextBlock {
public:
    const char& operator[](std::size_t position) const {
        a = 20;		// 正确
        b = "b";	// 错误 
        c = "c";	// 正确
    }
private:
    static int a = 10;
    std::string b;
    char c[100];
}
```

mutable (可变的) 将非静态数据成员从按位常量的限制中解放出来

```cpp
class CTextBlock {
public:
    std::size_t length() const {
        b = std::strlen(text);	// 正确 
        return b
    }
private:
    mutable std::size_t b;
	mutable bool c;				// 即让该值的位变化，视作 "其实没有修改类的内容"，是安全的
}
```

> ##### 避免const重载的代码重复





## (04) 确定对象被使用前已被初始化



















# 构造/析构/赋值运算

## (05) 了解C++默默编写并调用哪些函数

## (06) 若不想使用编译器自动生成的函数，就该明确拒绝

## (07) 为多态基类声明virtual析构函数

## (08) 别让异常逃离析构函数

## (09) 绝不在构造和析构过程中调用virtual函数

## (10) 令operator=返回一个reference to *this

## (11) 在operator=中处理"自我赋值"

## (12) 复制对象时勿忘其每一个成分

# 资源管理

## (13) 以对象管理资源

## (14) 在资源管理类中小心copying行为

## (15) 在资源管理类中提供对原始资源的访问

## (16) 成对使用new和delete时要采用相同形式

## (17) 以独立语句将newed对象置入智能指针

# 设计与声明

## (18) 让接口容易被正确使用，不易被误用

## (19) 设计class犹如设计type

## (20) 宁以pass-by-reference-to-const替换pass-by-value

## (21) 必须返回对象时，别妄想返回其reference

## (22) 将成员变量声明为private

## (23) 宁以non-member、non-friend替换函数

















