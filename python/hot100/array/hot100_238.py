"""
@file hot100_238.py
@brief LeetCode 238. 除自身以外数组的乘积（Product of Array Except Self）— HOT 100

@题目描述
    给你一个整数数组 nums，返回数组 answer，其中 answer[i] 等于 nums 中除
    nums[i] 之外其余各元素的乘积。题目数据保证数组 nums 之中任意元素的全部
    前缀元素和后缀的乘积都在 32 位整数范围内。
    要求 O(n) 时间且不使用除法；进阶要求 O(1) 额外空间（不计输出数组）。

@示例
    示例 1：
    输入：nums = [1,2,3,4]
    输出：[24,12,8,6]

    示例 2：
    输入：nums = [-1,1,0,-3,3]
    输出：[0,0,9,0,0]

    数据范围：
    2 <= nums.length <= 1e5

@解题思路
    前缀积 × 后缀积：
    1. 从左到右，把位置 i 左侧元素的乘积写入 ret[i]，不包含 nums[i]；
    2. 从右到左，用变量 right 维护位置 i 右侧元素的乘积，再乘入 ret[i]；
    3. 每次先使用累积乘积，再乘当前元素，保证不把自身计入答案。
    空前缀、空后缀的乘积均为 1；含零情况由乘法自然处理，无需分类讨论。

    时间复杂度 O(n)，空间复杂度 O(1)（不计输出）

来源：LeetCode
链接：https://leetcode.cn/problems/product-of-array-except-self/description/
"""


class Solution:
    def productExceptSelf(self, nums: list[int]) -> list[int]:
        n = len(nums)
        ret = [1] * n

        left = 1  # 位置 i 左侧全体元素之积（不含自身）
        for i in range(n):
            ret[i] = left
            left *= nums[i]

        right = 1  # 位置 i 右侧全体元素之积（不含自身）
        for i in range(n - 1, -1, -1):
            ret[i] *= right
            right *= nums[i]

        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例（期望值经暴力对照机器核对）----
    assert solution.productExceptSelf([1, 2, 3, 4]) == [24, 12, 8, 6]
    assert solution.productExceptSelf([-1, 1, 0, -3, 3]) == [0, 0, 9, 0, 0]

    # ---- 两个零：全零输出 ----
    assert solution.productExceptSelf([0, 4, 0]) == [0, 0, 0]

    # ---- 唯一的零位于首端或末端，检验空前缀与空后缀 ----
    assert solution.productExceptSelf([0, 2, 3]) == [6, 0, 0]
    assert solution.productExceptSelf([2, 3, 0]) == [0, 0, 6]

    # ---- 最小规模 ----
    assert solution.productExceptSelf([2, 3]) == [3, 2]

    # ---- 负数 ----
    assert solution.productExceptSelf([-2, 3]) == [3, -2]


if __name__ == "__main__":
    test_solution()
    print("✅ No.238（HOT 100）全部测试通过")
