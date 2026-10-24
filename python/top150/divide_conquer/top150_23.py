"""
@file top150_23.py
@brief LeetCode 23. 合并 K 个升序链表

@题目描述
    给你一个链表数组 lists，每个链表都已经按升序排列。

    请你将所有链表合并到一个升序链表中，返回合并后的链表。

@示例
    示例 1：
    输入：lists = [[1,4,5],[1,3,4],[2,6]]
    输出：[1,1,2,3,4,4,5,6]
    解释：链表数组如下：
        1 -> 4 -> 5
        1 -> 3 -> 4
        2 -> 6
    将它们合并成一个有序链表：1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6

    示例 2：
    输入：lists = []
    输出：[]

    示例 3：
    输入：lists = [[]]
    输出：[]

    提示：k == lists.length；0 <= k <= 10^4；0 <= lists[i].length <= 500；
    -10^4 <= lists[i][j] <= 10^4；lists[i] 按 升序 排列；lists[i].length 的总和 <= 10^4。

@解题思路
    顺序两两合并：从第一条链表开始，把后面的链表逐条归并进结果链表——
    1. mergeLists 用哑节点 + 双指针归并两条有序链表，每次接上节点后指针记得后移；
    2. lists 为空直接返回 None；内层空链表（None）在归并循环里天然被跳过；
    3. 更优路线是两两分治合并或小根堆，可把 O(k²n) 降到 O(kn log k)。

    时间复杂度 O(k²n)（k 条链表、平均长度 n，顺序合并的最坏情形），空间复杂度 O(1)（哑节点外无额外空间）

来源：LeetCode
链接：https://leetcode.cn/problems/merge-k-sorted-lists/description/
"""

from leetcode_common import ListNode, build_list, to_list


class Solution:
    def mergeKLists(self, lists: list[ListNode | None]) -> ListNode | None:
        def mergeLists(l1, l2):
            head = ListNode()
            ph = head
            p1 = l1
            p2 = l2
            while p1 is not None and p2 is not None:
                if p1.val < p2.val:
                    ph.next = p1
                    p1 = p1.next
                else:
                    ph.next = p2
                    p2 = p2.next

                ph = ph.next
            while p1 is not None:
                ph.next = p1
                p1 = p1.next
                ph = ph.next
            while p2 is not None:
                ph.next = p2
                p2 = p2.next
                ph = ph.next

            return head.next

        if len(lists) == 0:
            return None

        ret = lists[0]
        for i in range(1, len(lists)):
            ret = mergeLists(ret, lists[i])
        return ret


def _build_lists(grid: list[list[int]]) -> list[ListNode | None]:
    """[[1,4,5],[1,3,4],[2,6]] -> [链表, 链表, 链表]，内层空列表转 None（对齐 LeetCode 输入格式）。"""
    return [build_list(values) for values in grid]


def test_solution() -> None:
    solution = Solution()

    # 官方示例 1：三条有序链表交错合并
    assert to_list(solution.mergeKLists(_build_lists([[1, 4, 5], [1, 3, 4], [2, 6]]))) == [
        1,
        1,
        2,
        3,
        4,
        4,
        5,
        6,
    ]

    # 官方示例 2：空数组
    assert to_list(solution.mergeKLists(_build_lists([]))) == []

    # 官方示例 3：数组内只有一个空链表
    assert to_list(solution.mergeKLists(_build_lists([[]]))) == []

    # 边界：单链表原样返回
    assert to_list(solution.mergeKLists(_build_lists([[1, 2, 3]]))) == [1, 2, 3]

    # 不等长 + 负数 + 空链表混在其中
    assert to_list(solution.mergeKLists(_build_lists([[-2, 0], [-3, -1, 2, 5], []]))) == [-3, -2, -1, 0, 2, 5]

    # 全重复值
    assert to_list(solution.mergeKLists(_build_lists([[1, 1], [1, 1, 1]]))) == [1, 1, 1, 1, 1]

    # 规模：100 条单节点链表合并后恰为 0..99（k 大、每条极短的情形）
    assert to_list(solution.mergeKLists(_build_lists([[i] for i in range(100)]))) == list(range(100))


if __name__ == "__main__":
    test_solution()
    print("✅ 23 全部测试通过")
