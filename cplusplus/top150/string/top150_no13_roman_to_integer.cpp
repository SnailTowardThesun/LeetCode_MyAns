/**
 * @file top150_no13_roman_to_integer.cpp
 * @brief LeetCode 13. 罗马数字转整数
 *
 * @题目描述
 * 罗马数字包含以下七种字符: I，V，X，L，C，D 和 M。
 * 字符          数值
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 * 例如，罗马数字 2 写做 II，即为两个并列的 1。12 写做 XII，即为 X + II。
 * 27 写做 XXVII, 即为 XX + V + II。
 * 通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，
 * 而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。
 * 同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
 * - I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
 * - X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
 * - C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
 * 给定一个罗马数字，将其转换成整数。
 *
 * @示例
 * 示例 1：
 * 输入: s = "III"
 * 输出: 3
 *
 * 示例 2：
 * 输入: s = "IV"
 * 输出: 4
 *
 * 示例 3：
 * 输入: s = "IX"
 * 输出: 9
 *
 * 示例 4：
 * 输入: s = "LVIII"
 * 输出: 58
 * 解释: L = 50, V = 5, III = 3.
 *
 * 示例 5：
 * 输入: s = "MCMXCIV"
 * 输出: 1994
 * 解释: M = 1000, CM = 900, XC = 90, IV = 4.
 *
 * @解题思路
 * 1. 从左到右遍历：
 *    - 如果当前字符代表的值小于下一个字符的值，则减去当前值（如 IV = 5 - 1 = 4）
 *    - 否则加上当前值
 *    - 最后一个字符直接加上其值
 *
 * 2. 直接映射法：
 *    - 使用 switch 或哈希表映射每个字符到数值
 *    - 处理特殊情况（如 IV, IX 等）
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，需要遍历字符串一次
 * - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(TOP150, No13_RomanToInt) {
    class Solution {
    public:
        int roman_to_int(string s) {
            auto ret = 0;

            for (auto i = 0; i < s.size();) {
                if (s[i] == 'M') {
                    ret += 1000;
                    i++;
                } else if (s[i] == 'D') {
                    ret += 500;
                    i++;
                } else if (s[i] == 'C') {
                    if (i < s.size() - 1 && s[i + 1] == 'M') {
                        ret += 900;
                        i += 2;
                    } else if (i < s.size() - 1 && s[i + 1] == 'D') {
                        ret += 400;
                        i += 2;
                    } else {
                        ret += 100;
                        i++;
                    }
                } else if (s[i] == 'L') {
                    ret += 50;
                    i++;
                } else if (s[i] == 'X') {
                    if (i < s.size() - 1 && s[i + 1] == 'L') {
                        ret += 40;
                        i += 2;
                    } else if (i < s.size() - 1 && s[i + 1] == 'C') {
                        ret += 90;
                        i += 2;
                    } else {
                        ret += 10;
                        i++;
                    }
                } else if (s[i] == 'V') {
                    ret += 5;
                    i++;
                } else if (s[i] == 'I') {
                    if (i < s.size() - 1 && s[i + 1] == 'V') {
                        ret += 4;
                        i += 2;
                    } else if (i < s.size() - 1 && s[i + 1] == 'X') {
                        ret += 9;
                        i += 2;
                    } else {
                        ret += 1;
                        i++;
                    }
                }
            }
            return ret;
        }
    };

    Solution solution;
    auto s = "MCMXCIV";
    auto ret = solution.roman_to_int(s);
    EXPECT_EQ(ret, 1994);
}
