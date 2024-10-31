// string1.h -- fixed and augmented string class definition

#ifndef STRING1_H_
#define STRING1_H_
#include <iostream>
using std::ostream;
using std::istream;
/* 知识点：
 * 默认提供的成员函数，主要用到下面三个
 * 1. 默认构造函数
 * 2. 默认赋值构造函数（浅赋值）
 * 3. 赋值运算符（浅赋值）
 * 
 * 类中创建的动态成员
 * 1. 注意不仅仅是构造函数，复制构造函数和赋值运算符都要手动new对象
 * 2. 注意不仅仅是析构函数，赋值运算符也要手动delete对象
 * 3. 注意浅赋值所带来的问题及解决方案（需要真正意义上复制new对象）
 * 
 * 静态类成员函数和变量
 */
class String                                                            // 字符串
{
private:
    char * str;                                                         // 字符串指针 pointer to string
    int len;                                                            // 字符串长度 length of string
    static int num_strings;                                             // 对象个数（静态） number of objects
    static const int CINLIM = 80;                                       // cin输入限制（静态） cin input limit
public:
// constructors and other methods
    String(const char * s);                                             // 构造函数 constructor
    String();                                                           // 默认构造函数 default constructor   // 【浅赋值问题】
    String(const String &);                                             // 默认复制构造函数 copy constructor
    ~String();                                                          // 析构函数 destructor
    int length () const { return len; }                                 // 返回字符串长度
// overloaded operator methods    
    String & operator=(const String &);                                 // 运算符重载=对象赋值               // 【浅赋值问题】
    String & operator=(const char *);                                   // 运算符重载=
    char & operator[](int i);                                           // 运算符重载[]
    const char & operator[](int i) const;                               // 运算符重载[]
// overloaded operator friends
    friend bool operator<(const String &st, const String &st2);         // 运算符重载<（友元）
    friend bool operator>(const String &st1, const String &st2);        // 运算符重载>（友元）
    friend bool operator==(const String &st, const String &st2);        // 运算符重载==（友元）
    friend ostream & operator<<(ostream & os, const String & st);       // 运算符重载<<（友元）
    friend istream & operator>>(istream & is, String & st);             // 运算符重载>>（友元）
// static function
    static int HowMany();                                               // 返回创建了多少个对象（静态方法）
};
#endif
