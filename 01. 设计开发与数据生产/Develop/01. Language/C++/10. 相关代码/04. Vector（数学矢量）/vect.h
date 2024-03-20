// vect.h -- Vector class with <<, mode state
#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
/* 知识点：
 * 类 x 命名空间
 * 运算符重载
 * 友元
 * 状态成员的技巧
 */
namespace VECTOR
{
    class Vector                                                    // 数学矢量
    {
    public:
        enum Mode {RECT, POL};                                      // 枚举量，模式：矩形or极坐标
    // RECT for rectangular, POL for Polar modes
    private:
        double x;                                                   // 水平x坐标 horizontal value
        double y;                                                   // 垂直y坐标 vertical value
        double mag;                                                 // 矢量长度 length of vector
        double ang;                                                 // 矢量角度 direction of vector in degrees
        Mode mode;                                                  // 模式（直角or极坐标）（状态成员） RECT or POL
    // private methods for setting values
        void set_mag();                                             // 设置矢量长度
        void set_ang();                                             // 设置矢量角度
        void set_x();                                               // 设置x坐标
        void set_y();                                               // 设置y坐标
    public:
       Vector();                                                    // 默认构造函数
        Vector(double n1, double n2, Mode form = RECT);             // 构造函数
        void reset(double n1, double n2, Mode form = RECT);         // 重新设置值
        ~Vector();                                                  // 析构函数
        double xval() const {return x;}                             // 显示x值 report x value
        double yval() const {return y;}                             // 显示y值 report y value
        double magval() const {return mag;}                         // 显示长度值 report magnitude
        double angval() const {return ang;}                         // 显示角度值 report angle
        void polar_mode();                                          // 设置为极坐标模式 set mode to POL
        void rect_mode();                                           // 设置为直角坐标模式 set mode to RECT
    // operator overloading
        Vector operator+(const Vector & b) const;                   // 运算符重载+
        Vector operator-(const Vector & b) const;                   // 运算符重载-
        Vector operator-() const;                                   // 运算符重载-
        Vector operator*(double n) const;                           // 运算符重载*
    // friends
        friend Vector operator*(double n, const Vector & a);        // 运算符重载*（友元）
        friend std::ostream & operator<<(std::ostream & os, const Vector & v);  // 运算符重载<<（友元）
    };

}   // end namespace VECTOR
#endif
