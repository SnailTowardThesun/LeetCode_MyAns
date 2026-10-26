"""
@file top150_399.py
@brief LeetCode 399. Evaluate Division（除法求值）

@题目描述
    给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中
    equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i]。
    每个 Ai 或 Bi 是一个表示单个变量的字符串。

    另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，
    请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。

    返回 所有问题的答案。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。
    如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。

    注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，
    且不存在任何矛盾的结果。
    注意：未在等式列表中出现的变量是未定义的，因此无法确定它们的答案。

    提示：
    - 1 <= equations.length <= 20
    - equations[i].length == 2，1 <= Ai.length, Bi.length <= 5
    - values.length == equations.length，0.0 < values[i] <= 20.0
    - 1 <= queries.length <= 20
    - queries[i].length == 2，1 <= Cj.length, Dj.length <= 5
    - Ai, Bi, Cj, Dj 由小写英文字母与数字组成

@示例
    示例 1：
    输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0],
         queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
    输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
    解释：条件：a / b = 2.0, b / c = 3.0
         问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
         结果：[6.0, 0.5, -1.0, 1.0, -1.0]
         注意：x 是未定义的 => -1.0

    示例 2：
    输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0],
         queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
    输出：[3.75000,0.40000,5.00000,0.20000]

    示例 3：
    输入：equations = [["a","b"]], values = [0.5],
         queries = [["a","b"],["b","a"],["a","c"],["x","x"]]
    输出：[0.50000,2.00000,-1.00000,-1.00000]

@解题思路
    带权并查集：普通并查集只回答"连不连通"，本题还要回答"比值是多少"，
    所以给每个节点加一个权值 weight[x] = x 的值 / parent[x] 的值（根恒为 1）。
    1. 变量是字符串，先扫一遍 equations 给每个变量分配递增下标（最多 40 个）；
    2. 对每条等式 a / b = v：先 find 两端（顺带把 weight[a]、weight[b] 刷成相对各自根），
       同根跳过；否则把 a 的根挂到 b 的根下，权值由 a/b = v 推出：
       weight[root_a] = v · weight[b] / weight[a]；
    3. find 做路径压缩时权值同步累乘：先递归让父亲 p 直接挂到根（weight[p] = p/root），
       再 weight[x] *= weight[p] 得到 x/root，最后才改 parent——顺序反了只在链深 ≥ 3 时露馅；
    4. 查询 c / d：任一变量没出现过或两者根不同 → -1；同根则
       c/d = (c/root)/(d/root) = weight[c] / weight[d]，c == d 时自然得 1.0。

    时间复杂度 O((E + Q)·α(V))，空间复杂度 O(V)（V 为变量数，E 为等式数，Q 为查询数）

来源：LeetCode
链接：https://leetcode.cn/problems/evaluate-division/description/
"""

import math


class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.weight = [1.0] * n

    def find(self, x):
        if self.parent[x] != x:
            p = self.parent[x]
            root = self.find(p)
            self.weight[x] *= self.weight[p]
            self.parent[x] = root
        return self.parent[x]

    def union(self, x, y, v):
        root_x, root_y = self.find(x), self.find(y)
        if root_x == root_y:
            return

        self.parent[root_x] = root_y
        self.weight[root_x] = v * self.weight[y] / self.weight[x]


class Solution:
    def calcEquation(self, equations: list[list[str]], values: list[float], queries: list[list[str]]) -> list[float]:
        ids = {}
        for a, b in equations:
            for s in (a, b):
                if s not in ids:
                    ids[s] = len(ids)

        uf = UnionFind(len(ids))
        for (a, b), v in zip(equations, values, strict=True):
            uf.union(ids[a], ids[b], v)

        res = []
        for c, d in queries:
            if c not in ids or d not in ids:
                res.append(-1.0)
            elif uf.find(ids[c]) != uf.find(ids[d]):
                res.append(-1.0)
            else:
                res.append(uf.weight[ids[c]] / uf.weight[ids[d]])

        return res


def assert_close(actual: list[float], expected: list[float]) -> None:
    """浮点逐项比较（LeetCode 判题允许 1e-5 误差）。"""
    assert len(actual) == len(expected), f"长度不一致: {actual} vs {expected}"
    for i, (a, e) in enumerate(zip(actual, expected, strict=True)):
        assert math.isclose(a, e, rel_tol=1e-9, abs_tol=1e-5), f"第 {i} 项: {a} != {e}"


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert_close(
        solution.calcEquation(
            [["a", "b"], ["b", "c"]],
            [2.0, 3.0],
            [["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"]],
        ),
        [6.0, 0.5, -1.0, 1.0, -1.0],
    )
    assert_close(
        solution.calcEquation(
            [["a", "b"], ["b", "c"], ["bc", "cd"]],
            [1.5, 2.5, 5.0],
            [["a", "c"], ["c", "b"], ["bc", "cd"], ["cd", "bc"]],
        ),
        [3.75, 0.4, 5.0, 0.2],
    )
    assert_close(
        solution.calcEquation(
            [["a", "b"]],
            [0.5],
            [["a", "b"], ["b", "a"], ["a", "c"], ["x", "x"]],
        ),
        [0.5, 2.0, -1.0, -1.0],
    )

    # ---- 查询恰好就是已知等式本身 / 其倒数 ----
    assert_close(solution.calcEquation([["a", "b"]], [4.0], [["a", "b"], ["b", "a"]]), [4.0, 0.25])

    # ---- 自己除自己：变量已知为 1.0，变量未知仍为 -1.0 ----
    assert_close(solution.calcEquation([["a", "b"]], [2.0], [["a", "a"], ["b", "b"], ["z", "z"]]), [1.0, 1.0, -1.0])

    # ---- 一端已知、一端未知 -> -1 ----
    assert_close(solution.calcEquation([["a", "b"]], [2.0], [["a", "q"], ["q", "b"]]), [-1.0, -1.0])

    # ---- 长链传递：a/b=2, b/c=3, c/d=4 ----
    eq = [["a", "b"], ["b", "c"], ["c", "d"]]
    vals = [2.0, 3.0, 4.0]
    assert_close(
        solution.calcEquation(eq, vals, [["a", "d"], ["d", "a"], ["b", "d"], ["a", "c"]]),
        [24.0, 1 / 24, 12.0, 6.0],
    )

    # ---- 两个互不连通的分量：组内可算，跨组 -1 ----
    eq = [["a", "b"], ["x", "y"]]
    vals = [2.0, 4.0]
    assert_close(
        solution.calcEquation(eq, vals, [["a", "b"], ["x", "y"], ["y", "x"], ["a", "x"], ["b", "y"]]),
        [2.0, 4.0, 0.25, -1.0, -1.0],
    )

    # ---- 两个分量被后出现的等式"桥接"后全部可达（等式顺序不应影响结果） ----
    eq = [["a", "b"], ["c", "d"], ["b", "c"]]
    vals = [2.0, 5.0, 3.0]
    assert_close(solution.calcEquation(eq, vals, [["a", "d"], ["d", "a"]]), [30.0, 1 / 30])

    # ---- 等式构成环（题目保证无矛盾）：a/b=2, b/c=3, c/a=1/6 ----
    eq = [["a", "b"], ["b", "c"], ["c", "a"]]
    vals = [2.0, 3.0, 1 / 6]
    assert_close(solution.calcEquation(eq, vals, [["a", "c"], ["c", "a"], ["b", "a"]]), [6.0, 1 / 6, 0.5])

    # ---- 星型：多个变量都以 a 为分子给出，叶子之间也要能互相换算 ----
    eq = [["a", "b"], ["a", "c"], ["a", "d"]]
    vals = [2.0, 4.0, 8.0]
    assert_close(solution.calcEquation(eq, vals, [["b", "c"], ["c", "d"], ["d", "b"]]), [2.0, 2.0, 0.25])

    # ---- 小数与上限值：0.5 与 20.0 ----
    eq = [["p", "q"], ["q", "r"]]
    vals = [0.5, 20.0]
    assert_close(solution.calcEquation(eq, vals, [["p", "r"], ["r", "p"]]), [10.0, 0.1])

    # ---- 变量名含数字 / 多字符（题目允许小写字母与数字） ----
    eq = [["x1", "x2"], ["x2", "x3"]]
    vals = [3.0, 3.0]
    assert_close(solution.calcEquation(eq, vals, [["x1", "x3"], ["x3", "x1"], ["x1", "y1"]]), [9.0, 1 / 9, -1.0])


if __name__ == "__main__":
    test_solution()
    print("✅ No.399 全部测试通过")
