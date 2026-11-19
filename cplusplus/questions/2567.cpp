// @题目描述:
// 给你一个整数数组 nums。低分为任意两个不同下标元素之差的绝对值的最小值，
// 高分为其中的最大值，数组分数为低分与高分之和。
// 将两个位置的元素改为任意整数，返回修改后能得到的最小分数。
// 数据范围：3 <= nums.length <= 10^5，1 <= nums[i] <= 10^9。
//
// @示例:
// 输入：nums = [1,4,3]
// 输出：0（把 1 和 4 改成 3，高分和低分均为 0）
// 输入：nums = [1,4,7,8,5]
// 输出：3（把 1 和 4 改成 6，低分 0，高分 8-5 = 3）
//
// @解题思路:
// 排序 + 三种删法取最小：
// 1. 固定要改的两个位置，分数至少是保留元素的极差：高分至少为此极差，低分非负。
// 2. 把两个位置都改成保留值域内的同一个数，低分变为 0，高分恰为保留元素的极差。
// 3. 因此只需找最短的保留值域。排序后，任取 n-2 个保留元素，其覆盖范围至少
//    包含一个长度为 n-2 的连续窗口。三个候选窗口分别对应：
//    - 删最大的两个：极差 nums[n-3] - nums[0]
//    - 删最大和最小：极差 nums[n-2] - nums[1]
//    - 删最小的两个：极差 nums[n-1] - nums[2]
//
// 复杂度分析：
// - 时间复杂度：O(n log n)，排序主导
// - 额外空间复杂度：常见 std::sort 实现使用 O(log n) 栈空间，其余计算为 O(1)

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int minimizeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        // 三种删法：删两个最大 / 删一大一最小 / 删两个最小
        return min(nums[n - 3] - nums[0], min(nums[n - 2] - nums[1], nums[n - 1] - nums[2]));
    }
};
}  // namespace

TEST(Daily, 2567) {
    Solution s;

    // 官方示例
    vector<int> nums1{1, 4, 3};
    EXPECT_EQ(s.minimizeSum(nums1), 0);
    vector<int> nums2{1, 4, 7, 8, 5};
    EXPECT_EQ(s.minimizeSum(nums2), 3);

    // 有重复值的全相等数组
    vector<int> nums3{1, 1, 1, 1};
    EXPECT_EQ(s.minimizeSum(nums3), 0);

    // 最小规模 n=3：必可全改成同一个值，答案恒 0
    vector<int> nums4{1, 2, 3};
    EXPECT_EQ(s.minimizeSum(nums4), 0);

    // n=4：只保留两个相邻值
    vector<int> nums5{1, 2, 3, 4};
    EXPECT_EQ(s.minimizeSum(nums5), 1);

    // 三种端点组合分别是唯一最优解
    vector<int> two_largest{1, 2, 3, 10, 20};
    EXPECT_EQ(s.minimizeSum(two_largest), 2);
    vector<int> both_ends{1, 10, 11, 12, 100};
    EXPECT_EQ(s.minimizeSum(both_ends), 2);
    vector<int> two_smallest{1, 10, 20, 21, 22};
    EXPECT_EQ(s.minimizeSum(two_smallest), 2);
}
