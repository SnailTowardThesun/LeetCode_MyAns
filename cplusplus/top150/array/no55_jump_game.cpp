/**
 * @file no55_jump_game.cpp
 * @brief LeetCode 55. 跳跃游戏
 *
 * @题目描述
 * 给定一个非负整数数组 nums，你最初位于数组的第一个下标。数组中的每个元素代表你在
 * 该位置可以跳跃的最大长度。判断你是否能够到达最后一个下标。
 *
 * @示例
 * 示例 1：
 * 输入: nums = [2,3,1,1,4]
 * 输出: true
 * 解释: 可以先跳 1 步，从下标 0 到达下标 1，然后再从下标 1 跳 3 步到达最后一个下标。
 *
 * 示例 2：
 * 输入: nums = [3,2,1,0,4]
 * 输出: false
 * 解释: 无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0，
 *      所以永远不可能到达最后一个下标。
 *
 * @解题思路
 * 1. 贪心法（维护最远可达位置）：
 *    - 维护一个变量 right_most 表示当前能到达的最远位置
 *    - 遍历数组，对于每个位置 i：
 *      - 如果 i > right_most，说明当前位置不可达，返回 false
 *      - 更新 right_most = max(right_most, i + nums[i])
 *      - 如果 right_most >= n-1，说明可以到达终点，返回 true
 *
 * 2. 动态规划法：
 *    - dp[i] 表示能否到达位置 i
 *    - dp[i] = true 如果存在 j < i 使得 dp[j] = true 且 j + nums[j] >= i
 *    - 时间复杂度 O(n^2)，空间复杂度 O(n)
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，只需要遍历数组一次
 * - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

TEST(TOP150, No55_CanJump) {
    class Solution {
    public:
        bool can_jump(vector<int>& nums) {
            auto right_most = 0;
            for (auto i = 0; i < nums.size(); i++) {
                if (i <= right_most) {
                    right_most = std::max(right_most, i + nums[i]);
                    if (right_most >= nums.size() - 1) {
                        return true;
                    }
                }
            }

            return false;
        }
    };

    Solution solution;
    vector<int> nums{2, 3, 1, 1, 4};
    auto ret = solution.can_jump(nums);
    EXPECT_EQ(ret, true);
}
