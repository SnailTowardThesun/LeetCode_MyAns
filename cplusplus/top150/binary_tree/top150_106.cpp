//
// Created by hankun on 2026/10/5.
//

/**
 * @file top150_106.cpp
 * @brief LeetCode 106. 从中序与后序遍历序列构造二叉树
 *
 * @题目描述
 * 给定两个整数数组 inorder 和 postorder，其中 inorder 是二叉树的中序遍历，
 * postorder 是同一棵树的后序遍历，请你构造并返回这颗二叉树。
 *
 * @示例
 * 示例 1：
 * 输入：inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
 * 输出：[3,9,20,null,null,15,7]
 *
 * 示例 2：
 * 输入：inorder = [-1], postorder = [-1]
 * 输出：[-1]
 *
 * @解题思路
 * 1. 递归分治：
 *    - 后序遍历的最后一个元素是根节点的值
 *    - 在中序遍历中找到根值的位置，其左侧是左子树的所有节点，
 *      右侧是右子树的所有节点
 *    - 后序切分与中序对齐：左子树段 postorder[i] 对应 inorder[i]
 *      （i < 左子树大小），右子树段在左段之后、根之前
 *    - 分别切分出左/右子树的中序与后序数组，递归构建并挂到根上
 *    - 数组为空时返回 nullptr，单元素时直接返回叶节点
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n^2)，每层递归都要线性查找根位置并复制数组
 *    - 空间复杂度: O(n^2)，递归栈 O(h) 加上每层切分数组的开销
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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        if (postorder.size() == 0) {
            return nullptr;
        }

        int root_val = postorder.back();
        TreeNode *root = new TreeNode(root_val);
        if (postorder.size() == 1) {
            return root;
        }

        vector<int> inorder_left_nodes;
        vector<int> postorder_left_nodes;
        for (auto i = 0; i < inorder.size(); i++) {
            if (inorder[i] == root_val) {
                break;
            }
            inorder_left_nodes.emplace_back(inorder[i]);
            postorder_left_nodes.emplace_back(postorder[i]);
        }

        vector<int> inorder_right_nodes;
        vector<int> postorder_right_nodes;
        for (auto i = inorder_left_nodes.size() + 1; i < inorder.size(); i++) {
            inorder_right_nodes.emplace_back(inorder[i]);
            postorder_right_nodes.emplace_back(postorder[i - 1]);
        }

        root->left = buildTree(inorder_left_nodes, postorder_left_nodes);
        root->right = buildTree(inorder_right_nodes, postorder_right_nodes);

        return root;
    }
};

TEST(top150, 106) {
    vector<int> inorder{9, 3, 15, 20, 7};
    vector<int> postorder{9, 15, 7, 20, 3};
    Solution s;
    auto ret = s.buildTree(inorder, postorder);
    EXPECT_EQ(ret->val, 3);
    EXPECT_EQ(ret->left->val, 9);
    EXPECT_EQ(ret->right->val, 20);
    EXPECT_EQ(ret->right->left->val, 15);
    EXPECT_EQ(ret->right->right->val, 7);
}

}  // namespace
