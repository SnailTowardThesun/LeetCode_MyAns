//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 137.cpp
 * @brief LeetCode 137. 只出现一次的数字 II
 *
 * @题目描述
 * 给定一个非空整数数组，除了某个元素只出现一次外，其余每个元素均出现三次。找出那个只出现了一次的元素。
 * 你的算法应该满足线性时间复杂度和常数空间复杂度。
 *
 * @示例
 * 示例 1：
 * 输入：[2,2,2,3]
 * 输出：3
 *
 * 示例 2：
 * 输入：[0,1,0,1,0,1,99]
 * 输出：99
 *
 * @解题思路
 * 1. 位运算法：
 *    - 统计每一位上 1 出现的次数
 *    - 如果出现次数不是 3 的倍数，说明目标数字在该位上有 1
 *
 * 2. 算法步骤：
 *    - 创建一个长度为 32 的数组 x，用于统计每一位上 1 出现的次数
 *    - 遍历数组中的每个数字，统计每一位上 1 出现的次数
 *    - 将次数对 3 取模，得到目标数字的每一位
 *    - 组合所有位得到目标数字
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(1)
 */

#include <gtest/gtest.h>

using namespace std;

TEST(Daily, 137) {
    class Solution {
    public:
        int singleNumber(int A[], int n) {
            int x[32] = {0};
            for (int i = 0; i < n; i++)
                for (int j = 0; j < 32; j++) {
                    x[j] += (A[i] >> j) & 1;
                    x[j] %= 3;
                }
            int res = 0;
            for (int i = 0; i < 32; i++)
                res += (x[i] << i);
            return res;
        }
    };

    Solution s;
    
    // 测试用例 1
    int A1[] = {2, 2, 2, 3};
    EXPECT_EQ(s.singleNumber(A1, 4), 3);
    
    // 测试用例 2
    int A2[] = {0, 1, 0, 1, 0, 1, 99};
    EXPECT_EQ(s.singleNumber(A2, 7), 99);
    
    // 测试用例 3
    int A3[] = {1, 1, 1, 2};
    EXPECT_EQ(s.singleNumber(A3, 4), 2);
}
