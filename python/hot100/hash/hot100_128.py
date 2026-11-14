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
    输入：nums = [0]
    输出：1

    数据范围：
    0 <= nums.length <= 1e5
    -1e9 <= nums[i] <= 1e9

@解题思路
    去重排序 + 游程扫描：
    1. set 去重（重复元素不会延长连续段），排序后相邻差为 1 即连续；
    2. 一次遍历维护当前连续游程 run：与前一元素差 1 则 run++，否则重置为 1，
       全程记录最大值；
    3. 空数组特判返回 0（否则初始 run=1 会误报）。

    时间复杂度 O(n log n)（排序主导），空间复杂度 O(n)
    题目进阶要求 O(n)：哈希集合存全部数字，只从「序列起点」（x-1 不在集合中）
    开始向后数——每个数字至多被访问两次，总 O(n)；此解法见对应博客文章。

来源：LeetCode
链接：https://leetcode.cn/problems/longest-consecutive-sequence/description/
"""


class Solution:
    def longestConsecutive(self, nums: list[int]) -> int:
        if not nums:
            return 0

        container = sorted(set(nums))  # 去重后排序，重复元素不延长连续段
        ret = 1
        run = 1
        for i in range(1, len(container)):
            if container[i] - container[i - 1] == 1:
                run += 1
                ret = max(ret, run)
            else:
                run = 1  # 断开：从当前元素重新起段

        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：[1,2,3,4] ----
    assert solution.longestConsecutive([100, 4, 200, 1, 3, 2]) == 4

    # ---- 官方示例 2：[0..8] 全连续 ----
    assert solution.longestConsecutive([0, 3, 7, 2, 5, 8, 4, 6, 0, 1]) == 9

    # ---- 官方示例 3：单元素 ----
    assert solution.longestConsecutive([0]) == 1

    # ---- 空数组 ----
    assert solution.longestConsecutive([]) == 0

    # ---- 重复元素不延长连续段 ----
    assert solution.longestConsecutive([1, 2, 0, 1]) == 3

    # ---- 无任何连续：各成一段 ----
    assert solution.longestConsecutive([10, 30, 20]) == 1

    # ---- 负数 ----
    assert solution.longestConsecutive([-2, -1, 1, 2, 3]) == 3


if __name__ == "__main__":
    test_solution()
    print("✅ No.128（HOT 100）全部测试通过")
