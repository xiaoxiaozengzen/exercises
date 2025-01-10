#include <iostream>
#include <memory>

// template<class T>
// class shared_ptr;

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
  if (std::is_same<std::shared_ptr<A>::element_type, A>::value) {
    std::cout << "shared_ptr<A>::element_type is A" << std::endl;
  } else {
    std::cout << "shared_ptr<A>::element_type is not A" << std::endl;
  }
}

void ConFun() {
  std::shared_ptr<A> a1;
  std::shared_ptr<A> a2(nullptr);
  std::shared_ptr<A> a3(new A(1));
  std::shared_ptr<A> a4(new A(2), std::default_delete<A>());
  std::shared_ptr<A> a5(new A(3), [](A* p) {
    std::cout << "custom deleter" << std::endl;
    delete p;
  });
  std::shared_ptr<A> a6(a5);
  std::shared_ptr<A> a7(std::move(a5));
  // move from other types of managed pointers
  std::unique_ptr<A> a(new A(3));
  std::shared_ptr<A> a8(std::move(a));
  std::cout << "a8.use_count(): " << a8.use_count() << std::endl;
  if (a == nullptr) {
    std::cout << "a is nullptr" << std::endl;
  } else {
    std::cout << "a is not nullptr" << std::endl;
  }

  // std::weak_ptr<A> w1;
  // std::shared_ptr<A> a9(w1);

  // aliasing constructor
  // template <class U> shared_ptr (const shared_ptr<U>& x, element_type* p) noexcept;
  // 共享指针并不拥有p，也不会管理它的内存；而是和x共同拥有x管理的对象，并且增加x的一个计数，同时负责x指向对象的内存管理；
  // 这种构造形式一般用来指向一个已经被智能指针管理的对象的成员；
  // x可以算是owner pointer,用于最后进行delete；而p可以算是stored pointer，进行*，即解引用操作；
  std::shared_ptr<A> a10(new A(20));
  std::shared_ptr<A> a11(a10, a10.get());
  std::cout << "a10.use_count(): " << a10.use_count() << ", a: " << a10->a << std::endl;
  std::cout << "a11.use_count(): " << a11.use_count() << ", a: " << a11->a << std::endl;
  std::shared_ptr<A> a13(new A(11));
  std::shared_ptr<int> a14(a13, &a3->a);
  int* p = nullptr;
  std::shared_ptr<int> a15(a13, p);
  std::cout << "a10.use_count(): " << a10.use_count() << ", a: " << a10->a << std::endl;
  std::cout << "a11.use_count(): " << a11.use_count() << ", a: " << a11->a << std::endl;
  std::cout << "a13.use_count(): " << a13.use_count() << ", a13: " << *a13 << std::endl;
  std::cout << "a14.use_count(): " << a14.use_count() << ", a14: " << *a14 << std::endl;
  // 报错，a15此时的stored pointer为空指针
  // std::cout << "a15.use_count(): " << a15.use_count() << ", a15: " << *a15 << std::endl;
}

void MemFun() {
  std::shared_ptr<int> a(new int(1));
  std::shared_ptr<int> b(new int(2));
  a.swap(b);
  std::cout << "a: " << *a << ", b: " << *b << std::endl;

  a.reset();
  std::cout << "a.use_count(): " << a.use_count() << std::endl;
  if (a == nullptr) {
    std::cout << "a is nullptr" << std::endl;
  }
  a.reset(new int(3));
  std::cout << "a.use_count(): " << a.use_count() << ", *a: " << *a << std::endl;
  a.reset(new int(4), [](int* p) {
    std::cout << "custom deleter" << std::endl;
    delete p;
  });
  std::cout << "a.use_count(): " << a.use_count() << ", *a: " << *a << std::endl;

  std::shared_ptr<A> c(new A(5));
  std::shared_ptr<int> d(c, new int(6));
  int* p = d.get();  // Returns the stored pointer.
  std::cout << "p: " << *p << ", *d: " << *d << std::endl;
  // Returns the number of shared_ptr objects that share ownership over the same pointer as this
  // object (including it).
  std::cout << "c.use_count(): " << c.use_count() << ", d.use_count(): " << d.use_count()
            << std::endl;

  if (d.unique()) {
    std::cout << "d is unique" << std::endl;
  } else {
    std::cout << "d is not unique" << std::endl;
  }

  // 指针的weak compare。1）两个指针类型是否一致 2）前者地址是否小于后者
  // 改接口用来判断两个指针是否指向同一对象：
  // !(ptr.owner_before(ptr1) || ptr1.owner_before(ptr)) 为真，则ptr和ptr1指向同一对象
  std::shared_ptr<A> e(c);
  std::cout << "c.owner_before(e): " << c.owner_before(e) << std::endl;
  std::cout << "b.owner_before(c): " << b.owner_before(c) << std::endl;
  std::cout << "b.owner_berfore(d): " << b.owner_before(d) << std::endl;
}

struct DelFun {
  void operator()(int* p) {
    std::cout << "deleter called" << std::endl;
    delete p;
  }
};

struct ShaFT : public std::enable_shared_from_this<ShaFT> {
  ShaFT() { std::cout << "ShaFT construct" << std::endl; }
  ~ShaFT() { std::cout << "ShaFT deconstruct" << std::endl; }
};

void NoMemFun() {
  std::shared_ptr<A> a = std::make_shared<A>(1);
  std::shared_ptr<A> b = std::allocate_shared<A>(std::allocator<A>(), 2);

  std::shared_ptr<int> foo(new int(2), DelFun());
  int* bar = new int(3);
  (*std::get_deleter<DelFun>(foo))(bar);

  std::shared_ptr<ShaFT> c = std::make_shared<ShaFT>();
  std::shared_ptr<ShaFT> d = c->shared_from_this();
  std::cout << "c.use_count(): " << c.use_count() << ", d.use_count(): " << d.use_count()
            << std::endl;
}

int main() {
  std::cout << "================================ MemType ================================"
            << std::endl;
  MemType();
  std::cout << "================================ ConFun ================================"
            << std::endl;
  ConFun();
  std::cout << "================================ MemFun ================================"
            << std::endl;
  MemFun();
  std::cout << "================================ NoMemFun ================================"
            << std::endl;
  NoMemFun();
}