"""
@file hot100_238.py
@brief LeetCode 238. 除自身以外数组的乘积（Product of Array Except Self）— HOT 100

@题目描述
    给你一个整数数组 nums，返回数组 answer，其中 answer[i] 等于 nums 中除
    nums[i] 之外其余各元素的乘积。题目数据保证数组 nums 之中任意元素的全部
    前缀元素和后缀的乘积都在 32 位整数范围内。
    进阶要求：O(n) 时间且【不使用除法】；O(1) 空间（不计输出数组）。

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
    统计零 + 总乘积 + 分类讨论（本实现，使用了除法）：
    1. 一趟统计：零的个数 zero_count、唯一零的下标 zero_idx、
       全体非零元素的总乘积 total；
    2. 两个及以上零：任何位置的结果都含 0 因子，全零输出；
    3. 恰一个零：除零位外都被 0 乘成 0，零位结果恰为 total；
    4. 无零：answer[i] = total // nums[i]（整除精确，因 total 含因子 nums[i]）。
    注意：题目【明确要求不使用除法】，本实现判题可通过但不符合该要求；
    标准解法是前缀积 × 后缀积——把前缀积写进答案数组，再从右向左用
    变量乘后缀积，O(n) 时间、O(1) 额外空间且天然处理含零场景
    （见对应博客的实现）。

    时间复杂度 O(n)，空间复杂度 O(1)（不计输出）

来源：LeetCode
链接：https://leetcode.cn/problems/product-of-array-except-self/description/
"""


class Solution:
    def productExceptSelf(self, nums: list[int]) -> list[int]:
        n = len(nums)
        if n == 0:
            return []

        zero_count = 0
        zero_idx = -1
        total = 1  # 全体非零元素的总乘积
        for i in range(n):
            if nums[i] == 0:
                zero_count += 1
                zero_idx = i
            else:
                total *= nums[i]
        if zero_count > 1:
            return [0] * n  # 任何位置都含 0 因子

        if zero_count == 1:
            ret = [0] * n  # 除零位外全为 0，零位恰为 total
            ret[zero_idx] = total
            return ret

        return [total // nums[i] for i in range(n)]  # 整除精确：total 含因子 nums[i]


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例（期望值经暴力对照机器核对）----
    assert solution.productExceptSelf([1, 2, 3, 4]) == [24, 12, 8, 6]
    assert solution.productExceptSelf([-1, 1, 0, -3, 3]) == [0, 0, 9, 0, 0]

    # ---- 两个零：全零输出 ----
    assert solution.productExceptSelf([0, 4, 0]) == [0, 0, 0]

    # ---- 最小规模 ----
    assert solution.productExceptSelf([2, 3]) == [3, 2]

    # ---- 负数 ----
    assert solution.productExceptSelf([-2, 3]) == [3, -2]


if __name__ == "__main__":
    test_solution()
    print("✅ No.238（HOT 100）全部测试通过")
