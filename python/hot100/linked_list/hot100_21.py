"""
@file hot100_21.py
@brief LeetCode 21. 合并两个有序链表（Merge Two Sorted Lists）

@题目描述
    给定两个按非递减顺序排列的单链表，重新连接它们的原节点，返回合并后有序链表的头节点。
    链表允许为空，每条链表最多 50 个节点，节点值在 [-100, 100] 之间。

@示例
    [1, 2, 4] 与 [1, 3, 4] 合并为 [1, 1, 2, 3, 4, 4]。
    [] 与 [] 合并为 []；[] 与 [0] 合并为 [0]。

@解题思路
    空链表与另一条链表合并时，直接返回另一条链表的头节点。
    用哑节点 root 记录结果的起点，cur_r 指向已合并部分的尾部。
    每次从两个待处理的头节点中选取值较小的一个，接到尾部。值相等时先取第一条链表的节点。
    一侧取完后，将另一侧的剩余节点依次接上，返回 root.next。
    设两条链表的长度分别为 m 和 n，时间复杂度 O(m+n)，额外空间复杂度 O(1)。
"""

from leetcode_common import ListNode, build_list


class Solution:
    def mergeTwoLists(self, list1: ListNode | None, list2: ListNode | None) -> ListNode | None:
        if list1 is None:
            return list2
        if list2 is None:
            return list1

        root = ListNode(0)
        cur_r, cur_1, cur_2 = root, list1, list2
        while cur_1 is not None and cur_2 is not None:
            if cur_1.val > cur_2.val:
                cur_r.next = cur_2
                cur_2 = cur_2.next
            else:
                cur_r.next = cur_1
                cur_1 = cur_1.next
            cur_r = cur_r.next

        while cur_1 is not None:
            cur_r.next = cur_1
            cur_1 = cur_1.next
            cur_r = cur_r.next

        while cur_2 is not None:
            cur_r.next = cur_2
            cur_2 = cur_2.next
            cur_r = cur_r.next

        return root.next


def test_solution() -> None:
    solution = Solution()
    cases = [
        ([1, 2, 4], [1, 3, 4]),
        ([], []),
        ([], [0]),
        ([0], []),
        ([1], [2, 3, 4]),
        ([2, 3, 4], [1]),
        ([-100, 0, 0, 100], [-100, 0, 100]),
    ]
    for left, right in cases:
        head1, head2 = build_list(left), build_list(right)
        remaining = set()
        for node in (head1, head2):
            while node is not None:
                remaining.add(node)
                node = node.next

        node = solution.mergeTwoLists(head1, head2)
        for value in sorted(left + right):
            assert node is not None and node.val == value
            assert node in remaining
            remaining.remove(node)
            node = node.next
        assert node is None
        assert not remaining


if __name__ == "__main__":
    test_solution()
