//
// Created by 韩堃 on 2026/10/3.
//

// @题目描述:
// 给你一个字符串表达式 s，请你实现一个基本计算器来计算并返回它的值。
// - s 由数字、'+'、'-'、'('、')' 和空格 ' ' 组成；
// - 输入表达式始终有效，只有加减法，允许括号嵌套；
// - 所有整数均为非负数，结果保证是一个 32 位有符号整数。
//
// @示例:
// 示例 1：输入：s = "1 + 1"                  输出：2
// 示例 2：输入：s = " 2-1 + 2 "              输出：3
// 示例 3：输入：s = "(1+(4+5+2)-3)+(6+8)"    输出：23
//
// @解题思路:
// 一次遍历 + 栈保存括号外的上下文。维护 ret（当前层已结算结果）、num（正在读取的多位数）、
// pre（当前数字前的符号：+1 / -1）：
// 1. 遇到数字：累加到 num（num = num * 10 + digit）；
// 2. 遇到 '+' / '-'：把 pre * num 结算进 ret，重置 num 并更新符号；
// 3. 遇到 '('：把当前层的 ret 和符号压栈，然后重置为括号内的新一层（ret=0, pre=1）；
// 4. 遇到 ')'：先结算括号内最后一个数字，ret 乘上栈中保存的括号外符号，
//    再加上栈中保存的括号外结果，完成一层归并；
// 5. 空格直接忽略；循环结束后补上最后一个数字 ret + pre * num。
//
// 复杂度分析：
// - 时间复杂度：O(n)，每个字符处理一次；
// - 空间复杂度：O(n)，括号嵌套深度决定栈大小。

#include <gtest/gtest.h>

#include <stack>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int calculate(string s) {
        long ret = 0;
        long num = 0;
        long pre = 1;  // 1 for plus, -1 for minus
        stack<long> stk;

        for (auto c : s) {
            if (c >= '0' && c <= '9') {
                num = num * 10 + c - '0';
            } else if (c == '+') {
                ret += pre * num;
                num = 0;
                pre = 1;
            } else if (c == '-') {
                ret += pre * num;
                num = 0;
                pre = -1;
            } else if (c == '(') {
                stk.push(ret);
                stk.push(pre);
                ret = 0;
                pre = 1;
            } else if (c == ')') {
                ret += num * pre;
                num = 0;
                ret *= stk.top();
                stk.pop();
                ret += stk.top();
                stk.pop();
            }
        }

        return static_cast<int>(ret + pre * num);
    }
};
}  // namespace

TEST(top150, 224) {
    Solution s;
    // 基本加减
    EXPECT_EQ(s.calculate("1 + 1"), 2);
    // 带空格
    EXPECT_EQ(s.calculate(" 2-1 + 2 "), 3);
    // 括号嵌套
    EXPECT_EQ(s.calculate("(1+(4+5+2)-3)+(6+8)"), 23);
    // 边界：单个数字
    EXPECT_EQ(s.calculate("2147483647"), 2147483647);
    // 边界：括号前为负号，括号内整体取反
    EXPECT_EQ(s.calculate("2-(5-6)"), 3);
}