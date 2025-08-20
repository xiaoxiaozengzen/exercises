#include <exception>
#include <iostream>

//基类
class A {
 public:
  A(int a) : m_a(a) {}

 public:
  void display() { std::cout << "Class A: m_a=" << m_a << std::endl; }

 public:
  int m_a;
};

//派生类
class B : public A {
 public:
  B(int a, int b) : A(a), m_b(b) {}

 public:
  void display() { std::cout << "Class B: m_a=" << m_a << ", m_b=" << m_b << std::endl; }

 public:
  int m_b;
};

//基类C
class C {
 public:
  C(int c) : m_c(c) {}

 public:
  void display() { std::cout << "Class C: m_c=" << m_c << std::endl; }

 public:
  int m_c;
};

//最终派生类D
class D : public B, public C {
 public:
  D(int a, int b, int c, int d) : B(a, b), C(c), m_d(d) {}

 public:
  void display() {
    std::cout << "Class D: m_a=" << m_a << ", m_b=" << m_b << ", m_c=" << m_c << ", m_d=" << m_d
              << std::endl;
  }

 private:
  int m_d;
};

class Fa {
 public:
  int a = 10;
};

class Su : public Fa {
 public:
  int a = 12;
};

/**
 * 向上类型转换：
 *    派生类对象转换成基类对象，派生类指针转换成基类指针，派生类引用转换成基类引用
 * 向下类型转换：
 *    基类指针转换成派生类指针，基类引用转换成派生类引用
 *    注：基类对象一般不能直接转派生类对象，内存布局对不上。一般是多态得到的父类指针转回相对应的子类对象
 *    向下类型转换不一定安全
 */

/**
 * 多重继承中类的对象的内存布局：
 *    通常是将每个基类的子对象顺序排列，然后再加上派生类自己的成员
 * 例如对应D的对象：
 * +-------------------+  <-- D对象起始地址
 * | B::A::m_a         |  // B继承自A，A的成员
 * | B::m_b            |  // B自己的成员
 * +-------------------+
 * | C::m_c            |  // C的成员
 * +-------------------+
 * | D::m_d            |  // D自己的成员
 * +-------------------+
 * 其中：
 *    B和C的对象在内存中是分开的，B的对象在C的对象之前，符合继承的顺序
 */

/**
 * @brief 派生类对象转基类对象
 * 
 * @note
 *   基类                 派生类
 *  基类成员    <-赋值    基类成员
 *             <-舍弃    派生类成员
 */
void up_type_cast_object() {
  std::cout << "size A: " << sizeof(A) << ", size B: " << sizeof(B) << std::endl;
  A a(10);
  B b(66, 99);
  //赋值前
  a.display();
  b.display();
  std::cout << "--------------" << std::endl;
  //赋值后
  a = b;
  a.display();
  b.display();
}

/**
 * @brief 派生类指针转基类指针
 * 
 * @note 底层的时间就是简单的将派生类指针的地址赋值给基类指针
 */
void up_type_cast_ptr() {
  A *pa = new A(1);
  B *pb = new B(2, 20);
  C *pc = new C(3);
  D *pd = new D(4, 40, 400, 4000);
  pa = pd;
  pa->display();
  pb = pd;
  pb->display();
  pc = pd;
  pc->display();
  std::cout << "-----------------------" << std::endl;
  std::cout << "pa=" << pa << std::endl;
  std::cout << "pb=" << pb << std::endl;
  std::cout << "pc=" << pc << std::endl;  // 这里因为C是独立的类，则其地址等价于成员m_c的地址
  std::cout << "pd->m_c=" << &(pd->m_c) << std::endl;  // C的成员
  std::cout << "pd=" << pd << std::endl;

  std::cout << "-----------------------" << std::endl;
  Fa *fa = new Fa;
  Su *su = new Su;
  Su *su2 = new Su;
  fa = su;
  std::cout << "fa->a " << fa->a << std::endl;
  fa = static_cast<Su *>(su2);  // 向上类型转换
  std::cout << "fa->a " << fa->a << std::endl;

}

class Base {
 public:
  int base = 10;

 public:
  virtual void test() { std::cout << "Base::test" << std::endl; }
};

class Derived : public Base {
 public:
  int derived = 11;
};

/**
 * 向下类型转换不一定安全，dynamic_cast是安全的向下类型转换方式
 */
void down_type_cast_ptr() {
  // 基类指针转为子类指针
  Base *b_obj = new Base;
  Derived *d_obj1 = (Derived *)b_obj;
  std::cout << "d_obj1->derived:" << d_obj1->derived << std::endl;
  Derived *d_obj2 = static_cast<Derived *>(b_obj);
  std::cout << "d_obj2->derived:" << d_obj2->derived << std::endl;
  Derived *d_obj3 = dynamic_cast<Derived *>(b_obj);
  if (d_obj3) {
    std::cout << "d_obj3->derived:" << d_obj3->derived << std::endl;
  } else {
    std::cout << "d_obj3 is nullptr" << std::endl;
  }

  // 基类引用转子类引用
  Base bobj;
  Derived dobj;
  Derived &dref1 = (Derived &)(bobj);             //方式一
  Derived &drefw = static_cast<Derived &>(bobj);  //方式二
  try {
    Derived &dref2 = dynamic_cast<Derived &>(bobj);  //方式三
  }catch (const std::exception &e) {
    std::cout << "down_type_cast_ptr, capture a exception: " << e.what() << std::endl;
  }
}

/**
 * static_cast用于进行编译时类型转换
 * 
 * 1.较明显的类型转换
 * 2.向上类型转换：派生类指针或引用转换为基类指针或引用
 * 3.向下类型转换：基类指针或引用转换为派生类指针或引用（不安全）
 */
void static_example() {
  // 1.较明显的类型转换
  int a = 10;
  double b = static_cast<double>(a);
  std::cout << "b = " << b << std::endl;

  double c = 11.6;
  int d = static_cast<double>(c);
  std::cout << "d = " << d << std::endl;

  // 2.向上类型转换
  // 参考 up_type_cast函数

  // 3.向下类型转换
  // 参考down_type_cast_ptr
}

/**
 * dynamic_cast用于进行运行时类型转换
 * 
 * 1.用于多态类型之间的向上转型和向下转型，并进行安全的运行时类型检查。
 * 2.当转换的目标类型为指针时，如果转换失败，dynamic_cast会返回空指针；当转换的目标类型为引用时，如果转换失败，dynamic_cast会抛出异常。
 */
void dynamic_example() {
  // 1.用于多态类型之间的向上转型和向下转型，并进行安全的运行时类型检查。
  // 参考down_type_cast_ptr
  Base *b = new Derived;
  Derived *d = dynamic_cast<Derived *>(b);
  if (d) {
    std::cout << "d->derived: " << d->derived << std::endl;
  } else {
    std::cout << "d is nullptr" << std::endl;
  }

  // 2.当转换的目标类型为指针时，如果转换失败，dynamic_cast会返回空指针；当转换的目标类型为引用时，如果转换失败，dynamic_cast会抛出异常。
  Base bobj;
  try {
    Derived &dref3 = dynamic_cast<Derived &>(bobj);
  } catch (const std::exception &e) {
    std::cout << "capture a exception: " << e.what() << std::endl;
  }
}

/**
 * @brief const_cast的使用示例
 * 
 * @note
 *   const_cast用于添加或移除指针或引用的const或volatile修饰符。
 *   注意：
 *      如果常量本身不是常量，使用const_cast去掉const是合法的；
 *      如果常量本身是常量，使用const_cast再写的后果是未定义的。
 */
void const_example() {
  /**
   * 符合语法，虽然num为const，但通过const_cast修改了引用。
   * 但是因为num本身就是const，这会导致未定义行为
   */
  const int num = 10;
  int &ref = const_cast<int &>(num);
  ref = 20;
  std::cout << "num: " << num << ",ref: " << ref << std::endl;

  /**
   * 合法，lambda表达式中const int &a是一个引用，但是实际变量a是一个非const的int类型。
   */
  int a = 10;
  auto fun = [](const int &value) {
    int &b = const_cast<int &>(value);
    b++;
  };
  fun(a);
  std::cout << "a = " << a << std::endl;

  /**
   * 合法，p是一个int指针，通过const_cast转换为const int指针。
   */
  int b = 20;
  int *p = &b;
  // 添加 const，转换为 const int*
  const int *cp = const_cast<const int *>(p);
#if 0
  // cp 不能用于修改 b
  *cp = 30; // 编译报错
#endif
  std::cout << "b: " << b << ", cp: " << *cp << std::endl;
  b = 30; // 修改原始变量b
  std::cout << "b: " << b << ", cp: " << *cp << std::endl;

  /**
   * 合法，volatile int *vp是一个volatile指针，通过const_cast转换为int指针。
   */
  volatile int v = 100;
  volatile int *vp = &v;
  // 去除 volatile
  int *p2 = const_cast<int *>(vp);
  *p2 = 200; // 修改原始变量v
  std::cout << "v: " << v << ", p2: " << *p2 << std::endl;

  int c = 300;
  volatile int *vc = const_cast<volatile int *>(&c);
  *vc = 400; // 修改原始变量c
  std::cout << "c: " << c << ", vc: " << *vc << std::endl;
}

/**
 * @brief reinterpret_cast的使用示例
 * 
 * @note
 *   reinterpret_cast用于进行低级别的类型转换，通常用于指针类型之间的转换。
 *   它可以将一个指针类型转换为另一个不相关的指针类型，但需要谨慎使用，因为它可能导致未定义行为。
 */
void reinterpret_example() {
  int * a = new int(10);
  // 将int指针转换为char指针
  char *b = reinterpret_cast<char *>(a);
  std::cout << "a: " << a << ", b: " << static_cast<void *>(b) << std::endl;

  // 将char指针转换回int指针
  int *c = reinterpret_cast<int *>(b);
  std::cout << "c: " << c << ", *c: " << *c << std::endl;

  delete a; // 注意：这里需要释放原始的int指针
}

int main() {
  std::cout << "=================up_type_cast_object===============" << std::endl;
  up_type_cast_object();
  std::cout << "=================up_type_cast_ptr===============" << std::endl;
  up_type_cast_ptr();
  std::cout << "=================down_type_cast_ptr===============" << std::endl;
  down_type_cast_ptr();
  std::cout << "=================static_example===============" << std::endl;
  static_example();
  std::cout << "=================dynamic_example===============" << std::endl;
  dynamic_example();
  std::cout << "=================const_example===============" << std::endl;
  const_example();
  std::cout << "=================reinterpret_example===============" << std::endl;
  reinterpret_example();
  return 0;
}