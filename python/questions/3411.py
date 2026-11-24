"""
@file 3411.py
@brief LeetCode 3411. 最长乘积等价子数组（Maximum Subarray With Equal Products）

@题目描述
    在正整数数组 nums 中，求满足「元素乘积 = 最大公因数 × 最小公倍数」的最长连续子数组长度。
    数组长度在 2 到 100 之间，每个元素在 1 到 10 之间。

@示例
    [1, 2, 1, 2, 1, 1, 1] 返回 5，末尾的 [1, 2, 1, 1, 1] 满足等式。
    [2, 3, 4, 5, 6] 返回 3，对应 [3, 4, 5]。
    [1, 2, 3, 1, 4, 5, 1] 返回 5。

@解题思路
    任意两个正整数都满足 a * b = gcd(a, b) * lcm(a, b)，所以答案至少为 2。
    固定左端点，向右逐个纳入元素，同步更新区间的乘积、最大公因数和最小公倍数。
    每次等式成立时，用当前区间长度更新答案。
    共检查 n(n-1)/2 个区间，按常数时间整数运算计，时间 O(n²)，使用常数个变量。
    Python 精确保存乘积；在元素不超过 10 的条件下，乘积最多占 O(n) 位。
"""

from math import gcd, lcm


class Solution:
    def maxLength(self, nums: list[int]) -> int:
        best = 2
        for left, first in enumerate(nums):
            product = divisor = multiple = first
            for right in range(left + 1, len(nums)):
                value = nums[right]
                product *= value
                divisor = gcd(divisor, value)
                multiple = lcm(multiple, value)
                if product == divisor * multiple:
                    best = max(best, right - left + 1)
        return best


def test_solution() -> None:
    cases = [
        ([1, 2, 1, 2, 1, 1, 1], 5),
        ([2, 3, 4, 5, 6], 3),
        ([1, 2, 3, 1, 4, 5, 1], 5),
        ([6, 6], 2),  # 两个数即使有公共因数，也必定满足等式
        ([4, 9, 5, 7], 4),  # 整段两两互质
        ([1] * 100, 100),
        ([10] * 100, 2),  # 长区间乘积很大，但只有长度为 2 的区间满足等式
    ]
    solution = Solution()
    for nums, expected in cases:
        assert solution.maxLength(nums) == expected, nums


if __name__ == "__main__":
    test_solution()
