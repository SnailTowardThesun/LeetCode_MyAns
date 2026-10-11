//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 68.cpp
 * @brief LeetCode 68. 文本左右对齐
 *
 * @题目描述
 * 给定一个单词数组和一个长度 L，将单词左对齐并填充空格，使得每行恰好有 L 个字符。
 * 文本应该左对齐，组成清晰的段落。
 * 行尾需要填充空格使得每行恰好有 L 个字符。
 *
 * @示例
 * 示例：
 * words: ["This", "is", "an", "example", "of", "text", "justification."]
 * L: 16
 * 返回：
 * [
 *    "This    is    an",
 *    "example  of text",
 *    "justification.  "
 * ]
 *
 * @解题思路
 * 1. 贪心法：
 *    - 每行尽可能多地放置单词
 *    - 根据每行单词的数量计算需要分配的空格
 *
 * 2. 算法步骤：
 *    - 遍历单词，将尽可能多的单词放入一行
 *    - 计算每行需要填充的空格数
 *    - 将空格均匀分布到单词之间
 *    - 最后一行左对齐
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(maxWidth)，单行缓冲
 */

#include <gtest/gtest.h>

#include <string>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 方法产生 ODR 冲突
namespace {
class Solution {
   public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int n = words.size();
        int left = 0;

        while (left < n) {
            // 确定当前行能容纳的单词范围 [left, right)
            int len = words[left].size();
            int right = left + 1;
            while (right < n && len + 1 + words[right].size() <= maxWidth) {
                len += 1 + words[right].size();
                right++;
            }

            int wordCount = right - left;
            int gaps = wordCount - 1;
            string line;

            // 最后一行或只有一个单词：左对齐，空格补尾部
            if (right == n || gaps == 0) {
                for (int i = left; i < right; i++) {
                    if (i > left) line += " ";
                    line += words[i];
                }
                line += string(maxWidth - line.size(), ' ');
            } else {
                // 普通行：空格均匀分配，余数从左到右逐个多分一个
                int letters = 0;
                for (int i = left; i < right; i++) letters += words[i].size();
                int spaces = maxWidth - letters;
                int base = spaces / gaps;
                int extra = spaces % gaps;

                for (int i = left; i < right; i++) {
                    line += words[i];
                    if (i < right - 1) {
                        line += string(base + (i - left < extra ? 1 : 0), ' ');
                    }
                }
            }

            result.push_back(line);
            left = right;
        }
        return result;
    }
};
}  // namespace

TEST(Daily, 68) {
    Solution s;

    // 测试用例 1：普通行均匀分配 + 余数左置
    vector<string> words1 = {"This", "is", "an", "example", "of", "text", "justification."};
    auto ret1 = s.fullJustify(words1, 16);
    EXPECT_EQ(ret1.size(), 3);
    EXPECT_EQ(ret1[0], "This    is    an");
    EXPECT_EQ(ret1[1], "example  of text");
    EXPECT_EQ(ret1[2], "justification.  ");
    for (const auto& line : ret1) {
        EXPECT_EQ(line.size(), 16);
    }

    // 测试用例 2：单个单词的行左对齐，空格补尾部
    vector<string> words2 = {"Listen", "to", "many,", "speak", "to", "a", "few."};
    auto ret2 = s.fullJustify(words2, 6);
    EXPECT_EQ(ret2.size(), 6);
    EXPECT_EQ(ret2[0], "Listen");
    EXPECT_EQ(ret2[1], "to    ");
    EXPECT_EQ(ret2[2], "many, ");
    EXPECT_EQ(ret2[3], "speak ");
    EXPECT_EQ(ret2[4], "to   a");
    EXPECT_EQ(ret2[5], "few.  ");
    for (const auto& line : ret2) {
        EXPECT_EQ(line.size(), 6);
    }

    // 测试用例 3：普通行 + 最后一行左对齐
    vector<string> words3 = {"Science", "is", "what",    "we", "understand", "well",
                             "enough",  "to", "explain", "to", "a",          "computer."};
    auto ret3 = s.fullJustify(words3, 20);
    EXPECT_EQ(ret3.size(), 4);
    EXPECT_EQ(ret3[0], "Science  is  what we");
    EXPECT_EQ(ret3[1], "understand      well");
    EXPECT_EQ(ret3[2], "enough to explain to");
    EXPECT_EQ(ret3[3], "a computer.         ");  // 最后一行左对齐，补 9 个尾部空格
}
