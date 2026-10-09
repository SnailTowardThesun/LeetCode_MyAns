//
// Created by hankun on 2026/10/5.
//

/**
 * @file top150_105.cpp
 * @brief LeetCode 105. 从前序与中序遍历序列构造二叉树
 *
 * @题目描述
 * 给定两个整数数组 preorder 和 inorder，其中 preorder 是二叉树的先序遍历，
 * inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。
 *
 * @示例
 * 示例 1：
 * 输入：preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
 * 输出：[3,9,20,null,null,15,7]
 *
 * 示例 2：
 * 输入：preorder = [-1], inorder = [-1]
 * 输出：[-1]
 *
 * @解题思路
 * 1. 递归分治：
 *    - 前序遍历的第一个元素是根节点的值
 *    - 在中序遍历中定位根值：根左侧是左子树节点（数量记为 left_size），
 *      右侧是右子树节点
 *    - 前序遍历中跳过根后，紧接的 left_size 个元素是左子树的前序，
 *      其后是右子树的前序
 *    - 中序遍历中根左侧为左子树中序，右侧为右子树中序
 *    - 分别切分数组递归构建左右子树并挂到根上
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n^2)，每层递归线性查找根位置并复制数组
 *    - 空间复杂度: O(n^2)，递归栈 O(h) 加上切分数组开销
 */

#include <gtest/gtest.h>

using namespace std;

namespace {

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
    }
};

class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        if (preorder.empty()) {
            return nullptr;
        }

        TreeNode *root = new TreeNode(preorder[0]);
        if (preorder.size() == 1) {
            return root;
        }

        // get left points
        int inorder_left_end = 0;
        for (int i = 0; i < inorder.size(); i++) {
            if (inorder[i] == preorder[0]) {
                inorder_left_end = i - 1;
                break;
            }
        }
        vector<int> inorder_left_nodes;
        for (int i = 0; i <= inorder_left_end; i++) {
            inorder_left_nodes.emplace_back(inorder[i]);
        }

        vector<int> preorder_left_nodes;
        for (auto i = 1; i < 1+inorder_left_nodes.size(); i++) {
            preorder_left_nodes.emplace_back(preorder[i]);
        }

        // get right points
        int inorder_right_start = inorder_left_end + 2;
        vector<int> inorder_right_nodes;
        for (int i = inorder_right_start; i < inorder.size(); i++) {
            inorder_right_nodes.emplace_back(inorder[i]);
        }

        vector<int> preorder_right_nodes;
        for (int i = 1 + preorder_left_nodes.size(); i < preorder.size(); i++) {
            preorder_right_nodes.emplace_back(preorder[i]);
        }

        root->left = buildTree(preorder_left_nodes, inorder_left_nodes);
        root->right = buildTree(preorder_right_nodes, inorder_right_nodes);

        return root;
    }
};

TEST(Top150, 105) {
    Solution s;

    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    vector<int> preorder{3, 9, 20, 15, 7};
    vector<int> inorder{9, 3, 15, 20, 7};
    auto ret = s.buildTree(preorder, inorder);
    EXPECT_EQ(ret->val, 3);
    EXPECT_EQ(ret->left->val, 9);
    EXPECT_EQ(ret->right->val, 20);
    EXPECT_EQ(ret->right->left->val, 15);
    EXPECT_EQ(ret->right->right->val, 7);
}

}  // namespace
