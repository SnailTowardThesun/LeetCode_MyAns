"""
@file 1606.py
@brief LeetCode 1606. 找到处理最多请求的服务器（Find Servers That Handled Most Number of Requests）

@题目描述
    你有 k 个服务器，编号为 0 到 k-1，它们可以同时处理多个请求组。每个服务器有无穷
    的计算能力但是不能同时处理超过一个请求。请求分配到服务器的规则如下：
    - 第 i（序号从 0 开始）个请求到达时，如果所有服务器都已被占据，该请求被舍弃；
    - 如果第 (i % k) 个服务器空闲，那么对应服务器会处理该请求；
    - 否则，将请求安排给下一个空闲的服务器（服务器构成一个环，必要的话从第 0 个
      服务器开始继续找下一个空闲的服务器）。
    给定严格递增的正整数数组 arrival（第 i 个请求的到达时间）和数组 load（第 i 个
    请求的工作量，即处理所需时间），返回处理请求数最多的服务器编号列表（可能有
    多个，按编号升序返回）。

@示例
    示例 1：
    输入：k = 3, arrival = [1,2,3,4,5], load = [5,2,3,3,3]
    输出：[1]
    解释：前 3 个请求由服务器 0/1/2 依次处理；请求 3 到达时服务器 1 已空闲，接力
    处理（共 2 个）；请求 4 到达时全部繁忙，被舍弃。服务器 1 最忙。

    示例 2：
    输入：k = 3, arrival = [1,2,3], load = [10,12,11]
    输出：[0,1,2]

    示例 3：
    输入：k = 3, arrival = [1,2,3,4,8,9,10], load = [5,2,10,3,1,2,2]
    输出：[1]

    数据范围：
    1 <= k <= 1e5
    1 <= arrival.length == load.length <= 1e5
    1 <= arrival[i], load[i] <= 1e9，arrival 严格递增

@解题思路
    双小根堆模拟 + 空闲编号重定位技巧：
    1. busy 堆按 (结束时间, 编号) 组织，请求 i 到达时先把结束时间 <= arrival[i] 的
       服务器归还空闲堆；
    2. 关键技巧：归还时把空闲编号 j 重定位为 i + (j - i) % k，即 >= i 且与 j 同余
       (mod k) 的最小值（Python 取模天然非负）。这样空闲堆堆顶就是从 i%k 开始
       环形搜索遇到的第一个空闲服务器，弹出后对 k 取模还原真实编号；
       注意 C++ 的 % 对负数是截断取余，需改写为 ((j - i) % k + k) % k；
    3. 空闲堆为空则丢弃该请求；否则弹出堆顶，记录结束时间入 busy 堆并计数；
    4. 取计数最大值，所有计数等于最大值的编号即答案；k > n 时每个请求各占一台
       空闲服务器，编号 0..n-1 全部并列，直接返回。

    时间复杂度 O((n + k) log k)，空间复杂度 O(k)

来源：LeetCode
链接：https://leetcode.cn/problems/find-servers-that-handled-most-number-of-requests/description/
"""

from heapq import heappop, heappush


class Solution:
    def busiestServers(self, k: int, arrival: list[int], load: list[int]) -> list[int]:
        if k > len(arrival):
            return list(range(len(arrival)))

        idle = list(range(k))
        busy = []
        cnt = [0] * k

        for i, (t, d) in enumerate(zip(arrival, load, strict=False)):
            while busy and busy[0][0] <= t:
                _, j = heappop(busy)
                heappush(idle, i + (j - i) % k)

            if not idle:
                continue

            j = heappop(idle) % k
            heappush(busy, (t + d, j))
            cnt[j] += 1

        ret = []
        mm = max(cnt)
        for i in range(k):
            if cnt[i] == mm:
                ret.append(i)
        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：服务器 1 处理 2 个请求 ----
    assert solution.busiestServers(3, [1, 2, 3, 4, 5], [5, 2, 3, 3, 3]) == [1]

    # ---- 官方示例 2：请求 3 时刻服务器 0 恰好空闲，环首接力，共处理 2 个 ----
    assert solution.busiestServers(3, [1, 2, 3, 4], [1, 2, 1, 2]) == [0]

    # ---- 官方示例 3：三台各处理 1 个请求，全部并列 ----
    assert solution.busiestServers(3, [1, 2, 3], [10, 12, 11]) == [0, 1, 2]

    # ---- 官方示例 4：服务器 1 处理 4 个请求 ----
    assert solution.busiestServers(3, [1, 2, 3, 4, 8, 9, 10], [5, 2, 10, 3, 1, 2, 2]) == [1]

    # ---- 回归用例：空闲编号若未按 (j - i) % k 重定位（误写 i + j）会错答 [2] ----
    assert solution.busiestServers(3, [1, 2, 3, 4, 8], [1, 5, 5, 1, 1]) == [0, 1]

    # ---- 边界：服务器数多于请求数，编号 0..n-1 全部并列 ----
    assert solution.busiestServers(5, [1, 2], [3, 4]) == [0, 1]

    # ---- 边界：单台服务器串行处理所有请求 ----
    assert solution.busiestServers(1, [1, 2], [1, 1]) == [0]


if __name__ == "__main__":
    test_solution()
    print("✅ No.1606 全部测试通过")
