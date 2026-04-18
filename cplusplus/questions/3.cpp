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
 *    - 使用两个指针 idx 和 max
 *    - 遍历字符串，更新最大长度
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(1)，因为只需要 256 个位置的数组
 */

#include <gtest/gtest.h>
#include <string>
#include <cstring>

using namespace std;

TEST(Daily, 3) {
    class Solution {
    public:
        int lengthOfLongestSubstring(string s) {
            int result = 0;
            int locs[256];
            memset(locs, -1, sizeof(locs));
            int idx = -1, max = 0;
            for (int i = 0; i < s.size(); i++) {
                if (locs[s[i]] > idx)
                    idx = locs[s[i]];
                if (i - idx > max)
                    max = i - idx;
                locs[s[i]] = i;
            }
            return max;
        }
    };

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
}
