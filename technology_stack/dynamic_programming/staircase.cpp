#include <iostream>
#include <vector>

/**
 * 爬楼梯：
 * 1. 一次可以爬 1 级或 2 级楼梯，问爬到 n 级楼梯有多少种不同的方法。
 * 2. 这是一个经典的动态规划问题，可以使用递归、记忆化搜索或动态规划表来解决。
 * 3. 递归解法：f(n) = f(n-1) + f(n-2)，其中 f(1) = 1, f(2) = 2。
 * 4. 记忆化搜索：在递归的基础上使用一个数组来存储已经计算过的结果，避免重复计算。
 * 5. 动态规划表：从底向上计算，使用一个数组 dp 来存储每一级楼梯的解，最终 dp[n] 就是答案。
 */

/**
 * 动态规划的常用术语。
 * 1. 将数组dp称为「𝑑𝑝表」，𝑑𝑝[𝑖]表示状态𝑖对应子问题的解。
 * 2. 将最小子问题对应的状态（第1阶和第2阶楼梯）称为「初始状态」。
 * 3. 将递推公式𝑑𝑝[𝑖]=𝑑𝑝[𝑖−1]+𝑑𝑝[𝑖−2]称为「状态转移方程」。
 */

int climbStairsDP(int n) {
    // 边界条件
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    // 创建 dp 数组，dp[i] 表示爬到 i 级楼梯的方法数
    std::vector<int> dp(n + 1);

    // 初始状态
    dp[1] = 1;
    dp[2] = 2;

    // 状态转移：从较小问题逐步求解较大问题
    for (int i = 3; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int main() {
    int n = 5; // 爬到 5 级楼梯
    std::cout << "Number of ways to climb " << n << " stairs: " << climbStairsDP(n) << std::endl;
    return 0;
}