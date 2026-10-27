// @题目描述:
// 给你两个整数 m 和 n，分别表示网格的行数和列数。请构造任意一个只包含字符 '.' 和 '#'
// 的 m x n 网格（'.' 空单元格、'#' 障碍物），使得从左上角 (0, 0) 走到右下角 (m-1, n-1)
// 的有效路径恰好有一条：每一步只能向右或向下移动，且只能经过空单元格。
// 返回任意一个满足条件的网格。答案不唯一，判题程序按性质验证，无需与示例一致。
// 提示：1 <= m, n <= 25
// 题目：https://leetcode.cn/problems/create-grid-with-exactly-one-path/description/
//
// @示例:
// 输入：m = 2, n = 3
// 输出：["..#", "#.."]（唯一路径 (0,0) -> (0,1) -> (1,1) -> (1,2)）
// 输入：m = 3, n = 3
// 输出：["..#", "#..", "##."]（唯一路径 (0,0) -> (0,1) -> (1,1) -> (1,2) -> (2,2)）
// 输入：m = 1, n = 4
// 输出：["...."]（唯一路径 (0,0) -> (0,1) -> (0,2) -> (0,3)）
//
// @解题思路:
// 「Γ」形走廊：第 0 行全部填 '.'（从 (0,0) 一路向右走到 (0, n-1)）；
// 其余每行为 '#'*(n-1) + '.'（只有最后一列留空，再一路向下走到 (m-1, n-1)）。
// 顶行下方全是 '#'（中途下不去），最后一列右边是边界（只能向下），
// 每个可达格子只有一种来路，路径数恰好为 1。
// m=1 时追加行的循环零次、n=1 时 '#'*(n-1) 为空串，退化情形无需特判。
//
// 复杂度分析：
// - 时间复杂度：O(m·n)（构造 m 行、每行 n 个字符）
// - 空间复杂度：O(m·n)（返回的网格）

#include <gtest/gtest.h>

using namespace std;

namespace {
class Solution {
   public:
    vector<string> createGrid(int m, int n) {
        vector<string> ret;

        string top;
        string line;
        for (auto i = 0; i < n - 1; i++) {
            top += '.';
            line += '#';
        }

        top += '.';
        line += '.';

        ret.emplace_back(top);
        for (auto i = 0; i < m - 1; i++) {
            ret.emplace_back(line);
        }

        return ret;
    }
};

// 统计从 (0,0) 到 (m-1,n-1) 只向右/向下、只走 '.' 的路径数（判题同款验证逻辑）
long long countPaths(const vector<string>& grid) {
    int m = static_cast<int>(grid.size());
    int n = static_cast<int>(grid[0].size());
    vector<vector<long long>> dp(m, vector<long long>(n, 0));
    dp[0][0] = grid[0][0] == '.' ? 1 : 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '#') {
                continue;
            }
            if (i > 0) {
                dp[i][j] += dp[i - 1][j];
            }
            if (j > 0) {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }
    return dp[m - 1][n - 1];
}

// 答案不唯一：像判题程序一样按性质验证，而非比对具体输出
void expectValidGrid(const vector<string>& grid, int m, int n) {
    ASSERT_EQ(grid.size(), static_cast<size_t>(m));
    for (const string& row : grid) {
        ASSERT_EQ(row.size(), static_cast<size_t>(n));
        for (char c : row) {
            ASSERT_TRUE(c == '.' || c == '#');
        }
    }
    ASSERT_EQ(countPaths(grid), 1);
}
}  // namespace

TEST(Daily, 3963) {
    Solution s;

    // 官方示例（答案不唯一，按性质验证）
    expectValidGrid(s.createGrid(2, 3), 2, 3);
    expectValidGrid(s.createGrid(3, 3), 3, 3);
    expectValidGrid(s.createGrid(1, 4), 1, 4);

    // 最小网格：1x1，路径就是起点本身
    expectValidGrid(s.createGrid(1, 1), 1, 1);

    // 单行/单列：任何 '#' 都会挡死唯一通道，必须全 '.'
    expectValidGrid(s.createGrid(1, 25), 1, 25);
    expectValidGrid(s.createGrid(25, 1), 25, 1);

    // 最小方形 2x2：全 '.' 有两条路，必须用障碍压到一条
    expectValidGrid(s.createGrid(2, 2), 2, 2);

    // 窄长条：岔路多、障碍要交错放
    expectValidGrid(s.createGrid(2, 25), 2, 25);
    expectValidGrid(s.createGrid(25, 2), 25, 2);

    // 规模上限 25x25
    expectValidGrid(s.createGrid(25, 25), 25, 25);
}
