#pragma once

#include <iostream>

/**
 * 隐式实例化：在代码实际使用模板类/模板函数时，编译器会根据传入的具体类型推导，然后对模板进行实例化。
 *            这个过程就是隐式实例化。
 * 显式实例化：通过代码明确地告诉编译器需要针对哪个类型进行实例化，这称为显式实例化。
 *            必须将显示实例化的代码放在包含模板定义的cpp文件中。
 *            目的：在大型项目中，减少模板实例化的重复代码生成，从而减少编译时间和可执行文件的大小。(尽管现在编译器在连接阶段会进行优化)
 */

template <typename T>
int mv_convert(T value);

template <typename T>
void my_swap(T& a, T& b);