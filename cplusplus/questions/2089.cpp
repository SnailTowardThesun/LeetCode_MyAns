//
// Created by hankun on 2026/10/19.
//

// @题目描述:
// 2089. 找出数组排序后的目标下标（Find Target Indices After Sorting Array）— Easy
// 给你一个下标从 0 开始的整数数组 nums 以及一个目标元素 target。
// 「目标下标」是满足 nums[i] == target 的下标 i。
// 将 nums 按「非递减」顺序排序后，返回由 nums 中目标下标组成的数组。
// 如果不存在目标下标，返回一个空数组。返回的数组必须按递增顺序排列。
//
// @示例:
// 输入：nums = [1,2,5,2,3], target = 2
// 输出：[1,2]
// 解释：排序后 nums 变成 [1,2,2,3,5]，满足 nums[i] == 2 的下标是 1 和 2。
//
// @解题思路:
// 1. 先将数组按非递减顺序排序，目标值对应的下标即连续区间。
// 2. 从头线性扫描：遇到等于 target 的元素就记录其下标。
// 3. 一旦当前元素大于 target，后续不可能再出现目标值，提前退出循环。
// 优化：也可不排序，统计「小于 target 的个数 less」和「等于 target 的个数 equal」，
// 答案即为区间 [less, less + equal - 1] 内的所有下标，时间复杂度 O(n)。
//
// 复杂度分析：
// - 时间复杂度：O(n log n)，排序为主导；扫描部分为 O(n)。
// - 空间复杂度：O(log n)，排序所需的栈空间（不计返回数组）。

#include <gtest/gtest.h>

using namespace std;

namespace {
    class Solution {
    public:
        vector<int> targetIndices(vector<int> &nums, int target) {
            vector<int> ret;

            sort(nums.begin(), nums.end());
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] == target) {
                    ret.emplace_back(i);
                }

                if (nums[i] > target) {
                    break;
                }
            }

            return ret;
        }
    };
}

TEST(Daily, 2089) {
    Solution s;
    vector<int> nums{1, 2, 5, 2, 3};
    int target = 2;
    auto ret = s.targetIndices(nums, target);
    EXPECT_EQ(ret.size(), 2);
}
