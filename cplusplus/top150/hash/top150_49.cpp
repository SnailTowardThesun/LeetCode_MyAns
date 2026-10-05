//
// Created by hankun on 2026/10/1.
//

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    vector<vector<string> > groupAnagrams(vector<string> &strs) {
        unordered_map<string, vector<string> > container;
        for (auto str: strs) {
            auto sorted = str;
            sort(sorted.begin(), sorted.end());
            container[sorted].emplace_back(str);
        }

        vector<vector<string> > ret;
        for (auto it : container) {
            ret.emplace_back(it.second);
        }

        return ret;
    }
};

TEST(top150, 49) {
    Solution s;
    vector<string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    auto ret = s.groupAnagrams(strs);
    EXPECT_EQ(ret.size(), 3);
}
