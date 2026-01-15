// numeric_limits example
#include <climits>
#include <iostream>  // std::cout
#include <limits>    // std::numeric_limits
#include <cmath>
#include <iomanip>

class A {};

void int_example() {
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
}

void float_example() {
  std::cout << "float is specialized " << std::numeric_limits<float>::is_specialized << std::endl;

  std::cout << "Minimum value for float: " << std::numeric_limits<float>::min() << '\n';
  std::cout << "Maximum value for float: " << std::numeric_limits<float>::max() << '\n';
  std::cout << "lowest value for float: " << std::numeric_limits<float>::lowest() << '\n';
  std::cout << "digits value for float: " << std::numeric_limits<float>::digits << '\n';
  std::cout << "digits10 value for float: " << std::numeric_limits<float>::digits10 << '\n';
  std::cout << "max_digits10 value for float: " << std::numeric_limits<float>::max_digits10 << '\n';

  std::cout << "float is signed: " << std::numeric_limits<float>::is_signed << '\n';
  std::cout << "float is integer: " << std::numeric_limits<float>::is_integer << '\n';
  std::cout << "float is exact: " << std::numeric_limits<float>::is_exact << '\n';
  std::cout << "float radix: " << std::numeric_limits<float>::radix << '\n';

  std::cout << "float epsilon " << std::numeric_limits<float>::epsilon() << '\n';
  std::cout << "float has infinity: " << std::numeric_limits<float>::has_infinity << '\n';
  std::cout << "float infinity: " << std::numeric_limits<float>::infinity() << '\n';
}

/**
 * @brief 大小数相加测试
 * @note 理论上结果是1000.0 + 100000 * 0.00001 = 1001.0
 *       实际上结果是1000.0
 */
void big_small_test() {
    float big = 1e3f;
    float small = 1e-5f;

    // 显示big在max方向上的下一个可表示浮点数
    float next_big = std::nextafter(big, std::numeric_limits<float>::max());
    std::cout << std::setprecision(10)
              << "big: " << big 
              << ", next big: " << next_big 
              << ", diff: " << next_big - big 
              << std::endl;
    for(int i = 0; i < 100000; ++i) {
        big += small;
    }
    std::cout << std::setprecision(10) << "abnormal big: " << big << std::endl;

    // Kahan求和实现：
    // 一种补偿累加算法：在每次加法时记录被舍弃的低位误差（compensation），并在后续累加中补偿它，从而显著减少浮点累积误差。
    float sum = 0.0f;
    float c = 0.0f; // A running compensation for lost low-order bits.
    for(int i = 0; i < 100000; ++i) {
        float y = small - c;    // remove compensation term
        float t = sum + y;      // tentatively add
        c = (t - sum) - y;      // 获取新的 compensation
        sum = t;                // commit sum
    }
    std::cout << std::setprecision(10) << "normal big: " << (1000.0f + sum) << std::endl;
}

void math_example() {
  double val = 3.14;
  std::cout << "Value: " << val << std::endl;
  std::cout << "ceil: " << std::ceil(val) << std::endl;  // 向上取整
  std::cout << "floor: " << std::floor(val) << std::endl;  // 向下取整
}

int main() {
  std::cout << "============= int example =============" << std::endl;
  int_example();
  std::cout << "============= float example =============" << std::endl;
  float_example();
  std::cout << "============= big small test =============" << std::endl;
  big_small_test();
  std::cout << "============= math example =============" << std::endl;
  math_example();

  return 0;
}