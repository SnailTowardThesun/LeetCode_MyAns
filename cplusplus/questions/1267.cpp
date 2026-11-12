/**
 * @file 1267.cpp
 * @brief LeetCode 1267. 统计参与通信的服务器（Count Servers that Communicate）
 *
 * @题目描述
 * 给你一个 m x n 的整数矩阵 grid 表示一个服务器中心的数据分布图：
 * - grid[i][j] = 1 表示单元格 (i, j) 处有一台服务器；
 * - grid[i][j] = 0 表示该单元格没有服务器。
 * 两台服务器位于同一行或同一列，就说它们可以通信。
 * 统计并返回能够与至少一台其他服务器通信的服务器数目。
 *
 * @示例
 * 示例 1：
 * 输入：grid = [[1,0],[0,1]]
 * 输出：0
 * 解释：没有服务器可以与其他服务器通信。
 *
 * 示例 2：
 * 输入：grid = [[1,0],[1,1]]
 * 输出：3
 * 解释：三台服务器都能与至少一台其他服务器通信。
 *
 * 示例 3：
 * 输入：grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
 * 输出：4
 * 解释：第一行的两台服务器互相通信；第三列的两台服务器互相通信；
 * 右下角的服务器与谁都不在同一行列，不计入。
 *
 * 数据范围：
 * 1 <= m, n <= 250
 * grid[i][j] 为 0 或 1
 *
 * @解题思路
 * 「同一行或同一列即可通信」意味着一台服务器能否通信，只取决于它所在的
 * 行、列里是否还有别的服务器——与连通块的形状无关，用不着 DFS/并查集：
 * 1. 第一遍扫描：统计每行的服务器数 row_cnt 和每列的服务器数 col_cnt；
 * 2. 第二遍扫描：对每个 grid[i][j] == 1 的格子，若 row_cnt[i] > 1 或
 *    col_cnt[j] > 1，说明同行/同列至少还有一台服务器，计入答案；
 * 3. 返回计数。
 * 相比按连通分量做 DFS/并查集（分量大小 >= 2 即全计入），计数法一个公式
 * 就能判定，且完全无递归——本题 m、n 达 250，蛇形连通块可长达 6 万格，
 * 朴素 DFS 的递归深度会随之失控。
 *
 * 复杂度分析：
 * - 时间复杂度：O(m * n)（两遍线性扫描）
 * - 空间复杂度：O(m + n)（行列计数表）
 */

#include <gtest/gtest.h>

#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {

class Solution {
   public:
    int countServers(vector<vector<int>>& grid) {
        int ret = 0;
        int m = grid.size();
        int n = grid[0].size();

        vector<int> row_cnt(m, 0);
        vector<int> col_cnt(n, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    row_cnt[i] += 1;
                    col_cnt[j] += 1;
                }
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    if (row_cnt[i] > 1 || col_cnt[j] > 1) {
                        ret += 1;
                    }
                }
            }
        }
        return ret;
    }
};

}  // namespace

TEST(Daily, 1267) {
    Solution s;
    auto check = [&s](vector<vector<int>> grid, int expect) { EXPECT_EQ(s.countServers(grid), expect); };
    // 官方示例
    check({{1, 0}, {0, 1}}, 0);                                          // 示例 1：无同行同列，全部孤立
    check({{1, 0}, {1, 1}}, 3);                                          // 示例 2：三台全部互通
    check({{1, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}, 4);  // 示例 3：两组互通 + 一个孤立
    // 边界：单台服务器无法通信
    check({{1}}, 0);
    // 同一行 / 同一列多台：全部计入
    check({{1, 1, 1}}, 3);
    check({{1}, {1}, {1}}, 3);
    // 全 1 的 2x2：四台全部计入
    check({{1, 1}, {1, 1}}, 4);
    // 对角线摆放：不同行不同列，全部孤立
    check({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}, 0);
    // 四角互通、中心孤立：只数四角
    check({{1, 0, 1}, {0, 1, 0}, {1, 0, 1}}, 4);
}
