//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 5.cpp
 * @brief LeetCode 5. 最长回文子串
 *
 * @题目描述
 * 给你一个字符串 s，找到 s 中最长的回文子串。
 * 假设 s 的最大长度为 1000。
 *
 * @示例
 * 示例 1：
 * 输入：s = "babad"
 * 输出："bab"
 * 解释："aba" 也是答案
 *
 * 示例 2：
 * 输入：s = "cbbd"
 * 输出："bb"
 *
 * @解题思路
 * 1. 中心扩展法：
 *    - 每个回文串都有一个中心
 *    - 从中心向两边扩展，找出最长的回文串
 *
 * 2. 算法步骤：
 *    - 遍历字符串的每个位置
 *    - 对每个位置，尝试扩展回文串
 *    - 记录最长的回文串
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n^2)
 *    - 空间复杂度: O(1)
 */

#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(Daily, 5) {
    class Solution {
    public:
        string longestPalindrome(string s) {
            if (s.empty()) return "";
            int start = 0, maxLen = 0;
            
            for (int i = 0; i < s.size(); i++) {
                // 奇数长度的回文串
                int len1 = expandAroundCenter(s, i, i);
                // 偶数长度的回文串
                int len2 = expandAroundCenter(s, i, i + 1);
                int len = max(len1, len2);
                if (len > maxLen) {
                    start = i - (len - 1) / 2;
                    maxLen = len;
                }
            }
            return s.substr(start, maxLen);
        }
        
        int expandAroundCenter(string s, int left, int right) {
            while (left >= 0 && right < s.size() && s[left] == s[right]) {
                left--;
                right++;
            }
            return right - left - 1;
        }
    };

    Solution s;
    
    // 测试用例 1
    EXPECT_TRUE(s.longestPalindrome("babad") == "bab" || s.longestPalindrome("babad") == "aba");
    
    // 测试用例 2
    EXPECT_EQ(s.longestPalindrome("cbbd"), "bb");
    
    // 测试用例 3
    EXPECT_EQ(s.longestPalindrome("a"), "a");
    
    // 测试用例 4
    EXPECT_EQ(s.longestPalindrome("ac"), "a");
}
