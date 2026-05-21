//
// Created by hankun on 5/22/26.
//

/**
 * @题目描述
 * 33. 搜索旋转排序数组
 * 整数数组 nums 按升序排列，数组中的值 互不相同 。
 * 给你一个整数数组 nums 和一个整数 target，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了旋转。
 * 给你 旋转后 的数组 nums 和整数 target，请你搜索 target 并返回其下标。
 * 如果 target 不存在于 nums 中，返回 -1 。
 * 你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
 *
 * @示例
 * 示例 1：
 * 输入: nums = [4,5,6,7,0,1,2], target = 0
 * 输出: 4
 *
 * 示例 2：
 * 输入: nums = [4,5,6,7,0,1,2], target = 3
 * 输出: -1
 *
 * 示例 3：
 * 输入: nums = [1], target = 0
 * 输出: -1
 *
 * @解题思路
 * 二分查找：
 * 1. 使用二分查找，但需要处理旋转的情况
 * 2. 每次取中点，判断哪一半是有序的
 * 3. 根据 target 与中点的关系以及哪一半有序来确定搜索范围
 * 4. 时间复杂度: O(log n)
 *
 * @复杂度分析
 * 时间复杂度: O(log n)
 * 空间复杂度: O(1)
 */

#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) {
            return -1;
        }

        auto left = 0;
        auto right = nums.size() - 1;
        while (left <= right) {
            auto mid = (left + right) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[0] <= nums[mid]) {
                if (nums[0] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[nums.size() - 1]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        return -1;
    }
};

#include <gtest/gtest.h>

TEST(Daily, 33) {
    Solution s;

    auto nums1 = vector<int>{4, 5, 6, 7, 0, 1, 2};
    EXPECT_EQ(s.search(nums1, 0), 4);
    EXPECT_EQ(s.search(nums1, 3), -1);

    auto nums2 = vector<int>{1};
    EXPECT_EQ(s.search(nums2, 0), -1);
    EXPECT_EQ(s.search(nums2, 1), 0);

    auto nums3 = vector<int>{5, 1, 2, 3, 4};
    EXPECT_EQ(s.search(nums3, 3), 3);
    EXPECT_EQ(s.search(nums3, 1), 1);
}
