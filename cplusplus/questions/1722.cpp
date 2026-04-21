// 1722. 执行交换操作后的最小汉明距离
// 题目：https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/
// 题目描述：
// 给你两个整数数组 source 和 target，以及一个二维数组 allowedSwaps，其中 allowedSwaps[i] = [ai, bi] 表示你可以交换 source 中位于 ai 和 bi 位置的两个元素。
// 你可以最多交换一次 allowedSwaps 中的任意两个元素（也可以不进行交换）。
// 返回 source 和 target 之间的最小汉明距离。
// 汉明距离定义为两个数组在相同位置上有不同值的个数。
// 示例 1：
//   输入：source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
//   输出：1
//   解释：交换 source[0] 和 source[1]，得到 [2,1,3,4]，与 target 比较在位置2和3不同，汉明距离为1。
// 示例 2：
//   输入：source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
//   输出：0
// 解题思路：
// 1. 并查集：将可以通过交换操作相互到达的位置合并到同一个连通分量
// 2. 哈希表：记录每个连通分量中各元素的出现频率
// 3. 遍历 target，检查每个位置能否在同连通分量内匹配
// 4. 不能匹配的位置数即为最小汉明距离
// 时间复杂度：O((n+m) log n)，空间复杂度：O(n)

#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        // 并查集：初始化 parent 数组，每个元素的根节点指向自己
        int n = source.size();
        vector<int> parent(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        // 查找函数：带路径压缩的递归查找
        function<int(int)> find = [&](int x) -> int {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };

        // 合并函数：将两个元素所在的集合合并
        auto unionSet = [&](int u, int v) {
            int pu = find(u);
            int pv = find(v);
            if (pu != pv) {
                parent[pu] = pv;
            }
        };

        // 根据 allowedSwaps 构建连通分量
        for (auto& swap : allowedSwaps) {
            unionSet(swap[0], swap[1]);
        }

        // 哈希表：记录每个连通分量中各元素的出现频率
        unordered_map<int, unordered_map<int, int>> compFreq;
        for (int i = 0; i < n; i++) {
            int root = find(i);
            compFreq[root][source[i]]++;
        }

        // 计算最小汉明距离：遍历 target，检查每个位置能否在同连通分量内匹配
        int hammingDist = 0;
        for (int i = 0; i < n; i++) {
            int root = find(i);
            auto& freqMap = compFreq[root];
            if (freqMap[target[i]] > 0) {
                freqMap[target[i]]--;
            } else {
                hammingDist++;
            }
        }

        return hammingDist;
    }
};

TEST(Daily, 1722) {
    Solution s;
    auto source = vector<int>{1,2,3, 4};
    auto target = vector<int>{2,1,4, 5};
    auto allowedSwaps = vector<vector<int>>{{0,1}, {2,3}};
    EXPECT_EQ(s.minimumHammingDistance(source, target, allowedSwaps), 1);
}
