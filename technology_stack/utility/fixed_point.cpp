#include <bits/stdint-uintn.h>
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

/**
 * 在进行数学运算(加减乘除)时：
 *  1.中间结果：编译器或者CPU会选用对应类型的寄存器保存中间结果
 *  2.溢出处理：如果中间结果超过了类型的范围，可能会发生溢出，导致结果不正确。
 *  3.性能优化：在某些情况下，编译器可能会对定点数运算进行优化，例如使用位移操作代替乘除法，以提高性能
 *
 * 整型提升：
 * 1.在表达式计算时，各种整形首先要提升为int类型，
 *   如果int类型不足以表示的话，就需要提升为unsigned int类型，然后再执行表达式的运算
 */
void multiply_example() {
    std::cout << "--------- uint8_t example ---------" << std::endl;
    uint8_t a = 200;
    uint8_t b = 200;

    // 溢出：200 * 200 = 40000(0x9C40)，但uint8_t只能存储0-255，所以结果会溢出
    uint8_t result = a * b;
    // 较小的类型(uint8_t、uint16_t)相乘的时候，C++会先提升到int类型进行计算
    uint16_t result_correct = a * b;
    // 稳妥的方式就是提升到更大的类型进行计算，避免溢出
    uint16_t result_safe = static_cast<uint16_t>(a) * static_cast<uint16_t>(b);
    std::cout << "result (uint8_t): " << static_cast<int>(result) << " (溢出)" << std::endl;
    std::cout << "result_correct (uint16_t): " << result_correct << " (正确结果)" << std::endl;
    std::cout << "result_safe (uint16_t): " << result_safe << " (安全结果)" << std::endl;

    std::cout << "--------- uint32_t example ---------" << std::endl;
    uint32_t c = 1<<30; // 1073741824
    uint32_t d = 1<<30; // 1073741824
    uint32_t result32 = c * d;
    // 对于uint32_t或者更大类型，其乘法运算会直接在该类型的寄存器中进行计算，如果结果超过了uint32_t的范围，就会发生溢出
    uint64_t result32_correct = c * d;
    // 正确结果应该是1073741824 * 1073741824 = 1152921504606846976 (0x10000000000000000)，但由于uint32_t的范围是0-4294967295，所以结果会溢出
    uint64_t result32_safe = static_cast<uint64_t>(c) * static_cast<uint64_t>(d);
    std::cout << "result (uint32_t): " << result32 << " (溢出)" << std::endl;
    std::cout << "result_correct (uint64_t): " << result32_correct << " (溢出)" << std::endl;
    std::cout << "result_safe (uint64_t): " << result32_safe << " (安全结果)" << std::endl;
}

int main() {
    std::cout << "===================== Fixed Point Example =====================" << std::endl;
    fixed_point_example();
    std::cout << "===================== Fixed Point Round Example =====================" << std::endl;
    fixed_point_round_example();
    std::cout << "===================== Multiply Example =====================" << std::endl;
    multiply_example();

    return 0;
}