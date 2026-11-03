"""
@file top150_221.py
@brief LeetCode 221. Maximal Square（最大正方形）

@题目描述
    给定一个由 '0' 和 '1' 组成的 m x n 二进制矩阵 matrix，
    找出只包含 '1' 的最大正方形，并返回其面积。

@示例
    示例 1：
    输入：matrix = [["1","0","1","0","0"],
                   ["1","0","1","1","1"],
                   ["1","1","1","1","1"],
                   ["1","0","0","1","0"]]
    输出：4
    解释：存在 2x2 的全 '1' 正方形（如第 3~4 行、第 3~4 列），面积为 4。

    示例 2：
    输入：matrix = [["0","1"],["1","0"]]
    输出：1
    解释：最大的全 '1' 正方形边长为 1，面积为 1。

    示例 3：
    输入：matrix = [["0"]]
    输出：0

    数据范围：
    1 <= m, n <= 300
    matrix[i][j] 为 '0' 或 '1'

@解题思路
    二维 DP（以「右下角」为锚点定义状态）：
    - f[i+1][j+1]：以 matrix[i][j] 为右下角的全 '1' 最大正方形边长；
      f 比 matrix 多加一行一列 0 作哨兵，省去边界特判。
    - 转移：matrix[i][j] == '1' 时
        f[i+1][j+1] = min(f[i][j], f[i][j+1], f[i+1][j]) + 1
      即受「左上、上、左」三个邻格中最小者约束——正方形要向三个方向同时扩张；
    - matrix[i][j] == '0' 时 f 保持 0（无法构成任何正方形）。
    - 答案：max(f) 的平方（边长最大值的平方即面积）。

    时间复杂度 O(m·n)，空间复杂度 O(m·n)（可滚动数组优化到 O(n)）
"""


class Solution:
    def maximalSquare(self, matrix: list[list[str]]) -> int:
        m, n = len(matrix), len(matrix[0])
        # f 多加一行一列 0 作哨兵，f[i+1][j+1] 对应以 (i, j) 为右下角的最大边长
        f = [[0] * (n + 1) for _ in range(m + 1)]
        for i, row in enumerate(matrix):
            for j, ch in enumerate(row):
                if ch == "1":
                    # 受左上、上、左三侧最小者约束，三面都能扩出 k-1 才能扩到 k
                    f[i + 1][j + 1] = min(f[i][j], f[i][j + 1], f[i + 1][j]) + 1
        return max(map(max, f)) ** 2


def test_solution() -> None:
    solution = Solution()
    # 官方示例 1：2x2 正方形，面积 4
    assert (
        solution.maximalSquare(
            [["1", "0", "1", "0", "0"], ["1", "0", "1", "1", "1"], ["1", "1", "1", "1", "1"], ["1", "0", "0", "1", "0"]]
        )
        == 4
    )
    # 官方示例 2：边长 1，面积 1
    assert solution.maximalSquare([["0", "1"], ["1", "0"]]) == 1
    # 官方示例 3：全 0，面积 0
    assert solution.maximalSquare([["0"]]) == 0
    # 全 1 的 3x3：边长 3，面积 9
    assert solution.maximalSquare([["1"] * 3 for _ in range(3)]) == 9
    # 单行：边长最长 1
    assert solution.maximalSquare([["1", "1", "1"]]) == 1
    # 单列：边长最长 1
    assert solution.maximalSquare([["1"], ["1"]]) == 1
    # 对角线 1：互不相邻，面积 1
    assert solution.maximalSquare([["1", "0"], ["0", "1"]]) == 1


if __name__ == "__main__":
    test_solution()
    print("✅ No.221 全部测试通过")
