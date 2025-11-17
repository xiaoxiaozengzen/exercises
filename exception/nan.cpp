#include <cmath>

#include <iostream>

/**
 * 在C++编程中，NaN（Not a Number）是浮点数类型（如float、double、long double）中的一种特殊值，用于表示无法定义的数值或操作结果。
 */

void generate() {
    // 1.除以0
    double zero_result = 0.0 / 0.0;
    std::cout << "0.0 / 0.0 = " << zero_result << std::endl;

    // 2.负数的平方根
    double negative_sqrt = std::sqrt(-1.0);
    std::cout << "sqrt(-1.0) = " << negative_sqrt << std::endl;

    // 3.未定义的数学操作
    double undefined_operation = std::log(-1.0);
    std::cout << "log(-1.0) = " << undefined_operation << std::endl;
}

void pority() {
    double nan_value = std::nan("");
    double nan_value2 = std::nan("1");
    std::cout << "nan_value: " << nan_value << ", nan_value2: " << nan_value2 << std::endl;
    std::cout << "is nan_value NaN? " << std::isnan(nan_value) << std::endl;
    std::cout << "nan_value == nan_value? " << (nan_value == nan_value) << std::endl;
    float nan_float = std::nanf("");
    float nan_float2 = std::nanf("1");
    std::cout << "nan_float: " << nan_float << ", nan_float2: " << nan_float2 << std::endl;
    
}

int main() {
    std::cout << "=================generate=================" << std::endl;
    generate();
    std::cout << "=================pority=================" << std::endl;
    pority();
    return 0;
}