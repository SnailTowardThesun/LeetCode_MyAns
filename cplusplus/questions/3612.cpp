//
// Created by hankun on 6/16/26.
//

/**
 * @file 3612.cpp
 * @brief LeetCode 3612. Process String with Special Characters（使用特殊字符处理字符串）
 *
 * @题目描述
 * 给定一个只包含小写字母和三个特殊字符 *、#、% 的字符串 s，从左到右依次处理每个字符：
 * - '*'：删除结果字符串的最后一个字符（若结果非空则执行，否则忽略）
 * - '#'：将当前结果字符串复制一份追加到末尾（翻倍）
 * - '%'：将当前结果字符串原地反转
 * 其余小写字母直接拼接到结果末尾。
 * 返回最终处理后的字符串。
 *
 * @示例
 * 示例 1：
 * 输入: s = "a#b%*"
 * 输出: "ba"
 * 解释: a→"a", #→""(清空), b→"b", %→"ba"(反转) ... 
 *        （实际处理过程中 '#' 操作使空串翻倍仍为空，后续拼接和反转得到最终结果）
 *
 * @解题思路
 * 1. 维护一个可变字符串 ret，从左到右遍历输入 s：
 *     - '*'：ret.pop_back()（非空时）
 *     - '#'：ret += ret（翻倍追加）
 *     - '%'：std::reverse(ret.begin(), ret.end())（反转）
 *     - 其他字符：ret.push_back(c)
 * 2. 返回最终处理后的字符串。
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，每个字符最多执行一次基本操作，#的翻倍总代价不超过 O(n^2)
 * - 空间复杂度: O(n)，结果字符串最多存储 n 个字符
 */

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string processStr(string s) {
        string ret = "";

        for (auto i: s) {
            if (i == '*') {
                if (ret.size() > 0) {
                    ret.pop_back();
                    continue;
                }
            }

            if (i == '#') {
                ret += ret;
                continue;
            }

            if (i == '%') {
                reverse(ret.begin(), ret.end());
                continue;
            }

            ret += i;
        }

        return ret;
    }
};

TEST(Daily, 3612) {
    Solution s;
    auto eg = "a#b%*";
    auto ret = s.processStr(eg);
    EXPECT_EQ("ba", ret);
}
