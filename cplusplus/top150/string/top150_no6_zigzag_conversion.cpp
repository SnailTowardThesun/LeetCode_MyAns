/**
 * @file top150_no6_zigzag_conversion.cpp
 * @brief LeetCode 6. Z 字形变换
 *
 * @题目描述
 * 将一个给定字符串 s 根据给定的行数 numRows，以从上往下、从左到右进行 Z 字形排列。
 * 比如输入字符串为 "PAYPALISHIRING"，行数为 3 时，排列如下：
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。
 * 请你实现这个将字符串进行指定行数变换的函数。
 *
 * @示例
 * 示例 1：
 * 输入: s = "PAYPALISHIRING", numRows = 3
 * 输出: "PAHNAPLSIIGYIR"
 *
 * 示例 2：
 * 输入: s = "PAYPALISHIRING", numRows = 4
 * 输出: "PINALSIGYAHRPI"
 * 解释:
 * P     I    N
 * A   L S  I G
 * Y A   H R
 * P     I
 *
 * 示例 3：
 * 输入: s = "A", numRows = 1
 * 输出: "A"
 *
 * @解题思路
 * 1. 按行排序法：
 *    - 使用 numRows 个字符串（或 StringBuilder）存储每行的字符
 *    - 遍历原字符串，按 Z 字形顺序将字符放入对应行
 *    - 维护当前行号和方向（向上或向下）
 *    - 到达第一行或最后一行时改变方向
 *    - 最后将所有行的字符串连接起来
 *
 * 2. 数学规律法：
 *    - 找出每个字符在 Z 字形中的位置规律
 *    - 直接计算每个字符应该在哪一行
 *    - 周期为 2*numRows-2（第一行和最后一行之间的往返）
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，需要遍历字符串一次
 * - 空间复杂度: O(n)，需要存储所有字符
 */

#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

TEST(TOP150, No6_ZigzagConversion) {
    class Solution {
    public:
        string convert(string s, int num_rows) {
            if (num_rows == 1 || num_rows >= s.size()) {
                return s;
            }

            std::vector<std::string> rows(num_rows);
            for (auto& row : rows) {
                row.reserve(s.size() / num_rows + 1);
            }

            int cur_row = 0;
            bool going_down = false;

            for (char c : s) {
                rows[cur_row] += c;
                if (cur_row == 0 || cur_row == num_rows - 1) {
                    going_down = !going_down;
                }
                cur_row += going_down ? 1 : -1;
            }

            std::string ret;
            ret.reserve(s.size());
            for (const auto& row : rows) {
                ret += row;
            }

            return ret;
        }
    };

    Solution s;
    auto example = "PAYPALISHIRING";
    auto ret = s.convert(example, 3);

    EXPECT_EQ(ret, "PAHNAPLSIIGYIR");

    ret = s.convert(example, 4);
    EXPECT_EQ(ret, "PINALSIGYAHRPI");

    EXPECT_EQ(s.convert("A", 1), "A");
    EXPECT_EQ(s.convert("AB", 1), "AB");
}
