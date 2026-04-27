//
// Created by hankun on 4/27/26.
//

/**
 * @file 1391.cpp
 * @brief LeetCode 1391. 网格中是否存在路径
 *
 * @题目描述
 * 给你一个 m x n 的网格 grid，网格中的每个单元格表示一条街道类型（用整数 1~6 表示）：
 * - 1 表示连接左侧和右侧细胞的街道
 * - 2 表示连接上方和下方细胞的街道
 * - 3 表示连接左侧和下方细胞的街道
 * - 4 表示连接右侧和下方细胞的街道
 * - 5 表示连接左侧和上方细胞的街道
 * - 6 表示连接右侧和上方细胞的街道
 *
 * 网格中某个街道只属于一个单元格。换言之，一个单元格中最多只有一条街道。
 * 如果网格中存在一条从左上角单元格 (0, 0) 到右下角单元格 (m-1, n-1) 的有效路径，
 * 则返回 true，否则返回 false。
 *
 * 有效路径需满足：单元格之间的街道可以互相连接，即如果从当前单元格可以移动到下一个单元格，
 * 那么下一个街道也必须能回到当前单元格。
 *
 * @示例
 * 示例 1：
 * 输入：grid = [[2,4,3],[2,1,3]]
 * 输出：true
 * 解释：存在一条从 (0,0) 到 (2,2) 的有效路径。
 *
 * 示例 2：
 * 输入：grid = [[1,2,1],[1,2,1]]
 * 输出：false
 * 解释：不存在一条从 (0,0) 到 (2,2) 的有效路径。
 *
 * 示例 3：
 * 输入：grid = [[1,1,2]]
 * 输出：false
 * 解释：无法到达右下角单元格。
 *
 * @解题思路
 * 1. 街道方向定义：
 *      - 每种街道类型定义了该单元格可以通行的方向（dx, dy）
 *      - 类型 1: 左(0,-1)、右(0,1)
 *      - 类型 2: 上(-1,0)、下(1,0)
 *      - 类型 3: 左(0,-1)、下(1,0)
 *      - 类型 4: 右(0,1)、下(1,0)
 *      - 类型 5: 上(-1,0)、左(0,-1)
 *      - 类型 6: 右(0,1)、上(-1,0)
 *
 * 2. 街道连通性判断：
 *      - 从当前单元格沿方向 (dx, dy) 移动到下一个单元格
 *      - 下一个单元格必须拥有能回到当前单元格的方向 (-dx, -dy)
 *      - 即当前街道的出口与下一个街道的入口必须匹配
 *
 * 3. 深度优先搜索 (DFS)：
 *      - 从 (0, 0) 开始，沿当前街道允许的方向进行搜索
 *      - 对每个方向，检查是否能移动到下一个单元格
 *      - 如果下一单元格也能反向连接，则继续递归搜索
 *      - 使用 vis 数组记录已访问的单元格，避免循环
 *      - 到达右下角 (m-1, n-1) 时返回 true
 *
 * 4. 复杂度分析：
 *      - 时间复杂度: O(m*n)，每个单元格最多访问一次
 *      - 空间复杂度: O(m*n)，vis 数组 + DFS 递归栈深度
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 定义每种街道类型对应的方向集合
     * dirs[street] 包含该街道类型允许的两个方向 (dx, dy)
     * dirs[0] 为空，因为街道类型从 1 开始
     */
    vector<vector<vector<int> > > dirs = {
         {},
         {{0, 1}, {0, -1}}, // 1: 左-右
         {{-1, 0}, {1, 0}}, // 2: 上-下
         {{0, -1}, {1, 0}}, // 3: 左-下
         {{0, 1}, {1, 0}}, // 4: 右-下
         {{-1, 0}, {0, -1}}, // 5: 上-左
         {{0, 1}, {-1, 0}} // 6: 右-上
     };

    /**
     * @brief 判断下一个街道是否允许沿给定方向的反向进入
     * @param street 下一个单元格的街道类型
     * @param dx 行方向增量
     * @param dy 列方向增量
     * @return true 如果下一个街道允许从方向 (dx, dy) 进入
     */
    bool contains(int street, int dx, int dy) {
        auto dir = dirs[street];
        return (dir[0][0] == -dx && dir[0][1] == -dy) || (dir[1][0] == -dx && dir[1][1] == -dy);
     }

    /**
     * @brief 从 (x, y) 开始深度优先搜索，判断是否能到达右下角
     * @param grid 网格，每个单元格表示街道类型
     * @param vis 已访问标记数组
     * @param x 当前行坐标
     * @param y 当前列坐标
     * @return true 如果可以从 (x, y) 到达右下角
     */
    bool dfs(vector<vector<int> > &grid, vector<vector<int> > &vis, int x, int y) {
        int m = grid.size();
        int n = grid[0].size();

        if (x == grid.size() - 1 && y == grid[0].size() - 1) {
            return true;
         }

        vis[x][y] = 1;
        for (auto it: dirs[grid[x][y]]) {
            int nx = x + it[0];
            int ny = y + it[1];
            if (nx >= 0 && nx < m) {
                if (ny >= 0 && ny < n) {
                    if (!vis[nx][ny]) {
                        if (contains(grid[nx][ny], it[0], it[1])) {
                            if (dfs(grid, vis, nx, ny)) {
                                return true;
                             }
                         }
                     }
                 }
             }
         }


        return false;
     }

    /**
     * @brief 判断网格中是否存在从左上角到右下角的有效路径
     * @param grid m x n 网格，每个单元格表示街道类型 (1~6)
     * @return true 如果存在有效路径
     */
    bool hasValidPath(vector<vector<int> > &grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int> > vis(m, vector<int>(n, 0));

        return dfs(grid, vis, 0, 0);
     }
};

TEST(Daily, 1391) {
    Solution s;
    auto grid = vector<vector<int> >{{1, 1, 2}};
    auto ret = s.hasValidPath(grid);
    EXPECT_EQ(false, ret);
}
