//
// 396. 旋转函数
// https://leetcode.cn/problems/rotate-function/
//
// 给定一个整数数组 nums，长度为 n，假设数组 nums 在 0 索引处的旋转函数为 F(0)，
// 在 1 索引处的旋转函数为 F(1)，...，在 n-1 索引处的旋转函数为 F(n-1)。
//
// 旋转函数的计算规则如下：
// F(k) = 0 * Bk[0] + 1 * Bk[1] + ... + (n-1) * Bk[n-1]
// 其中，Bk 是数组 nums 顺时针旋转 k 个位置后的数组。
//
// 请计算 F(0), F(1), ..., F(n-1) 中的最大值。
//
// 示例 1：
// 输入：nums = [4,3,2,6]
// 输出：26
// 解释：
// F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
// F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
// F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
// F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26
// 最大值是 F(3) = 26
//
// 解题思路（数学推导）：
// 1. 计算初始 F(0) 和总和 totalSum
// 2. 通过数学公式推导 F(k) 与 F(k-1) 的关系：
//    F(k) = F(k-1) + totalSum - n * nums[n-k]
// 3. 遍历计算所有 F(k)，记录最大值
//
// 时间复杂度：O(n)，空间复杂度：O(1)
//

#include <gtest/gtest.h>
using namespace std;

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int totalSum = 0;
        int helper = 0;
        for (int i = 0; i < nums.size(); i++) {
            totalSum += nums[i];
            helper += i * nums[i];
        }

        int ret = helper;
        for (int i = nums.size()-1; i >= 0; i--) {
            helper += totalSum - nums.size() * nums[i];
            ret = max(ret, helper);
        }

        return ret;
    }
};

TEST(Daily, 396) {
    Solution s;
    auto nums = vector<int>{4,3,2,6};
    auto ret = s.maxRotateFunction(nums);
    EXPECT_EQ(26, ret);
}