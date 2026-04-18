//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 23.cpp
 * @brief LeetCode 23. 合并K个升序链表
 *
 * @题目描述
 * 给你一个链表数组，每个链表都是按升序排列的。
 * 请你合并所有链表，返回一个按升序排列的链表。
 *
 * @示例
 * 示例 1：
 * 输入：lists = [[1,4,5],[1,3,4],[2,6]]
 * 输出：[1,1,2,3,4,4,5,6]
 *
 * 示例 2：
 * 输入：lists = []
 * 输出：[]
 *
 * 示例 3：
 * 输入：lists = [[]]
 * 输出：[]
 *
 * @解题思路
 * 1. 最小堆法：
 *    - 使用最小堆来存储所有链表的头节点
 *    - 每次取出堆顶元素，将其添加到结果链表
 *    - 将取出的节点的下一个节点加入堆中
 *
 * 2. 算法步骤：
 *    - 将所有链表的头节点加入最小堆
 *    - 重复以下步骤直到堆为空：
 *      a. 取出堆顶节点
 *      b. 将节点添加到结果链表
 *      c. 如果该节点有下一个节点，将其加入堆中
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(N log k)，N 是所有节点总数，k 是链表数量
 *    - 空间复杂度: O(k)，堆的大小
 */

#include <gtest/gtest.h>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

TEST(Daily, 23) {
    class Solution {
    public:
        ListNode * mergeKLists(vector<ListNode*>& lists) {
            int count = lists.size();
            if (count == 0) {
                return nullptr;
            }

            ListNode node(0), *res = &node;
            auto cmp = [](const ListNode *a, const ListNode *b) { return a->val > b->val; };
            priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> que(cmp);

            for (int i = 0; i < count; i++) {
                if (lists[i]) {
                    que.push(lists[i]);
                }
            }

            while (!que.empty()) {
                ListNode * p = que.top();
                que.pop();
                res->next = p;
                res = p;

                if (p->next) {
                    que.push(p->next);
                }
            }
            return node.next;
        }
    };

    Solution s;
    
    // 测试用例 1
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);
    
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    
    ListNode* l3 = new ListNode(2);
    l3->next = new ListNode(6);
    
    vector<ListNode*> lists = {l1, l2, l3};
    ListNode* result = s.mergeKLists(lists);
    
    EXPECT_EQ(result->val, 1);
    EXPECT_EQ(result->next->val, 1);
    EXPECT_EQ(result->next->next->val, 2);
}
