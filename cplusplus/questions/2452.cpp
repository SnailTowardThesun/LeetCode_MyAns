// 2452. Words Within Two Edits of Dictionary
// 题目：https://leetcode.com/problems/words-within-two-edits-of-dictionary/
// 解题思路：
// 1. 遍历 queries 中的每个单词
// 2. 对于每个单词，遍历 dictionary 中的所有单词
// 3. 使用 isValid 函数检查两个单词的编辑距离是否不超过 2
// 4. 如果编辑距离 <= 2，则将该 query 加入结果集
// 5. 时间复杂度：O(n * m * k)，空间复杂度：O(1)
// 编辑定义：改变任意一个字符为另一个不同字符为一次编辑

#include <gtest/gtest.h>
#include <climits>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isValid(string s, string p) {
        int diffs = 0;
        for (int i = 0; i < p.size(); ++i) {
            if (s.at(i) != p[i]) {
                diffs++;
            }

            if (diffs > 2) {
                break;
            }
        }

        return diffs <= 2;
    }

    vector<string> twoEditWords(vector<string> &queries, vector<string> &dictionary) {
        vector<string> ret;
        for (int i = 0; i < queries.size(); ++i) {
            for (int j = 0; j < dictionary.size(); ++j) {
                if (isValid(queries[i], dictionary[j])) {
                    ret.push_back(queries[i]);
                    break;
                }
            }
        }

        return ret;
    }
};

TEST(Daily, 2452) {
    Solution s;
    auto queries = vector<string>{"word", "note", "ants", "wood"};
    auto dictionary = vector<string>{"wood", "joke", "moat"};

    auto ret = s.twoEditWords(queries, dictionary);
    EXPECT_EQ(ret.size(), 3);
}
