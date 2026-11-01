"""
@file top150_64.py
@brief LeetCode 64. Minimum Path Sum（最小路径和）

@题目描述
    给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，
    使得路径上的数字总和为最小。每一步只能向下或者向右移动一步。

@示例
    示例 1：
    输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
    输出：7
    解释：路径 1→3→1→1→1 的总和最小，为 7 。

    示例 2：
    输入：grid = [[1,2,3],[4,5,6]]
    输出：12

    数据范围：
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 200
    0 <= grid[i][j] <= 200
    （进阶：仅使用 O(n) 额外空间）

@解题思路
    经典二维网格 DP：dp[i][j] = 从 (0,0) 走到 (i,j) 的最小路径和。
    1. 「只能向右或向下」保证了计算顺序无环：按行序双循环天然是拓扑序；
    2. 转移：首行只能来自左侧、首列只能来自上方、其余取两者较小——
       dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])；
    3. 起点 dp[0][0] = grid[0][0] 必须显式处理：若漏掉，dp[0][0] 会误走首行分支，
       依赖 dp[0][-1] 的负索引巧合——移植到无负索引的语言（C++/Java）即越界。
    4. 空间可滚动到 O(n)（逐行覆盖），也可直接原地在 grid 上写。

    时间复杂度 O(m*n)，空间复杂度 O(m*n)（滚动可 O(n)）
"""


class Solution:
    def minPathSum(self, grid: list[list[int]]) -> int:
        m, n = len(grid), len(grid[0])
        dp = [[0] * n for _ in range(m)]
        for i in range(m):
            for j in range(n):
                if i == 0 and j == 0:  # 起点必须显式分支：漏掉会依赖 dp[0][-1] 的负索引巧合
                    dp[i][j] = grid[i][j]
                    continue
                if i == 0:  # 首行：只能来自左侧
                    dp[i][j] = grid[i][j] + dp[i][j - 1]
                elif j == 0:  # 首列：只能来自上方
                    dp[i][j] = grid[i][j] + dp[i - 1][j]
                else:
                    dp[i][j] = grid[i][j] + min(dp[i][j - 1], dp[i - 1][j])

        return dp[m - 1][n - 1]


def test_solution() -> None:
    solution = Solution()
    # 官方示例
    assert solution.minPathSum([[1, 3, 1], [1, 5, 1], [4, 2, 1]]) == 7  # 1→3→1→1→1
    assert solution.minPathSum([[1, 2, 3], [4, 5, 6]]) == 12
    # 边界：1x1 / 单行 / 单列 / 全 0
    assert solution.minPathSum([[5]]) == 5
    assert solution.minPathSum([[1, 2, 3]]) == 6
    assert solution.minPathSum([[1], [2], [3]]) == 6
    assert solution.minPathSum([[0, 0], [0, 0]]) == 0
    # 反贪心：每步选相邻较小值会先向右踩进 100 走廊（总和 206），最优 13 在向下那条
    assert solution.minPathSum([[1, 2, 100], [3, 100, 100], [3, 3, 3]]) == 13
    # 负索引陷阱已修：起点显式赋值，不再依赖 dp[0][-1] 恰好为 0
    assert solution.minPathSum([[7, 9], [8, 6]]) == 21
    # 值域上界：200x200 全 200，答案 = (m+n-1)*200
    assert solution.minPathSum([[200] * 200 for _ in range(200)]) == 79800


if __name__ == "__main__":
    test_solution()
    print("✅ No.64 全部测试通过")
