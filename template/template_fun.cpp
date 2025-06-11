#include <iostream>


/****************************** 数组引用 **************************************** */
template <typename T, size_t n>
size_t array_size(const T (&)[n]) {
  return n;
}

void array_test() {
  int a[] = {1, 2, 3};

  // a pointer, size is lost
  int *ap = a;

  // a reference to the array, size is not lost
  int(&ar)[3] = a;

#if 0
  // 错误：invalid initialization of reference of type ‘int (&)[2]’ from expression of type ‘int[3]’ 
  int (&ar2)[2] = a;
#endif

  std::cout << "*ap: " << *ap << std::endl;
  std::cout << "ar: " << ar[0] << std::endl;

  std::cout << "arry_size: " << array_size<int>(ar) << std::endl;
}

/*****************************2. 模板函数的特化 ****************************************** */
template <typename T, typename U>
void my_print_pair(const T &t, const U &u) {
  std::cout << "test pair: " << t << ", " << u << std::endl;
}

#if 0
/**
 * 特化模板函数会引起多重定义错误：
 * 1.模板特化函数就是一个普通函数，只是它的名字是模板名加上参数列表
 * 2.如果多个cpp文件中都引入了这个模板特化函数的定义，那么就会引起多重定义错误
 * 3.解决方法：
 *   a. 加inline关键字
 */
template <>
void my_print<int, double>(int t, double u) {
  std::cout << "test pair: " << t << ", " << u << std::endl;
}
#else
template <>
inline void my_print_pair<int, int>(const int &t, const int &u) {
  std::cout << "test pair: " << t << ", " << u << std::endl;
}
#endif

/**
 * @note 模板函数没有偏特化
 * @note 可以通过重载实现类似的效果
 * 
 */
template <typename T>
inline void my_print_pair(const T &t, const T &u) {
  std::cout << "test pair: " << t << ", " << u << "(int)" << std::endl;
}

void spcecialization_test() {
  my_print_pair(1, 2.0);  // 调用模板函数
  my_print_pair(1, 2);    // 调用重载后的模板函数，实现类似的偏特化效果
}

/*****************************3. 默认实参和形参 ****************************************** */
template <typename T, typename U = int>
void my_print_default(const T &t, const U &u = 0) {
  std::cout << "test default: " << t << ", " << u << std::endl;
}
template <typename T, std::size_t n = 10>
void my_print_default_value(const T value) {
  std::cout << "test default value: " << value << ", n: " << n << std::endl;
}

void default_test() {
  my_print_default(1);  // 调用默认实参
  my_print_default(1, 2);  // 调用默认实参

  my_print_default_value<int>(20);  // 调用默认值
  my_print_default_value<int, 20>(10);  // 调用默认值
}

/*****************************4. SFINAE ****************************************** */
/**
 * @brief SFINAE（Substitution Failure Is Not An Error）:代换失败不是错误
 * 
 * @note SFINAE是C++模板编程中的一个重要概念，在函数模板的重载决议中使用该规则：
 * 当模板形参在替换成显式指定的类型或推导出的类型失败时，从重载集中丢弃这个特化，而非导致编译失败
 * 注意：此特性被用于模板元编程中
 * 
 * @note 对模板的形参进行两次替换：
 * 1.第一次，在模板类型推导前，对显示指定的模板实参进行代换
 * 2.第二次，在模板类型推导后，对推导出的实参数和默认实参进行代换
 */

template<typename A>
struct B { using type = typename A::type; }; // 待决名，C++20 之前必须使用 typename 消除歧义

template<
    class T,
    class U = typename T::type,              // 如果 T 没有成员 type 那么就是 SFINAE 失败（代换失败）
    class V = typename B<T>::type>           // 如果 T 没有成员 type 那么就是硬错误 不过标准保证这里不会发生硬错误，因为到 U 的默认模板实参中的代换会首先失败
void foo(int) { std::puts("SFINAE T::type B<T>::type"); }

template<typename T>
void foo(double) { std::puts("SFINAE T"); }


void template_sfinane_test() {
    struct C { using type = int; };

    foo<B<C>>(1);       // void foo(int)    输出: SFINAE T::type B<T>::type
    foo<void>(1);       // void foo(double) 输出: SFINAE T
#if 0
    /**
     * @note 编译报错：
     * error: no matching function for call to ‘foo<void, int>(int)’
     */
    foo<void, int>(1);
#endif
}

int main() {
  std::cout << "===================== array_test=====================" << std::endl;
  array_test();
  std::cout << "===================== spcecialization_test=====================" << std::endl;
  spcecialization_test();
  std::cout << "===================== default_test=====================" << std::endl;
  default_test();
  std::cout << "===================== template_sfinane_test=====================" << std::endl;
  template_sfinane_test();
  return 0;
}