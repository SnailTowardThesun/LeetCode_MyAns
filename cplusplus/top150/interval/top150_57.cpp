//
// Created by hankun on 2026/10/2.
//

#include <gtest/gtest.h>
using namespace std;

class Solution {
public:
    vector<vector<int> > insert(vector<vector<int> > &intervals, vector<int> &newInterval) {
        sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[0] < b[0];
        });

        vector<vector<int> > ret;
        int left = newInterval[0];
        int right = newInterval[1];
        int begin = -1;
        int end = -1;
        for (auto i = 0; i < intervals.size(); i++) {
            auto v = intervals[i];
            if (begin == -1 && v[1] > left) {
                begin = i;
            }

            if (v[0] < right) {
                end = i;
            }
        }

        for (auto i = 0; i < begin; i++) {
            ret.push_back(intervals[i]);
        }

        auto ev = intervals[end][1] > right ? intervals[end][1] : right;
        ret.push_back(vector<int>{intervals[begin][0], ev});

        for (auto i = end + 1; i < intervals.size(); i++) {
            ret.push_back(intervals[i]);
        }

        return ret;

    }
};

TEST(top150, 57) {
    Solution s;
    vector<vector<int> > intervals = {{1, 3}, {6, 9}};
    vector<int> newInterval = {2, 5};
    auto ret = s.insert(intervals, newInterval);
    EXPECT_EQ(ret.size(), 2);
}
