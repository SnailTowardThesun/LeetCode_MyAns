//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 3.cpp
 * @brief LeetCode 3. 无重复字符的最长子串
 *
 * @题目描述
 * 给定一个字符串 s，请你找出其中不含有重复字符的最长子串的长度。
 *
 * @示例
 * 示例 1：
 * 输入：s = "abcabcbb"
 * 输出：3
 * 解释：因为无重复字符的最长子串是 "abc"，长度为 3
 *
 * 示例 2：
 * 输入：s = "bbbbb"
 * 输出：1
 * 解释：因为无重复字符的最长子串是 "b"，长度为 1
 *
 * 示例 3：
 * 输入：s = "pwwkew"
 * 输出：3
 * 解释：因为无重复字符的最长子串是 "wke"，长度为 3
 *
 * @解题思路
 * 1. 滑动窗口法：
 *    - 使用两个指针维护一个窗口
 *    - 右指针扩展窗口，左指针收缩窗口
 *    - 使用数组记录每个字符最后出现的位置
 *
 * 2. 算法步骤：
 *    - 初始化一个数组 locs[256] 记录每个字符最后出现的位置
 *    - idx 记录窗口左边界的前一格，result 记录最大窗口长度
 *    - 遍历字符串，更新最大长度
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(1)，因为只需要 256 个位置的数组
 */

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <string>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 方法产生 ODR 冲突
namespace {
class Solution {
   public:
    int lengthOfLongestSubstring(const string& s) {
        int result = 0;
        array<int, 256> locs;
        locs.fill(-1);
        int idx = -1;
        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            auto ch = static_cast<unsigned char>(s[i]);
            idx = max(idx, locs[ch]);
            result = max(result, i - idx);
            locs[ch] = i;
        }
        return result;
    }
};
}  // namespace

TEST(Daily, 3) {
    Solution s;

    // 测试用例 1
    EXPECT_EQ(s.lengthOfLongestSubstring("abcabcbb"), 3);

    // 测试用例 2
    EXPECT_EQ(s.lengthOfLongestSubstring("bbbbb"), 1);

    // 测试用例 3
    EXPECT_EQ(s.lengthOfLongestSubstring("pwwkew"), 3);

    // 测试用例 4
    EXPECT_EQ(s.lengthOfLongestSubstring(""), 0);

    // 测试用例 5
    EXPECT_EQ(s.lengthOfLongestSubstring("a"), 1);
    EXPECT_EQ(s.lengthOfLongestSubstring("abba"), 2);
    EXPECT_EQ(s.lengthOfLongestSubstring("tmmzuxt"), 5);
    EXPECT_EQ(s.lengthOfLongestSubstring("a 1!a"), 4);
    // 用无符号字节作下标，避免 char 为负时越界。
    string bytes = {static_cast<char>(0xFF), 'a', static_cast<char>(0xFF)};
    EXPECT_EQ(s.lengthOfLongestSubstring(bytes), 2);
}
