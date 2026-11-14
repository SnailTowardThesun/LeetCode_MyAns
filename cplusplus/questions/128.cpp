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
 * 输出：4（连续序列为 [0,1,2,3]）
 *
 * 示例 3：
 * 输入：nums = [0]
 * 输出：1
 *
 * @解题思路
 * 1. 哈希表法：
 *    - 使用哈希表存储数组中的每个数字
 *    - 只从没有前驱的序列起点向后扩展
 *
 * 2. 算法步骤：
 *    - 将所有数字存入哈希表
 *    - 遍历去重后的集合，避免重复起点引发重复扫描
 *    - 如果该数字是序列的起点（num-1 不在哈希表中），则向后扩展查找
 *    - 更新最长序列长度
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: 平均 O(n)，每段连续序列只扩展一次，哈希查询平均 O(1)
 *    - 空间复杂度: O(n)，用于存储哈希表
 */

#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> values(nums.begin(), nums.end());
        int result = 0;
        for (int x : values) {
            if (!values.contains(x - 1)) {
                int length = 1;
                while (values.contains(x + length)) ++length;
                result = max(result, length);
            }
        }
        return result;
    }
};
}  // namespace

TEST(Daily, 128) {
    Solution s;

    // 测试用例 1
    vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    EXPECT_EQ(s.longestConsecutive(nums1), 4);

    // 测试用例 2
    vector<int> nums2 = {0, 3, 7, 2, 1};
    EXPECT_EQ(s.longestConsecutive(nums2), 4);

    // 测试用例 3
    vector<int> nums3 = {0};
    EXPECT_EQ(s.longestConsecutive(nums3), 1);

    // 测试用例 4
    vector<int> nums4 = {1, 2, 3, 4, 5};
    EXPECT_EQ(s.longestConsecutive(nums4), 5);

    vector<int> empty;
    EXPECT_EQ(s.longestConsecutive(empty), 0);
    vector<int> duplicates(5000, 0);
    for (int i = 0; i < 5000; ++i) duplicates.push_back(i);
    EXPECT_EQ(s.longestConsecutive(duplicates), 5000);
    vector<int> negative = {-2, -1, 1, 2, 3};
    EXPECT_EQ(s.longestConsecutive(negative), 3);
}
