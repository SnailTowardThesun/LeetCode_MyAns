"""
@file top150_295.py
@brief LeetCode 295. 数据流的中位数

@题目描述
    中位数是有序整数列表中的中间值。如果列表的长度为偶数，则中位数是中间两个数的平均值。
    实现 MedianFinder 类：
    - MedianFinder() 初始化 MedianFinder 对象。
    - addNum(int num) 从数据流中添加一个整数到数据结构中。
    - double findMedian() 返回目前所有元素的中位数。

@示例
    示例 1：
    输入：["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
         [[], [1], [2], [], [3], []]
    输出：[null, null, null, 1.5, null, 2.0]
    解释：插入 1、2 后中位数为 (1+2)/2=1.5；再插入 3 后中位数为 2。

@解题思路
    双堆对半维护（对顶堆）：
    1. queue_min 存较小一半（存 0-num 即取负，用小顶堆模拟大顶堆），
       queue_max 存较大一半（普通小顶堆）；
    2. addNum：新数小于下半堆顶（或下半为空）则入下半，否则入上半；
       入下半后若下半比上半多超过 1 个，则把下半堆顶搬给上半；
       入上半后若上半比下半多，则把上半堆顶搬给下半——
       始终保持 len(queue_min) == len(queue_max) 或 len(queue_min) == len(queue_max) + 1；
    3. findMedian：总数为奇数时下半堆顶（取负还原）即中位数，
       偶数时取两堆顶的平均值。

    时间复杂度 addNum O(log n)、findMedian O(1)，空间复杂度 O(n)

来源：LeetCode
链接：https://leetcode.cn/problems/find-median-from-data-stream/description/
"""

import heapq


class MedianFinder:
    def __init__(self):
        self.queue_min = []
        self.queue_max = []

    def addNum(self, num: int) -> None:
        if len(self.queue_min) < 1 or num < 0 - self.queue_min[0]:
            heapq.heappush(self.queue_min, 0 - num)
            if len(self.queue_max) + 1 < len(self.queue_min):
                heapq.heappush(self.queue_max, 0 - heapq.heappop(self.queue_min))
        else:
            heapq.heappush(self.queue_max, num)
            if len(self.queue_max) > len(self.queue_min):
                heapq.heappush(self.queue_min, 0 - heapq.heappop(self.queue_max))

    def findMedian(self) -> float:
        if len(self.queue_min) > len(self.queue_max):
            return 0 - self.queue_min[0]

        return (0 - self.queue_min[0] + self.queue_max[0]) / 2.0


def _naive_median(nums: list[int]) -> float:
    """朴素参照解法：排序后取中位数，仅用于对拍。"""
    s = sorted(nums)
    n = len(s)
    return s[n // 2] if n % 2 else (s[n // 2 - 1] + s[n // 2]) / 2


def _feed_and_check(mf: MedianFinder, data: list[int]) -> None:
    """依次插入 data 中每个元素，每插一个就查询一次中位数并与朴素解法对照。"""
    stream: list[int] = []
    for x in data:
        mf.addNum(x)
        stream.append(x)
        expect = _naive_median(stream)
        assert mf.findMedian() == expect, f"插入 {stream} 后中位数应为 {expect}"


def test_median_finder() -> None:
    # ---- 官方示例 1：偶数个取平均，奇数个取中间 ----
    mf = MedianFinder()
    mf.addNum(1)
    mf.addNum(2)
    assert mf.findMedian() == 1.5  # [1, 2] -> (1+2)/2
    mf.addNum(3)
    assert mf.findMedian() == 2  # [1, 2, 3] -> 2

    # ---- 官方示例 2：负数流 ----
    mf = MedianFinder()
    for x, expect in [(-1, -1.0), (-2, -1.5), (-3, -2.0), (-4, -2.5), (-5, -3.0)]:
        mf.addNum(x)
        assert mf.findMedian() == expect

    # ---- 边界：单元素 ----
    mf = MedianFinder()
    mf.addNum(7)
    assert mf.findMedian() == 7

    # ---- 边界：全相同元素 ----
    mf = MedianFinder()
    for _ in range(4):
        mf.addNum(5)
    assert mf.findMedian() == 5

    # ---- 边界：题目约束的极值 -1e5 / 1e5 ----
    mf = MedianFinder()
    mf.addNum(-100000)
    mf.addNum(100000)
    assert mf.findMedian() == 0

    # ---- 乱序 / 递增 / 递减流：每插一个查一次，奇偶长度交替 ----
    _feed_and_check(MedianFinder(), [5, 15, 1, 3, 2, 8, 7, 9, 10, 6, 11, 4])
    _feed_and_check(MedianFinder(), list(range(1, 10)))  # 递增
    _feed_and_check(MedianFinder(), list(range(10, 0, -1)))  # 递减

    # ---- 随机对拍：插入与查询交错，与朴素解法对照 ----
    import random

    random.seed(42)
    for _ in range(5):
        mf = MedianFinder()
        stream: list[int] = []
        for _ in range(500):
            if stream and random.random() < 0.3:
                assert mf.findMedian() == _naive_median(stream)
            else:
                x = random.randint(-(10**5), 10**5)
                stream.append(x)
                mf.addNum(x)


if __name__ == "__main__":
    test_median_finder()
    print("✅ top150_295 全部测试通过")
