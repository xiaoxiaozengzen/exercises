#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <functional>

class A {
public:
    int a;
public:
    A() { std::cout << "A constructed" << std::endl; }
    A(int x):a(x) { std::cout << "A constructed with parameter: " << x << std::endl; }
    ~A() { std::cout << "A destructed" << std::endl; }
    A(const A& other) { 
        a = other.a;
        std::cout << "A copy constructed" << std::endl; 
    }
    A& operator=(const A& other) { 
        a = other.a;
        std::cout << "A copy assigned" << std::endl; return *this; 
    }
};

class B {
public:
    int b;
public:
    B() { std::cout << "B constructed" << std::endl; }
    B(int x):b(x) { std::cout << "B constructed with parameter: " << x << std::endl; }
    ~B() { std::cout << "B destructed" << std::endl; }
    B(const B& other) { 
        b = other.b;
        std::cout << "B copy constructed" << std::endl; 
    }
    B& operator=(const B& other) { 
        b = other.b;
        std::cout << "B copy assigned" << std::endl; return *this; 
    }
};

class C {
public:
    int c;
public:
    C(int x):c(x) { 
        std::cout << "C constructed with parameter: " << this->c << std::endl; 
    }
    ~C() { std::cout << "C destructed" << std::endl; }
    C(const C& other) {
        c = other.c;
        std::cout << "C copy constructed" << std::endl; 
    }
    C& operator=(const C& other) {
        c = other.c;
        std::cout << "C copy assigned" << std::endl; return *this; 
    }
};

class E {
public:
    int e;
};

class ClassInit {
public:
    A a;
    A a1;
    B b;
    C c{1};

    ClassInit() {
        std::cout << "ClassInit constructed" << std::endl;
    }

    ClassInit(int x):a(A(2)) {
        c = C(2); // 构造函数内部做初始化, 属于赋值操作
        std::cout << "ClassInit constructed with parameter: " << x << std::endl;
    }

    ~ClassInit() {
        std::cout << "ClassInit destructed" << std::endl;
    }
};

/**
 * 统一初始化(c++11引入)：也被称为{}初始化或列表初始化
 *   - 防止隐式类型转换
 *   - 防止窄化转换(例如double转int)
 *   - 统一初始化语法
 *   - 防止最常见的坑-VLA(变长数组)
 * 默认初始化：
 *   - 定义对象但是不给出初始化器，例如：T x; new T(不加括号)
 *   - 内置类型的成员变量不会被初始化，值未定义
 *   - 类类型的成员变量会调用默认构造函数进行初始化
 * 值初始化：
 *   - 使用空的括号或大括号进行初始化，例如：T x(); T x{};
 *   - T有用户定义的构造函数，则调用默认构造函数进行初始化
 *   - T没有用户定义的构造函数，所有标量设置成0，类类型的成员变量调用默认构造函数进行初始化
 * 零初始化：
 *   - 将对象的内存全部设置为0
 *   - 全局变量、静态变量会被自动零初始化
 *   - 跟默认初始化/值初始化不是一个概念，这种是静态存储期对象特有的初始化方式
 */
void initlize() {
    A a = A(); // 默认初始化
    std::cout << "a.a: " << a.a << std::endl;
    A a1;
    std::cout << "a1.a: " << a1.a << std::endl;
    A a2{}; // 默认初始化
    std::cout << "a2.a: " << a2.a << std::endl;
    A a3 = A(5); // 列表初始化
    std::cout << "a3.a: " << a3.a << std::endl;
    /**
     * E e; // 默认初始化，会调用默认构造函数。若构造函数不初始化成员变量，则成员变量值未定义
     * E e1{}; // 列表初始化
     *  - 若没有用户定义的构造函数，则会将内置类型成员变量初始化为0
     *  - 若有用户定义的构造函数，则调用该构造函数，若构造函数不初始化成员变量，则成员变量值未定义
     */
    E e;
    std::cout << "e.e: " << e.e << std::endl; // 未初始化，值未定义
    E e1{};
    std::cout << "e1.e: " << e1.e << std::endl; // 值为0
}

/**
 * 类成员的三种初始化方式:
 *  1.成员声明的同时做初始化，类内初始化
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
 *   - 如果类内初始化和列表初始化同时存在，则类内初始化的值会被忽略（注意不是被二次赋值覆盖，而是会忽略！！）
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
void class_init_order() {
    std::cout << "------------------start class init order------------------" << std::endl;
    ClassInit ci1(1);
    std::cout << "------------------end class init order------------------" << std::endl;
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
    std::cout << "=============uniform init=============" << std::endl;
    initlize();
    std::cout << "=============class init order=============" << std::endl;
    class_init_order();
    std::cout << "=============drive class init=============" << std::endl;
    drive_class_init();
    std::cout << "=============thread safe class init=============" << std::endl;
    thread_safe_class_init();
    return 0;
}