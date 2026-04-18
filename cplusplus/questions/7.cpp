//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 7.cpp
 * @brief LeetCode 7. 整数反转
 *
 * @题目描述
 * 给你一个 32 位的有符号整数 x，返回将 x 中的数字反转后的结果。
 * 如果反转后整数超过 32 位的有符号整数的范围 [−2^31, 2^31 − 1]，就返回 0。
 *
 * @示例
 * 示例 1：
 * 输入：x = 123
 * 输出：321
 *
 * 示例 2：
 * 输入：x = -123
 * 输出：-321
 *
 * 示例 3：
 * 输入：x = 120
 * 输出：21
 *
 * @解题思路
 * 1. 数字反转法：
 *    - 不断取模 10 得到最后一位数字
 *    - 然后除以 10 去掉最后一位
 *    - 逐步构建反转后的数字
 *
 * 2. 算法步骤：
 *    - 处理负数情况
 *    - 循环取模得到每一位数字
 *    - 构建反转后的数字
 *    - 检查是否溢出
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(log |x|)
 *    - 空间复杂度: O(1)
 */

#include <gtest/gtest.h>
#include <climits>

using namespace std;

TEST(Daily, 7) {
    class Solution {
    public:
        int reverse(int x) {
            long num = abs((long)x);
            long new_num = 0;
            while (num) {
                new_num = new_num * 10 + num % 10;
                num /= 10;
            }
            if (new_num > INT_MAX) return 0;
            return (x < 0 ? 0 - new_num : new_num);
        }
    };

    Solution s;
    
    // 测试用例 1
    EXPECT_EQ(s.reverse(123), 321);
    
    // 测试用例 2
    EXPECT_EQ(s.reverse(-123), -321);
    
    // 测试用例 3
    EXPECT_EQ(s.reverse(120), 21);
    
    // 测试用例 4
    EXPECT_EQ(s.reverse(0), 0);
    
    // 测试用例 5
    EXPECT_EQ(s.reverse(-2147483648), 0);
}
