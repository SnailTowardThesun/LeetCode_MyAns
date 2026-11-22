"""
@file 160.py
@brief LeetCode 160. 相交链表（Intersection of Two Linked Lists）— HOT 100

@题目描述
    给定两个无环单链表的头节点 headA 和 headB，返回它们的第一个公共节点；
    如果不相交，返回 None。相交指引用同一个节点对象，节点值相同不代表相交。
    函数返回后，两个链表必须保持原有结构。

@示例
    示例 1：A = [4,1,8,4,5]，B = [5,6,1,8,4,5]，
    A 跳过 2 个节点、B 跳过 3 个节点后，共享尾部 [8,4,5]，返回公共节点 8。

    示例 2：A = [1,9,1,2,4]，B = [3,2,4]，
    A 跳过 3 个节点、B 跳过 1 个节点后，共享尾部 [2,4]，返回公共节点 2。

    示例 3：A = [2,6,4]，B = [1,5]，没有公共节点，返回 None。

    数据范围：1 <= m, n <= 3 * 10^4，1 <= Node.val <= 10^5。
    判题器根据 intersectVal、listA、listB、skipA、skipB 构造链表，
    函数实际只接收 headA 和 headB；skipA、skipB 表示交点前的节点数。
    进阶要求 O(m+n) 时间、O(1) 额外空间，本实现使用哈希集合，额外空间为 O(m)。

@解题思路
    1. 遍历链表 A，把所有节点对象加入集合 set_a。
    2. 从头遍历链表 B，第一个存在于 set_a 的节点就是第一个公共节点。
    3. 遍历完 B 仍未命中则返回 None；只读取 next，不修改链表。
    公共 ListNode 没有重写 __eq__ / __hash__，集合按对象身份区分节点。

    复杂度：设 m、n 分别为 A、B 的长度，哈希操作平均 O(1) 时，
    时间复杂度 O(m+n)，额外空间复杂度 O(m)。

来源：LeetCode
链接：https://leetcode.com/problems/intersection-of-two-linked-lists/description/
"""

from leetcode_common import ListNode, build_list


class Solution:
    def getIntersectionNode(self, headA: ListNode | None, headB: ListNode | None) -> ListNode | None:
        set_a = set()
        cur = headA
        while cur is not None:
            set_a.add(cur)  # 保存节点对象，而非 cur.val
            cur = cur.next
        cur = headB
        while cur is not None:
            if cur in set_a:
                return cur
            cur = cur.next
        return None


def test_solution() -> None:
    solution = Solution()

    # (A 独有前缀, B 独有前缀, 共享尾部)：共享尾部只构造一次。
    cases = [
        ([4, 1], [5, 6, 1], [8, 4, 5]),  # 官方示例 1：值相同的前缀节点不是交点
        ([1, 9, 1], [3], [2, 4]),  # 官方示例 2：前缀长度不同
        ([2, 6, 4], [1, 5], []),  # 官方示例 3：不相交
        ([1, 2, 3], [1, 2, 3], []),  # 值完全相同，节点对象各自独立
        ([], [], [7]),  # 同一个单节点，头节点就是交点
        ([], [1, 2], [3, 4]),  # A 的头节点位于 B 中
        ([1, 2], [], [3, 4]),  # B 的头节点位于 A 中
        ([1, 2], [3], [9]),  # 仅尾节点相交
        ([1], [1], []),  # 两个同值的独立单节点
        ([], [1], []),  # 扩展边界：A 为空
        ([1], [], []),  # 扩展边界：B 为空
        ([], [], []),  # 扩展边界：两个链表都为空
    ]

    def prepend(values: list[int], tail: ListNode | None) -> ListNode | None:
        for value in reversed(values):
            tail = ListNode(value, tail)
        return tail

    for prefix_a, prefix_b, common in cases:
        shared = build_list(common)
        head_a = prepend(prefix_a, shared)
        head_b = prepend(prefix_b, shared)

        # 保存节点及 next 引用，验证调用后原有结构和节点值均未改变。
        before = []
        for head in (head_a, head_b):
            cur = head
            while cur is not None:
                before.append((cur, cur.val, cur.next))
                cur = cur.next

        assert solution.getIntersectionNode(head_a, head_b) is shared
        for node, value, next_node in before:
            assert node.val == value
            assert node.next is next_node


if __name__ == "__main__":
    test_solution()
    print("✅ No.160（HOT 100）12 组测试通过")
