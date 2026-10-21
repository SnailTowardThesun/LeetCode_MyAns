"""LeetCode 题解通用数据结构与构造工具。

需要链表/二叉树的题解统一 `from leetcode_common import ...`，
禁止在题解 .py 文件中重复定义 ListNode/TreeNode（对齐 cplusplus/leetcode_common.h 的约定）。
"""

from __future__ import annotations

from collections import deque
from collections.abc import Iterable

__all__ = [
    "ListNode",
    "TreeNode",
    "build_list",
    "to_list",
    "build_tree",
    "tree_to_level",
]


class ListNode:
    """链表节点（与 LeetCode 官方定义一致）。"""

    __slots__ = ("val", "next")

    def __init__(self, val: int = 0, next: ListNode | None = None) -> None:
        self.val = val
        self.next = next

    def __repr__(self) -> str:
        return " -> ".join(map(str, to_list(self))) or "None"


class TreeNode:
    """二叉树节点（与 LeetCode 官方定义一致）。"""

    __slots__ = ("val", "left", "right")

    def __init__(self, val: int = 0, left: TreeNode | None = None, right: TreeNode | None = None) -> None:
        self.val = val
        self.left = left
        self.right = right

    def __repr__(self) -> str:
        return f"TreeNode({tree_to_level(self)})"


def build_list(values: Iterable[int]) -> ListNode | None:
    """列表 -> 链表：[1, 2, 3] 转为 1 -> 2 -> 3，空序列返回 None。"""
    dummy = ListNode()
    tail = dummy
    for v in values:
        tail.next = ListNode(v)
        tail = tail.next
    return dummy.next


def to_list(head: ListNode | None) -> list[int]:
    """链表 -> 列表，便于断言与打印。"""
    values: list[int] = []
    while head:
        values.append(head.val)
        head = head.next
    return values


def build_tree(values: Iterable[int | None]) -> TreeNode | None:
    """层序数组 -> 二叉树，None 表示空位。

    例：[3, 9, 20, None, None, 15, 7] 对应 LeetCode 常见的层序输入格式。
    """
    vals = iter(values)
    first = next(vals, None)
    if first is None:
        return None
    root = TreeNode(first)
    queue: deque[TreeNode] = deque([root])
    while queue:
        node = queue.popleft()
        left = next(vals, None)
        if left is not None:
            node.left = TreeNode(left)
            queue.append(node.left)
        right = next(vals, None)
        if right is not None:
            node.right = TreeNode(right)
            queue.append(node.right)
    return root


def tree_to_level(root: TreeNode | None) -> list[int | None]:
    """二叉树 -> 层序数组（LeetCode 输出格式，保留中间空位，仅去掉尾部空位）。"""
    if root is None:
        return []
    values: list[int | None] = []
    queue: deque[TreeNode | None] = deque([root])
    while queue:
        node = queue.popleft()
        values.append(node.val if node else None)
        if node:
            queue.append(node.left)
            queue.append(node.right)
    while values and values[-1] is None:
        values.pop()
    return values
