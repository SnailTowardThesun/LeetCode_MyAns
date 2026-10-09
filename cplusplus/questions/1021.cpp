//
// Created by hankun on 2026/10/8.
//

/**
 * @file 1021.cpp
 * @brief LeetCode 1021. 删除最外层的括号
 *
 * @题目描述
 * 有效括号字符串为空 ""、"(" + A + ")" 或 A + B，其中 A 和 B 都是有效括号字符串。
 * 原始字符串是一个非空的有效括号字符串，且它不能分割为两个非空有效括号字符串的连接。
 * 给定一个有效括号字符串 s，考虑它的原始分解：s = P_1 + P_2 + ... + P_k。
 * 返回删除 s 中每个原始字符串最外层括号后的结果字符串。
 *
 * @示例
 * 示例 1：
 * 输入：s = "(()())(())"
 * 输出："()()()"
 * 解释：原始分解为 "(()())" + "(())"，删除最外层括号后为 "()()" + "()" = "()()()"。
 *
 * 示例 2：
 * 输入：s = "(()())(())(()(()))"
 * 输出："()()()()(())"
 *
 * 示例 3：
 * 输入：s = ""
 * 输出：""
 *
 * @解题思路
 * 1. 栈跟踪嵌套深度：
 *    - 用栈记录当前未匹配的 '('，栈的大小即当前嵌套深度
 *    - 遇到 '(' 时：若栈非空说明它不是最外层，保留到结果中；然后入栈
 *    - 遇到 ')' 时：先弹栈匹配；若弹栈后栈仍非空说明它不是最外层，保留到结果中
 *    - 最外层括号在栈空（深度为 0）时被自然跳过
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n)，其中 n 是字符串长度
 *    - 空间复杂度: O(n)，用于栈和结果字符串
 */

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
