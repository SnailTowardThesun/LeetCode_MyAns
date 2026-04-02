//
// Created by 韩堃 on 2026/4/2.
//

/**
 * @file 3418.cpp
 * @brief LeetCode 3418. 机器人可以获得的最大金币数
 *
 * @题目描述
 * 给你一个 m x n 的网格 grid，每个格子包含一个整数（可能为负数），表示该位置的金币值。
 * 一个机器人从左上角 (0,0) 出发，只能向右或向下移动，到达右下角 (m-1,n-1)。
 * 机器人最多可以使用 2 次"转换"机会，将负数金币变为 0（即不扣分）。
 *
 * 返回机器人可以获得的最大金币数。
 *
 * @示例
 * 示例 1：
 * 输入: grid = [[0,1,-1],[1,-2,3],[2,-3,4]]
 * 输出: 8
 * 解释: 路径 (0,0)->(0,1)->(0,2)->(1,2)->(2,2)
 *       使用 1 次转换将 -1 变为 0
 *       金币总和为 0+1+0+3+4 = 8
 *
 * @解题思路
 * 1. 问题分析：
 *    - 这是一个带约束的路径最优化问题
 *    - 约束1：只能向右或向下移动
 *    - 约束2：最多使用 2 次转换机会
 *    - 目标：最大化获得的金币数
 *
 * 2. 动态规划设计：
 *    - 状态定义：dp[i][j][k] 表示到达位置 (i,j)，使用了 k 次转换机会的最大金币数
 *    - k 的取值范围：0, 1, 2（共 3 种状态）
 *    - 初始化：dp[0][0][0] = grid[0][0], dp[0][0][1] = 0（使用转换）
 *
 * 3. 状态转移：
 *    - 不转换：dp[i][j][k] = max(dp[i-1][j][k], dp[i][j-1][k]) + grid[i][j]
 *    - 转换（k > 0）：dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-1], dp[i][j-1][k-1])
 *      （转换时当前金币变为 0，所以只加 0）
 *
 * 4. 边界处理：
 *    - 使用 INT_MIN 初始化不可达状态
 *    - 状态转移时检查前驱状态是否可达
 *    - 防止整数溢出
 *
 * 5. 复杂度分析：
 *    - 时间复杂度: O(m * n * 3)，需要遍历网格的每个位置的 3 种状态
 *    - 空间复杂度: O(m * n * 3)，需要存储三维 DP 数组
 */

#include <gtest/gtest.h>

#include <vector>
using namespace std;

class Solution {
   public:
    int maximumAmount(vector<vector<int>>& coins) {
        auto n = coins.size();
        auto m = coins[0].size();
        std::vector<std::vector<std::vector<int>>> container(
            n, std::vector<std::vector<int>>(m, std::vector<int>(3, INT_MIN)));

        container[0][0][0] = coins[0][0];
        container[0][0][1] = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // no change
                for (int k = 0; k < 3; k++) {
                    if (i > 0 && container[i - 1][j][k] != INT_MIN) {
                        container[i][j][k] = max(container[i][j][k], container[i - 1][j][k] + coins[i][j]);
                    }

                    if (j > 0 && container[i][j - 1][k] != INT_MIN) {
                        container[i][j][k] = max(container[i][j][k], container[i][j - 1][k] + coins[i][j]);
                    }
                }

                // change
                for (int k = 1; k < 3; k++) {
                    if (i > 0 && container[i - 1][j][k - 1] != INT_MIN) {
                        container[i][j][k] = max(container[i][j][k], container[i - 1][j][k - 1]);
                    }

                    if (j > 0 && container[i][j - 1][k - 1] != INT_MIN) {
                        container[i][j][k] = max(container[i][j][k], container[i][j - 1][k - 1]);
                    }
                }
            }
        }

        int ret = INT_MIN;
        for (int i = 0; i < 3; i++) {
            ret = max(ret, container[n - 1][m - 1][i]);
        }

        return ret;
    }
};

TEST(Daily, 3418) {
    Solution s;

    auto coins = vector<vector<int>>{{0, 1, -1}, {1, -2, 3}, {2, -3, 4}};
    auto ret = s.maximumAmount(coins);
    EXPECT_EQ(ret, 8);
}
