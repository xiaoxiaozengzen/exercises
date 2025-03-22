#ifndef INLINE_HPP
#define INLINE_HPP
// 不能使用#pragma once，要不然还是会报错

/**
 * inline的问题在于，它的含义在c++的发展历程中，发生了转变:
 *    1.早期的inline表示建议编译器在这里进行优化
 *    2.现在编译器基本都会忽略inline，自己选择优化.
 *      现在inline的意思已经变成了：在头文件中修饰的变量和函数(包含实现)的时候
 *      每一个引用头文件的cpp文件所持有的该函数/变量，都是同一个函数/变量。
 */
inline constexpr int value_global = 1; // inline variables are only available with ‘-std=c++17’ or ‘-std=gnu++17’

/**
 * constexpr的变量具有内部链接性，即它的作用域仅限于当前文件，类似于const
 */
constexpr int value_global1 = 2;

/**
 * const的变量具有内部链接性，即它的作用域仅限于当前文件
 * 这意味着即使头文件被多个源文件包含，每个源文件都会有自己的const副本，不会发生重定义错误
 */
const int value_global2 = 3;

#if 0
// 报错：multiple definition of `value_global2'
int value_global3 = 4;
#endif

// multiple definition
// 含义：连接器错误，同一个符号在多个目标文件中定义
// 发生阶段：
// 常见原因：
//   1. 头文件中定义了非inline或者非constexptr的全局变量，并被多个源文件包含
//   2. 多个源文件中定义了同名的全局变量

// redefination
// 含义：编译器错误，同一个符号在同一个目标文件中定义多次
// 发生阶段： 编译阶段
// 常见原因：
//   1. 同一个源文件中重复定义了同名的全局变量
//   2. 头文件中定义变量或者函数，但没有使用#pragma once或者#ifndef宏保护，导致头文件被多次包含

#endif // INLINE_HPP