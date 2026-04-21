// 136. Single Number
// 题目：https://leetcode.com/problems/single-number/
// 解题思路：
// 1. 使用异或运算的特性：相同数字异或为0，任何数字与0异或等于它本身
// 2. 异或运算满足交换律和结合律
// 3. 将数组所有元素进行异或，最终结果就是只出现一次的数字
// 4. 时间复杂度：O(n)，空间复杂度：O(1)
// 异或运算法则：
//   - a ^ a = 0
//   - a ^ 0 = a
//   - a ^ b ^ a = (a ^ a) ^ b = 0 ^ b = b

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
