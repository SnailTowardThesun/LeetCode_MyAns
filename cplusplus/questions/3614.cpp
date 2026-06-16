//
// Created by hankun on 6/17/26.
//

/**
 * @file 3614.cpp
 * @brief LeetCode 3614. Process String with Special Operations II（用特殊操作处理字符串 II）
 *
 * @题目描述
 * 给定一个只包含小写字母和三个特殊字符 `*`、`#`、`%` 的字符串 s，以及一个整数 k。
 * 从左到右依次处理每个字符：
 * - 小写字母：拼接到结果末尾
 * - `*`：删除结果字符串的最后一个字符（若结果非空则执行）
 * - `#`：将当前结果字符串复制一份追加到末尾（翻倍）
 * - `%`：将当前结果字符串原地反转
 * 返回处理后的最终字符串中第 k 个字符（0-indexed）。若 k >= 最终长度，返回 '.'。
 *
 * @示例
 * 示例 1：
 * 输入: s = "a#b%*", k = 1
 * 输出: 'a'
 * 解释: a→"a", #→"aa", b→"aab", %→"baa", *→"ba", ret[1]='a'
 *
 * 示例 2：
 * 输入: s = "cd%#*#", k = 3
 * 输出: 'd'
 * 解释: c→"c", d→"cd", %→"dc", #→"dcdc", *→"dcd", #→"dcddcd", ret[3]='d'
 *
 * 示例 3：
 * 输入: s = "z*#", k = 0
 * 输出: '.'
 * 解释: z→"z", *→"", #→"", 长度为0，k=0越界
 *
 * @解题思路
 * 核心难点：`#` 操作 `ret += ret` 会使字符串指数级增长（每次翻倍），直接模拟会导致 MLE。
 * 例如 60 个 `#` 操作会使长度达到 2^60，远超内存限制。
 *
 * 解决方案：**逆向回溯算法**，避免构建完整字符串。
 * 1. 正向扫描只记录每步后的字符串长度（用 long long），不存储字符串内容
 * 2. 若 k >= 最终长度，直接返回 '.'
 * 3. 从 s 末尾向前逆向回溯，维护 curK 和 len：
 *    - 小写字母 c：若 curK == len-1 则返回 c；否则 len--
 *    - `*`：len++（恢复被删除的字符）
 *    - `#`：len /= 2；若 curK >= len 则 curK -= len（映射回前半部分）
 *    - `%`：curK = len - 1 - curK（反转位置映射）
 *
 * 时间复杂度 O(n)，空间复杂度 O(1)（仅用几个变量）。
 */

#include <gtest/gtest.h>

#include <string>

using namespace std;

class Solution {
   public:
    char processStr(string s, long long k) {
        long long len = 0;
        for (char c : s) {
            if (c >= 'a' && c <= 'z') {
                len++;
            } else if (c == '*' && len > 0) {
                len--;
            } else if (c == '#') {
                len *= 2;
            }
        }
        if (k >= len) {
            return '.';
        }

        long long curK = k;
        for (int i = (int)s.size() - 1; i >= 0; --i) {
            char c = s[i];
            if (c >= 'a' && c <= 'z') {
                if (curK == len - 1) {
                    return c;
                }
                len--;
            } else if (c == '*') {
                len++;
            } else if (c == '#') {
                len /= 2;
                if (curK >= len) {
                    curK -= len;
                }
            } else if (c == '%') {
                curK = len - 1 - curK;
            }
        }
        return '.';
    }
};

TEST(Daily, 3614) {
    Solution sol;
    EXPECT_EQ(sol.processStr("a#b%*", 1), 'a');
    EXPECT_EQ(sol.processStr("cd%#*#", 3), 'd');
    EXPECT_EQ(sol.processStr("z*#", 0), '.');
    EXPECT_EQ(sol.processStr("", 0), '.');
    EXPECT_EQ(sol.processStr("a", 5), '.');
    EXPECT_EQ(sol.processStr("ab%", 0), 'b');
}
