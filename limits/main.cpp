// numeric_limits example
#include <climits>
#include <iostream>  // std::cout
#include <limits>    // std::numeric_limits

class A {};

int main() {
  std::cout << "int is specialized " << std::numeric_limits<int>::is_specialized << std::endl;
  std::cout << "A is specialized " << std::numeric_limits<A>::is_specialized << std::endl;

  std::cout << "Minimum value for int: " << std::numeric_limits<int>::min() << '\n';
  std::cout << "CHAR_MIN " << CHAR_MIN << ", INT_MIN" << INT_MIN << std::endl;
  std::cout << "Maximum value for int: " << std::numeric_limits<int>::max() << '\n';
  std::cout << "lowest value for int: " << std::numeric_limits<int>::lowest() << '\n';
  std::cout << "digits value for int: " << std::numeric_limits<int>::digits << '\n';
  std::cout << "digits10 value for int: " << std::numeric_limits<int>::digits10 << '\n';
  std::cout << "max_digits10 value for int: " << std::numeric_limits<int>::max_digits10 << '\n';

  std::cout << "int is signed: " << std::numeric_limits<int>::is_signed << '\n';
  std::cout << "int is integer: " << std::numeric_limits<int>::is_integer << '\n';
  std::cout << "int is exact: " << std::numeric_limits<int>::is_exact << '\n';
  std::cout << "int radix: " << std::numeric_limits<int>::radix << '\n';

  std::cout << "int epsilon " << std::numeric_limits<int>::epsilon() << '\n';

  std::cout << "int has infinity: " << std::numeric_limits<int>::has_infinity << '\n';
  return 0;
}