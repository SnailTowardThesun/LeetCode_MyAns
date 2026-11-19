"""
@file 2567.py
@brief LeetCode 2567. 修改两个元素后的最小分数（Minimum Score by Changing Two Elements）

@题目描述
    给你一个整数数组 nums。在所有不同下标的元素对中，最小绝对差为低分，
    最大绝对差为高分，数组分数是低分与高分之和。
    将两个位置的元素改为任意整数，返回修改后能得到的最小分数。

@示例
    示例 1：
    输入：nums = [1,4,3]
    输出：0
    解释：把 1 和 4 改成 3，高分和低分均为 0。

    示例 2：
    输入：nums = [1,4,7,8,5]
    输出：3
    解释：把 1 和 4 改成 6，低分为 0，高分为 8-5 = 3。

    数据范围：
    3 <= nums.length <= 1e5
    1 <= nums[i] <= 1e9

@解题思路
    排序 + 三种删法取最小：
    1. 固定要改的两个位置。高分至少是保留元素的极差，低分至少为 0。
    2. 把两个位置都改成保留值域内的同一个数，低分为 0，高分等于保留元素的极差，
       因此只需最小化保留元素的极差。
    3. 排序后，任取 n-2 个保留元素，其覆盖范围至少包含一个长度为 n-2 的连续窗口。
       三个候选窗口分别对应：
       - 删最大的两个：极差 nums[n-3] - nums[0]
       - 删最大和最小：极差 nums[n-2] - nums[1]
       - 删最小的两个：极差 nums[n-1] - nums[2]

    时间复杂度 O(n log n)，CPython 排序最坏使用 O(n) 额外空间。

来源：LeetCode
链接：https://leetcode.cn/problems/minimum-score-by-changing-two-elements/description/
"""


class Solution:
    def minimizeSum(self, nums: list[int]) -> int:
        nums.sort()
        # 三种删法：删两个最大 / 删一大一最小 / 删两个最小
        return min(nums[-3] - nums[0], nums[-2] - nums[1], nums[-1] - nums[2])


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.minimizeSum([1, 4, 3]) == 0
    assert solution.minimizeSum([1, 4, 7, 8, 5]) == 3

    # ---- 全相等：极差本就是 0 ----
    assert solution.minimizeSum([1, 1, 1, 1]) == 0

    # ---- 最小规模 n=3：必可全改成同一个值，答案恒 0 ----
    assert solution.minimizeSum([1, 2, 3]) == 0

    # ---- n=4：只保留两个相邻值 ----
    assert solution.minimizeSum([1, 2, 3, 4]) == 1

    # ---- 三种端点组合分别是唯一最优解 ----
    assert solution.minimizeSum([1, 2, 3, 10, 20]) == 2
    assert solution.minimizeSum([1, 10, 11, 12, 100]) == 2
    assert solution.minimizeSum([1, 10, 20, 21, 22]) == 2


if __name__ == "__main__":
    test_solution()
    print("✅ No.2567 全部测试通过")
