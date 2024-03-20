// workermi.h  -- working classes with MI
#ifndef WORKERMI_H_
#define WORKERMI_H_

#include <string>
/* 知识点：
 * 多重继承，以及多重继承的两个问题
 * - 虚基类
 * - 纯虚基类多重继承的写法
 */
class Worker                                                // 工作者（抽象基类）an abstract base class
{
private:
    std::string fullname;                                   // 全名
    long id;                                                // id
protected:
    virtual void Data() const;                              // 打印数据（虚方法）
    virtual void Get();                                     // 获取数据（虚方法）
public:
    Worker() : fullname("no one"), id(0L) {}                // 构造函数
    Worker(const std::string & s, long n)
            : fullname(s), id(n) {}
    virtual ~Worker() = 0;                                  // 析构函数（纯虚方法） pure virtual function
    virtual void Set() = 0;                                 // 设置（纯虚方法）
    virtual void Show() const = 0;                          // 展示（纯虚方法）
};

class Waiter : virtual public Worker                        // 侍者（虚基类公有继承）
{
private:
    int panache;
protected:
    void Data() const;                                      // 打印数据（保护）
    void Get();                                             // 获取数据（保护）
public:
    Waiter() : Worker(), panache(0) {}                      // 构造函数
    Waiter(const std::string & s, long n, int p = 0)        // 构造函数
            : Worker(s, n), panache(p) {}
    Waiter(const Worker & wk, int p = 0)                    // 构造函数
            : Worker(wk), panache(p) {}
    void Set();                                             // 获取数据（公有）
    void Show() const;                                      // 打印数据（公有）
};

class Singer : virtual public Worker                        // 唱歌者（虚基类公有继承）
{
protected:
enum {other, alto, contralto, soprano,                      // 枚举
                    bass, baritone, tenor};
    enum {Vtypes = 7};                                      // 枚举
    void Data() const;                                      // 打印数据（保护）
    void Get();                                             // 获取数据（保护）
private:
    static char *pv[Vtypes];                                // string equivs of voice types
    int voice;
public:
    Singer() : Worker(), voice(other) {}
    Singer(const std::string & s, long n, int v = other)
            : Worker(s, n), voice(v) {}
    Singer(const Worker & wk, int v = other)
            : Worker(wk), voice(v) {}
    void Set();                                             // 获取数据（公有）
    void Show() const;                                      // 打印数据（公有）
};

// multiple inheritance
class SingingWaiter : public Singer, public Waiter          // 唱歌侍者（公有多重继承）
{
protected:
    void Data() const;                                      // 打印数据（保护）
    void Get();                                             // 获取数据（保护）
public:
    SingingWaiter()  {}                                     // 构造方法
    SingingWaiter(const std::string & s, long n, int p = 0, // 构造方法
                            int v = other)
            : Worker(s,n), Waiter(s, n, p), Singer(s, n, v) {}
    SingingWaiter(const Worker & wk, int p = 0, int v = other)// 构造方法
            : Worker(wk), Waiter(wk,p), Singer(wk,v) {}
    SingingWaiter(const Waiter & wt, int v = other)         // 构造方法
            : Worker(wt),Waiter(wt), Singer(wt,v) {}
    SingingWaiter(const Singer & wt, int p = 0)             // 构造方法
            : Worker(wt),Waiter(wt,p), Singer(wt) {}
    void Set();                                             // 获取数据（公有）
    void Show() const;                                      // 打印数据（公有）
};

#endif
