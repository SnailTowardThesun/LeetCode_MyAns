"""
@file hot100_141.py
@brief LeetCode 141. 环形链表（Linked List Cycle）— HOT 100

@题目描述
    给定链表头节点 head，判断沿 next 指针访问时能否再次到达某个节点。
    存在环返回 True，否则返回 False。节点值相同不代表访问了同一个节点。
    判题器用 pos 表示尾节点连接的节点下标（从 0 开始），-1 表示无环；
    pos 仅用于构造测试链表，不作为函数参数传入。

@示例
    示例 1：head = [3,2,0,-4]，pos = 1，输出 True。
    示例 2：head = [1,2]，pos = 0，输出 True。
    示例 3：head = [1]，pos = -1，输出 False。

    数据范围：节点数为 [0,10^4]，-10^5 <= Node.val <= 10^5。
    pos 为 -1 或链表中的有效下标。进阶要求 O(1) 额外空间。

@解题思路
    1. slow、fast 从头节点出发，每轮分别前进 1 步、2 步。
    2. fast 没有后继时令其为 None，表示已经到达链表末尾。
    3. 移动后若两个指针指向同一个非空节点，则存在环；到达 None 则无环。
    若有环，两个指针进入环后，fast 每轮相对 slow 多走 1 步，最终一定相遇。
    公共 ListNode 未重写 __eq__，这里的 == 比较的是节点对象身份。

    复杂度：设可达的不同节点数为 n，时间复杂度 O(n)，额外空间复杂度 O(1)。
    算法只移动局部引用，不修改节点值或 next。

来源：LeetCode
链接：https://leetcode.com/problems/linked-list-cycle/description/
"""

from leetcode_common import ListNode


class Solution:
    def hasCycle(self, head: ListNode | None) -> bool:
        slow, fast = head, head

        while slow is not None and fast is not None:
            slow = slow.next

            if fast.next is not None:
                fast = fast.next.next
            else:
                fast = None

            if slow == fast and slow is not None and fast is not None:
                return True
        return False


def test_solution() -> None:
    solution = Solution()
    # (节点值, 尾节点连接的下标, 是否有环)
    cases = [
        ([3, 2, 0, -4], 1, True),  # 官方示例 1
        ([1, 2], 0, True),  # 官方示例 2
        ([1], -1, False),  # 官方示例 3
        ([], -1, False),  # 空链表
        ([1], 0, True),  # 单节点自环
        ([1, 2], -1, False),  # 偶数长度无环
        ([7, 7, 7], -1, False),  # 相同值的独立节点不能误判为环
        ([1, 2, 3, 4], 0, True),  # 环入口在头节点
        ([1, 2, 3, 4], 2, True),  # 非环前缀后接一个短环
        ([1, 2, 3, 4], 3, True),  # 尾节点自环
        ([1, 2, 3, 4, 5], -1, False),  # 奇数长度无环
        ([7, 7, 7], 1, True),  # 相同值且确实有环
    ]

    for values, pos, expected in cases:
        nodes = [ListNode(value) for value in values]
        for i in range(len(nodes) - 1):
            nodes[i].next = nodes[i + 1]
        if pos >= 0:
            nodes[-1].next = nodes[pos]
        head = nodes[0] if nodes else None

        # 使用有限的节点数组保存结构，不能对有环链表调用 to_list。
        before = [(node, node.val, node.next) for node in nodes]
        assert solution.hasCycle(head) is expected
        for node, value, next_node in before:
            assert node.val == value
            assert node.next is next_node


if __name__ == "__main__":
    test_solution()
    print("✅ No.141（HOT 100）12 组测试通过")
