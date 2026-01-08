#include "template_fun.hpp"

template <typename T>
void my_swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template void my_swap<int>(int& a, int& b);