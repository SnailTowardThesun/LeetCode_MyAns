//
// Created by hankun on 2026/10/18.
//

// LeetCode 34. 在排序数组中查找元素的第一个和最后一个位置
//
// @题目描述:
// 给定一个非递减数组 nums 和目标值 target，返回 target 在数组中的开始位置和结束位置。
// 若 target 不存在，返回 [-1, -1]，算法时间复杂度必须为 O(log n)。
//
// @示例:
// 输入：nums = [5,7,7,8,8,10], target = 8
// 输出：[3,4]
//
// @解题思路:
// 做两次方向不同的二分查找：
// 1. 找左边界：命中 target 时记录 mid，并继续在左侧找更小的下标；
// 2. 找右边界：命中 target 时记录 mid，并继续在右侧找更大的下标；
// 3. 若左边界不存在，target 必不存在，直接返回 [-1, -1]。
//
// 复杂度分析：
// - 时间复杂度：O(log n)，两次独立二分。
// - 空间复杂度：O(1)，只使用常数个变量。

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace {
class Solution {
   public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty()) {
            return {-1, -1};
        }

        int first = -1;
        int last = -1;
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        // 第一轮：即使命中，也继续向左收缩，最终 first 是最左下标。
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                first = mid;
            }

            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (first == -1) {
            return {-1, -1};
        }

        left = first;  // 右边界不可能在左边界之前，可以直接缩小搜索范围。
        right = static_cast<int>(nums.size()) - 1;

        // 第二轮：即使命中，也继续向右收缩，最终 last 是最右下标。
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                last = mid;
            }

            if (nums[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return {first, last};
    }
};
}  // namespace

TEST(Daily, 34) {
    Solution s;
    vector<int> nums{5, 7, 7, 8, 8, 10};
    EXPECT_EQ(s.searchRange(nums, 8), (vector<int>{3, 4}));
    EXPECT_EQ(s.searchRange(nums, 7), (vector<int>{1, 2}));
    EXPECT_EQ(s.searchRange(nums, 11), (vector<int>{-1, -1}));
    EXPECT_EQ(s.searchRange(nums, 1), (vector<int>{-1, -1}));

    vector<int> allSame{2, 2, 2, 2};
    EXPECT_EQ(s.searchRange(allSame, 2), (vector<int>{0, 3}));

    vector<int> empty;
    EXPECT_EQ(s.searchRange(empty, 3), (vector<int>{-1, -1}));
}
