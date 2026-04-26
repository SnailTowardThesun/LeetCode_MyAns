//
// Created by hankun on 4/26/26.
//
// ============================================================================
// LeetCode 1559. Detect Cycles in 2D Grid
// 题目描述：
//   给你一个 m x n 的二维字符网格 grid，请你判断其中是否包含由相同字符值
//   组成的"环"。环的定义如下：
//   1. 环由相同字符值组成，路径长度至少为 4。
//   2. 沿着网格中的四个方向（左、右、上、下）移动形成。
//   3. 移动过程中不能往回走（即不能沿原边返回）。
//   4. 同一个格子可以在环中被访问多次，但边不能重复。
//
// 示例 1：
//   输入：grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
//   输出：true
//   解释：网格中存在环，沿着边缘的 'a' 形成一个环。
//
// 示例 2：
//   输入：grid = [["a","b","b"],["b","z","z"],["z","z","f"]]
//   输出：false
//   解释：没有由相同字符组成的环。
//
// 解题思路：
//   使用 DFS + visited 数组检测图中是否存在环。
//   1. 遍历网格中的每个格子，如果未访问过，则从该格子开始 DFS。
//   2. DFS 过程中，沿四个方向查找相同字符值的相邻格子。
//   3. 记录 DFS 路径中访问过的格子（vis_ 数组）。
//   4. 若当前格子相邻的已访问格子不是其父节点（即不是上一格子），说明存在环。
//   5. 如果所有连通分量都没有发现环，则返回 false。
//
// 复杂度分析：
//   时间复杂度：O(m * n)，每个格子最多被访问一次。
//   空间复杂度：O(m * n)，visited 数组和 DFS 递归栈。
// ============================================================================

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
    int m_, n_;                         // 网格的行数和列数
    vector<vector<bool>> vis_;           // 记录每个格子是否已被访问
    // 四个方向：左、右、上、下
    const int DIRS[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    /**
     * @brief DFS 检测是否存在环
     * @param x  当前行坐标
     * @param y  当前列坐标
     * @param px 父节点行坐标（避免往回走）
     * @param py 父节点列坐标
     * @param c  当前格子字符值
     * @param grid 输入网格
     * @return 如果找到环返回 true，否则返回 false
     */
    bool dfs(int x, int y, int px, int py, char c, const vector<vector<char>>& grid) {
        vis_[x][y] = true;
        for (auto& d : DIRS) {
            int i = x + d[0], j = y + d[1];
            // 检查边界和字符值
            if (i >= 0 && i < m_ && j >= 0 && j < n_ && grid[i][j] == c) {
                if (vis_[i][j]) {
                    return true; // 找到环
                }
                // (i, j) 不是父节点才继续递归
                if ((i != px || j != py) && dfs(i, j, x, y, c, grid)) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    /**
     * @brief 检查网格中是否存在由相同字符组成的环
     * @param grid 输入的二维字符网格
     * @return 如果存在环返回 true，否则返回 false
     */
    bool containsCycle(vector<vector<char>>& grid) {
        m_ = grid.size(), n_ = grid[0].size();
        vis_.assign(m_, vector<bool>(n_, false));

        for (int i = 0; i < m_; i++) {
            for (int j = 0; j < n_; j++) {
                if (!vis_[i][j]) {
                    if (dfs(i, j, -1, -1, grid[i][j], grid)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

TEST(Daily, 1559) {
    Solution s;
    auto grid = vector<vector<char>>{{'a','a','a','a'},{'a','b','b','a'},{'a','b','b','a'},{'a','a','a','a'}};
    auto ret = s.containsCycle(grid);
    EXPECT_TRUE(ret);
}
