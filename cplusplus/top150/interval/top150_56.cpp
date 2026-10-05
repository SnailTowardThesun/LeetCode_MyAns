//
// Created by hankun on 2026/10/1.
//

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    vector<vector<int> > merge(vector<vector<int> > &intervals) {
        vector<vector<int> > ret;

        if (intervals.empty()) {
            return ret;
        }

        sort(intervals.begin(), intervals.end());
        for (int i = 0; i < intervals.size(); ++i) {
            int left = intervals[i][0];
            int right = intervals[i][1];
            if (ret.empty() || ret.back()[1] < left) {
                ret.push_back({left, right});
            } else {
                ret.back()[1] = max(ret.back()[1], right);
            }
        }


        return ret;
    }
};

TEST(top150, 56) {
    Solution s;
    vector<vector<int> > intervals{{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    auto ret = s.merge(intervals);
    EXPECT_EQ(ret.size(), 3);
}
