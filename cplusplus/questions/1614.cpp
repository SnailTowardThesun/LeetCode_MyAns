//
// Created by hankun on 2026/9/28.
//

#include <gtest/gtest.h>
#include <stack>

using namespace std;

class Solution {
public:
    int maxDepth(string s) {
        stack<char> st;
        int ret = 0;

        int count = 0;
        for (auto i: s) {
            if (i == '(') {
                st.emplace(i);
                count++;
                ret = max(ret, count);
            } else if (i == ')') {
                count--;

                // pop
                while (st.top() != '(') {
                    st.pop();
                }

                // pop '('
                st.pop();
            } else {
                st.emplace(i);
            }
        }

        return ret;
    }
};

TEST(Daily, 1614) {
    Solution s;
    string ss = "(1+(2*3)+((8)/4))+1";
    auto ret = s.maxDepth(ss);
    EXPECT_EQ(ret, 3);
}
