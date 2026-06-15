/**
 * @file 3838.cpp
 * @brief LeetCode 3838. Map Word Weights（映射单词权重）
 *
 * @题目描述
 * 给定一个字符串数组 words 和一个长度为 26 的整数数组 weights，其中 weights[i] 表示字母 'a' + i 的权重。
 * 对于每个单词，计算其所有字符权重之和，然后将结果对 26 取模得到一个值 k，将其映射为字母 'z' - k。
 * 返回一个字符串，其中每个字符对应 words 中每个单词的映射结果。
 *
 * @示例
 * 示例 1：
 * 输入: words = ["abcd", "def", "xyz"], weights = [5, 3, 12, 14, 1, 2, 3, 2, 10, 6, 6, 9, 7, 8, 7, 10, 8, 9, 6, 9, 9, 8, 3, 7, 7, 2]
 * 输出: "rij"
 * 解释:
 * - "abcd": a(5) + b(3) + c(12) + d(14) = 34, 34 % 26 = 8, 'z' - 8 = 'r'
 * - "def": d(14) + e(1) + f(2) = 17, 17 % 26 = 17, 'z' - 17 = 'i'
 * - "xyz": x(8) + y(7) + z(2) = 17, 17 % 26 = 17, 'z' - 17 = 'j'
 *
 * @解题思路
 * 1. 遍历 words 中的每个单词
 * 2. 对于每个单词，累加其所有字符对应的权重值
 * 3. 将权重和对 26 取模得到 k
 * 4. 将 k 映射为字母 'z' - k
 * 5. 将所有映射结果拼接成最终字符串返回
 *
 * @复杂度分析
 * - 时间复杂度: O(N * L)，其中 N 是单词数量，L 是单词的平均长度
 * - 空间复杂度: O(N)，用于存储结果字符串
 */

#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string map_word_weights(vector<string>& words, vector<int>& weights) {
        string ret;
        for (const auto& word : words) {
            int weight_sum = 0;
            for (char c : word) {
                weight_sum += weights[c - 'a'];
            }
            weight_sum %= 26;
            ret += 'z' - weight_sum;
        }
        return ret;
    }
};

TEST(Daily, 3838) {
    Solution s;
    vector<string> words{"abcd", "def", "xyz"};
    vector<int> weights{5, 3, 12, 14, 1, 2, 3, 2, 10, 6, 6, 9, 7, 8, 7, 10, 8, 9, 6, 9, 9, 8, 3, 7, 7, 2};
    EXPECT_EQ(s.map_word_weights(words, weights), "rij");
}
