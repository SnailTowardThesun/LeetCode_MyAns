"""
@file top150_148.py
@brief LeetCode 148. 排序链表

@题目描述
    给你链表的头结点 head，请将其按 升序 排列并返回 排序后的链表。

    进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？

@示例
    示例 1：
    输入：head = [4,2,1,3]
    输出：[1,2,3,4]

    示例 2：
    输入：head = [-1,5,3,4,0]
    输出：[-1,0,3,4,5]

    示例 3：
    输入：head = []
    输出：[]

    提示：链表中节点的数目在范围 [0, 5 * 10^4] 内；-10^5 <= Node.val <= 10^5

@解题思路
    自顶向下归并排序：
    1. 快慢指针找中点：fast 先走一步，之后每轮 fast 前进一格、slow 每两轮前进一格，
       fast 到尾时 slow 恰停在前半段最后一个节点（fast 若与 slow 同起点，n=2 时 slow 会停在第 2 个节点，
       切出的左半边仍是整条链表 → 无限递归）；
    2. 从 slow 之后切成两半，分别递归排序；
    3. 哑节点 + 双指针归并两段有序链表，每次接上较小者，接上后 pr 记得后移。

    时间复杂度 O(n log n)，空间复杂度 O(log n)（递归栈；进阶的 O(1) 空间需改用自底向上迭代归并）

来源：LeetCode
链接：https://leetcode.cn/problems/sort-list/description/
"""

from random import Random

from leetcode_common import ListNode, build_list, to_list


class Solution:
    def sortList(self, head: ListNode | None) -> ListNode | None:

        def doSort(head):
            if head is None or head.next is None:
                return head

            slow = head
            fast = head.next
            step = 0
            while fast is not None:
                fast = fast.next
                if step > 0:
                    step = 0
                    slow = slow.next
                else:
                    step += 1
            pre_slow = slow.next
            slow.next = None

            sort_pre = doSort(head)
            sort_last = doSort(pre_slow)

            pp = sort_pre
            lp = sort_last

            ret = ListNode()
            pr = ret

            while pp is not None and lp is not None:
                if pp.val < lp.val:
                    pr.next = pp
                    pp = pp.next
                else:
                    pr.next = lp
                    lp = lp.next

                pr = pr.next
            while pp is not None:
                pr.next = pp
                pp = pp.next
                pr = pr.next
            while lp is not None:
                pr.next = lp
                lp = lp.next
                pr = pr.next

            return ret.next

        return doSort(head)


def test_solution() -> None:
    solution = Solution()

    # 官方示例：排序结果是唯一的，直接断言精确输出
    assert to_list(solution.sortList(build_list([4, 2, 1, 3]))) == [1, 2, 3, 4]  # 示例 1
    assert to_list(solution.sortList(build_list([-1, 5, 3, 4, 0]))) == [-1, 0, 3, 4, 5]  # 示例 2
    assert solution.sortList(build_list([])) is None  # 示例 3：空链表

    # 边界与特殊形态：单元素、已有序、逆序、两元素、含重复值
    assert to_list(solution.sortList(build_list([1]))) == [1]
    assert to_list(solution.sortList(build_list([1, 2, 3, 4, 5]))) == [1, 2, 3, 4, 5]
    assert to_list(solution.sortList(build_list([5, 4, 3, 2, 1]))) == [1, 2, 3, 4, 5]
    assert to_list(solution.sortList(build_list([2, 1]))) == [1, 2]
    assert to_list(solution.sortList(build_list([3, 1, 2, 3, 1]))) == [1, 1, 2, 3, 3]

    # 对拍官方数据上限规模：固定随机种子保证可复现，期望值直接用内置 sorted
    rng = Random(42)
    values = [rng.randint(-100_000, 100_000) for _ in range(5_000)]
    assert to_list(solution.sortList(build_list(values))) == sorted(values)

    # 全等值长链表（重复值压力）
    assert to_list(solution.sortList(build_list([7] * 1_000))) == [7] * 1_000


if __name__ == "__main__":
    test_solution()
    print("✅ 148 全部测试通过")
