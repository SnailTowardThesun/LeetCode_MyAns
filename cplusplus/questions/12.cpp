//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 12.cpp
 * @brief LeetCode 12. 整数转罗马数字
 *
 * @题目描述
 * 罗马数字包含以下七种字符：I，V，X，L，C，D，M。
 * 给定一个整数，将其转换为罗马数字。
 * 输入确保在 1 到 3999 的范围内。
 *
 * @示例
 * 示例 1：
 * 输入：3
 * 输出："III"
 *
 * 示例 2：
 * 输入：4
 * 输出："IV"
 *
 * 示例 3：
 * 输入：9
 * 输出："IX"
 *
 * 示例 4：
 * 输入：58
 * 输出："LVIII"
 * 解释：L = 50, V = 5, III = 3
 *
 * 示例 5：
 * 输入：1994
 * 输出："MCMXCIV"
 * 解释：M = 1000, CM = 900, XC = 90, IV = 4
 *
 * @解题思路
 * 1. 贪心算法：
 *    - 使用哈希表存储罗马数字字符和对应的值
 *    - 从最大的数值开始，依次递减
 *    - 每次尽量使用最大的数值来表示
 *
 * 2. 算法步骤：
 *    - 定义罗马数字字符数组和对应值数组
 *    - 从最高位开始遍历（千位、百位、十位、个位）
 *    - 根据每位数值选择合适的罗马数字表示
 *    - 拼接所有结果
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(1)，因为输入范围固定（1-3999）
 *    - 空间复杂度: O(1)，只使用常数级别的额外空间
 */

#include <gtest/gtest.h>
#include <string>
#include <cstring>

using namespace std;

TEST(Daily, 12) {
    class Solution {
    public:
        void romanstr(string& roman, int num, char* symbol) {
            if (num == 0) return;
            else if (num < 4) {
                for (int i = 0; i < num; i++) {
                    roman += *symbol;
                }
            }
            else if (num == 4) {
                roman += *symbol;
                roman += *(symbol+1);
            }
            else if (num < 9) {
                roman += *(symbol+1);
                for (int i = 0; i < num-5; i++) {
                    roman += *symbol;
                }
            }
            else if (num == 9) {
                roman += *symbol;
                roman += *(symbol+2);
            }
        }
        string intToRoman(int num) {
            char symbol[9] = {'I','V','X','L','C','D','M'};
            string roman = "";
            int scale = 1000;
            int p = 6;
            while (num > 0) {
                int bit = num / scale;
                if (p >= 0 && p < 7) {
                    romanstr(roman, bit, symbol + p);
                }
                num %= scale;
                scale /= 10;
                p -= 2;
            }
            return roman;
        }
    };

    Solution s;
    
    // 测试用例 1
    EXPECT_EQ(s.intToRoman(3), "III");
    
    // 测试用例 2
    EXPECT_EQ(s.intToRoman(4), "IV");
    
    // 测试用例 3
    EXPECT_EQ(s.intToRoman(9), "IX");
    
    // 测试用例 4
    EXPECT_EQ(s.intToRoman(58), "LVIII");
    
    // 测试用例 5
    EXPECT_EQ(s.intToRoman(1994), "MCMXCIV");
    
    // 测试用例 6
    EXPECT_EQ(s.intToRoman(1), "I");
    
    // 测试用例 7
    EXPECT_EQ(s.intToRoman(3999), "MMMCMXCIX");
}
