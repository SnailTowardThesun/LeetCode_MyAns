//
// Created by hankun on 2026/10/1.
//

/**
 * @file top150_128.cpp
 * @brief LeetCode 128. 最长连续序列
 *
 * @题目描述
 * 给定一个未排序的整数数组 nums，找出数字连续的最长序列
 * （不要求序列元素在原数组中连续）的长度。
 * 请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [100,4,200,1,3,2]
 * 输出：4
 * 解释：最长数字连续序列是 [1, 2, 3, 4]，长度为 4。
 *
 * 示例 2：
 * 输入：nums = [0,3,7,2,5,8,4,6,0,1]
 * 输出：9
 *
 * @解题思路
 * 1. 哈希集合 + 只从起点延伸：
 *    - 全部数字放入 unordered_set，自动去重
 *    - 遍历集合中每个数 it：若 it - 1 也在集合中，
 *      说明 it 不是某段连续序列的起点，直接跳过
 *    - 若是起点，从 it 开始不断 +1 查找后继，段长为 next - it
 *    - 取所有段长的最大值；每个数字最多被延伸访问一次，总体 O(n)
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n)，每个数字最多被访问常数次
 *    - 空间复杂度: O(n)，哈希集合
 */

#include <gtest/gtest.h>

#include <unordered_set>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> container{nums.begin(), nums.end()};
        int ret = 1;
        for (auto it : container) {
            if (container.find(it - 1) != container.end()) {
                continue;
            }
            int next = it + 1;
            while (container.find(next) != container.end()) {
                next = next + 1;
            }

            ret = max(ret, next - it);
        }

        return ret;
    }
};
}  // namespace

TEST(top150, 128) {
    Solution s;
    vector<int> nums{100, 4, 200, 1, 3, 2};
    auto ret = s.longestConsecutive(nums);
    EXPECT_EQ(ret, 4);
}
