//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 8.cpp
 * @brief LeetCode 8. 字符串转换整数 (atoi)
 *
 * @题目描述
 * 实现一个 myAtoi(string s) 函数，将字符串转换为整数。
 * 函数首先丢弃尽可能多的空白字符，直到找到第一个非空白字符。
 * 然后，从该字符开始，取一个可选的初始正负号，后跟尽可能多的数字，并将它们解释为整数值。
 * 如果数组中的第一个非空白字符不是有效整数，或者没有这样的序列存在，则不执行转换并返回 0。
 *
 * @示例
 * 示例 1：
 * 输入：s = "42"
 * 输出：42
 *
 * 示例 2：
 * 输入：s = "   -42"
 * 输出：-42
 *
 * 示例 3：
 * 输入：s = "4193 with words"
 * 输出：4193
 *
 * @解题思路
 * 1. 有限状态机：
 *    - 跳过开头的空白字符
 *    - 处理可选的符号
 *    - 读取数字字符直到遇到非数字字符
 *    - 处理溢出情况
 *
 * 2. 算法步骤：
 *    - 跳过开头的空白字符
 *    - 处理正负号
 *    - 读取连续的数字字符
 *    - 检查溢出并返回结果
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(1)
 */

#include <gtest/gtest.h>
#include <climits>

using namespace std;

int myAtoi(char *str) {
    if (str == NULL) return 0;
    bool isPositive = true;
    long long result = 0;
    const char* ss = (const char*)str;
    while (*ss == ' ') ss++;

    if (*ss == '+') {
        isPositive = true;
        ss++;
    }
    else if (*ss == '-') {
        isPositive = false;
        ss++;
    }
    while (*ss >= '0' && *ss <= '9') {
        result = result * 10 + (*ss - '0');
        if (result > INT_MAX) return isPositive ? INT_MAX : INT_MIN;
        ss++;
    }
    return isPositive ? result : 0 - result;
}

TEST(Daily, 8) {
    // 测试用例 1
    EXPECT_EQ(myAtoi("42"), 42);
    
    // 测试用例 2
    EXPECT_EQ(myAtoi("   -42"), -42);
    
    // 测试用例 3
    EXPECT_EQ(myAtoi("4193 with words"), 4193);
    
    // 测试用例 4
    EXPECT_EQ(myAtoi("words and 987"), 0);
    
    // 测试用例 5
    EXPECT_EQ(myAtoi("-91283472332"), -2147483648);
}
