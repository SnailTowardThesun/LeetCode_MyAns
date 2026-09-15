// @题目描述:
// LeetCode 1621. 大小为 K 的不重叠线段的数目
// （Number of Sets of K Non-Overlapping Line Segments）
// 给你一维空间的 n 个点，编号从 0 到 n-1。请你找到并返回画 k 条
// 互不重叠线段的方案数。每条线段需要包含两个端点，且两个端点不能是同一个点。
// 线段之间不能有公共部分，但允许首尾相接（即相邻两条线段可以共享一个端点）。
// 因为答案可能很大，返回对 10^9 + 7 取余的结果。
//
// @示例:
// 示例 1：
// 输入：n = 4, k = 2
// 输出：5
// 示例 2：
// 输入：n = 3, k = 1
// 输出：3
// 解释：3 个点之间可画 [0,1]、[1,2]、[0,2] 共 3 条线段。
// 示例 3：
// 输入：n = 3, k = 2
// 输出：1
// 解释：只能画 [0,1] 和 [1,2]，两条线段共享端点 1，题目允许。
//
// @解题思路:
// 动态规划。定义 dp[i][j] 为只使用编号 0~i 的点画出 j 条互不重叠线段的方案数
// （点 i 可以不被使用）。按最右端点分类：
// 1. 点 i 不参与任何线段：方案数为 dp[i-1][j]。
// 2. 点 i 是最后一条线段的右端点，设最后一条线段为 [t, i]（t < i），
//    其左侧的 j-1 条线段只使用 0~t 的点（允许共享端点 t），
//    方案数对 t 求和：sum(dp[t][j-1]), t = 0..i-1。
// 因此：dp[i][j] = dp[i-1][j] + sum(dp[t][j-1]), t = 0..i-1。
// 直接求和是 O(n^2*k)。将该式与 dp[i-1][j] 的展开式相减消去求和，得到
// O(n*k) 的转移式：
//   dp[i][j] = 2*dp[i-1][j] + dp[i-1][j-1] - dp[i-2][j]
// 边界：
// - dp[i][0] = 1：画 0 条线段只有一种方案（空方案）。
// - i < j 时不可能画出 j 条线段，dp 表初始值 0 天然覆盖；i 从 j 开始枚举。
// - i-2 越界时（i < 2），dp[i-2][j] 视为 0。
// 减法可能产生负数，取模后加回 mod 修正。
//
// 复杂度分析：
// - 时间复杂度：O(n*k)。
// - 空间复杂度：O(n*k)，可利用滚动数组优化到 O(n)。

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
    public:
        int numberOfSets(int n, int k) {
            const int mod = 1000000007;
            // dp[i][j]：只使用点 0~i 画 j 条互不重叠线段的方案数
            vector<vector<long long>> dp(n, vector<long long>(k+1, 0));

            // 边界：画 0 条线段只有一种方案
            // dp[i][0] = 1
            for (auto i = 0; i < n; i++) {
                dp[i][0] = 1;
            }

            for (int j = 1; j <= k; j++) {
                // i < j 时点不够，方案数为 0，直接从 i = j 开始枚举
                for (int i = j; i < n; i++) {
                    long long option1 = dp[i - 1][j];
                    long long option2 = dp[i - 1][j - 1];
                    long long option3 = (i >= 2) ? dp[i - 2][j] : 0;

                    // 转移：dp[i][j] = 2*dp[i-1][j] + dp[i-1][j-1] - dp[i-2][j]
                    long long res =  (2 * option1 + option2 - option3) % mod;
                    // 修正减法可能导致的负数取模
                    res = res < 0 ? res + mod : res;
                    dp[i][j] = res;
                }
            }

            return dp[n-1][k];
        }
};

TEST(Daily, 1621) {
    Solution s;
    auto n = 4;
    auto k = 2;
    auto ret= s.numberOfSets(n, k);
    EXPECT_EQ(ret, 5);

    // 基本用例：3 个点画 1 条线段，共 C(3,2) = 3 条
    EXPECT_EQ(s.numberOfSets(3, 1), 3);

    // 边界用例：3 个点画 2 条线段，只能共享端点，方案数为 1
    EXPECT_EQ(s.numberOfSets(3, 2), 1);
}
