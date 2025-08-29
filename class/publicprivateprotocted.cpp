#include <iostream>

/**
 * 继承方式(public, protected, private)对基类成员访问权限的影响
 * 1. public继承
 *    - 基类的public成员在派生类中仍然是public
 *    - 基类的protected成员在派生类中仍然是protected
 *    - 基类的private成员在派生类中不可访问
 * 2. protected继承
 *   - 基类的public成员在派生类中变为protected
 *   - 基类的protected成员在派生类中仍然是protected
 *   - 基类的private成员在派生类中不可访问
 * 3. private继承
 *   - 基类的public成员在派生类中变为private
 *   - 基类的protected成员在派生类中变为private
 *   - 基类的private成员在派生类中不可访问
 * 
 * 注意：
 *   - 无论哪种继承方式，基类的private成员在派生类中都不可访问。
 *   - 继承方式只影响"外部代码"通过派生类对象访问基类成员的权限，不影响派生类内部对基类成员的访问权限。
 *   - 无论那种继承方式，派生类内部都可以访问基类的public和protected成员。
 */

class Base {
public:
  Base() {
    std::cout << "Base construct" << std::endl;
  }
  ~Base() {
    std::cout << "Base deconstruct" << std::endl;
  }

  int base_pub = 1;
  void base_pub_func() {
    std::cout << "Base public function" << std::endl;
  }
protected:
  int base_pro = 2;
  void base_pro_func() {
    std::cout << "Base protected function" << std::endl;
  }
private:
  int base_pri = 3;
  void base_pri_func() {
    std::cout << "Base private function" << std::endl;
  }
};

class DerivedPublic : public Base {
public:
  DerivedPublic() {
    std::cout << "DerivedPublic construct" << std::endl;
  }
  ~DerivedPublic() {
    std::cout << "DerivedPublic deconstruct" << std::endl;
  }
  void access() {
    std::cout << "DerivedPublic access base_pub: " << base_pub << std::endl;
    std::cout << "DerivedPublic access base_pro: " << base_pro << std::endl;
    base_pub_func();
    base_pro_func();
  }
};

class DerivedProtected : protected Base {
public:
  DerivedProtected() {
    std::cout << "DerivedProtected construct" << std::endl;
  }
  ~DerivedProtected() {
    std::cout << "DerivedProtected deconstruct" << std::endl;
  }
  void access() {
    std::cout << "DerivedProtected access base_pub: " << base_pub << std::endl;
    std::cout << "DerivedProtected access base_pro: " << base_pro << std::endl;
    base_pub_func();
    base_pro_func();
  }
};

class DerivedPrivate : private Base {
public:
  DerivedPrivate() {
    std::cout << "DerivedPrivate construct" << std::endl;
  }
  ~DerivedPrivate() {
    std::cout << "DerivedPrivate deconstruct" << std::endl;
  }
  void access() {
    std::cout << "DerivedPrivate access base_pub: " << base_pub << std::endl;
    std::cout << "DerivedPrivate access base_pro: " << base_pro << std::endl;
    base_pub_func();
    base_pro_func();
  }
};

void publicprivateprotocted_test() {
  std::cout << "+++++++++++++ DerivedPublic +++++++++++++" << std::endl;
  DerivedPublic dp;
  dp.access();
  std::cout << "dp.base_pub: " << dp.base_pub << std::endl;

  std::cout << "+++++++++++++ DerivedProtected +++++++++++++" << std::endl;
  DerivedProtected dpr;
  dpr.access();
  // dpr.base_pub_func(); // error: ‘void Base::base_pub_func()’ is inaccessible within this context

  std::cout << "+++++++++++++ DerivedPrivate +++++++++++++" << std::endl;
  DerivedPrivate dpt;
  dpt.access();

  std::cout << "+++++++++++++= End +++++++++++++=" << std::endl;
}

class Fa {
public:
  Fa() {
    std::cout << "Fa construct" << std::endl;
  }
  Fa(int v) : fa_pub(v) {
    std::cout << "Fa construct with value: " << v << std::endl;
  }
  ~Fa() {
    std::cout << "Fa deconstruct" << std::endl;
  }

private:
  Fa(const Fa &other) {
    std::cout << "Fa copy construct" << std::endl;
    this->fa_pub = other.fa_pub;
  }

  Fa &operator=(const Fa &other) {
    std::cout << "Fa copy assign construct" << std::endl;
    this->fa_pub = other.fa_pub;
    return *this;
  }

public:
  int fa_pub = 1;
};

class Son : public Fa {
public:
  Son(){
    std::cout << "Son construct" << std::endl;
  }
  ~Son() {
    std::cout << "Son deconstruct" << std::endl;
  }

  int son_pub = 2;
};

void test_inherit_copy() {
  Son s1;
  s1.fa_pub = 10;
  s1.son_pub = 20;

  /**
   * 注意：
   *   - 父类的拷贝构造函数是private或者delete时，子类的拷贝构造函数会被隐式删除，需要自己实现子类的拷贝构造函数
   */
#if 0
  // error: use of deleted function ‘Son::Son(const Son&)’
  // note: ‘Son::Son(const Son&)’ is implicitly deleted because the default definition would be ill-formed:
  // error: ‘Fa::Fa(const Fa&)’ is private within this context
  Son s2 = s1;
  std::cout << "s2.fa_pub: " << s2.fa_pub << ", s2.son_pub: " << s2.son_pub << std::endl;
#endif
}

int main() {
  std::cout << "================== publicprivateprotocted_test ====================" << std::endl;
  publicprivateprotocted_test();
  std::cout << "================== test_inherit_copy ====================" << std::endl;
  test_inherit_copy();

  return 0;
}