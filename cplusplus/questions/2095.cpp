//
// Created by hankun on 6/15/26.
//

/**
 * @file 2095.cpp
 * @brief LeetCode 2095. Delete the Middle of the Linked List（删除链表的中间节点）
 *
 * @题目描述
 * 给你一个链表的头节点 head，删除链表的中间节点，并返回修改后的链表的头节点。
 * 链表的中间节点定义为：如果链表中的节点数目为奇数，则返回中间节点；
 * 如果为偶数，则返回两个中间节点中后面的那个。
 *
 * @示例
 * 示例 1：
 * 输入: head = [1,3,4,7,1,2,6]
 * 输出: [1,3,4,1,2,6]
 * 解释:
 * 链表共7个节点，中间节点是值为7的第4个节点。删除后链表为[1,3,4,1,2,6]。
 *
 * 示例 2：
 * 输入: head = [1,2,3,4]
 * 输出: [1,2,4]
 * 解释:
 * 链表共4个节点，中间节点是值为3的第2个节点。删除后链表为[1,2,4]。
 *
 * 示例 3：
 * 输入: head = [1]
 * 输出: []
 * 解释:
 * 链表只有1个节点，删除中间节点后链表为空。
 *
 * @解题思路
 * 使用快慢指针法：
 * 1. 使用快慢指针找到链表的中间节点
 * 2. 快指针每次移动两步，慢指针每次移动一步
 * 3. 当快指针到达末尾时，慢指针指向的就是中间节点
 * 4. 使用一个前置指针记录慢指针的前一个节点
 * 5. 通过前置指针删除中间节点
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，其中 n 是链表节点数，快慢指针各遍历一次
 * - 空间复杂度: O(1)，只使用了几个指针变量
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {
    }

    ListNode(int x) : val(x), next(nullptr) {
    }

    ListNode(int x, ListNode *next) : val(x), next(next) {
    }
};

class Solution {
public:
    ListNode *deleteMiddle(ListNode *head) {
        if (head->next == nullptr) {
            return nullptr;
        }
        ListNode *pre = head;
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        pre->next = slow->next;

        return head;
    }
};

TEST(Daily, 2095) {
    Solution s;

    ListNode *head1 = new ListNode(1);
    head1->next = new ListNode(3);
    head1->next->next = new ListNode(4);
    head1->next->next->next = new ListNode(7);
    head1->next->next->next->next = new ListNode(1);
    head1->next->next->next->next->next = new ListNode(2);
    head1->next->next->next->next->next->next = new ListNode(6);
    auto result1 = s.deleteMiddle(head1);
    EXPECT_EQ(result1->next->next->val, 4);

    ListNode *head2 = new ListNode(1);
    head2->next = new ListNode(2);
    head2->next->next = new ListNode(3);
    head2->next->next->next = new ListNode(4);
    auto result2 = s.deleteMiddle(head2);
    EXPECT_EQ(result2->next->next->val, 4);

    ListNode *head3 = new ListNode(1);
    auto result3 = s.deleteMiddle(head3);
    EXPECT_EQ(result3, nullptr);
}
