// @题目描述:
// LeetCode 2265. 统计值等于子树平均值的节点数（Count Nodes Equal to Average of Subtree）
// 给你一棵二叉树的根节点 root，找出并返回满足要求的节点数：要求节点的值等于其
// 子树中所有节点值的平均值（平均值向下取整）。
// 注意：
// - n 个元素的平均值 = 这 n 个元素之和 / n，并向下取整。
// - root 的子树由 root 本身及其所有后代节点组成。
//
// @示例:
// 示例 1：
// 输入：root = [4,8,5,0,1,null,6]
// 输出：5
// 解释：
// - 值为 4 的节点：子树平均值 (4+8+5+0+1+6)/6 = 24/6 = 4，与节点值相等。
// - 值为 8 的节点：子树平均值 (8+0+1)/3 = 9/3 = 3，不相等。
// - 值为 5 的节点：子树平均值 (5+6)/2 = 11/2 = 5（向下取整），相等。
// - 值为 0 的节点：子树平均值 0/1 = 0，相等。
// - 值为 1 的节点：子树平均值 1/1 = 1，相等。
// - 值为 6 的节点：子树平均值 6/1 = 6，相等。
// 共 5 个节点满足要求。
// 示例 2：
// 输入：root = [1]
// 输出：1
// 解释：叶子节点的子树只含自身，平均值一定等于自身值。
//
// @解题思路:
// 遍历每个节点，对以该节点为根的子树统计「节点值之和」与「节点数」，
// 若 sum / count（整数除法，天然向下取整）等于该节点值，则答案加一。
// 1. helper：先序遍历整棵树的每个节点，逐个判定。
// 2. dfs：对一棵子树做深度优先遍历，通过引用参数累加节点值之和 sum 与
//    节点数 count（空节点直接返回，不产生贡献）。
//
// 复杂度分析：
// - 时间复杂度：O(n^2)，共 n 个节点，每个节点都要重新遍历其子树；
//   退化成链时总代价为 n+(n-1)+...+1。可改为一次后序遍历，
//   返回 {子树和, 节点数}，优化到 O(n)。
// - 空间复杂度：O(n)，最坏情况（单链）为递归栈深度。

#include <gtest/gtest.h>

#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
   public:

    // 后序遍历一棵子树，累加其全部节点的值之和 sum 与节点数 count
    void dfs(TreeNode* node, int& sum, int& count) {
        if (node == nullptr) {
            return;
        }
        sum += node->val;
        count++;
        dfs(node->left, sum, count);
        dfs(node->right, sum, count);
    }

    // 遍历每个节点，判定其值是否等于自身子树的平均值，满足则 ans 加一
    void helper(TreeNode* root, int& ans) {
        if (root == nullptr) {
            return;
        }

        // 统计以 root 为根的子树的节点值之和与节点数
        int sum = 0;
        int count = 0;
        dfs(root, sum, count);
        // 整数除法自动向下取整，与题目对平均值的定义一致
        if (count > 0 && sum / count == root->val) {
            ans++;
        }
        helper(root->left, ans);
        helper(root->right, ans);
    }

    int averageOfSubtree(TreeNode* root) {
        int ans = 0;
        helper(root, ans);
        return ans;
    }
};

TEST(Daily, 2265) {
    Solution s;
    // create [4,8,5,0,1,null,6]
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(8);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(1);
    root->right->right = new TreeNode(6);
    EXPECT_EQ(s.averageOfSubtree(root), 5);
}