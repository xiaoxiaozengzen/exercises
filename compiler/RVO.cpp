#include <iostream>
#include <limits>
#include <string>

// 不具名返回值优化(URVO): 发生在返回一个无名对象或者临时对象, 一般是 Return
// 语句中直接创建并返回的对象. 具名返回值优化(RVO,Return Value Optimization):
// 一般发生在返回一个已经创建的对象. 特殊情况
//     1.函数返回结果用于赋值会无优化。调用函数时, 造成的是拷贝赋值, 而不是拷贝构造,
//     即使是不具名的情况, 也不会发生返回值优化 2.若分支返回不全是同一具名对象, 则无返回值优化.
//     因为返回的对象在运行时确定, 编译器无法在编译期决定. 3.函数返回的是局部对象的成员变量,
//     也无法作用返回值优化, 即使是匿名变量. 4.函数返回的是输入参数或者全局变量, 也无返回值优化.
//     5.通过显式调用 std::move 返回函数结果往往是错误的. 即使如此,
//     这试图使对象显式调用移动构造函数, 导致返回值优化被抑制.

class A {
 public:
  A() { std::cout << "construct" << std::endl; }

  explicit A(std::string a) : a(a) { std::cout << "another construct" << std::endl; }

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
    output << a.a;
    return output;
  }

  bool operator==(const A& a) const {
    std::cout << "operator==, this " << this->a << ", other: " << a.a << std::endl;
    return this->a == a.a;
  }

 public:
  std::string a = "";
};

A getA() {
  std::cout << "getA start" << std::endl;
  A a("getA");
  std::cout << "getA end" << std::endl;
  return a;
}

A getB() {
  std::cout << "getA start" << std::endl;
  return A("getB");
}

int main() {
  A a = getA();
  std::cout << "===============================" << std::endl;
  A b = getB();
  std::cout << "===============================" << std::endl;
  A c = A("c");
  c = getA();
  std::cout << "===============================" << std::endl;
  return 0;
}
