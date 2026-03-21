//
// Created by 韩堃 on 2026/3/21.
//
#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(Daily, 3643) {
    class Solution {
    public:
        vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
            for (int i = 0; i < k / 2; ++i) {
                swap_ranges(grid[x + i].begin() + y, grid[x + i].begin() + y + k,
                            grid[x + k - i - 1].begin() + y);
            }
            return grid;
        }
    };

    Solution s;
    auto grid = vector<vector<int>>{
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };


    auto ret = s.reverseSubmatrix(grid,1,0, 3);
    EXPECT_EQ(ret, vector<vector<int>>({
        {1,2,3,4},
        {13,14,15,8},
        {9,10,11,12},
        {5,6,7,16}
    }));


    auto grid2 = vector<vector<int>>{
        {3,4,2,3},
            {2,3,4,2}
    };
    auto ret2 = s.reverseSubmatrix(grid2, 0,2,2);
    EXPECT_EQ(ret2, vector<vector<int>>({
    {3,4,4,2},
    {2,3,2,3}}));
}