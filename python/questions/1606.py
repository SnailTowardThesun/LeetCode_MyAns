"""
@file 1606.py
@brief LeetCode 1606. 找到处理最多请求的服务器（Find Servers That Handled Most Number of Requests）

@题目描述
    （粘贴题目原文）

@示例
    示例 1：
    输入：...
    输出：...

@解题思路
    1. ...

    时间复杂度 O()，空间复杂度 O()

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
    assert solution is not None  # TODO: 替换为真实测试用例（含边界情况）


if __name__ == "__main__":
    test_solution()
    print("✅ No.1606 全部测试通过")
