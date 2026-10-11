// @题目描述:
// 给你一个下标从 1 开始、长度为 n 的整数数组 nums。
// 如果某个下标 i 满足 n % i == 0，则称 nums[i] 为特殊元素。
// 返回 nums 中所有特殊元素的平方和。
//
// @示例:
// 输入: nums = [1,2,3,4]
// 输出: 21
// 解释: n = 4，特殊下标为 1、2、4，
//       平方和 = 1*1 + 2*2 + 4*4 = 21
//
// @解题思路:
// 按题目定义直接遍历 1-indexed 下标 i（从 1 到 n）：
// 1. 若 n % i == 0，则 nums[i] 是特殊元素；
// 2. 累加 nums[i-1] * nums[i-1]（换算为 0-indexed 数组元素）；
// 3. 遍历结束后返回累加结果。
//
// 复杂度分析：
// - 时间复杂度：O(n)，只需遍历数组一次
// - 空间复杂度：O(1)，仅使用常数额外空间
//

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    int sumOfSquares(vector<int>& nums) {
        int n = nums.size();
        int ret = 0;
        for (int i = 1; i <= n; i++) {
            if (n % i == 0) {
                ret += nums[i-1] * nums[i-1];
            }
        }

        return ret;
    }
};

TEST(Daily, 2778) {
    Solution s;

    // n = 3，特殊下标为 1、3：1*1 + 3*3 = 10
    vector<int> nums1 = {1, 2, 3};
    EXPECT_EQ(s.sumOfSquares(nums1), 10);

    // 官方示例：n = 4，特殊下标为 1、2、4：1 + 4 + 16 = 21
    vector<int> nums2 = {1, 2, 3, 4};
    EXPECT_EQ(s.sumOfSquares(nums2), 21);

    // 官方示例：n = 6，特殊下标为 1、2、3、6：4 + 49 + 1 + 9 = 63
    vector<int> nums3 = {2, 7, 1, 19, 18, 3};
    EXPECT_EQ(s.sumOfSquares(nums3), 63);
}
