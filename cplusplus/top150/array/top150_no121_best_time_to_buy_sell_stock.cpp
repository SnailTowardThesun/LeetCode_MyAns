/**
 * @file top150_no121_best_time_to_buy_sell_stock.cpp
 * @brief LeetCode 121. 买卖股票的最佳时机
 *
 * @题目描述
 * 给定一个数组 prices，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
 * 你只能选择某一天买入这只股票，并选择在未来的某一个不同的日子卖出该股票。
 * 设计一个算法来计算你所能获取的最大利润。返回你可以从这笔交易中获取的最大利润。
 * 如果你不能获取任何利润，返回 0。
 *
 * @示例
 * 示例 1：
 * 输入: prices = [7,1,5,3,6,4]
 * 输出: 5
 * 解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，
 *      最大利润 = 6-1 = 5 。注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。
 *
 * 示例 2：
 * 输入: prices = [7,6,4,3,1]
 * 输出: 0
 * 解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
 *
 * @解题思路
 * 1. 动态规划法：
 *    - 维护两个变量：min_price（历史最低价格）和 max_profit（最大利润）
 *    - 遍历价格数组：
 *      - 更新历史最低价格
 *      - 计算当天卖出的利润，更新最大利润
 *    - 只需遍历一次数组
 *
 * 2. 暴力法（不推荐）：
 *    - 双重循环，枚举所有买入卖出组合
 *    - 时间复杂度 O(n^2)
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，只需要遍历数组一次
 * - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

TEST(TOP150, No121_MaxProfit) {
    class Solution {
    public:
        int max_profit(vector<int>& prices) {
            auto ret = 0;
            auto min_price = prices[0];
            for (auto i = 1; i < prices.size(); i++) {
                if (prices[i] < min_price) {
                    min_price = prices[i];
                } else {
                    ret = std::max(ret, prices[i] - min_price);
                }
            }

            return ret;
        }
    };

    Solution solution;
    std::vector<int> prices{7, 1, 5, 3, 6, 4};
    auto ret = solution.max_profit(prices);

    EXPECT_EQ(ret, 5);
}
