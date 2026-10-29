"""
@file 3841.py
@brief LeetCode 3841. 查询树上回文路径（Palindromic Path Queries in a Tree）

@题目描述
    给你一棵包含 n 个节点的无向树，节点编号从 0 到 n-1。树由长度为 n-1 的二维数组 edges 表示，
    edges[i] = [ui, vi] 表示节点 ui 和 vi 之间存在一条无向边。
    另给你一个长度为 n、由小写英文字母组成的字符串 s，其中 s[i] 表示分配给节点 i 的字符。
    还给你一个字符串数组 queries，其中每个 queries[i] 为以下形式之一：
      - "update ui c"：将节点 ui 处的字符更改为 c（即 s[ui] = c）；
      - "query ui vi"：判断从 ui 到 vi 的唯一路径（含两端点）上的字符所组成的字符串，
        是否可以重新排列成一个回文串。
    返回一个布尔数组 answer：第 i 个 "query" 型查询可以重排成回文串则 answer[i] 为 true，
    否则为 false。回文串是指正读和反读都相同的字符串。

@示例
    示例 1：
    输入：n = 3, edges = [[0,1],[1,2]], s = "aac", queries = ["query 0 2","update 1 b","query 0 2"]
    输出：[true,false]
    解释：路径 0→1→2 的字符串为 "aac"，可重排为 "aca"；update 1 b 后路径为 "abc"，无法重排成回文串。

    示例 2：
    输入：n = 4, edges = [[0,1],[0,2],[0,3]], s = "abca",
         queries = ["query 1 2","update 0 b","query 2 3","update 3 a","query 1 3"]
    输出：[false,false,true]
    解释：query 1 2 路径为 "bac" 不可行；update 0 b 后 query 2 3 路径为 "cba" 不可行；
    update 3 a（s 不变）后 query 1 3 路径为 "bba"，可重排为 "bab"。

    数据范围：
    1 <= n == s.length <= 5 * 10^4
    edges.length == n - 1
    1 <= queries.length <= 5 * 10^4
    0 <= ui, vi <= n - 1
    s 由小写英文字母组成；c 是小写英文字母
    输入的 edges 表示一棵有效的树

@解题思路
    LCA（倍增）+ 前缀奇偶位图 + Euler 序上的 XOR 树状数组。
    1. 判定条件：路径字符可重排成回文 ⇔ 奇数次出现的字符不超过 1 个。把根→x 路径（含两端）
       上 26 个字符的出现奇偶压成一个位图 pref[x]（第 i 位 = 字符 i 出现奇数次），判定即 popcount ≤ 1。
    2. 路径位图：以 0 为根，mask(u→v) = pref[u] ^ pref[v] ^ bit(s[lca])——根→lca 的公共前缀
       在两侧各出现一次被异或抵消，而 lca 本身在路径上，需单独补回一次。
    3. LCA 用倍增表 up[k][x]（x 的 2^k 级祖先），单次查询 O(log n)。
    4. update 的难点：改 s[u] 会同时翻转 u 整棵子树内所有 pref 的两个字符位。子树在 DFS
       先序（Euler 序）中恰为连续区间 [tin[u], tout[u]]，于是用一棵支持"区间异或 / 单点查询"
       的树状数组维护全部增量：当前前缀 = base[x] ^ 点查(tin[x])，避免每次 update 重建子树。
    5. 全程迭代 DFS，避免深链输入触发递归上限。
    代码组织（四个组件 + 一个调度者，均可整体粘贴提交）：
    - _EulerTree：定根与先序 Euler 序，子树 = 连续区间；
    - _BinaryLiftingLCA：倍增表，find() 单次 O(log n)；
    - _RangeXorBit：0 下标"区间异或 / 单点查询"的树状数组，下标差分细节封装在内部；
    - _RootPathMasks：base 快照 + 增量维护"根→x"当前位图，update() 打子树区间补丁，
      path_mask(u, v, lca) 直接给出路径位图；
    - Solution.palindromePath 只负责解析每条操作并分派。

    时间复杂度 O((n + q) log n)，空间复杂度 O(n log n)

来源：LeetCode
链接：https://leetcode.cn/problems/palindromic-path-queries-in-a-tree/description/
"""


class _EulerTree:
    """无向树以 0 定根：迭代 DFS 求父节点 / 深度 / 先序 Euler 序。

    用手动栈而非递归——n 达 5e4 的链形输入会触发递归上限。
    先序保证父节点先于子节点出现，且子树 u 恰为连续区间，见 subtree_range()。
    """

    def __init__(self, n: int, edges: list[list[int]]) -> None:
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)

        self.parent = [0] * n  # parent[0] = 0：根自指，倍增表跳过头时停在根
        self.depth = [0] * n
        self.tin = [0] * n  # 先序时间戳
        order: list[int] = []
        visited = [False] * n
        visited[0] = True
        stack = [0]
        while stack:
            u = stack.pop()
            order.append(u)
            for w in adj[u]:
                if not visited[w]:
                    visited[w] = True
                    self.parent[w] = u
                    self.depth[w] = self.depth[u] + 1
                    stack.append(w)

        self._order = order
        for i, u in enumerate(order):
            self.tin[u] = i
        size = [1] * n
        for u in reversed(order):  # 逆先序累加子树大小
            if u:  # 根是 0：父是自己，跳过避免把自己加给自己
                size[self.parent[u]] += size[u]
        self._tout = [self.tin[u] + size[u] - 1 for u in range(n)]

    def subtree_range(self, u: int) -> tuple[int, int]:
        """子树 u 在先序中的连续区间（0 下标，双闭）。"""
        return self.tin[u], self._tout[u]

    def prefix_masks(self, chars: list[int]) -> list[int]:
        """base[x] = 根→x（含两端）每个字符出现次数的奇偶位图（第 i 位 = 字符 i 奇数次）。"""
        base = [0] * len(chars)
        for u in self._order:  # 先序保证算 x 时 base[parent[x]] 已就绪；根的父是自己，从 0 起算
            base[u] = base[self.parent[u]] ^ (1 << chars[u])
        return base


class _BinaryLiftingLCA:
    """倍增 LCA：up[k][x] = x 的 2^k 级祖先，预处理 O(n log n)，单次查询 O(log n)。"""

    def __init__(self, parent: list[int], depth: list[int]) -> None:
        n = len(parent)
        self._depth = depth
        self._log = max(1, n.bit_length())  # 深度差 ≤ n-1 < 2^log，步长够用
        self._up = [parent[:]] + [[0] * n for _ in range(self._log - 1)]
        for k in range(1, self._log):
            prev, cur = self._up[k - 1], self._up[k]
            for v in range(n):
                cur[v] = prev[prev[v]]

    def find(self, a: int, b: int) -> int:
        depth, up, log = self._depth, self._up, self._log
        if depth[a] < depth[b]:
            a, b = b, a
        for k in range(log):  # 先把 a 提到与 b 同深度
            if (depth[a] - depth[b]) >> k & 1:
                a = up[k][a]
        if a == b:  # b 本来就是 a 的祖先
            return a
        for k in range(log - 1, -1, -1):  # 从最大步长向下试探，最后停在 lca 的孩子
            if up[k][a] != up[k][b]:
                a, b = up[k][a], up[k][b]
        return up[0][a]


class _RangeXorBit:
    """树状数组：对外提供 0 下标的"区间异或 / 单点查询"，点值 = 覆盖该位置的所有增量之异或。"""

    def __init__(self, n: int) -> None:
        self._n = n
        self._tree = [0] * (n + 1)  # 内部按 1 下标实现

    def range_xor(self, lo: int, hi: int, v: int) -> None:
        """区间 [lo, hi]（0 下标，双闭）整体异或 v——差分成两个单点修改。"""
        self._flip(lo + 1, v)
        self._flip(hi + 2, v)  # 差分右端；越界时 _flip 内部条件自然空操作

    def point_xor(self, i: int) -> int:
        """位置 i（0 下标）累计收到的异或增量。"""
        tree, r = self._tree, 0
        i += 1
        while i:
            r ^= tree[i]
            i -= i & -i
        return r

    def _flip(self, i: int, v: int) -> None:
        tree, n = self._tree, self._n
        while i <= n:
            tree[i] ^= v
            i += i & -i


class _RootPathMasks:
    """维护每个节点"根→自己"路径的字符奇偶位图，支持单点改字符。

    改 s[u] 会翻转 u 整棵子树内所有位图的两个字符位；子树在先序中是连续区间，
    于是用 base（初始快照）+ _RangeXorBit（累计增量）表达当前值，避免逐点重建子树。
    """

    def __init__(self, tree: _EulerTree, chars: list[int]) -> None:
        self._tree = tree
        self._chars = chars  # 每个节点当前字符（0-25），update 时就地修改
        self._base = tree.prefix_masks(chars)
        self._bit = _RangeXorBit(len(chars))

    def update(self, u: int, c: int) -> None:
        """s[u] 改为字符 c（0-25）：对子树区间异或 (旧字符位 ^ 新字符位)。"""
        if self._chars[u] != c:
            delta = (1 << self._chars[u]) ^ (1 << c)
            self._bit.range_xor(*self._tree.subtree_range(u), delta)
            self._chars[u] = c

    def path_mask(self, u: int, v: int, w: int) -> int:
        """u→v 路径（含两端）的字符奇偶位图，w = lca(u, v)。

        pref[u] ^ pref[v] 把根→w 公共前缀（含 w 本身）抵消，w 在路径上需补回一次。
        """
        return self.prefix(u) ^ self.prefix(v) ^ (1 << self._chars[w])

    def prefix(self, x: int) -> int:
        """当前（含全部 update 影响）根→x 的位图。"""
        return self._base[x] ^ self._bit.point_xor(self._tree.tin[x])


class Solution:
    def palindromePath(self, n: int, edges: list[list[int]], s: str, queries: list[str]) -> list[bool]:
        tree = _EulerTree(n, edges)
        lca = _BinaryLiftingLCA(tree.parent, tree.depth)
        masks = _RootPathMasks(tree, [ord(c) - 97 for c in s])

        ans = []
        for ops in queries:
            op, a, b = ops.split()
            if op == "update":  # "update u c"：单点改字符
                masks.update(int(a), ord(b) - 97)
            else:  # "query u v"：奇偶位图中 1 的个数 ≤ 1 ⇔ 可重排成回文
                u, v = int(a), int(b)
                ans.append(masks.path_mask(u, v, lca.find(u, v)).bit_count() <= 1)
        return ans


def test_solution() -> None:
    solution = Solution()
    # 官方示例
    assert solution.palindromePath(3, [[0, 1], [1, 2]], "aac", ["query 0 2", "update 1 b", "query 0 2"]) == [
        True,
        False,
    ]  # 示例 1：更新节点 1 后 "aac"→"abc"，同一查询由真变假
    assert solution.palindromePath(
        4, [[0, 1], [0, 2], [0, 3]], "abca", ["query 1 2", "update 0 b", "query 2 3", "update 3 a", "query 1 3"]
    ) == [False, False, True]  # 示例 2：含"更新成原字符"的无效果 update
    # 边界：单节点树（edges 为空）与自查询
    assert solution.palindromePath(1, [], "a", ["query 0 0", "update 0 b", "query 0 0"]) == [
        True,
        True,
    ]  # u == v 时路径只含一个字符，必然可重排成回文
    # 链形树：同一棵树上不同长度的路径，及更新后的变化
    assert solution.palindromePath(
        5, [[0, 1], [1, 2], [2, 3], [3, 4]], "abcba", ["query 0 4", "query 0 3", "query 1 2", "update 4 c", "query 0 4"]
    ) == [True, False, False, True]
    # 边界：更新为原字符（无效果 update）不应影响结果；换成不同字符后同一查询由真变假
    assert solution.palindromePath(
        2, [[0, 1]], "aa", ["query 0 1", "update 0 a", "query 0 1", "update 1 b", "query 0 1"]
    ) == [True, True, False]
    # 星形树 + 全同字符：任意两点路径都可行
    assert solution.palindromePath(4, [[0, 1], [0, 2], [0, 3]], "aaaa", ["query 1 2", "query 0 3", "query 3 1"]) == [
        True,
        True,
        True,
    ]
    # 混合树（12 节点）：update 翻转结果（假→真、真→假）、query 双向等价（"query 2 5" 与 "query 5 2"）
    # 期望值经独立 BFS 暴力参考实现验证
    assert solution.palindromePath(
        12,
        [[0, 1], [0, 2], [1, 3], [1, 4], [2, 5], [2, 6], [3, 7], [4, 8], [6, 9], [9, 10], [9, 11]],
        "qcdbbefaaghi",
        [
            "query 7 8",
            "query 0 4",
            "query 10 11",
            "update 1 q",
            "query 0 4",
            "query 2 5",
            "query 5 2",
            "update 8 b",
            "query 7 8",
            "query 0 11",
        ],
    ) == [True, False, False, True, False, False, False, False]


if __name__ == "__main__":
    test_solution()
    print("✅ No.3841 全部测试通过")
