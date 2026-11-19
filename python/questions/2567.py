"""
@file 2567.py
@brief LeetCode 2567. 修改两个元素后的最小分数（Minimum Score by Changing Two Elements）

@题目描述
    给你一个下标从 0 开始的整数数组 nums。nums 的分数是 nums 中最大元素和
    最小元素的差值。你需要恰好修改两个元素（可以改成任意值，包括当前已有的值），
    返回修改后 nums 的最小分数。
    注意：n >= 3，修改后数组大小不变。

@示例
    示例 1：
    输入：nums = [1,4,3]
    输出：0
    解释：把 1 和 4 改成 3，数组全为 3，极差 0。

    示例 2：
    输入：nums = [1,4,7,8,5]
    输出：3
    解释：把 8 和 1 改成 5，数组为 [5,4,7,5,5]，极差 7-4 = 3。

    数据范围：
    3 <= nums.length <= 1e5
    1 <= nums[i] <= 1e9

@解题思路
    排序 + 三种删法取最小：
    1. 关键转化：把元素改成「保留元素中的某个值」最优（改小/改大都不如贴住
       保留值的边界），于是问题等价于「删掉恰好两个元素，最小化剩余极差」；
    2. 删两个元素使极差最小，最优方案必是三种之一（排序后）：
       - 删最大的两个：极差 nums[n-3] - nums[0]
       - 删最大和最小：极差 nums[n-2] - nums[1]
       - 删最小的两个：极差 nums[n-1] - nums[2]
       （任何「删中间元素」的方案不会更优——中间元素不影响 min/max）
    3. 三者取最小即为答案。

    时间复杂度 O(n log n)（排序主导），空间复杂度 O(1)

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
    assert solution.minimizeSum([1, 1, 1]) == 0

    # ---- 最小规模 n=3：必可全改成同一个值，答案恒 0 ----
    assert solution.minimizeSum([1, 2, 3]) == 0

    # ---- n=4（期望值由暴力对照机器算出）----
    assert solution.minimizeSum([1, 2, 3, 4]) == 1

    # ---- 两端离群、中间密集：砍掉两端后极差 0 ----
    assert solution.minimizeSum([100, 1, 50]) == 0


if __name__ == "__main__":
    test_solution()
    print("✅ No.2567 全部测试通过")
