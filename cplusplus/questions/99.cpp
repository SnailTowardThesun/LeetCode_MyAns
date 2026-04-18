//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 99.cpp
 * @brief LeetCode 99. 恢复二叉搜索树
 *
 * @题目描述
 * 给你二叉搜索树的根节点 root，该树中的两个节点被错误地交换。
 * 请在不改变其结构的情况下，恢复这棵树。
 *
 * @示例
 * 示例 1：
 * 输入：root = [1,3,null,null,2]
 * 输出：[3,1,null,null,2]
 *
 * 示例 2：
 * 输入：root = [3,1,null,null,2]
 * 输出：[2,1,3]
 *
 * @解题思路
 * 1. 中序遍历法：
 *    - 二叉搜索树的中序遍历是有序的
 *    - 找到中序遍历中顺序不对的两个节点
 *    - 交换这两个节点的值
 *
 * 2. 算法步骤：
 *    - 中序遍历二叉树
 *    - 找到第一对顺序不对的节点（prev.val > root.val）
 *    - 找到第二对顺序不对的节点
 *    - 交换这两个节点的值
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(h)，h 为树的高度
 */

#include <gtest/gtest.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TEST(Daily, 99) {
    class Solution {
    public:
        void findTwoNodes(TreeNode *root, TreeNode *&n1, TreeNode *&n2, TreeNode *&prev) {
            if (root == NULL) return;

            findTwoNodes(root->left, n1, n2, prev);
            if (prev != NULL && prev->val > root->val) {
                n2 = root;
                if (n1 == NULL) {
                    n1 = prev;
                }
            }
            prev = root;
            findTwoNodes(root->right, n1, n2, prev);
        }
        void recoverTree(TreeNode* root) {
            TreeNode *n1 = NULL;
            TreeNode *n2 = NULL;
            TreeNode *prev = NULL;
            findTwoNodes(root, n1, n2, prev);

            if (n1 != NULL && n2 != NULL) {
                int tmp = n2->val;
                n2->val = n1->val;
                n1->val = tmp;
            }
        }
    };

    Solution s;
    
    // 测试用例 1
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(3);
    root1->left->right = new TreeNode(2);
    s.recoverTree(root1);
    EXPECT_EQ(root1->val, 3);
    EXPECT_EQ(root1->left->val, 1);
    
    // 测试用例 2
    TreeNode* root2 = new TreeNode(3);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(2);
    s.recoverTree(root2);
    EXPECT_EQ(root2->val, 2);
    EXPECT_EQ(root2->right->val, 3);
}
