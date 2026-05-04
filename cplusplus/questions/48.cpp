//
// 48. 旋转图像
// https://leetcode.cn/problems/rotate-image/
//
// 给定一个 n × n 的二维矩阵 matrix，请你将矩阵顺时针旋转 90 度。
// 你必须在原地修改矩阵，即直接修改输入的二维矩阵。
//
// 示例 1：
// 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
// 输出：[[7,4,1],[8,5,2],[9,6,3]]
//
// 示例 2：
// 输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]
// 输出：[[13,9,5,1],[14,10,6,2],[15,11,7,3],[16,12,8,4]]
//
// 解题思路（两步骤法）：
// 1. 对角线翻转：以主对角线为轴，交换 matrix[i][j] 和 matrix[j][i]
// 2. 上下翻转：将每行反转，相当于水平镜像
//
// 时间复杂度：O(n²)，空间复杂度：O(1)
//

#include "gtest/gtest.h"
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }

        for (int i = 0; i < n; i++) {
            std::reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

TEST(Daily, 48) {
    Solution s;
    auto matrix = vector<vector<int>>{{1,2,3},{4,5,6},{7,8,9}};
    s.rotate(matrix);
}