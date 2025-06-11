#include <iostream>

/**
 * @brief c++14引入变量模板
 * 
 * 变量模板不是变量，只有实例化的变量才有值。
 */

template <typename T>
T v{};

template <typename T>
constexpr T v_c = T{5};

template <typename T = int>
constexpr T v_c_default = T{10};

template <typename std::size_t N = 5>
constexpr std::size_t v_c_default_size = N;

void example() {
    v<int> = 42; // 实例化变量模板
    std::cout << "v<int> = " << v<int> << std::endl;

    std::cout << "v_c<int> = " << v_c<int> << std::endl; // 使用变量模板的常量表达式
    std::cout << "v_c<double> = " << v_c<double> << std::endl; // 使用变量模板的常量表达式

    std::cout << "v_c_default<int> = " << v_c_default<> << std::endl; // 使用默认模板参数的变量模板

    std::cout << "v_c_default_size<10> = " << v_c_default_size<10> << std::endl; // 使用默认模板参数的变量模板
}

int main() {
    std::cout << "====================== Variable Template Example =====================" << std::endl;
    example();
    
    return 0;
}