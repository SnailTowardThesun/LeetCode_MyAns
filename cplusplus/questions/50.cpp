//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 50.cpp
 * @brief LeetCode 50. Pow(x, n)
 *
 * @题目描述
 * 实现 pow(x, n)，即计算 x 的 n 次幂函数。
 *
 * @示例
 * 示例 1：
 * 输入：x = 2.00000, n = 10
 * 输出：1024.00000
 *
 * 示例 2：
 * 输入：x = 2.10000, n = 3
 * 输出：9.26100
 *
 * 示例 3：
 * 输入：x = 2.00000, n = -2
 * 输出：0.25000
 * 解释：2^-2 = 1/2^2 = 1/4 = 0.25
 *
 * @解题思路
 * 1. 快速幂法：
 *    - 使用递归实现快速幂
 *    - n 为负数时，转换为求倒数
 *    - 偶数幂：x^n = (x^2)^(n/2)
 *    - 奇数幂：x^n = x * (x^2)^(n/2)
 *
 * 2. 算法步骤：
 *    - 处理 n = 0 和 n = 1 的情况
 *    - 处理 n 为负数的情况
 *    - 递归计算快速幂
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(log n)
 *    - 空间复杂度: O(log n)，递归调用栈深度
 */

#include <gtest/gtest.h>

using namespace std;

TEST(Daily, 50) {
    class Solution {
    public:
        double pow(double x, int n) {
            if (n == 0) return 1;
            if (n == 1) return x;
            int exp = n < 0 ? -n : n;
            double result = exp % 2 == 0 ? pow(x * x, exp / 2) : pow(x * x, exp / 2) * x;
            return n < 0 ? 1 / result : result;
        }
    };

    Solution s;
    
    // 测试用例 1
    EXPECT_NEAR(s.pow(2.0, 10), 1024.0, 0.0001);
    
    // 测试用例 2
    EXPECT_NEAR(s.pow(2.1, 3), 9.261, 0.001);
    
    // 测试用例 3
    EXPECT_NEAR(s.pow(2.0, -2), 0.25, 0.0001);
    
    // 测试用例 4
    EXPECT_NEAR(s.pow(2.0, 0), 1.0, 0.0001);
}
