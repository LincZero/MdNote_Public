// acctabc.h  -- bank account classes
#ifndef ACCTABC_H_
#define ACCTABC_H_
#include <iostream>
#include <string>
/* 知识点：
 * 保护继承
 * 抽象基类
 * 纯虚函数
 */

// Abstract Base Class
class AcctABC                                                   // 支票账号的抽象基类
{
private:
    std::string fullName;                                       // 客户全名
    long acctNum;                                               // 账号名
    double balance;                                             // 余额
protected:                                                      // 保护继承（一般可以放辅助方法）
    struct Formatting                                           // 用于设置输出格式
    {
         std::ios_base::fmtflags flag;                          // ？？？里面是什么鬼东西啊
         std::streamsize pr;
    };
    const std::string & FullName() const {return fullName;}     // 返回用户名
    long AcctNum() const {return acctNum;}                      // 返回账号名
    Formatting SetFormat() const;                               // 设置格式并返回（账号基本信息）
    void Restore(Formatting & f) const;                         // 用于恢复输出格式
public: 
    AcctABC(const std::string & s = "Nullbody", long an = -1,   // 构造函数
                double bal = 0.0);
    void Deposit(double amt) ;                                  // 往内存款
    virtual void Withdraw(double amt) = 0;                      // 取钱（纯虚函数） pure virtual function
    double Balance() const {return balance;};                   // 返回余额
    virtual void ViewAcct() const = 0;                          // 打印账号相关信息（纯需函数） pure virtual function
    virtual ~AcctABC() {}                                       // 析构函数（虚函数）
};

// Brass Account Class
class Brass :public AcctABC                                     // 普通支票账号
{
public:
    Brass(const std::string & s = "Nullbody", long an = -1,     // 构造函数
           double bal = 0.0) : AcctABC(s, an, bal) { }
    virtual void Withdraw(double amt);                          // 取钱（虚函数）
    virtual void ViewAcct() const;                              // 打印账号信息（虚函数）
    virtual ~Brass() {}                                         // 析构函数（虚函数）
};

//Brass Plus Account Class
class BrassPlus : public AcctABC                                // 能透支的支票账号
{
private:
    double maxLoan;                                             // 透支上限
    double rate;                                                // 利率
    double owesBank;                                            // 当前透支的总额
public:
    BrassPlus(const std::string & s = "Nullbody", long an = -1, // 构造函数
            double bal = 0.0, double ml = 500,
            double r = 0.10);
    BrassPlus(const Brass & ba, double ml = 500, double r = 0.1);// 构造函数
    virtual void ViewAcct()const;                               // 打印账号信息（虚函数）
    virtual void Withdraw(double amt);                          // 取钱
    void ResetMax(double m) { maxLoan = m; }                    // 重设透支上限
    void ResetRate(double r) { rate = r; };                     // 重设利率
    void ResetOwes() { owesBank = 0; }                          // 重设当前透支的总额为零
};

#endif
