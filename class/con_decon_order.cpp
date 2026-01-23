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
    A a;
#if 0
    // 编译报错：因为c只有带参数的构造，E的默认构造函数被删除了。找不到合适的构造函数对于e
    C c;
#endif
};

class F{
public:
    int f1;
    int f2;
    double f3;
public:
    F() {
        std::cout << "F constructed" << std::endl;
    }
    ~F() {
        std::cout << "F destructed" << std::endl;
    }
    explicit F(int a):f1(a), f2(0), f3(0.0) {
        std::cout << "F constructed with one parameter: " << f1 << std::endl;
    }
    F(int a, int b, double c):f1(a), f2(b), f3(c) {
        std::cout << "F constructed with parameters: " << f1 << ", " << f2 << ", " << f3 << std::endl;
    }
    F(const F& other) {
        f1 = other.f1;
        f2 = other.f2;
        f3 = other.f3;
        std::cout << "F copy constructed" << std::endl;
    }
    F& operator=(const F& other) {
        f1 = other.f1;
        f2 = other.f2;
        f3 = other.f3;
        std::cout << "F copy assigned" << std::endl; return *this;
    }
};

class G {
public:
    int data1;
    double data2;
    float data3;
};

/******************************1.现代c++的初始化问题 ******************************/
/**
 * 1.内置类型/类类型
 *   - 内置类型：char, int, float, double, 指针等
 *   - 类类型：用户自定义的类/结构体/联合体等
 * 2.c++初始化方式(内置类型跟类类型都支持)：
 *  - A a = ...; // 拷贝初始化
 *  - A a = {...}; // 拷贝列表初始化
 *  - A a{...}; // 直接列表初始化
 *  - A a(...); // 直接初始化
 * 2.1.四种初始化方式的区别：
 *  - 拷贝初始化：
 *    - 调用非explicit的构造函数，不可调用explicit的单参构造函数(否则编译报错)
 *    - 允许隐式类型转换
 *  - 直接初始化：
 *    - 直接按照参数匹配构造函数，可以调用explicit构造函数
 *    - 不涉及优先调用initializer_list构造函数的规则
 *    - 对聚合类不可用，聚合类必须用{...}初始化
 *  - 拷贝列表初始化：
 *    - 不允许窄化转换，例如double转int
 *    - 不可调用explicit的单参构造函数(否则编译报错)
 *    - 如果是聚合类，等同于聚合初始化
 *    - auto a = {...}; 会被推导为std::initializer_list<T>类型
 *    - 不允许construct():member(...)这种形式的成员初始化
 *  - 直接列表初始化：
 *    - 不允许窄化转换，例如double转int
 *    - 可以使用explicit构造函数
 *    - 如果是聚合类，等同于聚合初始化
 *    - auto a{...}; 会被推导为普通类型，而不是std::initializer_list<T>
 *    - 优先调用initializer_list构造函数(如果有的话)
 * 2.2.聚合类(aggregate)的定义：只包含数据成员的类/结构体/联合体，且满足以下条件：
 *   - 没有用户定义的构造函数
 *   - 没有私有/受保护的非静态数据成员
 *   - 没有基类
 *   - 没有虚函数
 * 3.默认初始化/值初始化/零初始化(从创建对象后的值来说)：
 *   - 默认初始化：对象未被显示赋值，例如：A a;
 *     - 内置类型：值未定义
 *     - 类类型：调用默认构造函数，若无默认构造函数则编译报错
 *   - 值初始化：一种特殊的默认初始化，例如：A a = A(); 或 A a{};
 *     - 内置类型：初始化为0
 *     - 类类型：调用默认构造函数，若无默认构造函数则编译报错
 *   - 零初始化：将对象的内存全部置为0，例如：memset(&a, 0, sizeof(A));
 *     - 内置类型：初始化为0
 *     - 类类型：所有成员都被零初始化，若有类类型成员，则递归进行零初始化
 */
void initlize() {
    F f1 = {1, 2, 3.0}; // 拷贝列表初始化
    std::cout << "f1: " << f1.f1 << ", " << f1.f2 << ", " << f1.f3 << std::endl;
    F f2{4, 5, 6.0}; // 直接列表初始化
    std::cout << "f2: " << f2.f1 << ", " << f2.f2 << ", " << f2.f3 << std::endl;
    
    auto a = {1}; // 列表初始化，推导为std::initializer_list<int>
    auto b{1};  // 直接初始化，推导为int
    std::cout << "type of a: " << typeid(a).name() << std::endl; // std::initializer_list<int>
    std::cout << "type of b: " << typeid(b).name() << std::endl; // int

    G g1; // 默认初始化，内置类型未定义
    std::cout << "g1: " << g1.data1 << ", " << g1.data2 << ", " << g1.data3 << std::endl;
    G g2 = G(); // 值初始化，内置类型初始化为0
    std::cout << "g2: " << g2.data1 << ", " << g2.data2 << ", " << g2.data3 << std::endl;
    G g3{}; // 值初始化，内置类型初始化为0
    std::cout << "g3: " << g3.data1 << ", " << g3.data2 << ", " << g3.data3 << std::endl;
    G g4 = {}; // 值初始化，内置类型初始化为0
    std::cout << "g4: " << g4.data1 << ", " << g4.data2 << ", " << g4.data3 << std::endl;
    G g5{1}; // 直接列表初始化，data1=1, data2和data3初始化为0
    std::cout << "g5: " << g5.data1 << ", " << g5.data2 << ", " << g5.data3 << std::endl;
}

class ClassInitOrder {
public:
    A a;
    A a1;
    B b;
    C c{1};

    ClassInitOrder() {
        std::cout << "ClassInitOrder constructed" << std::endl;
    }

    ClassInitOrder(int x):a(A(2)) {
        c = C(2); // 构造函数内部做初始化, 属于赋值操作
        std::cout << "ClassInitOrder constructed with parameter: " << x << std::endl;
    }

    ~ClassInitOrder() {
        std::cout << "ClassInitOrder destructed" << std::endl;
    }
};

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
    ClassInitOrder ci1(1);
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

class Derive : public ClassInitOrder {
public:
    Derive() : ClassInitOrder(3), d(4) { // 使用成员初始化列表进行初始化
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