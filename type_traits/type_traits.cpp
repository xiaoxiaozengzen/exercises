#include <type_traits>
#include <iostream>

/**
    在编译期间就能知道值得常量
 */
void HelperClass() {
    // template <class T, T v>
    // struct integral_constant {
        // static constexpr T value = v;
        // typedef T value_type;
        // typedef integral_constant<T,v> type;
        // constexpr operator T() const noexcept { return v; }
        // constexpr T operator()() const noexcept { return v; }
    // };
    std::integral_constant<int, 10> a;
    std::cout << "a.value: " << a.value << std::endl;
    if(std::is_same<int, decltype(a)::value_type>::value) {
        std::cout << "a::value_type is the same type as int" << std::endl;
    } else {
        std::cout << "a::value_type is not the same type as int" << std::endl;
    }

    // typedef integral_constant<bool,true> true_type;

    std::true_type t;
    std::cout << "t.value: " << t.value << std::endl;
    std::cout << "t(): " << t() << std::endl;
    std::cout << "t: " << t << std::endl;
}

void TypeTraits() {
    // 1.template <class T, class U> struct is_same;
    std::is_same<int, int>::value_type value = false;

    std::is_same<int, int>::type value2;
    std::cout << "value2.value: " << value2() << std::endl;

    std::cout << "value: " << std::is_same<int, int>::value << std::endl; //Inherited from integral_constant:

    if(std::is_same<int, int>()) {
        std::cout << "int and int are the same type" << std::endl;
    } else {
        std::cout << "int and int are not the same type" << std::endl;
    }
}

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename std::enable_if<std::is_integral<T>::value,bool>::type
is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
template < class T,
        class = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}

void Transform() {
    // 1.template <bool Cond, class T = void> struct enable_if;
    // The type T is enabled as member type enable_if::type if Cond is true.Otherwise, enable_if::type is not defined.

    short int i = 1;    // code does not compile if type of i is not integral

    std::cout << std::boolalpha;
    std::cout << "i is odd: " << is_odd(i) << std::endl;
    std::cout << "i is even: " << is_even(i) << std::endl;
}

int main() {
    std::cout << "--------------------------------HelperClass--------------------------------" << std::endl;
    HelperClass();
    std::cout << "--------------------------------TypeTraits--------------------------------" << std::endl;
    TypeTraits();
    std::cout << "--------------------------------Transform--------------------------------" << std::endl;
    Transform();
}