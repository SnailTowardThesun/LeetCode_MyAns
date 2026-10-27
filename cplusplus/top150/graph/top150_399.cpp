//
// Created by 韩堃 on 2026/10/27.
//

// @题目描述:
// 399. 除法求值（Evaluate Division）— Medium
// 给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，
// 其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i]。
// 每个 Ai 或 Bi 是一个表示单个变量的字符串。
// 另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，
// 请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。
// 返回所有问题的答案。如果存在某个无法确定的答案，则用 -1.0 替代这个答案；
// 如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。
// 注意：输入总是有效的。可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。
//
// @示例:
// 输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0],
//       queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
// 输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
// 解释：a / c = a / b * b / c = 6.0；b / a = 0.5；
//       e、x 未在已知条件中出现 → -1.0；a / a = 1.0。
//
// 输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0],
//       queries = [["a","c"],["c","b"],["bc","cd"],["bc","bd"]]
// 输出：[3.75000,0.40000,5.00000,-1.00000]
//
// 输入：equations = [["a","b"]], values = [0.5],
//       queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
// 输出：[0.50000,2.00000,-1.00000,-1.00000]

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdlib>
#include <locale>
#include <string>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class UnionFind {
    public:
        vector<int> parent;
        vector<double> weight;

        UnionFind(int n) {
            for (int i = 0; i < n; i++) {
                parent.emplace_back(i);
                weight.emplace_back(1.0);
            }
        }

        int find(int x) {
            if (parent[x] != x) {
                int p = parent[x];
                int root = find(p);

                parent[x] = root;
                weight[x] = weight[x] * weight[p];
            }
            return parent[x];
        }

        void unit(int x, int y, double v){
            int root_x = find(x);
            int root_y = find(y);
            if (root_x == root_y) {
                return ;
            }

            parent[root_x] = root_y;
            weight[root_x] = v * weight[y] / weight[x];
        }
};
class Solution {
   public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values,
                                vector<vector<string>>& queries) {
        vector<double> ret;

        map<string, int> container;
        for (auto i : equations) {
            for (auto j : i) {
                if (container.count(j) == 0) {
                    container[j] = container.size();
                }
            }
        }

        UnionFind uf(container.size());
        for (auto i = 0; i < equations.size(); i++) {
            auto x = equations[i][0];
            auto y = equations[i][1];
            auto v = values[i];
            uf.unit(container[x], container[y], v);
        }

        for (auto i = 0; i < queries.size(); i++) {
            auto c = queries[i][0];
            auto d = queries[i][1];
            if (container.count(c) == 0 || container.count(d) == 0) {
                ret.emplace_back(-1.0);
            } else if (uf.find(container[c]) != uf.find(container[d])) {
                ret.emplace_back(-1.0);
            } else {
                ret.emplace_back(uf.weight[container[c]] / uf.weight[container[d]]);
            }
        }

        return ret;
    }
};
}  // namespace

TEST(top150, 399) {
    Solution s;

    // 官方示例 1：a/b=2, b/c=3 → a/c=6；a/a=1；e、x 未定义 → -1
    vector<vector<string>> equations1 = {{"a", "b"}, {"b", "c"}};
    vector<double> values1 = {2.0, 3.0};
    vector<vector<string>> queries1 = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
    vector<double> expected1 = {6.0, 0.5, -1.0, 1.0, -1.0};
    auto ret1 = s.calcEquation(equations1, values1, queries1);
    ASSERT_EQ(ret1.size(), expected1.size());
    for (size_t i = 0; i < expected1.size(); i++) {
        EXPECT_NEAR(ret1[i], expected1[i], 1e-5) << "示例1 第 " << i << " 个查询不符";
    }

    // 官方示例 2：多段链式相乘；bd 未出现 → -1
    vector<vector<string>> equations2 = {{"a", "b"}, {"b", "c"}, {"bc", "cd"}};
    vector<double> values2 = {1.5, 2.5, 5.0};
    vector<vector<string>> queries2 = {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"bc", "bd"}};
    vector<double> expected2 = {3.75, 0.4, 5.0, -1.0};
    auto ret2 = s.calcEquation(equations2, values2, queries2);
    ASSERT_EQ(ret2.size(), expected2.size());
    for (size_t i = 0; i < expected2.size(); i++) {
        EXPECT_NEAR(ret2[i], expected2[i], 1e-5) << "示例2 第 " << i << " 个查询不符";
    }

    // 官方示例 3：单条等式，反向查询取倒数；未定义变量 → -1
    vector<vector<string>> equations3 = {{"a", "b"}};
    vector<double> values3 = {0.5};
    vector<vector<string>> queries3 = {{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}};
    vector<double> expected3 = {0.5, 2.0, -1.0, -1.0};
    auto ret3 = s.calcEquation(equations3, values3, queries3);
    ASSERT_EQ(ret3.size(), expected3.size());
    for (size_t i = 0; i < expected3.size(); i++) {
        EXPECT_NEAR(ret3[i], expected3[i], 1e-5) << "示例3 第 " << i << " 个查询不符";
    }
}
