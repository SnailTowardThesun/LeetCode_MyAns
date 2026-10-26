"""
@file top150_207.py
@brief LeetCode 207. Course Schedule（课程表）

@题目描述
    你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1。
    在选修某些课程之前需要一些先修课程。先修课程按数组 prerequisites 给出，
    其中 prerequisites[i] = [ai, bi]，表示如果要学习课程 ai 则 必须 先学习课程 bi。
    例如，先修课程对 [0, 1] 表示：想要学习课程 0，你需要先完成课程 1。
    请你判断是否可能完成所有课程的学习？如果可以，返回 true；否则，返回 false。

    提示：
    - 1 <= numCourses <= 2000
    - 0 <= prerequisites.length <= 5000
    - prerequisites[i].length == 2
    - 0 <= ai, bi < numCourses
    - prerequisites[i] 中的所有课程对 互不相同

@示例
    示例 1：
    输入：numCourses = 2, prerequisites = [[1,0]]
    输出：true
    解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。这是可能的。

    示例 2：
    输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
    输出：false
    解释：总共有 2 门课程。学习课程 1 之前，你需要先完成课程 0；
         并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。

@解题思路
    把先修关系 prerequisites[i] = [ai, bi] 看成有向边 bi -> ai（先修完 bi 才能修 ai），
    "能否修完全部课程"等价于"这张有向图是否无环"。

    DFS 三色标记判环：
    - state[node] == 0：白色，从未访问；
    - state[node] == 1：灰色，在当前 DFS 递归栈中（正在访问）；
    - state[node] == 2：黑色，从该节点出发的所有路径均已探完，确认无环。

    对每个白色节点启动 DFS：进入时染灰，依次递归它的所有后继；
    若某条边指向灰色节点，说明沿边走回了"正在途中的自己"——存在环，立即标记并逐层退出；
    全部后继处理完仍无环则染黑。所有节点都能染黑，说明图无环，可以修完全部课程。

    注意：递归写法的深度等于图中最长路径，测试用例规模需控制在
    Python 默认递归深度（1000）以内；更大的图应改用 Kahn 拓扑排序（BFS）迭代实现。

    复杂度分析：
    - 时间复杂度：O(N + P)，每个节点、每条边各访问一次（N 为课程数，P 为先修关系数）
    - 空间复杂度：O(N + P)，邻接表 + 状态数组 + 递归栈

来源：LeetCode
链接：https://leetcode.cn/problems/course-schedule/description/
"""


class Solution:
    def canFinish(self, numCourses: int, prerequisites: list[list[int]]) -> bool:
        # 邻接表：edges[bi] 存放先修完 bi 之后才能修的课程
        edges = [[] for _ in range(numCourses)]
        for a, b in prerequisites:
            edges[b].append(a)

        state = [0] * numCourses  # 0=未访问 1=访问中 2=已完成
        has_cycle = False

        def dfs(node: int) -> None:
            nonlocal has_cycle
            state[node] = 1

            for nxt in edges[node]:
                if state[nxt] == 0:
                    dfs(nxt)
                elif state[nxt] == 1:  # 指回"访问中"的节点 -> 有环
                    has_cycle = True
                if has_cycle:
                    return

            state[node] = 2

        for course in range(numCourses):
            if state[course] == 0 and not has_cycle:
                dfs(course)

        return not has_cycle


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.canFinish(2, [[1, 0]])
    assert not solution.canFinish(2, [[1, 0], [0, 1]])

    # ---- 边界：没有任何先修关系 ----
    assert solution.canFinish(1, [])
    assert solution.canFinish(5, [])

    # ---- 线性链 0 -> 1 -> 2 -> 3 -> 4 ----
    assert solution.canFinish(5, [[1, 0], [2, 1], [3, 2], [4, 3]])

    # ---- 三节点环 ----
    assert not solution.canFinish(3, [[1, 0], [2, 1], [0, 2]])

    # ---- 菱形依赖：节点 3 有两条前置路径，是 DAG 不是环 ----
    assert solution.canFinish(4, [[1, 0], [2, 0], [3, 1], [3, 2]])

    # ---- 星型：所有课程都依赖课程 0 / 反向星型：课程 0 依赖所有其他课程 ----
    assert solution.canFinish(6, [[i, 0] for i in range(1, 6)])
    assert solution.canFinish(6, [[0, i] for i in range(1, 6)])

    # ---- 多个连通分量全部无环 ----
    assert solution.canFinish(6, [[1, 0], [3, 2], [5, 4]])

    # ---- 多个连通分量，其中一个有环 -> 整体不可完成 ----
    assert not solution.canFinish(6, [[1, 0], [3, 2], [2, 3], [5, 4]])

    # ---- 无环前缀很长，环藏在尾部（3 -> 4 -> 5 -> 3） ----
    assert not solution.canFinish(6, [[1, 0], [2, 1], [3, 2], [4, 3], [5, 4], [3, 5]])

    # ---- 孤立课程：有课程完全不出现在 prerequisites 中 ----
    assert solution.canFinish(4, [[2, 1]])

    # ---- 稠密 DAG：课程 i 依赖所有 j < i（递归深度 100，低于 Python 默认限制 1000） ----
    n = 100
    dense = [[i, j] for i in range(n) for j in range(i)]
    assert solution.canFinish(n, dense)
    assert not solution.canFinish(n, dense + [[0, n - 1]])


if __name__ == "__main__":
    test_solution()
    print("✅ No.207 全部测试通过")
