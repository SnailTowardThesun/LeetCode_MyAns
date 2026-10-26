"""
@file top150_133.py
@brief LeetCode 133. Clone Graph（克隆图）

@题目描述
    给你无向 连通 图中一个节点的引用，请你返回该图的 深拷贝（克隆）。
    图中的每个节点都包含它的值 val（int）和其邻居的列表（list[Node]）。

        class Node {
            public int val;
            public List<Node> neighbors;
        }

    测试用例格式：
    简单起见，每个节点的值都和它的索引相同。例如，第一个节点值为 1（val = 1），
    第二个节点值为 2（val = 2），以此类推。该图在测试用例中使用邻接列表表示。
    邻接列表 是用于表示有限图的无序列表的集合。每个列表都描述了图中节点的邻居集。
    给定节点将始终是值为 1 的第一个节点。你必须将 给定节点的拷贝 作为对克隆图的引用返回。

    提示：
    - 这张图中的节点数在 [0, 100] 之间
    - 1 <= Node.val <= 100，且每个节点值都是唯一的
    - 图中没有重复的边，也没有自环
    - 图是连通图，你可以从给定节点访问到所有节点

@示例
    示例 1：
    输入：adjList = [[2,4],[1,3],[2,4],[1,3]]
    输出：[[2,4],[1,3],[2,4],[1,3]]
    解释：图中有 4 个节点。节点 1 的邻居是 2 和 4；节点 2 的邻居是 1 和 3；
         节点 3 的邻居是 2 和 4；节点 4 的邻居是 1 和 3。

    示例 2：
    输入：adjList = [[]]
    输出：[[]]
    解释：图仅有一个值为 1 的节点，它没有任何邻居。

    示例 3：
    输入：adjList = []
    输出：[]
    解释：空图，不含任何节点。

@解题思路
    DFS + 哈希表「原节点 -> 克隆节点」（lookup）：
    1. 空节点直接返回 None；
    2. 当前节点已克隆过（在 lookup 中）则直接返回对应副本，防止环导致无限递归，
       也保证每个节点只克隆一次，共享邻居（如菱形结构）复用同一引用；
    3. 否则先创建副本并立刻登记进 lookup（必须在递归邻居之前登记，
       否则回到自身时又会克隆一份），再 DFS 每个邻居填充 clone.neighbors。

    BFS 写法同理：队列 + 同一张 lookup，每次取出节点后为未克隆的邻居建副本入队。
    注：本题不适合并查集——并查集回答的是「两点是否连通 / 有几个连通分量」，
    而本题图本身就是连通的，真正的难点是构造一份节点对象全新、结构同构的图，
    需要的是「原节点 -> 副本」的一一映射，这是遍历 + 哈希表的职责。

    时间复杂度 O(N + E)，空间复杂度 O(N)（N 为节点数，E 为边数，递归栈最深 N 层）

来源：LeetCode
链接：https://leetcode.cn/problems/clone-graph/description/
"""

from __future__ import annotations

from collections import deque


class Node:
    """无向图节点（与 LeetCode 官方定义一致；目前仅本题使用，暂未放进 leetcode_common）。"""

    __slots__ = ("val", "neighbors")

    def __init__(self, val: int = 0, neighbors: list[Node] | None = None) -> None:
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

    def __repr__(self) -> str:
        return f"Node({self.val})"


class Solution:
    def cloneGraph(self, node: Node | None) -> Node | None:
        # 原节点 -> 克隆节点。必须在递归邻居之前登记，环才能在这里被截断。
        lookup: dict[Node, Node] = {}

        def dfs(n: Node | None) -> Node | None:
            if not n:
                return None
            if n in lookup:
                return lookup[n]

            clone = Node(n.val, [])
            lookup[n] = clone
            for ne in n.neighbors:
                clone.neighbors.append(dfs(ne))

            return clone

        return dfs(node)


# ---------------- 测试辅助：邻接表 <-> 图 ----------------


def build_graph(adj_list: list[list[int]]) -> Node | None:
    """LeetCode 邻接表 -> 图，返回值为 1 的节点；空列表返回 None。

    adj_list[i] 是节点 i+1 的邻居值列表（1-indexed），例如 [[2,4],[1,3],[2,4],[1,3]]。
    """
    if not adj_list:
        return None
    nodes = {v: Node(v) for v in range(1, len(adj_list) + 1)}
    for v, neighbors in enumerate(adj_list, start=1):
        nodes[v].neighbors = [nodes[w] for w in neighbors]
    return nodes[1]


def bfs_nodes(node: Node | None) -> list[Node]:
    """BFS 收集从 node 出发可达的所有节点对象（按对象身份去重，而非按 val）。"""
    if node is None:
        return []
    seen: set[int] = set()
    order: list[Node] = []
    queue: deque[Node] = deque([node])
    while queue:
        cur = queue.popleft()
        if id(cur) in seen:
            continue
        seen.add(id(cur))
        order.append(cur)
        queue.extend(cur.neighbors)
    return order


def graph_to_adj(node: Node | None) -> list[list[int]]:
    """图 -> LeetCode 邻接表（节点按 val 升序，邻居也按 val 升序，便于断言）。"""
    nodes = sorted(bfs_nodes(node), key=lambda cur: cur.val)
    return [sorted(nb.val for nb in cur.neighbors) for cur in nodes]


def assert_deep_clone(adj_list: list[list[int]]) -> None:
    """按邻接表建图并克隆，校验：邻接结构一致 + 全部是新对象 + 每个节点只克隆一次。"""
    original = build_graph(adj_list)
    clone = Solution().cloneGraph(original)

    # 1) 邻接关系与原图一致（同时也验证了 build_graph / graph_to_adj 自洽）
    expected = [sorted(nb) for nb in adj_list]
    assert graph_to_adj(original) == expected
    assert graph_to_adj(clone) == expected

    # 2) 深拷贝：克隆图中不能出现任何原图节点对象
    original_ids = {id(n) for n in bfs_nodes(original)}
    clone_nodes = bfs_nodes(clone)
    assert all(id(n) not in original_ids for n in clone_nodes), "克隆图里混入了原图节点"

    # 3) 每个 val 恰好出现一次：没有因为环 / 共享邻居而重复创建节点
    assert sorted(n.val for n in clone_nodes) == list(range(1, len(adj_list) + 1))


def test_solution() -> None:
    # ---- 官方示例 ----
    assert_deep_clone([[2, 4], [1, 3], [2, 4], [1, 3]])  # 示例 1：四节点环
    assert_deep_clone([[]])  # 示例 2：单节点无邻居
    assert Solution().cloneGraph(None) is None  # 示例 3：空图
    assert_deep_clone([])

    # ---- 边界：两节点一条边 ----
    assert_deep_clone([[2], [1]])

    # ---- 链：1-2-3-4-5 ----
    assert_deep_clone([[2], [1, 3], [2, 4], [3, 5], [4]])

    # ---- 星型：中心 1 连所有叶子 ----
    assert_deep_clone([[2, 3, 4, 5], [1], [1], [1], [1]])

    # ---- 三角形 + 尾巴：含环且有共享邻居 ----
    assert_deep_clone([[2, 3], [1, 3], [1, 2, 4], [3]])

    # ---- 菱形：节点 4 可由 2、3 两条路到达，必须只克隆一次 ----
    assert_deep_clone([[2, 3], [1, 4], [1, 4], [2, 3]])

    # ---- 完全图 K5：每个节点与其他所有节点相邻 ----
    n = 5
    assert_deep_clone([[w for w in range(1, n + 1) if w != v] for v in range(1, n + 1)])

    # ---- 题目上限：100 个节点的大环 + 一条弦 1-51 ----
    n = 100
    ring = [[(v - 2) % n + 1, v % n + 1] for v in range(1, n + 1)]  # 环上的前驱 / 后继
    ring[0].append(51)
    ring[50].append(1)
    assert_deep_clone(ring)

    # ---- 独立性：修改克隆的邻居列表不能影响原图（防止只做了浅拷贝） ----
    original = build_graph([[2, 3], [1, 3], [1, 2]])
    clone = Solution().cloneGraph(original)
    assert clone is not None
    clone.neighbors.clear()
    assert graph_to_adj(original) == [[2, 3], [1, 3], [1, 2]]


if __name__ == "__main__":
    test_solution()
    print("✅ No.133 全部测试通过")
