# C++

## 错题

### 多线程处理全局变量

```cpp
一个全局变量tally,两个线程并发执行(代码段都是ThreadProc),问两个线程都结束后,tally取值范围为_______
	
int tally=0;//全局变量
  void ThreadProc(){
     for(int i=1;i<=50;i++)
          tally+=1;
}
```

错：B [100,100]
对：A [50, 100]

A   最小值的情况：（线程a，b交替读取tally值）  a线程对tally加1后，还没有更新tally在内存中的值，线程b读取tally值，执行加1，更新tally为1，然后a线程重新读取tally值，这样交替运行，最终为50  最大值的情况：  a线程对tally加到50后，更新tally在内存中的值为50，然后线程b读取tally值，再执行加50运算，结果为100；

我本来还以为这个操作是原子的……看来要声明全局变量为原子的才行

### &int不能传给int类型参数

```cpp
int fun6(int);
int (*pf)(int) = fun6;
在下列选项中，正确的调用是（  ）
```

多选了：`int a=15; int n=fun6(&a);`，**在Dev-c++下加c++ 11编译选项，&a不被认为是int** 

### 线性类型存储不能遍历删

```cpp
CONTAINER::iterator iter, tempIt;
for (iter = cont.begin(); iter != cont.end();)    　　
{
    tempIt = iter;
    ++iter;
    cont.erase(tempIt);
    　　
}

 假设cont是一个CONTAINER的实例，里面包含数个元素，那么当CONTAINER为：
1、vector   2、list   3、map    4、deque
会导致上面的代码片段崩溃的CONTAINER类型是？ （双选）2 3
```

答案：1 4，因为1 4都是线性类型存储，线性类型存储不能遍历删的

### 内敛不能递归

关于内联函数说法错误的是:

```
不是任何一个函数都可定义成内联函数
内联函数的函数体内不能含有复杂的结构控制语句
递归函数可以被用来作为内联函数
内联函数一般适合于只有1~5行语句的小函数
```

答案C。我选了B，本来觉得这只是不建议，并不是说一定就不行

### Const能作为重载依据

C++中，能作为函数重载判断依据的是？

漏了个Const： 如果同时在类中，对于函数名相同的const函数和非const函数能够构成重载

https://blog.csdn.net/sun19910114/article/details/40051713

```cpp
A b( 2002 );
b.func( ); //调用 非const版本的func() 
    
const A c( 2002 );
c.func( ); //调用 const版本的func() 
```



```cpp
假定CSomething是一个类，执行下面这些语句之后，内存里创建了____个CSomething对象。 

CSomething a();
CSomething b(2);
CSomething c[3];
CSomething &ra = b;
CSomething d = b;
CSomething *pA = c;
CSomething *p = new CSomething(4);

10
9
8
7
6
5

CSomething a();// 定义一个函数，参数为空，返回值为CSomething对象， 类似int func();   
CSomething a; // 定义对象a，使用默认构造函数CSomething::CSomething()  
CSomething a(0); // 定义对象a，使用构造函数CSomething::CSomething(int) 
```

答案6，我选了7。`CSomething a();` 没有创建，不是默认构造函数，只是个函数声明（在C++ Primer393页中有说明），太傻逼了

## 不会

```cpp
使用操作符setw() 对数据进行格式输出时，应包含（ ）文件。
fstream.h
stdlib.h
iostream.h
iomanip.h
```

选D，iomanip.h

C++ setw() 函数用于设置字段的宽度，没见过没用过

## 没审题

```cpp
class A{
    public:
        long a;
};
class B : public A {
    public:
        long b;
};
void seta(A* data, int idx) {
    data[idx].a = 2;
}
int main(int argc, char *argv[]) {
    B data[4];
    for(int i=0; i<4; ++i){
        data[i].a = 1;
        data[i].b = 1;
        seta(data, i);
    }
    for(int i=0; i<4; ++i){
         std::cout << data[i].a << data[i].b;
    }
    return 0;
}
```

执行结果是 22221111 而非 21212121。这道题如果改为 `void seta(B* data, int idx)` 才是 21212121

对A进行下标的结果就是，步进长度是4而不是8

## 不确定

```cpp
以下#pragma预处理命令哪个是改变编译器的对齐方式（）

#pragma comment
#pragma pack
#pragma data_seg
#pragma once
```

B

```cpp
STL中的一级容器有: 

vector, deque, list, set, multiset, map, multimap.
序列容器，关联容器，容器适配器
set, multiset, map, multimap.
vector, deque, list.
```

D



## 误错	

```cpp
以下定义语句中正确的是（）

char a='A'b='B';
float a=b=10.0;
int a=10,*b=&a;
float *a,b=&a;
```

D不对的，未初始化不能取地址？而且a是`float*`，&a是`float**`。C是对的