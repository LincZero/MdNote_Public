// mytime3.h -- Time class with friends
#ifndef MYTIME3_H_
#define MYTIME3_H_
#include <iostream>

/* demo主要知识点
 * 运算符重载
 * 友元函数
 */
class Time                                                                  // 时间
{
private:
    int hours;                                                              // 小时
    int minutes;                                                            // 分钟
public:
    Time();                                                                 // 默认构造函数
    Time(int h, int m = 0);                                                 // 构造函数
    void AddMin(int m);                                                     // 加上分钟
    void AddHr(int h);                                                      // 加上小时
    void Reset(int h = 0, int m = 0);                                       // 重新设置时间
    Time operator+(const Time & t) const;                                   // 运算符重载+
    Time operator-(const Time & t) const;                                   // 运算符重载-
    Time operator*(double n) const;                                         // 运算符重载*
    friend Time operator*(double m, const Time & t)                         // 运算符重载*（友元）
        { return t * m; }   // inline definition
    friend std::ostream & operator<<(std::ostream & os, const Time & t);    // 运算符重载<<（友元）
};
#endif
