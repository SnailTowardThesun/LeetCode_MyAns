//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 100.cpp
 * @brief LeetCode 100. 相同的树
 *
 * @题目描述
 * 给你两棵二叉树 p 和 q，编写一个函数来检验这两棵树是否相同。
 * 两棵树如果结构相同且对应的节点值相同，则认为它们相同。
 *
 * @示例
 * 示例 1：
 * 输入：p = [1,2,3], q = [1,2,3]
 * 输出：true
 *
 * 示例 2：
 * 输入：p = [1,2], q = [1,null,2]
 * 输出：false
 *
 * 示例 3：
 * 输入：p = [1,2,1], q = [1,1,2]
 * 输出：false
 *
 * @解题思路
 * 1. 递归法：
 *    - 如果两个节点都为空，返回 true
 *    - 如果其中一个节点为空，返回 false
 *    - 如果两个节点都不为空，比较节点值
 *    - 递归比较左子树和右子树
 *
 * 2. 算法步骤：
 *    - 检查两个根节点是否为空
 *    - 比较两个根节点的值
 *    - 递归检查左子树
 *    - 递归检查右子树
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(h)，h 为树的高度
 */

#include <gtest/gtest.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TEST(Daily, 100) {
    class Solution {
    public:
        bool isSameTree(TreeNode* p, TreeNode* q) {
            if (p == NULL || q == NULL)
                return p == q ? true : false;
            return p->val == q->val
                ? isSameTree(p->left, q->left) && isSameTree(p->right, q->right)
                : false;
        }
    };

    Solution s;
    
    // 测试用例 1
    TreeNode* p1 = new TreeNode(1);
    p1->left = new TreeNode(2);
    p1->right = new TreeNode(3);
    TreeNode* q1 = new TreeNode(1);
    q1->left = new TreeNode(2);
    q1->right = new TreeNode(3);
    EXPECT_TRUE(s.isSameTree(p1, q1));
    
    // 测试用例 2
    TreeNode* p2 = new TreeNode(1);
    p2->left = new TreeNode(2);
    TreeNode* q2 = new TreeNode(1);
    q2->right = new TreeNode(2);
    EXPECT_FALSE(s.isSameTree(p2, q2));
    
    // 测试用例 3
    TreeNode* p3 = new TreeNode(1);
    TreeNode* q3 = new TreeNode(2);
    EXPECT_FALSE(s.isSameTree(p3, q3));
}
