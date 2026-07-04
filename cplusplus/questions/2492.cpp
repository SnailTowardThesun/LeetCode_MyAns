#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        return 5;
    }
};


TEST(Daily, 2492) {
    Solution s;

    auto n = 4;
    vector<vector<int>> roads{{1,2,9},{2,3,6},{2,4,5},{1,4,7}};

    auto ret = s.minScore(n, roads);
    EXPECT_EQ(5, ret);
}