//
// Created by 韩堃 on 2026/3/28.
//

/*
 * 对任一由 n 个小写英文字母组成的字符串 word ，我们可以定义一个 n x n 的矩阵，并满足：
 *
 * lcp[i][j] 等于子字符串 word[i,...,n-1] 和 word[j,...,n-1] 之间的最长公共前缀的长度。
 * 给你一个 n x n 的矩阵 lcp 。返回与 lcp 对应的、按字典序最小的字符串 word 。
 * 如果不存在这样的字符串，则返回空字符串。
 *
 * 对于长度相同的两个字符串 a 和 b ，如果在 a 和 b 不同的第一个位置，字符串 a 的字母在字母表中出现的顺序先于 b
 * 中的对应字母，则认为字符串 a 按字典序比字符串 b 小。例如，"aabd" 在字典上小于 "aaca"
 * ，因为二者不同的第一位置是第三个字母，而 'b' 先于 'c' 出现。
 *
 * 示例 1：
 * 输入：lcp = [[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
 * 输出："abab"
 * 解释：lcp 对应由两个交替字母组成的任意 4 字母字符串，字典序最小的是 "abab" 。
 *
 * 示例 2：
 * 输入：lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,1]]
 * 输出："aaaa"
 * 解释：lcp 对应只有一个不同字母的任意 4 字母字符串，字典序最小的是 "aaaa" 。
 *
 * 示例 3：
 * 输入：lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,3]]
 * 输出：""
 * 解释：lcp[3][3] 无法等于 3 ，因为 word[3,...,3] 仅由单个字母组成；因此，不存在答案。
 *
 * 提示：
 * 1 <= n == lcp.length == lcp[i].length <= 1000
 * 0 <= lcp[i][j] <= n
 */

#include <gtest/gtest.h>

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
