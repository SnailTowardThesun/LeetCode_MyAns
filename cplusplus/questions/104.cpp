//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 104.cpp
 * @brief LeetCode 104. 二叉树的最大深度
 *
 * @题目描述
 * 给定一个二叉树，找出其最大深度。
 * 二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
 *
 * @示例
 * 示例 1：
 * 输入：[3, 9, 20, null, null, 15, 7]
 * 输出：3
 *
 * 示例 2：
 * 输入：[1, null, 2]
 * 输出：2
 *
 * @解题思路
 * 1. 递归法：
 *    - 最大深度 = max(左子树深度, 右子树深度) + 1
 *
 * 2. 算法步骤：
 *    - 如果根节点为空，返回 0
 *    - 递归计算左子树深度
 *    - 递归计算右子树深度
 *    - 返回 max(左深度, 右深度) + 1
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(h)，h 为树的高度
 */

#include <gtest/gtest.h>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TEST(Daily, 104) {
    class Solution {
    public:
        int maxDepth(TreeNode* root) {
            if (root == NULL) return 0;
            return max(maxDepth(root->left), maxDepth(root->right)) + 1;
        }
    };

    Solution s;
    
    // 测试用例 1
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);
    EXPECT_EQ(s.maxDepth(root1), 3);
    
    // 测试用例 2
    TreeNode* root2 = new TreeNode(1);
    root2->right = new TreeNode(2);
    EXPECT_EQ(s.maxDepth(root2), 2);
    
    // 测试用例 3
    EXPECT_EQ(s.maxDepth(NULL), 0);
    
    // 测试用例 4
    TreeNode* root4 = new TreeNode(1);
    EXPECT_EQ(s.maxDepth(root4), 1);
}
