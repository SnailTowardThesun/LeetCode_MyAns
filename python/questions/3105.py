"""
@file 3105.py
@brief LeetCode 3105. 最长的严格递增或递减子数组（Longest Strictly Increasing or Strictly Decreasing Subarray）

@题目描述
    给你一个整数数组 nums，返回 nums 中最长「严格递增」或「严格递减」子数组的长度。
    子数组是数组中的一个连续元素序列。注意严格单调不允许相等：相邻元素相等时
    既不算递增也不算递减。

@示例
    示例 1：
    输入：nums = [1,4,3,3,2]
    输出：2
    解释：严格递增子数组 [1,4]、严格递减子数组 [4,3] 与 [3,2] 长度均为 2；
    [3,3] 因相等不算单调，故答案为 2。

    示例 2：
    输入：nums = [3,3,3,3]
    输出：1（任何相邻元素都相等，单个元素即最长单调子数组）

    示例 3：
    输入：nums = [3,2,1]
    输出：3（整个数组严格递减）

    数据范围：
    1 <= nums.length <= 50
    1 <= nums[i] <= 50

@解题思路
    一次遍历 + 游程计数（run-length）：
    1. 同时维护两个计数器：large 为以当前元素结尾的最长严格递增游程长度，
       small 为最长严格递减游程长度，ret 取全局最大；
    2. nums[i] > nums[i-1] 时 large++，否则（含相等）large 重置为 1；
       small 对称处理 nums[i] < nums[i-1] 的情形；
    3. 相等元素同时打断两条游程——这是「严格」二字的唯一坑点；
    4. 初始值均为 1（单个元素自成单调子数组），n == 1 时直接返回 1。

    时间复杂度 O(n)，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/description/
"""


class Solution:
    def longestMonotonicSubarray(self, nums: list[int]) -> int:
        ret = 1
        large, small = 1, 1
        for i in range(1, len(nums)):
            # 严格递增游程：相等也算打断
            if nums[i] > nums[i - 1]:
                large += 1
                ret = max(ret, large)
            else:
                large = 1

            # 严格递减游程：对称处理
            if nums[i] < nums[i - 1]:
                small += 1
                ret = max(ret, small)
            else:
                small = 1

        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：相等对打断两条游程，最长为 2 ----
    assert solution.longestMonotonicSubarray([1, 4, 3, 3, 2]) == 2

    # ---- 官方示例 2：全部相等，单个元素即最长 ----
    assert solution.longestMonotonicSubarray([3, 3, 3, 3]) == 1

    # ---- 官方示例 3：整个数组严格递减 ----
    assert solution.longestMonotonicSubarray([3, 2, 1]) == 3

    # ---- 最小规模：单元素 ----
    assert solution.longestMonotonicSubarray([5]) == 1

    # ---- 整体严格递增 ----
    assert solution.longestMonotonicSubarray([1, 2, 3, 4, 5]) == 5

    # ---- 山峰形：先增后减，两侧各取最长 ----
    assert solution.longestMonotonicSubarray([1, 3, 5, 4, 2]) == 3

    # ---- 混合形态：[1,2,3] 增 3 长与 [2,1] 减 2 长，答案 3 ----
    assert solution.longestMonotonicSubarray([1, 2, 3, 2, 2, 1]) == 3


if __name__ == "__main__":
    test_solution()
    print("✅ No.3105 全部测试通过")
