"""
@file hot100_73.py
@brief LeetCode 73. 矩阵置零（Set Matrix Zeroes）— HOT 100

@题目描述
    给定 m × n 矩阵，若某个元素为 0，则将其所在行和列的所有元素置为 0。
    请使用原地算法完成修改。

@示例
    示例 1：
    输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
    输出：[[1,0,1],[0,0,0],[1,0,1]]

    示例 2：
    输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
    输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]

    数据范围：
    1 <= m, n <= 200
    -2^31 <= matrix[i][j] <= 2^31 - 1
    进阶：使用 O(1) 空间解决

@解题思路
    复用第一行和第一列作为标记：
    1. 在写入任何标记前，记录第一行和第一列是否原本就含零。
    2. 扫描其余单元格。遇到零时，将所在行的行首、所在列的列首置零。
    3. 根据行首和列首的标记置零，最后按步骤 1 的记录处理第一行和第一列。
    分开标记和置零，避免把后续写入的零误当作原始零。

    时间复杂度 O(m×n)，额外空间复杂度 O(1)。

来源：LeetCode
链接：https://leetcode.cn/problems/set-matrix-zeroes/description/
"""


class Solution:
    def setZeroes(self, matrix: list[list[int]]) -> None:
        m, n = len(matrix), len(matrix[0])
        first_row_zero = 0 in matrix[0]
        first_col_zero = any(row[0] == 0 for row in matrix)

        for i in range(1, m):
            for j in range(1, n):
                if matrix[i][j] == 0:
                    matrix[i][0] = matrix[0][j] = 0

        for i in range(1, m):
            for j in range(1, n):
                if matrix[i][0] == 0 or matrix[0][j] == 0:
                    matrix[i][j] = 0

        if first_row_zero:
            for j in range(n):
                matrix[0][j] = 0
        if first_col_zero:
            for i in range(m):
                matrix[i][0] = 0


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    m1 = [[1, 1, 1], [1, 0, 1], [1, 1, 1]]
    solution.setZeroes(m1)
    assert m1 == [[1, 0, 1], [0, 0, 0], [1, 0, 1]]

    m2 = [[0, 1, 2, 0], [3, 4, 5, 2], [1, 3, 1, 5]]
    solution.setZeroes(m2)
    assert m2 == [[0, 0, 0, 0], [0, 4, 5, 0], [0, 3, 1, 0]]

    # ---- 无 0：原样返回 ----
    m3 = [[1, 2], [3, 4]]
    solution.setZeroes(m3)
    assert m3 == [[1, 2], [3, 4]]

    # ---- 全 0 ----
    m4 = [[0, 0], [0, 0]]
    solution.setZeroes(m4)
    assert m4 == [[0, 0], [0, 0]]

    # ---- 单元素 ----
    m5 = [[0]]
    solution.setZeroes(m5)
    assert m5 == [[0]]

    # ---- 首行/首列含 0 ----
    m6 = [[0, 2], [3, 4]]
    solution.setZeroes(m6)
    assert m6 == [[0, 0], [0, 4]]

    # ---- 多个 0：同一行或列可以被多次标记 ----
    m7 = [[1, 0, 3], [4, 5, 0], [7, 8, 9]]
    solution.setZeroes(m7)
    assert m7 == [[0, 0, 0], [0, 0, 0], [7, 0, 0]]

    # ---- 首行与首列的标记相互独立 ----
    first_row_only = [[1, 0, 3], [4, 5, 6]]
    solution.setZeroes(first_row_only)
    assert first_row_only == [[0, 0, 0], [4, 0, 6]]

    first_col_only = [[1, 2], [0, 4], [5, 6]]
    solution.setZeroes(first_col_only)
    assert first_col_only == [[0, 2], [0, 0], [0, 6]]


if __name__ == "__main__":
    test_solution()
    print("✅ No.73（HOT 100）全部测试通过")
