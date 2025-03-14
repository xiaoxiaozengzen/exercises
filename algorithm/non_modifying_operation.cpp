#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <functional>

/**
 * @brief: all_of() checks if unary predicate pred returns true for all elements in the range [first, last).
 */
void all_of() {
#if 0
template <
    class InputIterator,
    class UnaryPredicate>  
bool all_of (InputIterator first, InputIterator last, UnaryPredicate pred);
#endif

  std::array<int,8> foo = {3,5,7,11,13,17,19,23};

  if ( std::all_of(foo.begin(), foo.end(), [](int i){return i%2;}) ) {
    std::cout << "All the elements are odd numbers.\n";
  }
}

/**
 * @brief: any_of() checks if unary predicate pred returns true for at least one element in the range [first, last).
 */
void any_of() {
#if 0
template <class InputIterator, class UnaryPredicate>  
bool any_of (InputIterator first, InputIterator last, UnaryPredicate pred);
#endif

  std::array<int,8> foo = {0,0,0,0,1,0,0,0};

  if ( std::any_of(foo.begin(), foo.end(), [](int i){return i;}) ) {
    std::cout << "There is at least one element different from zero.\n";
  }
}

/**
 * @brief: none_of() checks if unary predicate pred returns true for no elements in the range [first, last).
 */
void none_of() {
#if 0
template <class InputIterator, class UnaryPredicate>
bool none_of (InputIterator first, InputIterator last, UnaryPredicate pred);
#endif

  std::array<int,8> foo = {0,0,0,0,0,0,0,0};

  if ( std::none_of(foo.begin(), foo.end(), [](int i){return i;}) ) {
    std::cout << "There is no element different from zero.\n";
  }
}

/**
 * @brief: for_each() applies function fn to each of the elements in the range [first, last).
 */
void for_each() {
#if 0
template <class InputIterator, class Function>
Function for_each (InputIterator first, InputIterator last, Function fn);
#endif

  std::vector<int> foo = {10,20,30,40,50};

  std::function<void(int&)> fun = std::for_each(foo.begin(), foo.end(), [](int &n){ n++; });

  std::cout << "foo contains:";
  for (int &x : foo) std::cout << ' ' << x;
  std::cout << '\n';

  int a = 10;
  fun(a);
  std::cout << "a = " << a << std::endl;
}

int main() {
  std::cout << "==================== all_of ====================" << std::endl;
  all_of();
  std::cout << "==================== any_of ====================" << std::endl;
  any_of();
  std::cout << "==================== none_of ====================" << std::endl;
  none_of();
  std::cout << "==================== for_each ====================" << std::endl;
  for_each();
  return 0;
}