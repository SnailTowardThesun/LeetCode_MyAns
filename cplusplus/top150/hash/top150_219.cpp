//
// Created by hankun on 2026/10/1.
//

/**
 * @file top150_219.cpp
 * @brief LeetCode 219. 存在重复元素 II
 *
 * @题目描述
 * 给你一个整数数组 nums 和一个整数 k，
 * 判断数组中是否存在两个不同的索引 i 和 j，
 * 满足 nums[i] == nums[j] 且 abs(i - j) <= k。
 * 如果存在，返回 true；否则，返回 false。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [1,2,3,1], k = 3
 * 输出：true
 *
 * 示例 2：
 * 输入：nums = [1,0,1,1], k = 1
 * 输出：true
 *
 * 示例 3：
 * 输入：nums = [1,2,3,1,2,3], k = 2
 * 输出：false
 *
 * @解题思路
 * 1. 哈希表记录最近下标：
 *    - 用哈希表 container 记录每个值最后一次出现的下标
 *    - 遍历数组，若当前值已在表中，计算当前下标与记录下标的差值：
 *      a. 差值 <= k：找到满足条件的重复对，返回 true
 *      b. 差值 > k：更新该值的下标为当前下标（更近的坐标更可能满足后续比较）
 *    - 只需保留最近一次出现的下标：若旧下标与当前差值已超过 k，
 *      则旧下标与更后面的元素差距只会更大，可以安全丢弃
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n)，每个元素处理一次
 *    - 空间复杂度: O(n)，哈希表最多存 n 个不同的值
 */

#include <gtest/gtest.h>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> container;
        for (auto i = 0; i < nums.size(); i++) {
            if (container.find(nums[i]) != container.end()) {
                auto diff = abs(i - container[nums[i]]);
                if (diff <= k) {
                    return true;
                }
            }
            container[nums[i]] = i;
        }

        return false;
    }
};
}  // namespace

TEST(top150, 219) {
    Solution s;
    vector<int> nums{1, 2, 3, 1};
    auto k = 3;
    auto ret = s.containsNearbyDuplicate(nums, k);
    EXPECT_TRUE(ret);
}
