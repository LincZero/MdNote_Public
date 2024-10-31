# X宏

参考：http://notes.tanchuanqi.com/language/cpp/cpp_micro.html

## 先复习一下宏

### 普通宏，实现文本替换

```cpp
#define PI 3.1415926
```

### 宏做函数

宏可以像函数一样被定义，例如:

```
#define MIN(x,y) ((x)<(y)?(x):(y))
```

但是在实际使用时，只有当写上MIN()，必须加括号，MIN才会被作为宏展开，否则不做任何处理。 编译器 (预处理器) 对宏只进行简单的文本替换，而 **不会进行语法检查** ，所以更多的检查性工作得你自己来做。

#### 为什么要用宏来做函数？

1. **鸭子原则**：比如MIN宏适用于任何实现了operator<的类型，包括自定义类型（这点与template类似）；
2. 效率最高：虽然使用inline提示符也将函数或模板定义为内联的，但这只是一种提示而已，到底编译器有没有优化还依赖于编译器的实现，而使用宏函数则是完全由代码本身控制。

#### 2个宏编程易犯的错误

程序员对宏定义的使用要非常小心，特别要注意两个问题：

- 谨慎地将宏定义中的 **“参数”** 和 **整个宏** 都用括弧括起来。

  所以，严格地讲，下述解答: 

  ```cpp
  #define MIN(A, B) (A) <= (B) ? (A) : (B) 	// 零分
  #define MIN(A, B) (A <= B ? A : B ) 		// 零分
  #define MIN(A, B) ((A) <= (B) ? (A) : (B)) 	// 正确写法
  ```

- **防止宏的副作用** :

  宏定义 `#define MIN(A,B) ((A) <= (B) ? (A) : (B))` 对 `MIN(*p++, b)` 的作用结果是： `((*p++) <= (b) ? (*p++) : (*p++))` 这个表达式会产生副作用，指针p会作三次++自增操作。 （因为， **宏的本质是文本替换** ）
  除此之外，另一个应该判0分的解答是： `#define MIN(A,B) ((A) <= (B) ? (A) : (B));` 这个解答在宏定义的后面加”;”，显示编写者对宏的概念模糊不清，只能被无情地判0分并被面试官淘汰。

#### 后面加不加分号

宏定义一般都不在最后加分号，调用的时候才加分号。 这样处理之后就要求使用者将宏视为一条普通语句而不是一个宏，从而需要在后面加上;号。

#### 特殊符号：#、## (字符串化运算符)

1. \# 符号把一个符号直接转换为字符串，例如:

   ```cpp
   #define STRING(x) #x;						// 宏定义
   const char *str = STRING( test_string );	// 宏使用
   const char *str = "test_string"				// 宏展开。`#`是字符串化运算符，会把其后的符号直接加上双引号
   ```

2. `##` 符号会连接两个符号，从而产生新的符号(词法层次)，例如:

   ```cpp
   #define SIGN( x ) INT_##x 	// 宏定义
   int SIGN( 1 );				// 宏使用
   int INT_1;					// 宏展开
   ```
3. 有资料说可以用#@把一个宏参数变成字符（也就是给参数加上单引号，相对应于#的双引号） `#@a = 'a'`。
   但是，在gcc上的测试显示不支持#@，测试的结果是”“@，相当于对空添加双引号再加上@的结果。


### do{…}while(0) 技巧

这个技巧非常漂亮！

使用do-while(0)的宏定义是为了防止if-else( if)的语法错误,这一般是库作者来保证代码的健壮性所使用的技巧。 而且，还 **可以使得宏中使用到的变量都成为 局部变量** ，不造成任何副作用！

### 使用宏完成注册操作

### 常见用途

- 宏常量：但是如果仅仅是定义常量，那么应该果断的**使用const而不是使用宏**。

- 头文件的重复包含：这个用途几乎不用说了，头文件都需要用宏包含起来以免重复包含。

- 条件编译：生成一个程序的不同版本、或者对debug和release使用不同的代码时非常常见:

  ```cpp
  #if defined(OS_HPUX) && (defined(HPUX_11_11) || defined(HPUX_11_23)
  // for HP-UX 11.11 and 11.23
  #elif defined(OS_HPUX) && defined(HPUX_11_31
  // for HP-UX 11.31
  #elif defined(OS_AIX)
  // for AIX
  #else
  ...
  #endif
  ```

- 使用_DEBUG进行一个调试工作:

  ```cpp
  #ifdef DEBUG
  printf("Debug information\n");
  #endif
  ```

- 宏函数：避免函数调用，提高程序效率。宏函数**基本上可以被模板和内联函数所取代**，但是还是有一些简单的函数会使用宏，而且宏函数可以确保一定是内联的。

- 引用编译期数据：这种情况只能使用宏来解决了:

  ```cpp
  #define SHOW_CODE_LOCATION() cout<<__FILE__<<':'<<__LINE__<<'\n'
  ```

- 当然，最NB的功能肯定是自动生成代码了！

## X宏

### 语法基础

`X-Macro` 只是一种宏的使用技巧，**并不是什么特殊的语法**，但却在实际应用中十分高效简洁，且拓展性非常强；

首先我们介绍一下`#define`与`#undef`的用法：

```cpp

#define X_MACRO(a, b)   a
#undef X_MACRO
#define X_MACRO(a, b)   b
#undef X_MACRO
```

### 核心思想

参考：https://www.51cto.com/article/719151.html

#### 灵活的应用#define与#undef

X-MACRO宏技术的核心在于灵活的应用#define与#undef，对于玩C语言的伙计#define是再熟悉不过了，但#undef却鲜有人在实际的开发过程中熟练使用，基本上都是#define走天下。

那#define的作用域是怎样的呢？其作用范围都是从宏定义处到文件结束，不管函数内外均可以随意使用。

那一不小心使用#define重复定义相同的宏又会怎样呢?对于大部分编译器会报重复定义警告，但也有小部分编译器采用最近的宏定义直接通过，所以稍不留神就把bug引入到了代码中。

其实对于C语言编程素养良好的工程师们多会使用#undef来限制宏定义的作用范围，即取消宏定义，以免造成宏泛滥。

```cpp
#include <stdio.h>
#include <stdlib.h>
#define HELLO_BUG   100

int main(int argc, char *argv[]) {
    printf("hello bug %d\r\n",HELLO_BUG);
    #undef HELLO_BUG
    printf("hello bug %d\r\n",HELLO_BUG); // 编译报错，提示第二条打印语句HELLO_BUG宏未定义
    return 0;
}
```

#### X-MACRO

X-MACRO平时我们也叫"X宏"，其实在bug菌之前的文章<三种管理C程序中标志位的方法，最后一种比较秀~>有一个简单的提及，今天单独拧出来简化讲讲。

```cpp
#define X_MACRO(a, b)   a
//do something
#undef X_MACRO

#define X_MACRO(a, b)   b
//do something
#undef X_MACRO
```

如上是X-MACRO的比较精华的几句，通过#define与#undef的配合，可以使用相同的宏名称**选择性的替换出我们想要的结构**，从而达到简化代码的目的。同时我们也非常清楚，由于宏主要是靠编译器来处理，所以X-MACRO技巧也主要是在编译阶段来维护代码。

#### 原理实例

下面来一波操作看看效果吧

```cpp
/*************消息定义**********/
#define MSG_TABLE                  \
    X_MACROS(USER_MSG1, MsgProc1)  \
    X_MACROS(USER_MSG2, MsgProc2)  \
    X_MACROS(USER_MSG3, MsgProc3)  \

/*************消息枚举定义**********/
typedef enum {
    #define X_MACROS(a, b) a,
    MSG_TABLE
    #undef X_MACROS
    MSG_MAX  
} MSG_TYPE;

/*************消息处理定义**********/
const Proc Proc_table[] = {
    #define X_MACROS(a, b) b,
    MSG_TABLE
    #undef X_MACROS  
};

/*************实际使用**********/
void sMessageProc(MSG_TYPE msgtype) {
    (Proc_table[msgtype])();
}
```

当然X-MACRO还可以扩展多个参数来供序列化替换，同时X-MACRO宏定义也可以更加的复杂。

比如使用 `#define X_MACROS(a, b) #a` 宏来处理为字符串等。

详细解释一下这里的宏展开：

```cpp
// 1. 该行生效：#define X_MACROS(a, b) a,
// 2. 先使用 MSG_TABLE 宏替换第一遍：
{
    X_MACROS(USER_MSG1, MsgProc1)
    X_MACROS(USER_MSG2, MsgProc2)
    X_MACROS(USER_MSG3, MsgProc3)
    MSG_MAX 
}
// 3. 再使用 X_MACROS 宏替换第二遍
{
    USER_MSG1
    USER_MSG2
    USER_MSG3
    MSG_MAX 
}
// 4. 最后卸载该宏：#undef X_MACROS
```

### 使用示例

#### define & undef

```cpp
#define X_MACRO(a, b)   a
int x = X_MACRO(10, 100)
#undef X_MACRO
    
#define X_MACRO(a, b)   b
int y = X_MACRO(10, 100)
#undef X_MACRO
```

`#undef`可以取消定义宏，然后再通过`#define`重新定义宏，此时得到的`x`，`y`的值分别是`10`和`100`

#### 列表

`X-Macro`其实就是通过`#define`与`#undef`实现的一种宏定义的技巧；

当我们需要一个命令列表时可以这样定义：

```cpp
// 定义宏列表
#define MACROS_TABLE                    \
    X_MACROS(CMD_LED_ON,  led_on)       \
    X_MACROS(CMD_LED_OFF, led_off)      \

// 当我们需要一个命令列表时
typedef enum {
    #define X_MACROS(a, b) a,
    MACROS_TABLE
    #undef X_MACROS
    CMD_MAX
} cmd_e;
```

宏展开后是这样的形式：

```cpp
typedef enum {
    CMD_LED_ON,
    CMD_LED_OFF,
    CMD_MAX
} cmd_e;
```

#### 示例

如果我们需要一个命令的字符串列表用作 log 打印时也可以定义这样的列表：

```cpp
const char* cmd_str[] = {
    #define X_MACROS(a, b) #a,
    MACROS_TABLE
    #undef X_MACROS
};
```

宏展开后是这样的形式：

```cpp
const func func_table[] = {
    “CMD_LED_ON”，
    “CMD_LED_OFF”，
};
```

#### 示例

当我们需要一个函数列表时可以这样操作：

```cpp
const func func_table[] = 
{
    #define X_MACROS(a, b) b,
    MACROS_TABLE
    #undef X_MACROS
};
```

宏展开后是这样的形式：

```cpp
const func func_table[] = 
{
    led_on,
    led_off,
};
```

由于函数列表与命令列表都是根据`MACROS_TABLE`这个宏拓展出来的，是一一对应的，所以我们可以直接使用索引的方式来调用函数：

```cpp
static void cmd_handle(cmd_e cmd)
{
    if(cmd < CMD_MAX)
    {
        func_table[cmd]((void*)cmd_str[cmd]);
    }
}
```

使用`X-MACRO`对于此类的命令消息处理十分高效简洁，非常实用，且拓展性非常强。

**整体代码如下：**

```cpp
#include <stdio.h>

#define MACROS_TABLE                    \
    X_MACROS(CMD_LED_ON,  led_on)       \
    X_MACROS(CMD_LED_OFF, led_off)      \

/*定义命令列表*/
typedef enum
{
    #define X_MACROS(a, b) a,
    MACROS_TABLE
    #undef X_MACROS
    CMD_MAX
}cmd_e;


/*定义字符串列表用作Log打印*/
const char* cmd_str[] = 
{
    #define X_MACROS(a, b) #a,
    MACROS_TABLE
    #undef X_MACROS
};


typedef void (*func)(void* p);

static void led_on(void* p)
{
    printf("%s \r\n", (char *)p);
}

static void led_off(void* p)
{
    printf("%s \r\n", (char *)p);
}

/*定义函数列表*/
const func func_table[] = 
{
    #define X_MACROS(a, b) b,
    MACROS_TABLE
    #undef X_MACROS
};


/*直接通过索引的方式调用函数*/
static void cmd_handle(cmd_e cmd)
{
    if(cmd < CMD_MAX)
    {
        func_table[cmd]((void*)cmd_str[cmd]);
    }
}


void main(void)
{
    cmd_handle(CMD_LED_ON);
    cmd_handle(CMD_LED_OFF);
}
```











