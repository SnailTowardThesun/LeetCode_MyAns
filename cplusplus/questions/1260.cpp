// @题目描述:
// 给你一个 m 行 n 列的二维网格 grid 和一个整数 k。
// 每次将 grid 中的元素整体向右移动一格：每行元素右移一位，
// 行末元素移到下一行行首，最后一行行末元素移到第一行行首。
// 返回执行 k 次移位后的网格。
//
// @示例:
// 示例 1：
// 输入：grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
// 输出：[[9,1,2],[3,4,5],[6,7,8]]
//
// 示例 2：
// 输入：grid = [[1,2,3],[4,5,6],[7,8,9]], k = 9
// 输出：[[1,2,3],[4,5,6],[7,8,9]]
// 解释：m*n = 9，k = 9 时恰好移位一整圈，回到原状。
//
// @解题思路:
// 展平 + 旋转 + 还原。
// 1. 将 m×n 的网格按行序展平为一维数组 container。
// 2. 实际移位步数 step = k % (m*n)，超过一圈的部分等价于取余。
// 3. 将 container 尾部 step 个元素移到头部（右移 step 位），得到 helper。
//    即 helper = container[end-step, end) + container[begin, end-step)。
// 4. 将 helper 按 m 行 n 列重新装回二维网格返回。
//
// 复杂度分析：
// - 时间复杂度：O(m*n)，遍历所有元素各常数次。
// - 空间复杂度：O(m*n)，用于展平和旋转的辅助数组。

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> container;
        for (const auto& row : grid) {
            for (int v : row) {
                container.push_back(v);
            }
        }

        int step = k % (m * n);
        vector<int> helper;
        helper.insert(helper.end(), container.end() - step, container.end());
        helper.insert(helper.end(), container.begin(), container.end() - step);

        vector<vector<int>> result;
        for (int i = 0; i < m; i++) {
            vector<int> tmp;
            for (int j = 0; j < n; j++) {
                tmp.push_back(helper[i * n + j]);
            }
            result.push_back(tmp);
        }

        return result;
    }
};

TEST(Daily, 1260) {
    Solution s;

    // 基本用例
    auto grid1 = vector<vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto expected1 = vector<vector<int>>{{9, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    EXPECT_EQ(s.shiftGrid(grid1, 1), expected1);

    // k 恰为 m*n，移位一整圈回到原状
    auto grid2 = vector<vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto expected2 = vector<vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(s.shiftGrid(grid2, 9), expected2);

    // 边界用例：单元素，k 任意大都取余为 0
    auto grid3 = vector<vector<int>>{{1}};
    auto expected3 = vector<vector<int>>{{1}};
    EXPECT_EQ(s.shiftGrid(grid3, 100), expected3);

    // k = 0，不变
    auto grid4 = vector<vector<int>>{{3, 8, 1, 9}, {19, 7, 2, 5}, {4, 6, 11, 10}, {12, 0, 21, 13}};
    EXPECT_EQ(s.shiftGrid(grid4, 0), grid4);
}
