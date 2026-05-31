//
// @题目描述: 给定字符串 s 和 t，判断 s 是否是 t 的子序列。
//            子序列是指通过删除一些（或不删除）字符而不改变剩余字符顺序得到的序列。
//
// @示例: 输入: s = "abc", t = "ahbgdc"
//        输出: true
//        解释: s可以通过从t中删除一些字符得到
//
// @解题思路: 使用双指针同步遍历s和t。
//            s_p指向s的当前字符，t_p指向t的当前字符。
//            如果两个指针指向的字符相同，则s_p右移。
//            无论是否匹配，t_p都右移。
//            最终如果s_p到达s末尾，说明s是t的子序列。
//            时间复杂度: O(n)，空间复杂度: O(1)
//
// Created by hankun on 5/31/26.
//

#include <gtest/gtest.h>
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        size_t s_p = 0;
        size_t t_p = 0;
        while (s_p < s.size() && t_p < t.size()) {
            if (s[s_p] == t[t_p]) {
                s_p++;
            }

            t_p++;
        }

        return s_p == s.size();
    }
};

TEST(top150, 392) {
    Solution s;
    auto e1 = "abc";
    auto t = "ahbgdc";
    auto ret = s.isSubsequence(e1, t);
    EXPECT_TRUE(ret);
}