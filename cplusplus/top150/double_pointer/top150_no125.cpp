//
// @题目描述: 给定一个字符串，判断它是否是回文串。
//            判断时只考虑字母和数字字符，忽略大小写和所有其他字符。
//
// @示例: 输入: "A man, a plan, a canal: Panama"
//        输出: true
//        解释: 忽略大小写和非字母数字字符后变为 "amanaplanacanalpanama"，是回文串
//
// @解题思路: 第一步预处理：遍历字符串，只保留字母和数字，并转为小写。
//            第二步：使用双指针从字符串两端向中间比较。
//            如果发现不匹配的字符，返回false；全部匹配则返回true。
//            时间复杂度: O(n)，空间复杂度: O(n) (用于存储预处理后的字符串)
//
// Created by hankun on 5/31/26.
//

#include <gtest/gtest.h>
#include <vector>
#include <cctype>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        string helper= "";
        for (auto i : s) {
            if (i >= 'a' && i <= 'z') {
                helper += i;
            } else if (i >= 'A' && i <= 'Z') {
                helper += tolower(i);
            } else if (i >= '0' && i <= '9') {
                helper += i;
            }
        }

        for (int i = 0, j = helper.size() - 1; i < j; i++, j--) {
            if (helper[i] != helper[j]) {
                return false;
            }
        }

        return true;
    }
};

TEST(top150, 125) {
    Solution s;
    auto  ret= s.isPalindrome("A man, a plan, a canal: Panama");
    EXPECT_TRUE(ret);
}