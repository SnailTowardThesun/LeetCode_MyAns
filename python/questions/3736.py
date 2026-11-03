"""
@file 3736.py
@brief LeetCode 3736. 最小操作次数使数组元素相等 III（Minimum Moves to Equal Array Elements III）

@题目描述
    给你一个整数数组 nums。一步操作中，你可以将任意单个元素 nums[i] 的值增加 1。
    返回使数组中所有元素相等所需的最小总操作次数。

@示例
    示例 1：
    输入：nums = [2,1,3]
    输出：3
    解释：将 nums[0] 从 2 增到 3（1 次），再将 nums[1] 从 1 增到 3（2 次），
    最终所有元素均为 3。

    示例 2：
    输入：nums = [4,4,5]
    输出：2
    解释：两个 4 各增加 1 变为 5，共 2 次操作。

    数据范围：
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

@解题思路
    全部补齐到最大值：答案 = sum(max - nums[i])。
    1. 操作只能 +1 不能减，公共目标值 V 必须 >= 每个元素（大元素降不下去），
       即 V >= max；
    2. 每步操作使数组总和恰好增加 1，故总操作数 = n*V - sum，随 V 严格递增；
    3. V 取最小可行值 max 最优，答案 = sum(max - nums[i])——
       每个元素到 max 的缺口就是它各自需要的操作次数，缺口之和即总次数；
    4. 系列对比：453（n-1 个元素 +1）补集转化等价于单元素 -1，目标锁死在 min，
       答案 sum - n*min；462（单元素 ±1）目标自由选，聚拢到中位数；
       本题单元素只能 +1，目标顶到 max。同一题面家族，操作规则一字之差。

    时间复杂度 O(n)（求 max 与求和各一遍），空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-iii/description/
"""


class Solution:
    def minMoves(self, nums: list[int]) -> int:
        mm = max(nums)
        return sum((mm - i) for i in nums)


def test_solution() -> None:
    solution = Solution()
    # 官方示例
    assert solution.minMoves([2, 1, 3]) == 3  # 示例 1：2→3 一次、1→3 两次
    assert solution.minMoves([4, 4, 5]) == 2  # 示例 2：两个 4 各 +1
    # 边界：单元素 / 全相等（零成本）
    assert solution.minMoves([1]) == 0
    assert solution.minMoves([7, 7, 7]) == 0
    # 最大值在头部/尾部不影响结果
    assert solution.minMoves([100, 1]) == 99
    assert solution.minMoves([1, 100]) == 99
    # 多个最小值同时补齐：三个 1 各缺 99
    assert solution.minMoves([1, 1, 1, 100]) == 297
    # 多个最大值：缺口全在较小元素上
    assert solution.minMoves([5, 5, 3]) == 2
    # 无序小数组
    assert solution.minMoves([3, 1, 2]) == 3
    # 规模上界：99 个 1 + 1 个 100，答案 99*(100-1)=9801
    assert solution.minMoves([1] * 99 + [100]) == 9801
    # 满值域小数组
    assert solution.minMoves(list(range(1, 101))) == sum(range(100))  # 缺口 99+98+...+0


if __name__ == "__main__":
    test_solution()
    print("✅ No.3736 全部测试通过")
