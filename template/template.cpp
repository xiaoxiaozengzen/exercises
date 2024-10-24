#include <iostream>

template<typename T, size_t n>
size_t array_size(const T (&)[n])
{
    return n;
}

int main() {
    int a[] = {1, 2, 3};

    int *ap = a; // a pointer, size is lost
    int (&ar)[3] = a; // a reference to the array, size is not lost
    // 错误：invalid initialization of reference of type ‘int (&)[2]’ from expression of type ‘int [3]’
    // int (&ar2)[2] = a;

    std::cout << "*ap: " << *ap << std::endl;
    std::cout << "ar: " << ar[0] << std::endl;

    std::cout << "arry_size: " << array_size<int>(ar) << std::endl;
}