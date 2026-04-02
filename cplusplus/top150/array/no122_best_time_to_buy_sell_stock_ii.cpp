/**
 * @file no122_best_time_to_buy_sell_stock_ii.cpp
 * @brief LeetCode 122. 买卖股票的最佳时机 II
 *
 * @题目描述
 * 给你一个整数数组 prices，其中 prices[i] 表示某支股票第 i 天的价格。
 * 在每一天，你可以决定是否购买和/或出售股票。你在任何时候最多只能持有一股股票。
 * 你也可以先购买，然后在同一天出售。返回你能获得的最大利润。
 *
 * @示例
 * 示例 1：
 * 输入: prices = [7,1,5,3,6,4]
 * 输出: 7
 * 解释: 在第 2 天买入（价格 = 1），第 3 天卖出（价格 = 5），利润 = 5-1 = 4。
 *      然后在第 4 天买入（价格 = 3），第 5 天卖出（价格 = 6），利润 = 6-3 = 3。
 *      总利润 = 4 + 3 = 7。
 *
 * 示例 2：
 * 输入: prices = [1,2,3,4,5]
 * 输出: 4
 * 解释: 在第 1 天买入（价格 = 1），第 5 天卖出（价格 = 5），利润 = 5-1 = 4。
 *      总利润 = 4。
 *
 * 示例 3：
 * 输入: prices = [7,6,4,3,1]
 * 输出: 0
 * 解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
 *
 * @解题思路
 * 1. 动态规划法：
 *    - 状态定义：dp[i][0] 表示第 i 天未持有股票的最大利润
 *              dp[i][1] 表示第 i 天持有股票的最大利润
 *    - 状态转移：
 *      - dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])  // 保持不持有或卖出
 *      - dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])  // 保持持有或买入
 *    - 初始状态：dp[0][0] = 0, dp[0][1] = -prices[0]
 *
 * 2. 贪心法（更优）：
 *    - 只要今天价格比昨天高，就在昨天买入今天卖出
 *    - 将所有上涨区间的利润累加
 *    - 时间复杂度 O(n)，空间复杂度 O(1)
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，需要遍历数组一次
 * - 空间复杂度: O(n)，使用动态规划数组（可用滚动数组优化至 O(1)）
 */

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

TEST(TOP150, No122_MaxProfitII) {
    class Solution {
    public:
        int max_profit(vector<int>& prices) {
            auto n = prices.size();
            std::vector<std::vector<int> > dp(n, std::vector<int>(2, 0));

            dp[0][0] = 0;
            dp[0][1] = -prices[0];
            for (int i = 1; i < n; i++) {
                dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
                dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
            }

            std::cout << "0: " << std::endl;
            for (auto i = 0; i < n; i++) {
                std::cout << dp[i][0] << ", ";
            }

            std::cout << std::endl;

            std::cout << "1: " << std::endl;
            for (auto i = 0; i < n; i++) {
                std::cout << dp[i][1] << ", ";
            }

            return dp[n - 1][0];
        }
    };

    Solution solution;
    std::vector<int> prices{7, 1, 5, 3, 6, 4};
    auto ret = solution.max_profit(prices);
    EXPECT_EQ(ret, 7);
}
