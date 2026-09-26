//
// Created by 韩堃 on 2026/9/26.
//
// LeetCode 76. 最小覆盖子串
// 思路：滑动窗口。lookup 统计 t 中每个字符的需求量，
// 右指针扩张窗口、左指针在窗口覆盖 t 后尽量收缩，记录最短窗口。

#include <gtest/gtest.h>
#include <climits>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int m = s.size();
        int n = t.size();

        if (m < n) {
            return "";
        }

        // t 中每个字符的需求量
        unordered_map<char, int> lookup;
        for (auto i: t) {
            lookup[i]++;
        }

        unordered_map<char, int> window;
        int need = lookup.size();  // 需要满足的字符种类数
        int matched = 0;           // 当前窗口内已满足的种类数
        int best_len = INT_MAX;
        int best_left = -1;
        int left = 0;

        for (int right = 0; right < m; right++) {
            char c = s[right];
            if (lookup.count(c)) {
                window[c]++;
                // 该字符数量恰好达标时，种类数 +1
                if (window[c] == lookup[c]) {
                    matched++;
                }
            }

            // 窗口已覆盖 t，收缩左边界寻找更短的覆盖
            while (matched == need) {
                if (right - left + 1 < best_len) {
                    best_len = right - left + 1;
                    best_left = left;
                }
                char lc = s[left];
                if (lookup.count(lc)) {
                    window[lc]--;
                    // 移出后不再满足需求，种类数 -1，结束收缩
                    if (window[lc] < lookup[lc]) {
                        matched--;
                    }
                }
                left++;
            }
        }

        return best_left == -1 ? "" : s.substr(best_left, best_len);
    }
};

TEST(top150, 76) {
    Solution s;
    // 示例 1
    auto ss = "ADOBECODEBANC";
    auto t = "ABC";
    auto ret = s.minWindow(ss, t);
    EXPECT_EQ(ret, "BANC");

    // 示例 2：无覆盖
    EXPECT_EQ(s.minWindow("a", "aa"), "");

    // 示例 3：单字符
    EXPECT_EQ(s.minWindow("a", "a"), "a");
}
