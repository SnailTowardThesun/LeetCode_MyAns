// @题目描述:
// 给你一个正整数 n，表示总共有 n 个城市，城市从 1 到 n 编号。给你一个二维数组 roads，
// 其中 roads[i] = [ai, bi, distancei] 表示城市 ai 和 bi 之间有一条双向道路，道路距离为 distancei。
// 城市构成的图不一定是连通的。两个城市之间一条路径的分数定义为这条路径中道路的最小距离。
// 返回城市 1 和城市 n 之间的所有路径的最小分数。
//
// @示例:
// 示例 1：
// 输入：n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
// 输出：5
// 解释：城市 1 到城市 4 的路径中，分数最小的一条为：1 -> 2 -> 4。这条路径的分数是 min(9,5) = 5。
//
// 示例 2：
// 输入：n = 4, roads = [[1,2,2],[1,3,4],[3,4,7]]
// 输出：2
// 解释：城市 1 到城市 4 分数最小的路径是：1 -> 2 -> 1 -> 3 -> 4。这条路径的分数是 min(2,2,4,7) = 2。
//
// @解题思路:
// 这道题的关键在于理解：题目允许路径多次包含同一条道路，也可以多次到达城市 1 和城市 n。
// 因此，只要某条道路在城市 1 所在的连通分量中，就可以被纳入路径中。
// 所以问题转化为：找出城市 1 所在连通分量中的最小边权。
//
// 使用深度优先搜索（DFS）：
// 1. 构建邻接表表示图
// 2. 从城市 1 开始进行 DFS，遍历所有可达的城市
// 3. 在遍历过程中记录遇到的最小边权
// 4. 返回最小边权作为答案
//
// 复杂度分析：
// - 时间复杂度：O(n + m)，n 是城市数量，m 是道路数量
// - 空间复杂度：O(n + m)，邻接表和访问标记数组

#include <gtest/gtest.h>

#include <climits>
#include <vector>

using namespace std;

class Solution {
   public:
    void dfs(vector<vector<pair<int, int>>>& container, vector<int>& vis, int pos, int& ans) {
        vis[pos] = true;
        for (auto i : container[pos]) {
            ans = min(i.second, ans);
            if (!vis[i.first]) {
                dfs(container, vis, i.first, ans);
            }
        }
    }

    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> container(n + 1);
        vector<int> visual(n + 1, 0);
        int res = INT_MAX;

        for (auto i : roads) {
            container[i[0]].emplace_back(pair<int, int>{i[1], i[2]});
            container[i[1]].emplace_back(pair<int, int>{i[0], i[2]});
        }

        dfs(container, visual, 1, res);

        return res;
    }
};

TEST(Daily, 2492) {
    Solution s;

    int n = 4;
    vector<vector<int>> roads{{1, 2, 9}, {2, 3, 6}, {2, 4, 5}, {1, 4, 7}};
    int ret = s.minScore(n, roads);
    EXPECT_EQ(5, ret);

    n = 4;
    roads = {{1, 2, 2}, {1, 3, 4}, {3, 4, 7}};
    ret = s.minScore(n, roads);
    EXPECT_EQ(2, ret);
}
