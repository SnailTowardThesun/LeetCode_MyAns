//
// Created by 韩堃 on 2026/3/25.
//
// LeetCode 3546: 矩阵分割判断
// 题目: 判断是否可以通过一条水平或垂直分割线将矩阵分割成两部分，使得两部分元素和相等
//

#include <gtest/gtest.h>

#include <vector>

using namespace std;

// ============================================================
// 版本 1: 暴力解法 - 前缀和 + 后缀和数组
// ============================================================
// 思路:
//   1. 先计算每行的和，存储到 row_sums 数组
//   2. 对 row_sums 计算前缀和数组 pre 和后缀和数组 post
//   3. 遍历检查是否存在 pre[i] == post[i+1]
//   4. 对列做同样的处理
//
// 时间复杂度: O(m*n + m + n) = O(m*n)
// 空间复杂度: O(m + n) - 需要存储行和、列和数组，以及前缀/后缀数组
//
// 局限性:
//   - 需要多次分配内存，内存开销较大
//   - 代码结构复杂，需要辅助函数
//   - 存在重复计算，先存数组再遍历检查效率不高
// ============================================================
class SolutionV1 {
public:
    bool helper(const vector<int64_t>& board) {
        int n = board.size();
        vector<int64_t> pre(n);
        vector<int64_t> post(n);

        // 计算前缀和
        pre[0] = board[0];
        for (int i = 1; i < n; i++) {
            pre[i] = board[i] + pre[i - 1];
        }

        // 计算后缀和
        post[n - 1] = board[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            post[i] = board[i] + post[i + 1];
        }

        // 检查是否存在分割点
        for (int i = 0; i < n - 1; i++) {
            if (pre[i] == post[i + 1]) {
                return true;
            }
        }
        return false;
    }

    bool canPartitionGrid(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // 计算每行的和
        vector<int64_t> row_sums(rows);
        for (int i = 0; i < rows; i++) {
            int64_t sum = 0;
            for (int val : grid[i]) {
                sum += val;
            }
            row_sums[i] = sum;
        }

        if (helper(row_sums)) {
            return true;
        }

        // 计算每列的和
        vector<int64_t> col_sums(cols);
        for (int j = 0; j < cols; j++) {
            int64_t sum = 0;
            for (int i = 0; i < rows; i++) {
                sum += grid[i][j];
            }
            col_sums[j] = sum;
        }

        return helper(col_sums);
    }
};

// ============================================================
// 版本 2: 优化解法 - 总和 + 单次遍历
// ============================================================
// 思路:
//   1. 计算行和数组的总和 total
//   2. 遍历行和数组，累加前缀和 prefix
//   3. 如果 prefix * 2 == total，说明找到分割点
//   4. 利用数学性质: 如果总和是奇数，直接返回 false
//
// 时间复杂度: O(m*n + m + n) = O(m*n)
// 空间复杂度: O(m + n) - 仍需要存储行和、列和数组
//
// 优化点:
//   - 去掉了后缀和数组，通过总和减去前缀和得到后缀和
//   - 利用奇偶性提前返回，减少不必要的计算
//   - 代码更简洁，只需单次遍历
//
// 局限性:
//   - 仍然需要 O(m+n) 的额外空间存储行和列的和
//   - 需要两次遍历矩阵（一次计算行和，一次计算列和）
// ============================================================
class SolutionV2 {
public:
    bool helper(const vector<int64_t>& board) {
        int64_t total = 0;
        for (int64_t val : board) {
            total += val;
        }

        // 奇偶性判断：总和为奇数不可能平分
        if (total % 2 != 0) {
            return false;
        }

        int64_t target = total / 2;
        int64_t prefix = 0;

        for (size_t i = 0; i < board.size() - 1; i++) {
            prefix += board[i];
            if (prefix == target) {
                return true;
            }
        }
        return false;
    }

    bool canPartitionGrid(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // 计算每行的和
        vector<int64_t> row_sums(rows);
        for (int i = 0; i < rows; i++) {
            int64_t sum = 0;
            for (int val : grid[i]) {
                sum += val;
            }
            row_sums[i] = sum;
        }

        if (helper(row_sums)) {
            return true;
        }

        // 计算每列的和
        vector<int64_t> col_sums(cols);
        for (int j = 0; j < cols; j++) {
            int64_t sum = 0;
            for (int i = 0; i < rows; i++) {
                sum += grid[i][j];
            }
            col_sums[j] = sum;
        }

        return helper(col_sums);
    }
};

// ============================================================
// 版本 3: 最优解法 - O(1)空间，直接计算
// ============================================================
// 思路:
//   1. 一次性计算整个矩阵的总和 total_sum
//   2. 检查水平分割线：遍历每一行，累加前缀行和
//      - 如果 prefix_row_sum * 2 == total_sum，返回 true
//   3. 检查垂直分割线：遍历每一列，累加前缀列和
//      - 如果 prefix_col_sum * 2 == total_sum，返回 true
//
// 时间复杂度: O(m*n) - 只需遍历矩阵常数次
// 空间复杂度: O(1) - 仅用几个变量，无需额外数组
//
// 核心优化:
//   - 摒弃了"先存储每行/列和，再检查"的中间步骤
//   - 直接在遍历矩阵的过程中计算前缀和并检查
//   - 无需辅助函数，逻辑完全内联
//   - 代码最简洁，执行效率最高
//
// 适用场景:
//   - 大规模矩阵时优势最明显（节省 O(m+n) 空间）
//   - 对内存敏感的场景
//   - 追求极致性能的场景
// ============================================================
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // 计算整个矩阵的总和
        int64_t total_sum = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                total_sum += grid[i][j];
            }
        }

        // 检查水平分割线：前k行 vs 剩余行
        int64_t prefix_row_sum = 0;
        for (int i = 0; i < rows - 1; i++) {
            for (int j = 0; j < cols; j++) {
                prefix_row_sum += grid[i][j];
            }
            if (prefix_row_sum * 2 == total_sum) {
                return true;
            }
        }

        // 检查垂直分割线：前k列 vs 剩余列
        int64_t prefix_col_sum = 0;
        for (int j = 0; j < cols - 1; j++) {
            for (int i = 0; i < rows; i++) {
                prefix_col_sum += grid[i][j];
            }
            if (prefix_col_sum * 2 == total_sum) {
                return true;
            }
        }

        return false;
    }
};

// ============================================================
// 测试用例
// ============================================================
TEST(Daily, 3546) {
    Solution s;
    vector<vector<int>> eg{{54756, 54756}};
    auto ret = s.canPartitionGrid(eg);
    EXPECT_EQ(true, ret);
}

TEST(Daily, 3546_V1) {
    SolutionV1 s;
    vector<vector<int>> eg{{54756, 54756}};
    auto ret = s.canPartitionGrid(eg);
    EXPECT_EQ(true, ret);
}

TEST(Daily, 3546_V2) {
    SolutionV2 s;
    vector<vector<int>> eg{{54756, 54756}};
    auto ret = s.canPartitionGrid(eg);
    EXPECT_EQ(true, ret);
}

// 额外测试用例：2x2矩阵
TEST(Daily, 3546_2x2) {
    Solution s;
    vector<vector<int>> eg{{1, 4}, {2, 3}};  // 水平分割: 1+4=5, 2+3=5
    auto ret = s.canPartitionGrid(eg);
    EXPECT_EQ(true, ret);
}

TEST(Daily, 3546_V1_2x2) {
    SolutionV1 s;
    vector<vector<int>> eg{{1, 4}, {2, 3}};
    auto ret = s.canPartitionGrid(eg);
    EXPECT_EQ(true, ret);
}

TEST(Daily, 3546_V2_2x2) {
    SolutionV2 s;
    vector<vector<int>> eg{{1, 4}, {2, 3}};
    auto ret = s.canPartitionGrid(eg);
    EXPECT_EQ(true, ret);
}
