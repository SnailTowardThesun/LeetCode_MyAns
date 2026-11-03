"""
@file top150_123.py
@brief LeetCode 123. Best Time to Buy and Sell Stock III（买卖股票的最佳时机 III）

@题目描述
    给定一个数组 prices，它的第 i 个元素 prices[i] 表示某支股票第 i 天的价格。
    设计算法计算所能获取的最大利润：最多可以完成两笔交易（买入并卖出算一笔），
    同时最多只能持有一支股票（卖出后才能再次买入）。

@示例
    示例 1：
    输入：prices = [3,3,5,0,0,3,1,4]
    输出：6
    解释：第 4 天（价格 0）买入、第 6 天（价格 3）卖出，第一笔利润 3；
          第 7 天（价格 1）买入、第 8 天（价格 4）卖出，第二笔利润 3，总计 6。

    示例 2：
    输入：prices = [1,2,3,4,5]
    输出：4
    解释：第 1 天买入、第 5 天卖出，利润 4，一笔交易已是最优。

    示例 3：
    输入：prices = [7,6,4,3,1]
    输出：0
    解释：单调递减，不交易即最优。

    数据范围：
    1 <= prices.length <= 10^5
    0 <= prices[i] <= 10^5

@解题思路
    状态机 DP（O(n) 时间、O(1) 空间），四个状态滚动维护：
    - buy1 ：完成第 1 次买入后（持有）的最大收益
    - sell1：完成第 1 次卖出后的最大收益
    - buy2 ：完成第 2 次买入后（持有）的最大收益
    - sell2：完成第 2 次卖出后的最大收益
    第 i 天按依赖顺序转移（max(维持原状, 今天操作)）：
      buy1  = max(buy1,  -prices[i])            今天第一次买入
      sell1 = max(sell1, buy1 + prices[i])      今天卖出第一笔
      buy2  = max(buy2,  sell1 - prices[i])     今天第二次买入
      sell2 = max(sell2, buy2 + prices[i])      今天卖出第二笔
    初始 buy1 = buy2 = -prices[0]、sell1 = sell2 = 0，答案为 sell2。
    "至多两笔"意味着 sell2 >= sell1 >= 0；同一天先买后卖收益为 0，
    等价于少做一笔交易，因此转移用当天新值更新也不影响正确性。

    时间复杂度 O(n)，空间复杂度 O(1)
"""


class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        n = len(prices)
        # 初始：第 0 天买入（一次/两次都视作已买入，同日买卖收益 0）
        buy1 = buy2 = -prices[0]
        sell1 = sell2 = 0

        for i in range(1, n):
            buy1 = max(buy1, -prices[i])  # 今天第一次买入
            sell1 = max(sell1, buy1 + prices[i])  # 今天卖出第一笔
            buy2 = max(buy2, sell1 - prices[i])  # 今天第二次买入
            sell2 = max(sell2, buy2 + prices[i])  # 今天卖出第二笔

        return sell2


def test_solution() -> None:
    solution = Solution()
    # 官方示例
    assert solution.maxProfit([3, 3, 5, 0, 0, 3, 1, 4]) == 6
    assert solution.maxProfit([1, 2, 3, 4, 5]) == 4
    assert solution.maxProfit([7, 6, 4, 3, 1]) == 0
    # 边界：单天无法交易
    assert solution.maxProfit([2]) == 0
    # 两笔优于一笔：(4-1) + (8-2) = 9 > 单笔最大 8 - 2 = 6
    assert solution.maxProfit([1, 4, 2, 8]) == 9
    # 两天单调：只能做一笔 3 - 1 = 2
    assert solution.maxProfit([1, 3]) == 2


if __name__ == "__main__":
    test_solution()
    print("✅ No.123 全部测试通过")
