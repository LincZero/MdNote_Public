// tabtenn1.h -- a table-tennis base class
#ifndef TABTENN1_H_
#define TABTENN1_H_
#include <string>
using std::string;
/* 知识点：
 * 公有派生
 * 成员初始化列表
 */
// simple base class
class TableTennisPlayer                                             // 基类：乒乓球会员
{
private:
    string firstname;                                               // 名
    string lastname;                                                // 姓
    bool hasTable;                                                  // 是否有球桌
public:
    TableTennisPlayer (const string & fn = "none",                  // 构造函数
                       const string & ln = "none", bool ht = false);
    void Name() const;                                              // 打印名字
    bool HasTable() const { return hasTable; };                     // 有乒乓球（内联）
    void ResetTable(bool v) { hasTable = v; };                      // 重设有无乒乓球（内联）
};

// simple derived class
class RatedPlayer : public TableTennisPlayer                        // 派生类：乒乓球会员的比分
{
private:
    unsigned int rating;                                            // 分数/比分
public:
    RatedPlayer (unsigned int r = 0, const string & fn = "none",    // 构造方法
                 const string & ln = "none", bool ht = false);
    RatedPlayer(unsigned int r, const TableTennisPlayer & tp);      // 构造方法
    unsigned int Rating() const { return rating; }                  // 获取分数
    void ResetRating (unsigned int r) {rating = r;}                 // 重设分数
};

#endif
