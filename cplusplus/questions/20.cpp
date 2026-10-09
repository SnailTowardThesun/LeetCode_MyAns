//
// Created by hankun on 2026/10/1.
//

/**
 * @file 20.cpp
 * @brief LeetCode 20. 有效的括号
 *
 * @题目描述
 * 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s，
 * 判断字符串是否有效。
 * 有效字符串需满足：
 * - 左括号必须用相同类型的右括号闭合；
 * - 左括号必须以正确的顺序闭合；
 * - 每个右括号都有一个对应的相同类型的左括号。
 *
 * @示例
 * 示例 1：
 * 输入：s = "()"
 * 输出：true
 *
 * 示例 2：
 * 输入：s = "()[]{}"
 * 输出：true
 *
 * 示例 3：
 * 输入：s = "(]"
 * 输出：false
 *
 * 示例 4：
 * 输入：s = "([)]"
 * 输出：false
 *
 * 示例 5：
 * 输入：s = "{[]}"
 * 输出：true
 *
 * @解题思路
 * 1. 栈匹配：
 *    - 括号的嵌套结构天然符合"后进先出"，最内层的左括号最先被闭合
 *    - 遇到左括号 '('、'{'、'[' 时入栈
 *    - 遇到右括号时：
 *      a. 栈为空说明没有左括号可配，返回 false
 *      b. 检查栈顶左括号是否与当前右括号同类，不匹配返回 false
 *      c. 匹配则弹栈
 *    - 遍历结束后栈必须为空：还有剩余说明左括号多于右括号
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n)，每个字符处理一次
 *    - 空间复杂度: O(n)，最坏情况全是左括号
 */

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
