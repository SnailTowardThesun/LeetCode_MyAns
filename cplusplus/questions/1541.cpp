//
// Created by hankun on 2026/10/9.
//

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    int minInsertions(string s) {
        int ret = 0;
        int l = 0;

        for (auto i = 0; i < s.size(); ++i) {
            if (s.at(i) == '(') {
                l++;
                continue;
            }

            if (l > 0) {
                l--;
            } else {
                ret++;
            }

            if (i < s.size() - 1 && s.at(i+1) == ')') {
                i++;
            } else {
                ret++;
            }
        }

        ret += l * 2;


        return ret;
    }
};

TEST(Daily, 1541) {
    Solution s;
    auto ss = "()())))()";
    auto ret = s.minInsertions(ss);
    EXPECT_EQ(3, ret);
}
