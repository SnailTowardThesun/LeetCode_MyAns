"""
@file hot100_54.py
@brief LeetCode 54. 螺旋矩阵（Spiral Matrix）— HOT 100

@题目描述
    给你一个 m 行 n 列的矩阵 matrix，请按照顺时针螺旋顺序，返回矩阵中的所有元素。

@示例
    示例 1：
    输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
    输出：[1,2,3,6,9,8,7,4,5]

    示例 2：
    输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
    输出：[1,2,3,4,8,12,11,10,9,5,6,7]

    数据范围：
    m == matrix.length, n == matrix[i].length
    1 <= m, n <= 10
    -100 <= matrix[i][j] <= 100

@解题思路
    剥圈递归：
    1. 每层按「右→下→左→上」的顺时针方向采集最外圈元素；
    2. 用切片提取去掉外圈后的子矩阵，递归处理内圈，直到矩阵为空。
    两处边界判断用于避免重复采集：
    - 单行（m == 1）时跳过「向左」：底行与顶行是同一行，回头会把顶行再采一遍；
    - 单列（n == 1）时跳过「向上」：左列与右列是同一列，回头会把左列再采一遍。
    边界判断既处理单行/单列输入，也处理递归内层出现单行/单列（如 3×4 的内圈是 1×2）。

    最坏时间复杂度 O(m×n×min(m,n))：采集本身为 O(m×n)，但每层都复制内圈并拼接结果。
    最坏额外空间复杂度 O(m×n×min(m,n))（不计输出）：递归期间各层子矩阵同时存活。
    对边长为 N 的方阵，各层复制量为 (N-2)² + (N-4)² + ...，总量为 O(N³)。
    迭代四边界写法可避免复制，实现 O(m×n) 时间、O(1) 额外空间。

来源：LeetCode
链接：https://leetcode.cn/problems/spiral-matrix/description/
"""


class Solution:
    def spiralOrder(self, matrix: list[list[int]]) -> list[int]:
        def do_spiral(matrix: list[list[int]]) -> list[int]:
            if len(matrix) == 0:
                return []
            if len(matrix[0]) == 0:
                return []

            m, n = len(matrix), len(matrix[0])
            ret = []

            # 1. 向右：采集顶行
            for i in range(n):
                ret.append(matrix[0][i])

            # 2. 向下：采集右列（从第二行起）
            for i in range(1, m):
                ret.append(matrix[i][n - 1])

            # 3. 向左：采集底行；单行时底行==顶行，跳过避免重复
            if m > 1:
                for i in range(n - 2, -1, -1):
                    ret.append(matrix[m - 1][i])

            # 4. 向上：采集左列；单列时左列==右列，跳过避免重复
            if n > 1:
                for i in range(m - 2, 0, -1):
                    ret.append(matrix[i][0])

            # 去掉外圈，递归内圈
            sub = [row[1 : n - 1] for row in matrix[1 : m - 1]]
            return ret + do_spiral(sub)

        return do_spiral(matrix)


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.spiralOrder([[1, 2, 3], [4, 5, 6], [7, 8, 9]]) == [1, 2, 3, 6, 9, 8, 7, 4, 5]
    assert solution.spiralOrder([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]]) == [
        1,
        2,
        3,
        4,
        8,
        12,
        11,
        10,
        9,
        5,
        6,
        7,
    ]

    # ---- 单行 / 单列（曾因回头方向重复采集而出错）----
    assert solution.spiralOrder([[1, 2, 3]]) == [1, 2, 3]
    assert solution.spiralOrder([[1], [2], [3]]) == [1, 2, 3]

    # ---- 内圈退化为单列（4×3 内圈 2×1；5×3 内圈 3×1）----
    assert solution.spiralOrder([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]]) == [
        1,
        2,
        3,
        6,
        9,
        12,
        11,
        10,
        7,
        4,
        5,
        8,
    ]
    assert solution.spiralOrder([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12], [13, 14, 15]]) == [
        1,
        2,
        3,
        6,
        9,
        12,
        15,
        14,
        13,
        10,
        7,
        4,
        5,
        8,
        11,
    ]

    # ---- 单元素 / 2×2 ----
    assert solution.spiralOrder([[1]]) == [1]
    assert solution.spiralOrder([[1, 2], [3, 4]]) == [1, 2, 4, 3]

    # ---- 多层：4×4 两圈 / 5×5 三圈（中心收尾）----
    assert solution.spiralOrder([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]) == [
        1,
        2,
        3,
        4,
        8,
        12,
        16,
        15,
        14,
        13,
        9,
        5,
        6,
        7,
        11,
        10,
    ]
    assert solution.spiralOrder(
        [[1, 2, 3, 4, 5], [6, 7, 8, 9, 10], [11, 12, 13, 14, 15], [16, 17, 18, 19, 20], [21, 22, 23, 24, 25]]
    ) == [1, 2, 3, 4, 5, 10, 15, 20, 25, 24, 23, 22, 21, 16, 11, 6, 7, 8, 9, 14, 19, 18, 17, 12, 13]


if __name__ == "__main__":
    test_solution()
    print("✅ No.54（HOT 100）全部测试通过")
