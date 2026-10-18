//
// Created by hankun on 2026/10/18.
//

// LeetCode 74. 搜索二维矩阵
//
// @题目描述:
// 给定一个 m x n 矩阵，每行从左到右升序，且每行第一个数大于前一行最后一个数。
// 判断 target 是否存在于矩阵中。
//
// @示例:
// 输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
// 输出：true
//
// @解题思路:
// 先二分行，再二分当前行：
// 1. 若 target 小于当前行首或大于当前行尾，可立即排除该行；
// 2. 若 target 位于当前行首尾之间，则目标行找到；
// 3. 在目标行内做标准二分查找。
//
// 复杂度分析：
// - 时间复杂度：O(log m + log n)。
// - 空间复杂度：O(1)。

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace {
class Solution {
   public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }

        int top = 0;
        int bottom = static_cast<int>(matrix.size()) - 1;
        int targetRow = -1;

        // 第一轮二分：利用每行首尾元素定位唯一可能包含 target 的行。
        while (top <= bottom) {
            int mid = top + (bottom - top) / 2;
            if (target < matrix[mid].front()) {
                bottom = mid - 1;
            } else if (target > matrix[mid].back()) {
                top = mid + 1;
            } else {
                targetRow = mid;
                break;
            }
        }

        if (targetRow == -1) {
            return false;
        }

        // 第二轮二分：在有序行内查找 target。
        int left = 0;
        int right = static_cast<int>(matrix[targetRow].size()) - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (matrix[targetRow][mid] == target) {
                return true;
            }

            if (matrix[targetRow][mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return false;
    }
};
}  // namespace

TEST(Daily, 74) {
    Solution s;
    vector<vector<int>> matrix{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    EXPECT_TRUE(s.searchMatrix(matrix, 3));
    EXPECT_TRUE(s.searchMatrix(matrix, 1));
    EXPECT_TRUE(s.searchMatrix(matrix, 60));
    EXPECT_FALSE(s.searchMatrix(matrix, 13));
    EXPECT_FALSE(s.searchMatrix(matrix, 0));
    EXPECT_FALSE(s.searchMatrix(matrix, 61));

    vector<vector<int>> oneRow{{1, 3}};
    EXPECT_TRUE(s.searchMatrix(oneRow, 3));
    EXPECT_FALSE(s.searchMatrix(oneRow, 2));
}
