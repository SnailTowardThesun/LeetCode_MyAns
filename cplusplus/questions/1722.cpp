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
