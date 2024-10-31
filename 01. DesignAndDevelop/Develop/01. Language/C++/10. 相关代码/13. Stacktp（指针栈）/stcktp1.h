// stcktp1.h -- modified Stack template
#ifndef STCKTP1_H_
#define STCKTP1_H_
/* 知识点：
 * 类模板
 * 注意点：涉及类成员new
 */
template <class Type>
class Stack                                             // 栈
{
private:
    enum {SIZE = 10};                                   // 枚举 default size
    int stacksize;                                      // 栈大小
    Type * items;                                       // 存储指针的类型 holds stack items
    int top;                                            // 栈项 index for top stack item
public:
    explicit Stack(int ss = SIZE);                      // 构造函数（禁止隐式转换）
    Stack(const Stack & st);                            // 复制构造函数【避免成员复制】
    ~Stack() { delete [] items; }                       // 析构函数
    bool isempty() { return top == 0; }                 // 是否为空
    bool isfull() { return top == stacksize; }          // 是否满了
    bool push(const Type & item);                       // 压入 add item to stack
    bool pop(Type & item);                              // 弹出 pop top into item
    Stack & operator=(const Stack & st);                // 赋值运算符重载【避免成员复制】
};

template <class Type>
Stack<Type>::Stack(int ss) : stacksize(ss), top(0)      // 构造函数
{
    items = new Type [stacksize];
}

template <class Type>
Stack<Type>::Stack(const Stack & st)                    // 构造函数
{
    stacksize = st.stacksize;
    top = st.top;
    items = new Type [stacksize];
    for (int i = 0; i < top; i++)
        items[i] = st.items[i];
}

template <class Type>
bool Stack<Type>::push(const Type & item)               // 压入
{
    if (top < stacksize)
    {
        items[top++] = item;
        return true;
    }
    else
        return false;
}

template <class Type>
bool Stack<Type>::pop(Type & item)                      // 弹出
{
    if (top > 0)
    {
        item = items[--top];
        return true;
    }
    else
        return false;
}

template <class Type>
Stack<Type> & Stack<Type>::operator=(const Stack<Type> & st) // 运算符重载
{
    if (this == &st)
        return *this;
    delete [] items;
    stacksize = st.stacksize;
    top = st.top;
    items = new Type [stacksize];
    for (int i = 0; i < top; i++)
        items[i] = st.items[i];
    return *this; 
}

#endif
