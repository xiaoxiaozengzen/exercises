#include <iostream>
#include <cmath>

/**
 * @brief 向上取整，即向正无穷方向取整
 * @note 该函数的返回值是跟参数同样类型的浮点:
 *       - 避免了整数类型的溢出问题，例如浮点数很大时，向上取整可能会超过整数类型的范围。
 *       - 保持了输入类型的一致性，方便后续的计算和使用
 *       - 浮点语义更完整，还有处理NAN和INF的能力
 */
void ceil_example() {
    double x = 3.14;
    double result = std::ceil(x);
    int int_result = static_cast<int>(result); // 将结果转换为整数类型
    std::cout << "Ceil of " << x << " is " << result << " (as int: " << int_result << ")" << std::endl; // 输出: Ceil of 3.14 is 4

    double y = -3.14;
    double result_y = std::ceil(y);
    int int_result_y = static_cast<int>(result_y); // 将结果转换为整数类型
    std::cout << "Ceil of " << y << " is " << result_y << " (as int: " << int_result_y << ")" << std::endl; // 输出: Ceil of -3.14 is -3

    double z = 3.5;
    double result_z = std::ceil(z);
    int int_result_z = static_cast<int>(result_z); // 将结果转换为整数类型
    std::cout << "Ceil of " << z << " is " << result_z << " (as int: " << int_result_z << ")" << std::endl; // 输出: Ceil of 3.5 is 4
}

/**
 * @brief 用于对整数进行向上取整的函数
 * @note 实际中常常需要得到n/N的向上取整结果，可以通过以下方式实现
 */
void my_ceil_example() {
    int n = 10;
    int N = 3;
    int result = (n + N - 1) / N;
    std::cout << "My ceil of " << n << " / " << N << " is " << result << std::endl; // 输出: Ceil of 10 / 3 is 4

    /**
     * 另外一种写法：(n - 1) / N + 1
     * 这种写法有弊端：
     * - 当n>0时，跟上面写法等价
     * - 当n=0时，n-1为负数字，符号语义不对的，且若输入是无符号整数时，n-1会发生溢出，导致结果错误
     */
}

/**
 * @brief 对浮点数向下取整，即向负无穷方向取整
 * @note 该函数的返回值是跟参数同样类型的浮点:
 *       - 避免了整数类型的溢出问题，例如浮点数很大时，向下取整可能会超过整数类型的范围。
 *       - 保持了输入类型的一致性，方便后续的计算和使用
 *       - 浮点语义更完整，还有处理NAN和INF的能力
 */
void floor_example() {
    double x = 3.14;
    double result = std::floor(x);
    int int_result = static_cast<int>(result); // 将结果转换为整数类型
    std::cout << "Floor of " << x << " is " << result << " (as int: " << int_result << ")" << std::endl; // 输出: Floor of 3.14 is 3

    double y = -3.14;
    double result_y = std::floor(y);
    int int_result_y = static_cast<int>(result_y); // 将结果转换为整数类型
    std::cout << "Floor of " << y << " is " << result_y << " (as int: " << int_result_y << ")" << std::endl; // 输出: Floor of -3.14 is -4

    double z = 3.5;
    double result_z = std::floor(z);
    int int_result_z = static_cast<int>(result_z); // 将结果转换为整数类型
    std::cout << "Floor of " << z << " is " << result_z << " (as int: " << int_result_z << ")" << std::endl; // 输出: Floor of 3.5 is 3
}

/**
 * @brief 对浮点数进行四舍五入，返回最接近的整数值
 * @note 该函数的返回值是跟参数同样类型的浮点:
 *       - 避免了整数类型的溢出问题，例如浮点数很大时，四舍五入可能会超过整数类型的范围。
 *       - 保持了输入类型的一致性，方便后续的计算和使用
 *       - 浮点语义更完整，还有处理NAN和INF的能力
 */
void round_example() {
    double x = 3.14;
    double result = std::round(x);
    int int_result = static_cast<int>(result); // 将结果转换为整数类型
    std::cout << "Round of " << x << " is " << result << " (as int: " << int_result << ")" << std::endl; // 输出: Round of 3.14 is 3

    double y = -3.14;
    double result_y = std::round(y);
    int int_result_y = static_cast<int>(result_y); // 将结果转换为整数类型
    std::cout << "Round of " << y << " is " << result_y << " (as int: " << int_result_y << ")" << std::endl; // 输出: Round of -3.14 is -3

    double z = 3.5;
    double result_z = std::round(z);
    int int_result_z = static_cast<int>(result_z); // 将结果转换为整数类型
    std::cout << "Round of " << z << " is " << result_z << " (as int: " << int_result_z << ")" << std::endl; // 输出: Round of 3.5 is 4
}

/**
 * @brief 对浮点数进行截断，即去掉小数部分，返回整数部分
 * @note 该函数的返回值是跟参数同样类型的浮点:
 *       - 避免了整数类型的溢出问题，例如浮点数很大时，截断可能会超过整数类型的范围。
 *       - 保持了输入类型的一致性，方便后续的计算和使用
 *       - 浮点语义更完整，还有处理NAN和INF的能力
 */
void trunc_example() {
    double x = 3.14;
    double result = std::trunc(x);
    int int_result = static_cast<int>(result); // 将结果转换为整数类型
    std::cout << "Trunc of " << x << " is " << result << " (as int: " << int_result << ")" << std::endl; // 输出: Trunc of 3.14 is 3

    double y = -3.14;
    double result_y = std::trunc(y);
    int int_result_y = static_cast<int>(result_y); // 将结果转换为整数类型
    std::cout << "Trunc of " << y << " is " << result_y << " (as int: " << int_result_y << ")" << std::endl; // 输出: Trunc of -3.14 is -3

    double z = 3.5;
    double result_z = std::trunc(z);
    int int_result_z = static_cast<int>(result_z); // 将结果转换为整数类型
    std::cout << "Trunc of " << z << " is " << result_z << " (as int: " << int_result_z << ")" << std::endl; // 输出: Trunc of 3.5 is 3
}

int main() {
    std::cout << "=========== Ceil Example ============" << std::endl;
    ceil_example();
    std::cout << "=========== My Ceil Example ============" << std::endl;
    my_ceil_example();
    std::cout << "=========== Floor Example ============" << std::endl;
    floor_example();
    std::cout << "=========== Round Example ============" << std::endl;
    round_example();
    std::cout << "=========== Trunc Example ============" << std::endl;
    trunc_example();

    return 0;
}