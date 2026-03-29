//
// Created by 韩堃 on 2026/3/29.
//

#include <gtest/gtest.h>
#include <vector>
using namespace std;
class Solution {
public:
    bool canBeEqual(string s1, string s2) {
        if (s1 == s2) {
            return true;
        }

        std::swap(s1.at(0), s1.at(2));
        if (s1 == s2) {
            return true;
        }

        std::swap(s1.at(1), s1.at(3));
        if (s1 == s2) {
            return true;
        }

        std::swap(s1.at(0), s1.at(2));
        if (s1 == s2) {
            return true;
        }

        return false;
    }
};

TEST(Daily, 2839) {
    Solution s;
    string s1 = "abcd";
    string s2 = "cdab";
    auto ret = s.canBeEqual(s1, s2);
    EXPECT_EQ(true, ret);
}