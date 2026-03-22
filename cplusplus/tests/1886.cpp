//
// Created by 韩堃 on 2026/3/22.
//

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

TEST(Daily, 1886) {
    class Solution {
       public:
        // 优化1: 使用数学公式直接计算旋转后的位置，避免多次push_back
        vector<vector<int>> rotate(const vector<vector<int>>& mat) {
            int n = mat.size();
            if (n == 0) return {};

            vector<vector<int>> ret(n, vector<int>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    // 顺时针90度: (i, j) -> (j, n-1-i)
                    ret[j][n - 1 - i] = mat[i][j];
                }
            }
            return ret;
        }

        // 优化2: 直接比较，无需真正旋转矩阵
        bool check(const vector<vector<int>>& mat, const vector<vector<int>>& target, int rotation) {
            int n = mat.size();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int ni = i, nj = j;
                    // 根据旋转次数计算原坐标
                    for (int r = 0; r < rotation; r++) {
                        int ti = ni;
                        ni = nj;
                        nj = n - 1 - ti;
                    }
                    if (mat[ni][nj] != target[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
            if (mat.size() != target.size()) return false;

            // 尝试0°, 90°, 180°, 270°四种旋转
            for (int k = 0; k < 4; k++) {
                if (check(mat, target, k)) {
                    return true;
                }
            }
            return false;
        }
    };

    Solution s;
    auto mat = std::vector<std::vector<int>>{{0, 1}, {1, 0}};
    auto target = std::vector<std::vector<int>>{{1, 0}, {0, 1}};

    auto ret = s.findRotation(mat, target);
    EXPECT_TRUE(ret);
}
