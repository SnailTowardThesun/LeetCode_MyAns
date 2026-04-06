/**
 * @file top150_68.cpp
 * @brief LeetCode 68. 文本左右对齐
 *
 * @题目描述
 * 给定一个单词数组 words 和一个长度 maxWidth，重新排版单词，使其成为每行恰好有 maxWidth 个字符，且左右两端对齐的文本。
 * 你应该使用“贪心算法”来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 ' ' 填充，使得每行恰好有
 * maxWidth 个字符。
 * 要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。
 * 文本的最后一行应为左对齐，且单词之间不插入额外的空格。
 *
 * @示例
 * 示例 1：
 * 输入: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
 * 输出:
 * [
 *   "This    is    an",
 *   "example  of text",
 *   "justification.  "
 * ]
 *
 * 示例 2：
 * 输入: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
 * 输出:
 * [
 *   "What   must   be",
 *   "acknowledgment  ",
 *   "shall be        "
 * ]
 *
 * @解题思路
 * 1. 分组：将单词分组，每组单词的总长度加上单词间的空格数不超过maxWidth
 * 2. 处理每行：
 *    - 对于非最后一行：计算单词间的空格数，尽可能均匀分配，左侧空格数多于右侧
 *    - 对于最后一行：左对齐，单词间只有一个空格，末尾补全空格
 * 3. 特殊情况：当一行只有一个单词时，左对齐，右侧补全空格
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，其中n是单词总数，每个单词只处理一次
 * - 空间复杂度: O(n)，需要存储分组后的单词和结果
 */

#include <gtest/gtest.h>

#include <cmath>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<vector<string>> container;

        int total = 0;
        vector<string> temp;
        for (int i = 0; i < words.size(); i++) {
            auto w = words[i];
            if (total + w.length() + temp.size() > maxWidth) {
                container.push_back(temp);
                temp.clear();

                temp.push_back(w);
                total = w.length();
            } else {
                temp.push_back(w);
                total += w.length();
            }
        }

        if (temp.size() > 0) {
            container.push_back(temp);
        }

        vector<string> result;
        for (int i = 0; i < container.size(); i++) {
            string ret = "";
            int word_length = 0;

            auto s = container[i];
            int word_number = s.size();

            for (auto j : s) {
                word_length += j.size();
            }
            int blank_size = maxWidth - word_length;
            if (word_number == 1) {
                ret += s[0];
                ret = s[0] + string(blank_size, ' ');
            } else if (i == container.size() - 1) {
                for (int j = 0; j < word_number; j++) {
                    ret += s[j];
                    if (j < word_number - 1) ret += " ";  // 单词间仅一个空格
                }
                ret += string(maxWidth - ret.size(), ' ');  // 末尾补全
            } else {
                int spaces_between = word_number - 1;
                int avg_space = blank_size / spaces_between;
                int extra_space = blank_size % spaces_between;

                for (int j = 0; j < word_number; j++) {
                    ret += s[j];
                    if (j < spaces_between) {
                        // 每一个间隙先给平均值，如果还有余数(extra_space)，就多给1个
                        int current_blank = avg_space + (j < extra_space ? 1 : 0);
                        ret += string(current_blank, ' ');
                    }
                }
            }

            result.push_back(ret);
        }

        return result;
    }
};

TEST(TOP150, 68) {
    Solution s;
    auto words = vector<string>{"This", "is", "an", "example", "of", "text", "justification."};
    auto max_width = 16;
    auto ret = s.fullJustify(words, max_width);
    EXPECT_EQ(ret.size(), 3);
}
