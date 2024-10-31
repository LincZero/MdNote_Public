// queue.h -- interface for a queue
#ifndef QUEUE_H_
#define QUEUE_H_
// This queue will contain Customer items
/* 知识点：
 * 队列的实现原理：链表（而不是数组或循环数组）
 * 
 * new对象
 * 包含类
 * 
 * 成员初始化列表语法
 * 
 * 私有的复制构造函数和赋值运算符重载（伪私有方法）
 * 作用：抢先定义，以防止公开复制
 */
class Customer                                              // 客户
{
private:
    long arrive;                                            // 客户到达时间 arrival time for customer
    int processtime;                                        // 客户处理业务的时间 processing time for customer
public:
    Customer() : arrive(0), processtime (0){}               // 构造函数（内联）
    void set(long when);                                    // 设置客户属性
    long when() const { return arrive; }                    // 显示客户到达时间
    int ptime() const { return processtime; }               // 显示客户处理业务时间
};

typedef Customer Item;                                      // 客户作为队列Item

class Queue                                                 // 队列（好像不允许索引来着）
{
private:
// class scope definitions
    // Node is a nested structure definition local to this class
    struct Node { Item item; struct Node * next;};          // 表示链表节点的结构体（单向链表）
    enum {Q_SIZE = 10};                                     // 枚举
// private class members
    Node * front;                                           // 前端指针 pointer to front of Queue
    Node * rear;                                            // 后端指针 pointer to rear of Queue
    int items;                                              // 队列项数 current number of items in Queue
    const int qsize;                                        // 队列允许的最大项数 maximum number of items in Queue
    // 抢先定义，以防止公开复制 preemptive definitions to prevent public copying
    Queue(const Queue & q) : qsize(0) { }                   // 复制构造函数（第一次见私有的复制构造函数哎）
    Queue & operator=(const Queue & q) { return *this;}     // 运算符重载=（第一次见私有的赋值运算符重载哎）
public:
    Queue(int qs = Q_SIZE);                                 // 构造函数 create queue with a qs limit
    ~Queue();                                               // 析构函数
    bool isempty() const;                                   // 是否为空
    bool isfull() const;                                    // 是否满了
    int queuecount() const;                                 // 队列项数
    bool enqueue(const Item &item);                         // 末尾增加成员 add item to end
    bool dequeue(Item &item);                               // 删除首位成员 remove item from front
};
#endif
