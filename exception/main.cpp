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

int main() {
  errorcode();

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