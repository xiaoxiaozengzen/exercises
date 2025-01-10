#include <iostream>
#include <type_traits>

/**
    在编译期间就能知道值得常量
 */
void integral_constant() {
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
  if (std::is_same<int, decltype(a)::value_type>::value) {
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

void is_same() {
  // 1.template <class T, class U> struct is_same;
  std::is_same<int, int>::value_type value = false;

  std::is_same<int, int>::type value2;
  std::cout << "value2.value: " << value2() << std::endl;

  std::cout << "value: " << std::is_same<int, int>::value
            << std::endl;  // Inherited from integral_constant:

  if (std::is_same<int, int>()) {
    std::cout << "int and int are the same type" << std::endl;
  } else {
    std::cout << "int and int are not the same type" << std::endl;
  }
}

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename std::enable_if<std::is_integral<T>::value, bool>::type is_odd(T i) {
  return bool(i % 2);
}

// 2. the second template argument is only valid if T is an integral type:
template <class T, class = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even(T i) {
  return !bool(i % 2);
}

void enable_if() {
  // 1.template <bool Cond, class T = void> struct enable_if;
  // The type T is enabled as member type enable_if::type if Cond is true.Otherwise, enable_if::type
  // is not defined.

  short int i = 1;  // code does not compile if type of i is not integral

  std::cout << std::boolalpha;
  std::cout << "i is odd: " << is_odd(i) << std::endl;
  std::cout << "i is even: " << is_even(i) << std::endl;
}

void conditional() {
  // template <bool Cond, class T, class F> struct conditional;
  // Obtains either T or F, depending on whether Cond is true or false.
  // If Cond is true, member type conditional::type is defined as an alias of T.
  // If Cond is false, member type conditional::type is defined as an alias of F.

  std::conditional<true, int, double>::type value = 10;
  if (std::is_same<int, decltype(value)>::value) {
    std::cout << "value is int" << std::endl;
  } else {
    std::cout << "value is not int" << std::endl;
  }
}

void is_reference() {
  // template <class T> struct is_reference;
  int a = 10;
  int &b = a;

  if (std::is_same<std::is_reference<int>::value_type, bool>::value) {
    std::cout << "is_reference<int>::value_type is bool" << std::endl;
  } else {
    std::cout << "is_reference<int>::value_type is not bool" << std::endl;
  }
  if (std::is_same<std::is_reference<int>::type, std::true_type>::value) {
    std::cout << "is_reference<int>::type is true_type" << std::endl;
  } else {
    std::cout << "is_reference<int>::type is not true_type" << std::endl;
  }
  if (std::is_same<std::is_reference<int>::type, std::false_type>::value) {
    std::cout << "is_reference<int>::type is false_type" << std::endl;
  } else {
    std::cout << "is_reference<int>::type is not false_type" << std::endl;
  }

  std::cout << "is_reference<int>::value: " << std::is_reference<int>::value << std::endl;
  std::cout << "is_reference<int&>::type: " << std::is_reference<int &>::value << std::endl;
}

void remove_reference() {
  // template <class T> struct remove_reference;
  if (std::is_same<std::remove_reference<int>::type, int>::value) {
    std::cout << "remove_reference<int>::type is int" << std::endl;
  } else {
    std::cout << "remove_reference<int>::type is not int" << std::endl;
  }
  if (std::is_same<std::remove_reference<int &>::type, int>::value) {
    std::cout << "remove_reference<int&>::type is int" << std::endl;
  } else {
    std::cout << "remove_reference<int&>::type is not int" << std::endl;
  }
  if (std::is_same<std::remove_reference<int &&>::type, int>::value) {
    std::cout << "remove_reference<int&&>::type is int" << std::endl;
  } else {
    std::cout << "remove_reference<int&&>::type is not int" << std::endl;
  }
}

int main() {
  std::cout << "--------------------------------integral_constant--------------------------------"
            << std::endl;
  integral_constant();
  std::cout << "--------------------------------is_same--------------------------------"
            << std::endl;
  is_same();
  std::cout << "--------------------------------enable_if--------------------------------"
            << std::endl;
  enable_if();
  std::cout << "--------------------------------conditional--------------------------------"
            << std::endl;
  conditional();
  std::cout << "--------------------------------is_reference--------------------------------"
            << std::endl;
  is_reference();
  std::cout << "--------------------------------remove_reference--------------------------------"
            << std::endl;
  remove_reference();
}