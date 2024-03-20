// workermi.cpp -- working class methods with MI
#include "workermi.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
// Worker methods
Worker::~Worker() { }

// protected methods
void Worker::Data() const                           // 保护方法版本负责访问私有变量
{
    cout << "Name: " << fullname << endl;
    cout << "Employee ID: " << id << endl;
}

void Worker::Get()                                  // 保护方法版本负责访问私有变量
{
    getline(cin, fullname);
    cout << "Enter worker's ID: ";
    cin >> id;
    while (cin.get() != '\n')
        continue;
}

// Waiter methods
void Waiter::Set()                                  // 公有方法版本调用保护方法版本
{
    cout << "Enter waiter's name: ";
    Worker::Get();
    Get();
}

void Waiter::Show() const                           // 公有方法版本调用保护方法版本
{
    cout << "Category: waiter\n";
    Worker::Data();
    Data();
}

// protected methods
void Waiter::Data() const
{
    cout << "Panache rating: " << panache << endl;  // 保护方法版本负责访问私有变量
}

void Waiter::Get()                                  // 保护方法版本负责访问私有变量
{
    cout << "Enter waiter's panache rating: ";
    cin >> panache;
    while (cin.get() != '\n')
        continue;
}

// Singer methods

char * Singer::pv[Singer::Vtypes] = {"other", "alto", "contralto",
            "soprano", "bass", "baritone", "tenor"};

void Singer::Set()                                  // 同上
{
    cout << "Enter singer's name: ";
    Worker::Get();
    Get();
}

void Singer::Show() const                           // 同上
{
    cout << "Category: singer\n";
    Worker::Data();
    Data();
}

// protected methods
void Singer::Data() const                           // 同上
{
    cout << "Vocal range: " << pv[voice] << endl;
}

void Singer::Get()                                  // 同上
{
    cout << "Enter number for singer's vocal range:\n";
    int i;
    for (i = 0; i < Vtypes; i++)
    {
        cout << i << ": " << pv[i] << "   ";
        if ( i % 4 == 3)
            cout << endl;
    }
    if (i % 4 != 0)
        cout << '\n';
    while (cin >>  voice && (voice < 0 || voice >= Vtypes) )
        cout << "Please enter a value >= 0 and < " << Vtypes << endl;
    while (cin.get() != '\n')
        continue;
}

// SingingWaiter methods
void SingingWaiter::Data() const                    // 保护方法版本负责访问私有变量
{
    Singer::Data();
    Waiter::Data();
}

void SingingWaiter::Get()                           // 保护方法版本负责访问私有变量
{
    Waiter::Get();
    Singer::Get();
}

void SingingWaiter::Set()                           // 公有方法版本调用保护方法版本
{
    cout << "Enter singing waiter's name: ";
    Worker::Get();
    Get();
}

void SingingWaiter::Show() const                    // 公有方法版本调用保护方法版本
{
    cout << "Category: singing waiter\n";
    Worker::Data();
    Data();
}
