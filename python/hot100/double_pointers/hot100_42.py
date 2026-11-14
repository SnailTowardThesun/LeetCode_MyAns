"""
@file hot100_42.py
@brief LeetCode 42. 接雨水（Trapping Rain Water）— HOT 100

@题目描述
    给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，
    计算按此排列的柱子，下雨之后能接多少雨水。

@示例
    示例 1：
    输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
    输出：6

    示例 2：
    输入：height = [4,2,0,3,2,5]
    输出：9

    数据范围：
    n == height.length
    1 <= n <= 2 * 1e4
    0 <= height[i] <= 1e5

@解题思路
    前后缀最大值（逐列结算）：
    1. 每列能存的水 = min(左侧最高柱, 右侧最高柱) - 自身高度（负数则该列存不住）；
    2. 预处理两个数组：leftmax[i] = max(height[0..i]) 从左向右递推，
       rightmax[i] = max(height[i..n-1]) 从右向左递推，各一趟 O(n)；
    3. 再一趟求和 min(leftmax[i], rightmax[i]) - height[i]。
    2 的正确性：一列的水位由「两侧最高墙的较矮者」决定——超过它就会从那侧溢出，
    低于柱顶的部分被柱子占据。

    时间复杂度 O(n)（三趟线性扫描），空间复杂度 O(n)（两个辅助数组）
    进阶：对撞双指针维护实时 leftmax/rightmax 可把空间降到 O(1)——
    指针每次移动较矮一侧，较矮侧的水位由同侧前缀最大值独立确定，无需数组。

来源：LeetCode
链接：https://leetcode.cn/problems/trapping-rain-water/description/
"""


class Solution:
    def trap(self, height: list[int]) -> int:
        n = len(height)

        # leftmax[i] = height[0..i] 的最大值（含自身），从左向右递推
        leftmax = [0] * n
        leftmax[0] = height[0]
        for i in range(1, n):
            leftmax[i] = max(leftmax[i - 1], height[i])

        # rightmax[i] = height[i..n-1] 的最大值（含自身），从右向左递推
        rightmax = [0] * n
        rightmax[n - 1] = height[n - 1]
        for i in range(n - 2, -1, -1):
            rightmax[i] = max(rightmax[i + 1], height[i])

        # 每列水位 = min(两侧最高墙) - 柱高，负数说明自身就是墙，存不住水
        return sum(min(leftmax[i], rightmax[i]) - height[i] for i in range(n))


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1 ----
    assert solution.trap([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]) == 6

    # ---- 官方示例 2 ----
    assert solution.trap([4, 2, 0, 3, 2, 5]) == 9

    # ---- 最小可存水单元：两侧夹一根矮柱 ----
    assert solution.trap([1, 0, 1]) == 1

    # ---- 碗形：中间低四周高 ----
    assert solution.trap([3, 2, 1, 2, 3]) == 4

    # ---- 单调（升/降）存不住水 ----
    assert solution.trap([1, 2, 3, 4]) == 0
    assert solution.trap([4, 3, 2, 1]) == 0

    # ---- 边界：单柱 / 双柱 ----
    assert solution.trap([5]) == 0
    assert solution.trap([2, 5]) == 0


if __name__ == "__main__":
    test_solution()
    print("✅ No.42（HOT 100）全部测试通过")
