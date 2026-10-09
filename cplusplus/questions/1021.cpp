//
// Created by hankun on 2026/10/8.
//

#include <gtest/gtest.h>
#include <stack>

using namespace std;

class Solution {
public:
    string removeOuterParentheses(string s) {
        string ret;
        stack<char> container;
        for (auto ch: s) {
            if (ch == '(') {
                if (!container.empty()) {
                    ret += ch;
                }
                container.emplace(ch);
            } else {
                if (container.top() == '(') {
                    container.pop();
                }
                if (!container.empty()) {
                    ret += ch;
                }
            }
        }

        return ret;
    }
};

TEST(Daily, 1021) {
    Solution s;
    auto ss = "(()())(())";
    auto ret = s.removeOuterParentheses(ss);
    EXPECT_EQ("()()()", ret);
}
