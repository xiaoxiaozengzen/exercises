#include <iostream>

// 操作符重载范围
// 1.如果一个重载操作符是类成员，那么只有当与
// 它的左操数是该类的对象时，该操作符才会被调用。如果
// 该操作符的左操作数必须是其他的类型，则操作符必须被重载为全局名字空间的成员。

// 2.C++要求赋值=，下标[]，调用()， 和成员指向->
// 操作符必须被定义为类成员操作符。任何把这些操作符定义为名
// 字空间成员的定义都会被标记为编译时刻错误。

// 3.如果有一个操作数是类类型如string类的情形那么对于对称操作符比如等于操作符最好定义为全局名字空间成员。

// 4.""_v形式的操作符重载，用于重载用户定义的字面量

class person {
 private:
  int age;

 public:
  person(int a) { this->age = a; }
  inline bool operator==(const person &ps) const;
  inline void operator()() { std::cout << "callable object" << std::endl; }

  // 类型转换运算符: operator type() const;
  operator int() { return this->age; }
};

// 因为operator ==是class
// person的一个成员函数，所以对象p1,p2都可以调用该函数，上面的if语句中，相当
// 于p1调用函数==，把p2作为该函数的一个参数传递给该函数，从而实现了两个对象的比较。
inline bool person::operator==(const person &ps) const {
  if (this->age == ps.age) return true;
  return false;
}

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

/******************""_v形式重载************** */
// 双引号之间加的内容是一些字面常量，比如"hello"，"world"等等，这些字面常量是由编译器来解释的，我们可以通过重载""_v来自定义这些字面量的含义。
class Length {
 public:
  Length(int l) : length_(l) {}
  int getLength() { return length_; }

 private:
  int length_;
};

Length operator""_m(unsigned long long l) { return Length(l); }

/****************** ++操作符重载************** */
class Counter {
 public:
  Counter() : count(0) {}
  Counter(int c) : count(c) {}

  // 前置++
  void operator++() { ++count; }
  // 后置++
  void operator++(int) { count++; }

 public:
  int count;
};

int main() {
  person p1(10);
  person p2(10);
  if (p1 == p2) {
    std::cout << "the age is equal!" << std::endl;
  }
  p2();

  int a = p1;
  std::cout << "a = " << a << std::endl;

  people p11(10);
  people p22(10);
  if (p11 == p22) {
    std::cout << "the age is equal!" << std::endl;
  }

  p11 = 30;
  std::cout << "p11.age " << p11.age << std::endl;

  Length l = 10_m;
  std::cout << "length: " << l.getLength() << std::endl;

  Counter coun;
  coun++;
  std::cout << "coun.count: " << coun.count << std::endl;
  ++coun;
  std::cout << "coun.count: " << coun.count << std::endl;
}
