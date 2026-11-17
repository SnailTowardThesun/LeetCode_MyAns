"""
@file hot100_41.py
@brief LeetCode 41. 缺失的第一个正数（First Missing Positive）— HOT 100

@题目描述
    给定一个未排序的整数数组 nums，请你找出其中没有出现的最小的正整数。
    请你实现时间复杂度为 O(n) 并且只使用常数级空间（O(1)）的解决方案。

@示例
    示例 1：
    输入：nums = [1,2,0]
    输出：3

    示例 2：
    输入：nums = [3,4,-1,1]
    输出：2

    示例 3：
    输入：nums = [7,8,9,11,12]
    输出：1

    数据范围：
    1 <= nums.length <= 1e5
    -2^31 <= nums[i] <= 2^31 - 1

@解题思路
    原地哈希（循环交换归位）：
    1. n 个元素中缺失的最小正数一定在 [1,n+1] 内；
    2. 把值 x 在 [1,n] 内的元素交换到下标 x-1，其他值无需归位；
    3. 目标位置已有相同值时停止交换，避免重复值造成死循环；
    4. 归位后，第一个 nums[i] != i+1 的位置对应答案 i+1；全部正确则返回 n+1。
    每次有效交换都让一个值归位，归位的值不会再被移走，因此总交换次数不超过 n。
    该方法会修改输入数组，只使用常数个辅助变量。

    时间复杂度 O(n)，额外空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/first-missing-positive/description/
"""


class Solution:
    def firstMissingPositive(self, nums: list[int]) -> int:
        n = len(nums)
        for i in range(n):
            # 目标位置已有相同值时停止，避免重复值导致无限交换
            while 1 <= nums[i] <= n and nums[nums[i] - 1] != nums[i]:
                j = nums[i] - 1
                nums[i], nums[j] = nums[j], nums[i]

        for i in range(n):
            if nums[i] != i + 1:
                return i + 1
        return n + 1


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.firstMissingPositive([1, 2, 0]) == 3
    assert solution.firstMissingPositive([3, 4, -1, 1]) == 2
    assert solution.firstMissingPositive([7, 8, 9, 11, 12]) == 1

    # ---- 1..n 齐全：答案是 n+1 ----
    assert solution.firstMissingPositive([1]) == 2
    assert solution.firstMissingPositive([2, 1]) == 3

    # ---- 重复值：[1,1] 缺 2 ----
    assert solution.firstMissingPositive([1, 1]) == 2
    assert solution.firstMissingPositive([2, 2, 1]) == 3

    # ---- 同一位置需要连续交换，才能完成归位 ----
    assert solution.firstMissingPositive([2, 3, 4, 1]) == 5

    # ---- 全负 / 含大数：答案是 1 ----
    assert solution.firstMissingPositive([-5, -3]) == 1
    assert solution.firstMissingPositive([100, 200]) == 1


if __name__ == "__main__":
    test_solution()
    print("✅ No.41（HOT 100）全部测试通过")
