"""
@file 462.py
@brief LeetCode 462. 最小操作次数使数组元素相等 II（Minimum Moves to Equal Array Elements II）

@题目描述
    给你一个长度为 n 的整数数组 nums，返回使所有数组元素相等需要的最小操作数。
    在一次操作中，你可以使数组中的一个元素加 1 或者减 1。
    测试用例经过设计以使答案在 32 位整数范围内。

@示例
    示例 1：
    输入：nums = [1,2,3]
    输出：2
    解释：[1,2,3] => [2,2,3] => [2,2,2]，先将 1 加 1，再将 3 减 1。

    示例 2：
    输入：nums = [1,10,2,9]
    输出：16

    数据范围：
    n == nums.length
    1 <= n <= 10^5
    -10^9 <= nums[i] <= 10^9
    答案在 32 位整数范围内

@解题思路
    目标值取中位数：排序后取 nums[n//2]，答案 = 各元素到中位数的绝对偏差之和。
    1. 每次操作让一个元素 ±1，总代价 = 各元素到目标值的绝对偏差和；
    2. 绝对偏差和的最小点在中位数：目标每右移一格，右侧元素各省 1、左侧元素各费 1，
       跨过中位数后"费/省"关系翻转，故停在 n//2 处最优（偶数个元素时两中位之间任意点等价）；
    3. 均值最小化的是平方偏差而非绝对偏差，离群值会把它拉偏
       （[2,2,2,2,100] 朝均值走要 158 步，中位数路线 98 步）；
    4. 官方保证答案在 int32 内，Python 大整数无溢出之虞。

    时间复杂度 O(n log n)（排序），空间复杂度 O(1)（原地排序）

来源：LeetCode
链接：https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/description/
"""


class Solution:
    def minMoves2(self, nums: list[int]) -> int:
        nums.sort()
        mid = nums[len(nums) // 2]
        return sum(abs(i - mid) for i in nums)


def test_solution() -> None:
    solution = Solution()
    # 官方示例
    assert solution.minMoves2([1, 2, 3]) == 2  # 示例 1：1 加 1、3 减 1
    assert solution.minMoves2([1, 10, 2, 9]) == 16  # 示例 2
    # 边界：单元素 / 全相等（零成本）
    assert solution.minMoves2([5]) == 0
    assert solution.minMoves2([7, 7, 7]) == 0
    # 两个元素：中间任意点相遇
    assert solution.minMoves2([1, 9]) == 8
    # 偶数个元素：两个中位之间任意目标等价
    assert solution.minMoves2([1, 2, 4, 5]) == 6
    # 陷阱：离群值会把均值拉偏——朝均值靠拢要 158 步，正确答案 98
    assert solution.minMoves2([2, 2, 2, 2, 100]) == 98
    # 负数与小规模混合（期望值经枚举目标值暴力验证）
    assert solution.minMoves2([1, 0, 0, 8, 6]) == 14
    assert solution.minMoves2([-5, -1, -3]) == 4
    # 大值：答案贴近 int32 上界（官方保证答案在 32 位内，中间求和需注意宽度）
    assert solution.minMoves2([-1000000000, 1000000000]) == 2000000000
    assert solution.minMoves2([-1000000000, -1000000000, 1000000000]) == 2000000000
    assert solution.minMoves2([999999999, -999999999, 0]) == 1999999998


if __name__ == "__main__":
    test_solution()
    print("✅ No.462 全部测试通过")
