// @题目描述:
// 你正在爬一个有 n + 1 级台阶的楼梯，台阶编号从 0 到 n。给定长度为 n 的整数数组
// costs。题面按 1-based 描述台阶费用；本文统一使用实际传参的 0-based 下标，
// 第 j 级台阶的费用为 costs[j-1]。
// 从第 i 级台阶只能跳到第 i+1、i+2 或 i+3 级台阶；从 i 跳到 j 的成本定义为
// costs[j-1] + (j - i)^2。从第 0 级台阶出发（初始 cost = 0），返回到达第 n 级台阶
// 所需的最小总成本。
//
// @示例:
// 输入：n = 4, costs = [1,2,3,4]
// 输出：13
// 解释：最优路径 0 -> 1 -> 2 -> 4，三跳成本 (1+1) + (2+1) + (4+4) = 2+3+8 = 13。
// 输入：n = 4, costs = [5,1,6,2]
// 输出：11（最优路径 0 -> 2 -> 4：(1+4) + (2+4) = 5+6 = 11）
// 输入：n = 3, costs = [9,8,3]
// 输出：12（一步到位 0 -> 3：3 + 9 = 12）
//
// @解题思路:
// 线性 DP：dp[j] 表示到达第 j 级台阶的最小总成本。
// 1. 转移方程：dp[j] = min(dp[j-1] + costs[j-1] + 1, dp[j-2] + costs[j-1] + 4,
//    dp[j-3] + costs[j-1] + 9)，三步跳距的平方代价分别为 1/4/9；
// 2. 起点在第 0 级免费，dp[0] = 0；j = 1 时只有 0 -> 1 一种跳法，
//    j = 2 时可从 0 直跳或经 1 中转，单独初始化；j >= 3 起三项转移齐全；
// 3. 落点成本 costs[j-1] 对三种跳距相同，提出 min 外不改变结果；
// 4. 约束保证 n >= 1，无需处理 n = 0。答案即 dp[n]。
//
// 复杂度分析：
// - 时间复杂度：O(n)，一次线性递推
// - 空间复杂度：O(n)，dp 数组（可滚动至 O(1)，n <= 1e5 无需优化）
// 数值安全：总成本上界 n * (max(costs) + 9) ≈ 1e5 * 10009 ≈ 1.0e9 < INT_MAX

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int climbStairs(int n, vector<int>& costs) {
        vector<int> dp(n + 1, 0);

        // 第 1 级：只能从 0 直跳一步
        dp[1] = costs[0] + 1;
        if (n == 1) {
            return dp[1];
        }

        // 第 2 级：从 0 直跳两步，或经第 1 级中转
        dp[2] = min(costs[1] + 1 + dp[1], costs[1] + 4);
        if (n == 2) {
            return dp[2];
        }

        // 第 3 级起三项转移齐全；落点成本 costs[i-1] 三种跳距相同，留在 min 内直观表达
        for (int i = 3; i <= n; i++) {
            dp[i] = min(costs[i - 1] + 1 + dp[i - 1], min(costs[i - 1] + 4 + dp[i - 2], costs[i - 1] + 9 + dp[i - 3]));
        }

        return dp[n];
    }
};
}  // namespace

TEST(Daily, 3693) {
    Solution s;

    // 官方示例 1：最优路径 0 -> 1 -> 2 -> 4
    vector<int> costs1{1, 2, 3, 4};
    EXPECT_EQ(s.climbStairs(4, costs1), 13);

    // 官方示例 2：最优路径 0 -> 2 -> 4，跨过昂贵的第 1 级
    vector<int> costs2{5, 1, 6, 2};
    EXPECT_EQ(s.climbStairs(4, costs2), 11);

    // 官方示例 3：一步到位 0 -> 3，付出 9 的平方代价
    vector<int> costs3{9, 8, 3};
    EXPECT_EQ(s.climbStairs(3, costs3), 12);

    // 最小规模：单级台阶只能直跳一步
    vector<int> costs4{7};
    EXPECT_EQ(s.climbStairs(1, costs4), 8);

    // 两级台阶：直跳 (9+4) 便宜于中转 (8 + 9+1)
    vector<int> costs5{7, 9};
    EXPECT_EQ(s.climbStairs(2, costs5), 13);

    // 混合贪心陷阱：n=5 最优是 1,2,2 组合（经 1、3、5），逐级爬反而更贵
    vector<int> costs6{2, 3, 1, 4, 2};
    EXPECT_EQ(s.climbStairs(5, costs6), 14);
}
