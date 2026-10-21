"""
@file top150_215.py
@brief LeetCode 215. 数组中的第K个最大元素

@题目描述
    给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
    请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
    你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

@示例
    示例 1：
    输入：nums = [3,2,1,5,6,4], k = 2
    输出：5

    示例 2：
    输入：nums = [3,2,3,1,2,4,5,5,6], k = 4
    输出：4

@解题思路
    维护一个大小为 k 的最小堆：
    1. 依次把每个元素压入堆；
    2. 一旦堆大小超过 k，弹出堆顶（当前堆里最小的）——堆中永远只保留"至今最大的 k 个"；
    3. 遍历结束后堆顶就是这 k 个里最小的，即全数组第 k 大。
    相比整体排序 O(n*log n)，k 远小于 n 时优势明显；
    若要严格 O(n) 期望时间可用快速选择（quickselect）。

    时间复杂度 O(n*log k)，空间复杂度 O(k)

来源：LeetCode
链接：https://leetcode.cn/problems/kth-largest-element-in-an-array/description/
"""

import heapq


class Solution:
    def findKthLargest(self, nums: list[int], k: int) -> int:
        container = []
        for n in nums:
            heapq.heappush(container, n)

            if len(container) > k:
                heapq.heappop(container)

        print(container)
        return container[0]


if __name__ == "__main__":
    s = Solution()
    ret = s.findKthLargest([3, 2, 1, 5, 6, 4], 2)
