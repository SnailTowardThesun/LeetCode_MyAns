//
// Created by hankun on 2026/10/18.
//

// LeetCode 162. 寻找峰值
//
// @题目描述:
// 给定整数数组 nums，相邻元素互不相等，峰值是严格大于左右邻居的下标。
// 边界只需要大于相邻一侧邻居。返回任意一个峰值下标，要求 O(log n)。
//
// @示例:
// 输入：nums = [1,2,3,1]
// 输出：2
//
// @解题思路:
// 二分始终保持区间内存在峰值：
// - 若 nums[mid] < nums[mid + 1]，mid 右侧处于上升坡，右侧必有峰值；
// - 否则 mid 本身可能是峰值，或在左侧下降，左侧必有峰值；
// - 当 left == right 时，该下标就是峰值。
// SolutionOn 保留 O(n) 扫描最大值做法，作为理解题意的对照版本。
//
// 复杂度分析：
// - 时间复杂度：O(log n)。
// - 空间复杂度：O(1)。

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace {
class SolutionOn {
   public:
    int findPeakElement(vector<int>& nums) {
        int index = 0;
        int maxValue = nums[0];
        for (int i = 1; i < static_cast<int>(nums.size()); ++i) {
            if (nums[i] > maxValue) {
                maxValue = nums[i];
                index = i;
            }
        }
        return index;
    }
};

class Solution {
   public:
    int findPeakElement(vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[mid + 1]) {
                left = mid + 1;  // 上升方向必有峰值。
            } else {
                right = mid;  // mid 可能是峰值，不能丢掉。
            }
        }

        return left;
    }
};
}  // namespace

TEST(Daily, 162) {
    Solution s;
    vector<int> nums1{1, 2, 3, 1};
    EXPECT_EQ(s.findPeakElement(nums1), 2);

    vector<int> nums2{1, 2, 1, 3, 5, 6, 4};
    int peak = s.findPeakElement(nums2);
    EXPECT_TRUE(peak == 1 || peak == 5);

    vector<int> nums3{1};
    EXPECT_EQ(s.findPeakElement(nums3), 0);

    vector<int> nums4{1, 2};
    EXPECT_EQ(s.findPeakElement(nums4), 1);

    vector<int> nums5{2, 1};
    EXPECT_EQ(s.findPeakElement(nums5), 0);

    SolutionOn linear;
    EXPECT_EQ(linear.findPeakElement(nums1), 2);
}
