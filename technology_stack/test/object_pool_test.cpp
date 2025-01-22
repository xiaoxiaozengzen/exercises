#include <iostream>

#include "object_pool/object_pool.hpp"

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

struct CleanFun {
  void operator()(A* a) {
    std::cout << "cleaner" << std::endl;
    a->a = 0;
  }
};

int main() {
  ObjectPool::ObjectPool<A> pool(10);
  pool.regist_cleaner(CleanFun());
  std::cout << "size: " << pool.size() << std::endl;
  std::cout << "capacity: " << pool.capacity() << std::endl;
  std::cout << "empty: " << pool.empty() << std::endl;
  std::cout << "full: " << pool.full() << std::endl;

  std::cout << "==============================" << std::endl;

  std::shared_ptr<A> p = pool.get_shared_pointer();
  std::cout << "size: " << pool.size() << std::endl;
  std::cout << "capacity: " << pool.capacity() << std::endl;
  std::cout << "empty: " << pool.empty() << std::endl;
  std::cout << "full: " << pool.full() << std::endl;

  std::cout << "==============================" << std::endl;

  std::shared_ptr<A> p1 = pool.get_shared_pointer();
  std::cout << "size: " << pool.size() << std::endl;
  std::cout << "capacity: " << pool.capacity() << std::endl;
  std::cout << "empty: " << pool.empty() << std::endl;
  std::cout << "full: " << pool.full() << std::endl;

  std::cout << "==============================" << std::endl;
  std::shared_ptr<A> p2(p1);
  std::cout << "size: " << pool.size() << std::endl;
  std::cout << "capacity: " << pool.capacity() << std::endl;
  std::cout << "empty: " << pool.empty() << std::endl;
  std::cout << "full: " << pool.full() << std::endl;

  std::cout << "==============================" << std::endl;

}