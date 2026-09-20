//
// Created by 韩堃 on 2026/9/20.
//
// @题目描述:
// LeetCode 3498. 字符串的反转度（Reverse Degree of a String）
// 给定一个只包含小写英文字母的字符串 s，定义字符 ch 的「反转字母值」为：
//   reverseValue(ch) = 'z' - ch + 1，即 a=26, b=25, ..., z=1，
// 也就是普通字母值（a=1..z=26）关于 27 的镜像。
// 字符串 s 的反转度定义为：对每个 1 起始下标 i，把 s[i] 的反转字母值
// 乘以其下标 i 后求和。
// 返回字符串 s 的反转度。
//
// @示例:
// 示例 1：
// 输入：s = "abc"
// 输出：148
// 解释：a(26)*1 + b(25)*2 + c(24)*3 = 26 + 50 + 72 = 148。
// 示例 2：
// 输入：s = "zaza"
// 输出：160
// 解释：z(1)*1 + a(26)*2 + z(1)*3 + a(26)*4 = 1 + 52 + 3 + 104 = 160。
//
// @解题思路:
// 直接模拟。一次遍历，对第 i（0 起始）个字符：
//   反转字母值 = 26 - (ch - 'a')；其位置乘数 = i + 1。
// 累乘后累加即可。
// 注意：反转字母值 = 26 - (ch - 'a')，不要误写成 27 - (ch - 'a')
// （后者会让 a=27、z=2，与题意不符）。
//
// 复杂度分析：
// - 时间复杂度：O(n)，n 为字符串长度。
// - 空间复杂度：O(1)，只使用常数额外空间。

#include <gtest/gtest.h>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int reverseDegree(string s) {
        int ret = 0;
        for (int i = 0; i < s.length(); i++) {
            // 反转字母值：a=26..z=1；位置乘数为 1 起始下标 i+1
            ret += (26 - (s.at(i) - 'a')) * (i+1);
        }

        return ret;
    }
};

TEST(Daily, 3498) {
   string s = "abc";
    auto ret = Solution().reverseDegree(s);
    EXPECT_EQ(ret, 148);

    // 交替字符：z(1)*1 + a(26)*2 + z(1)*3 + a(26)*4 = 160
    EXPECT_EQ(Solution().reverseDegree("zaza"), 160);

    // 边界用例：单个字符 z，反转值为 1，乘位置 1
    EXPECT_EQ(Solution().reverseDegree("z"), 1);

    // 边界用例：单个字符 a，反转值为 26，乘位置 1
    EXPECT_EQ(Solution().reverseDegree("a"), 26);
}
