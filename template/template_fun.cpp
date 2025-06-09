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

int main() {
  std::cout << "===================== array_test=====================" << std::endl;
  array_test();
  std::cout << "===================== spcecialization_test=====================" << std::endl;
  spcecialization_test();
  std::cout << "===================== default_test=====================" << std::endl;
  default_test();
  return 0;
}