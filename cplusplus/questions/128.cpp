//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 128.cpp
 * @brief LeetCode 128. 最长连续序列
 *
 * @题目描述
 * 给定一个未排序的整数数组 nums，找出数字连续的最长序列（不重复）。
 * 要求算法的时间复杂度为 O(n)。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [100, 4, 200, 1, 3, 2]
 * 输出：4
 * 解释：最长连续序列是 [1, 2, 3, 4]，长度为 4
 *
 * 示例 2：
 * 输入：nums = [0, 3, 7, 2, 1]
 * 输出：3
 *
 * 示例 3：
 * 输入：nums = [0]
 * 输出：1
 *
 * @解题思路
 * 1. 哈希表法：
 *    - 使用哈希表存储数组中的每个数字
 *    - 遍历数组，对于每个数字，向前向后扩展查找连续序列
 *
 * 2. 算法步骤：
 *    - 将所有数字存入哈希表
 *    - 遍历数组中的每个数字
 *    - 如果该数字是序列的起点（num-1 不在哈希表中），则向后扩展查找
 *    - 更新最长序列长度
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)，每个数字最多被访问两次
 *    - 空间复杂度: O(n)，用于存储哈希表
 */

#include <gtest/gtest.h>
#include <vector>
#include <map>

using namespace std;

TEST(Daily, 128) {
    class Solution {
    public:
        map<int, int> mp;
        int longestConsecutiveSequence(vector<int> &nums) {
            for (int i = 0; i < nums.size(); i++)
                mp[nums[i]] = 1;

            int result = 0;
            for (int i = 0; i < nums.size(); i++) {
                int sum = 1;
                if (mp.count(nums[i]) && mp[nums[i]]) {
                    mp[nums[i]] = 0;
                    int left = nums[i] - 1;
                    while (mp.count(left) && mp[left]) {
                        mp[left--] = 0;
                        sum++;
                    }
                    int right = nums[i] + 1;
                    while (mp.count(right) && mp[right]) {
                        mp[right++] = 0;
                        sum++;
                    }
                }
                if (result < sum) result = sum;
            }
            return result;
        }
    };

    Solution s;
    
    // 测试用例 1
    vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    EXPECT_EQ(s.longestConsecutiveSequence(nums1), 4);
    
    // 测试用例 2
    vector<int> nums2 = {0, 3, 7, 2, 1};
    EXPECT_EQ(s.longestConsecutiveSequence(nums2), 4);
    
    // 测试用例 3
    vector<int> nums3 = {0};
    EXPECT_EQ(s.longestConsecutiveSequence(nums3), 1);
    
    // 测试用例 4
    vector<int> nums4 = {1, 2, 3, 4, 5};
    EXPECT_EQ(s.longestConsecutiveSequence(nums4), 5);
}
