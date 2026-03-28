//
// Created by 韩堃 on 2026/3/28.
//

#include <gtest/gtest.h>
#include <vector>
using namespace std;

TEST(Daily, 2946) {
    class Solution {
    public:
        bool areSimilar(vector<vector<int>>& mat, int k) {
            int  n = mat.size();
            int  m = mat[0].size();

            auto actual_step = k % m;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (mat[i][j] != mat[i][(j + actual_step)%m]) {
                        return false;
                    }
                }
            }
            return true;
        }
    };

    Solution s;
    // auto mat = vector<vector<int>>{{1,2,3}, {4,5,6}, {7,8,9}};
    auto mat = vector<vector<int>>{{5,4,5,10,5} };
    auto ret= s.areSimilar(mat, 9);

    EXPECT_EQ(ret, false);
}