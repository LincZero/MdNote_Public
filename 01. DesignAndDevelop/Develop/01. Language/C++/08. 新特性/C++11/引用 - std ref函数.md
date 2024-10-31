# C++

# 目录

# std::ref函数

本篇参考：

- [【博客园】C++11 std::ref使用场景 ](https://www.cnblogs.com/moodlxs/p/10111609.html)
- [【CSDN】C++ ref和引用（&）](https://blog.csdn.net/xuebing1995/article/details/103729013)（主要参考）
- [【CSDN】C++11  ref函数的使用](https://blog.csdn.net/zhouguoqionghai/article/details/45792273)

## 简概

std::ref只是尝试模拟引用传递，并不能真正变成引用，

在非模板情况下，std::ref根本没法实现引用传递，只有模板自动推导类型时，ref能用包装类型reference_wrapper来代替原本会被识别的值类型，而reference_wrapper能隐式转换为被引用的值的引用类型

## 应用场景

### bind

std::ref主要是考虑函数式编程（如std::bind）在使用时，是对参数直接拷贝，而不是引用

### thread

其中代表的例子是thread

比如thread的方法传递引用的时候，必须外层用ref来进行引用传递，否则就是浅拷贝

## 使用例程

### 普通引用

```c++
class TestRef
{
public:
	TestRef():i(0)							// 默认构造函数 
	{
		cout << "TestRef默认构造函数" << this << endl;
	} 	
	TestRef(const TestRef&testR) :i(0) 		// 拷贝构造函数
	{
		cout << "TestRef拷贝构造函数" << this << endl;
	}
	~TestRef()								// 析构函数
	{
		cout << "TestRef析构函数" << this << endl;
	}
	mutable int i ;
};

class TestRef1
{
public:
	TestRef1():i(0)							// 默认构造函数 
	{
		cout << "TestRef1默认构造函数" << this << endl;
	}
	TestRef1(const TestRef1&testR):i(0)		// 拷贝构造函数
	{
		cout << "TestRef1拷贝构造函数" << this << endl;
	}
	~TestRef1()								// 析构函数
	{
		cout << "TestRef1析构函数" << this << endl;
	}
	mutable int i=0;
};

void funs(const TestRef&test1, const TestRef1&test2)	// 输出并修改两个类的值
{
	cout << "function " << "test1:" << &test1 <<" "<< test1.i << endl;
	cout << "function " << "test2:" << &test2 <<" "<< test2.i << endl;
	test1.i++;
	test2.i++;
}
void testFunction()										// 流程
{
	TestRef t1;
	TestRef1 t2;
	cout << "testFunction " << "t1:" << &t1 << " " << t1.i << " t2:" << " " << &t2 << " " << t2.i << endl;
	funs(t1,t2);
	cout << "testFunction " << "t1:" << &t1 <<" "<< t1.i << " t2:" <<" " << &t2 << " " << t2.i <<endl;
}
int main()
{
	testFunction();
}
```

输出：

```shell
TestRef默认构造函数	00EFF904 0
TestRef1默认构造函数	00EFF8F8 0

testFunction 
t1:					00EFF904 0
t2: 				00EFF8F8 0

function test1: 	00EFF904 0 # 【注意】地址不变，说明是引用传参
function test2:		00EFF8F8 0

testFunction 
t1:					0OEFF904 1 # 【注意】外面的值被修改，说明可以通过引用修改值
t2:					00EFF8F8 1

TestRef1　析构函数	00EFF8F8
TestRef　析构函数	00EFF904
```

### ref引用（bind/thread）

```c++
void testFunction()
{
	TestRef t1;
	TestRef1 t2;
	function<void()> f1 = bind(funs, t1, ref(t2));	// 【注意】这里是ref传参给bind函数
	f1();											// 调用函数指针
	cout << "testFunction " << "t1:" << &t1 << " " << t1.i << " t2:" << " " << &t2 << " " << t2.i << endl;
}
```

输出

```shell
TestRef默认构造函数		007BF904 0
TestRef1默认构造函数		007BF8F8 0

testFunction
t1:						007BF904 0
t2: 					007BF8F8 0

TestRef拷贝构造函数		007BF7D0	# 与原来地址不同
TestRef拷贝构造函数		01085A34	# 与原来地址不同
TestRef　　析构函数		007BF7D0

function test1:			01085A34 0 	# function中test1用的是拷贝出来的01085A34这个对象
function test2:			007BF8F8 0 	# test2用的就是传进俩的007BF8F8这个对象

testFunction
t1:						007BF904 0	# 没有改变值，用的是普通的引用传参
t2:						007BF8F8 1	# 改变了值，用的是ref传参

TestRef　　析构函数		01085A34
TestRef1　　析构函数		007BF8F8
TestRef　　析构函数		007BF904
```





































