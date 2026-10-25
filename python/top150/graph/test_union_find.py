from top150.graph.union_find import UnionFind


def test_initial_state() -> None:
    uf = UnionFind(5)

    assert len(uf) == 5
    assert uf.count == 5
    assert uf.groups() == [[0], [1], [2], [3], [4]]
    assert all(uf.size(x) == 1 for x in range(5))


def test_union_and_connected() -> None:
    uf = UnionFind(6)

    assert uf.union(0, 1) is True
    assert uf.union(1, 2) is True
    assert uf.union(3, 4) is True
    # 0、1、2 已经连通，重复合并不会产生新的连通分量。
    assert uf.union(2, 0) is False

    assert uf.connected(0, 2) is True
    assert uf.connected(1, 4) is False
    assert uf.count == 3
    assert uf.size(2) == 3
    assert uf.size(4) == 2
    assert uf.groups() == [[0, 1, 2], [3, 4], [5]]


def test_union_all_returns_merged_count() -> None:
    uf = UnionFind(5)

    assert uf.union_all([(0, 1), (1, 2), (2, 0), (3, 4)]) == 3
    assert uf.count == 2
    assert uf.connected(0, 2) is True
    assert uf.connected(3, 4) is True
    assert not uf.connected(0, 4)


def test_empty_and_invalid_size() -> None:
    assert len(UnionFind(0)) == 0
    assert UnionFind(0).count == 0
    assert UnionFind(0).groups() == []
    try:
        UnionFind(-1)
    except ValueError as error:
        assert str(error) == "size must be non-negative"
    else:
        raise AssertionError("UnionFind(-1) should raise ValueError")


def test_invalid_element() -> None:
    uf = UnionFind(3)

    for element in (-1, 3):
        try:
            uf.find(element)
        except IndexError as error:
            assert "out of range" in str(error)
        else:
            raise AssertionError(f"find({element}) should raise IndexError")
