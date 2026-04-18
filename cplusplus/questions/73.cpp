//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 73.cpp
 * @brief LeetCode 73. 矩阵置零
 *
 * @题目描述
 * 给定一个 m x n 的矩阵，如果一个元素为 0，则将整个矩阵该行和该列的所有元素都设置为 0。
 * 请使用原地算法。
 *
 * @示例
 * 示例 1：
 * 输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
 * 输出：[[1,0,1],[0,0,0],[1,0,1]]
 *
 * 示例 2：
 * 输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
 * 输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 *
 * @解题思路
 * 1. 原地标记法：
 *    - 使用矩阵的第一行和第一列来标记哪些行和列需要置零
 *    - 记录第一行和第一列是否需要置零
 *
 * 2. 算法步骤：
 *    - 遍历矩阵，如果遇到 0，则将该元素所在的行和列的第一个元素标记为 0
 *    - 再次遍历矩阵，根据标记将对应的元素置零
 *    - 最后根据记录处理第一行和第一列
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(mn)
 *    - 空间复杂度: O(1)
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(Daily, 73) {
    class Solution {
    public:
        void setZeroes(vector<vector<int>> &matrix) {
            if (matrix.empty()) return;
            int m = matrix.size();
            int n = matrix[0].size();
            bool row = false, col = false;
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; j++)
                    if (matrix[i][j] == 0) {
                        if (i == 0) row = true;
                        if (j == 0) col = true;
                        matrix[i][0] = 0;
                        matrix[0][j] = 0;
                    }
            for (int i = 1; i < m; ++i)
                for (int j = 1; j < n; j++)
                    if (matrix[i][0] == 0 || matrix[0][j] == 0)
                        matrix[i][j] = 0;
            if (row) for (int j = 0; j < n; ++j) matrix[0][j] = 0;
            if (col) for (int i = 0; i < m; ++i) matrix[i][0] = 0;
        }
    };

    Solution s;
    
    // 测试用例 1
    vector<vector<int>> matrix1 = {{1,1,1},{1,0,1},{1,1,1}};
    s.setZeroes(matrix1);
    EXPECT_EQ(matrix1[0], vector<int>({1,0,1}));
    EXPECT_EQ(matrix1[1], vector<int>({0,0,0}));
    EXPECT_EQ(matrix1[2], vector<int>({1,0,1}));
    
    // 测试用例 2
    vector<vector<int>> matrix2 = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    s.setZeroes(matrix2);
    EXPECT_EQ(matrix2[0], vector<int>({0,0,0,0}));
    EXPECT_EQ(matrix2[1], vector<int>({0,4,5,0}));
}
