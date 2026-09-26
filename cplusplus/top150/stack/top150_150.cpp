//
// Created by 韩堃 on 2026/9/26.
//

#include <gtest/gtest.h>
#include <stack>

using namespace std;


class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> container;
        container.emplace(stoi(tokens[0]));

        int ret = stoi(tokens[0]);
        for (auto i = 1; i < tokens.size(); i++) {
            if (tokens[i] == "+") {
                // pop two to add
                int last = container.top();
                container.pop();
                int pre = container.top();
                container.pop();

                ret = pre + last;
                container.emplace(ret);

            } else if (tokens[i] == "-") {
                int last = container.top();
                container.pop();
                int pre = container.top();
                container.pop();

                ret = pre - last;
                container.emplace(ret);

            } else if (tokens[i] == "*") {
                int last = container.top();
                container.pop();
                int pre = container.top();
                container.pop();

                ret = pre * last;
                container.emplace(ret);

            } else if (tokens[i] == "/") {
                int last = container.top();
                container.pop();
                int pre = container.top();
                container.pop();

                ret = pre / last;
                container.emplace(ret);

            } else {
                container.emplace(stoi(tokens[i]));
            }
        }

        return ret;
    }
};

TEST(top150,150) {
    Solution s;
    vector<string> tokens{"2","1","+","3","*"};
    auto ret = s.evalRPN(tokens);
    EXPECT_EQ(ret, 9);
}
