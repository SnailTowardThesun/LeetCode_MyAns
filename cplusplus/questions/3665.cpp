//
// Created by 韩堃 on 2026/10/31.
//

/**
 * @file 3665.cpp
 * @brief LeetCode 3665. 统计镜子反射路径数目（Twisted Mirror Path Count）
 *
 * @题目描述
 * 给你一个 m x n 的二进制网格 grid，grid[i][j] == 0 表示空格子，1 表示一面镜子。
 * 机器人从 (0, 0) 出发走向 (m-1, n-1)，只能向右或向下移动。
 * 试图移入镜子格时会在进入前被反射：向右进入 -> 转向下、移动到镜子正下方；
 * 向下进入 -> 转向右、移动到镜子正右方。反射落点出界则该路径无效。
 * 若反射落点仍是镜子则立即再次反射（链式），方向规则同上：向右进入转向下、向下进入转向右。
 * 返回有效路径数量对 10^9 + 7 取模的结果。
 *
 * @示例
 * 示例 1：
 * 输入：grid = [[0,1,0],[0,0,1],[1,0,0]]
 * 输出：5
 *
 * 示例 2：
 * 输入：grid = [[0,0],[0,0]]
 * 输出：2
 *
 * 示例 3：
 * 输入：grid = [[0,1,1],[1,1,0]]
 * 输出：1
 *
 * @解题思路
 * 状态设计：dp[i][j][d] = 以方向 d 进入格子 (i,j) 的路径数
 * （d=0 向下进入、d=1 向右进入）。空格进入即静止；镜子上不存在静止，进入瞬间被换向。
 *
 * 1. 转移只看"来源格"：
 *    - 来源格为空：静止后可自由选方向，两分量全量流入下方格 / 右方格；
 *    - 来源格为镜：只放行被反弹的分量——
 *      上方格是镜时，dp[i][j][0] 取 dp[i-1][j][1]（向右进入被反弹向下）；
 *      左方格是镜时，dp[i][j][1] 取 dp[i][j-1][0]（向下进入被反弹向右）。
 * 2. 出界天然裁剪：反弹或移动的落点越界时对应 dp 项不存在，值自动丢弃，无需判定。
 * 3. 链式反射自动传播：反弹流入的下一格若仍是镜，按新进入方向再次换向，无需特判。
 * 4. 终点保证为空格，答案 = 两个方向进入终点之和。
 *
 * 复杂度分析：
 * - 时间复杂度: O(m*n)
 * - 空间复杂度: O(m*n)
 */

#include <gtest/gtest.h>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const int MOD = 1'000'000'007;
        // dp[i][j][d]：以方向 d 进入 (i,j) 的路径数（0=向下进入，1=向右进入）
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, {0, 0}));
        dp[0][0][1] = 1;  // 起点静止，种子放任一分量即可（流出时两分量求和）
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i > 0) {
                    // 来源格（上方）为空：全量向下流入；为镜：只放"向右进入被反弹向下"的 [1]
                    dp[i][j][0] = grid[i - 1][j] == 0 ? dp[i - 1][j][0] + dp[i - 1][j][1] : dp[i - 1][j][1];
                    dp[i][j][0] %= MOD;
                }
                if (j > 0) {
                    // 来源格（左方）为空：全量向右流入；为镜：只放"向下进入被反弹向右"的 [0]
                    dp[i][j][1] = grid[i][j - 1] == 0 ? dp[i][j - 1][0] + dp[i][j - 1][1] : dp[i][j - 1][0];
                    dp[i][j][1] %= MOD;
                }
            }
        }

        return (dp[m - 1][n - 1][0] + dp[m - 1][n - 1][1]) % MOD;
    }
};
}  // namespace

TEST(Daily, 3665) {
    Solution s;
    // 官方示例
    {
        vector<vector<int>> grid{{0, 1, 0}, {0, 0, 1}, {1, 0, 0}};
        EXPECT_EQ(s.uniquePaths(grid), 5);  // 示例 1：三种反射各有路径
    }
    {
        vector<vector<int>> grid{{0, 0}, {0, 0}};
        EXPECT_EQ(s.uniquePaths(grid), 2);  // 示例 2：无镜子退化为经典路径数
    }
    {
        vector<vector<int>> grid{{0, 1, 1}, {1, 1, 0}};
        EXPECT_EQ(s.uniquePaths(grid), 1);  // 示例 3：二连反射一有效一出界
    }
    // 边界：单行 / 单列，以及一维网格中镜子反射必然出界
    {
        vector<vector<int>> grid{{0, 0, 0}};
        EXPECT_EQ(s.uniquePaths(grid), 1);
    }
    {
        vector<vector<int>> grid{{0}, {0}, {0}};
        EXPECT_EQ(s.uniquePaths(grid), 1);
    }
    {
        vector<vector<int>> grid{{0, 1, 0, 0}};
        EXPECT_EQ(s.uniquePaths(grid), 0);  // 向右进镜弹向下方，无下方行
    }
    {
        vector<vector<int>> grid{{0}, {1}, {0}};
        EXPECT_EQ(s.uniquePaths(grid), 0);  // 向下进镜弹向右侧，无右侧列
    }
    // 对角双镜：起点的两个方向都恰好被弹进终点
    {
        vector<vector<int>> grid{{0, 1}, {1, 0}};
        EXPECT_EQ(s.uniquePaths(grid), 2);
    }
    // 无镜空网格：答案即 C(m+n-2, m-1)
    {
        vector<vector<int>> grid{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        EXPECT_EQ(s.uniquePaths(grid), 6);  // C(4,2)
    }
    // 链式反射（三连）：右进 (0,1) 镜 -> 弹到 (1,1) 仍是镜（向下进入）-> 弹到 (1,2) 仍是镜
    // （向右进入）-> 弹到正下方 (2,2) 空格
    {
        vector<vector<int>> grid{{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
        EXPECT_EQ(s.uniquePaths(grid), 3);
    }
    // 随机含镜网格（期望值经 DAG-DP 与全枚举 DFS 两套独立参考实现交叉验证）
    {
        vector<vector<int>> grid{{0, 1, 1, 0}, {1, 1, 0, 1}, {0, 0, 0, 0}, {1, 0, 1, 1}, {0, 1, 1, 0}};
        EXPECT_EQ(s.uniquePaths(grid), 3);
    }
    {
        vector<vector<int>> grid{{0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 1, 0}, {1, 0, 1, 0}};
        EXPECT_EQ(s.uniquePaths(grid), 19);
    }
    {
        vector<vector<int>> grid{{0, 0, 0, 0, 1}, {0, 0, 1, 0, 0}, {1, 0, 0, 0, 1}, {0, 0, 0, 0, 0}};
        EXPECT_EQ(s.uniquePaths(grid), 22);
    }
    // 取模：50x50 空网格答案 C(98,49) 远超 10^9+7（经 math.comb(98,49) % MOD 独立核对）
    {
        vector<vector<int>> grid(50, vector<int>(50, 0));
        EXPECT_EQ(s.uniquePaths(grid), 267422234);
    }
}
