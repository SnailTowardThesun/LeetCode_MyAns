//
// Created by hankun on 5/10/26.
//

/**
 * @file 2770.cpp
 * @brief LeetCode 2770. Maximum Number of Jumps to Reach the Last Index（达到末尾下标所需的最大跳跃次数）
 *
 * @题目描述
 * 给定一个 0-indexed 的整数数组 nums 和一个整数 target。
 * 你初始位置在下标 0。在一步操作中，你可以从下标 i 跳跃到任意下标 j（j > i），
 * 使得 -target <= nums[j] - nums[i] <= target。
 * 返回你到达下标 n - 1 所需的最大跳跃次数。如果无法到达下标 n - 1，返回 -1。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [1,3,6,4,1,2], target = 2
 * 输出：3
 * 解释：要想以最大跳跃次数到达最后一个下标，你可以按以下跳跃序列操作：
 * 从下标 0 跳到下标 1，需要 1 步。
 * 从下标 1 跳到下标 3，需要 2 步。
 * 从下标 3 跳到下标 5，需要 3 步。
 * 可以证明，3 是到达最后一个下标所需的最大跳跃次数。
 *
 * 示例 2：
 * 输入：nums = [1,3,6,4,1,2], target = 3
 * 输出：5
 *
 * 示例 3：
 * 输入：nums = [1,3,6,4,1,2], target = 0
 * 输出：-1
 *
 * @解题思路
 * 这道题可以使用动态规划（记忆化搜索）来解决。
 *
 * 1. 动态规划思路：
 *    - 定义 dp[i] 表示从下标 0 跳到下标 i 的最大跳跃次数
 *    - 对于每个位置 j，遍历所有 i < j，如果 |nums[j] - nums[i]| <= target，
 *      则 dp[j] = max(dp[j], dp[i] + 1)
 *    - 初始状态：dp[0] = 0（起点不需要跳跃）
 *
 * 2. 记忆化搜索实现：
 *    - 使用递归 + 记忆化的方式，从最后一个位置开始回溯
 *    - container[j] 存储从下标 0 跳到下标 j 的最大跳跃次数
 *    - 如果 container[j] 已经计算过，直接返回结果
 *    - 否则遍历所有 i < j，找到满足条件的最大跳跃次数
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n^2)，需要两层循环遍历所有位置对
 *    - 空间复杂度: O(n)，需要一个数组存储中间结果
 */

#include <gtest/gtest.h>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int dfs(vector<int> &nums, int j, int target, vector<int> &container) {
        if (j == 0) {
            return 0;
        }

        int& res = container[j];
        if (res) {
            return res;
        }

        res = INT_MIN;
        for (int i = 0; i < j; i++) {
            if (abs(nums[i] - nums[j]) <= target) {
                res = max(res, dfs(nums, i, target, container) + 1);
            }
        }

        return res;
    }

    int maximumJumps(vector<int> &nums, int target) {
        auto container = vector<int>(nums.size());

        auto ret = dfs(nums, nums.size() - 1, target, container);

        return ret < 0 ? -1 : ret;
    }
};

TEST(Daily, 2770) {
    Solution s;

    // 测试用例 1
    auto nums1 = vector<int>{1, 3, 6, 4, 1, 2};
    auto target1 = 2;
    auto ret1 = s.maximumJumps(nums1, target1);
    EXPECT_EQ(ret1, 3);

    // 测试用例 2
    auto nums2 = vector<int>{1, 3, 6, 4, 1, 2};
    auto target2 = 3;
    auto ret2 = s.maximumJumps(nums2, target2);
    EXPECT_EQ(ret2, 5);

    // 测试用例 3
    auto nums3 = vector<int>{1, 3, 6, 4, 1, 2};
    auto target3 = 0;
    auto ret3 = s.maximumJumps(nums3, target3);
    EXPECT_EQ(ret3, -1);
}
