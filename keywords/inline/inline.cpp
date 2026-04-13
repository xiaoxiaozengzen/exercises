#include "inline1.hpp"
#include "inline2.hpp"

#if 0
// 无意义，对inline函数进行extern声明，只是声明了符号，但是没有定义
extern inline void inline_function_example_error();
#endif

int main() {
    fun1();
    fun2();

    inline_function_example();
#if 0
    // 编译报错：undefined reference to `inline_function_example_error()'
    // 原因：inline函数的定义必须放在头文件中，因为编译器需要在编译阶段看到函数的实现，以便进行内联优化。
    //        如果inline函数的定义放在源文件中，其他源文件无法访问到该函数的实现，导致链接错误。
    inline_function_example_error();
#endif
    return 0;
}