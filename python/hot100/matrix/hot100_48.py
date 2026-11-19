"""
@file hot100_48.py
@brief LeetCode 48. 旋转图像（Rotate Image）— HOT 100

@题目描述
    给定一个 n × n 的二维矩阵 matrix 表示一个图像，请将图像顺时针旋转 90 度。
    必须原地旋转输入矩阵，即不能使用另一个矩阵来旋转图像。

@示例
    示例 1：
    输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
    输出：[[7,4,1],[8,5,2],[9,6,3]]

    示例 2：
    输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
    输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

    数据范围：
    n == matrix.length == matrix[i].length
    1 <= n <= 20
    -1000 <= matrix[i][j] <= 1000

@解题思路
    先沿主对角线转置，再反转每行。
    1. 转置时令 j 从 i+1 开始，只遍历严格上三角，每对非对角线元素交换一次。
    2. 逐行反转，把每行下标 i 处的元素移到该行下标 n-1-i 处。
    原位置 (i,j) 经过这两个步骤依次变为 (j,i) 和 (j,n-1-i)，对应顺时针旋转 90°。

    时间复杂度 O(n²)，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/rotate-image/description/
"""


class Solution:
    def rotate(self, matrix: list[list[int]]) -> None:
        n = len(matrix)

        # 只遍历严格上三角，避免重复交换
        for i in range(n):
            for j in range(i + 1, n):
                matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]

        for row in matrix:
            row.reverse()


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    m1 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    solution.rotate(m1)
    assert m1 == [[7, 4, 1], [8, 5, 2], [9, 6, 3]]

    m2 = [[5, 1, 9, 11], [2, 4, 8, 10], [13, 3, 6, 7], [15, 14, 12, 16]]
    solution.rotate(m2)
    assert m2 == [[15, 13, 2, 5], [14, 3, 4, 1], [12, 6, 8, 9], [16, 7, 10, 11]]

    # ---- 最小规模 ----
    m3 = [[1]]
    solution.rotate(m3)
    assert m3 == [[1]]

    m4 = [[1, 2], [3, 4]]
    solution.rotate(m4)
    assert m4 == [[3, 1], [4, 2]]

    # ---- 不变量：旋转 4 次（360°）回到原矩阵（5×5）----
    m5 = [[i * 5 + j for j in range(5)] for i in range(5)]
    origin = [row[:] for row in m5]
    for _ in range(4):
        solution.rotate(m5)
    assert m5 == origin

    # ---- 不变量：旋转 2 次（180°）等于整体倒序 ----
    m6 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    solution.rotate(m6)
    solution.rotate(m6)
    assert m6 == [[9, 8, 7], [6, 5, 4], [3, 2, 1]]


if __name__ == "__main__":
    test_solution()
    print("✅ No.48（HOT 100）全部测试通过")
