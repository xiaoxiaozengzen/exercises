/**
https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
*/

#include <stdarg.h>  //该头文件中包含后面va_list.va_start等函数
#include <stdio.h>

#include <iostream>

//  ISO C standard of 1999
#define debug1(format, ...) fprintf(stderr, format, __VA_ARGS__)
#define debug4(...) printf(__VA_ARGS__)

#define debug2(format, args...) fprintf(stderr, format, args)

#define debug3(format, ...) fprintf(stderr, format, ##__VA_ARGS__)

/**
    va_list
*/
void MyPrintf(const char* format, ...) {
  int count = 4;
  int first;

  va_list ap;
  va_start(ap, format);
  while (count > 0) {
    first = va_arg(ap, int);
    count--;

    printf("first : %d\n", first);
  }
  va_end(ap);
}

/**
    function
*/
template <typename First, typename... Rest>
void my_print(const First& first, const Rest&... rest) {
  std::cout << first << ", ";
  printf(rest...);  // recursive call using pack expansion syntax
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

int main() {
  debug1("hello %s\n", "world");
  debug2("hello %s\n", "world");
  debug3("hello %s\n", "world");
  debug4("hello %s\n", "world");

  MyPrintf("nihoa ", 1, 2, 3, 4);

  my_print("nihoa", "hello %s\n", "hahah");
  print("nihoa", "hello %s", "hahah");

  tuple<int, float, std::string> t(1, 2.3, "hello");
  std::cout << t.head() << " " << t.tail().head() << " " << t.tail().tail().head() << std::endl;
}