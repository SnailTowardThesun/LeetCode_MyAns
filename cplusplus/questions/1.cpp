//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 1.cpp
 * @brief LeetCode 1. 两数之和
 *
 * @题目描述
 * 给定一个整数数组 nums 和一个整数目标值 target，
 * 请你在该数组中找出和为目标值 target 的那两个整数，并返回它们的数组下标。
 *
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
 * 你可以按任意顺序返回答案。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [2,7,11,15], target = 9
 * 输出：[0,1]
 * 解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
 *
 * 示例 2：
 * 输入：nums = [3,2,4], target = 6
 * 输出：[1,2]
 *
 * 示例 3：
 * 输入：nums = [3,3], target = 6
 * 输出：[0,1]
 *
 * @解题思路
 * 1. 哈希表法：
 *    - 使用哈希表来存储已经遍历过的元素及其下标
 *    - 对于当前元素 nums[i]，计算需要的目标值 complement = target - nums[i]
 *    - 检查 complement 是否在哈希表中，如果存在，返回当前下标和哈希表中存储的下标
 *    - 如果不存在，将当前元素及其下标存入哈希表
 *
 * 2. 算法步骤：
 *    - 初始化一个哈希表
 *    - 遍历数组中的每个元素：
 *      a. 计算 complement = target - nums[i]
 *      b. 检查 complement 是否在哈希表中
 *      c. 如果在，返回 [哈希表中 complement 的下标, i]
 *      d. 如果不在，将 nums[i] 及其下标 i 存入哈希表
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)，其中 n 是数组的长度
 *    - 空间复杂度: O(n)，用于存储哈希表
 */

#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>

using namespace std;

TEST(Daily, 1) {
    class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            unordered_map<int, int> hash;
            for (int i = 0; i < nums.size(); ++i) {
                int complement = target - nums[i];
                if (hash.find(complement) != hash.end()) {
                    return {hash[complement], i};
                }
                hash[nums[i]] = i;
            }
            return {};
        }
    };

    Solution s;
    
    // 测试用例 1
    vector<int> nums1 = {2, 7, 11, 15};
    EXPECT_EQ(s.twoSum(nums1, 9), vector<int>({0, 1}));
    
    // 测试用例 2
    vector<int> nums2 = {3, 2, 4};
    EXPECT_EQ(s.twoSum(nums2, 6), vector<int>({1, 2}));
    
    // 测试用例 3
    vector<int> nums3 = {3, 3};
    EXPECT_EQ(s.twoSum(nums3, 6), vector<int>({0, 1}));
    
    // 测试用例 4
    vector<int> nums4 = {1, 2, 3, 4, 5};
    EXPECT_EQ(s.twoSum(nums4, 9), vector<int>({3, 4}));
}
