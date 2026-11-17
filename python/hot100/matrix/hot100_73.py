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
    先收集后置零（本实现，O(m×n) 时间 / O(k) 空间，k 为 0 的个数）：
    1. 第一遍遍历，把所有 0 的坐标 (i, j) 收进列表；
    2. 依据收集到的坐标，把对应行、列整体置零。
    顺序很关键：必须"先收集、后置零"——若边扫边置零，新写入的 0 会再次
    触发整行整列置零，污染结果。
    注意：题目进阶要求 O(1) 空间，标准解法是用第一行/第一列自身做标记位
    （两个 bool 分别记录首行、首列自身是否含 0，从 (1,1) 开始按标记置零，
    最后处理首行首列）——见对应博客的实现。

    时间复杂度 O(m×n)，空间复杂度 O(k)（最坏 O(m×n)）

来源：LeetCode
链接：https://leetcode.cn/problems/set-matrix-zeroes/description/
"""


class Solution:
    def setZeroes(self, matrix: list[list[int]]) -> None:
        m, n = len(matrix), len(matrix[0])
        zeros = [(i, j) for i in range(m) for j in range(n) if matrix[i][j] == 0]

        # 先收集后置零：新写入的 0 不会再触发置零
        for r, c in zeros:
            for j in range(n):  # 整行置零
                matrix[r][j] = 0
            for i in range(m):  # 整列置零
                matrix[i][c] = 0


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

    # ---- 同行多个 0：重复置零幂等 ----
    m7 = [[1, 0, 3], [4, 5, 0], [7, 8, 9]]
    solution.setZeroes(m7)
    assert m7 == [[0, 0, 0], [0, 0, 0], [7, 0, 0]]


if __name__ == "__main__":
    test_solution()
    print("✅ No.73（HOT 100）全部测试通过")
