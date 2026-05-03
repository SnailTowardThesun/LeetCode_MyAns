//
// 796. 旋转字符串
// https://leetcode.cn/problems/rotate-string/
//
// 给定两个字符串 s 和 goal，如果 s 可以通过若干次字符移位得到 goal，返回 true。
// 字符移位定义：将字符串的第一个字符移动到末尾。
//
// 示例 1：
// 输入：s = "abcde", goal = "cdeab"
// 输出：true
// 解释：
// "abcde" 经过一次移位变为 "bcdea"
// "bcdea" 经过一次移位变为 "cdeab"
// 共移位 2 次得到 "cdeab"
//
// 示例 2：
// 输入：s = "abcde", goal = "abced"
// 输出：false
// 解释：无论移位多少次都无法得到 "abced"
//
// 解题思路：
// 1. 如果 s 和 goal 长度不同，直接返回 false
// 2. 将 s 与自身拼接，s + s 包含 s 所有可能的旋转结果
// 3. 检查 goal 是否为 s + s 的子串
//
// 时间复杂度：O(n)，空间复杂度：O(n)
//

#include <gtest/gtest.h>
using namespace std;

class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.length() != goal.length()) {
            return false;
        }

        string combined = s + s;
        return combined.find(goal) != string::npos;
    }
};

TEST(Daily, 796) {
    Solution sl;
    auto s = "abcde", goal = "cdeab";
    EXPECT_TRUE(sl.rotateString(s, goal));
}
