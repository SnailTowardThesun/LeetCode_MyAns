"""
@file 2747.py
@brief LeetCode 2747. Count Zero Request Servers（统计没有收到请求的服务器数目）

@题目描述
    给你一个整数 n，表示有 n 台服务器，编号为 1 到 n。
    给你一个二维整数数组 logs，其中 logs[i] = [server_id, time] 表示编号为
    server_id 的服务器在 time 时收到了一个请求。
    同时给你一个整数 x 和一个整数数组 queries，其中 queries[j] = q_j。
    在时间区间 [q_j - x, q_j]（闭区间）内收到过请求的服务器会承受额外负载。

    返回一个长度为 queries.length 的数组 answer，其中 answer[j] 表示在第 j
    个查询的时间区间内没有收到任何请求的服务器数目。

    提示：
    - 1 <= n <= 10^5
    - 1 <= logs.length <= 10^5，1 <= queries.length <= 10^5
    - 1 <= logs[i][0] <= n（服务器编号 1 到 n），1 <= logs[i][1] <= 10^6
    - 1 <= x <= 10^5
    - x < queries[j] <= 10^6

@示例
    示例 1：
    输入：n = 3, logs = [[1,3],[2,6],[1,5]], x = 5, queries = [10,11]
    输出：[1,2]
    解释：
    - 查询 10 的区间为 [5, 10]：服务器 1（t=5）和服务器 2（t=6）收到过请求，
      没有收到请求的服务器只有 3 号，答案为 1。
    - 查询 11 的区间为 [6, 11]：只有服务器 2（t=6）收到过请求，
      服务器 1 和 3 都没有，答案为 2。

    示例 2：
    输入：n = 3, logs = [[2,4],[2,1],[1,2],[3,1]], x = 2, queries = [3,4]
    输出：[0,1]
    解释：
    - 查询 3 的区间为 [1, 3]：三台服务器都收到过请求，答案为 0。
    - 查询 4 的区间为 [2, 4]：服务器 1（t=2）和 2（t=4）收到过请求，
      只有 3 号没有，答案为 1。

@解题思路
    答案 = n - 「窗口 [q-x, q] 内收到过请求的不同服务器数」。
    难点在大量查询共享计算，且「去重计数」不可按时间分段拆分求和
    （同一服务器会出现在多个子段中，直接相加会重复统计）。

    采用离线 + 排序 + 双指针滑动窗口：
    1. logs 按时间排序；queries 连同原下标一起按时间排序（离线处理）。
    2. 按查询时间从小到大处理，窗口 [q-x, q] 的左右边界都单调不减，
       两个指针各自只会单向前进：
       - 右指针把 time <= q 的日志收进 Counter，某服务器计数从 0 变 1
         时 busy（窗口内"忙碌"的不同服务器数）加一；
       - 左指针把 time < q-x 的日志移出，计数减到 0 时删除键并 busy 减一。
    3. 每个查询的答案即 n - busy，按原下标写回。

    Counter 按服务器 id 计数，天然处理了「同一服务器多次请求只算一台」；
    查询排序后窗口单向滑动，每条日志至多进出窗口各一次。

    时间复杂度 O(M log M + Q log Q)（M = len(logs)，Q = len(queries)，
    排序占主导，双指针均摊线性）；空间复杂度 O(M + Q)。

来源：LeetCode
链接：https://leetcode.cn/problems/count-zero-request-servers/description/
"""


class Solution:
    def countServers(self, n: int, logs: list[list[int]], x: int, queries: list[int]) -> list[int]:
        logs = sorted(logs, key=lambda log: log[1])
        order = sorted(range(len(queries)), key=lambda i: queries[i])

        cnt: dict[int, int] = {}  # 窗口内 server_id -> 请求条数
        busy = 0  # 窗口内收到过至少一个请求的不同服务器数
        ret = [0] * len(queries)

        left = right = 0
        for i in order:
            start, end = max(0, queries[i] - x), queries[i]
            # 右指针：纳入 time <= q 的日志（右端点闭区间）
            while right < len(logs) and logs[right][1] <= end:
                server = logs[right][0]
                cnt[server] = cnt.get(server, 0) + 1
                if cnt[server] == 1:
                    busy += 1
                right += 1
            # 左指针：剔除 time < q-x 的日志（左端点闭区间，等于的保留）
            while left < right and logs[left][1] < start:
                server = logs[left][0]
                cnt[server] -= 1
                if cnt[server] == 0:
                    busy -= 1
                    del cnt[server]
                left += 1
            ret[i] = n - busy

        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1 ----
    assert solution.countServers(3, [[1, 3], [2, 6], [1, 5]], 5, [10, 11]) == [1, 2]

    # ---- 官方示例 2 ----
    assert solution.countServers(3, [[2, 4], [2, 1], [1, 2], [3, 1]], 2, [3, 4]) == [0, 1]

    # ---- 请求恰好落在右端点 t = q：闭区间必须计入 ----
    assert solution.countServers(2, [[1, 10]], 0, [10]) == [1]

    # ---- 请求恰好落在左端点 t = q - x：闭区间必须计入 ----
    assert solution.countServers(2, [[1, 5]], 5, [10]) == [1]

    # ---- 同一服务器多条日志：去重后只算一台 ----
    assert solution.countServers(3, [[1, 3], [1, 4], [1, 5]], 10, [5]) == [2]

    # ---- 查询乱序输入：离线排序后仍按原下标返回 ----
    assert solution.countServers(3, [[1, 3], [2, 6], [1, 5]], 5, [11, 10]) == [2, 1]

    # ---- 查询跨过一段日志：新纳入的过期日志必须在本轮删除，不能先左后右 ----
    assert solution.countServers(2, [[1, 3], [2, 8]], 2, [4, 10]) == [1, 1]

    # ---- 没有任何日志：所有服务器都是零请求 ----
    assert solution.countServers(3, [], 2, [10, 11]) == [3, 3]

    # ---- 窗口完全早于所有日志：同样全部零请求 ----
    assert solution.countServers(2, [[1, 100]], 5, [10]) == [2]

    # ---- 窗口完全晚于所有日志 ----
    assert solution.countServers(2, [[1, 1]], 5, [10]) == [2]


if __name__ == "__main__":
    test_solution()
    print("✅ No.2747 全部测试通过")
