"""
@file hot100_239.py
@brief LeetCode 239. 滑动窗口最大值（Sliding Window Maximum）— HOT 100

@题目描述
    给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的
    最右侧。你只能看到滑动窗口内的 k 个数字，窗口每次向右移动一位。返回每个窗口
    位置的最大值组成的数组。

@示例
    示例 1：
    输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
    输出：[3,3,5,5,6,7]
    解释：
    窗口位置                  最大值
    ---------------          -----
    [1  3  -1] -3  5  3  6  7   3
     1 [3  -1  -3] 5  3  6  7   3
     1  3 [-1  -3  5] 3  6  7   5
     1  3  -1 [-3  5  3] 6  7   5
     1  3  -1  -3 [5  3  6] 7   6
     1  3  -1  -3  5 [3  6  7]  7

    示例 2：
    输入：nums = [1], k = 1
    输出：[1]

    数据范围：
    1 <= nums.length <= 1e5
    -1e4 <= nums[i] <= 1e4
    1 <= k <= nums.length

@解题思路
    大根堆 + 懒删除（堆顶过期才弹出）：
    1. 堆存 (-值, 下标)：Python heapq 是小根堆，取负把最大值顶到堆顶，
       下标用于判过期；
    2. 窗口右滑到 i：先压入 (-nums[i], i)，再把堆顶下标 <= i-k 的过期元素
       逐个弹出——只在「挡路的恰好是过期元素」时才清理，无需为每个窗口
       主动删除离开的元素（懒删除）；
    3. 每个元素至多进出堆各一次，弹出均摊 O(1) 次，总 O(n log n)。
    进阶：单调递减双端队列 O(n)——队尾比新元素小的全部弹出（它们永远
    不可能再当最大值），队首过期出队，队首即窗口最大值。

    时间复杂度 O(n log n)，空间复杂度 O(n)

来源：LeetCode
链接：https://leetcode.cn/problems/sliding-window-maximum/description/
"""

import heapq


class Solution:
    def maxSlidingWindow(self, nums: list[int], k: int) -> list[int]:
        n = len(nums)

        ans: list[int] = []
        # 堆存 (-值, 下标)：小根堆取负模拟大根堆，下标用于判窗口过期
        q = [(-nums[i], i) for i in range(k)]
        heapq.heapify(q)

        ans.append(-q[0][0])
        for i in range(k, n):
            heapq.heappush(q, (-nums[i], i))
            while q[0][1] <= i - k:  # 懒删除：堆顶过期才弹，弹到未过期为止
                heapq.heappop(q)
            ans.append(-q[0][0])

        return ans


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.maxSlidingWindow([1, 3, -1, -3, 5, 3, 6, 7], 3) == [3, 3, 5, 5, 6, 7]
    assert solution.maxSlidingWindow([1], 1) == [1]

    # ---- k = 1：窗口就是每个元素自身 ----
    assert solution.maxSlidingWindow([4, -2, 7], 1) == [4, -2, 7]

    # ---- k = n：整个数组只有一个窗口 ----
    assert solution.maxSlidingWindow([2, 9, 1, 5], 4) == [9]

    # ---- 单调递减：过期最大值逐个让位 ----
    assert solution.maxSlidingWindow([5, 4, 3, 2, 1], 2) == [5, 4, 3, 2]

    # ---- 单调递增：新元素总是新窗口最大值 ----
    assert solution.maxSlidingWindow([1, 2, 3, 4], 2) == [2, 3, 4]

    # ---- 相同元素：4 个元素 k=2 有 3 个窗口，并列最大值正确过期 ----
    assert solution.maxSlidingWindow([3, 3, 3, 3], 2) == [3, 3, 3]


if __name__ == "__main__":
    test_solution()
    print("✅ No.239（HOT 100）全部测试通过")
