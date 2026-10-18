//
// Created by hankun on 2026/10/18.
//

// LeetCode 33. 搜索旋转排序数组
//
// @题目描述:
// 升序数组在未知下标处旋转过（如 [4,5,6,7,0,1,2] 由 [0,1,2,4,5,6,7] 旋转得到），
// 给定 target，存在则返回其下标，否则返回 -1。
//
// @示例:
// 输入：nums = [4,5,6,7,0,1,2], target = 0
// 输出：4
//
// @解题思路:
// 二分后 [left, mid] 与 [mid, right] 至少有一半完全有序（nums[left] <= nums[mid]
//       则左半有序，否则右半有序）；再判断 target 是否落在有序半边的值域内，
//       在则收缩到该半边，不在则去另一半。
//
// 复杂度分析：
// - 时间复杂度：O(log n)。
// - 空间复杂度：O(1)。

#include <gtest/gtest.h>

using namespace std;

namespace {
class Solution {
   public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] == target) {
                return mid;
            }

            if (nums[left] <= nums[mid]) {
                // 左半 [left, mid] 有序：target 落在 (nums[left], nums[mid]) 内则去左半，否则去右半
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                // 右半 [mid, right] 有序：target 落在 (nums[mid], nums[right]) 内则去右半，否则去左半
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        return -1;  // 未找到
    }
};
}  // namespace

TEST(top150, 33) {
    Solution s;
    vector<int> nums{4, 5, 6, 7, 8, 1, 2, 3};
    int target = 8;
    auto ret = s.search(nums, target);
    EXPECT_EQ(ret, 4);
    EXPECT_EQ(s.search(nums, 100), -1);
}
