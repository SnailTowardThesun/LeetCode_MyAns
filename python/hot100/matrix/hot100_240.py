"""
@file hot100_240.py
@brief LeetCode 240. 搜索二维矩阵 II（Search a 2D Matrix II）— HOT 100

@题目描述
    给定一个 m × n 矩阵 matrix，满足：
    - 每行的元素从左到右升序排列；
    - 每列的元素从上到下升序排列。
    判断目标值 target 是否存在于矩阵中。

@示例
    示例 1：
    输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
    输出：True

    示例 2：
    输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
    输出：False

    数据范围：
    m == matrix.length, n == matrix[i].length
    1 <= m, n <= 300
    -10^9 <= matrix[i][j], target <= 10^9
    每行、每列均升序（行与行之间无大小约束）

@解题思路
    右上角阶梯搜索：
    从右上角 (0, n-1) 出发——它是所在行的最大值、所在列的最小值，两个方向
    的单调性相反，恰好能唯一决策：
    1. 当前值 > target：本列往下更大，整列排除，左移一列（y -= 1）；
    2. 当前值 < target：本行往左更小，整行排除，下移一行（x += 1）；
    3. 相等则找到，越界则不存在。
    每步至少排除一行或一列，最多 m + n 步出结果。
    起点也可以选左下角（行最小、列最大，方向相反）；但左上角（双最小）和
    右下角（双最大）无法决策，不能作起点。
    对比：74 题矩阵行间也全局有序，可二分定位；本题行间无序，逐行二分是
    O(m log n)，阶梯搜索 O(m + n) 更稳。

    时间复杂度 O(m + n)，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/search-a-2d-matrix-ii/description/
"""


class Solution:
    def searchMatrix(self, matrix: list[list[int]], target: int) -> bool:
        m, n = len(matrix), len(matrix[0])
        x, y = 0, n - 1  # 从右上角出发：行内最大、列内最小，两向单调性相反
        while x < m and y >= 0:
            if matrix[x][y] == target:
                return True

            if matrix[x][y] > target:
                y -= 1  # 本列往下更大 → 整列排除，左移
            else:
                x += 1  # 本行往左更小 → 整行排除，下移

        return False


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    mx = [[1, 4, 7, 11, 15], [2, 5, 8, 12, 19], [3, 6, 9, 16, 22], [10, 13, 14, 17, 24], [18, 21, 23, 26, 30]]
    assert solution.searchMatrix(mx, 5) is True
    assert solution.searchMatrix(mx, 20) is False

    # ---- 四个角与界外 ----
    assert solution.searchMatrix(mx, 1) is True  # 左上最小
    assert solution.searchMatrix(mx, 30) is True  # 右下最大
    assert solution.searchMatrix(mx, 0) is False  # 小于最小
    assert solution.searchMatrix(mx, 31) is False  # 大于最大

    # ---- 单行 / 单列 ----
    assert solution.searchMatrix([[1, 3, 5]], 5) is True
    assert solution.searchMatrix([[1, 3, 5]], 4) is False
    assert solution.searchMatrix([[1], [3], [5]], 3) is True
    assert solution.searchMatrix([[1], [3], [5]], 2) is False

    # ---- 单元素 ----
    assert solution.searchMatrix([[1]], 1) is True
    assert solution.searchMatrix([[1]], 2) is False

    # ---- 走完整条搜索路径的对角用例 ----
    assert solution.searchMatrix([[1, 4], [2, 5]], 2) is True
    assert solution.searchMatrix([[1, 4], [2, 5]], 3) is False


if __name__ == "__main__":
    test_solution()
    print("✅ No.240（HOT 100）全部测试通过")
