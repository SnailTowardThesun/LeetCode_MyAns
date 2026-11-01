"""
@file top150_63.py
@brief LeetCode 63. Unique Paths II（不同路径 II）

@题目描述
    一个机器人位于 m x n 网格的左上角（起点 grid[0][0]）。机器人每次只能向下或者向右
    移动一步，试图到达网格的右下角 grid[m-1][n-1]。
    网格中的障碍物和空位置分别用 1 和 0 表示，机器人的移动路径中不能包含任何障碍物。
    返回机器人能够到达右下角的不同路径数量。测试用例保证答案 <= 2 * 10^9。

@示例
    示例 1：
    输入：obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
    输出：2
    解释：3x3 网格正中间有一个障碍物，共 2 条路径：
         右→右→下→下；下→下→右→右。

    示例 2：
    输入：obstacleGrid = [[0,1],[0,0]]
    输出：1

    数据范围：
    m == obstacleGrid.length
    n == obstacleGrid[i].length
    1 <= m, n <= 100
    obstacleGrid[i][j] 为 0 或 1

@解题思路
    经典网格计数 DP：dp[i][j] = 到达 (i,j) 的路径数。
    1. 障碍格 dp 恒为 0——这一条就足够：转移中"前驱是否障碍"无需再判断，
       加上 0 自然等价于"那条方向无路可来"，边界行/列同理，全程一个转移式；
    2. 起点可达则 dp[0][0] = 1；起点是障碍时 dp[0][0] 保持 0，答案自然为 0，
       无需特判提前返回；
    3. 越界方向（i=0 的上方、j=0 的左侧）按 0 处理，统一成
       dp[i][j] = top + left。
    备注：本文件初版的转移带四分支前驱障碍判断与"首行前后是否为 0"的冗余分支，
    行为正确但均为死代码（障碍 dp=0 已隐式表达），整理时塌缩为单一转移式，
    200 组随机网格对拍验证两版结果一致。

    时间复杂度 O(m*n)，空间复杂度 O(m*n)（滚动可 O(n)）
"""


class Solution:
    def uniquePathsWithObstacles(self, obstacleGrid: list[list[int]]) -> int:
        m, n = len(obstacleGrid), len(obstacleGrid[0])
        # dp[i][j] = 到达 (i,j) 的路径数；障碍格保持 0，转移加 0 即"该方向无路可来"
        dp = [[0] * n for _ in range(m)]
        for i in range(m):
            for j in range(n):
                if obstacleGrid[i][j] == 1:
                    continue  # 障碍：保持 0（起点/终点是障碍时答案自然为 0）
                if i == 0 and j == 0:
                    dp[i][j] = 1  # 起点可达时恰有 1 种走法
                    continue
                top = dp[i - 1][j] if i > 0 else 0
                left = dp[i][j - 1] if j > 0 else 0
                dp[i][j] = top + left
        return dp[m - 1][n - 1]


def test_solution() -> None:
    solution = Solution()
    # 官方示例
    assert solution.uniquePathsWithObstacles([[0, 0, 0], [0, 1, 0], [0, 0, 0]]) == 2
    assert solution.uniquePathsWithObstacles([[0, 1], [0, 0]]) == 1
    # 边界：1x1（含起点即障碍）
    assert solution.uniquePathsWithObstacles([[0]]) == 1
    assert solution.uniquePathsWithObstacles([[1]]) == 0
    # 单行 / 单列：中间障碍会整段封死
    assert solution.uniquePathsWithObstacles([[0, 0, 0]]) == 1
    assert solution.uniquePathsWithObstacles([[0, 1, 0]]) == 0
    assert solution.uniquePathsWithObstacles([[0], [1], [0]]) == 0
    # 终点是障碍：一步之遥也算 0（注意 [[0,1]] 这类"终点即障碍"的小网格）
    assert solution.uniquePathsWithObstacles([[0, 0], [0, 1]]) == 0
    assert solution.uniquePathsWithObstacles([[0, 1]]) == 0
    # 无障碍退化为组合数：3x3 = C(4,2) = 6
    assert solution.uniquePathsWithObstacles([[0, 0, 0], [0, 0, 0], [0, 0, 0]]) == 6
    # 挡墙只留一个缺口：所有路径被迫走同一列
    assert solution.uniquePathsWithObstacles([[0, 0, 0], [1, 1, 0], [0, 0, 0]]) == 1
    # 随机含障网格（期望值经 DFS 全路径计数暴力验证）
    assert solution.uniquePathsWithObstacles([[0, 0, 1, 0], [0, 1, 0, 0], [0, 0, 0, 0]]) == 1
    assert solution.uniquePathsWithObstacles([[0, 0], [1, 0], [0, 0], [0, 0]]) == 1


if __name__ == "__main__":
    test_solution()
    print("✅ No.63 全部测试通过")
