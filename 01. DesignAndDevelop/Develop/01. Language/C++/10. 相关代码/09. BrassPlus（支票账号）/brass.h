// brass.h  -- bank account classes
#ifndef BRASS_H_
#define BRASS_H_
#include <string>
/* 知识点：
 * 多态公有继承
 * 虚方法
 */
// Brass Account Class
class Brass                                                     // 支票账号
{
private:
    std::string fullName;                                       // 客户姓名
    long acctNum;                                               // 账号
    double balance;                                             // 余额
public:
    Brass(const std::string & s = "Nullbody", long an = -1,     // 构造函数
                double bal = 0.0);
    void Deposit(double amt);                                   // 往内存款
    virtual void Withdraw(double amt);                          // 取钱（虚方法）
    double Balance() const;                                     // 返回余额
    virtual void ViewAcct() const;                              // 打印账号相关信息（虚方法）
    virtual ~Brass() {}                                         // 析构函数
};

//Brass Plus Account Class
class BrassPlus : public Brass                                  // 支票账户Plus（可透支）
{
private:
    double maxLoan;                                             // 透支上限
    double rate;                                                // 透支贷款利率
    double owesBank;                                            // 当前透支的总额
public:
    BrassPlus(const std::string & s = "Nullbody", long an = -1, // 构造函数
            double bal = 0.0, double ml = 500,
            double r = 0.11125);
    BrassPlus(const Brass & ba, double ml = 500,                // 构造函数
		                        double r = 0.11125);
    virtual void ViewAcct()const;                               // 打印账号相关信息（多态）（虚方法）
    virtual void Withdraw(double amt);                          // 取钱（多态）（虚方法）
    void ResetMax(double m) { maxLoan = m; }                    // 重设透支上限
    void ResetRate(double r) { rate = r; };                     // 重设利率
    void ResetOwes() { owesBank = 0; }                          // 清零当前透支的总额
};

#endif
