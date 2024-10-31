// string1.cpp -- String class methods
#include <cstring>                 // string.h for some
#include "string1.h"               // includes <iostream>
using std::cin;
using std::cout;

// initializing static class member

int String::num_strings = 0;

// static method
int String::HowMany()
{
    return num_strings;
}

// class methods
String::String(const char * s)              // 构造函数 construct String from C string
{
    len = std::strlen(s);                   // 查看长度 set size
    str = new char[len + 1];                // 动态创建 allot storage
    std::strcpy(str, s);                    // 初始化字符串 initialize pointer
    num_strings++;                          // 对象加一 set object count
}

String::String()                            // 默认构造函数 default constructor
{
    len = 4;
    str = new char[1];
    str[0] = '\0';                          // 默认字符串 default string
    num_strings++;                          // 对象加一 
}

String::String(const String & st)           // 复制构造函数                           // 【浅赋值问题】
{
    num_strings++;                          // 对象加一 handle static member update
    len = st.len;                           // 复制字符串1 same length                // new并真正意义上复制字符串
    str = new char [len + 1];               // 复制字符串2 allot space
    std::strcpy(str, st.str);               // 复制字符串3 copy string to new location
}

String::~String()                           // 析构函数
{
    --num_strings;                          // 对象减一
    delete [] str;                          // 删除动态创建的成员 - 字符串
}

// overloaded operator methods    

    // assign a String to a String
String & String::operator=(const String & st)// 运算符重载（赋值运算符）                // 【浅赋值问题】
{
    if (this == &st)                        // 如果是自己赋值给自己，delete掉再new也行，但消耗性能
        return *this;                       // 最好的方式是什么都不作
    delete [] str;                                                                      // 删除对象
    len = st.len;                           // 复制字符串1 same length                  // new并真正意义上复制字符串
    str = new char[len + 1];                // 复制字符串2 allot space
    std::strcpy(str, st.str);               // 复制字符串3 copy string to new location
    return *this;
}

    // assign a C string to a String
String & String::operator=(const char * s)
{
    delete [] str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    return *this;
}

    // read-write char access for non-const String
char & String::operator[](int i)
{
    return str[i];
}

    // read-only char access for const String
const char & String::operator[](int i) const
{
    return str[i];
}

// overloaded operator friends

bool operator<(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) < 0);
}

bool operator>(const String &st1, const String &st2)
{
    return st2 < st1;
}

bool operator==(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) == 0);
}

    // simple String output
ostream & operator<<(ostream & os, const String & st)
{
    os << st.str;
    return os; 
}

    // quick and dirty String input
istream & operator>>(istream & is, String & st)
{
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);
    if (is)
        st = temp;
    while (is && is.get() != '\n')
        continue;
    return is; 
}
