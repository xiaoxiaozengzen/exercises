#include <iostream>
#include <cmath>

/**
 * double pow(double base, double exponent);
 * @note  返回以base为底exponent为指数的幂
 */
void pow_example() {
    double base = 2.0;
    double exponent = 3.0;
    double result = std::pow(base, exponent);
    std::cout << base << " raised to the power of " << exponent << " is " << result << std::endl;
}

/**
 * double sqrt(double x);
 * @note  返回x的平方根
 */
void sqrt_example() {
    double value = 16.0;
    double result = std::sqrt(value);
    std::cout << "The square root of " << value << " is " << result << std::endl;
}

/**
 * double cbrt(double x);
 * @note  返回x的立方根
 */
void cbrt_example() {
    double value = 27.0;
    double result = std::cbrt(value);
    std::cout << "The cube root of " << value << " is " << result << std::endl;
}

/**
 * double hypot(double x, double y);
 * @note  返回sqrt(x*x + y*y)，即计算直角三角形的斜边长度
 */
void hypot_example() {
    double a = 3.0;
    double b = 4.0;
    double result = std::hypot(a, b);
    std::cout << "The hypotenuse of a right triangle with sides " << a << " and " << b << " is " << result << std::endl;
}

int main() {
    std::cout << "=================== pow example ===================" << std::endl;
    pow_example();

    std::cout << "=================== sqrt example ===================" << std::endl;
    sqrt_example();

    std::cout << "=================== cbrt example ===================" << std::endl;
    cbrt_example();

    std::cout << "=================== hypot example ===================" << std::endl;
    hypot_example();

    return 0;
}