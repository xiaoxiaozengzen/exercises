#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>

class A {
 public:
  A() { std::cout << "construct" << std::endl; }
  A(int a) : a(a) { std::cout << "another construct" << std::endl; }
  ~A() { std::cout << "deconstruct" << std::endl; }

  A(const A&) { std::cout << "copy construct" << std::endl; }

  A& operator=(const A&) {
    std::cout << "copy assign construct" << std::endl;
    return *this;
  }

  A(A&&) { std::cout << "move construct" << std::endl; }

  A& operator=(A&&) {
    std::cout << "move assign construct" << std::endl;
    return *this;
  }

 public:
  int a = 0;
  double b = 0.0;
};

void Traits() {
  if (std::is_same<std::allocator_traits<std::allocator<A>>::value_type, A>::value) {
    std::cout << "value_type is A" << std::endl;
  }

  if (std::is_same<std::allocator_traits<std::allocator<A>>::pointer, A*>::value) {
    std::cout << "pointer is A*" << std::endl;
  }

  if (std::is_same<std::allocator<A>::reference, A&>::value) {
    std::cout << "reference is A&" << std::endl;
  }
}

/**
    使用allocator可以手动控制内存的分配和释放，即手动控制类型的构造和析构
 */
void MemFun() {
  std::allocator<A> a_pool;

  A a;
  std::allocator<A>::pointer p = a_pool.address(a);
  std::cout << "p: " << p << " ,&a: " << &a << std::endl;

  std::allocator<A>::pointer p2 = a_pool.allocate(10);
  a_pool.deallocate(p2, 10);
  // a_pool.deallocate(p2, 10); 报错：free(): double free detected in tcache 2

  std::cout << "max size: " << a_pool.max_size() << std::endl;

  // 只会调用构造
  a_pool.construct(p2, 10);
  std::cout << "p2->a: " << p2->a << std::endl;
  a_pool.construct(p2 + 1, 12);
  std::cout << "(p2 + 1)->a: " << (p2 + 1)->a << std::endl;

  // 只会调用析构
  a_pool.destroy(p2);
  a_pool.destroy(p2 + 1);

  // template <class Type> struct rebind {
  //     typedef allocator<Type> other;
  // };
  // rebind是一个模板类，用于将allocator转换为另一个类型的allocator
  std::allocator<A>::rebind<int>::other int_pool;
  if (std::is_same<std::allocator_traits<decltype(int_pool)>::value_type, int>::value) {
    std::cout << "std::allocator<A>::rebind<int>::other is int" << std::endl;
  }
}

int main() {
  std::cout << "--------------------------------Traits--------------------------------"
            << std::endl;
  Traits();
  std::cout << "--------------------------------MemFun--------------------------------"
            << std::endl;
  MemFun();
  std::allocator<A> a_pool;
}