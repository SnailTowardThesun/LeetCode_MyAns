//
// Created by 韩堃 on 2026/9/25.
//

#include <gtest/gtest.h>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() < 1) {
            return 0;
        }

        int n = s.size();
        int left = 0;
        int ret = INT_MIN;
        while (left < n) {
            unordered_set<char> lookup;
            int i = left;
            for (; i < n; i++) {
                if (lookup.find(s.at(i)) != lookup.end()) {
                    break;
                }

                lookup.insert(s.at(i));
            }

            ret = max(ret, i - left);
            left++;
        }

        return ret;
    }
};

TEST(top150, 3) {
    Solution s;
    auto st = "1R1T7";
    auto ret = s.lengthOfLongestSubstring(st);
    EXPECT_EQ(ret, 4);
}
