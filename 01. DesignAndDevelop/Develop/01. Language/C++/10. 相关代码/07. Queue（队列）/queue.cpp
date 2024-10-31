// queue.cpp -- Queue and Customer methods
#include "queue.h"
#include <cstdlib>         // (or stdlib.h) for rand()

// Queue methods
Queue::Queue(int qs) : qsize(qs)            // 构造函数，指出队列的最大项
{
    front = rear = NULL;                    // 设置前和后指针均为空 or nullptr
    items = 0;                              // 项目数为0
}

Queue::~Queue()                             // 析构函数                 // 【核心方法】
{                                           // 要delete删除队列里所有new出来的项
    Node * temp;
    while (front != NULL)                   // while queue is not yet empty
    {
        temp = front;                       // save address of front item
        front = front->next;                // reset pointer to next item
        delete temp;                        // delete former front
    }
}

bool Queue::isempty() const                 // 是否为空
{
    return items == 0;
}

bool Queue::isfull() const                  // 是否满了
{
    return items == qsize;
}

int Queue::queuecount() const               // 队列项数
{
    return items;
}

// Add item to queue
bool Queue::enqueue(const Item & item)      // 末尾增加成员               // 【核心方法】
{
    if (isfull())                           // 检测是否已满
        return false;
    Node * add = new Node;                  // 创建位于末端的节点 create node
// on failure, new throws std::bad_alloc exception
    add->item = item;                       // 设置节点的项目 set node pointers
    add->next = NULL;                       // 设置节点的下个地址为空（这是一个往后的单向链表） or nullptr;
    items++;                                // 项目数+1
    if (front == NULL)                      // 如果前面没项，则将其设为前端地址 if queue is empty,
        front = add;                            // place item at front
    else                                    // 如果前面有项，则设置前一个节点的地址
        rear->next = add;                       // else place at rear
    rear = add;                             // 将该节点设为前端 have rear point to new node
    return true;
}

// Place front item into item variable and remove from queue
bool Queue::dequeue(Item & item)            // 删除首位成员               // 【核心方法】
{                                           // 即把首位项目delete掉，并把下个节点设置为首位
    if (front == NULL)
        return false;
    item = front->item;                     // set item to first item in queue
    items--;
    Node * temp = front;                    // save location of first item
    front = front->next;                    // reset front to next item
    delete temp;                            // 注意new的对象要delete掉 delete former first item
    if (items == 0)
        rear = NULL;
    return true;
}

// 客户方法 customer method

// 客户何时到达 when is the time at which the customer arrives
// 到达时间设置为何时和处理 the arrival time is set to when and the processing
// 时间设置为1-3的随机值 time set to a random value in the range 1 - 3
void Customer::set(long when)
{
    processtime = std::rand() % 3 + 1;      // 设置客户处理业务的时间
    arrive = when;                          // 设置客户到达时间
}
