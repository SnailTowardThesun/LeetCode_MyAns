from top150.graph.union_find import UnionFind


def test_initial_state() -> None:
    uf = UnionFind(5)

    # 初始时每个元素自成一集，代表元就是自己。
    assert all(uf.find(x) == x for x in range(5))


def test_union_and_connectivity() -> None:
    uf = UnionFind(6)

    uf.union(0, 1)
    uf.union(1, 2)
    uf.union(3, 4)

    # 连通性 = 两个元素的代表元相同。
    assert uf.find(0) == uf.find(2)
    assert uf.find(1) != uf.find(4)
    assert uf.find(5) != uf.find(0)


def test_repeated_union_is_noop() -> None:
    uf = UnionFind(6)

    uf.union(0, 1)
    uf.union(1, 2)
    root = uf.find(0)

    uf.union(2, 0)  # 已连通：合并是无操作
    uf.union(1, 1)  # 自合并：同样是无操作

    assert uf.find(2) == root
    assert uf.find(0) == uf.find(1) == uf.find(2)


def test_merge_two_groups() -> None:
    uf = UnionFind(6)

    uf.union(0, 1)
    uf.union(1, 2)
    uf.union(3, 4)

    uf.union(4, 2)  # 两个已成分量合并成一个

    assert len({uf.find(x) for x in range(5)}) == 1
    assert uf.find(5) != uf.find(0)


def test_groups_by_pattern() -> None:
    size = 200
    uf = UnionFind(size)

    # 每 4 个连续元素合并成一组，最终应形成 50 个大小为 4 的分量。
    for i in range(0, size, 4):
        uf.union(i, i + 1)
        uf.union(i + 1, i + 2)
        uf.union(i + 2, i + 3)

    groups: dict[int, list[int]] = {}
    for x in range(size):
        groups.setdefault(uf.find(x), []).append(x)

    assert len(groups) == 50
    assert all(len(members) == 4 for members in groups.values())
