// studenti.h -- defining a Student class using private inheritance
#ifndef STUDENTC_H_
#define STUDENTC_H_

#include <iostream>                                                 // 输入输出流
#include <valarray>                                                 // 数值数组
#include <string>                                                   // 字符串
/* 知识点：
 * 初始化顺序
 * 包含类对象 
 * 私有继承、多重继承
 * 包含和私有继承的比较
 */
class Student : private std::string, private std::valarray<double>  // 学生（私有继承与多重继承版本）
{   
private:
    typedef std::valarray<double> ArrayDb;                          // 重命名变量类型
    // private method for scores output
    std::ostream & arr_out(std::ostream & os) const;                // 私有辅助方法
public:
    Student() : std::string("Null Student"), ArrayDb() {}           // 默认构造函数
    explicit Student(const std::string & s)                         // 构造函数（限制隐式转换）
            : std::string(s), ArrayDb() {}
    explicit Student(int n) : std::string("Nully"), ArrayDb(n) {}   // 构造函数（限制隐式转换）
    Student(const std::string & s, int n)                           // 构造函数
            : std::string(s), ArrayDb(n) {}
    Student(const std::string & s, const ArrayDb & a)               // 构造函数
            : std::string(s), ArrayDb(a) {}
    Student(const char * str, const double * pd, int n)             // 构造函数
            : std::string(str), ArrayDb(pd, n) {}
    ~Student() {}                                                   // 析构函数
    double Average() const;                                         // 平均值
    double & operator[](int i);                                     // 运算符重载[]
    double operator[](int i) const;                                 // 运算符重载[]
    const std::string & Name() const;                               // 返回名字
// friends
    // input
    friend std::istream & operator>>(std::istream & is,             // 运算符重载>>
                                     Student & stu);  // 1 word
    friend std::istream & getline(std::istream & is,                // 
                                  Student & stu);     // 1 line
    // output
    friend std::ostream & operator<<(std::ostream & os,             // 运算符重载<<
                                     const Student & stu);
};

#endif
