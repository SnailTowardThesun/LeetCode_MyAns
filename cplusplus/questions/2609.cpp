//
// Created by hankun on 2026/3/24.
//

// 2609. 乘积矩阵
// 题目：https://leetcode.com/problems/product-of-array-except-self/
// 题目描述：
// 给你一个整数数组 nums，返回一个数组 answer，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。
// 题目数据保证数组 nums 中任意元素的全部前缀元素和后缀的乘积都在 32 位整数范围内。
// 请在 O(n) 时间复杂度内解决这个问题，且不能使用除法。
// 示例 1：
//   输入：nums = [1,2,3,4]
//   输出：[24,12,8,6]
// 示例 2：
//   输入：nums = [-1,1,0,-3,3]
//   输出：[0,0,9,0,0]
// 解题思路：
// 1. 前缀后缀法：使用两个遍历分别计算前缀积和后缀积
// 2. 结果数组：answer[i] = 前缀积[i-1] * 后缀积[i+1]
// 3. 时间复杂度：O(n)，空间复杂度：O(1)（不算输出数组）
// 注意：本题 LeetCode 原题要求不能使用除法，且输出数组不算额外空间

#include <gtest/gtest.h>

#include <vector>

using namespace std;

// ============================================================
// 版本 1: 暴力解法 (O((n*m)^2) 时间复杂度)
// 特点: 对每个位置都重新计算整个矩阵的乘积
// 缺点: 时间复杂度过高，大数据量会超时
// ============================================================
class SolutionV1 {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        const int MOD = 12345;

        vector<vector<int>> result(row, vector<int>(col, 0));

        int zero_count = 0;
        int zero_i = 0, zero_j = 0;

        // 统计零的个数
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == 0) {
                    zero_count++;
                    zero_i = i;
                    zero_j = j;
                }
            }
        }

        // 超过1个零，所有结果都是0
        if (zero_count > 1) {
            return result;
        }

        // 恰好1个零
        if (zero_count == 1) {
            long long product = 1;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    if (i != zero_i || j != zero_j) {
                        product = product * grid[i][j] % MOD;
                    }
                }
            }
            result[zero_i][zero_j] = static_cast<int>(product);
            return result;
        }

        // 没有零: 四重循环暴力计算
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                long long product = 1;
                for (int ii = 0; ii < row; ii++) {
                    for (int jj = 0; jj < col; jj++) {
                        if (ii != i || jj != j) {
                            product = product * grid[ii][jj] % MOD;
                        }
                    }
                }
                result[i][j] = static_cast<int>(product);
            }
        }

        return result;
    }
};

// ============================================================
// 版本 2: 前缀积 + 后缀积数组 (O(n*m) 时间, O(n*m) 空间)
// 特点: 使用辅助数组存储前缀积和后缀积
// 优点: 时间复杂度降到线性
// 缺点: 需要额外的 O(n*m) 空间
// ============================================================
class SolutionV2 {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        const int MOD = 12345;
        int n = row * col;

        vector<vector<int>> result(row, vector<int>(col, 0));

        int zero_count = 0;
        long long total_product = 1;

        // 统计零的个数并计算总乘积
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == 0) {
                    zero_count++;
                } else {
                    total_product = total_product * grid[i][j] % MOD;
                }
            }
        }

        // 超过1个零
        if (zero_count > 1) {
            return result;
        }

        // 恰好1个零
        if (zero_count == 1) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    if (grid[i][j] == 0) {
                        result[i][j] = static_cast<int>(total_product);
                    }
                }
            }
            return result;
        }

        // 没有零: 使用前缀积和后缀积数组
        vector<long long> prefix(n, 1);
        vector<long long> suffix(n, 1);

        // 计算前缀积
        for (int i = 1; i < n; i++) {
            int r = (i - 1) / col;
            int c = (i - 1) % col;
            prefix[i] = prefix[i - 1] * grid[r][c] % MOD;
        }

        // 计算后缀积
        for (int i = n - 2; i >= 0; i--) {
            int r = (i + 1) / col;
            int c = (i + 1) % col;
            suffix[i] = suffix[i + 1] * grid[r][c] % MOD;
        }

        // 合并结果
        for (int i = 0; i < n; i++) {
            int r = i / col;
            int c = i % col;
            result[r][c] = static_cast<int>(prefix[i] * suffix[i] % MOD);
        }

        return result;
    }
};

// ============================================================
// 版本 3: 最优解法 (O(n*m) 时间, O(1) 额外空间)
// 特点: 利用结果矩阵本身存储中间值，只用两个变量
// 优点: 时间和空间都达到最优
// ============================================================
class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        const int MOD = 12345;

        vector<vector<int>> result(row, vector<int>(col, 0));

        int zero_count = 0;
        long long total_product = 1;

        // 统计零的个数并计算总乘积
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == 0) {
                    zero_count++;
                } else {
                    total_product = total_product * grid[i][j] % MOD;
                }
            }
        }

        // 超过1个零
        if (zero_count > 1) {
            return result;
        }

        // 恰好1个零
        if (zero_count == 1) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    if (grid[i][j] == 0) {
                        result[i][j] = static_cast<int>(total_product);
                    }
                }
            }
            return result;
        }

        // 没有零: O(1)空间解法
        // 第一轮: 从右下到左上，计算后缀积并存入result
        long long suffix = 1;
        for (int i = row - 1; i >= 0; i--) {
            for (int j = col - 1; j >= 0; j--) {
                result[i][j] = static_cast<int>(suffix);
                suffix = suffix * grid[i][j] % MOD;
            }
        }

        // 第二轮: 从左到右，计算前缀积并与result中的后缀积相乘
        long long prefix = 1;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                result[i][j] = static_cast<int>(result[i][j] * prefix % MOD);
                prefix = prefix * grid[i][j] % MOD;
            }
        }

        return result;
    }
};

TEST(Daily, 2609) {
    Solution s;
    auto target = std::vector<std::vector<int>>{{10, 20}, {18, 16}, {17, 14}, {16, 9},  {14, 6},
                                                {16, 5},  {14, 8},  {20, 13}, {16, 10}, {14, 17}};

    auto ret = s.constructProductMatrix(target);
    EXPECT_EQ(ret.size(), 10);
}

// 测试所有版本
TEST(Daily, 2609_V1) {
    SolutionV1 s;
    auto target = std::vector<std::vector<int>>{{10, 20}, {18, 16}, {17, 14}, {16, 9},  {14, 6},
                                                {16, 5},  {14, 8},  {20, 13}, {16, 10}, {14, 17}};

    auto ret = s.constructProductMatrix(target);
    EXPECT_EQ(ret.size(), 10);
}

TEST(Daily, 2609_V2) {
    SolutionV2 s;
    auto target = std::vector<std::vector<int>>{{10, 20}, {18, 16}, {17, 14}, {16, 9},  {14, 6},
                                                {16, 5},  {14, 8},  {20, 13}, {16, 10}, {14, 17}};

    auto ret = s.constructProductMatrix(target);
    EXPECT_EQ(ret.size(), 10);
}
