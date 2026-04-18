//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 24.cpp
 * @brief LeetCode 24. 两两交换链表中的节点
 *
 * @题目描述
 * 给你一个链表，两两交换相邻的节点，并返回交换后的链表。
 * 你不能只是修改节点内部的值，而是需要实际的进行节点交换。
 *
 * @示例
 * 示例 1：
 * 输入：head = [1,2,3,4]
 * 输出：[2,1,4,3]
 *
 * 示例 2：
 * 输入：head = []
 * 输出：[]
 *
 * 示例 3：
 * 输入：head = [1]
 * 输出：[1]
 *
 * @解题思路
 * 1. 迭代法：
 *    - 使用四个指针：pre、cur、next、nextNext
 *    - 不断交换相邻的两个节点
 *
 * 2. 算法步骤：
 *    - 初始化指针
 *    - 循环交换相邻节点对
 *    - 更新指针位置
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(1)
 */

#include <gtest/gtest.h>

using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *swapPairs(struct ListNode *head) {
    struct ListNode *cur = NULL, *next = NULL, *tmp = NULL, *pre = NULL;
    cur = head;
    if (cur != NULL && cur->next != NULL)
        head = cur->next;
    while (cur != NULL) {
        if (cur->next == NULL) {
            return head;
        }
        next = cur->next;
        if (pre != NULL)
            pre->next = next;
        tmp = next->next;
        next->next = cur;
        cur->next = tmp;
        pre = cur;
        cur = cur->next;
    }
    return head;
}

TEST(Daily, 24) {
    // 测试用例 1
    ListNode* head1 = new ListNode();
    head1->val = 1;
    head1->next = new ListNode();
    head1->next->val = 2;
    head1->next->next = new ListNode();
    head1->next->next->val = 3;
    head1->next->next->next = new ListNode();
    head1->next->next->next->val = 4;
    
    ListNode* result1 = swapPairs(head1);
    EXPECT_EQ(result1->val, 2);
    EXPECT_EQ(result1->next->val, 1);
    EXPECT_EQ(result1->next->next->val, 4);
    EXPECT_EQ(result1->next->next->next->val, 3);
    
    // 测试用例 2
    ListNode* head2 = NULL;
    ListNode* result2 = swapPairs(head2);
    EXPECT_EQ(result2, nullptr);
    
    // 测试用例 3
    ListNode* head3 = new ListNode();
    head3->val = 1;
    ListNode* result3 = swapPairs(head3);
    EXPECT_EQ(result3->val, 1);
}
