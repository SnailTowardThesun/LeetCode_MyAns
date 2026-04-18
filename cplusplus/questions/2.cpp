//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 2.cpp
 * @brief LeetCode 2. 两数相加
 *
 * @题目描述
 * 给你两个非空的链表，表示两个非负的整数。
 * 它们每位数字都是按照逆序的方式存储的，并且每个节点只能存储一位数字。
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 *
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 *
 * @示例
 * 示例 1：
 * 输入：l1 = [2,4,3], l2 = [5,6,4]
 * 输出：[7,0,8]
 * 解释：342 + 465 = 807.
 *
 * 示例 2：
 * 输入：l1 = [0], l2 = [0]
 * 输出：[0]
 *
 * 示例 3：
 * 输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 * 输出：[8,9,9,9,0,0,0,1]
 *
 * @解题思路
 * 1. 模拟加法过程：
 *    - 遍历两个链表，逐位相加
 *    - 处理进位
 *    - 注意链表长度可能不同
 *    - 注意最后可能还有进位
 *
 * 2. 算法步骤：
 *    - 初始化一个哑节点作为结果链表的头节点
 *    - 初始化进位 carry 为 0
 *    - 遍历两个链表，直到两个链表都为空且进位为 0：
 *      a. 取出两个链表当前节点的值（如果节点为空则为 0）
 *      b. 计算当前位的和：sum = val1 + val2 + carry
 *      c. 更新进位：carry = sum / 10
 *      d. 创建新节点，值为 sum % 10，添加到结果链表
 *      e. 移动两个链表的指针
 *    - 返回哑节点的下一个节点
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(max(m, n))，其中 m 和 n 是两个链表的长度
 *    - 空间复杂度: O(max(m, n))，用于存储结果链表
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

TEST(Daily, 2) {
    class Solution {
    public:
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            if (l1 == NULL || l2 == NULL) return l1 == NULL ? l1 : l2;

            ListNode* result = new ListNode(0);
            ListNode* pResult = result;
            ListNode* p1 = l1;
            ListNode* p2 = l2;
            int isBiggerThenTen = 0;
            while (p1 != NULL && p2 != NULL) {
                int tmp = 0;
                tmp = p1->val + p2->val + isBiggerThenTen;
                ListNode* tmpNode = new ListNode((tmp) % 10);
                pResult->next = tmpNode;
                pResult = pResult->next;
                tmp >= 10 ? isBiggerThenTen = 1 : isBiggerThenTen = 0;
                p1 = p1->next;
                p2 = p2->next;
            }
            while (p1 != NULL || p2 != NULL || isBiggerThenTen != 0) {
                int tmp = 0;
                ListNode* tmpNode = NULL;
                if (p1 != NULL || p2 != NULL) {
                    if (p1 == NULL) {
                        tmp = p2->val + isBiggerThenTen;
                        tmpNode = new ListNode(tmp % 10);
                        tmp >= 10 ? isBiggerThenTen = 1 : isBiggerThenTen = 0;
                        p2 = p2->next;
                    } else {
                        tmp = p1->val + isBiggerThenTen;
                        tmpNode = new ListNode(tmp % 10);
                        tmp >= 10 ? isBiggerThenTen = 1 : isBiggerThenTen = 0;
                        p1 = p1->next;
                    }
                } else {
                    tmpNode = new ListNode(isBiggerThenTen);
                    isBiggerThenTen = 0;
                }
                pResult->next = tmpNode;
                pResult = pResult->next;
            }
            return result->next;
        }
    };

    Solution s;
    
    // 测试用例 1
    ListNode* l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);
    
    ListNode* l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);
    
    ListNode* result1 = s.addTwoNumbers(l1, l2);
    EXPECT_EQ(result1->val, 7);
    EXPECT_EQ(result1->next->val, 0);
    EXPECT_EQ(result1->next->next->val, 8);
    EXPECT_EQ(result1->next->next->next, nullptr);
    
    // 测试用例 2
    ListNode* l3 = new ListNode(0);
    ListNode* l4 = new ListNode(0);
    ListNode* result2 = s.addTwoNumbers(l3, l4);
    EXPECT_EQ(result2->val, 0);
    EXPECT_EQ(result2->next, nullptr);
    
    // 清理内存
    delete l1->next->next;
    delete l1->next;
    delete l1;
    delete l2->next->next;
    delete l2->next;
    delete l2;
    delete result1->next->next;
    delete result1->next;
    delete result1;
    delete l3;
    delete l4;
    delete result2;
}
