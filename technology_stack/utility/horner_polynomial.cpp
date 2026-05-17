#include <iostream>
#include <vector>

/**
 * Horner法计算多项式：
 * 给定多项式的系数和一个值x，使用Horner法计算多项式在x处的值。目的是减少乘法运算，提高计算效率。
 * 多项式形如：P(x) = a_n * x^n + a_(n-1) * x^(n-1) + ... + a_1 * x + a_0
 * 其中a_n, a_(n-1), ..., a_0是多项式的系数，x是变量。
 * Horner法的计算方式是：P(x) = (...((a_n * x + a_(n-1)) * x + a_(n-2)) * x + ... + a_1) * x + a_0
 */
double horner_polynomial(const std::vector<double>& coefficients, double x) {
	if (coefficients.empty()) {
		return 0.0;
	}

	double result = 0.0;
    for(size_t i = 0; i < coefficients.size(); ++i) {
        result = result * x + coefficients[i];
    }

	return result;
}

int main() {
	// 示例：计算多项式 P(x) = 2x^3 - 6x^2 + 2x - 1 在 x = 3 处的值
	const std::vector<double> coefficients = {2.0, -6.0, 2.0, -1.0};
	const double x = 3.0;
	const double result = horner_polynomial(coefficients, x);

	std::cout << "Polynomial: 2x^3 - 6x^2 + 2x - 1" << std::endl;
	std::cout << "x = " << x << std::endl;
	std::cout << "Result = " << result << std::endl;

	return 0;
}