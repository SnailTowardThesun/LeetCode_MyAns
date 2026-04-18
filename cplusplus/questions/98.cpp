//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 98.cpp
 * @brief LeetCode 98. 验证二叉搜索树
 *
 * @题目描述
 * 给你一个二叉树的根节点 root，判断其是否是一个有效的二叉搜索树。
 *
 * 二叉搜索树的定义：
 * - 节点的左子树只包含小于当前节点的数
 * - 节点的右子树只包含大于当前节点的数
 * - 所有子树本身也必须是二叉搜索树
 *
 * @示例
 * 示例 1：
 * 输入：root = [2,1,3]
 * 输出：true
 *
 * 示例 2：
 * 输入：root = [5,1,4,null,null,3,6]
 * 输出：false
 * 解释：根节点的值是 5，但是右子树中节点的值是 4
 *
 * @解题思路
 * 1. 中序遍历法：
 *    - 二叉搜索树的中序遍历应该是一个升序序列
 *    - 在中序遍历过程中检查序列是否升序
 *
 * 2. 算法步骤：
 *    - 中序遍历二叉树
 *    - 记录上一个访问的节点值
 *    - 如果当前节点值小于等于上一个节点值，返回 false
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(h)，h 为树的高度
 */

#include <gtest/gtest.h>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        long prev = LLONG_MIN;
        return isValidBSTHelper(root, prev);
    }

private:
    bool isValidBSTHelper(TreeNode* root, long& prev) {
        if (root == NULL) return true;

        if (!isValidBSTHelper(root->left, prev)) return false;

        if (root->val <= prev) return false;
        prev = root->val;

        if (!isValidBSTHelper(root->right, prev)) return false;

        return true;
    }
};

TEST(Daily, 98) {
    Solution s;

    // 测试用例 1
    TreeNode* root1 = new TreeNode(2);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(3);
    EXPECT_TRUE(s.isValidBST(root1));

    // 测试用例 2
    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(4);
    root2->right->left = new TreeNode(3);
    root2->right->right = new TreeNode(6);
    EXPECT_FALSE(s.isValidBST(root2));

    // 测试用例 3
    TreeNode* root3 = new TreeNode(1);
    EXPECT_TRUE(s.isValidBST(root3));

    // 测试用例 4
    TreeNode* root4 = NULL;
    EXPECT_TRUE(s.isValidBST(root4));
}
