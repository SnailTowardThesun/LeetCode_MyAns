"""
@file hot100_142.py
@brief LeetCode 142. 环形链表 II（Linked List Cycle II）

@题目描述
    给定单链表头节点 head，返回从头出发进入环时遇到的第一个节点。无环时返回 None。
    链表最多有 10^4 个节点，节点值在 [-10^5, 10^5] 之间。求解过程中须保持链表结构。
    测试用 pos 标明尾节点连接的下标，-1 表示无环。函数只接收 head。

@示例
    [3, 2, 0, -4]，pos = 1，返回下标 1 的节点。
    [1, 2]，pos = 0，返回头节点。
    [1]，pos = -1，返回 None。

@解题思路
    快慢指针同时从头出发，每轮分别走两步和一步。若快指针无法再走两步，则无环。
    相遇后让一个指针从头出发，另一个从相遇点出发，两者每轮各走一步，首次重合处即入口。
    设头到入口的距离为 a，环长为 L，入口沿环走到相遇点需要 b 步。
    相遇时快指针多走的距离等于慢指针的总步数，且是 L 的倍数，故 a + b 是 L 的倍数。
    从相遇点再走 a 步恰好回到入口。时间 O(n)，额外空间 O(1)，n 为可达节点数。
"""

from leetcode_common import ListNode


class Solution:
    def detectCycle(self, head: ListNode | None) -> ListNode | None:
        slow = fast = head
        while fast is not None and fast.next is not None:
            # 快指针仍能前进两步，走得更慢的 slow 必然还在链表上。
            assert slow is not None
            slow = slow.next
            fast = fast.next.next
            if slow is fast:
                while head is not slow:
                    # 已确认有环，从头节点或环内出发都不会走到 None。
                    assert head is not None and slow is not None
                    head = head.next
                    slow = slow.next
                return head
        return None


def test_solution() -> None:
    solution = Solution()
    cases = [
        ([3, 2, 0, -4], 1),  # 首次相遇在下标 3，入口在下标 1
        ([1, 2], 0),
        ([1], -1),  # 原实现会在此访问 None.next
        ([], -1),
        ([5], 0),  # 单节点自环
        ([7, 7, 7, 7], -1),
        ([7, 7, 7, 7], 2),  # 节点同值，按身份核对入口
        ([1, 2, 3, 4], 3),  # 长前缀接尾节点自环
    ]
    for values, pos in cases:
        nodes = [ListNode(value) for value in values]
        for left, right in zip(nodes, nodes[1:], strict=False):
            left.next = right
        entry = nodes[pos] if pos >= 0 else None
        if nodes:
            nodes[-1].next = entry
        links = [node.next for node in nodes]

        result = solution.detectCycle(nodes[0] if nodes else None)
        # 失败时显示输入，避免格式化有环链表的节点。
        correct_entry = result is entry
        assert correct_entry, (values, pos)
        assert all(node.next is link for node, link in zip(nodes, links, strict=True))


if __name__ == "__main__":
    test_solution()
