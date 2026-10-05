//
// Created by hankun on 2026/10/5.
//
#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    int scoreOfParentheses(string s) {
        int ret = 0;

        if (s.empty() || s.size() % 2 != 0) {
            return ret;
        }

        int depth = 0;
        for (auto i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;
                if (s.at(i-1) == '(') {
                    ret += 1<<depth;
                }
            }
        }

        return ret;
    }
};

TEST(Daily, 856) {
    Solution s;
    auto ss = "(()(()))";
    auto ret = s.scoreOfParentheses(ss);
    EXPECT_EQ(ret, 6);
}
