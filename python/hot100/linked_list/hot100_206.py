"""
@file hot100_206.py
@brief LeetCode 206. 反转链表（Reverse Linked List）— HOT 100

@题目描述
    给定单链表的头节点 head，返回反转后的链表。
    本实现收集节点值并逆序重建链表，返回全新的节点，原链表保持不变。

@示例
    示例 1：输入 head = [1,2,3,4,5]，输出 [5,4,3,2,1]。
    示例 2：输入 head = [1,2]，输出 [2,1]。
    示例 3：输入 head = []，输出 []。

    数据范围：链表节点数为 [0,5000]，-5000 <= Node.val <= 5000。
    进阶：分别用迭代和递归实现反转。

@解题思路
    1. 顺序遍历链表，把节点值存入数组 container。
    2. 调用 container.reverse()，将数组中的值原地逆序排列。
    3. 从哑节点 ret 出发，按逆序后的值依次创建节点并连接，返回 ret.next。
    空链表对应空数组，不会创建数据节点，ret.next 自然为 None。
    reverse() 只修改数组，不会改变原链表的 next 引用。

    复杂度：设节点数为 n，时间复杂度 O(n)；额外空间复杂度 O(n)，
    即使不计返回链表，存储节点值的数组仍占 O(n)。新链表本身也占 O(n) 空间。
    若需要复用原节点并达到 O(1) 额外空间，可改用迭代法逐个翻转 next 指针。

来源：LeetCode
链接：https://leetcode.com/problems/reverse-linked-list/description/
"""

from leetcode_common import ListNode, build_list


class Solution:
    def reverseList(self, head: ListNode | None) -> ListNode | None:
        container = []
        cur = head
        while cur is not None:
            container.append(cur.val)
            cur = cur.next

        container.reverse()

        ret = ListNode(0)  # 哑节点，统一处理空链表和第一个节点
        cur = ret
        for i in container:
            cur.next = ListNode(i)
            cur = cur.next

        return ret.next


def test_solution() -> None:
    solution = Solution()
    cases = [
        ([1, 2, 3, 4, 5], [5, 4, 3, 2, 1]),  # 官方示例 1
        ([1, 2], [2, 1]),  # 官方示例 2
        ([], []),  # 官方示例 3：空链表
        ([7], [7]),  # 单节点
        ([2, 2, 2], [2, 2, 2]),  # 全部相同
        ([-2, 0, 3], [3, 0, -2]),  # 负数、零与正数
        ([-5000, 5000], [5000, -5000]),  # 节点值上下界
        ([1, 2, 1, 2], [2, 1, 2, 1]),  # 交替重复值
        ([1, 2, 3, 2, 1], [1, 2, 3, 2, 1]),  # 回文序列
    ]

    for values, expected in cases:
        head = build_list(values)
        before = []
        cur = head
        while cur is not None:
            before.append((cur, cur.val, cur.next))
            cur = cur.next
        original_nodes = {node for node, _, _ in before}

        result = solution.reverseList(head)
        # 按预期长度检查值和节点身份，末尾必须为 None，也能发现意外形成的环。
        cur = result
        for value in expected:
            assert cur is not None
            assert cur.val == value
            assert cur not in original_nodes
            cur = cur.next
        assert cur is None

        # 本实现返回新链表，原节点的值及 next 引用均保持不变。
        for node, value, next_node in before:
            assert node.val == value
            assert node.next is next_node


if __name__ == "__main__":
    test_solution()
    print("✅ No.206（HOT 100）9 组测试通过")
