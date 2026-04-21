// 2452. Words Within Two Edits of Dictionary
// 题目：https://leetcode.com/problems/words-within-two-edits-of-dictionary/
// 题目描述：
// 给你两个字符串数组 queries 和 dictionary，每个数组中的单词仅由小写英文字母组成，且长度相同。
// 一次编辑可以：将 queries 中的某个单词的任意一个字符改变为另一个不同的字符。
// 从 queries 中找到所有满足条件的字符串：经过最多两次编辑后，可以与 dictionary 中某个单词相同。
// 返回所有满足条件的 queries 中的单词，返回顺序与 queries 中的顺序一致。
// 示例 1：
//   输入：queries = ["word","note","ants","wood"], dictionary = ["wood","joke","moat"]
//   输出：["word","note","wood"]
//   解释：将 "word" 的 'r' 改为 'o' 可变成 "wood"；将 "note" 的 'n' 改为 'j'，'t' 改为 'k' 可变成 "joke"；
//        "ants" 需要超过 2 次编辑；"wood" 无需编辑即匹配。
// 示例 2：
//   输入：queries = ["yes"], dictionary = ["not"]
//   输出：[]
//   解释：对 "yes" 进行任意两次编辑都无法变成 "not"。
// 约束：1 <= queries.length, dictionary.length <= 100，n == queries[i].length == dictionary[j].length，1 <= n <= 100
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
