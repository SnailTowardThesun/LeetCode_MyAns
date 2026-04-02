//
// Created by 韩堃 on 2026/4/2.
//

#include <gtest/gtest.h>

#include <vector>
using namespace std;

class Solution {
   public:
    int maximumAmount(vector<vector<int>>& coins) {
        auto n = coins.size();
        auto m = coins[0].size();
        std::vector<std::vector<std::vector<int>>> container(
            n, std::vector<std::vector<int>>(m, std::vector<int>(3, INT_MIN)));

        container[0][0][0] = coins[0][0];
        container[0][0][1] = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // no change
                for (int k = 0; k < 3; k++) {
                    if (i > 0 && container[i - 1][j][k] != INT_MIN) {
                        container[i][j][k] = max(container[i][j][k], container[i - 1][j][k] + coins[i][j]);
                    }

                    if (j > 0 && container[i][j - 1][k] != INT_MIN) {
                        container[i][j][k] = max(container[i][j][k], container[i][j - 1][k] + coins[i][j]);
                    }
                }

                // change
                for (int k = 1; k < 3; k++) {
                    if (i > 0 && container[i - 1][j][k - 1] != INT_MIN) {
                        container[i][j][k] = max(container[i][j][k], container[i - 1][j][k - 1]);
                    }

                    if (j > 0 && container[i][j - 1][k - 1] != INT_MIN) {
                        container[i][j][k] = max(container[i][j][k], container[i][j - 1][k - 1]);
                    }
                }
            }
        }

        int ret = INT_MIN;
        for (int i = 0; i < 3; i++) {
            ret = max(ret, container[n - 1][m - 1][i]);
        }

        return ret;
    }
};

TEST(Daily, 3418) {
    Solution s;

    auto coins = vector<vector<int>>{{0, 1, -1}, {1, -2, 3}, {2, -3, 4}};
    auto ret = s.maximumAmount(coins);
    EXPECT_EQ(ret, 8);
}
