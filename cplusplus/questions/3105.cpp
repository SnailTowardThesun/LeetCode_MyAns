// @题目描述:
// 给你一个整数数组 nums，返回 nums 中最长「严格递增」或「严格递减」子数组的长度。
// 子数组是数组中的一个连续元素序列。注意严格单调不允许相等：相邻元素相等时
// 既不算递增也不算递减。
//
// @示例:
// 输入：nums = [1,4,3,3,2]
// 输出：2
// 解释：严格递增子数组 [1,4]、严格递减子数组 [4,3] 与 [3,2] 长度均为 2；
// [3,3] 因相等不算单调，故答案为 2。
// 输入：nums = [3,3,3,3]
// 输出：1（任何相邻元素都相等，单个元素即最长单调子数组）
// 输入：nums = [3,2,1]
// 输出：3（整个数组严格递减）
//
// @解题思路:
// 一次遍历 + 游程计数（run-length）：
// 1. 同时维护两个计数器：large 为以当前元素结尾的最长严格递增游程长度，
//    small 为最长严格递减游程长度，ret 取全局最大；
// 2. nums[i] > nums[i-1] 时 large++，否则（含相等）large 重置为 1；
//    small 对称处理 nums[i] < nums[i-1] 的情形；
// 3. 相等元素同时打断两条游程——这是「严格」二字的唯一坑点；
// 4. 初始值均为 1（单个元素自成单调子数组），n == 1 时直接返回 1。
//
// 复杂度分析：
// - 时间复杂度：O(n)，单次遍历
// - 空间复杂度：O(1)，三个计数器

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int ret = 1, large = 1, small = 1;
        for (int i = 1; i < nums.size(); i++) {
            // 严格递增游程：相等也算打断
            if (nums[i] > nums[i - 1]) {
                large++;
                ret = max(ret, large);
            } else {
                large = 1;
            }

            // 严格递减游程：对称处理
            if (nums[i] < nums[i - 1]) {
                small++;
                ret = max(ret, small);
            } else {
                small = 1;
            }
        }

        return ret;
    }
};
}  // namespace

TEST(Daily, 3105) {
    Solution s;

    // 官方示例 1：相等对打断两条游程，最长为 2
    vector<int> nums1{1, 4, 3, 3, 2};
    EXPECT_EQ(s.longestMonotonicSubarray(nums1), 2);

    // 官方示例 2：全部相等，单个元素即最长
    vector<int> nums2{3, 3, 3, 3};
    EXPECT_EQ(s.longestMonotonicSubarray(nums2), 1);

    // 官方示例 3：整个数组严格递减
    vector<int> nums3{3, 2, 1};
    EXPECT_EQ(s.longestMonotonicSubarray(nums3), 3);

    // 最小规模：单元素
    vector<int> nums4{5};
    EXPECT_EQ(s.longestMonotonicSubarray(nums4), 1);

    // 整体严格递增
    vector<int> nums5{1, 2, 3, 4, 5};
    EXPECT_EQ(s.longestMonotonicSubarray(nums5), 5);

    // 山峰形：先增后减，两侧各取最长
    vector<int> nums6{1, 3, 5, 4, 2};
    EXPECT_EQ(s.longestMonotonicSubarray(nums6), 3);

    // 混合形态：[3,4,5] 增 3 长与 [2,1] 减 2 长，答案 3
    vector<int> nums7{1, 2, 3, 2, 2, 1};
    EXPECT_EQ(s.longestMonotonicSubarray(nums7), 3);
}
