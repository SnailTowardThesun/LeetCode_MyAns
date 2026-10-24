"""
@file top150_53.py
@brief LeetCode 53. 最大子数组和

@题目描述
    给你一个整数数组 nums，请你找出一个具有最大和的连续子数组
    （子数组最少包含一个元素），返回其最大和。

@示例
    示例 1：
    输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
    输出：6
    解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。

    示例 2：
    输入：nums = [1]
    输出：1

    示例 3：
    输入：nums = [5,4,-1,7,8]
    输出：23

@解题思路
    动态规划（Kadane 的 dp 数组版）：
    1. 定义 dp[i] 为以 nums[i] 结尾的最大子数组和，只有两种选择——把 nums[i]
       接在前一个子数组后面（dp[i-1] + nums[i]），或另起炉灶从 nums[i] 单独
       开始（nums[i]），取较大者：dp[i] = max(nums[i], dp[i-1] + nums[i])；
    2. 前缀 dp[i-1] 为负时另起炉灶必然更优，即"拖后腿的前缀不如不要"；
    3. 最优子数组必然以某个下标结尾，故答案为 max(dp)；
    4. 初始化 dp[0] = nums[0] 而非 0——子数组至少含一个元素，全负数组的
       答案是最大的那个负数。

    时间复杂度 O(n)，空间复杂度 O(n)（dp 数组；dp[i] 只依赖 dp[i-1]，
    可用滚动变量优化到 O(1)，见同目录 README.md 标准版）

来源：LeetCode
链接：https://leetcode.cn/problems/maximum-subarray/description/
"""


class Solution:
    def maxSubArray(self, nums: list[int]) -> int:
        dp = [0] * len(nums)
        if len(nums) == 0:
            return 0
        dp[0] = nums[0]
        for i in range(1, len(nums)):
            if nums[i] > nums[i] + dp[i - 1]:
                dp[i] = nums[i]
            else:
                dp[i] = nums[i] + dp[i - 1]
        return max(dp)


def test_solution() -> None:
    solution = Solution()

    # 官方示例
    assert solution.maxSubArray([-2, 1, -3, 4, -1, 2, 1, -5, 4]) == 6
    assert solution.maxSubArray([1]) == 1
    assert solution.maxSubArray([5, 4, -1, 7, 8]) == 23

    # 边界：全负数组的答案是最大的那个负数；单负数元素
    assert solution.maxSubArray([-3, -1, -2]) == -1
    assert solution.maxSubArray([-5]) == -5


if __name__ == "__main__":
    test_solution()
    print("✅ 53 全部测试通过")
