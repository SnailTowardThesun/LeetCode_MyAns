//
// Created by 韩堃 on 2026/9/25.
//
// @题目描述:
// LeetCode 394. 字符串解码（Decode String）
// 给定一个经过编码的字符串，返回它解码后的字符串。
// 编码规则为：k[encoded_string]，表示其中方括号内部的 encoded_string
// 重复 k 次。注意 k 保证为正整数。
// 你可以认为输入字符串总是有效的，没有多余的空格，且方括号格式正确。
// 此外，原始数据中不包含任何数字，数字只用来表示重复次数 k，且
// 不存在如 2[4] 或 2[2[2]] 的非法嵌套。
//
// @示例:
// 示例 1：
// 输入：s = "3[a]2[bc]"
// 输出："aaabcbc"
// 示例 2：
// 输入：s = "3[a2[c]]"
// 输出："accaccacc"
// 解释：先解内层 2[c]="cc"，得 3[acc]，再展开为 "accaccacc"。
// 示例 3：
// 输入：s = "2[abc]3[cd]ef"
// 输出："abcabccdcdcdef"
// 示例 4：
// 输入：s = "abc3[cd]xyz"
// 输出："abccdcdcdxyz"
//
// @解题思路:
// 栈模拟。嵌套结构天然对应「先进后出」，用一个栈保存每层进入 '[' 前
// 的上下文：(已累积的字符串, 该层要重复的次数)。
// 遍历 s，按字符分类：
// 1. 数字字符：累乘解析出完整的十进制次数 times（k 可能 > 9，如 "12[a]"）；
// 2. 小写字母：直接追加到当前正在构造的字符串 ret；
// 3. 遇到 '['：把当前 ret 和 times 压栈，然后把 ret 清空、times 归零，
//    准备解析括号内层；
// 4. 遇到 ']'：弹出栈顶 (prev_str, repeat_times)，把 ret 重复
//    repeat_times 次后拼到 prev_str 后面，作为新的 ret。
// 遍历结束时，ret 即完整解码结果。
//
// 关键点：
// - 数字必须按位累加（times = times*10 + (c-'0')），而不能直接取字符面值，
//   否则多位数 k 会被截断成单次数；
// - 栈元素同时保存「外层已拼好的字符串」与「当前括号的重复次数」，
//   二者缺一不可，所以用 pair<string, int>；
// - 输入保证合法，无需处理 ']' 多于 '[' 等异常。
//
// 复杂度分析：
// - 时间复杂度：O(解码后字符串长度)，每个结果字符被拼接常数次。
// - 空间复杂度：O(n)，n 为输入长度，递归深度由括号嵌套决定。

#include <gtest/gtest.h>
#include <stack>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        // 栈元素：(进入当前 '[' 之前已累积的字符串, 当前括号的重复次数)
        stack<pair<string, int> > container;
        string ret;      // 当前正在构造的字符串
        int times = 0;   // 当前正在解析的重复次数
        for (auto c: s) {
            if (c >= '0' && c <= '9') {
                // 按位累加，支持多位数（如 "12[a]"）
                times = times * 10 + c - '0';
            } else if (c >= 'a' && c <= 'z') {
                ret += c;
            } else if (c == '[') {
                // 保存当前上下文，进入括号内层
                container.emplace(std::move(ret), times);
                times = 0;
                ret = "";
            } else if (c == ']') {
                // 弹出外层上下文，把内层字符串重复 repeat 次拼到外层后面
                auto tmp_ret = container.top().first;
                auto tmp_times = container.top().second;

                container.pop();

                for (auto i = 0; i < tmp_times; i++) {
                    tmp_ret += ret;
                }

                ret = tmp_ret;
            }
        }

        return ret;
    }
};

TEST(Daily, 394) {
    Solution s;
    auto st = "3[a]2[bc]";
    auto ret = s.decodeString(st);
    EXPECT_EQ(ret, "aaabcbc");

    // 嵌套括号：3[a2[c]] -> 3[acc] -> accaccacc
    EXPECT_EQ(s.decodeString("3[a2[c]]"), "accaccacc");

    // 多个并列括号 + 普通字符
    EXPECT_EQ(s.decodeString("2[abc]3[cd]ef"), "abcabccdcdcdef");

    // 普通字符穿插括号
    EXPECT_EQ(s.decodeString("abc3[cd]xyz"), "abccdcdcdxyz");

    // 多位数次数：10[z]
    EXPECT_EQ(s.decodeString("10[z]"), "zzzzzzzzzz");
}
