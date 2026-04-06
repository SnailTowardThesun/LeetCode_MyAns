/**
 * @file top150_no58_length_of_last_word.cpp
 * @brief LeetCode 58. 最后一个单词的长度
 *
 * @题目描述
 * 给你一个字符串 s，由若干单词组成，单词前后用一些空格字符隔开。返回字符串中
 * 最后一个单词的长度。单词是指仅由字母组成、不包含任何空格字符的最大子字符串。
 *
 * @示例
 * 示例 1：
 * 输入: s = "Hello World"
 * 输出: 5
 * 解释: 最后一个单词是 "World"，长度为 5。
 *
 * 示例 2：
 * 输入: s = "   fly me   to   the moon  "
 * 输出: 4
 * 解释: 最后一个单词是 "moon"，长度为 4。
 *
 * 示例 3：
 * 输入: s = "luffy is still joyboy"
 * 输出: 6
 * 解释: 最后一个单词是 "joyboy"，长度为 6。
 *
 * @解题思路
 * 1. 从后向前遍历：
 *    - 先跳过末尾的所有空格
 *    - 然后从末尾开始计数，直到遇到空格或到达字符串开头
 *    - 返回计数结果
 *
 * 2. 使用字符串分割：
 *    - 使用 stringstream 或手动分割字符串
 *    - 找到最后一个非空单词
 *    - 返回其长度
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，最坏情况下需要遍历整个字符串
 * - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(TOP150, No58_LengthOfLastWord) {
    class Solution {
    public:
        int length_of_last_word(string s) {
            int idx = s.size() - 1;
            while (s[idx] == ' ' && idx >= 0) {
                idx--;
            }

            auto end = idx;
            while (idx >= 0 && s[idx] != ' ') {
                idx--;
            }
            return end - idx;
        }
    };

    Solution solution;
    auto ret = solution.length_of_last_word("Hello World");
    EXPECT_EQ(ret, 5);
}
