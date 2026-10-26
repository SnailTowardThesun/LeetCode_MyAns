"""
@file top150_210.py
@brief LeetCode 210. Course Schedule II（课程表 II）

@题目描述
    现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。给你一个数组
    prerequisites，其中 prerequisites[i] = [ai, bi]，表示在选修课程 ai 前 必须 先选修 bi。
    例如，想要学习课程 0，你需要先完成课程 1，我们用一个匹配来表示：[0,1]。
    返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种
    就可以了。如果不可能完成所有课程，返回 一个空数组。

    提示：
    - 1 <= numCourses <= 2000
    - 0 <= prerequisites.length <= numCourses * (numCourses - 1)
    - prerequisites[i].length == 2
    - 0 <= ai, bi < numCourses，ai != bi
    - 所有 [ai, bi] 互不相同

@示例
    示例 1：
    输入：numCourses = 2, prerequisites = [[1,0]]
    输出：[0,1]
    解释：总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1]。

    示例 2：
    输入：numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
    输出：[0,2,1,3]
    解释：总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2
         都应该排在课程 0 之后。因此，一个正确的课程顺序是 [0,1,2,3]。另一个正确的排序是
         [0,2,1,3]。

    示例 3：
    输入：numCourses = 1, prerequisites = []
    输出：[0]

@解题思路
    DFS 三色标记 + 后序逆序（拓扑排序）：
    1. 建邻接表：prerequisites[i] = [a, b] 表示先修 b 再修 a，边 b -> a
       （方向建反输出会整体倒置）；
    2. 三色状态 0/1/2 = 未访问 / 在当前递归栈上 / 已完成。对每门未访问的课做 DFS：
       入口标 1，遍历后继——后继为 0 则递归；后继为 1 说明绕回了栈上的节点（回边），
       存在环，置 is_circle 立即返回；全部后继处理完后标 2，把该课追加到 result（后序）；
    3. 有环返回空列表；无环则 result 逆序即拓扑序——任何一条边 b -> a，DFS 保证 a 比 b
       先完成，逆序后 b 自然排在 a 前面。

    时间复杂度 O(N + P)，空间复杂度 O(N + P)（N 为课程数，P 为先修关系数）。
    注：递归深度最大为 N，本地跑超长链需抬高 sys.setrecursionlimit（LeetCode 线上上限很高）。

来源：LeetCode
链接：https://leetcode.cn/problems/course-schedule-ii/description/
"""


class Solution:
    def findOrder(self, numCourses: int, prerequisites: list[list[int]]) -> list[int]:
        edges = {i: [] for i in range(numCourses)}
        for q in prerequisites:
            edges[q[1]].append(q[0])

        statue = [0] * numCourses

        result = []
        is_circle = False

        def dfs(node):
            nonlocal is_circle
            statue[node] = 1

            for edge in edges[node]:
                if statue[edge] == 0:
                    dfs(edge)
                    if is_circle:
                        return
                elif statue[edge] == 1:
                    is_circle = True
                    return
            statue[node] = 2
            result.append(node)

        for n in range(numCourses):
            if not is_circle and statue[n] == 0:
                dfs(n)

        if is_circle:
            return []

        return result[::-1]


def assert_valid_order(order: list[int], num_courses: int, prerequisites: list[list[int]]) -> None:
    """合法顺序 = 恰好是 0..n-1 的一个排列，且每条 [a, b] 中 b 都排在 a 前面。"""
    assert sorted(order) == list(range(num_courses)), f"不是 0..{num_courses - 1} 的排列: {order}"
    pos = {course: i for i, course in enumerate(order)}
    for a, b in prerequisites:
        assert pos[b] < pos[a], f"课程 {b} 必须排在课程 {a} 之前: {order}"


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例（答案不唯一时只校验合法性） ----
    assert solution.findOrder(2, [[1, 0]]) == [0, 1]  # 示例 1：顺序唯一
    prereq = [[1, 0], [2, 0], [3, 1], [3, 2]]  # 示例 2：[0,1,2,3] 与 [0,2,1,3] 都对
    assert_valid_order(solution.findOrder(4, prereq), 4, prereq)
    assert solution.findOrder(1, []) == [0]  # 示例 3

    # ---- 有环：返回空列表 ----
    assert solution.findOrder(2, [[1, 0], [0, 1]]) == []
    assert solution.findOrder(3, [[1, 0], [2, 1], [0, 2]]) == []

    # ---- 没有先修关系：任意排列都合法 ----
    assert_valid_order(solution.findOrder(4, []), 4, [])

    # ---- 线性链：顺序唯一 ----
    assert solution.findOrder(4, [[1, 0], [2, 1], [3, 2]]) == [0, 1, 2, 3]
    assert solution.findOrder(4, [[0, 1], [1, 2], [2, 3]]) == [3, 2, 1, 0]  # 反向链

    # ---- 多个连通分量 + 孤立课程 4 ----
    prereq = [[1, 0], [3, 2]]
    assert_valid_order(solution.findOrder(5, prereq), 5, prereq)

    # ---- 多个连通分量，其中一个有环 -> 空 ----
    assert solution.findOrder(6, [[1, 0], [3, 2], [2, 3], [5, 4]]) == []

    # ---- 星型：所有课都依赖 0，0 必须排第一 ----
    prereq = [[i, 0] for i in range(1, 6)]
    order = solution.findOrder(6, prereq)
    assert_valid_order(order, 6, prereq)
    assert order[0] == 0

    # ---- 反向星型：0 依赖所有其他课，0 必须排最后 ----
    prereq = [[0, i] for i in range(1, 6)]
    order = solution.findOrder(6, prereq)
    assert_valid_order(order, 6, prereq)
    assert order[-1] == 0

    # ---- 复杂 DAG：多条路径汇合再分叉 ----
    prereq = [[2, 0], [2, 1], [3, 1], [4, 2], [4, 3], [5, 4], [5, 0]]
    assert_valid_order(solution.findOrder(6, prereq), 6, prereq)

    # ---- 稠密 DAG：课程 i 依赖所有 j < i，全序关系，顺序唯一 ----
    n = 100
    dense = [[i, j] for i in range(n) for j in range(i)]
    assert solution.findOrder(n, dense) == list(range(n))
    assert solution.findOrder(n, dense + [[0, n - 1]]) == []


if __name__ == "__main__":
    test_solution()
    print("✅ No.210 全部测试通过")
