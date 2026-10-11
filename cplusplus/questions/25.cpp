//
// Created by 韩堃 on 2026/10/3.
//

/**
 * @file 25.cpp
 * @brief LeetCode 25. K 个一组翻转链表
 *
 * @题目描述
 * 给你链表的头节点 head，每 k 个节点一组进行翻转，请你返回修改后的链表。
 * k 是一个正整数，它的值小于或等于链表的长度。
 * 如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
 * 进阶：你可以设计一个只用 O(1) 额外内存空间的算法解决此问题吗？
 *
 * @示例
 * 示例 1：
 * 输入：head = [1,2,3,4,5], k = 2
 * 输出：[2,1,4,3,5]
 *
 * 示例 2：
 * 输入：head = [1,2,3,4,5], k = 3
 * 输出：[3,2,1,4,5]
 *
 * @解题思路
 * 1. 数组化 + 分组反转：
 *    - 第一次遍历把所有节点指针收集到数组 nodes 中
 *    - 从下标 0 开始，每隔 k 个一组调用 reverse 反转指针数组
 *      （只翻转完整组：i + k <= n，末尾不足 k 的部分保持原序）
 *    - 重新串联：nodes[i]->next = nodes[i+1]，末节点置空
 *    - 返回 nodes[0] 作为新头节点
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n)，收集、反转、重连各一遍
 *    - 空间复杂度: O(n)，用于存储节点指针数组
 */

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

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
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
}  // namespace

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
