//
// Created by 韩堃 on 2026/9/26.
//

// @题目描述:
// 给定字符串 s 和字符串数组 words。words 中所有字符串长度相同。
// s 中的串联子串是指一个包含 words 中所有字符串恰好一次（任意顺序）的子串，
// 中间不能有其他多余字符。返回所有这种子串在 s 中的起始下标（任意顺序）。
//
// @示例:
// 输入：s = "barfoothefoobarman", words = ["foo","bar"]
// 输出：[0,9]
// 解释：从下标 0 开始的 "barfoo"、下标 9 开始的 "foobar" 都是串联子串。
//
// @解题思路:
// 单词频率计数 + 枚举窗口起点。
// 1. 设每个单词长 ws，窗口总长 = words.size() * ws。
// 2. 用哈希表 lookup 记录 words 中每个单词的目标出现次数。
// 3. 枚举每个窗口起点 i，把窗口按 ws 长度切成单词，用临时表 tmp 计数：
//    - 切出的单词不在 lookup 中，或其计数超过目标次数，立即判定失败；
//    - 全部匹配则 i 为一个答案。
//
// 复杂度分析：
// - 时间复杂度：设 s 长 L、words 长 n、单词长 ws，约 O((L - n*ws) * n * ws)
//   （切单词与 substr 拷贝带来 ws 因子）。
// - 空间复杂度：O(n)，两个单词频率哈希表。

#include <gtest/gtest.h>
#include <unordered_map>

using namespace std;


class Solution {
public:
    vector<int> findSubstring(string s, vector<string> &words) {
        vector<int> ret;

        int n = words.size();
        int ws = words[0].size();
        int window_length = n * ws;

        if (s.size() < window_length) {
            return ret;
        }

        /// sort(words.begin(), words.end());
        unordered_map<string, int> lookup;
        for (int i = 0; i < n; i++) {
            lookup[words[i]]++;
        }

        for (auto i = 0; i <= s.size() - window_length; i++) {
            auto ss = s.substr(i, window_length);
            unordered_map<string, int> tmp;
            bool is_same = true;
            for (auto j = 0; j < n; j++) {
                string word = s.substr(i + j * ws, ws);
                auto it = lookup.find(word); // 单词不存在，或者出现次数超过目标次数
                if (it == lookup.end() || ++tmp[word] > it->second) {
                    is_same = false;
                    break ;
                }
            }

            if (is_same) {
                ret.push_back(i);
            }
        }

        return ret;
    }
};

TEST(top150, 30) {
    Solution s;
    auto st = "wordgoodgoodgoodbestword";
    vector<string> words{"word", "good", "best", "good"};

    // 唯一匹配起点是 8："goodgoodbestword" -> good/good/best/word
    auto ret = s.findSubstring(st, words);
    EXPECT_EQ(ret, (vector<int>{8}));
}
