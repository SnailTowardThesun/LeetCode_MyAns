"""
@file hot100_53.py
@brief LeetCode 53. 最大子数组和（Maximum Subarray）— HOT 100

@题目描述
    给你一个整数数组 nums，请你找出一个具有最大和的连续子数组（子数组至少
    包含一个元素），返回其最大和。

@示例
    示例 1：
    输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
    输出：6
    解释：连续子数组 [4,-1,2,1] 的和最大，为 6。

    示例 2：
    输入：nums = [1]
    输出：1

    示例 3：
    输入：nums = [5,4,-1,7,8]
    输出：23

    数据范围：
    1 <= nums.length <= 1e5
    -1e4 <= nums[i] <= 1e4

@解题思路
    Kadane 动态规划（dp 数组版）：
    1. dp[i] = 以 nums[i] 结尾的最大子数组和；
    2. 转移：dp[i] = max(nums[i], dp[i-1] + nums[i])——
       之前的段和为正时接上有益（dp[i-1] + nums[i] 更大），
       为负时是拖累，当前元素单独成段更优（nums[i] 更大）；
    3. 答案是所有 dp[i] 的最大值（最优子数组以某个位置结尾）；
    4. 进阶：dp[i] 只依赖 dp[i-1]，可滚动成一个变量 local，
       边扫边更新 global，空间降到 O(1)（对应 C++ 版写法）；
    5. 全负数组也正确：max(dp) 至少选中最大的单个元素。

    时间复杂度 O(n)，空间复杂度 O(n)（滚动后 O(1)）

来源：LeetCode
链接：https://leetcode.cn/problems/maximum-subarray/description/
"""


class Solution:
    def maxSubArray(self, nums: list[int]) -> int:
        n = len(nums)
        dp = [0] * n
        dp[0] = nums[0]
        for i in range(1, n):
            # 接上前段（dp[i-1] > 0 时有益）还是单独成段，取较大者
            if nums[i] > nums[i] + dp[i - 1]:
                dp[i] = nums[i]
            else:
                dp[i] = nums[i] + dp[i - 1]
        return max(dp)


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.maxSubArray([-2, 1, -3, 4, -1, 2, 1, -5, 4]) == 6
    assert solution.maxSubArray([1]) == 1
    assert solution.maxSubArray([5, 4, -1, 7, 8]) == 23

    # ---- 全负数组：必须选至少一个元素，答案是最大单元素 ----
    assert solution.maxSubArray([-1]) == -1
    assert solution.maxSubArray([-2, -1]) == -1

    # ---- 负数在中间被两侧正段跨越 ----
    assert solution.maxSubArray([1, -2, 3]) == 3
    assert solution.maxSubArray([2, -1, 2]) == 3


if __name__ == "__main__":
    test_solution()
    print("✅ No.53（HOT 100）全部测试通过")
