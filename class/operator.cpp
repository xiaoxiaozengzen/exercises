#include <iostream>
#include <new>

/**
 * 操作符重载范围
 * 1. 如果一个重载操作符是类成员，那么只有当与
 *    它的左操数是该类的对象时，该操作符才会被调用。如果
 *    该操作符的左操作数必须是其他的类型，则操作符必须被重载为全局名字空间的成员。
 * 2. C++要求赋值=，下标[]，调用()， 和成员指向->
 *    操作符必须被定义为类成员操作符。任何把这些操作符定义为名
 *    字空间成员的定义都会被标记为编译时刻错误。
 * 3. 如果有一个操作数是类类型如string类的情形那么对于对称操作符比如等于操作符最好定义为全局名字空间成员。
 * 4. ""_v形式的操作符重载，用于重载用户定义的字面量
 * 5. 不能重载sizeof，.，.*，::，三元操作符?:
 * 6. 不能重载操作符的优先级和结合性
 * 7. 不能重载操作符的返回值类型
 * 8. 不能重载操作符的参数个数
 */

/******************非类成员函数的操作符重载************** */
class people {
 public:
  int age;

 public:
  people(int a) { this->age = a; }

  int operator=(int a) {
    this->age = a;
    return a;
  }
};
bool operator==(people &p1, people const &p2) {
  {
    if (p1.age == p2.age) {
      return true;  //满足要求
    }
    return false;
  }
}

#if 0
// 编译报错：error: ‘void operator()()’ must be a nonstatic member function
void operator()() {
  std::cout << "callable object" << std::endl;
}
#endif

/******************类成员函数的操作符重载************** */

class A {
public:
  A() { std::cout << "construct" << std::endl; }
  explicit A(int a) : a(a) { std::cout << "another construct" << std::endl; }
  ~A() { std::cout << "deconstruct" << std::endl; }

  A(const A &other) {
    std::cout << "copy construct" << std::endl;
    this->a = other.a;
  }

  A &operator=(const A &other) {
    std::cout << "copy assign construct" << std::endl;
    this->a = other.a;
    return *this;
  }

  A(A &&other) {
    std::cout << "move construct" << std::endl;
    this->a = other.a;
  }

  A &operator=(A &&other) {
    std::cout << "move assign construct" << std::endl;
    this->a = other.a;
    return *this;
  }

  ///< 重载小于号
  bool operator<(const A &a) const {
    std::cout << "operator<, this " << this->a << ", other: " << a.a << std::endl;
    return this->a < a.a;
  }

  ///< 重载输出操作符
  friend std::ostream &operator<<(std::ostream &output, const A &a) {
    output << a.a;
    return output;
  }

  /**
  * @brief ==操作符重载
  * 
  * @param a
  * @return true
  */
  bool operator==(const A &a) const {
    std::cout << "operator==, this " << this->a << ", other: " << a.a << std::endl;
    return this->a == a.a;
  }

  ///< 前置++
  A& operator++() { this->a++; return *this; }

  ///< 后置++
  A& operator++(int) { this->a++; return *this; }

  ///< 重载解引用操作符，&表示只能用于左值对象
  int operator*() & { return a; }

public:
  int a = 0;
};

/**
 * @brief ""_v形式重载
 * 
 * @note c++标准规定，整数字面量的用户定义字面量操作符参数类型是以下之一
 *       unsigned long long int
 *       const char* 用于字符串
 *       const char*, std::size_t 用于字符串
 *       long double 用于浮点数
 *       char, wchar_t, char8_t, char16_t, char32_t 用于字符
 */
A operator""_A(unsigned long long a) {
  A obj(a);
  return obj;
}

void OperatorTest() {
  // 非成员函数的操作符重载
  people p1(10);
  people p2(20);
  std::cout << "p1==p2: " << ((p1 == p2)?"true":"false") << std::endl;

  // 类成员函数的操作符重载
  A a1(10);
  A a2(20);

  std::cout << "a1==a2: " << ((a1 == a2)?"true":"false") << std::endl;
  std::cout << "a1<a2: " << ((a1 < a2)?"true":"false") << std::endl;
  std::cout << "a1: " << a1 << std::endl;
  std::cout << "a2++: " << (a2++) << std::endl;
  std::cout << "++a2: " << (++a2) << std::endl;
  A a3 = 123_A;
  std::cout << "a3: " << a3 << std::endl;
  std::cout << "*a3: " << *a3 << std::endl;
}


/************************************operator new**************************************** */
// throwing (1)
// void* operator new (std::size_t size) throw (std::bad_alloc);
// nothrow (2)
// void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) throw();
// placement (3)
// void* operator new (std::size_t size, void* ptr) throw();

// ordinary (1)
// void operator delete (void* ptr) noexcept;
// nothrow (2)
// void operator delete (void* ptr, const std::nothrow_t& nothrow_constant) noexcept;
// placement (3)
// void operator delete (void* ptr, void* voidptr2) noexcept;

void *operator new(std::size_t size) {
  std::cout << "operator new" << std::endl;
  return malloc(size);
}

void *operator new(std::size_t size, const std::nothrow_t &nothrow_value) noexcept {
  std::cout << "operator new nothrow" << std::endl;
  return malloc(size);
}

void operator delete(void *ptr) noexcept {
  std::cout << "operator delete" << std::endl;
  free(ptr);
}

void operator delete(void *ptr, const std::nothrow_t &nothrow_constant) noexcept {
  std::cout << "operator delete nothrow" << std::endl;
  free(ptr);
}

// new handler
void no_memory() {
  std::cout << "Failed to allocate memory!\n";
  // std::exit (1);
}

void NewTest() {
  std::cout << "**********new handler**********" << std::endl;
  std::set_new_handler(no_memory);
  std::new_handler p = std::get_new_handler();
  p();

  std::cout << "**********operator new**********" << std::endl;
  A *a = new A(10);
  std::cout << "*a: " << *a << std::endl;

  std::cout << "**********operator new nothrow**********" << std::endl;
  A *b = new (std::nothrow) A(20);
  if (b == nullptr) {
    std::cout << "new failed" << std::endl;
  } else {
    std::cout << "*b:" << *b << std::endl;
  }

  std::cout << "**********operator replace new**********" << std::endl;
  A *c = new (b) A(30);  // c跟a地址一样
  std::cout << "*b:" << *b << std::endl;
  std::cout << "*c:" << *c << std::endl;

  std::cout << "**********malloc**********" << std::endl;
  A *d = (A *)malloc(sizeof(A));
  new (d) A(40);
  std::cout << "*d:" << *d << std::endl;

  std::cout << "**********operator new but no construct**********" << std::endl;
  A *e = (A *)::operator new(sizeof(A));
  std::cout << "*e:" << *e << std::endl;

  std::cout << "**********operator delete**********" << std::endl;
  delete a;
  delete b;
  // delete c; // 会报错，因为c是b的地址，不能重复释放
  free(d);
  ::operator delete(e);

  std::cout << "**********operator delete after**********" << std::endl;
  // 依然可以使用，但是此时b已经被释放了，所以会有问题
  std::cout << "*b: " << *b << std::endl;
}

int main() {
  std::cout << "===================== OperatorTest =====================" << std::endl;
  OperatorTest();
  std::cout << "===================== NewTest =====================" << std::endl;
  NewTest();
  return 0;
}
