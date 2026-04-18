//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 19.cpp
 * @brief LeetCode 19. 删除链表的倒数第 N 个节点
 *
 * @题目描述
 * 给你一个链表，删除链表的倒数第 n 个节点，并且返回链表的头节点。
 *
 * @示例
 * 示例 1：
 * 输入：head = [1,2,3,4,5], n = 2
 * 输出：[1,2,3,5]
 *
 * 示例 2：
 * 输入：head = [1], n = 1
 * 输出：[]
 *
 * 示例 3：
 * 输入：head = [1,2], n = 1
 * 输出：[1]
 *
 * @解题思路
 * 1. 双指针法：
 *    - 使用两个指针，它们之间相隔 n 个节点
 *    - 当第一个指针到达末尾时，第二个指针指向的就是要删除的节点的前一个节点
 *
 * 2. 算法步骤：
 *    - 初始化两个指针，都指向头节点
 *    - 让第一个指针先走 n+1 步
 *    - 然后两个指针一起走，直到第一个指针到达末尾
 *    - 此时第二个指针的下一个节点就是要删除的节点
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(1)
 */

#include <gtest/gtest.h>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
};

TEST(Daily, 19) {
    class Solution {
    public:
        ListNode* removeNthFromEnd(ListNode* head, int n) {
            if (head == NULL) return head;
            ListNode* pr = head;
            ListNode* pe = head;
            for (int i = 0; i <= n; i++) {
                if (!pe) return head->next;
                pe = pe->next;
            }
            while (pe != NULL) {
                pe = pe->next;
                pr = pr->next;
            }
            pr->next = pr->next->next;
            return head;
        }
    };

    Solution s;
    
    // 测试用例 1
    ListNode* head1 = new ListNode();
    head1->val = 1;
    head1->next = new ListNode();
    head1->next->val = 2;
    head1->next->next = new ListNode();
    head1->next->next->val = 3;
    head1->next->next->next = new ListNode();
    head1->next->next->next->val = 4;
    head1->next->next->next->next = new ListNode();
    head1->next->next->next->next->val = 5;
    
    ListNode* result1 = s.removeNthFromEnd(head1, 2);
    EXPECT_EQ(result1->next->next->next->val, 5);
    
    // 测试用例 2
    ListNode* head2 = new ListNode();
    head2->val = 1;
    ListNode* result2 = s.removeNthFromEnd(head2, 1);
    EXPECT_EQ(result2, nullptr);
}
