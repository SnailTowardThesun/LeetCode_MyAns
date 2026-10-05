//
// Created by hankun on 2026/10/1.
//

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s == t) {
            return true;
        }

        if (s.length() != t.length()) {
            return false;
        }

        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        for (auto i = 0; i < s.length(); i++) {
            if (s.at(i) != t.at(i)) {
                return false;
            }
        }

        return true;
    }
};

TEST(top150, 242) {
    Solution solution;
    auto s = "anagram", t = "nagaram";
    auto ret = solution.isAnagram(s, t);
    EXPECT_TRUE(ret == true);
}
