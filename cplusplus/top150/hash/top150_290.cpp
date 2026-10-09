//
// Created by hankun on 2026/10/1.
//
#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words;
        string tmp = "";
        for (auto ch: s) {
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
