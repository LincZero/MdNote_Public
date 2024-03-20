// stack.h -- class definition for the stack ADT
#ifndef STACK_H_
#define STACK_H_

/* 定义存储栈层数据的类型
 * 缺点是需要修改头文件
 * 后面学模板类会比较舒服
 */
typedef unsigned long Item;                 

/* demo主要知识点
 * 抽象数据类型
 * 作用域为类的常量
 */
class Stack                                 // 栈类
{
private:
    enum {MAX = 10};                        // 栈层 constant specific to class
    Item items[MAX];                        // 保存栈数据 holds stack items
    int top;                                // 栈顶位置 index for top stack item
public:
    Stack();                                // 构造函数
    bool isempty() const;                   // 查看栈是否为空（const成员函数）
    bool isfull() const;                    // 查看栈是否填满（const成员函数）
    // push() 如果堆栈已满则返回false，否则返回true
    bool push(const Item & item);           // 压入 add item to stack
    // pop() 如果堆栈已为空，则返回false，否则返回true
    bool pop(Item & item);                  // 弹出 pop top into item
};
#endif
