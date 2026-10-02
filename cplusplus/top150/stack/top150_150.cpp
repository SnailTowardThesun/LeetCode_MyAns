//
// Created by 韩堃 on 2026/9/26.
//

// @题目描述:
// 给你一个字符串数组 tokens，表示一个根据逆波兰表示法（后缀表达式）书写的算术表达式。
// 所有操作数为整数或也是表达式；运算符为 +、-、*、/；除法向零取整；
// 不存在除以零。计算整个表达式，返回整数值。
//
// @示例:
// 输入：tokens = ["2","1","+","3","*"]
// 输出：9
// 解释：等价于算式 (2 + 1) * 3 = 9。
//
// @解题思路:
// 栈模拟求值。
// 1. 遍历 token：数字直接入栈。
// 2. 遇到运算符：依次弹出两个操作数 last、pre，按 pre op last 计算后结果入栈。
//    注意弹出顺序，减和除不满足交换律，必须是先弹出的当右操作数。
// 3. 遍历结束栈中唯一元素即答案。
//
// 复杂度分析：
// - 时间复杂度：O(n)。
// - 空间复杂度：O(n)。

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
