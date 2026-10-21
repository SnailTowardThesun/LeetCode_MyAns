"""
@file top150_373.py
@brief LeetCode 373. 查找和最小的 K 对数字

@题目描述
    给定两个以 非递减顺序 排列的整数数组 nums1 和 nums2, 以及一个整数 k。
    定义一对值 (u, v)，其中第一个元素来自 nums1，第二个元素来自 nums2。
    请找到和最小的 k 对数字 (u1, v1), (u2, v2) ... (uk, vk)。

@示例
    示例 1：
    输入：nums1 = [1,7,11], nums2 = [2,4,6], k = 3
    输出：[[1,2],[1,4],[1,6]]
    解释：返回序列中的前 3 对数：[1,2],[1,4],[1,6]（和依次为 3,5,7）

@解题思路
    朴素写法把全部 m*n 个数对塞进堆再弹 k 次，内存 O(m*n)，大数组下直接 MLE；
    用"大小为 k 的最大堆筛选"能把内存压到 O(k)，但仍要枚举全部 m*n 对，时间不达标。
    改用"多路归并"式的动态堆：
    1. 把所有数对看成 len(nums1) 行的矩阵：第 i 行是 nums1[i] 分别配 nums2[0..n-1]，
       因为 nums2 有序，每行内部递增，行头就是该行最小值。
    2. 初始只把前 min(k, m) 个"行头"放入堆，元素为 (和, i, j)。
    3. 每弹出一个当前全局最小 (i, j)，就把同行的下一个 (i, j+1) 压入堆——
       堆大小始终不超过 min(k, m)，弹满 k 次即得答案，且天然按升序输出。
    堆是"按需生长"的：只探索被弹出候选的右邻居，不会物化整个乘积空间。

    时间复杂度 O(k * log(min(k, m)))，空间复杂度 O(min(k, m))

来源：LeetCode
链接：https://leetcode.cn/problems/find-k-pairs-with-smallest-sums/description/
"""

import heapq


class Solution:
    def kSmallestPairs(self, nums1: list[int], nums2: list[int], k: int) -> list[list[int]]:
        ret: list[list[int]] = []
        if not nums1 or not nums2 or k <= 0:
            return ret

        # 动态堆：初始只装 min(k, m) 个行头 (sum, i, j)，而不是整个 m*n 乘积空间
        heap = [(nums1[i] + nums2[0], i, 0) for i in range(min(k, len(nums1)))]
        heapq.heapify(heap)

        while heap and len(ret) < k:
            _, i, j = heapq.heappop(heap)
            ret.append([nums1[i], nums2[j]])
            # 被弹出的候选向右推进一位，其邻居入堆（按需扩展，堆大小不变）
            if j + 1 < len(nums2):
                heapq.heappush(heap, (nums1[i] + nums2[j + 1], i, j + 1))

        return ret


def test_solution() -> None:
    solution = Solution()
    assert solution.kSmallestPairs([1, 7, 11], [2, 4, 6], 3) == [[1, 2], [1, 4], [1, 6]]

    # 和相等的数对返回顺序不唯一，校验"和序列非递减 + 数对多重集与官方答案一致"
    ret = solution.kSmallestPairs([1, 1, 2], [1, 2, 3], 10)
    expected = [[1, 1], [1, 1], [2, 1], [1, 2], [1, 2], [2, 2], [1, 3], [1, 3], [2, 3]]
    sums = [a + b for a, b in ret]
    assert sums == sorted(sums)
    assert sorted(map(tuple, ret)) == sorted(map(tuple, expected))

    assert solution.kSmallestPairs([1, 2], [3], 3) == [[1, 3], [2, 3]]  # k 超过总对数
    assert solution.kSmallestPairs([], [1, 2], 5) == []  # 空数组边界

    # 与暴力解法对拍：随机小数组上结果的多重集必须一致
    import random

    for _ in range(200):
        m, n = random.randint(1, 8), random.randint(1, 8)
        a = sorted(random.randint(0, 20) for _ in range(m))
        b = sorted(random.randint(0, 20) for _ in range(n))
        k = random.randint(1, m * n + 2)  # 故意让 k 可能超过总对数
        got = solution.kSmallestPairs(a, b, k)
        brute = sorted(([x, y] for x in a for y in b), key=lambda p: p[0] + p[1])[: len(got)]
        sums = [x + y for x, y in got]
        assert sums == sorted(sums)
        assert sorted(map(tuple, got)) == sorted(map(tuple, brute))


if __name__ == "__main__":
    test_solution()
    print("✅ top150_373 全部测试通过")
