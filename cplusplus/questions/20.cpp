//
// Created by hankun on 2026/10/1.
//
#include <gtest/gtest.h>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> container;
        for (auto ch : s) {
            if (ch == '(' || ch == '{' || ch == '[') {
                container.emplace(ch);
            } else {
                if (container.size() == 0) {
                    return false;
                }

                auto top = container.top();
                if (top == '(' && ch != ')') {
                    return false;
                }
                if (top == '[' && ch != ']') {
                    return false;
                }
                if (top == '{' && ch != '}') {
                    return false;
                }

                container.pop();
            }
        }

        return container.empty();
    }
};

TEST(Daily, 20) {
    Solution s;
    auto ss = "()[]{}";
    auto ret = s.isValid(ss);
    EXPECT_TRUE(ret);
}