// @题目描述:
// 给你一个有效括号字符串 s，返回字符串的嵌套深度。
// 嵌套深度是指字符串中括号的最大嵌套层数。
//
// @示例:
// 示例 1：
// 输入：s = "(1+(2*3)+((8)/4))+1"
// 输出：3
// 解释：数字 8 在嵌套的 3 层括号中。
//
// 示例 2：
// 输入：s = "(1)+((2))+(((3)))"
// 输出：3
//
// @解题思路:
// 栈 + 计数器。
// 1. 遍历字符串，遇到 '(' 时计数器 count++，并更新最大深度 ret。
// 2. 遇到 ')' 时计数器 count--。
// 3. 其他字符直接压栈（不影响深度）。
// 4. 栈用于辅助匹配括号（弹栈直到遇到 '('），实际深度由 count 维护。
//
// 复杂度分析：
// - 时间复杂度：O(n)，单次遍历。
// - 空间复杂度：O(n)，栈存储字符。

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
