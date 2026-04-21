//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 136.cpp
 * @brief LeetCode 136. 只出现一次的数字
 *
 * @题目描述
 * 给定一个非空整数数组，除了某个元素只出现一次外，其余每个元素均出现两次。找出那个只出现了一次的元素。
 * 你的算法应该满足线性时间复杂度和常数空间复杂度。
 *
 * @示例
 * 示例 1：
 * 输入：[2,2,1]
 * 输出：1
 *
 * 示例 2：
 * 输入：[4,1,2,1,2]
 * 输出：4
 *
 * @解题思路
 * 1. 位运算法（异或）：
 *    - 异或运算满足交换律和结合律
 *    - 相同数字异或为 0
 *    - 任何数字与 0 异或都等于它本身
 *
 * 2. 算法步骤：
 *    - 初始化结果为数组第一个元素
 *    - 遍历数组，将结果与每个元素异或
 *    - 最终结果就是只出现一次的数字
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(1)
 */

#include <gtest/gtest.h>

using namespace std;

TEST(Daily, 136) {
    class Solution {
    public:
        int singleNumber(int A[], int n) {
            int result = 0;
            for (int i = 0; i < n; i++)
                result = result ^ A[i];
            return result;
        }
    };

    Solution s;

    // 测试用例 1
    int A1[] = {2, 2, 1};
    EXPECT_EQ(s.singleNumber(A1, 3), 1);

    // 测试用例 2
    int A2[] = {4, 1, 2, 1, 2};
    EXPECT_EQ(s.singleNumber(A2, 5), 4);

    // 测试用例 3
    int A3[] = {1};
    EXPECT_EQ(s.singleNumber(A3, 1), 1);

    // 测试用例 4
    int A4[] = {1, 2, 3, 2, 1};
    EXPECT_EQ(s.singleNumber(A4, 5), 3);
}
