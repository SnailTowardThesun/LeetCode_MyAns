"""
@file 42.py
@brief LeetCode 42. 接雨水（Trapping Rain Water）

@题目描述
    给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，
    计算按此排列的柱子，下雨之后能接多少雨水。

@示例
    示例 1：
    输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
    输出：6
    解释：在这种情况下，可以接 6 个单位的雨水。

@解题思路
    1. 按列计算：每个位置能接的水 = min(左边最高, 右边最高) - 当前高度
    2. 预处理 leftmax / rightmax 两个数组：leftmax[i] 为 [0..i] 的最大高度，
       rightmax[i] 为 [i..n-1] 的最大高度
    3. 线性扫描累加每个位置的接水量

    时间复杂度 O(n)，空间复杂度 O(n)
"""


class Solution:
    def trap(self, height: list[int]) -> int:
        n = len(height)
        leftmax = [0] * n
        leftmax[0] = height[0]
        for i in range(1, n):
            leftmax[i] = max(height[i], leftmax[i-1])
        rightmax = [0] * n
        rightmax[n-1] = height[n-1]

        for i in range(n-2, -1, -1):
            rightmax[i] = max(height[i], rightmax[i+1])
        ret = 0
        for i in range(n):
            ret += min(leftmax[i], rightmax[i]) - height[i]
        return ret

if __name__ == '__main__':
    s = Solution()
    ret = s.trap([0,1,0,2,1,0,1,3,2,1,2,1])
    print(ret)


def test_solution() -> None:
    solution = Solution()

    # 官方示例
    assert solution.trap([0,1,0,2,1,0,1,3,2,1,2,1]) == 6
    assert solution.trap([4,2,0,3,2,5]) == 9

    # 边界：单调 / 平地不积水
    assert solution.trap([3,2,1,0]) == 0
    assert solution.trap([2,2,2]) == 0
    assert solution.trap([5]) == 0
