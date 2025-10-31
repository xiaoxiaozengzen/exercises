#include <iostream>

#include <cstddef>

int main() {
    std::byte b1{1};
    std::cout << "b1: " << std::to_integer<int>(b1) << std::endl;

    b1 <<= 2; // 左移两位
    std::cout << "b1 << 2: " << std::to_integer<int>(b1) << std::endl;
}