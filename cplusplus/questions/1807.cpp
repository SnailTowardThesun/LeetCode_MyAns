//
// Created by 韩堃 on 2026/9/26.
//
// @题目描述:
// LeetCode 1807. 替换字符串中的括号内容（Evaluate the Bracket Pairs of a String）
// 给你一个字符串 s，包含小写英文字母和括号。
// 每对括号内有一个或多个非空格字符，键名可由小写英文字母和数字组成。
// 给你一个二维字符串数组 knowledge，表示对括号内容的知识替换规则，
// 其中 knowledge[i] = [key_i, value_i] 表示如果括号中的字符串等于 key_i，
// 则替换为对应的 value_i；否则替换为单个字符 '?'。
// 所有括号按顺序出现（不会嵌套），且不存在空括号。
//
// @示例:
// 示例 1：
// 输入：s = "(name)is(age)yearsold"
//        knowledge = [["name","bob"],["age","two"]]
// 输出："bobistwoyearsold"
// 解释：括号内的 "name" 和 "age" 均有对应替换值。
//
// 示例 2：
// 输入：s = "hi(name)"
//        knowledge = [["a","b"]]
// 输出："hi?"
// 解释：括号内的 "name" 无对应替换，替换为 '?'。
//
// 示例 3：
// 输入：s = "(a)(a)(a)aaa"
//        knowledge = [["a","yes"]]
// 输出："yesyesyesaaa"
// 解释：每个括号独立替换。
//
// @解题思路:
// 1. 预处理：将 knowledge 哈希化为 unordered_map<string, string>，
//    保证 O(1) 查询替换值或判定不存在。
// 2. 双指针扫描原串 s：
//    - 普通字符：直接追加到结果 ret，指针 i 右移；
//    - 遇到 '('：j 从 i+1 向后查找第一个 ')'，提取中间子串作为 key，
//      i 跳到 ')' 的下一个位置，然后在 map 中查找并追加替换值或 '?'。
// 3. 关键点：括号不嵌套，所以每遇到 '(' 直接找下一个 ')' 即可，
//    不需要栈；提取 key 时逐个字符追加（因为 key 很短，用 string 即可）。
//
// 复杂度分析：
// - 时间复杂度：O(n + m)，n 为 s 长度，m 为 knowledge 总字符数。
// - 空间复杂度：O(m + k)，哈希表和结果字符串。

#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    string evaluate(string s, vector<vector<string> > &knowledge) {
        // 建立 key -> value 的哈希映射
        unordered_map<string, string> lookup;
        for (auto i: knowledge) {
            lookup[i[0]] = i[1];
        }

        string ret = "";
        for (auto i = 0; i < s.size();) {
            // 普通字符直接输出
            if (s.at(i) != '(') {
                ret += s.at(i);
                i++;
                continue;
            }

            // 遇到 '('，提取括号内的 key
            string tmp = "";
            int j = i + 1;
            for (; j < s.size(); j++) {
                if (s.at(j) == ')') {
                    break;
                }
                tmp += s.at(j);
            }
            i = j + 1;  // 跳到 ')' 之后
            // 查表替换，不存在则替换为 '?'
            if (lookup.count(tmp) > 0) {
                ret += lookup[tmp];
            } else {
                ret += '?';
            }
        }

        return ret;
    }
};

TEST(Daily, 1807) {
    Solution s;
    // 示例 1
    auto ss = "(name)is(age)yearsold";
    vector<vector<string> > knowledge = {{"name", "bob"}, {"age", "two"}};
    EXPECT_EQ(s.evaluate(ss, knowledge), "bobistwoyearsold");

    // 示例 2：key 不存在
    vector<vector<string> > knowledge2 = {{"a", "b"}};
    EXPECT_EQ(s.evaluate("hi(name)", knowledge2), "hi?");

    // 示例 3：多个连续括号
    vector<vector<string> > knowledge3 = {{"a", "yes"}};
    EXPECT_EQ(s.evaluate("(a)(a)(a)aaa", knowledge3), "yesyesyesaaa");

    // 边界：无括号，直接返回原串
    vector<vector<string> > empty_knowledge;
    EXPECT_EQ(s.evaluate("hello", empty_knowledge), "hello");

    // 边界：整个串都是括号
    vector<vector<string> > knowledge4 = {{"key", "value"}};
    EXPECT_EQ(s.evaluate("(key)", knowledge4), "value");
}
