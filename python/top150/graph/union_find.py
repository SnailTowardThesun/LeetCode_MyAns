"""通用并查集（Disjoint Set Union / Union-Find）实现。"""

from __future__ import annotations


class UnionFind:
    """路径压缩 + 按秩合并的并查集。"""

    def __init__(self, size: int) -> None:
        self._parent = list(range(size))
        self._rank = [0] * size

    def find(self, x: int) -> int:
        if self._parent[x] != x:
            self._parent[x] = self.find(self._parent[x])
        return self._parent[x]

    def union(self, x: int, y: int) -> None:
        root_x, root_y = self.find(x), self.find(y)
        if root_x == root_y:
            return

        # 按秩合并：比较的是两个根的秩，y 只是普通成员时 _rank[y] 没有意义。
        if self._rank[root_x] > self._rank[root_y]:
            self._parent[root_y] = root_x
        elif self._rank[root_x] < self._rank[root_y]:
            self._parent[root_x] = root_y
        else:
            self._parent[root_y] = root_x
            self._rank[root_x] += 1
