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
    正数集合 + 从 1 线性探测（本实现，O(n) 时间 / O(n) 空间）：
    1. 一趟把所有正数收进集合；
    2. 从 1 开始逐个探测，第一个不在集合里的即为答案；
    3. 鸽笼原理保证答案 <= n+1（n 个位置最多放下 1..n，否则 1..n 某个缺席），
       探测至多 n+1 步，时间 O(n)。
    注意：题目进阶要求 O(1) 空间，本实现用了 O(n) 集合不符合该要求；
    标准解法是原地哈希（循环交换归位）：理想状态 nums[i] == i+1，把值在
    [1,n] 内的元素不断交换到自己的位置（目标位未被正确占位才交换，防重复值
    死循环），归位后第一个 nums[i] != i+1 处返回 i+1，全对则 n+1——
    见对应博客的实现。

    时间复杂度 O(n)，空间复杂度 O(n)

来源：LeetCode
链接：https://leetcode.cn/problems/first-missing-positive/description/
"""


class Solution:
    def firstMissingPositive(self, nums: list[int]) -> int:
        container = {i for i in nums if i > 0}  # 只需正数

        # 鸽笼原理：答案 <= n+1，探测至多 n+1 步必命中
        i = 1
        while i in container:
            i += 1
        return i


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

    # ---- 全负 / 含大数：答案是 1 ----
    assert solution.firstMissingPositive([-5, -3]) == 1
    assert solution.firstMissingPositive([100, 200]) == 1


if __name__ == "__main__":
    test_solution()
    print("✅ No.41（HOT 100）全部测试通过")
