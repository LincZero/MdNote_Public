// stock20.h -- augmented version
#ifndef STOCK20_H_
#define STOCK20_H_
#include <string>

/* 知识点：const成员函数
 * const后缀表明
 * 1.该方法不会改变类成员属性
 * 2.即使对象实例被声明为const类型仍然能访问该函数）
 */
/* 知识点：this指针
 */
class Stock                                                     // 股票类
{
private:
    std::string company;                                        // 公司名（string类存储）
    int shares;                                                 // 持有股份数
    double share_val;                                           // 单股股价
    double total_val;                                           // 持有总股值
    void set_tot() { total_val = shares * share_val; }          // 设置总股价
public:
  //  Stock();        // default constructor
    Stock(const std::string & co, long n = 0, double pr = 0.0);
    ~Stock();       // do-nothing destructor
    void buy(long num, double price);                           // 买入
    void sell(long num, double price);                          // 卖出
    void update(double price);                                  // 股价变化、更新股价
    void show()const;                                           // 展示查看（知识点）
    const Stock & topval(const Stock & s) const;                // 比较两个实例，并返回大的那一个
};

#endif
