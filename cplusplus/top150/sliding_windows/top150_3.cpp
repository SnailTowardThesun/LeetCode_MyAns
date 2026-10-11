//
// Created by 韩堃 on 2026/9/25.
//

/**
 * @file top150_3.cpp
 * @brief LeetCode 3. 无重复字符的最长子串
 *
 * @题目描述
 * 给定一个字符串 s，请你找出其中不含有重复字符的最长子串的长度。
 *
 * @示例
 * 示例 1：
 * 输入：s = "abcabcbb"
 * 输出：3
 * 解释：无重复字符的最长子串是 "abc"，长度为 3。
 *
 * 示例 2：
 * 输入：s = "bbbbb"
 * 输出：1
 * 解释：最长子串是 "b"，长度为 1。
 *
 * 示例 3：
 * 输入：s = "pwwkew"
 * 输出：3
 * 解释：最长子串是 "wke"，长度为 3。注意答案必须是子串，"pwke" 是子序列。
 *
 * @解题思路
 * 1. 枚举左端点 + 集合判重：
 *    - 对每个左端点 left，向右扫描并用 unordered_set 记录已见字符
 *    - 一旦遇到重复字符立即停止，当前窗口长度为 i - left
 *    - 取所有窗口长度的最大值，left 右移进入下一轮
 *    - 本实现左端点右移后重建集合，最坏 O(n^2)；
 *      标准滑动窗口（右指针不回退）可优化到 O(n)
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n^2)（最坏）
 *    - 空间复杂度: O(min(n, 字符集大小))
 */

#include <gtest/gtest.h>

#include <unordered_set>
using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() < 1) {
            return 0;
        }

        int n = s.size();
        int left = 0;
        int ret = INT_MIN;
        while (left < n) {
            unordered_set<char> lookup;
            int i = left;
            for (; i < n; i++) {
                if (lookup.find(s.at(i)) != lookup.end()) {
                    break;
                }

                lookup.insert(s.at(i));
            }

            ret = max(ret, i - left);
            left++;
        }

        return ret;
    }
};
}  // namespace

TEST(top150, 3) {
    Solution s;
    auto st = "1R1T7";
    auto ret = s.lengthOfLongestSubstring(st);
    EXPECT_EQ(ret, 4);
}
