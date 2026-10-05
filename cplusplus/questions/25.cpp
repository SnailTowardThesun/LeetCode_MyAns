//
// Created by 韩堃 on 2026/10/3.
//
/**
 * Definition for singly-linked list.
 */

#include <gtest/gtest.h>

#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        vector<ListNode*> nodes;
        ListNode* cur = head;
        while (cur) {
            nodes.emplace_back(cur);
            cur = cur->next;
        }

        int n = nodes.size();
        if (n == 0) {
            return nullptr;
        }
        // 只翻转完整的组，末尾不足 k 的部分保持原顺序（越界 reverse 会读到野指针）
        for (int i = 0; i + k <= n; i += k) {
            reverse(nodes.begin() + i, nodes.begin() + i + k);
        }

        for (int i = 0; i + 1 < n; i++) {
            nodes[i]->next = nodes[i + 1];
        }
        nodes[n - 1]->next = nullptr;

        return nodes[0];
    }
};

// 根据值数组构造链表，返回头指针
static ListNode* make_list(const vector<int>& vals) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int v : vals) {
        auto* node = new ListNode(v);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

TEST(Daily, 25) {
    Solution s;

    // k=3，长度 5：前 3 个翻转，末尾 2 个保持原样 -> 3->2->1->4->5
    auto ret = s.reverseKGroup(make_list({1, 2, 3, 4, 5}), 3);
    for (int v : {3, 2, 1, 4, 5}) {
        ASSERT_NE(ret, nullptr);
        EXPECT_EQ(ret->val, v);
        ret = ret->next;
    }
    EXPECT_EQ(ret, nullptr);

    // k=1：等价于不翻转
    ret = s.reverseKGroup(make_list({1, 2, 3}), 1);
    for (int v : {1, 2, 3}) {
        ASSERT_NE(ret, nullptr);
        EXPECT_EQ(ret->val, v);
        ret = ret->next;
    }
    EXPECT_EQ(ret, nullptr);

    // 长度恰为 k 的倍数：全部翻转
    ret = s.reverseKGroup(make_list({1, 2, 3, 4}), 2);
    for (int v : {2, 1, 4, 3}) {
        ASSERT_NE(ret, nullptr);
        EXPECT_EQ(ret->val, v);
        ret = ret->next;
    }
    EXPECT_EQ(ret, nullptr);

    // 边界：空链表
    EXPECT_EQ(s.reverseKGroup(nullptr, 3), nullptr);
}