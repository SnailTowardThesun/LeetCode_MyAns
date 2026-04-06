/**
 * @file top150_no12_integer_to_roman.cpp
 * @brief LeetCode 12. 整数转罗马数字
 *
 * @题目描述
 * 罗马数字包含以下七种字符：I，V，X，L，C，D 和 M。
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
 * 给定一个整数，将其转为罗马数字。
 *
 * @示例
 * 示例 1：
 * 输入: num = 3
 * 输出: "III"
 *
 * 示例 2：
 * 输入: num = 4
 * 输出: "IV"
 *
 * 示例 3：
 * 输入: num = 9
 * 输出: "IX"
 *
 * 示例 4：
 * 输入: num = 58
 * 输出: "LVIII"
 * 解释: L = 50, V = 5, III = 3.
 *
 * 示例 5：
 * 输入: num = 1994
 * 输出: "MCMXCIV"
 * 解释: M = 1000, CM = 900, XC = 90, IV = 4.
 *
 * @解题思路
 * 1. 贪心法（从大到小匹配）：
 *    - 预定义所有罗马数字符号（包括特殊组合如 IV, IX 等）
 *    - 从最大的数值开始，尽可能多地使用当前符号
 *    - 然后处理下一个较小的符号
 *    - 直到数值减为 0
 *
 * 2. 硬编码法：
 *    - 分别处理千位、百位、十位、个位
 *    - 每个位置有固定的表示方式
 *
 * @复杂度分析
 * - 时间复杂度: O(1)，因为罗马数字的位数有限（最多 15 位左右）
 * - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

TEST(TOP150, No12_IntToRoman) {
    class Solution {
    public:
        string int_to_roman(int num) {
            std::string ret;

            std::vector<int> nums{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
            std::vector<std::string> signs{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

            for (int i = 0; i < nums.size(); i++) {
                while (num >= nums[i]) {
                    num -= nums[i];
                    ret += signs[i];
                }
            }

            return ret;
        }
    };

    Solution solution;
    auto ret = solution.int_to_roman(1994);
    EXPECT_EQ(ret, "MCMXCIV");
}
