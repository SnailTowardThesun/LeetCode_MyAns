//
// Created by hankun on 5/15/26.
//

/**
 * @file 153.cpp
 * @brief LeetCode 153. Find Minimum in Rotated Sorted Array（寻找旋转排序数组中的最小值）
 *
 * @题目描述
 * 已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次旋转后，得到旋转后的数组 nums。
 * 请你找出并返回数组中的最小元素。
 * 你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [3,4,5,1,2]
 * 输出：1
 * 解释：原数组为 [1,2,3,4,5]，旋转 3 次得到。最小元素是 1。
 *
 * 示例 2：
 * 输入：nums = [4,5,6,7,0,1,2]
 * 输出：0
 * 解释：原数组为 [0,1,2,4,5,6,7]，旋转 4 次得到。最小元素是 0。
 *
 * 示例 3：
 * 输入：nums = [11,13,15,17]
 * 输出：11
 * 解释：原数组为 [11,13,15,17]，旋转 4 次得到。最小元素是 11。
 *
 * @解题思路
 * 使用二分查找来解决这个问题，时间复杂度 O(log n)：
 *
 * 1. 二分查找思路：
 *    - 比较 nums[mid] 和 nums[right]
 *    - 如果 nums[mid] < nums[right]，说明右半部分是有序的，最小值在左半部分（包括 mid）
 *    - 如果 nums[mid] >= nums[right]，说明左半部分是有序的，最小值在右半部分（不包括 mid）
 *
 * 2. 算法步骤：
 *    - 初始化 left = 0, right = nums.size() - 1
 *    - 当 left < right 时：
 *      - 计算 mid = left + (right - left) / 2
 *      - 如果 nums[mid] < nums[right]，right = mid
 *      - 否则 left = mid + 1
 *    - 返回 nums[left]
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(log n)，每次将搜索区间减半
 *    - 空间复杂度: O(1)，只需要常数级别额外空间
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[right]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return nums[left];
    }
};

TEST(Daily, 153) {
    Solution s;

    // 测试用例 1
    auto nums1 = vector<int>{3, 4, 5, 1, 2};
    EXPECT_EQ(s.findMin(nums1), 1);

    // 测试用例 2
    auto nums2 = vector<int>{4, 5, 6, 7, 0, 1, 2};
    EXPECT_EQ(s.findMin(nums2), 0);

    // 测试用例 3
    auto nums3 = vector<int>{11, 13, 15, 17};
    EXPECT_EQ(s.findMin(nums3), 11);

    // 测试用例 4
    auto nums4 = vector<int>{5, 1, 2, 3, 4};
    EXPECT_EQ(s.findMin(nums4), 1);
}
