//
// Created by hankun on 6/7/26.
//

/**
 * @file 2196.cpp
 * @brief LeetCode 2196. Create Binary Tree From Descriptions（根据描述创建二叉树）
 *
 * @题目描述
 * 给你一个二维整数数组 descriptions，其中 descriptions[i] = [parenti, childi, isLefti]，
 * 表示 parenti 是 childi 在二叉树中的父节点，二叉树中各节点的值互不相同。
 *
 * 请你根据 descriptions 的描述构造这棵二叉树，并返回二叉树的根节点。
 *
 * @示例
 * 示例 1：
 * 输入：descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
 * 输出：[50,20,80,15,17,19]
 * 解释：
 * 根节点是值为 50 的节点，因为它没有父节点。
 * 创建的二叉树如图所示。
 *
 * 示例 2：
 * 输入：descriptions = [[1,2,1],[2,3,0],[3,4,1]]
 * 输出：[1,2,null,null,3,4]
 *
 * @解题思路
 * 1. 哈希表法：
 *    - 使用哈希表存储节点值对应的节点对象
 *    - 使用另一个哈希表记录每个节点的父节点信息
 *    - 遍历描述数组，创建所有节点并建立父子关系
 *    - 找到没有父节点的节点作为根节点
 *
 * 2. 算法步骤：
 *    - 初始化两个哈希表：nodes 存储节点值到节点对象的映射，
 *      container 存储节点值到父节点和左右子节点信息的映射
 *    - 遍历 descriptions 数组，为每个节点创建 TreeNode 对象
 *    - 根据 isLeft 标记将子节点连接到父节点的左或右子节点
 *    - 记录每个子节点的父节点
 *    - 遍历 container 找到父节点为 0 的节点，即为根节点
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)，需要遍历 descriptions 两次（一次构建树，一次找根节点）
 *    - 空间复杂度: O(n)，需要哈希表存储所有节点
 */

#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>
using namespace std;

// Definition for a binary tree node.
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
    TreeNode *createBinaryTree(vector<vector<int> > &descriptions) {
        // key=val, value[0] = parent, value[1] = left, value[2]=right, default is 0
        unordered_map<int, vector<int>> container;
        unordered_map<int, TreeNode*> nodes;
        for (auto i: descriptions) {
            int p = i[0];
            int c = i[1];
            int isLeft = i[2];

            if (container.find(p) == container.end()) {
                container[p] = vector<int>{0, 0, 0};
                nodes[p] = new TreeNode(p);
            }

            if (container.find(c) == container.end()) {
                container[c] = vector<int>{0, 0, 0};
                nodes[c] = new TreeNode(c);
            }

            if (isLeft) {
                container[p][1] = c;
                nodes[p]->left = nodes[c];
            } else {
                container[p][2] = c;
                nodes[p]->right = nodes[c];
            }

            container[c] = vector<int>{p, 0, 0};
        }

        int root = 0;

        for (auto i: container) {
            if (i.second[0] == 0) {
                root = i.first;
                break;
            }
        }


        return nodes[root];
    }
};

TEST(Daily, 2196) {
    Solution s;
    vector<vector<int> > descriptions = {{20, 15, 1}, {20, 17, 0}, {50, 20, 1}, {50, 80, 0}, {80, 19, 1}};
    auto ret = s.createBinaryTree(descriptions);
    EXPECT_EQ(ret->val, 50);
}
