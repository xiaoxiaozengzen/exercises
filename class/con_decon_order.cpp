#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <functional>

class A {
public:
    A() { std::cout << "A constructed" << std::endl; }
    A(int x) { std::cout << "A constructed with parameter: " << x << std::endl; }
    ~A() { std::cout << "A destructed" << std::endl; }
    A(const A&) { std::cout << "A copy constructed" << std::endl; }
    A& operator=(const A&) { std::cout << "A copy assigned" << std::endl; return *this; }
};

class B {
public:
    B() { std::cout << "B constructed" << std::endl; }
    B(int x) { std::cout << "B constructed with parameter: " << x << std::endl; }
    ~B() { std::cout << "B destructed" << std::endl; }
    B(const B&) { std::cout << "B copy constructed" << std::endl; }
    B& operator=(const B&) { std::cout << "B copy assigned" << std::endl; return *this; }
};

class C {
public:
    C() { std::cout << "C constructed" << std::endl; }
    C(int x) { std::cout << "C constructed with parameter: " << x << std::endl; }
    ~C() { std::cout << "C destructed" << std::endl; }
    C(const C&) { std::cout << "C copy constructed" << std::endl; }
    C& operator=(const C&) { std::cout << "C copy assigned" << std::endl; return *this; }
};

class ClassInit {
public:
    A a;
    A a1;
    B b;
    C c;

    ClassInit() {
        std::cout << "ClassInit constructed" << std::endl;
    }

    ClassInit(int x):a(A(2)) {
        c = C(2); // 构造函数内部做初始化
        std::cout << "ClassInit constructed with parameter: " << x << std::endl;
    }

    ~ClassInit() {
        std::cout << "ClassInit destructed" << std::endl;
    }
};

/**
 * 类成员的三种初始化方式:
 *  1.成员声明的同时做初始化，姑且称为默认初始化
 *  2.使用成员初始化列表进行初始化，以下情况必须使用这种方式：
 *    - 当初始化引用类型的成员时
 *    - 初始化一个常量成员时(c++11之后不再适用，因为可以使用默认成员初始化)
 *    - 当需要使用父类有参数的构造函数时
 *    - 委托构造
 *  3.构造函数内部做初始化
 *    - 这种方式不算初始化，属于赋值操作
 * 
 * 类成员初始化顺序：
 *   - 无论采用哪种初始化方式，类成员的初始化顺序始终跟成员的声明顺序相同。
 *   - 析构的时候按照声明顺序的倒序进行析构。
 * 
 * 三者的优先级关系：
 *   - 如果默认初始化和列表初始化同时存在，则默认初始化的值会被忽略（注意不是被二次赋值覆盖，而是会忽略！！）
 *   - 列表初始化的代码会被编译器插入到构造函数的开始处，先于手写的代码执行。
 * 
 * 如果还有父类，则其大致初始化顺序：
 *   - 父类构造函数
 *   - 成员变量初始化，跟声明顺序一致
 *   - 类自己的构造函数
 * 大致的析构顺序：
 *   - 类自己的析构函数
 *   - 成员变量析构，跟声明顺序的倒序一致
 *   - 父类析构函数
 */
void class_init() {
    A a = A(); // 默认初始化
    std::cout << "------------------start class init------------------" << std::endl;
    ClassInit ci1(1);
    std::cout << "------------------end class init------------------" << std::endl;
}

class D {
public:
    D() { std::cout << "D constructed" << std::endl; }
    D(int x) { std::cout << "D constructed with parameter: " << x << std::endl; }
    ~D() { std::cout << "D destructed" << std::endl; }
    D(const D&) { std::cout << "D copy constructed" << std::endl; }
    D& operator=(const D&) { std::cout << "D copy assigned" << std::endl; return *this; }
};

class Derive : public ClassInit {
public:
    Derive() : ClassInit(3), d(4) { // 使用成员初始化列表进行初始化
        std::cout << "Derive constructed" << std::endl;
    }

    ~Derive() {
        std::cout << "Derive destructed" << std::endl;
    }

public:
    D d;
};

void drive_class_init() {
    std::cout << "------------------drive class init------------------" << std::endl;
    Derive d;
    std::cout << "------------------end drive class init------------------" << std::endl;
}


/**
 * 多线程环境下，构造和析构的顺序可能会受到线程调度的影响。
 *    - 在即将析构对象时，怎么知道其他线程是否在使用这个对象？
 *    - 如何在保证执行成员函数的时候，对象不会在另一个线程中被析构？
 *    - 在调用某个对象的成员函数之前，如何得知这个对象还活着？它的析构函数会不会刚执行到一半？
 */
class BaseClass {
public:
    BaseClass():data_(std::make_shared<int>(42)) {
        std::cout << "BaseClass constructed" << std::endl;
        Init(); // 调用Init函数
        this->Init(); // 调用Init函数
        th_ = std::thread([this](){
            while(true) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                this->doSomething();
                Init(); // 调用Init函数
            }
        });
    }

    virtual void Init() {
        std::cout << "BaseClass Init called" << std::endl;
    }

    virtual ~BaseClass() { 
        std::cout << "BaseClass destructed" << std::endl;
        th_.join(); // 等待线程结束
    }

    virtual void doSomething() {
        std::cout << "Doing something with ptr: " << *data_ << std::endl;
    }

public:
    std::thread th_;
    std::shared_ptr<int> data_{nullptr}; // 使用智能指针管理资源
};

class DerivedClass : public BaseClass {
public:
    DerivedClass():data_(std::make_shared<int>(10)) { 
        std::cout << "DerivedClass constructed" << std::endl; 
    }
    ~DerivedClass() { std::cout << "DerivedClass destructed" << std::endl; }
public:
    void doSomething() override{
        std::cout << "DerivedClass doing something with data: " << *data_ << std::endl;
    }

    void Init() override {
        std::cout << "DerivedClass Init called" << std::endl;
    }

    void Fun() {
        std::cout << "DerivedClass Fun called" << std::endl;
    }

    std::shared_ptr<int> data_{nullptr};
};

void thread_safe_class_init() {
    std::shared_ptr<BaseClass> basePtr = std::make_shared<DerivedClass>();
    basePtr->doSomething();
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 等待
}

int main() {
    std::cout << "=============lass init=============" << std::endl;
    class_init();
    std::cout << "=============drive class init=============" << std::endl;
    drive_class_init();
    std::cout << "=============thread safe class init=============" << std::endl;
    thread_safe_class_init();
    return 0;
}