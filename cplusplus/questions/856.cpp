//
// Created by hankun on 2026/10/5.
//

/**
 * @file 856.cpp
 * @brief LeetCode 856. 括号的分数
 *
 * @题目描述
 * 给定一个平衡括号字符串 s，按如下规则计算并返回它的得分：
 * - "()" 得 1 分
 * - AB 得 A + B 分，其中 A 和 B 是平衡括号字符串
 * - (A) 得 2 * A 分，其中 A 是平衡括号字符串
 *
 * @示例
 * 示例 1：
 * 输入：s = "()"
 * 输出：1
 *
 * 示例 2：
 * 输入：s = "(())"
 * 输出：2
 *
 * 示例 3：
 * 输入：s = "()()"
 * 输出：2
 *
 * 示例 4：
 * 输入：s = "(()(()))"
 * 输出：6
 *
 * @解题思路
 * 1. 深度计数法：
 *    - 核心原理：每个最内层 "()" 的贡献由其嵌套深度决定，深度为 d 的 "()" 贡献 2^d 分
 *    - 维护变量 depth 表示当前嵌套深度
 *    - 遇到 '(' 时深度加一
 *    - 遇到 ')' 时深度减一；若前一个字符是 '('（即刚好遇到一对 "()"），
 *      则向结果累加 1 << depth（注意此时 depth 已减一，对应外层深度）
 *    - 例如 "(()(()))"：两对内层 "()" 深度分别为 2 和 2，得 4 + 2 = 6
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n)，其中 n 是字符串长度
 *    - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    int scoreOfParentheses(string s) {
        int ret = 0;

        if (s.empty() || s.size() % 2 != 0) {
            return ret;
        }

        int depth = 0;
        for (auto i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;
                if (s.at(i-1) == '(') {
                    ret += 1<<depth;
                }
            }
        }

        return ret;
    }
};

TEST(Daily, 856) {
    Solution s;
    auto ss = "(()(()))";
    auto ret = s.scoreOfParentheses(ss);
    EXPECT_EQ(ret, 6);
}
