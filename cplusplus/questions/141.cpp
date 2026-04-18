//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 141.cpp
 * @brief LeetCode 141. 环形链表
 *
 * @题目描述
 * 给你一个链表的头节点 head，判断链表中是否有环。
 * 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
 * 为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
 * 如果 pos 是 -1，则在该链表中没有环。
 *
 * @示例
 * 示例 1：
 * 输入：head = [3,2,0,-4], pos = 1
 * 输出：true
 * 解释：链表中有一个环，其尾部连接到索引 1 的节点
 *
 * 示例 2：
 * 输入：head = [1,2], pos = 0
 * 输出：true
 * 解释：链表中有一个环，其尾部连接到索引 0 的节点
 *
 * 示例 3：
 * 输入：head = [1], pos = -1
 * 输出：false
 * 解释：链表中没有环
 *
 * @解题思路
 * 1. 快慢指针法（Floyd 判圈算法）：
 *    - 使用两个指针，快指针每次走两步，慢指针每次走一步
 *    - 如果链表中存在环，快慢指针最终会相遇
 *
 * 2. 算法步骤：
 *    - 初始化快慢指针都指向头节点
 *    - 快指针每次移动两步，慢指针每次移动一步
 *    - 如果存在环，快慢指针会相遇
 *    - 如果快指针到达链表末尾，则不存在环
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)，其中 n 是链表的节点数
 *    - 空间复杂度: O(1)，只使用两个指针
 */

#include <gtest/gtest.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

TEST(Daily, 141) {
    class Solution {
    public:
        bool hasCycle(ListNode *head) {
            if (head == NULL || head->next == NULL) {
                return false;
            }
            ListNode* slow = head;
            ListNode* fast = head->next;

            while (slow != fast) {
                if (fast == NULL || fast->next == NULL) {
                    return false;
                }
                slow = slow->next;
                fast = fast->next->next;
            }
            return true;
        }
    };

    Solution s;
    
    // 测试用例 1
    ListNode* head1 = new ListNode(3);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(0);
    head1->next->next->next = new ListNode(-4);
    head1->next->next->next->next = head1->next;
    EXPECT_TRUE(s.hasCycle(head1));
    
    // 测试用例 2
    ListNode* head2 = new ListNode(1);
    head2->next = new ListNode(2);
    head2->next->next = head2;
    EXPECT_TRUE(s.hasCycle(head2));
    
    // 测试用例 3
    ListNode* head3 = new ListNode(1);
    EXPECT_FALSE(s.hasCycle(head3));
}
