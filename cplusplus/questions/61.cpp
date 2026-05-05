//
// Created by hankun on 5/5/26.
//

/**
 * @file 61.cpp
 * @brief LeetCode 61. Rotate List（旋转链表）
 *
 * @题目描述
 * 给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
 *
 * @示例
 * 示例 1：
 * 输入：head = [1,2,3,4,5], k = 2
 * 输出：[4,5,1,2,3]
 * 解释：
 * 向右旋转 1 步：[5,1,2,3,4]
 * 向右旋转 2 步：[4,5,1,2,3]
 *
 * 示例 2：
 * 输入：head = [0,1,2], k = 4
 * 输出：[2,0,1]
 * 解释：
 * 向右旋转 1 步：[2,0,1]
 * 向右旋转 2 步：[1,2,0]
 * 向右旋转 3 步：[0,1,2]
 * 向右旋转 4 步：[2,0,1]
 *
 * @解题思路
 * 1. 数组辅助法：
 *    - 将链表节点的值存储到数组中
 *    - 计算实际需要旋转的步数：k % 数组长度（避免重复旋转）
 *    - 将数组从位置 (数组长度 - 实际步数) 处分割，然后重新拼接
 *    - 根据新的数组创建新的链表
 *
 * 2. 算法步骤：
 *    - 遍历链表，将所有节点值存储到 vector 中
 *    - 如果链表为空，直接返回
 *    - 计算实际旋转步数：steps = 数组长度 - k % 数组长度
 *    - 将数组从 steps 位置分割，后半部分在前，前半部分在后
 *    - 根据新数组创建新的链表
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)，需要遍历链表两次（一次收集值，一次创建新链表）
 *    - 空间复杂度: O(n)，需要额外的数组存储节点值
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
    ListNode *rotateRight(ListNode *head, int k) {
        if (head == nullptr) {
            return head;
        }
        vector<int> container;
        for (auto it = head; it != nullptr; it = it->next) {
            container.push_back(it->val);
        }

        auto steps = container.size() - k % container.size();

        vector<int> ret_container;
        ret_container.reserve(container.size());
        ret_container.insert(ret_container.begin(), container.begin() + steps, container.end());
        ret_container.insert(ret_container.end(), container.begin(), container.begin() + steps);

        ListNode *ret = new ListNode();
        ListNode *pos = ret;
        for (auto i: ret_container) {
            pos->next = new ListNode(i);
            pos = pos->next;
        }

        return ret->next;
    }
};

TEST(Daily, 61) {
    // head = [1,2,3,4,5], k = 2
    ListNode head = ListNode(1);
    head.next = new ListNode(2);
    head.next->next = new ListNode(3);
    head.next->next->next = new ListNode(4);
    head.next->next->next->next = new ListNode(5);

    Solution s;
    auto ret = s.rotateRight(&head, 2);
    EXPECT_EQ(4, ret->val);
}
