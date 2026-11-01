"""
@file 453.py
@brief LeetCode 453. 最小操作次数使数组元素相等（Minimum Moves to Equal Array Elements）

@题目描述
    给你一个长度为 n 的整数数组 nums，每次操作将会使 n - 1 个元素增加 1。
    返回让数组所有元素相等的最小操作次数。

@示例
    示例 1：
    输入：nums = [1,2,3]
    输出：3
    解释：[1,2,3] => [2,3,3] => [3,4,3] => [4,4,4]（每次操作增加两个元素）。

    示例 2：
    输入：nums = [1,1,1]
    输出：0

    数据范围：
    n == nums.length
    1 <= n <= 10^5
    -10^9 <= nums[i] <= 10^9
    答案保证符合 32-bit 整数范围

@解题思路
    补集转化（逆向思维）。
    1. 每次「给 n-1 个元素 +1」等价于「给 1 个元素 -1」：两种操作对所有元素间差值的影响完全
       相同，最终全等的目标在两种视角下可互相换算，操作次数不变。
    2. 于是问题变为：每次选一个元素 -1，让全部相等的最少次数——最优是把所有数都降到最小值，
       答案 = sum(nums) - n * min(nums)。
    3. 溢出：sum 与 n*min 量级可达 10^5 * 10^9 = 10^14，远超 int32；官方只保证最终答案在
       32-bit 内，中间量必须用宽类型（C++ 用 long long；Python 天然大整数无此虑）。
    4. 可一次遍历同时求 sum 与 min。

    时间复杂度 O(n)，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/minimum-moves-to-equal-array-elements/description/
"""


class Solution:
    def minMoves(self, nums: list[int]) -> int:
        return sum(nums) - min(nums) * len(nums)


def test_solution() -> None:
    solution = Solution()
    # 官方示例
    assert solution.minMoves([1, 2, 3]) == 3  # 示例 1：三次操作后全等
    assert solution.minMoves([1, 1, 1]) == 0  # 示例 2：初始已全等
    # 边界：单元素 / 全相等
    assert solution.minMoves([5]) == 0  # n=1 时每次操作加 0 个元素，天然全等
    assert solution.minMoves([7, 7, 7, 7]) == 0
    # 负数（约束允许 -1e9）
    assert solution.minMoves([-1, -5]) == 4
    assert solution.minMoves([-5, -3, -1]) == 6
    # 小规模混合（期望值经 BFS 全状态枚举暴力验证）
    assert solution.minMoves([1, 2]) == 1
    assert solution.minMoves([1, 0, 2]) == 3
    assert solution.minMoves([5, 1, 3, 2]) == 7
    # 大值与溢出：三个 -1e9 的和为 -3e9，超出 int32——中间量必须用更宽类型计算，
    # 而最终答案 2000000000 仍在 int32 内（官方保证）
    assert solution.minMoves([1, 1000000000]) == 999999999
    assert solution.minMoves([-1000000000, 1000000000]) == 2000000000
    assert solution.minMoves([-1000000000, -1000000000, 1000000000]) == 2000000000


if __name__ == "__main__":
    test_solution()
    print("✅ No.453 全部测试通过")
