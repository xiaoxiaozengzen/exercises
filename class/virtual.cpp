#include <stdio.h>

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <functional>

/**
 * 多态的两个条件：
 *   - 1.虚函数重写 
 *   - 2.必须通过基类的指针或者引用调用虚函数。
 * 
 * 对于成员变量:
 *   - 代码编译和执行时都看父类，以父类为依据（有无及值以父类为标准）；
 * 对于成员方法:
 *   - 编译时以父类为依据（父类无则编译报错），执行时以子类为依据（执行子类方法），但前提是子类必须对方法进行重载，在C++中父类函数还必须为虚函数。
 */
class A {
 public:
  void fun1() { std::cout << "A::fun1" << std::endl; }

  virtual void fun2() { std::cout << "virtual A::fun2" << std::endl; }

  virtual void fun3() { std::cout << "virtual A::fun3" << std::endl; }

  virtual void fun4(int d) { std::cout << "virtual A::fun4: " << d << std::endl; }

 public:
  int a;
  char b;
};

class AA {
 public:
  void fun1() { std::cout << "AA::fun1" << std::endl; }

 public:
  int a;
  char b;
};

typedef void (*Fun1)();
typedef void (*Fun2)(int);
void fun() { std::cout << "fun" << std::endl; }

/**
 * 虚函数表的原理：
 *   - 每个类都有一个虚函数表（vtable），其中存储了该类的虚函数指针。
 *   - 每个对象都有一个指向其类的虚函数表的指针（vptr）。
 *   - 当调用虚函数时，编译器会查找对象的 vptr，找到对应的虚函数表，然后根据函数名查找对应的函数指针并调用。
 */
void virtual_tabel() {
  /**
   * 查看类的大小：
   *   - sizeof(A) 返回类 A 的大小，包括所有成员变量和虚函数表指针。
   *   - sizeof(AA) 返回类 AA 的大小，包括所有成员变量，但没有虚函数表指针。
   *  注意：如果类中有虚函数，则编译器会为该类添加一个虚函数表指针，这会增加类的大小。
   */
  std::cout << "sizeof A:" << sizeof(A) << std::endl;
  std::cout << "sizeof AA:" << sizeof(AA) << std::endl;

  /**
   * 函数指针的使用：
   *   - Fun1 f = fun; 将函数 fun 的地址赋值给函数指针 f。
   *   - f(); 调用函数指针 f 指向的函数
   */
  Fun1 f = fun;
  f();
  printf("f1 address: %p\n", f);
  printf("fun address: %p\n", fun);

  /**
   * 类的虚函数表指针（vptr）：
   *   - 每个类的对象都有一个指向其虚函数表的指针（vptr）。
   *   - vptr 存储在对象的内存布局中，通常是对象的第一个成员。
   *   - 虚函数表是类的一个静态成员，存储了类的所有虚函数的地址。
   * 
   * 下面例子：
   *   - &vptr的地址不一样，因为每个对象都有自己的虚函数表指针。
   *   - *vptr的值是虚函数表的地址，指向类的虚函数表。都是一样的地址
   */
  A a;
  A a1;
  printf("a: &vptr=%p, *vptr=%llx\n", &a, *(long long*)&a);
  printf("a1: &vptr=%p, *vptr=%llx\n", &a1, *(long long*)&a1);

  /**
   * 模仿编译器查找虚函数表，并执行虚函数表中的函数。
   */
  auto* vptr = (long long*)&a;
  auto* vtabel = (long long*)*vptr;
  printf("vptr=%p, vtabel=%p\n", vptr, vtabel);
  printf("*vtabel=%llx\n", *vtabel);
  printf("*vtabel2=%llx\n", *(vtabel + 1));
  Fun1 fu1 = (Fun1)(*vtabel);  // 对应 A::fun2
  fu1();
  Fun1 fu2 = (Fun1)(*(vtabel + 1));  // 对应 A::fun3
  fu2();
  Fun2 fu3 = (Fun2)(*(vtabel + 2));  // 对应 A::fun4
  fu3(10);
  printf("fun1() %llx\n", *(long long*)*(long long*)&a);
  Fun1 f1 = (Fun1)(*(long long*)(*(long long*)&a));
  f1();
}

/*******************************************多态**********************************************/
class Base {
 public:
  Base():c(12) { 
    std::cout << "Base construct" << std::endl; 
  }

  virtual ~Base() { 
    std::cout << "Base deconstruct" << std::endl; 
  }

  void first() { 
    std::cout << "Base::first" << std::endl; 
  }

  virtual void second() { 
    std::cout << "Base::second: " 
              << ", a= " << this->a
              << ", b= " << this->b
              << ", c= " << this->c
              << ", e= " << this->e
              << std::endl; 
  }

  virtual void third() { 
    std::cout << "Base::third: " << this->c << std::endl; 
  }

  /**
   * 协变，即基类的虚函数返回基类对象的指针或者引用，派生类虚函数返回派生类对象的指针或者引用
   */
  virtual Base& re() {
    std::cout << "Base::re" << std::endl;
    return *this;
  }

 public:
  int a = 10;
  int b = 11;
  int c;
  int e = 14;
};

class Derived : public Base {
 public:
  Derived() { 
    std::cout << "Derived construct" << std::endl; 
  }

  ~Derived() { 
    std::cout << "Derived deconstruct" << std::endl; 
  }

  int first() { 
    std::cout << "Derived::first" << std::endl;
    return 0; 
  }

  virtual void second() override { 
    std::cout << "Derived::second: " 
              << ", a= " << this->a
              << ", b= " << this->b
              << ", c= " << this->c
              << ", d= " << this->d
              << std::endl; 
  }

  void third() override{ 
    std::cout << "Derived::third"<< std::endl; 
  }

  Derived& re() override{
    std::cout << "Derived::re" << std::endl;
    return *this; 
  }

 public:
  int a = 22;
  int c = 23;
  int d = 24;  // 派生类新增成员变量
};

class DerivedOther {
 public:
  virtual int first() { std::cout << "DerivedOther::first" << std::endl; return 1; }
};

/**
 * 多重继承的情况：
 *  - 如果派生类同时继承了多个基类，并且这些基类有同名的虚函数，那么派生类必须重载这些虚函数，否则编译器会报错。
 */
class DerivedEnd : public Derived, public DerivedOther {
 public:
  virtual int first() { std::cout << "DerivedEnd::first" << std::endl; return 4; }
};

/**
 * 多态示例：
 *   - 基类指针指向派生类对象，基于虚函数表，调用虚函数时会根据实际对象类型调用对应的函数。
 *   - 成员变量在编译和运行时都以基类为准
 *   - 虚函数在访问内部成员变量，访问的是实际对象的成员变量，而不是基类的成员变量。
 *   - 切片(slice)问题：如果将派生类对象赋值给基类对象，会导致派生类的额外成员变量被切掉，只保留基类的部分。
 */
void duotai_example() {
  Base* b = new Derived;
  b->first();
  b->second();
  b->third();

  std::cout << "b->a: " << b->a << std::endl;
  std::cout << "b->b: " << b->b << std::endl;

  // 向下转型，使用 dynamic_cast
  Derived &derived_value = dynamic_cast<Derived&>(b->re());
  std::cout << "derived_value.a: " << derived_value.a << std::endl;
  std::cout << "derived_value.b: " << derived_value.b << std::endl;
  std::cout << "derived_value.c: " << derived_value.c << std::endl;
  std::cout << "derived_value.d: " << derived_value.d << std::endl;
  std::cout << "derived_value.e: " << derived_value.e << std::endl;
  derived_value.first();
  derived_value.second();
  derived_value.third();

  // 向上转型，使用基类引用
  Base&  base_ref = b->re();
  std::cout << "base_ref.a: " << base_ref.a << std::endl;
  std::cout << "base_ref.b: " << base_ref.b << std::endl;
  std::cout << "base_ref.c: " << base_ref.c << std::endl;
  std::cout << "base_ref.e: " << base_ref.e << std::endl;
  base_ref.first();
  base_ref.second();
  base_ref.third();
  
  delete b;

  std::cout << "sizeof(Base): " << sizeof(Base) 
            << ", sizeof(Derived): " << sizeof(Derived)
            << ", sizeof(DerivedOther): " << sizeof(DerivedOther)
            << ", sizeof(DerivedEnd): " << sizeof(DerivedEnd) << std::endl;
}

/****************************shared ptr******************************/
void SharedPtrExample() {
  std::shared_ptr<Base> basePtr = std::make_shared<Derived>();
  basePtr->first();  // 调用基类的 first 方法
  basePtr->second(); // 调用派生类的 second 方法
  basePtr->third();  // 调用派生类的 third 方法
}


/*******************************************pure virtual**********************************************/
class PureVirtual {
 public:
  virtual void Init() = 0;
  virtual void Print() = 0;
};

class DerivedPureVirtual : public PureVirtual {
 public:
  void Init() override { std::cout << "DerivedPureVirtual::Init" << std::endl; }

  void Print() override { std::cout << "DerivedPureVirtual::Print" << std::endl; }
};

void PureVirtualExample() {
#if 0
  // 1. 纯虚函数的类不能实例化
  PureVirtual obj = PureVirtual();
  PureVirtual* obj = new PureVirtual();
  std::shared_ptr<PureVirtual> obj = std::make_shared<PureVirtual>();
#endif

  PureVirtual* obj = new DerivedPureVirtual();
  obj->Init();
  obj->Print();

  std::shared_ptr<PureVirtual> obj_ptr = std::make_shared<DerivedPureVirtual>();
  obj_ptr->Init();
  obj_ptr->Print();
}

/*************************virtual never in construct********************************* */
/**
 * 不建议在构造函数和析构函数中调用虚函数，但是语法上是允许的
 * 
 * 构造跟析构中不会体现多态：
 * - 类的构造顺序先构造基类然后再派生类，所以在构造函数中调用虚函数，虚函数是不会呈现出多态的。
 * - 类的析构顺序是先析构派生类然后再析构基类，所以当调用继承层次中某一层次的类的析构函数时，
 *   这代表其派生类已经进行了析构，所以也并不会呈现多态。
 */
class BaseClass {
public:
    BaseClass():data_(std::make_shared<int>(42)) {
        std::cout << "BaseClass constructed start" << std::endl;
        
        // 构造函数中调用虚函数，虽然语法上允许，但不建议这样做，因为在构造函数中，虚函数不会表现出多态性。
        Init();

        // 父类构造完成才会创建线程，线程中调用虚函数时，
        // 已经是子类的虚函数了，此时子类的成员变量也已经初始化了，所以不会有问题。
        thread_ = std::thread([&](){
          while(cycle_) {
            doSomething();
            std::this_thread::sleep_for(std::chrono::seconds(1));
          }
        });
        std::cout << "BaseClass constructed end" << std::endl;
    }

    virtual void Init() {
        std::cout << "BaseClass Init called" << std::endl;
    }

    virtual ~BaseClass() { 
        std::cout << "BaseClass destructed start" << std::endl;
        doSomethingElse();
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // 析构函数中调用虚函数，虽然语法上允许，但不建议这样做，因为在析构函数中，虚函数也不会表现出多态性。
        cycle_ = false;  // 停止线程循环
        thread_.join();  // 确保线程结束
        std::cout << "BaseClass destructed end" << std::endl;
    }

    virtual void doSomething() {
        std::cout << "BaseClass Doing something with ptr: " << *data_ << std::endl;
    }

    virtual void doSomethingElse() {
        std::cout << "BaseClass Doing something else with ptr: " << *data_ << std::endl;
    }

public:
    std::thread thread_;
    std::shared_ptr<int> data_{nullptr};
    bool cycle_ = true;
};

class DerivedClass : public BaseClass {
public:
    DerivedClass():ptr_(std::make_shared<int>(10)) { 
        std::cout << "DerivedClass constructed" << std::endl; 
    }
    ~DerivedClass() { 
      std::cout << "DerivedClass destructed" << std::endl;
#if 0
    /**
     * 程序奔溃：
     *  - ptr释放资源
     *  - 但此时线程还在，在子类未完全析构之前，线程还是会多态调用了子类的doSomething方法，
     *  - 但此时子类的ptr已经被释放了，导致访问了已释放的内存。
     *  - 这就是为什么永远不要在构造函数和析构函数
     */
    ptr_.reset();
#endif
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
public:
    void doSomething() override{
        std::cout << "DerivedClass doing something with data: " << *ptr_ << std::endl;
    }

    void Init() override {
        std::cout << "DerivedClass Init called" << std::endl;
    }

    void doSomethingElse() override {
        std::cout << "DerivedClass doing something else with data: " << *ptr_ << std::endl;
    }

    void Fun() {
        std::cout << "DerivedClass Fun called" << std::endl;
    }

    std::shared_ptr<int> ptr_{nullptr};
};

void virtual_in_construct() {
    std::cout << "-------------------virtual_in_construct------------------" << std::endl;
    std::shared_ptr<BaseClass> basePtr = std::make_shared<DerivedClass>();
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "-------------------virtual_in_construct end------------------" << std::endl;
}

/**
  * 虚函数的调用开销：
  *   - 虚函数调用时间接的，即先通过对象的虚函数表指针（vptr）找到虚函数表（vtable），
  *     然后在虚函数表中找到对应的函数指针，最后调用函数。这种方式有额外开销，但是通常是可以接受的，尤其是在需要多态性的情况下。
  *   - 阻碍了编译器内联函数和各种函数级别的优化，导致性能开销较大。
  */
void virtual_fun_cost() {

}

int main() {
  std::cout << "=================virtual_tabel()===============" << std::endl;
  virtual_tabel();
  std::cout << "=================duotai_example()===============" << std::endl;
  duotai_example();
  std::cout << "=================SharedPtrExample()===============" << std::endl;
  SharedPtrExample();
  std::cout << "=================PureVirtualExample()===============" << std::endl;
  PureVirtualExample();
  std::cout << "=================virtual_in_construct()===============" << std::endl;
  virtual_in_construct();

  return 0;
}