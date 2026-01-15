#include <cerrno>
#include <cmath>
#include <exception>
#include <iostream>
#include <system_error>  // error_code

/**
 * class exception {
 *  public:
 *    exception() noexcept;
 *    exception(const exception&) noexcept;
 *    exception& operator=(const exception&) noexcept;
 *    virtual ~exception() noexcept;
 *    virtual const char* what() const noexcept;
 * };
 */

class MyException : public std::exception {
 public:
  const char* what() const noexcept { return "my exception!"; }
};

/**
 * @brief 描述了std::error_code对象的使用
 */
void errorcode() {
  // 1. constructors
  std::error_code ec1;  // 默认构造函数，表示没有错误
  // 1.1 class error_category;是一个基类，用于定义错误类别
  std::error_code ec2(ENOENT, std::generic_category());  // 使用错误码和错误类别构造
  std::cout << "std::generic_category == std::system_category: "
            << (std::generic_category() == std::system_category() ? "true" : "false")
            << std::endl;
  std::cout << "std::generic_category name: "
            << std::generic_category().name() << std::endl;
  std::error_condition con = std::generic_category().default_error_condition(ENOENT);
  bool equal = std::generic_category().equivalent(ec2.value(), con);
  std::cout << "ec2 equivalent to default_error_condition: "
            << (equal ? "true" : "false") << std::endl;
  std::string msg = std::generic_category().message(ENOENT);
  std::cout << "std::generic_category message for ENOENT: "
            << msg << std::endl;
  // 1.2 class error_condition;保留对应category的value
  std::error_condition ec_cond;
  std::error_condition ec_cond2(ENOENT, std::generic_category());
  ec_cond2.assign(EPERM, std::generic_category());
  std::cout << "ec_cond2 value: " << ec_cond2.value() << std::endl;
  std::error_category const& cat = ec_cond2.category();
  std::string msg2 = ec_cond2.message();
  std::cout << "ec_cond2 category name: " << cat.name()
            << ", message: " << msg2 << std::endl;
  ec_cond2.clear();
  // operator bool
  // 1.3 enum class errc;定义了一堆generic_category下的error_condition
  // 例如：address_in_use就等价于EADDRINUSE(erron=98)
  std::error_code ec3 = make_error_code(std::errc::address_in_use);
  
  // 2. member functions
  ec2.assign(EPERM, std::generic_category());  // 重新赋值
  ec2.clear();                               // 清除错误码，变为无错误状态
  std::cout << "ec2 after clear"
            << ", value: " << ec2.value()
            << ", category: " << ec2.category().name()
            << ", message: " << ec2.message() << std::endl;
  std::error_condition cond2 = ec3.default_error_condition();
  ec2.assign(EPERM, std::generic_category());
  ec3.assign(EPERM, std::system_category());
  std::cout << "ec2 value: " << ec2.value()
            << ", category: " << ec2.category().name()
            << ", message: " << ec2.message() << std::endl;
  std::cout << "ec3 value: " << ec3.value()
            << ", category: " << ec3.category().name()
            << ", message: " << ec3.message() << std::endl;
}

class A {
 public:
  A() {}  // 默认构造函数
  virtual ~A() noexcept {}  // 析构函数
  void first() noexcept {
    std::cout << "A::first()" << std::endl;
  }
  virtual void second() noexcept {
    std::cout << "A::second()" << std::endl;
  }
};

class B : public A {
 public:
  B() {}
  ~B() {}  // 重写基类的析构函数
  void first() {
    std::cout << "B::first()" << std::endl;
  }

  // 不加noexcept会编译报错，
  // error: looser throw specifier for ‘virtual void B::second()’
  void second() noexcept override {
    std::cout << "B::second()" << std::endl;
  }
};

/**
 * @brief c++11新增的noexcept说明符，用于指示函数不会抛出异常
 * @note 作用：
 * 1. 优化性能：编译器可以进行更好的优化，因为它知道某个函数不会抛出异常。
 *    编译器不会为其额外生成的异常处理代码，从而减少了开销。
 * 2. 增强代码的可读性：通过明确标注哪些函数不会抛出异常，代码的意图更加清晰。
 * 3. 标识了noexcept函数：如果一个noexcept函数在运行时抛出异常，程序会调用std::terminate()终止执行。无法被捕获。
 *
 * @note 使用：
 * 1. 在函数声明或定义中使用noexcept关键字，例如：
 *    void myFunction() noexcept {
 *        // 函数体
 *    }
 * 2. 可以使用条件表达式来决定函数是否为noexcept，例如：
 *    void myFunction() noexcept(condition) {
 *        // 函数体
 *    }
 *    其中condition是一个常量表达式，返回true或false。
 * 3. 可以在移动构造函数和移动赋值运算符中使用noexcept，以确保在容器（如std::vector）中使用这些类型时的性能优化。
 *    例如：扩容的时候，如果移动构造函数是noexcept的，std::vector可以安全地使用它，而不需要回退到拷贝构造函数。
 * 4. 在继承关系中，父类的虚函数如果被标记为noexcept，子类重写该函数时也必须保持noexcept，否则会导致编译错误。
 *    即，重写函数的异常规范必须与基类函数兼容。
 */
void noexcept_example() {
  B b{};
}

int main() {
  std::cout << "=================errorcode=================" << std::endl;
  errorcode();
  std::cout << "=================noexcept_example=================" << std::endl;
  noexcept_example();

  std::cout << "=================MyException=================" << std::endl;
  try {
    MyException ex;
    throw ex;
  } catch (MyException& ex) {
    std::cout << ex.what() << std::endl;
  } catch (std::exception& ex) {  // 因为exception是base类，因此可以通过它抓到所有类别
    std::cout << ex.what() << std::endl;
  }
  return 0;
}