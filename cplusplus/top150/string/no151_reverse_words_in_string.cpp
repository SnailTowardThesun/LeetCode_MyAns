/**
 * @file no151_reverse_words_in_string.cpp
 * @brief LeetCode 151. 反转字符串中的单词
 *
 * @题目描述
 * 给你一个字符串 s，请你反转字符串中单词的顺序。单词是由非空格字符组成的字符串。
 * s 中使用至少一个空格将字符串中的单词分隔开。返回单词顺序颠倒且单词之间用单个空格
 * 连接的结果字符串。注意：输入字符串 s 中可能会存在前导空格、尾随空格或者单词间的
 * 多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。
 *
 * @示例
 * 示例 1：
 * 输入: s = "the sky is blue"
 * 输出: "blue is sky the"
 *
 * 示例 2：
 * 输入: s = "  hello world  "
 * 输出: "world hello"
 * 解释: 反转后的字符串中不能存在前导空格和尾随空格。
 *
 * 示例 3：
 * 输入: s = "a good   example"
 * 输出: "example good a"
 * 解释: 如果两个单词间有多余的空格，反转后的字符串需要将单词间的空格减少到仅有一个。
 *
 * @解题思路
 * 1. 分割 + 反转：
 *    - 先分割字符串，提取所有单词
 *    - 将单词顺序反转
 *    - 用单个空格连接
 *
 * 2. 原地反转（双指针）：
 *    - 先整体反转整个字符串
 *    - 再逐个反转每个单词
 *    - 最后去除多余空格
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，需要遍历字符串
 * - 空间复杂度: O(n)，需要存储分割后的单词
 */

#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

TEST(TOP150, No151_ReverseWords) {
    class Solution {
    public:
        string reverse_words(string s) {
            std::vector<std::string> words;
            int n = s.size();
            int i = 0;

            // 跳过前导空格
            while (i < n && s[i] == ' ') {
                i++;
            }

            // 提取单词
            while (i < n) {
                std::string word;
                while (i < n && s[i] != ' ') {
                    word += s[i];
                    i++;
                }
                words.push_back(word);

                // 跳过空格
                while (i < n && s[i] == ' ') {
                    i++;
                }
            }

            // 反转单词顺序
            std::string ret = "";
            for (int j = words.size() - 1; j >= 0; j--) {
                ret.append(words[j]);
                if (j > 0) {
                    ret.append(" ");
                }
            }

            return ret;
        }
    };

    Solution solution;
    auto ret = solution.reverse_words("the sky is blue");
    EXPECT_EQ(ret, "blue is sky the");
}
