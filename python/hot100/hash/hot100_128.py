"""
@file hot100_128.py
@brief LeetCode 128. 最长连续序列（Longest Consecutive Sequence）— HOT 100

@题目描述
    给定一个未排序的整数数组 nums，找出数字连续的最长序列（不要求序列元素在原数组中
    连续）的长度。请设计并实现时间复杂度为 O(n) 的算法解决此题。

@示例
    示例 1：
    输入：nums = [100,4,200,1,3,2]
    输出：4
    解释：最长数字连续序列是 [1, 2, 3, 4]，长度为 4

    示例 2：
    输入：nums = [0,3,7,2,5,8,4,6,0,1]
    输出：9

    示例 3：
    输入：nums = [1,0,1,2]
    输出：3

    数据范围：
    0 <= nums.length <= 1e5
    -1e9 <= nums[i] <= 1e9

@解题思路
    哈希集合 + 只从序列起点扩展：
    1. set 去重，遍历集合而非原数组，避免重复起点导致重复扫描；
    2. 只有 x-1 不在集合时，x 才是序列起点，从 x 向后数连续数字；
    3. 每个不同数字只在所属序列中计数一次，维护最大长度；空集合自然返回 0。

    时间复杂度平均 O(n)（哈希查询平均 O(1)），空间复杂度 O(n)。
    排序扫描虽能求出答案，但 O(n log n) 不满足题目要求的 O(n)。

来源：LeetCode
链接：https://leetcode.cn/problems/longest-consecutive-sequence/description/
"""


class Solution:
    def longestConsecutive(self, nums: list[int]) -> int:
        num_set = set(nums)
        ret = 0
        for x in num_set:
            if x - 1 not in num_set:
                run = 1
                while x + run in num_set:
                    run += 1
                ret = max(ret, run)
        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：[1,2,3,4] ----
    assert solution.longestConsecutive([100, 4, 200, 1, 3, 2]) == 4

    # ---- 官方示例 2：[0..8] 全连续 ----
    assert solution.longestConsecutive([0, 3, 7, 2, 5, 8, 4, 6, 0, 1]) == 9

    # ---- 官方示例 3：重复值 ----
    assert solution.longestConsecutive([1, 0, 1, 2]) == 3

    # ---- 单元素 ----
    assert solution.longestConsecutive([0]) == 1

    # ---- 空数组 ----
    assert solution.longestConsecutive([]) == 0

    # ---- 重复元素不延长连续段 ----
    assert solution.longestConsecutive([1, 2, 0, 1]) == 3

    # ---- 无任何连续：各成一段 ----
    assert solution.longestConsecutive([10, 30, 20]) == 1

    # ---- 负数 ----
    assert solution.longestConsecutive([-2, -1, 1, 2, 3]) == 3

    # ---- 大量重复起点：必须遍历集合，避免重复扫描同一段 ----
    assert solution.longestConsecutive([0] * 5000 + list(range(5000))) == 5000


if __name__ == "__main__":
    test_solution()
    print("✅ No.128（HOT 100）全部测试通过")
