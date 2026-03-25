#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>

/**
 * double exp(double x);
 * @note 返回值等价e的x次幂
 */
void exp_example() {
    std::stringstream ss;
    ss << "E = " << std::fixed << std::setprecision(6) << M_E;
    std::cout << ss.str() << std::endl;
    ss.str("");
    double ret1 = exp(1.0);
    ss << "exp(1.0) = " << std::fixed << std::setprecision(6) << ret1;
    std::cout << ss.str() << std::endl;
    ss.str("");
    double input = 2.0;
    double ret2 = 1 / (1 + exp(-1 * input));
    ss << "sigmoid(" << input << ") = " << std::fixed << std::setprecision(6) << ret2;
    std::cout << ss.str() << std::endl;
}

int main() {
    std::cout << "=========== exp example ==========\n";
    exp_example();

    return 0;
}