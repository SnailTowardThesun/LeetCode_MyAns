"""
@file top150_918.py
@brief LeetCode 918. 环形子数组的最大和

@题目描述
    给定一个长度为 n 的环形整数数组 nums，返回 nums 的非空子数组的最大可能和。
    环形数组意味着数组的末端将会与开头相连呈环状。形式上，nums[i] 的下一个元素是
    nums[(i + 1) % n]，nums[i] 的前一个元素是 nums[(i - 1 + n) % n]。
    子数组最多只能包含固定缓冲区 nums 中的每个元素一次。

@示例
    示例 1：
    输入：nums = [1,-2,3,-2]
    输出：3
    解释：从子数组 [3] 得到最大和 3

    示例 2：
    输入：nums = [5,-3,5]
    输出：10
    解释：从子数组 [5,5] 得到最大和 10

    示例 3：
    输入：nums = [-3,-2,-3]
    输出：-2
    解释：从子数组 [-2] 得到最大和 -2

@解题思路
    环形子数组只有两种形态，分别求最大再取较大值：
    1. 不跨环：就是普通的最大子数组和，用 Kadane 一趟求出 best_max；
    2. 跨环：子数组由"后缀 + 前缀"拼成，它的补集是中间一段连续的不跨环子数组，
       所以跨环最大和 = 总和 total − 最小子数组和 best_min（把 Kadane 的 max 换成 min 即可求出）；
    3. 边界：全为负数时 best_min 就是整个数组，total − best_min = 0 对应空子数组，
       题目要求非空，此时直接返回 best_max（即最大的那个负数）。
    best_max、best_min、total 三个量可以在同一次遍历中滚动维护，只需常数个变量。

    时间复杂度 O(n)，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/maximum-sum-circular-subarray/description/
"""

import random


class Solution:
    def maxSubarraySumCircular(self, nums: list[int]) -> int:
        # cur_max / cur_min：以当前元素结尾的最大 / 最小子数组和（Kadane 滚动变量）
        cur_max = best_max = cur_min = best_min = total = nums[0]
        for x in nums[1:]:
            cur_max = max(x, cur_max + x)
            best_max = max(best_max, cur_max)
            cur_min = min(x, cur_min + x)
            best_min = min(best_min, cur_min)
            total += x

        # 全负时 total − best_min == 0 对应空子数组，题目要求非空，只能取不跨环的 best_max
        if best_max < 0:
            return best_max
        return max(best_max, total - best_min)


def _brute_answer(nums: list[int]) -> int:
    """O(n^2) 暴力：枚举环上每个起点、长度 1..n 的所有子数组，作为对拍真值。"""
    n = len(nums)
    best = nums[0]
    for start in range(n):
        acc = 0
        for length in range(1, n + 1):
            acc += nums[(start + length - 1) % n]
            best = max(best, acc)
    return best


def test_max_subarray_sum_circular() -> None:
    s = Solution()

    # ---- 官方示例 ----
    assert s.maxSubarraySumCircular([1, -2, 3, -2]) == 3  # 不跨环，子数组 [3]
    assert s.maxSubarraySumCircular([5, -3, 5]) == 10  # 跨环，子数组 [5,5]
    assert s.maxSubarraySumCircular([-3, -2, -3]) == -2  # 全负，取最大的单个元素

    # ---- 单元素 ----
    assert s.maxSubarraySumCircular([5]) == 5
    assert s.maxSubarraySumCircular([-7]) == -7
    assert s.maxSubarraySumCircular([0]) == 0

    # ---- 全正：答案即整个数组之和 ----
    assert s.maxSubarraySumCircular([1, 2, 3, 4]) == 10

    # ---- 全负（陷阱：总和 − 最小子数组和 = 0 对应空子数组，不能取）----
    assert s.maxSubarraySumCircular([-2, -3, -1]) == -1
    assert s.maxSubarraySumCircular([-5, -1, -8, -9]) == -1

    # ---- 答案必须跨环 ----
    assert s.maxSubarraySumCircular([8, -1, 3, 4]) == 15  # 3+4+8，绕过中间的 -1
    assert s.maxSubarraySumCircular([2, -2, 2, -2, 2]) == 4  # 首尾两个 2 相接
    assert s.maxSubarraySumCircular([-2, 4, -5, 4, -5, 9, 4]) == 15  # 去掉中段 [-5,4,-5]，剩余 9+4-2+4

    # ---- 不跨环与跨环结果相同 ----
    assert s.maxSubarraySumCircular([3, -1, 2, -1]) == 4  # [3,-1,2] 与 [2,-1,3] 均为 4

    # ---- 含 0：答案为 0 而非负数 ----
    assert s.maxSubarraySumCircular([-1, 0, -1]) == 0

    # ---- 题目上限 n = 3·10^4、|nums[i]| ≤ 3·10^4，同时作为 O(n) 的冒烟检查 ----
    assert s.maxSubarraySumCircular([30000] * 30000) == 900_000_000
    assert s.maxSubarraySumCircular([-30000] * 30000) == -30000

    # ---- 随机对拍：与 O(n^2) 暴力真值对照 ----
    random.seed(42)
    for _ in range(300):
        n = random.randint(1, 8)
        nums = [random.randint(-10, 10) for _ in range(n)]
        want = _brute_answer(nums)
        got = s.maxSubarraySumCircular(nums)
        assert got == want, f"nums={nums}: got {got}, want {want}"


if __name__ == "__main__":
    test_max_subarray_sum_circular()
    print("✅ 918 全部测试通过")
