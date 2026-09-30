//
// Created by hankun on 2026/9/30.
//

#include <gtest/gtest.h>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> ret(seq.size(), 0);

        int depth = 0;
        for (auto i = 0; i < seq.size(); ++i) {
            if (seq.at(i) == '(') {
                ret[i] = depth % 2;
                depth++;
            } else if (seq.at(i) == ')') {
                depth--;
                ret[i] = depth % 2;
            }
        }

        return ret;
    }
};

TEST(Daily, 1111) {
    Solution s;
    auto seq = "(()())";
    auto ret = s.maxDepthAfterSplit(seq);
    EXPECT_EQ(vector<int>({0,1,1,1,1,0}), ret);
}
