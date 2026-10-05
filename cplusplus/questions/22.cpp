//
// Created by hankun on 2026/10/2.
//

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    void dfs(string path, vector<string> &container, int n, int left, int right) {
        if (left > n) {
            return;
        }
        if (right > left) {
            return;
        }

        if (path.length() == n * 2) {
            container.push_back(path);
            return;
        }

        dfs(path + "(", container, n, left + 1, right);
        dfs(path + ")", container, n, left, right + 1);
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        dfs("", ret, n, 0, 0);
        // auto valid = [](string str) {
        //     stack<string> st;
        //     for (int i = 0; i < str.length(); i++) {
        //         if (str[i] == '(') {
        //             st.push(str.substr(0, i));
        //         } else if (str[i] == ')') {
        //             if (st.empty()) {
        //                 return false;
        //             }
        //             st.pop();
        //         }
        //     }

        //     return st.empty();
        // };

        // vector<string> ans;
        // for (int i = 0; i < container.size(); i++) {
        //     if (valid(container[i])) {
        //         ans.push_back(container[i]);
        //     }
        // }
        return ret;
    }
};

TEST(Daily, 22) {
    Solution s;
    auto ret = s.generateParenthesis(3);
    EXPECT_EQ(ret.size(), 5);
    for (int i = 0; i < ret.size(); i++) {
        cout << ret[i] << endl;
    }
}
