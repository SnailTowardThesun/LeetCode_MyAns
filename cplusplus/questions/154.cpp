//
// Created by hankun on 5/16/26.
//

/**
 * @file 154.cpp
 * @brief LeetCode 154. Find Minimum in Rotated Sorted Array II（寻找旋转排序数组中的最小值 II）
 *
 * @题目描述
 * 已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次旋转后，得到旋转后的数组 nums。
 * 数组中可能包含重复元素。
 * 请你找出并返回数组中的最小元素。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [1,3,5]
 * 输出：1
 *
 * 示例 2：
 * 输入：nums = [2,2,2,0,1]
 * 输出：0
 *
 * @解题思路
 * 使用二分查找来解决这个问题，时间复杂度平均为 O(log n)，最坏情况为 O(n)：
 *
 * 1. 二分查找思路：
 *    - 比较 nums[mid] 和 nums[right]
 *    - 如果 nums[mid] < nums[right]，说明右半部分是有序的，最小值在左半部分（包括 mid）
 *    - 如果 nums[mid] > nums[right]，说明左半部分是有序的，最小值在右半部分（不包括 mid）
 *    - 如果 nums[mid] == nums[right]，无法确定最小值位置，需要缩小搜索范围（right--）
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: 平均 O(log n)，最坏 O(n)（当所有元素都相同时）
 *    - 空间复杂度: O(1)，只需要常数级别额外空间
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int> &nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == nums[right]) {
                right--;
            } else if (nums[mid] < nums[right]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return nums[left];
    }
};

TEST(Daily, 154) {
    Solution s;

    // 测试用例 1
    auto eg1 = vector<int>{2, 2, 2, 0, 1};
    EXPECT_EQ(s.findMin(eg1), 0);

    // 测试用例 2
    auto eg2 = vector<int>{1, 3, 5};
    EXPECT_EQ(s.findMin(eg2), 1);

    // 测试用例 3
    auto eg3 = vector<int>{3, 3, 1, 3};
    EXPECT_EQ(s.findMin(eg3), 1);

    // 测试用例 4
    auto eg4 = vector<int>{1, 1, 1, 1};
    EXPECT_EQ(s.findMin(eg4), 1);
}
