/**
https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
*/

#include <stdarg.h>  //该头文件中包含后面va_lis,va_start等函数
#include <stdio.h>

#include <iostream>

/***************************宏定义***************************** */

// __VA_ARGS__ 不能是空的，##__VA_ARGS__ 可以是空的
// __VA_ARGS__ 只能在宏定义中使用，不能在函数中使用
#define debug1(format, ...) fprintf(stderr, format, __VA_ARGS__)

#define debug2(format, args...) fprintf(stderr, format, args)

#define debug3(format, ...) fprintf(stderr, format, ##__VA_ARGS__)

#define debug4(...) printf(__VA_ARGS__)

/***************************va_list***************************** */
void MyPrintf(const char* format, ...) {
  int count = 4;
  int first;

  va_list ap;

  /**
   * @brief 该函数的作用是将可变参数列表初始化为一个指向参数列表的指针
   * @param ap 指向参数列表的指针
   * @param parmN 第一个参数
   */
  va_start(ap, format);
  while (count > 0) {
    /**
     * @brief 该函数的作用是将参数列表中的下一个参数取出，并将其存储在指定的变量中
     * 
     * @param ap 指向参数列表的指针
     * @param T 参数类型
     * 
     * @return T 返回参数值
     */
    first = va_arg(ap, int);
    count--;

    printf("first : %d\n", first);
  }
  va_end(ap);
}

/***************************template***************************** */
template <typename First, typename... Rest>
void my_print(const First& first, const Rest&... rest) {
  printf(first, rest...);  // recursive call using pack expansion syntax
}

/**************** 递归展开参数，从而进行使用 ******************* */
void print() { std::cout << std::endl; }
template <typename T>
void print(const T& t) {
  std::cout << t << std::endl;
}
template <typename First, typename... Rest>
void print(const First& first, const Rest&... rest) {
  std::cout << first << ", ";
  print(rest...);  // recursive call using pack expansion syntax
}

/****************** class ******************* */
template <typename... Values>
class tuple;
template <>
class tuple<> {};

template <typename Head, typename... Tail>
class tuple<Head, Tail...> : private tuple<Tail...> {
  typedef tuple<Tail...> inherited;

 public:
  tuple() {}
  tuple(Head v, Tail... vtail) : m_head(v), inherited(vtail...) {}
  Head& head() { return m_head; }
  inherited& tail() { return *this; }

 protected:
  Head m_head;
};

void define_test() {
  debug1("hello1 %s\n", "world");
  debug2("hello2 %s\n", "world");
  debug3("hello3 %s\n", "world");
  debug4("hello4 %s\n", "world");
}

void va_list_test() {
  MyPrintf("hello %s %d %f %c\n", "world", 1, 2.3, 'a');
}

void template_test() {
  my_print("hello\n");
  my_print("hello %s\n", "nihao");
  my_print("hello %s %d %f %d\n", "world", 1, 2.3, 'a');
  
  // 递归展开参数
  print("hello", "world", 1, 2.3, 'a');
}

void tuple_test() {
  tuple<int, float, std::string> t(1, 2.3, "hello");
  std::cout << t.head() << " " << t.tail().head() << " " << t.tail().tail().head() << std::endl;
}

int main() {
  std::cout << "====================== define_test ======================" << std::endl;
  define_test();
  std::cout << "====================== va_list_test ======================" << std::endl;
  va_list_test();
  std::cout << "====================== template_test ======================" << std::endl;
  template_test();
  std::cout << "====================== tuple_test ======================" << std::endl;
  tuple_test();
  return 0;
}