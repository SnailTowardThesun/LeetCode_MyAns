//
// Created by hankun on 2026/10/1.
//

/**
 * @file top150_242.cpp
 * @brief LeetCode 242. 有效的字母异位词
 *
 * @题目描述
 * 给定两个字符串 s 和 t，编写一个函数来判断 t 是否是 s 的字母异位词。
 * 字母异位词是通过重新排列源单词的所有字母得到的新单词。
 * 进阶：如果输入字符串包含 Unicode 字符怎么办？
 *
 * @示例
 * 示例 1：
 * 输入：s = "anagram", t = "nagaram"
 * 输出：true
 *
 * 示例 2：
 * 输入：s = "rat", t = "car"
 * 输出：false
 *
 * @解题思路
 * 1. 排序比较法：
 *    - 若两串相等，直接返回 true（相同的串互为异位词）
 *    - 长度不等则不可能是异位词，返回 false
 *    - 将 s 和 t 分别排序，逐位比较；字母异位词排序后必然完全相同
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n log n)，n 是字符串长度，主要是排序开销
 *    - 空间复杂度: O(log n)，排序的栈空间（原地排序）
 */

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s == t) {
            return true;
        }

        if (s.length() != t.length()) {
            return false;
        }

        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        for (auto i = 0; i < s.length(); i++) {
            if (s.at(i) != t.at(i)) {
                return false;
            }
        }

        return true;
    }
};

TEST(top150, 242) {
    Solution solution;
    auto s = "anagram", t = "nagaram";
    auto ret = solution.isAnagram(s, t);
    EXPECT_TRUE(ret == true);
}
