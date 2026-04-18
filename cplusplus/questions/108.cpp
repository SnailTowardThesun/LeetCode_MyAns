//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 108.cpp
 * @brief LeetCode 108. 将有序数组转换为二叉搜索树
 *
 * @题目描述
 * 给定一个按照升序排列的有序数组，将其转换为一棵高度平衡的二叉搜索树。
 * 高度平衡二叉树是指一个二叉树每个节点的左右两个子树的高度差的绝对值不超过 1。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [-10,-3,0,5,9]
 * 输出：[0,-3,9,-10,null,5]
 * 解释：一个可能的高度平衡二叉搜索树
 *
 * 示例 2：
 * 输入：nums = [1,3]
 * 输出：[3,1] 或 [1,3]
 * 解释：两个可能的高度平衡二叉搜索树
 *
 * @解题思路
 * 1. 高度平衡二叉搜索树的特性：
 *    - 左子树的所有节点值小于根节点值
 *    - 右子树的所有节点值大于根节点值
 *    - 左右子树的高度差不超过 1
 *
 * 2. 算法步骤：
 *    - 选择数组的中间元素作为根节点
 *    - 递归地对左半部分数组构建左子树
 *    - 递归地对右半部分数组构建右子树
 *    - 这样可以保证左右子树的节点数量差不超过 1，从而保证高度平衡
 *
 * 3. 实现细节：
 *    - 使用递归函数，传入当前处理的数组范围 [left, right]
 *    - 当 left > right 时，返回 nullptr
 *    - 计算中间位置 mid = (left + right) / 2
 *    - 创建根节点，值为 nums[mid]
 *    - 递归构建左子树（范围 [left, mid-1]）
 *    - 递归构建右子树（范围 [mid+1, right]）
 *
 * 4. 复杂度分析：
 *    - 时间复杂度: O(n)，每个节点只访问一次
 *    - 空间复杂度: O(log n)，递归调用栈的深度
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TEST(Daily, 108) {
    class Solution {
    public:
        TreeNode* sortedArrayToBST(vector<int> &num) {
            TreeNode* root = NULL;
            GetResult(num, 0, num.size()-1, root);
            return root;
        }
        void GetResult(vector<int> &num, int left, int right, TreeNode* &root) {
            if (left > right) return;
            int mid = (left + right + 1) / 2;
            root = new TreeNode(num[mid]);
            GetResult(num, left, mid-1, root->left);
            GetResult(num, mid+1, right, root->right);
        }
    };

    Solution s;
    
    // 测试用例 1
    vector<int> nums1 = {-10, -3, 0, 5, 9};
    TreeNode* root1 = s.sortedArrayToBST(nums1);
    EXPECT_EQ(root1->val, 0);
    EXPECT_EQ(root1->left->val, -3);
    EXPECT_EQ(root1->right->val, 9);
    EXPECT_EQ(root1->left->left->val, -10);
    EXPECT_EQ(root1->right->left->val, 5);
    
    // 测试用例 2
    vector<int> nums2 = {1, 3};
    TreeNode* root2 = s.sortedArrayToBST(nums2);
    EXPECT_TRUE(root2->val == 1 || root2->val == 3);
    
    // 测试用例 3
    vector<int> nums3 = {};
    TreeNode* root3 = s.sortedArrayToBST(nums3);
    EXPECT_EQ(root3, nullptr);
    
    // 测试用例 4
    vector<int> nums4 = {1};
    TreeNode* root4 = s.sortedArrayToBST(nums4);
    EXPECT_EQ(root4->val, 1);
    EXPECT_EQ(root4->left, nullptr);
    EXPECT_EQ(root4->right, nullptr);
}
