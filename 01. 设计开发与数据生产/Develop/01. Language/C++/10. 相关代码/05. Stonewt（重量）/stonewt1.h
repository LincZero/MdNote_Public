// stonewt1.h -- revised definition for the Stonewt class
#ifndef STONEWT1_H_
#define STONEWT1_H_
/* 知识点：
 * 自动类型转换
 * 转换函数
 */
/* 补充
 * LBS是英文pounds（磅） 一种不恰当的缩写
 * st或stn是stone（英石）的缩写
 */
class Stonewt                       // 重量
{
private:
    enum {Lbs_per_stn = 14};        // 枚举量，换算值 pounds per stone
    int stone;                      // 英石（单位） whole stones
    double pds_left;                // fractional pounds
    double pounds;                  // 英镑（单位） entire weight in pounds
public:
    Stonewt(double lbs);            // 构造函数（允许自动类型转换） construct from double pounds
    Stonewt(int stn, double lbs);   // 构造函数 construct from stone, lbs
    Stonewt();                      // 默认构造函数 default constructor
    ~Stonewt();                     // 析构函数
    void show_lbs() const;          // 显示英镑重量 show weight in pounds format
    void show_stn() const;          // 显示英石重量 show weight in stone format
// conversion functions
    operator int() const;           // 类型转换函数
    operator double() const;        // 类型转换函数
};
#endif
