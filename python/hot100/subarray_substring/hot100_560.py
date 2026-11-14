"""
@file hot100_560.py
@brief LeetCode 560. 和为 K 的子数组（Subarray Sum Equals K）— HOT 100

@题目描述
    给你一个整数数组 nums 和一个整数 k，请你统计并返回该数组中和为 k 的连续
    非空子数组的个数。

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
    2. 顺序扫描每个非空前缀的和值 s[j]：先累加「之前出现过多少个 s[j]-k」（它们各自对应
       一段和为 k 的子数组），再把 s[j] 计入哈希表——先查后加保证 i < j，
       k = 0 时不会把自己配给自己；
    3. 用 prefix 滚动维护当前前缀和，cnt 初始为 {0: 1}，代表空前缀。
       查询使用 get，未出现的和值按 0 次处理，不为它创建无效条目。

    为什么不能按和值收缩窗口：nums 含负数，窗口和没有单调性，右扩不一定增大——
    常规的「和大于 k 就收缩」无法保证正确，前缀和 + 哈希不依赖这种单调性。

    平均时间复杂度 O(n)，辅助空间复杂度 O(n)

来源：LeetCode
链接：https://leetcode.cn/problems/subarray-sum-equals-k/description/
"""


class Solution:
    def subarraySum(self, nums: list[int], k: int) -> int:
        ret = 0
        prefix = 0
        cnt = {0: 1}  # 空前缀，让从下标 0 开始的子数组也能被计数
        for x in nums:
            prefix += x
            # 先查询历史前缀，再记录当前前缀，保证子数组非空
            ret += cnt.get(prefix - k, 0)
            cnt[prefix] = cnt.get(prefix, 0) + 1
        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.subarraySum([1, 1, 1], 2) == 2
    assert solution.subarraySum([1, 2, 3], 3) == 2

    # ---- k = 0 陷阱：先查后加不自配；全零数组的每一段都算 ----
    assert solution.subarraySum([-1, -1, 1], 0) == 1
    assert solution.subarraySum([0, 0, 0], 0) == 6

    # ---- 负数数组：不能按和值收缩窗口，前缀和可解 ----
    assert solution.subarraySum([1, -1, 1, -1], 0) == 4

    # ---- 整个数组恰为一段 ----
    assert solution.subarraySum([3], 3) == 1

    # ---- 无解 ----
    assert solution.subarraySum([1, 2, 3], 7) == 0

    # ---- 负目标值与重复前缀：不能只记录某个前缀是否出现 ----
    assert solution.subarraySum([-1, -1, 1], -1) == 3
    assert solution.subarraySum([0], 0) == 1
    assert solution.subarraySum([1], 0) == 0

    # ---- 最大规模全零：每个非空子数组都有效 ----
    assert solution.subarraySum([0] * 20000, 0) == 20000 * 20001 // 2


if __name__ == "__main__":
    test_solution()
    print("✅ No.560（HOT 100）全部测试通过")
