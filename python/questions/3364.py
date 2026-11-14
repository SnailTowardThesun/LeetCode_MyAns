"""
@file 3364.py
@brief LeetCode 3364. 最小正和子数组（Minimum Positive Sum Subarray）

@题目描述
    给你一个整数数组 nums 和两个整数 l 和 r。找到一个长度在 [l, r] 之间（含边界）
    且和大于 0 的子数组，返回其最小和；不存在这样的子数组返回 -1。
    子数组是数组中连续的非空序列。

@示例
    示例 1：
    输入：nums = [3,-2,1,4], l = 2, r = 3
    输出：1
    解释：长度 2 的子数组 [3,-2] 和为 1，是所有和为正的子数组中最小的。

    示例 2：
    输入：nums = [-2,2,-3,1], l = 2, r = 3
    输出：-1（所有长度 2/3 的子数组和都 <= 0）

    示例 3：
    输入：nums = [1,2,3,4], l = 2, r = 4
    输出：3（[1,2] 和为 3 最小）

    数据范围：
    1 <= nums.length <= 100
    -1000 <= nums[i] <= 1000
    1 <= l <= r <= nums.length

@解题思路
    枚举左端点 + 增量求和：
    1. 左端 i 从 0 到 n-l（保证长度 l 的窗口放得下）；
    2. 用生成器计算首个长度 l 的窗口和，不创建切片；左端移动时减去离开的值、
       加上进入的值，O(1) 更新基础窗口；再向右扩展到长度 r，每次只加新元素；
    3. 用 inf 作哨兵记录最小正和，0 < s < ret 链式比较一步完成
       「是正数且更小」的判定，最后哨兵未更新则返回 -1。

    时间复杂度 O(l + (n-l+1)*(r-l+1))，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/minimum-positive-sum-subarray/description/
"""

from math import inf


class Solution:
    def minimumSumSubarray(self, nums: list[int], l: int, r: int) -> int:  # noqa: E741  # l 保持 LeetCode 官方签名
        ret = inf
        n = len(nums)
        base = sum(nums[j] for j in range(l))
        for i in range(n - l + 1):
            # 基础窗口随左端滑动，之后从长度 l 扩到 r，全程不创建切片
            if i:
                base += nums[i + l - 1] - nums[i - 1]
            s = base
            if 0 < s < ret:
                ret = s
            for j in range(i + l, min(n, i + r)):
                s += nums[j]
                if 0 < s < ret:
                    ret = s

        return ret if ret < inf else -1


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：[3,-2] 和为 1 是最小正和 ----
    assert solution.minimumSumSubarray([3, -2, 1, 4], 2, 3) == 1

    # ---- 官方示例 2：所有合法长度子数组和都 <= 0 ----
    assert solution.minimumSumSubarray([-2, 2, -3, 1], 2, 3) == -1

    # ---- 官方示例 3：[1,2] 和为 3 ----
    assert solution.minimumSumSubarray([1, 2, 3, 4], 2, 4) == 3

    # ---- 最小规模：单元素正数 ----
    assert solution.minimumSumSubarray([5], 1, 1) == 5

    # ---- 单元素负数：无解 ----
    assert solution.minimumSumSubarray([-5], 1, 1) == -1

    # ---- l == r == n：整个数组是唯一候选 ----
    assert solution.minimumSumSubarray([2, -1, 2], 3, 3) == 3

    # ---- 和为 0 不算正数：[1,-1]=0 被跳过，[-1,2]=1 入选 ----
    assert solution.minimumSumSubarray([1, -1, 2], 2, 3) == 1

    # ---- 固定长度窗口的最小正和在末尾，检查基础窗口滑动 ----
    assert solution.minimumSumSubarray([10, -4, 3, -2], 2, 2) == 1

    # ---- 最优值来自扩展窗口，下一左端的基础和不应混入扩展部分 ----
    assert solution.minimumSumSubarray([4, -2, -1], 2, 3) == 1


if __name__ == "__main__":
    test_solution()
    print("✅ No.3364 全部测试通过")
