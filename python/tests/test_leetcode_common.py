"""框架自检：验证 leetcode_common 构造/还原工具可用（非题解）。"""

from leetcode_common import build_list, build_tree, to_list, tree_to_level


def test_list_round_trip() -> None:
    assert to_list(build_list([1, 2, 3])) == [1, 2, 3]
    assert to_list(build_list([])) == []


def test_tree_round_trip() -> None:
    values: list[int | None] = [3, 9, 20, None, None, 15, 7]
    assert tree_to_level(build_tree(values)) == values
    assert tree_to_level(build_tree([])) == []
