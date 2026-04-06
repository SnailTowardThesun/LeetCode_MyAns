/**
 * @file top150_28.cpp
 * @brief LeetCode 28. 找出字符串中第一个匹配项的下标
 *
 * @题目描述
 * 给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。
 * 如果 needle 不是 haystack 的一部分，则返回  -1 。
 *
 * @示例
 * 示例 1：
 * 输入：haystack = "sadbutsad", needle = "sad"
 * 输出：0
 * 解释："sad" 在下标 0 和 6 处匹配。第一个匹配项的下标是 0 ，所以返回 0 。
 *
 * 示例 2：
 * 输入：haystack = "leetcode", needle = "leeto"
 * 输出：-1
 * 解释："leeto" 没有在 "leetcode" 中出现，所以返回 -1 。
 *
 * @解题思路
 * 1. 暴力解法：
 *    - 遍历 haystack 字符串，从每个位置开始尝试匹配 needle
 *    - 对于每个位置，检查后续字符是否与 needle 完全匹配
 *    - 时间复杂度 O(n*m)，其中 n 是 haystack 长度，m 是 needle 长度
 *
 * 2. KMP 算法（可选，更高效）：
 *    - 预处理 needle 字符串，构建部分匹配表
 *    - 利用部分匹配表进行高效匹配
 *    - 时间复杂度 O(n+m)
 *
 * @复杂度分析
 * - 时间复杂度: O(n*m)，暴力解法
 * - 空间复杂度: O(1)
 */
#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        auto ret = -1;

        int n = haystack.length();
        int m = needle.length();

        for (int i = 0; i < n - m + 1; i++) {
            if (haystack.at(i) == needle.at(0)) {
                auto is_equal = true;
                for (int j = 0; j < m; j++) {
                    if (haystack.at(i + j) != needle.at(j)) {
                        is_equal = false;
                        break;
                    }
                }

                if (is_equal) {
                    return i;
                }
            }
        }


        return ret;
    }
};

TEST(TOP150, 28) {
    auto haystack = "sadbutsad";
    auto needle = "sad";

    Solution s;
    auto ret = s.strStr(haystack, needle);
    EXPECT_EQ(ret, 0);
}