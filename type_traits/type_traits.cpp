#include <iostream>
#include <typeinfo>
#include <typeindex>

// <type_traits>定义了很多类，这些类包含了类型信息，并且编译器在编译期间就能知道这些信息
#include <type_traits>
#include <functional>

/**
 * <typeinfo>头文件中定义了操作符typeid和dynamic_cast相关的
 * 
 * typeid返回一个type_info对象，包含了类型的信息
 */
void typeinfo_example() {
  int a = 10;
  double b = 20.0;
  std::cout << "typeid(a) == typeid(int): " << (typeid(a) == typeid(int)) << std::endl;
  std::cout << "typeid(a) != typeid(double): " << (typeid(a) != typeid(double)) << std::endl;
  const char *type_name = typeid(a).name();
  std::cout << "typeid(a).name(): " << type_name << std::endl;
  bool ret = typeid(int).before(typeid(char));
  std::cout << "typeid(int).before(typeid(char)): " << ret << std::endl;
  std::size_t hash_code = typeid(int).hash_code();
  std::cout << "typeid(int).hash_code(): " << hash_code << std::endl;

}

/**
 * <typeindex>头文件中定义了std::type_index类
 * 
 * std::type_index是一个封装了type_info的类，提供了hash_code()和operator<()等操作
 */
void typeindex_example() {
  std::type_index ti1(typeid(int));
  std::type_index ti2(ti1);
  std::type_index ti3(std::move(ti1));

  std::size_t hash_code1 = ti2.hash_code();
  std::cout << "ti2.hash_code(): " << hash_code1 << std::endl;
  const char *type_name = ti2.name();
  std::cout << "ti2.name(): " << type_name << std::endl;
  std::cout << "ti2 == ti3: " << (ti2 == ti3) << std::endl;

  /**
   * template <class T> struct hash; hash有个模板特化typeindex
   */
  std::size_t hash_code2 = std::hash<std::type_index>()(ti2);
  std::cout << "std::hash<std::type_index>()(ti2): " << hash_code2 << std::endl;
}

/**
 * @brief 用于提供编译时常量
 * 
 * template <class T, T v>
 * struct integral_constant {
 *   static const T value = v;
 *   typedef T value_type;
 *   typedef integral_constant<T, v> type;
 *   constexpr operator T() const noexcept { return v; }
 *   constexpr T operator()() const noexcept { return v; }
 * };
 */
void integral_constant() {
  std::integral_constant<int, 10> a;
  std::cout << "a.value: " << a.value << std::endl;
  if (std::is_same<int, decltype(a)::value_type>::value) {
    std::cout << "a::value_type is the same type as int" << std::endl;
  } else {
    std::cout << "a::value_type is not the same type as int" << std::endl;
  }

  /**
   * typedef integral_constant<bool,true> true_type;
   */
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

enum ENUM1 {a,b,c};
enum class ENUM2 : unsigned char {x,y,z};
void make_signed() {
  // template <class T> struct make_signed;
  if (std::is_same<std::make_signed<unsigned int>::type, int>::value) {
    std::cout << "make_signed<unsigned int>::type is int" << std::endl;
  } else {
    std::cout << "make_signed<unsigned int>::type is not int" << std::endl;
  }

  typedef std::make_signed<int>::type A;                // int
  typedef std::make_signed<unsigned>::type B;           // int
  typedef std::make_signed<const unsigned>::type C;     // const int
  typedef std::make_signed<ENUM1>::type D;              // int
  typedef std::make_signed<ENUM2>::type E;              // signed char

  std::cout << "typedefs of int:" << std::endl;
  std::cout << "A: " << std::is_same<int,A>::value << std::endl;
  std::cout << "B: " << std::is_same<int,B>::value << std::endl;
  std::cout << "C: " << std::is_same<int,C>::value << std::endl;
  std::cout << "D: " << std::is_same<int,D>::value << std::endl;
  std::cout << "E: " << std::is_same<int,E>::value << std::endl;
}

// template <class Fn, class... ArgTypes> struct result_of<Fn(ArgTypes...)>;
int fn(int) {return int();}                            // function
typedef int(&fn_ref)(int);                             // function reference
typedef int(*fn_ptr)(int);                             // function pointer
struct fn_class { int operator()(int i){return i;} };  // function-like class
class fn_class2 {
public:
  int func(int i) {return i;}
};
class fn_class3 {
public:
  int func(int i) {return i;}
  std::function<int(int)> f = [this](int i) {return i;};
};
void result_of() {
  fn_class2 f2;
  fn_class3 f3;

  typedef std::result_of<decltype(fn)&(int)>::type A;  // int
  typedef std::result_of<decltype(&fn)(int)>::type B;  // int
  typedef std::result_of<fn_ref(int)>::type C;         // int
  typedef std::result_of<fn_ptr(int)>::type D;         // int
  typedef std::result_of<fn_class(int)>::type E;       // int
  typedef std::result_of<decltype(&fn_class2::func)(fn_class2,int)>::type F; // int
  // typedef std::result_of<decltype(&f3.f)(int(int))>::type F; // 编译报错，调用对象不能是成员变量？

  std::cout << std::boolalpha;
  std::cout << "typedefs of int:" << std::endl;

  std::cout << "A: " << std::is_same<int,A>::value << std::endl;
  std::cout << "B: " << std::is_same<int,B>::value << std::endl;
  std::cout << "C: " << std::is_same<int,C>::value << std::endl;
  std::cout << "D: " << std::is_same<int,D>::value << std::endl;
  std::cout << "E: " << std::is_same<int,E>::value << std::endl;
  std::cout << "F: " << std::is_same<int,F>::value << std::endl;
}

void is_destructible() {
  // template <class T> struct is_destructible;

  struct A { };
  struct B { ~B() = delete; };
  struct C : B {};
  std::cout << std::boolalpha;
  std::cout << "is_destructible:" << std::endl;
  std::cout << "int: " << std::is_destructible<int>::value << std::endl;
  std::cout << "A: " << std::is_destructible<A>::value << std::endl;
  std::cout << "B: " << std::is_destructible<B>::value << std::endl;
  std::cout << "C: " << std::is_destructible<C>::value << std::endl;
}

int main() {
  std::cout << "--------------------------------typeinfo_example--------------------------------" << std::endl;
  typeinfo_example();
  std::cout << "--------------------------------typeindex_example--------------------------------" << std::endl;
  typeindex_example();
  std::cout << "--------------------------------integral_constant--------------------------------" << std::endl;
  integral_constant();
  std::cout << "--------------------------------is_same--------------------------------" << std::endl;
  is_same();
  std::cout << "--------------------------------enable_if--------------------------------" << std::endl;
  enable_if();
  std::cout << "--------------------------------conditional--------------------------------" << std::endl;
  conditional();
  std::cout << "--------------------------------is_reference--------------------------------" << std::endl;
  is_reference();
  std::cout << "--------------------------------remove_reference--------------------------------" << std::endl;
  remove_reference();
  std::cout << "--------------------------------make_signed--------------------------------" << std::endl;
  make_signed();
  std::cout << "--------------------------------result_of--------------------------------" << std::endl;
  result_of();
  std::cout << "--------------------------------is_destructible--------------------------------" << std::endl;
  is_destructible();
}