"""
@file hot100_2.py
@brief LeetCode 2. 两数相加（Add Two Numbers）

@题目描述
    两条非空单链表分别表示两个非负整数，从头到尾按个位、十位、百位的顺序存储数字。
    将它们相加，返回同样按低位在前排列的结果链表。每条输入链表有 1 到 100 个节点，
    每个节点的值在 0 到 9 之间，除数字 0 外，输入整数的最高位均非零。

@示例
    [2, 4, 3] + [5, 6, 4] 得到 [7, 0, 8]，即 342 + 465 = 807。
    [0] + [0] 得到 [0]。
    [9, 9, 9] + [1] 得到 [0, 0, 0, 1]，即 999 + 1 = 1000。

@解题思路
    从两个头节点开始模拟竖式加法。当前两位与进位之和至多为 19，
    满十就减十写入结果，并向下一位进一。较短链表耗尽后，继续把进位加到较长链表的剩余位。
    最后一位算完若仍有进位，在尾部追加节点 1。哑节点的后继就是结果头节点。
    设输入长度为 m、n，时间为 O(max(m,n))，额外空间为 O(1)，输出链表占 O(max(m,n))。
"""

from leetcode_common import ListNode, build_list, to_list


class Solution:
    def addTwoNumbers(self, l1: ListNode | None, l2: ListNode | None) -> ListNode | None:
        if l1 is None:
            return l2
        if l2 is None:
            return l1

        root = ListNode(0)
        carry = 0

        cur, cur_1, cur_2 = root, l1, l2
        while cur_1 is not None and cur_2 is not None:
            val = cur_1.val + cur_2.val + carry
            if val > 9:
                val = val - 10
                carry = 1
            else:
                carry = 0

            n = ListNode(val)
            cur.next = n
            cur = cur.next

            cur_1 = cur_1.next
            cur_2 = cur_2.next

        while cur_1 is not None:
            val = cur_1.val + carry
            if val > 9:
                val = val - 10
                carry = 1
            else:
                carry = 0
            n = ListNode(val)
            cur.next = n
            cur = cur.next
            cur_1 = cur_1.next

        while cur_2 is not None:
            val = cur_2.val + carry
            if val > 9:
                val = val - 10
                carry = 1
            else:
                carry = 0
            n = ListNode(val)
            cur.next = n
            cur = cur.next
            cur_2 = cur_2.next

        if carry > 0:
            cur.next = ListNode(carry)

        return root.next


def test_solution() -> None:
    solution = Solution()
    cases = [
        ([2, 4, 3], [5, 6, 4], [7, 0, 8]),
        ([0], [0], [0]),
        ([9] * 7, [9] * 4, [8, 9, 9, 9, 0, 0, 0, 1]),
        ([1], [9] * 100, [0] * 100 + [1]),  # 第二条链表更长，连续进位到新最高位
        ([9, 0, 4], [1], [0, 1, 4]),  # 进位在第一条链表的中途消失
        ([0], [0, 0, 1], [0, 0, 1]),  # 100 + 0，低位的零需要保留
        ([9], [9], [8, 1]),  # 等长且产生最后一次进位
    ]
    for left, right, expected in cases:
        result = solution.addTwoNumbers(build_list(left), build_list(right))
        assert to_list(result) == expected


if __name__ == "__main__":
    test_solution()
