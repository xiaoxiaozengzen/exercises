#include <iostream>
#include <iomanip>
#include <bitset>
#include <type_traits>

// template <size_t N>
// class bitset;

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
    output << a.a;
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
  if(std::is_same<std::bitset<10>::reference, bool&>::value) {
    std::cout << "bitset<10>::reference is bool&" << std::endl;
  } else {
    std::cout << "bitset<10>::reference is not bool&" << std::endl;
  }
}

/**
 * bitset中[0]表示最低位，[N-1]表示最高位
 */
void ConFun() {
  std::bitset<16> foo;
  std::bitset<16> bar (0x1f); // 如果参数值大于16位，只取低16位；如果参数值小于16位，高位补0

  // template<class charT, class traits, class Alloc>
  // explicit bitset (
  //   const basic_string<charT,traits,Alloc>& str,
  //   typename basic_string<charT,traits,Alloc>::size_type pos = 0,
  //   typename basic_string<charT,traits,Alloc>::size_type n = basic_string<charT,traits,Alloc>::npos)
  std::bitset<16> baz (std::string("0101111001"));
  std::cout << "foo: " << foo << std::endl;
  std::cout << "bar: " << bar << std::endl;
  std::cout << "baz: " << baz << std::endl;

}

void MemFun() {
  std::bitset<16> bar (0x1f);

  // 1. bit access
  for(std::size_t i = 0; i < 16; ++i) {
    std::cout << bar[i] << " ";
  }
  std::cout << std::endl;
  std::size_t count = bar.count();
  std::cout << "count: " << count << std::endl;
  std::size_t size = bar.size();
  std::cout << "size: " << size << std::endl;
  bool test_1 = bar.test(1);
  std::cout << "test_1: " << test_1 << std::endl;
  bool any = bar.any();
  std::cout << "any: " << any << std::endl;
  bool none = bar.none();
  std::cout << "none: " << none << std::endl;
  bool all = bar.all();
  std::cout << "all: " << all << std::endl;

  // 2. bit operation
  bar = bar.set();
  std::cout << "all: " << bar.all() << std::endl;
  bar = bar.set(1, 0);
  std::cout << "test_1: " << bar.test(1) << std::endl;
  bar = bar.reset();
  std::cout << "none: " << bar.none() << std::endl;
  bar = bar.set(1, 1);
  bar = bar.reset(1);
  std::cout << "test_1: " << bar.test(1) << std::endl;

  // 3. bitset operation
  bar.set();
  bar.reset(1);
  std::string str = bar.to_string();
  std::cout << "str: " << str << std::endl;
  unsigned long ul = bar.to_ulong();
  std::cout << std::hex << "ul: " << ul << std::endl;
  unsigned long long ull = bar.to_ullong();
  std::cout << "ull: " << ull << std::endl;

  // 4. operator
  std::bitset<4> foo (std::string("0101"));
  std::bitset<4> baz (std::string("0011"));
  std::cout << std::hex << "foo: " << foo << ", baz: " << baz << std::endl;
  std::bitset<4> bar_and = foo & baz;
  std::cout << "foo & baz: " << bar_and << std::endl;
  ~foo;
  std::cout << "~foo: " << foo << std::endl;
  foo&=baz;
  std::cout << "foo &= baz: " << foo << std::endl;
  foo<<1;
  std::cout << "foo << 1: " << foo << std::endl;
  foo<<=1;
  std::cout << "foo <<= 1: " << foo << std::endl;
}

int main() {
  std::cout << "====================== MemType ======================" << std::endl;
  MemType();
  std::cout << "====================== ConFun ======================" << std::endl;
  ConFun();
  std::cout << "====================== MemFun ======================" << std::endl;
  MemFun();
}