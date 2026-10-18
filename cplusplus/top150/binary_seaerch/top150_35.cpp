//
// Created by hankun on 2026/10/18.
//

// LeetCode 35. 搜索插入位置
//
// @题目描述:
// 给定一个排序数组 nums 和目标值 target，若 target 存在则返回下标；
// 若不存在，返回按顺序插入后的下标。算法必须 O(log n)。
//
// @示例:
// 输入：nums = [1,3,5,6], target = 2
// 输出：1
//
// @解题思路:
// 二分维护闭区间 [left, right]：
// - nums[mid] == target：mid 就是答案；
// - nums[mid] < target：插入位置只能在 mid 右侧；
// - nums[mid] > target：mid 可能就是插入位置，继续向左找。
// 循环结束时 left 指向第一个大于等于 target 的位置。
//
// 复杂度分析：
// - 时间复杂度：O(log n)。
// - 空间复杂度：O(1)。

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace {
class Solution {
   public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            }

            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return left;
    }
};
}  // namespace

TEST(Top150, 35) {
    Solution s;
    vector<int> nums{1, 3, 5, 6};
    EXPECT_EQ(s.searchInsert(nums, 5), 2);
    EXPECT_EQ(s.searchInsert(nums, 2), 1);
    EXPECT_EQ(s.searchInsert(nums, 7), 4);
    EXPECT_EQ(s.searchInsert(nums, 0), 0);
    EXPECT_EQ(s.searchInsert(nums, 1), 0);

    vector<int> empty;
    EXPECT_EQ(s.searchInsert(empty, 9), 0);
}
