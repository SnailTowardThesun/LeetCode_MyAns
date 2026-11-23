"""
@file hot100_234.py
@brief LeetCode 234. 回文链表（Palindrome Linked List）— HOT 100

@题目描述
    给定单链表头节点 head，判断节点值序列是否为回文。
    正序和逆序读到的值完全一致时返回 True，否则返回 False。

@示例
    示例 1：输入 head = [1,2,2,1]，输出 True。
    示例 2：输入 head = [1,2]，输出 False。

    数据范围：节点数为 [1,10^5]，0 <= Node.val <= 9。
    进阶要求 O(n) 时间、O(1) 额外空间；本实现使用数组，额外空间为 O(n)。

@解题思路
    1. 沿 next 遍历链表，将节点值按顺序存入数组 container。
    2. 对 i = 0 到 n // 2 - 1，比较 container[i] 和 container[n - 1 - i]。
    3. 任意一对不同就返回 False，全部相同则返回 True。
    奇数长度的中间元素无需比较；只读取原链表，不改变节点及其连接关系。

    复杂度：设节点数为 n，时间复杂度 O(n)，额外空间复杂度 O(n)。
    可用快慢指针找中点并反转后半段实现 O(1) 额外空间，若要保留原结构，
    比较完还需将后半段反转回来。

来源：LeetCode
链接：https://leetcode.com/problems/palindrome-linked-list/description/
"""

from leetcode_common import ListNode, build_list


class Solution:
    def isPalindrome(self, head: ListNode | None) -> bool:
        container = []
        cur = head
        while cur is not None:
            container.append(cur.val)
            cur = cur.next

        n = len(container)
        for i in range(n // 2):
            if container[i] != container[n - 1 - i]:
                return False
        return True


def test_solution() -> None:
    solution = Solution()
    cases = [
        ([1, 2, 2, 1], True),  # 官方示例 1
        ([1, 2], False),  # 官方示例 2
        ([7], True),  # 单节点
        ([1, 1], True),  # 两个相同节点值
        ([1, 2, 1], True),  # 奇数长度回文
        ([1, 2, 3], False),  # 奇数长度非回文
        ([1, 2, 3, 1], False),  # 外层相同，内层不同
        ([1, 2, 2, 3], False),  # 内层相同，外层不同
        ([0, 9, 9, 0], True),  # 节点值上下界
        ([0, 0, 0, 0], True),  # 全部相同
        ([1, 2, 3, 2, 1], True),  # 多组对称位置
        ([], True),  # 题目范围外的扩展边界：空序列也满足回文条件
    ]

    for values, expected in cases:
        head = build_list(values)
        before = []
        cur = head
        while cur is not None:
            before.append((cur, cur.val, cur.next))
            cur = cur.next

        assert solution.isPalindrome(head) is expected
        for node, value, next_node in before:
            assert node.val == value
            assert node.next is next_node


if __name__ == "__main__":
    test_solution()
    print("✅ No.234（HOT 100）12 组测试通过")
