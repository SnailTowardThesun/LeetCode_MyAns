"""
@file hot100_240.py
@brief LeetCode 240. 搜索二维矩阵 II（Search a 2D Matrix II）— HOT 100

@题目描述
    给定一个 m × n 矩阵 matrix，满足：
    - 每行的元素从左到右非递减；
    - 每列的元素从上到下非递减。
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
    行列分别有序，按行拼接后的序列不一定有序。

@解题思路
    从右上角 (0, n-1) 开始阶梯搜索。每一步都在剩余区域的右上角比较：
    1. 当前值 > target：同列下方的候选值都不小于当前值，排除此列并向左移动。
    2. 当前值 < target：同行左侧的候选值都不大于当前值，排除此行并向下移动。
    3. 相等则找到，越界则不存在。
    每步至多访问一个位置，总共至多访问 m+n-1 个位置。
    起点也可以选左下角（行最小、列最大，方向相反）；但左上角（双最小）和
    右下角（双最大）不能仅靠一次比较确定这类搜索的移动方向。
    对比：74 题可按行展开为一维有序数组，本题不满足这一条件。
    逐行二分为 O(m log(n+1))，阶梯搜索为 O(m+n)，优劣取决于矩阵形状；
    例如单行矩阵中，二分为 O(log(n+1))，阶梯搜索最坏为 O(n)。

    时间复杂度 O(m + n)，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/search-a-2d-matrix-ii/description/
"""


class Solution:
    def searchMatrix(self, matrix: list[list[int]], target: int) -> bool:
        m, n = len(matrix), len(matrix[0])
        row, col = 0, n - 1
        while row < m and col >= 0:
            value = matrix[row][col]
            if value == target:
                return True

            if value > target:
                col -= 1
            else:
                row += 1

        return False


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    mx = [[1, 4, 7, 11, 15], [2, 5, 8, 12, 19], [3, 6, 9, 16, 22], [10, 13, 14, 17, 24], [18, 21, 23, 26, 30]]
    assert solution.searchMatrix(mx, 5) is True
    assert solution.searchMatrix(mx, 20) is False

    # ---- 矩阵中的最小值、最大值及范围之外 ----
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

    # ---- 重复值允许出现在同一行或同一列 ----
    assert solution.searchMatrix([[1, 2, 2], [2, 2, 4]], 4) is True
    assert solution.searchMatrix([[1, 2, 2], [2, 2, 4]], 3) is False


if __name__ == "__main__":
    test_solution()
    print("✅ No.240（HOT 100）全部测试通过")
