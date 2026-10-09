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
