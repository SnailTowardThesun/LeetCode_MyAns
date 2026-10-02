// @题目描述:
// 对任一由 n 个小写英文字母组成的字符串 word，定义一个 n × n 的矩阵 lcp，其中
// lcp[i][j] 等于子串 word[i..n-1] 和 word[j..n-1] 的最长公共前缀长度。
// 给你一个 n × n 的矩阵 lcp，返回与 lcp 对应的、按字典序最小的字符串 word。
// 如果不存在这样的字符串，返回空字符串。
//
// @示例:
// 示例 1：
// 输入：lcp = [[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
// 输出："abab"
//
// 示例 2：
// 输入：lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,1]]
// 输出："aaaa"
//
// 示例 3：
// 输入：lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,3]]
// 输出：""
//
// @解题思路:
// 利用 LCP 矩阵的递推性质构造字典序最小字符串。
// 关键性质：若 word[i] == word[j]，则 lcp[i][j] = lcp[i+1][j+1] + 1（边界为 1）；
// 若 word[i] != word[j]，则 lcp[i][j] = 0。
//
// 步骤：
// 1. 贪心赋值：从左到右扫描，遇到未赋值位置 i 时赋当前最小可用字符 c，
//    并将所有满足 lcp[i][j] > 0 的位置 j 也赋值为 c（因为 lcp[i][j] > 0 意味着 word[i] == word[j]）。
//    若字符超过 'z'，返回空串。
// 2. 验证：从右下到左上递推验证每个 lcp[i][j] 是否与构造出的字符串一致，
//    不一致则返回空串。
//
// 本文件同时提供并查集（SolutionUnionFind）和贪心（SolutionGreedy）两种实现，
// 核心思路一致：先合并等价位置，再按字典序最小分配字符，最后验证。
//
// 复杂度分析：
// - 时间复杂度：O(n^2)，构造和验证各遍历一次矩阵。
// - 空间复杂度：O(n)，存储结果字符串和并查集/字符映射。

#include <gtest/gtest.h>

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

class SolutionUnionFind {
   public:
    /**
     * 构建与 LCP 矩阵对应的字典序最小字符串, 并查集算法
     *
     * @param lcp 给定的 n x n LCP 矩阵
     * @return 字典序最小的字符串，不存在则返回空字符串
     */
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();

        string ret(n, '1');
        vector<int> container(n, -1);
        iota(container.begin(), container.end(), 0);

        auto find = [&](auto self, int i) -> int {
            if (container[i] == i) {
                return i;
            }

            container[i] = self(self, container[i]);
            return container[i];
        };

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (lcp[i][j] > 0) {
                    int rootI = find(find, i), rootJ = find(find, j);
                    if (rootI != rootJ) {
                        container[rootI] = rootJ;  // 合并 i 和 j 的集合
                    }
                }
            }
        }

        char ch = 'a';
        vector<char> char_map(n, '1');
        for (int i = 0; i < n; i++) {
            int root = find(find, i);
            if (char_map[root] == '1') {
                if (ch > 'z') {
                    return "";
                }
                char_map[root] = ch++;
            }
            ret[i] = char_map[root];
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int correct_number = 0;
                if (ret.at(i) == ret.at(j)) {
                    if (i == n - 1 || j == n - 1) {
                        correct_number = 1;
                    } else {
                        correct_number = lcp[i + 1][j + 1] + 1;
                    }
                }

                if (lcp[i][j] != correct_number) {
                    return "";
                }
            }
        }

        return ret;
    }
};

class SolutionGreedy {
   public:
    /**
     * 构建与 LCP 矩阵对应的字典序最小字符串, 贪心算法
     *
     * @param lcp 给定的 n x n LCP 矩阵
     * @return 字典序最小的字符串，不存在则返回空字符串
     */
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        string container(n, '1');

        char c = 'a';
        for (int i = 0; i < n; i++) {
            if (container.at(i) != '1') {
                continue;
            }

            if (c > 'z') {
                std::cout << "c > 'z'" << std::endl;
                return "";
            }

            for (int j = i; j < n; j++) {
                if (lcp[i][j] > 0) {
                    container.at(j) = c;
                }
            }

            c++;
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int correct_number = 0;
                if (container.at(i) == container.at(j)) {
                    if (i == n - 1 || j == n - 1) {
                        correct_number = 1;
                    } else {
                        correct_number = lcp[i + 1][j + 1] + 1;
                    }
                }

                if (lcp[i][j] != correct_number) {
                    return "";
                }
            }
        }

        return container;
    }
};

TEST(Daily, 2573) {
    // SolutionGreedy solution;
    SolutionUnionFind solution;

    // 示例 1：交替字母情况
    vector<vector<int>> lcp1 = {{4, 0, 2, 0}, {0, 3, 0, 1}, {2, 0, 2, 0}, {0, 1, 0, 1}};
    EXPECT_EQ(solution.findTheString(lcp1), "abab");

    // 示例 2：全相同字母情况
    vector<vector<int>> lcp2 = {{4, 3, 2, 1}, {3, 3, 2, 1}, {2, 2, 2, 1}, {1, 1, 1, 1}};
    EXPECT_EQ(solution.findTheString(lcp2), "aaaa");

    // 示例 3：无效 LCP 矩阵情况
    vector<vector<int>> lcp3 = {{4, 3, 2, 1}, {3, 3, 2, 1}, {2, 2, 2, 1}, {1, 1, 1, 3}};
    EXPECT_EQ(solution.findTheString(lcp3), "");
}
