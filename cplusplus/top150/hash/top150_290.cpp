//
// Created by hankun on 2026/10/1.
//

/**
 * @file top150_290.cpp
 * @brief LeetCode 290. 单词规律
 *
 * @题目描述
 * 给定一种规律 pattern 和一个字符串 s，判断 s 是否遵循相同的规律。
 * 这里的"遵循"指完全匹配，例如 pattern 里的每个字母和字符串 s 中的每个
 * 非空单词之间存在着双向连接的对应规律。
 *
 * @示例
 * 示例 1：
 * 输入：pattern = "abba", s = "dog cat cat dog"
 * 输出：true
 * 解释：a ↔ dog, b ↔ cat。
 *
 * 示例 2：
 * 输入：pattern = "abba", s = "dog dog dog dog"
 * 输出：false
 * 解释：a 和 b 都应映射到 dog，违反双向一一对应。
 *
 * 示例 3：
 * 输入：pattern = "aaaa", s = "dog cat cat dog"
 * 输出：false
 *
 * @解题思路
 * 1. 分词 + 双向哈希映射：
 *    - 先把 s 按空格拆分成单词数组 words
 *    - 若 pattern 长度与 words 数量不相等，直接返回 false
 *    - 维护两个哈希表：m1（字母 → 单词）、m2（单词 → 字母）
 *    - 遍历每一对（字母 c, 单词 w）：
 *      a. 若两者都是新出现的，建立双向映射
 *      b. 若只有一方出现过，说明映射冲突，返回 false
 *      c. 若双方都出现过，检查现有映射是否互相一致，不一致返回 false
 *    - 双向映射保证一一对应，避免 "dog dog dog dog" 这类多对一误判
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n + m)，n 是 pattern 长度，m 是字符串总长度
 *    - 空间复杂度: O(n + m)，用于单词数组和两个哈希表
 */

#include <gtest/gtest.h>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    bool wordPattern(string pattern, string s) {
        vector<string> words;
        string tmp = "";
        for (auto ch : s) {
            if (ch == ' ' && !tmp.empty()) {
                words.emplace_back(tmp);
                tmp = "";
                continue;
            }

            tmp += ch;
        }
        if (!tmp.empty()) {
            words.emplace_back(tmp);
        }

        if (pattern.size() != words.size()) {
            return false;
        }

        unordered_map<char, string> m1;
        unordered_map<string, char> m2;
        for (auto i = 0; i < pattern.size(); ++i) {
            auto c = pattern.at(i);
            auto w = words.at(i);
            if (m1.find(c) == m1.end() && m2.find(w) == m2.end()) {
                m1[c] = w;
                m2[w] = c;
            } else {
                if (m1.find(c) == m1.end() || m2.find(w) == m2.end()) {
                    return false;
                }

                if (m1[c] != w || m2[w] != c) {
                    return false;
                }
            }
        }

        return true;
    }
};
}  // namespace

TEST(top150, 290) {
    Solution solution;
    string pattern = "abba";
    string sentence = "dog cat cat dog";
    auto ret = solution.wordPattern(pattern, sentence);
    EXPECT_TRUE(ret);

    string duplicate_pattern = "abba";
    string duplicate_sentence = "dog dog dog dog";
    EXPECT_FALSE(solution.wordPattern(duplicate_pattern, duplicate_sentence));
}
