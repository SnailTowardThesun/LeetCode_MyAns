"""
@file top150_502.py
@brief LeetCode 502. IPO

@题目描述
    假设 LeetCode 即将开始 IPO。为了以更高的价格将股票卖给投资公司，
    LeetCode 希望在 IPO 之前开展一些项目以增加其资本。由于资源有限，
    它只能在 IPO 之前完成最多 k 个不同的项目。给你 n 个项目：对每个项目 i，
    它都有纯利润 profits[i]，和启动该项目所需的最小资本 capital[i]。
    最初你的资本为 w。完成一个项目时，你将获得纯利润并加到总资本中。
    从给定项目中选择最多 k 个不同项目，最大化最终资本，输出最终可获取的最大资本。

@示例
    示例 1：
    输入：k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
    输出：4
    解释：第 1 轮资本 0，只能做项目 0，资本变 1；第 2 轮可选项目 1/2，
         做利润最高的项目 2，资本变 4。

@解题思路
    贪心：每轮在"买得起"（capital <= w）的项目里选利润最高的（profits >= 1，做必不亏）。
    性能关键是让每个项目只被处理一次：
    1. 项目按启动资本升序排序，维护指针 idx 指向下一个未入堆的项目；
    2. 每轮把所有 capital <= w 的项目入堆（w 只增不减，买得起的集合只会扩张，
       指针永不回退，每个项目一生只入堆一次）；堆存取负的利润，模拟最大堆；
    3. 弹堆顶（当前最大利润）累加到 w；堆空说明无项目可做，提前结束。
    旧写法每轮重建堆 + nlargest + del 列表，单轮 O(n)，共 O(k*n*log n) 会超时。

    时间复杂度 O(n*log n + k*log n)，空间复杂度 O(n)

来源：LeetCode
链接：https://leetcode.cn/problems/ipo/description/
"""

import heapq


class Solution:
    def findMaximizedCapital(self, k: int, w: int, profits: list[int], capital: list[int]) -> int:
        projects = sorted(zip(capital, profits, strict=True))
        idx = 0
        container = []
        for _ in range(k):
            while idx < len(projects) and projects[idx][0] <= w:
                heapq.heappush(container, -projects[idx][1])
                idx += 1

            if len(container) == 0:
                continue

            w = w - heapq.heappop(container)

        return w


if __name__ == "__main__":
    s = Solution()
    k = 2
    w = 0
    profits = [1, 2, 3]
    capital = [0, 1, 1]
    ret = s.findMaximizedCapital(k, w, profits, capital)
    print(ret)
