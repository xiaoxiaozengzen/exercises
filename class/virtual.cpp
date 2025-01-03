#include <stdio.h>

#include <iostream>
#include <memory>

// 多态的两个条件：1.虚函数重写 2.必须通过基类的指针或者引用调用虚函数。
// 对于成员变量，代码编译和执行时都看父类，以父类为依据（有无及值以父类为标准）；
// 对于成员方法，编译时以父类为依据（父类无则编译报错），执行时以子类为依据（执行子类方法），但前提是子类必须对方法进行重载，在C++中父类函数还必须为虚函数。

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

void ptr_array() {
  int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  printf("a :%p\n", a);
  printf("a[0]: %p, %d  %d\n", &a[0], a[0], *(int*)&a);
}

void virtual_tabel() {
  std::cout << "sizeof A:" << sizeof(A) << std::endl;
  std::cout << "sizeof AA:" << sizeof(AA) << std::endl;

  // 函数指针使用
  Fun1 f = fun;
  f();
  printf("f1 address: %p\n", f);
  printf("fun address: %p\n", fun);

  A a;
  A a1;
  printf("a: &vptr=%p, * vptr=%p\n", (long long*)&a, *(long long*)&a);
  printf("a1: &vptr=%p, * vptr=%p\n", (long long*)&a1, *(long long*)&a1);

  auto* vptr = (long long*)&a;
  auto* vtabel = (long long*)*vptr;
  printf("vptr=%p, vtabel=%p\n", vptr, vtabel);
  printf("*vtabel=%p\n", *vtabel);
  printf("*vtabel2=%p\n", *(vtabel + 1));
  Fun1 fu1 = (Fun1)*vtabel;
  fu1();
  Fun1 fu2 = (Fun1) * (vtabel + 1);
  fu2();
  Fun2 fu3 = (Fun2) * (vtabel + 2);
  fu3(10);

  printf("fun1() %p\n", *(long long*)*(long long*)&a);
  printf("fun1() %p\n", (void*)&A::fun2);
  Fun1 f1 = (Fun1)(void*)&A::fun2;
  f1();
  f1 = (Fun1) * (long long*)*(long long*)&a;
  f1();
}

/*******************************************多态**********************************************/
class Base {
 public:
  Base() { std::cout << "Base construct" << std::endl; }

  // 不为虚函数，则多态的时候只调用父类的析构，造成内存泄漏
  virtual ~Base() { std::cout << "Base deconstruct" << std::endl; }

  void first() { std::cout << "Base::first" << std::endl; }

  virtual void second() { std::cout << "Base::second" << std::endl; }

  virtual void third() { std::cout << "Base::third: " << this->a << std::endl; }

  // 协变，即基类的虚函数返回基类对象的指针或者引用，派生类虚函数返回派生类对象的指针或者引用
  virtual Base& re() { return *this; }

 public:
  int a = 10;
  int b = 11;
};

class Derived : public Base {
 public:
  Derived() { std::cout << "Derived construct" << std::endl; }

  ~Derived() { std::cout << "Derived deconstruct" << std::endl; }
  int first() { std::cout << "Derived::first" << std::endl; }

  virtual void second() { std::cout << "Derived::second" << std::endl; }

  void third() { std::cout << "Derived::third:" << this->a << std::endl; }

  Derived& re() { return *this; }

 public:
  int a = 12;
  int c = 13;
};

class DerivedOther {
 public:
  virtual int first() { std::cout << "DerivedOther::first" << std::endl; }
};

/**
多重集成的情况下，包含两个虚函数表了
 */
class DerivedEnd : public Derived, public DerivedOther {
 public:
  virtual int first() { std::cout << "DerivedEnd::first" << std::endl; }
};

/**
多态的两个条件：1.虚函数重写 2.必须通过基类的指针或者引用调用虚函数。
 */
void duotai_example() {
  Base* b = new Derived;
  b->first();
  b->second();
  b->third();

  // 多态中：成员变量编译和运行的时候都以父类为准
  std::cout << "b->a: " << b->a << std::endl;
  std::cout << "b->b: " << b->b << std::endl;
  delete b;

  std::cout << "sizeof(Base): " << sizeof(Base) << ", sizeof(Derived): " << sizeof(Derived)
            << ", sizeof(DerivedOther): " << sizeof(DerivedOther)
            << ", sizeof(DerivedEnd): " << sizeof(DerivedEnd) << std::endl;
}

/****************************shared ptr******************************/

struct Value {
  int a;
  int b;

  void Print() {
    printf("Value::value_: %p\n", &a);
  }
};
class BasePtr {
 public:
  BasePtr() { std::cout << "BasePtr construct" << std::endl; }

  virtual ~BasePtr() { std::cout << "BasePtr deconstruct" << std::endl; }

  virtual void Init() {
    std::cout << "BasePtr::Init" << std::endl;
  }

  virtual void Print() {
    std::cout << "BasePtr::Print" << std::endl;
  }
};

class DerivedPtr : public BasePtr {
 public:
  DerivedPtr() { std::cout << "DerivedPtr construct" << std::endl; }

  ~DerivedPtr() { std::cout << "DerivedPtr deconstruct" << std::endl; }

  void Init() override {
    std::cout << "DerivedPtr::Init" << std::endl;
    value_ = std::make_shared<Value>();
  }

  void Print() override {
    std::cout << "DerivedPtr::Print" << std::endl;
    value_->Print();
    printf("DerivedPtr::value_: %p\n", &(value_->a));
  } 
private:
  std::shared_ptr<Value> value_ = nullptr;
};

class DerivedPtrOther : public BasePtr {
 public:
  DerivedPtrOther() {
    std::cout << "DerivedPtrOther construct" << std::endl; 
    Init();
  }

  ~DerivedPtrOther() { std::cout << "DerivedPtrOther deconstruct" << std::endl; }

  void Init() override {
    std::cout << "DerivedPtrOther::Init" << std::endl;
    value_ = std::make_shared<Value>();
  }

  void Print() override {
    std::cout << "DerivedPtrOther::Print" << std::endl;
    value_->Print();
    printf("DerivedPtrOther::value_: %p\n", &(value_->a));
  }
private:
  std::shared_ptr<Value> value_ = nullptr;
};

class BaseFactory {
public:
  static std::shared_ptr<BasePtr> Create() {
    return std::make_shared<DerivedPtr>();
  }
};

/**
 * 工厂模式
 */
class BaseFactoryOther {
public:
  static std::shared_ptr<BasePtr> Create(std::string name) {
    std::shared_ptr<BasePtr> base_ptr = nullptr;
    if(name == "DerivedPtr") {
      base_ptr = std::make_shared<DerivedPtr>();
    } else if(name == "DerivedPtrOther") {
      base_ptr = std::make_shared<DerivedPtrOther>();
    } else {
      
    }

    return base_ptr;
  }
};

void SharedPtrExample() {
  std::shared_ptr<BasePtr> base_ptr = std::make_shared<DerivedPtr>();
  base_ptr->Init();
  base_ptr->Print();
  std::cout << "-----------1----------" << std::endl;
  std::shared_ptr<BasePtr> base_ptr_other = std::make_shared<DerivedPtrOther>();
  base_ptr_other->Print();
  std::cout << "-----------2-----------" << std::endl;

  std::shared_ptr<BasePtr> base_ptr_factory = BaseFactory::Create();
  base_ptr_factory->Init();
  base_ptr_factory->Print();
  std::cout << "-----------3-----------" << std::endl;
  std::shared_ptr<BasePtr> base_ptr_factory_other = BaseFactory::Create();
  base_ptr_factory_other->Init();
  base_ptr_factory_other->Print();
  std::cout << "-----------4-----------" << std::endl;

  // 返回的函数地址是不一样的
  std::shared_ptr<BasePtr> base_ptr_factory1 = BaseFactoryOther::Create("DerivedPtr");
  base_ptr_factory1->Init();
  base_ptr_factory1->Print();
  std::cout << "-----------5-----------" << std::endl;
  std::shared_ptr<BasePtr> base_ptr_factory2 = BaseFactoryOther::Create("DerivedPtr");
  base_ptr_factory2->Init();
  base_ptr_factory2->Print();
  std::cout << "-----------6-----------" << std::endl;
  std::shared_ptr<BasePtr> base_ptr_factory_other1 = BaseFactoryOther::Create("DerivedPtrOther");
  base_ptr_factory_other1->Init();
  base_ptr_factory_other1->Print();
  std::cout << "-----------7-----------" << std::endl;
  std::shared_ptr<BasePtr>& base_ptr_factory_other2 = base_ptr_factory1;
  base_ptr_factory_other2->Print();
  std::cout << "-----------8-----------" << std::endl;
}

/*******************************************pure virtual**********************************************/
class PureVirtual {
 public:
  virtual void Init() = 0;
  virtual void Print() = 0;
};

class DerivedPureVirtual : public PureVirtual {
 public:
  void Init() override {
    std::cout << "DerivedPureVirtual::Init" << std::endl;
  }

  void Print() override {
    std::cout << "DerivedPureVirtual::Print" << std::endl;
  }
};

void PureVirtualExample() {
  // 1. 纯虚函数的类不能实例化
  // PureVirtual obj = PureVirtual();
  // PureVirtual* obj = new PureVirtual();
  // std::shared_ptr<PureVirtual> obj = std::make_shared<PureVirtual>();

  PureVirtual* obj = new DerivedPureVirtual();
  obj->Init();
  obj->Print();

  std::shared_ptr<PureVirtual> obj_ptr = std::make_shared<DerivedPureVirtual>();
  obj_ptr->Init();
  obj_ptr->Print();
}

int main() {
  std::cout << "=================ptr_array===============" << std::endl;
  ptr_array();
  std::cout << "=================virtual_tabel()===============" << std::endl;
  virtual_tabel();
  std::cout << "=================duotai_example()===============" << std::endl;
  duotai_example();
  std::cout << "=================SharedPtrExample()===============" << std::endl;
  SharedPtrExample();
  std::cout << "=================PureVirtualExample()===============" << std::endl;
  PureVirtualExample();
}