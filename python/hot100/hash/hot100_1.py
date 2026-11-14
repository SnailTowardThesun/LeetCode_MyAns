"""
@file hot100_1.py
@brief LeetCode 1. 两数之和（Two Sum）— HOT 100

@题目描述
    给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值
    target 的那两个整数，并返回它们的数组下标。你可以假设每种输入只会对应一个答案，
    但是数组中同一个元素在答案里不能重复出现。可以按任意顺序返回答案。

@示例
    示例 1：
    输入：nums = [2,7,11,15], target = 9
    输出：[0,1]
    解释：nums[0] + nums[1] == 9，返回 [0, 1]。

    示例 2：
    输入：nums = [3,2,4], target = 6
    输出：[1,2]

    示例 3：
    输入：nums = [3,3], target = 6
    输出：[0,1]（重复值各占一个下标，先查后插天然处理）

    数据范围：
    2 <= nums.length <= 1e4
    -1e9 <= nums[i] <= 1e9
    -1e9 <= target <= 1e9
    恰好存在一个有效答案

@解题思路
    一遍哈希表：
    1. 用哈希表 seen 记录「值 -> 下标」，遍历数组；
    2. 对每个 nums[i]，先查 target - nums[i] 是否已在表中——在则直接返回两个下标；
    3. 不在才把 nums[i] 插入。先查后插保证不会把当前元素和自己配对，
       且重复值（如 [3,3]）时第二个 3 能查到第一个 3 的下标；
    4. 暴力双循环 O(n^2)，哈希把「找配对」降为 O(1)，总 O(n)。

    时间复杂度 O(n)，空间复杂度 O(n)

来源：LeetCode
链接：https://leetcode.cn/problems/two-sum/description/
"""


class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        seen: dict[int, int] = {}  # 值 -> 下标
        for i, x in enumerate(nums):
            diff = target - x
            if diff in seen:  # 先查后插：天然处理重复值，也不会配到自己
                return [seen[diff], i]
            seen[x] = i
        return []


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1 ----
    assert solution.twoSum([2, 7, 11, 15], 9) == [0, 1]

    # ---- 官方示例 2：答案不在开头 ----
    assert solution.twoSum([3, 2, 4], 6) == [1, 2]

    # ---- 官方示例 3：重复值 ----
    assert solution.twoSum([3, 3], 6) == [0, 1]

    # ---- 最小规模 ----
    assert solution.twoSum([1, 2], 3) == [0, 1]

    # ---- 负数 ----
    assert solution.twoSum([-3, 4, 3, 90], 0) == [0, 2]


if __name__ == "__main__":
    test_solution()
    print("✅ No.1（HOT 100）全部测试通过")
