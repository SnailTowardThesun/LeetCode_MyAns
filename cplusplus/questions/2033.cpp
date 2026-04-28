//
// 2033. 获取单值网格的最小操作数
// https://leetcode.cn/problems/minimum-operations-to-make-a-uni-value-grid/
//
// 给你一个二维整数网格 grid，grid[i][j] 是第 i 行第 j 列的单元格价值。
// 你可以对 grid 中的任意元素执行以下操作任意次（也可以零次）：
// - 如果 grid[i][j] >= x，则将 grid[i][j] 减少 x
// - 如果 grid[i][j] <= x，则将 grid[i][j] 增加 x
//
// 如果可以将网格 grid 转换为单值网格（所有元素都相同的网格），返回最少操作次数。
// 否则，返回 -1。
//
// 示例 1：
// 输入：grid = [[2,4],[6,8]], x = 2
// 输出：4
// 解释：
// 可以执行以下操作使所有元素变为 4：
// - grid[0][0] 从 2 增加 2 次 2 -> 4（2次操作）
// - grid[0][1] 从 4 减少 0 次 2 -> 4（0次操作）
// - grid[1][0] 从 6 减少 1 次 2 -> 4（1次操作）
// - grid[1][1] 从 8 减少 2 次 2 -> 4（2次操作）
// 总计 4 次操作
//
// 示例 2：
// 输入：grid = [[1,2],[3,4]], x = 2
// 输出：-1
// 解释：1%2=1, 2%2=0, 3%2=1, 4%2=0，无法统一
//
// 解题思路：
// 1. 首先判断是否有解：所有元素对 x 取余必须相同，否则返回 -1
// 2. 将二维网格展平为一维数组并排序
// 3. 找到中位数（最佳目标值）
// 4. 计算所有元素到中位数的距离之和，即为最少操作次数
//
// 时间复杂度：O(m*n*log(m*n))，空间复杂度：O(m*n)
//

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int m = grid.size();
        int n = grid[0].size();

        int t = grid[0][0] % x;

        vector<int> container(m*n, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] % x != t) {
                    return -1;
                }

                container[i*n+j] = grid[i][j];
            }
        }

        std::sort(container.begin(), container.end());
        int median = container[m / 2];

        int ret = 0;
        for (auto i : container) {
            ret += abs(i - median);
        }

        return ret / x;
    }
};

TEST(Daily, 2033) {
    Solution s;
    auto grid = vector<vector<int>> {{2,4},{6,8}};
    auto x = 2;
    auto ret = s.minOperations(grid, x);
    EXPECT_EQ(4, ret);
}
