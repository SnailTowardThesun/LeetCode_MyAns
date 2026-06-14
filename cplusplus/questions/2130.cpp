//
// Created by hankun on 6/14/26.
//

/**
 * @file 2130.cpp
 * @brief LeetCode 2130. 链表最大孪生和（Maximum Twin Sum of a Linked List）
 *
 * @题目描述
 * 在一个大小为 n 且 n 为偶数的链表中，对于满足 0 <= i <= n/2 - 1 的 i，
 * 第 i 个节点（从 0 开始计数）的孪生节点是第 (n-1-i) 个节点。
 * 
 * 例如：链表有 4 个节点时，索引为 0 和 3 互为孪生，索引为 1 和 2 互为孪生。
 * 
 * 请你返回链表中所有节点的最大孪生和。
 *
 * @示例
 * 示例 1：
 * 输入：head = [5,4,2,1]
 * 输出：6
 * 解释：节点 0 和节点 3 互为孪生，和为 5+1=6；节点 1 和节点 2 互为孪生，和为 4+2=6。最大值为 6。
 *
 * 示例 2：
 * 输入：head = [4,2,2,3]
 * 输出：7
 * 解释：最大孪生和为 4+3=7。
 *
 * 示例 3：
 * 输入：head = [1,100000]
 * 输出：100001
 * 解释：只有两个节点互为孪生，和为 1+100000=100001。
 *
 * @解题思路
 * 方法一（当前实现）：双指针 + 链表反转
 *     - 使用快慢指针找到链表中点
 *     - 将后半段链表原地反转
 *     - 从前半段和反转后的后半段同步遍历，计算每对孪生节点的和
 *     - 取所有孪生和的最大值
 * 
 * 方法二（备选）：数组法（代码注释中的原始实现）
 *     - 将链表所有节点值存入 vector
 *     - 用双指针从两端向中间遍历，计算孪生和
 *     - 时间 O(n)，空间 O(n)
 * 
 * @复杂度分析
 * - 方法一：时间复杂度 O(n)，空间复杂度 O(1)（原地反转）
 * - 方法二：时间复杂度 O(n)，空间复杂度 O(n)（额外数组）
 */

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    int pairSum(ListNode *head) {
        // Step 1: Find the middle of the linked list using slow/fast pointers
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Reverse the second half of the linked list in-place
        ListNode* prev = NULL;
        ListNode* curr = slow;
        while (curr != NULL) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }

        // Step 3: Traverse from head and reversed second half simultaneously
        // to compute twin sums and find the maximum.
        int maxSum = 0;
        ListNode* left = head;
        ListNode* right = prev;
        while (right != NULL) {
            maxSum = max(maxSum, left->val + right->val);
            left = left->next;
            right = right->next;
        }

        return maxSum;
     }
};

TEST(Daily, 2130) {
    Solution s;

    // Test case 1: [5,4,2,1] => twin sums: 5+1=6, 4+2=6 => max=6
    ListNode* head1 = new ListNode(5);
    head1->next = new ListNode(4);
    head1->next->next = new ListNode(2);
    head1->next->next->next = new ListNode(1);
    EXPECT_EQ(s.pairSum(head1), 6);

    // Test case 2: [4,2,2,3] => twin sums: 4+3=7, 2+2=4 => max=7
    ListNode* head2 = new ListNode(4);
    head2->next = new ListNode(2);
    head2->next->next = new ListNode(2);
    head2->next->next->next = new ListNode(3);
    EXPECT_EQ(s.pairSum(head2), 7);

    // Test case 3: [1,100000] => twin sum: 1+100000=100001
    ListNode* head3 = new ListNode(1);
    head3->next = new ListNode(100000);
    EXPECT_EQ(s.pairSum(head3), 100001);

    // Cleanup
    delete head1->next->next->next;
    delete head1->next->next;
    delete head1->next;
    delete head1;

    delete head2->next->next->next;
    delete head2->next->next;
    delete head2->next;
    delete head2;

    delete head3->next;
    delete head3;
}
