//
// Created by hankun on 2026/10/5.
//

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
