//
// Created by 韩堃 on 2026/9/27.
//
// @题目描述:
// LeetCode 1190. 反转每对括号间的子串（Reverse Substrings Between Each Pair of Parentheses）
// 给出一个字符串 s（仅含有小写英文字母和括号）。
// 请你按照从括号内到外的顺序，逐层反转每对匹配括号中的字符串，并返回最终的字符串。
// 注意：结果中不应包含任何括号。
//
// @示例:
// 示例 1：
// 输入：s = "(abcd)"
// 输出："dcba"
//
// 示例 2：
// 输入：s = "(u(love)i)"
// 输出："iloveu"
// 解释：先反转内层 (love) -> evol，得到 "(uevoli)"，再整体反转 -> "iloveu"。
//
// 示例 3：
// 输入：s = "a(bcdefghijkl(mno)p)q"
// 输出："apmnolkjihgfedcbq"
//
// @解题思路（栈模拟）:
// 1. 顺序扫描 s，普通字符直接压栈；
// 2. 遇到 ')'：不断弹栈直到遇到 '('，弹出的字符顺序天然是「倒序」，
//    正好完成一次反转（tmp 不需要再 reverse）；再弹出 '('，把 tmp 依次压回栈中；
// 3. 扫描结束后栈中字符是正序串的逆序存放，依次弹出再整体 reverse 一次即可。
// 关键点：嵌套括号时，内层先处理、结果压回栈，外层 ')' 会把内层结果一起反转，
//         自动实现「由内到外逐层反转」。
//
// 复杂度分析：
// - 时间复杂度：O(n^2)，最坏情况（如全嵌套）每个字符进出栈 O(n) 次。
// - 空间复杂度：O(n)，栈和临时字符串。

#include <gtest/gtest.h>

#include <algorithm>
#include <stack>
#include <string>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    string reverseParentheses(string s) {
        stack<char> st;
        for (auto i : s) {
            if (i == ')') {
                // 收集 '(' 之后的全部字符，弹栈顺序本身就是反转顺序
                string tmp = "";
                while (st.top() != '(') {
                    tmp += st.top();
                    st.pop();
                }

                // pop '('
                st.pop();
                // tmp 已经是反转后的结果，依次压回栈即可，无需 reverse
                for (auto j : tmp) {
                    st.emplace(j);
                }
            } else {
                st.emplace(i);
            }
        }

        // 栈中自底向上是正序串，弹栈得到逆序，最后再 reverse 还原
        string ret = "";
        while (st.empty() == false) {
            ret += st.top();
            st.pop();
        }
        reverse(ret.begin(), ret.end());

        return ret;
    }
};
}  // namespace

TEST(Daily, 1190) {
    Solution s;
    // 示例 2：嵌套括号
    string ss = "(u(love)i)";
    EXPECT_EQ(s.reverseParentheses(ss), "iloveu");

    // 示例 1：单层括号
    EXPECT_EQ(s.reverseParentheses("(abcd)"), "dcba");

    // 示例 3：括号外有普通字符，多层嵌套
    EXPECT_EQ(s.reverseParentheses("a(bcdefghijkl(mno)p)q"), "apmnolkjihgfedcbq");

    // 边界：无括号，原样返回
    EXPECT_EQ(s.reverseParentheses("abcd"), "abcd");

    // 边界：多段并列括号 "(ab)(cd)" -> "ba" + "dc"
    EXPECT_EQ(s.reverseParentheses("(ab)(cd)"), "badc");
}
