"""
@file top150_120.py
@brief LeetCode 120. Triangle（三角形最小路径和）

@题目描述
    给定一个三角形 triangle ，找出自顶向下的最小路径和。
    每一步只能移动到下一行中相邻的结点上。更正式地说，如果你正位于当前行的下标 i
    （该行元素为 triangle[row][i]），那么下一步可以移动到下一行的下标 i 或 i + 1 处。
    返回自顶向下的最小路径和。

@示例
    示例 1：
    输入：triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
    输出：11
    解释：最小路径和为 2 + 3 + 5 + 1 = 11。

    示例 2：
    输入：triangle = [[-10]]
    输出：-10

    数据范围：
    1 <= triangle.length <= 200
    0 <= triangle[i].length < triangle.length
    -10^4 <= triangle[i][j] <= 10^4
    （进阶：仅使用 O(n) 额外空间，n 为三角形总行数）

@解题思路
    自顶向下逐行 DP：dp[i][j] = 到达 (i, j) 的最小路径和。
    1. 边界列：每行第 0 列只能来自上一行第 0 列（正上方）；第 i 行第 i 列只能来自
       上一行第 i-1 列（左上方）——三角形两腰只有一条来路。
    2. 中间列：dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]) + triangle[i][j]，
       从左上、正上两个前缀中取更优。
    3. 答案 = 最后一行所有 dp 值的最小值（终点可在底行任意位置）。
    备注：亦可自底向上滚动，把空间压到 O(n)——从倒数第二行往上
    dp[j] = min(dp[j], dp[j+1]) + triangle[i][j]，省去两腰的边界分支。

    时间复杂度 O(n^2)（n 为行数，元素总数 n(n+1)/2），空间复杂度 O(n^2)
"""


class Solution:
    def minimumTotal(self, triangle: list[list[int]]) -> int:
        n = len(triangle)
        dp = [[0] * i for i in range(1, n + 1)]
        for i in range(n):
            if i == 0:
                dp[0][0] = triangle[0][0]
                continue
            for j in range(i + 1):
                if j == 0:  # 左腰：只能来自正上方
                    dp[i][j] = dp[i - 1][j] + triangle[i][j]
                elif j == i:  # 右腰：只能来自左上方
                    dp[i][j] = dp[i - 1][j - 1] + triangle[i][j]
                else:  # 中间：取左上 / 正上较优
                    dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j]

        return min(dp[n - 1])


def test_solution() -> None:
    solution = Solution()
    # 官方示例
    assert solution.minimumTotal([[2], [3, 4], [6, 5, 7], [4, 1, 8, 3]]) == 11  # 2+3+5+1
    assert solution.minimumTotal([[-10]]) == -10
    # 边界：单行 / 两行
    assert solution.minimumTotal([[5]]) == 5
    assert solution.minimumTotal([[1], [2, 3]]) == 3
    # 反贪心：第二行先选小的 2 会得到 103，最优 102 恰在先选大的 100 那条路上
    assert solution.minimumTotal([[1], [2, 100], [100, 100, 1]]) == 102
    # 负数（约束允许 -10^4）：必须真取 min 而非初值 0 污染
    assert solution.minimumTotal([[-1], [-2, -3]]) == -4
    assert solution.minimumTotal([[1], [-5, -4]]) == -4
    # 全同值：任意路径等价
    assert solution.minimumTotal([[3], [3, 3], [3, 3, 3]]) == 9
    # 随机三角形（期望值经全路径 DFS 暴力验证）
    assert solution.minimumTotal([[1], [-7, 6], [8, -4, 3], [-6, -1, -9, -4]]) == -19


if __name__ == "__main__":
    test_solution()
    print("✅ No.120 全部测试通过")
