#include <array>
#include <iostream>
#include <type_traits>
#include <tuple>

// template<
//     class T, 
//     size_t N 
// > class array;

class A {
public:
    A() {
        std::cout << "construct" << std::endl;
    }
    explicit A(int a):a(a) {
        std::cout << "another construct" << std::endl;
    }
    ~A() {
        std::cout << "deconstruct" << std::endl;
    }

    A(const A& other) {
        std::cout << "copy construct" << std::endl;
        this->a = other.a;
    }

    A& operator=(const A& other) {
        std::cout << "copy assign construct" << std::endl;
        this->a = other.a;
        return *this;
    }

    A(A&& other) {
        std::cout << "move construct" << std::endl;
        this->a = other.a;
    }

    A& operator=(A&& other) {
        std::cout << "move assign construct" << std::endl;
        this->a = other.a;
        return *this;
    }

    bool operator<(const A &a) const {
      std::cout << "operator<, this " << this->a << ", other: " << a.a << std::endl;
      return this->a < a.a;
    }

    friend std::ostream& operator<<(std::ostream &output, const A &a) { 
        output << a.a;
        return output;            
    }

    bool operator==(const A &a) const {
      std::cout << "operator==, this " << this->a << ", other: " << a.a << std::endl;
      return this->a == a.a;
    }

public:
    int a = 0;
};

void basicSetMemberTypes() {
    std::array<int, 3> arr = {1, 2, 3};
    if(std::is_same<std::array<int, 3>::value_type, int>::value) {
        std::cout << "value_type is int" << std::endl;
    }
    if(std::is_same<std::array<int, 3>::size_type, std::size_t>::value) {
        std::cout << "size_type is std::size_t" << std::endl;
    }
    if(std::is_same<std::array<int, 3>::difference_type, std::ptrdiff_t>::value) {
        std::cout << "difference_type is std::ptrdiff_t" << std::endl;
    }
    if(std::is_same<std::array<int, 3>::reference, int&>::value) {
        std::cout << "reference is int&" << std::endl;
    }
    if(std::is_same<std::array<int, 3>::const_reference, const int&>::value) {
        std::cout << "const_reference is const int&" << std::endl;
    }
    if(std::is_same<std::array<int, 3>::pointer, int*>::value) {
        std::cout << "pointer is int*" << std::endl;
    }
    if(std::is_same<std::array<int, 3>::const_pointer, const int*>::value) {
        std::cout << "const_pointer is const int*" << std::endl;
    }
    if(std::is_same<std::array<int, 3>::iterator, std::array<int, 3>::pointer>::value) {
        std::cout << "iterator is pointer" << std::endl;
    } else {
        std::cout << "iterator is not pointer" << std::endl;
    }
    if(std::is_same<std::array<int, 3>::const_iterator, std::array<int, 3>::const_pointer>::value) {
        std::cout << "const_iterator is const_pointer" << std::endl;
    } else {
        std::cout << "const_iterator is not const_pointer" << std::endl;
    }
}

void Construct() {
    std::array<A, 3> arr;
    arr[0] = A(1);
    arr[1] = A(2);
    arr[2] = A(3);
}

void MemberFun() {
    std::array<int, 3> arr = {1, 2, 3};
    
    // 1.iterator
    std::array<int, 3>::iterator it = arr.begin();
    std::cout << "begin: " << *it << std::endl;
    it = arr.end();
    std::cout << "end: " << *(it - 1) << std::endl;
    std::array<int, 3>::reverse_iterator it2 = arr.rbegin();
    std::cout << "rbegin: " << *it << std::endl;
    it2 = arr.rend();
    std::cout << "rend: " << *(it - 1) << std::endl;
    std::array<int, 3>::const_iterator it3 = arr.cbegin();
    std::cout << "cbegin: " << *it3 << std::endl;
    it3 = arr.cend();
    std::cout << "cend: " << *(it3 - 1) << std::endl;
    std::array<int, 3>::const_reverse_iterator it4 = arr.crbegin();
    std::cout << "crbegin: " << *it4 << std::endl;
    it4 = arr.crend();
    std::cout << "crend: " << *(it4 - 1) << std::endl;

    // 2.capacity
    std::cout << "size: " << arr.size() << std::endl;
    std::cout << "max_size: " << arr.max_size() << std::endl;
    std::cout << "empty: " << arr.empty() << std::endl;

    std::array<int, 0> arr2;
    std::cout << "empty: " << arr2.empty() << std::endl;

    // 3.element access
    std::cout << "arr[0]: " << arr[0] << std::endl;
    std::cout << "arr.at(0): " << arr.at(0) << std::endl;
    std::array<int, 3>::reference ref = arr.front();
    std::cout << "front: " << ref << std::endl;
    ref = 10;
    std::cout << "arr[0]: " << arr[0] << std::endl;
    std::array<int, 3>::const_reference cref = arr.back();
    std::cout << "back: " << cref << std::endl;
    std::array<int, 3>::pointer ptr = arr.data();
    std::cout << "data: " << *ptr << std::endl;
    std::cout << "data + 1: " << *(ptr + 1) << std::endl;

    // 4.modifiers
    arr.fill(11);
    for(auto i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::array<int, 3> arr3 = {1, 2, 3};
    arr3.swap(arr);
    for(auto i : arr3) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void NoMemFun() {
    std::array<int,3> myarray = {10, 20, 30};
    std::tuple<int,int,int> mytuple (10, 20, 30);

    std::tuple_element<0,decltype(myarray)>::type myelement;  // int myelement

    myelement = std::get<2>(myarray);
    std::get<2>(myarray) = std::get<0>(myarray);
    std::get<0>(myarray) = myelement;

    std::cout << "first element in myarray: " << std::get<0>(myarray) << "\n";
    std::cout << "first element in mytuple: " << std::get<0>(mytuple) << "\n";
}

int main() {
    std::cout << "--------------------------------BasicSetMemberTypes--------------------------------" << std::endl;
    basicSetMemberTypes();
    std::cout << "--------------------------------Construct--------------------------------" << std::endl;
    Construct();
    std::cout << "--------------------------------MemberFun--------------------------------" << std::endl;
    MemberFun();
    std::cout << "--------------------------------NoMemFun--------------------------------" << std::endl;
    NoMemFun();
}