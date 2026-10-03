//
// Created by 韩堃 on 2026/10/3.
//

// @题目描述:
// 给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。
//
// @示例:
// 示例 1：输入：s = "(()"      输出：2    解释：最长有效括号子串是 "()"
// 示例 2：输入：s = ")()())"   输出：4    解释：最长有效括号子串是 "()()"
// 示例 3：输入：s = ""         输出：0
//
// @解题思路:
// 使用下标栈一次遍历，栈底始终存放“最后一个未被匹配的右括号”的下标，作为有效区间的断点，初始压入 -1：
// 1. 遇到 '('：将其下标压栈，等待匹配；
// 2. 遇到 ')'：弹出栈顶（尝试与一个左括号配对）；
//    - 弹完后栈为空：说明该右括号多余，将其下标压栈成为新的断点；
//    - 弹完后栈非空：配对成功，以当前位置结尾的有效串长度为 i - 栈顶下标，更新答案。
//
// 复杂度分析：
// - 时间复杂度：O(n)，每个下标至多入栈、出栈各一次；
// - 空间复杂度：O(n)，最坏情况下（全为左括号）栈中保存全部下标。

#include <gtest/gtest.h>

#include <stack>

using namespace std;

class Solution {
   public:
    int longestValidParentheses(string s) {
        int ret = 0;

        stack<int> stk;
        stk.emplace(-1);
        for (auto i = 0; i < s.size(); ++i) {
            if (s.at(i) == '(') {
                stk.emplace(i);
            } else {
                stk.pop();
                if (stk.empty()) {
                    stk.emplace(i);
                } else {
                    ret = max(ret, i - stk.top());
                }
            }
        }

        return ret;
    }
};

TEST(Daily, 32) {
    Solution s;
    // 基本用例：一对括号
    EXPECT_EQ(s.longestValidParentheses("()"), 2);
    // 嵌套：完整匹配
    EXPECT_EQ(s.longestValidParentheses("(()"), 2);
    // 右括号开头，中间存在有效串
    EXPECT_EQ(s.longestValidParentheses(")()())"), 4);
    // 边界：空串
    EXPECT_EQ(s.longestValidParentheses(""), 0);
    // 边界：全部无法匹配
    EXPECT_EQ(s.longestValidParentheses("((("), 0);
}