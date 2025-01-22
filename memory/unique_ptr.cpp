#include <iostream>
#include <memory>

// non-specialized
// template <class T, class D = default_delete<T>> class unique_ptr;
// array specialization
// template <class T, class D> class unique_ptr<T[],D>;

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
  if (std::is_same<std::unique_ptr<int>::element_type, int>::value) {
    std::cout << "unique_ptr<int>::element_type is int" << std::endl;
  }
  if (std::is_same<std::unique_ptr<int>::deleter_type, std::default_delete<int>>::value) {
    std::cout << "unique_ptr<int>::deleter_type is std::default_delete<int>" << std::endl;
  }
  std::default_delete<int> d;
  int* p = new int(1);
  d(p);
  if (std::is_same<std::unique_ptr<int>::pointer, int*>::value) {
    std::cout << "unique_ptr<int>::pointer is int*" << std::endl;
  }
}

struct DelFun {
  void operator()(A* p) {
    std::cout << "deleter called" << std::endl;
    delete p;
  }
};

struct DelArrFun {
  void operator()(A* p) {
    std::cout << "deleter array called" << std::endl;
    delete[] p;
  }
};

void ConFun() {
  std::unique_ptr<A> a1;
  std::unique_ptr<A> a2(nullptr);
  std::unique_ptr<A> a3(new A(1));
  std::unique_ptr<A> a4(new A(2), std::default_delete<A>());
  std::unique_ptr<A, DelFun> a5(new A(3), DelFun());
  std::unique_ptr<A> a6(std::move(a4));
  if (a4 == nullptr) {
    std::cout << "a4 is nullptr" << std::endl;
  } else {
    std::cout << "a4 is not nullptr" << std::endl;
  }
  std::unique_ptr<A, DelFun> a7(std::move(a5));
  if (a5 == nullptr) {
    std::cout << "a5 is nullptr" << std::endl;
  } else {
    std::cout << "a5 is not nullptr" << std::endl;
  }

  std::cout << "before shuzu" << std::endl;

  std::unique_ptr<A[]> b1;
  std::unique_ptr<A[]> b2(nullptr);
  std::unique_ptr<A[]> b3(new A[2]);
  std::unique_ptr<A[]> b4(new A[2], std::default_delete<A[]>());
  std::unique_ptr<A[], DelArrFun> b5(new A[2], DelArrFun());
  std::unique_ptr<A[]> b6 = std::make_unique<A[]>(2);

  std::cout << "after shuzu" << std::endl;
}

void MemFun() {
  std::unique_ptr<A> a(new A(1));
  std::unique_ptr<A, DelFun> b(new A(2), DelFun());

  std::unique_ptr<A>::pointer p = a.get();
  std::cout << "p: " << *p << ", *a: " << *a << std::endl;

  std::unique_ptr<A, DelFun>::deleter_type d = b.get_deleter();
  A* q = new A(3);
  d(q);

  bool no_null{a};
  std::cout << "no_null: " << no_null << std::endl;

  std::unique_ptr<A>::pointer r = a.release();
  if (a == nullptr) {
    std::cout << "a is nullptr" << std::endl;
    std::cout << "r: " << *r << std::endl;
  } else {
    std::cout << "a is not nullptr" << std::endl;
    std::cout << "r: " << *r << ", *a: " << *a << std::endl;
  }

  std::unique_ptr<A> s(new A(4));
  s.reset();
  if (s == nullptr) {
    std::cout << "s is nullptr" << std::endl;
  } else {
    std::cout << "s is not nullptr" << std::endl;
  }
  s.reset(new A(5));
  std::cout << "*s: " << *s << std::endl;

  s.swap(a);
  if (s == nullptr) {
    std::cout << "s is nullptr" << std::endl;
  } else {
    std::cout << "s is not nullptr" << std::endl;
  }
}

void NoMemFun() { std::unique_ptr<A> a = std::make_unique<A>(1); }

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