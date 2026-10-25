"""通用并查集（Disjoint Set Union / Union-Find）实现。"""

from __future__ import annotations

from collections.abc import Iterable


class UnionFind:
    """基于路径压缩与按大小合并的并查集。

    元素固定为 ``0 .. size-1``，适合图的顶点编号、数组下标等连续整数场景。
    两个优化结合后，单次操作的均摊时间复杂度近似为 O(alpha(size))，
    其中 alpha 是反阿克曼函数，在常规数据规模下可视为常数。
    """

    __slots__ = ("_parent", "_size", "_count")

    def __init__(self, size: int) -> None:
        """初始化 ``size`` 个互不相连的元素。

        Args:
            size: 元素个数，必须为非负整数。
        """
        if size < 0:
            raise ValueError("size must be non-negative")

        # 初始时每个元素都是一个独立集合，父节点指向自己。
        self._parent = list(range(size))
        # 记录每棵树根节点对应的集合大小，只保证根节点的值有效。
        self._size = [1] * size
        # 当前连通分量个数。
        self._count = size

    @property
    def count(self) -> int:
        """当前集合（连通分量）个数。"""
        return self._count

    def find(self, x: int) -> int:
        """返回元素 ``x`` 所在集合的代表元素（树根）。

        使用两趟路径压缩：第一趟找到根，第二趟把路径上的节点直接挂到根上，
        让后续查询越来越接近 O(1)。
        """
        self._validate(x)

        root = x
        while self._parent[root] != root:
            root = self._parent[root]

        while self._parent[x] != root:
            self._parent[x], x = root, self._parent[x]

        return root

    def union(self, x: int, y: int) -> bool:
        """合并 ``x`` 与 ``y`` 所在集合。

        Returns:
            若二者原本不在同一集合并成功合并，返回 ``True``；
            若已经连通，则不改动结构并返回 ``False``。
        """
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False

        # 按大小合并：把小树挂到大树下，避免树退化成链表。
        if self._size[root_x] < self._size[root_y]:
            root_x, root_y = root_y, root_x

        self._parent[root_y] = root_x
        self._size[root_x] += self._size[root_y]
        self._count -= 1
        return True

    def union_all(self, pairs: Iterable[tuple[int, int]]) -> int:
        """依次合并若干 ``(x, y)`` 边，返回实际发生合并的次数。"""
        merged_count = 0
        for x, y in pairs:
            if self.union(x, y):
                merged_count += 1
        return merged_count

    def connected(self, x: int, y: int) -> bool:
        """判断 ``x`` 与 ``y`` 是否属于同一个集合。"""
        return self.find(x) == self.find(y)

    def size(self, x: int) -> int:
        """返回 ``x`` 所在集合的元素个数。"""
        return self._size[self.find(x)]

    def groups(self) -> list[list[int]]:
        """按代表元素分组，返回所有非空集合。

        每组内部按元素编号升序排列，组间按首个元素升序排列，便于测试和展示。
        """
        grouped: dict[int, list[int]] = {}
        for x in range(len(self._parent)):
            grouped.setdefault(self.find(x), []).append(x)
        return sorted(grouped.values(), key=lambda group: group[0])

    def _validate(self, x: int) -> None:
        """校验元素下标，尽早暴露越界错误。"""
        if not 0 <= x < len(self._parent):
            raise IndexError(f"element {x} is out of range [0, {len(self._parent) - 1}]")

    def __len__(self) -> int:
        """返回元素总数，而不是集合个数。"""
        return len(self._parent)

    def __repr__(self) -> str:
        """展示元素个数、集合个数和当前分组。"""
        return f"UnionFind(size={len(self)}, count={self._count}, groups={self.groups()})"
