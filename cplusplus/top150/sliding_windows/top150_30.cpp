//
// Created by 韩堃 on 2026/9/26.
//

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
