"""
@file hot100_560.py
@brief LeetCode 560. 和为 K 的子数组（Subarray Sum Equals K）— HOT 100

@题目描述
    给你一个整数数组 nums 和一个整数 k，请你统计并返回该数组中和为 k 的连续
    子数组的个数。

@示例
    示例 1：
    输入：nums = [1,1,1], k = 2
    输出：2

    示例 2：
    输入：nums = [1,2,3], k = 3
    输出：2

    数据范围：
    1 <= nums.length <= 2 * 1e4
    -1000 <= nums[i] <= 1000
    -1e7 <= k <= 1e7

@解题思路
    前缀和 + 哈希计数：
    1. 子数组 nums[i..j-1] 的和 = 前缀和 s[j] - s[i]（s[0] = 0，长度 n+1），
       「和为 k」即找满足 s[i] == s[j] - k 的 i < j；
    2. 顺序扫描每个前缀和 j：先累加「之前出现过多少个 s[j]-k」（它们各自对应
       一段和为 k 的子数组），再把 s[j] 计入哈希表——先查后加保证 i < j，
       k = 0 时不会把自己配给自己；
    3. 前缀和数组一趟预处理，计数一趟扫描，两趟分离写法直观；
       也可边扫边算前缀和一趟完成（省 O(n) 数组）。

    为什么不能滑动窗口：nums 含负数，窗口和没有单调性，右扩不一定增大——
    滑窗失效，前缀和 + 哈希是本题的标准解法。

    时间复杂度 O(n)，空间复杂度 O(n)

来源：LeetCode
链接：https://leetcode.cn/problems/subarray-sum-equals-k/description/
"""

from collections import defaultdict


class Solution:
    def subarraySum(self, nums: list[int], k: int) -> int:
        # 前缀和 s[j] = nums[0..j-1] 之和，s[0] = 0
        s = [0] * (len(nums) + 1)
        for i, x in enumerate(nums):
            s[i + 1] = s[i] + x

        ret = 0
        cnt: defaultdict[int, int] = defaultdict(int)  # 前缀和 -> 出现次数
        for j in s:
            # 先查后加：cnt[s[j]-k] 是「起点侧」满足 s[i] = s[j]-k 的 i 个数，
            # 每个 i 对应一段和为 k 的子数组；顺序保证 i < j，k=0 时不自配
            ret += cnt[j - k]
            cnt[j] += 1
        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.subarraySum([1, 1, 1], 2) == 2
    assert solution.subarraySum([1, 2, 3], 3) == 2

    # ---- k = 0 陷阱：先查后加不自配；全零数组的每一段都算 ----
    assert solution.subarraySum([-1, -1, 1], 0) == 1
    assert solution.subarraySum([0, 0, 0], 0) == 6

    # ---- 负数数组：滑窗失效、前缀和可解的场景 ----
    assert solution.subarraySum([1, -1, 1, -1], 0) == 4

    # ---- 整个数组恰为一段 ----
    assert solution.subarraySum([3], 3) == 1

    # ---- 无解 ----
    assert solution.subarraySum([1, 2, 3], 7) == 0


if __name__ == "__main__":
    test_solution()
    print("✅ No.560（HOT 100）全部测试通过")
