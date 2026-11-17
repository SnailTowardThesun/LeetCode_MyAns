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
    转置 + 逐行反转（两次原地翻转等价于顺时针旋转 90°）：
    1. 沿主对角线转置：交换 matrix[i][j] 与 matrix[j][i]。内层 j 从 i
       出发只走「上三角」（含对角线，对角线自交换是 no-op），保证每对
       (i,j)/(j,i) 恰好交换一次——若 j 扫全列，每对会交换两次还原回去；
    2. 每行左右反转（水平镜像）。
    顺时针 90° = 主对角线转置 + 水平镜像；若要逆时针 90°，改为转置 +
    上下镜像即可。另一条路线是按圈四点轮转：(i,j) → (j, n-1-i)。

    时间复杂度 O(n²)，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/rotate-image/description/
"""


class Solution:
    def rotate(self, matrix: list[list[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        m, n = len(matrix), len(matrix[0])

        # 1. 主对角线转置：j 从 i 起只走上三角，每对元素只交换一次
        for i in range(m):
            for j in range(i, n):
                matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]

        # 2. 逐行左右反转（水平镜像），组合后即顺时针旋转 90°
        for i in range(m):
            for j in range(n // 2):
                matrix[i][j], matrix[i][n - j - 1] = matrix[i][n - j - 1], matrix[i][j]


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
