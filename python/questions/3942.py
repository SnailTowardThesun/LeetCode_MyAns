"""
@file 3942.py
@brief LeetCode 3942. 排序排列的最少操作数

@题目描述
    给你一个长度为 n 的整数数组 nums，其中 nums 是区间 [0..n-1] 中所有数字的一个排列。
    你 只能 执行以下操作：
    - 反转 整个数组。
    - 左旋一位：将第一个元素移动到数组末尾，其余元素整体向左移动一位。
    返回将数组按 递增 顺序排序所需的 最少 操作次数。
    如果仅使用给定操作无法将数组排序，则返回 -1。

@示例
    示例 1：
    输入：nums = [0,2,1]
    输出：2
    解释：左旋一位得 [2,1,0]，再反转为 [0,1,2]。

    示例 2：
    输入：nums = [1,0,2]
    输出：2
    解释：先反转得 [2,0,1]，再左旋一位得 [0,1,2]。

    示例 3：
    输入：nums = [2,0,1,3]
    输出：-1

@解题思路
    旋转与翻转的组合只能生成 2n 种状态，排列可排序当且仅当：
    从 0 出发沿环某个方向（步长 +1 或 -1）环序递增。
    找 0 的位置 zero，构造两个环序切片（都以 0 开头）：
    - right = nums[zero:] + nums[:zero]（向右走）
    - left  = nums[zero::-1] + nums[:zero:-1]（向左走）
    向右递增 → 候选代价：zero（直接左旋）、n - zero + 2（反转+左旋+反转）
    向左递增 → 候选代价：zero + 2（左旋把 0 送末尾再反转）、n - zero（反转+左旋）
    四个候选取最小；两方向都不递增则 -1。

    时间复杂度 O(n)，空间复杂度 O(n)（两个切片；下标取模可做到 O(1)）

来源：LeetCode
链接：https://leetcode.cn/problems/minimum-operations-to-sort-a-permutation/description/
"""

from itertools import pairwise


class Solution:
    def is_monotonic_one_pass(self, a: list[int]) -> bool:
        inc = dec = True
        for x, y in pairwise(a):
            inc &= x <= y
            dec &= x >= y
            if not inc and not dec:  # 两个方向都破产,提前判乱序
                return False
        return inc or dec

    def minOperations(self, nums: list[int]) -> int:
        n = len(nums)
        zero = nums.index(0)  # 排列的 min 就是 0,一次定位

        # 从 0 出发沿环两个方向的环序（两个切片都以 0 开头，降序分支自动失活）
        right = nums[zero:] + nums[:zero]  # 向右走（步长 +1）
        left = nums[zero::-1] + nums[:zero:-1]  # 向左走（步长 -1）

        ans = n + 1  # 哨兵：任何合法方向至少给出一个 <= n 的候选
        if self.is_monotonic_one_pass(right):
            # 向右递增：直接左旋 zero 位 / 反转 + 左旋 (n-zero) 位 + 再反转
            ans = min(ans, zero, n - zero + 2)
        if self.is_monotonic_one_pass(left):
            # 向左递增：左旋 (zero+1) 位把 0 送到末尾再反转 / 反转 + 左旋 (n-zero-1) 位
            ans = min(ans, zero + 2, n - zero)

        return -1 if ans == n + 1 else ans


if __name__ == "__main__":
    s = Solution()
    assert s.minOperations([0, 2, 1]) == 2  # 官方示例 1：左旋一位 + 反转
    assert s.minOperations([1, 0, 2]) == 2  # 官方示例 2：反转 + 左旋一位
    assert s.minOperations([2, 0, 1, 3]) == -1  # 官方示例 3：不可行
    assert s.minOperations([0]) == 0  # 单元素已有序
    print("✅ 3942 官方示例全部通过")
