/**
 * @file no45_jump_game_ii.cpp
 * @brief LeetCode 45. 跳跃游戏 II
 *
 * @题目描述
 * 给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。
 * 每个元素 nums[i] 表示从索引 i 向前跳转的最大长度。换句话说，如果你在 nums[i] 处，
 * 你可以跳转到任意 nums[i + j] 处（其中 0 <= j <= nums[i]）。
 * 返回到达 nums[n - 1] 的最小跳跃次数。生成的测试用例可以到达 nums[n - 1]。
 *
 * @示例
 * 示例 1：
 * 输入: nums = [2,3,1,1,4]
 * 输出: 2
 * 解释: 跳到最后一个位置的最小跳跃数是 2。
 *      从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
 *
 * 示例 2：
 * 输入: nums = [2,3,0,1,4]
 * 输出: 2
 *
 * @解题思路
 * 1. 贪心法（维护当前边界和最大可达位置）：
 *    - 维护两个变量：
 *      - end：当前这一步能到达的最远边界
 *      - max_pos：从当前范围内能跳到的最远位置
 *    - 遍历数组（除了最后一个元素）：
 *      - 更新 max_pos = max(max_pos, i + nums[i])
 *      - 当 i == end 时，说明需要再跳一步，更新 end = max_pos，步数加 1
 *
 * 2. 动态规划法：
 *    - dp[i] 表示到达位置 i 的最小跳跃次数
 *    - dp[i] = min(dp[j] + 1) 对于所有能到达 i 的 j
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

TEST(TOP150, No45_JumpGameII) {
    class Solution {
    public:
        int jump(vector<int>& nums) {
            auto max_pos = 0;
            auto end = 0;
            auto ret = 0;

            for (auto i = 0; i < nums.size() - 1; i++) {
                if (max_pos >= i) {
                    max_pos = std::max(max_pos, i + nums[i]);
                    if (i == end) {
                        end = max_pos;
                        ret++;
                    }
                }
            }

            return ret;
        }
    };
    Solution solution;
    std::vector<int> nums{2, 3, 1, 1, 4};
    auto ret = solution.jump(nums);
    EXPECT_EQ(ret, 2);
}
