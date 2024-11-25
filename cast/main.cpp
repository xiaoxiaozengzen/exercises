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

 protected:
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
    向上类型转换：派生类对象转换成基类对象，派生类指针转换成基类指针，派生类引用转换成基类引用
    向下类型转换：基类指针转换成派生类指针，基类引用转换成派生类引用.(注：基类对象一般不能直接转派生类对象，内存布局对不上)
    向下类型转换不一定安全
 */
void up_type_cast_object() {
  /**
      基类                 派生类
      基类成员    <-赋值    基类成员
                 <-舍弃    派生类成员

   */
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

void up_type_cast_ptr() {
  /**
      只是把指针指向的位置修改了
   */
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
  std::cout << "pc=" << pc << std::endl;
  std::cout << "pd=" << pd << std::endl;

  std::cout << "-----------------------" << std::endl;
  Fa *fa = new Fa;
  Su *su = new Su;
  fa = su;
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
    向下类型转换不一定安全，dynamic_cast是安全的向下类型转换方式
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

  // 基类左值转子类引用
  Base bobj;
  Derived dobj;
  Derived &dref1 = (Derived &)(bobj);             //方式一
  Derived &drefw = static_cast<Derived &>(bobj);  //方式二
  // Derived &dref3=dynamic_cast<Derived&>(bobj);//方式三，只有Base
  // class中有虚函数才能使用，否则编译错误（Derived class中有虚函数也不行）
}

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
const_cast用于添加或移除指针或引用的const或volatile修饰符
*/
void const_example() {
  /**
  一个变量在使用const_cast去掉指针或者引用的const限定符后:
      如果常量本身不是常量，获得的权限是合法的，
      如果本身是常量，使用const_cast再写的后果是未定义的。
   */
  const int num = 10;
  int &ref = const_cast<int &>(num);
  ref =
      20;  // 合法，虽然num为const，但通过const_cast修改了引用。这会导致未定义行为，且程序设计有无问题，为什么要修改const
  std::cout << "num: " << num << ",ref: " << ref << std::endl;

  int a = 10;
  auto fun = [](const int &a) {
    int &b = const_cast<int &>(a);
    b++;
  };
  fun(a);
  std::cout << "a = " << a << std::endl;
}

void reinterpret_example() {
  // 强制转换
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
  return 0;
}