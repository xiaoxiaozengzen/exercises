#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
// template <class T> class weak_ptr;

class A {
 public:
  A() { std::cout << "construct" << std::endl; }
  explicit A(int a) : a(a) { std::cout << "another construct" << std::endl; }
  ~A() { std::cout << "deconstruct" << std::endl; }

  A(const A& other) {
    std::cout << "copy construct" << std::endl;
    this->a = other.a;
  }

  A& operator=(const A& other) {
    std::cout << "copy assign construct" << std::endl;
    this->a = other.a;
    return *this;
  }

  A(A&& other) {
    std::cout << "move construct" << std::endl;
    this->a = other.a;
  }

  A& operator=(A&& other) {
    std::cout << "move assign construct" << std::endl;
    this->a = other.a;
    return *this;
  }

  bool operator<(const A& a) const {
    std::cout << "operator<, this " << this->a << ", other: " << a.a << std::endl;
    return this->a < a.a;
  }

  friend std::ostream& operator<<(std::ostream& output, const A& a) {
    output << " A<<: " << a.a;
    return output;
  }

  bool operator==(const A& a) const {
    std::cout << "operator==, this " << this->a << ", other: " << a.a << std::endl;
    return this->a == a.a;
  }

 public:
  int a = 0;
};

void MemType() {
  if (std::is_same<std::weak_ptr<int>::element_type, int>::value) {
    std::cout << "std::weak_ptr<int>::element_type is int" << std::endl;
  } else {
    std::cout << "std::weak_ptr<int>::element_type is not int" << std::endl;
  }
}

void ConFun() {
  std::shared_ptr<A> sp1 = std::make_shared<A>(1);

  std::weak_ptr<A> wp1;
  std::weak_ptr<A> wp2(wp1);
  std::weak_ptr<A> wp3(sp1);
}

void MemFun() {
  std::shared_ptr<A> sp1 = std::make_shared<A>(1);
  std::shared_ptr<A> sp2(sp1);
  std::weak_ptr<A> wp1 = sp1;
  std::weak_ptr<A> wp2;
  std::cout << "wp1.use_count(): " << wp1.use_count() << ", wp2.use_count: " << wp2.use_count()
            << std::endl;
  bool wp1_expired = wp1.expired();
  std::cout << "wp1.expired(): " << wp1_expired << std::endl;
  bool wp2_expired = wp2.expired();
  std::cout << "wp2.expired(): " << wp2_expired << std::endl;

  wp1.swap(wp2);

  long int use_count = wp1.use_count();
  std::cout << "wp1.use_count(): " << use_count << ", wp2.use_count: " << wp2.use_count()
            << std::endl;

  wp2.reset();
  std::cout << "wp2.use_count: " << wp2.use_count() << ", wp2.expired(): " << wp2.expired()
            << std::endl;

  std::shared_ptr<A> sp3 = wp1.lock();
  if (sp3 == nullptr) {
    std::cout << "wp1 is expired" << std::endl;
  } else {
    std::cout << "wp1 is not expired" << std::endl;
  }

  wp2 = sp1;
  std::cout << "wp2.use_count: " << wp2.use_count() << ", wp2.expired(): " << wp2.expired()
            << std::endl;
  std::shared_ptr<A> sp4 = wp2.lock();
  if (sp4 == nullptr) {
    std::cout << "wp2 is expired" << std::endl;
  } else {
    std::cout << "wp2 is not expired, " << *sp4 << std::endl;
  }

  std::weak_ptr<A> wp3 = sp1;
  std::cout << "wp2 has same ownership with wp3: "
            << !(wp2.owner_before(wp3) || wp3.owner_before(wp2)) << std::endl;
  std::cout << "wp3 has same ownership with wp1: "
            << !(wp3.owner_before(wp1) || wp1.owner_before(wp3)) << std::endl;
}

/***************************Cycle Reference********************************/
class Data2;
class Data3;
class Data4;

class Data1 {
 public:
  Data1() { std::cout << "Data1 construct" << std::endl; }
  ~Data1() { std::cout << "Data1 deconstruct" << std::endl; }

  std::shared_ptr<Data2> data2;
};

class Data2 {
 public:
  Data2() { std::cout << "Data2 construct" << std::endl; }
  ~Data2() { std::cout << "Data2 deconstruct" << std::endl; }

  std::shared_ptr<Data1> data1;
};

class Data3 {
 public:
  Data3() { std::cout << "Data3 construct" << std::endl; }
  ~Data3() { std::cout << "Data3 deconstruct" << std::endl; }

  std::weak_ptr<Data4> data4;
};

class Data4 {
 public:
  Data4() { std::cout << "Data4 construct" << std::endl; }
  ~Data4() { std::cout << "Data4 deconstruct" << std::endl; }

  std::weak_ptr<Data3> data3;
};

/**
 * @brief 循环引用, 两个对象互相引用，导致无法释放内存，造成内存泄漏
 */
void CycleReference() {
  std::shared_ptr<Data1> data1 = std::make_shared<Data1>();
  std::shared_ptr<Data2> data2 = std::make_shared<Data2>();
  data1->data2 = data2;
  data2->data1 = data1;
}

void SolveCycleReference() {
  std::shared_ptr<Data3> data3 = std::make_shared<Data3>();
  std::shared_ptr<Data4> data4 = std::make_shared<Data4>();
  data3->data4 = data4;
  data4->data3 = data3;
}

/******************************************destruct***********************************/
class Data5 {
 public:
  Data5() : data5(std::make_shared<A>(1)) { std::cout << "Data5 construct" << std::endl; }
  ~Data5() { std::cout << "Data5 deconstruct" << std::endl; }

  std::shared_ptr<A> data5;
};

/**
 * @brief 先按顺序构造成员变量，再构造类本身，然后先析构类本身，再析构成员变量
 */
void Destruct() {
  std::shared_ptr<Data5> data5 = std::make_shared<Data5>();
  std::cout << "data5.use_count(): " << data5.use_count() << std::endl;
}

int main() {
  std::cout << "===================== MemType ======================" << std::endl;
  MemType();
  std::cout << "=================== ConFun =====================" << std::endl;
  ConFun();
  std::cout << "==================== MemFun ====================="
            << std::endl;
  MemFun();
  std::cout << "================== CycleReference ==================" << std::endl;
  CycleReference();
  std::cout << "================== SolveCycleReference =====================" << std::endl;
  SolveCycleReference();
  std::cout << "===================== Destruct ================" << std::endl;
  Destruct();
}