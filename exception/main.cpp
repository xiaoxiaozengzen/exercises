/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-08-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cerrno>
#include <cmath>
#include <exception>
#include <iostream>
#include <system_error>  // error_code

/**
class exception {
public:
  exception () noexcept;
  exception (const exception&) noexcept;
  exception& operator= (const exception&) noexcept;
  virtual ~exception();
  virtual const char* what() const noexcept;
}
*/

/**
 * @brief
 *
 */
class MyException : public std::exception {
 public:
  const char* what() const noexcept { return "my exception!"; }
};

void errorcode() {
  errno = 0;
  std::sqrt(-1.0);  // errno set to EDOM
  std::error_code ec(errno, std::generic_category());
  std::error_condition ok;
  if (ec != ok) std::cout << "Error: " << ec.message() << '\n';
  errno = 0;

  std::pow(3.0, 10e6);
  if (errno) {
    ec.assign(errno, std::generic_category());
    std::cout << "Error2: " << ec.message() << '\n';
  }
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