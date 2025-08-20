#include <iostream>
#include <memory>

/**
 * shared_ptr对象可以共享指针的所有权，同时指向另一个对象。这种能力叫做aliasing(见构造函数)。
 * 一般常用于掌管一个对象后，指向改对象的子对象或成员。因此，一个shared_ptr对象有两个指针：
 * 1）stored pointer：shared_ptr所指向的对象，可以通过operator*进行解引用；
 * 2）owner pointer：shared_ptr所管理的对象，即需要进行delete释放的对象，也是counter的计数对象。
 * 通常情况下，stored pointer和owner pointer是同一个对象，即shared_ptr所指向的对象也是需要进行delete释放的对象。
 * 但是在aliasing构造函数中，stored pointer和owner pointer是不同的
 * 
 * 不拥有任何指针的shared_ptr对象是empty的
 * 没有指向任何对象的shared_ptr对象是null的，并且不能被解引用
 * 因此：empty的shared_ptr对象不等于null的shared_ptr对象，同理null的shared_ptr对象不等于empty的shared_ptr对象。
 */

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
  /**
   * copy from weak_ptr
   * 1）如果weak_ptr是expired的，则会拷贝weak_ptr指向的shared_ptr对象
   * 2）否则会报bad_weak_ptr异常
   */
  std::weak_ptr<A> w1(a3);
  std::cout << "w1.use_count(): " << w1.use_count() << std::endl;
  std::shared_ptr<A> a6_from_w1(w1);
  std::cout << "a6_from_w1.use_count(): " << a6_from_w1.use_count() << std::endl;

  std::shared_ptr<A> a7(std::move(a5));
  /**
   * @brief move from other ptr
   * @note 从其他类型的智能指针对象移动构造shared_ptr对象，其他类型的智能指针对象会被置为nullptr。
   */
  std::unique_ptr<A> a(new A(3));
  std::shared_ptr<A> a8(std::move(a));
  std::cout << "a8.use_count(): " << a8.use_count() << std::endl;
  if (a == nullptr) {
    std::cout << "a is nullptr" << std::endl;
  } else {
    std::cout << "a is not nullptr" << std::endl;
  }

  /**
   * template <class U> 
   * shared_ptr (const shared_ptr<U>& x, element_type* p) noexcept;
   * @brief aliasing constructor
   * @note 跟拷贝构造函数一样，区别就是stored pointer变成了p
   * 
   * @note 这种构造形式一般用于：管理整个对象的生命周期，但只操作对象的某个成员或子对象。
   * @note x可以算是owner pointer,用于最后进行delete；而p可以算是stored pointer，进行*，即解引用操作；
   */
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
  std::cout << "a15.use_count(): " << a15.use_count() << std::endl;
#if 0
  // 报错，a15此时的stored pointer为空指针，不能解引用
  std::cout << "a15.use_count(): " << a15.use_count() << ", a15: " << *a15 << std::endl;
#endif
}

void MemFun() {
  std::shared_ptr<int> a(new int(1));
  std::shared_ptr<int> b(new int(2));
  a.swap(b);
  std::cout << "a: " << *a << ", b: " << *b << std::endl;

  /**
   * 改shared_ptr对象变为empty
   */
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

  /**
   * get()：返回stored pointer
   * operator*：解引用，返回stored pointer所指向的对象
   * operator->：返回一个指向stored pointer的指针，一遍访问对象的成员
   * 
   * use_count()：返回owner pointer的引用计数。若是empty，则返回0
   * unique()：如果use_count()==1，返回true；否则返回false；empty的shared_ptr对象也返回false，因为没有掌管相关的对象
   */
  std::shared_ptr<A> c(new A(5));
  std::shared_ptr<int> d(c, new int(6));
  int* p = d.get();
  std::cout << "p: " << *p << ", *d: " << *d << std::endl;
  std::cout << "c.use_count(): " << c.use_count() << ", d.use_count(): " << d.use_count() << std::endl;
  if (d.unique()) {
    std::cout << "d is unique" << std::endl;
  } else {
    std::cout << "d is not unique" << std::endl;
  }

  /**
   * operator bool：判断stored pointer是否为空
   */
  if(d) {
    std::cout << "d is not nullptr" << std::endl;
  } else {
    std::cout << "d is nullptr" << std::endl;
  }

  /**
   * owner_before()：比较两个智能指针对象的所有权顺序。判断是否管理同一份资源，以及所有权的先后顺序
   * 
   *  !(ptr.owner_before(ptr1) || ptr1.owner_before(ptr)) 为真，则ptr和ptr1指向同一对象
   */
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

/**
 * @brief enable_shared_from_this:让类的成员函数内部安全地获得指向自身的 shared_ptr
 * 
 * @note 该类提供了shared_from_this()成员函数，用于在当前成员函数中安全的获取当前对象的shared_ptr。
 *       需要注意的是，只有当当前对象已经被shared_ptr管理时，才能调用shared_from_this()。
 *       否则会抛出std::bad_weak_ptr异常。
 */
struct ShaFT : public std::enable_shared_from_this<ShaFT> {
  ShaFT() { std::cout << "ShaFT construct" << std::endl; }
  ~ShaFT() { std::cout << "ShaFT deconstruct" << std::endl; }

  void show() {
    std::shared_ptr<ShaFT> self = shared_from_this();
    std::cout << "self use_count: " << self.use_count() << std::endl;
  }
};

void NoMemFun() {
  std::shared_ptr<A> a = std::make_shared<A>(1);
  std::shared_ptr<A> b = std::allocate_shared<A>(std::allocator<A>(), 2);

  std::shared_ptr<int> foo(new int(2), DelFun());
  int* bar = new int(3);
  (*std::get_deleter<DelFun>(foo))(bar);

  std::shared_ptr<ShaFT> c = std::make_shared<ShaFT>();
  c->show();
  std::cout << "c.use_count(): " << c.use_count() << std::endl;
}

int main() {
  std::cout << "================================ MemType ================================" << std::endl;
  MemType();
  std::cout << "================================ ConFun ================================" << std::endl;
  ConFun();
  std::cout << "================================ MemFun ================================" << std::endl;
  MemFun();
  std::cout << "================================ NoMemFun ================================" << std::endl;
  NoMemFun();

  return 0;
}