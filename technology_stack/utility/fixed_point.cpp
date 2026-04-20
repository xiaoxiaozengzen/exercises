#include <iostream>

/**
 * 定点数缩放：
 * 1.放大：将小数乘以一个固定的缩放因子（通常是2的幂），然后转换为整数。
 * 2.运算：将原来整数和放大后的整数进行运算，得到一个新的整数结果。
 * 3.缩小：将结果除以相同的缩放因子，或者使用位移操作将结果缩小回小数。
 * 
 * 例如：需要计算YUV2RGB的场景中，会有R = Y + 1.402 * (V - 128)
 * 如果直接使用浮点数进行计算，可能会导致性能问题。通过定点数缩放，
 * 可以将1.402放大为一个整数（例如，1.402 * 1024 ≈ 1436），然后在计算时使用整数运算，最后再将结果缩小回小数。
 *
 * 这种方法在需要高性能和低内存占用的场景中非常有用，尤其是在嵌入式系统或图形处理等领域。
 */

void fixed_point_example() {
    // 定义一个整数
    int original_value = 100;
    // 定义一个小数值
    double factor_double = 0.3;
    // 定义缩放因子（例如，2的10次方）
    const int scale_factor = 1 << 10; // 1024
    int factor_int = static_cast<int>(factor_double * scale_factor); // 将小数放大并转换为整数
    // 进行定点数乘法
    int result_int = (original_value * factor_int);
    // 将结果转换回小数
    double result_double = static_cast<double>(result_int >> 10); // 将结果缩小回小数
    std::cout << "Original value: " << original_value << std::endl;
    std::cout << "Factor (double): " << factor_double << std::endl;
    std::cout << "Factor (int): " << factor_int << std::endl;
    std::cout << "Result (int): " << result_int << std::endl;
    std::cout << "Result (double): " << result_double << std::endl;
}

void fixed_point_round_example() {
    // 定义一个整数
    int original_value = 100;
    // 定义一个小数值
    double factor_double = 0.3;
    // 定义缩放因子（例如，2的20次方）
    const int scale_factor = 1 << 20; // 1048576
    int factor_int = static_cast<int>(factor_double * scale_factor); // 将小数放大并转换为整数
    
    /**
     * 定点数乘法并进行四舍五入：
     * 1.右移n位相当于除以2的n次方，左移n位相当于乘以2的n次方。
     * 2.直接右移会向下取整，如果需要四舍五入，可以在右移之前加上一个偏移值（通常是缩放因子的一半）。
     */
    int result_int = (original_value * factor_int + (1 << 19)) >> 20; // 加上半个缩放因子进行四舍五入
    std::cout << "Original value: " << original_value << std::endl;
    std::cout << "Factor (double): " << factor_double << std::endl;
    std::cout << "Factor (int): " << factor_int << std::endl;
    std::cout << "Result (int): " << result_int << std::endl;
}

int main() {
    std::cout << "===================== Fixed Point Example =====================" << std::endl;
    fixed_point_example();
    std::cout << "===================== Fixed Point Round Example =====================" << std::endl;
    fixed_point_round_example();
    return 0;
}