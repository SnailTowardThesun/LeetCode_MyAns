"""
@file top150_188.py
@brief LeetCode 188. Best Time to Buy and Sell Stock IV（买卖股票的最佳时机 IV）

@题目描述
    给定一个整数 k 和一个数组 prices，它的第 i 个元素 prices[i] 表示某支股票第 i 天的价格。
    设计算法计算所能获取的最大利润：最多可以完成 k 笔交易（买入并卖出算一笔），
    同时最多只能持有一支股票（卖出后才能再次买入）。

@示例
    示例 1：
    输入：k = 2, prices = [2,4,1]
    输出：2
    解释：第 1 天（价格 2）买入、第 2 天（价格 4）卖出，利润 2；
          k 用不完没关系，一笔交易即是最优。

    示例 2：
    输入：k = 2, prices = [3,2,6,5,0,3]
    输出：7
    解释：第 2 天（价格 2）买入、第 3 天（价格 6）卖出，第一笔利润 4；
          第 5 天（价格 0）买入、第 6 天（价格 3）卖出，第二笔利润 3，总计 7。

    数据范围：
    1 <= k <= 100
    1 <= prices.length <= 1000
    0 <= prices[i] <= 1000

@解题思路
    二维状态机 DP（123 题「至多两笔」推广到「至多 k 笔」）：
    - k 裁剪：一笔交易至少占两天（买入日 + 卖出日），有效交易数不超过 n//2，
      先令 k = min(k, n // 2)，既保证正确性也把 DP 规模控制在 O(n^2) 以内。
    - buy[i][j] ：第 i 天结束、已完成第 j+1 次买入（持股）的最大收益
    - sell[i][j]：第 i 天结束、已完成第 j+1 次卖出（空仓）的最大收益
    第 i 天对每个状态取 max(维持原状, 今天操作)：
      buy[i][j]  = max(buy[i-1][j],  sell[i-1][j]  - prices[i])   今天完成第 j+1 次买入
      sell[i][j] = max(sell[i-1][j], buy[i-1][j-1] + prices[i])   今天完成第 j+1 次卖出
    初始：第 0 天只能完成第一次买入，buy[0][0] = -prices[0]、sell[0][0] = 0，
    j >= 1 的状态不可达，置为 -inf；sell[i][0] 恒为 0（从未买入）。
    答案：max(sell[n-1])——「至多 k 笔」允许少做或不做，取所有卖出层的最大值。

    时间复杂度 O(n·k)，空间复杂度 O(n·k)（可滚动数组优化到 O(k)）
"""


class Solution:
    def maxProfit(self, k: int, prices: list[int]) -> int:
        n = len(prices)
        # 一笔交易至少占两天（买入日 + 卖出日），有效交易数不超过 n//2
        k = min(k, n // 2)
        # buy[i][j]：第 i 天结束、已完成第 j+1 次买入（持股）的最大收益
        # sell[i][j]：第 i 天结束、已完成第 j+1 次卖出（空仓）的最大收益
        buy = [[0] * (k + 1) for _ in range(n)]
        sell = [[0] * (k + 1) for _ in range(n)]

        # 初始：第 0 天只能完成第一次买入，j >= 1 不可达
        buy[0][0] = -prices[0]
        sell[0][0] = 0
        for j in range(1, k + 1):
            buy[0][j] = sell[0][j] = float("-inf")

        for i in range(1, n):
            # 第 0 层：从未卖出过，只能继续持有或今天首次买入
            buy[i][0] = max(buy[i - 1][0], sell[i - 1][0] - prices[i])
            for j in range(1, k + 1):
                # 今天完成第 j+1 次买入：从前一天同层的空仓状态转入
                buy[i][j] = max(buy[i - 1][j], sell[i - 1][j] - prices[i])
                # 今天完成第 j+1 次卖出：从前一天低一层的持股状态转入
                sell[i][j] = max(sell[i - 1][j], buy[i - 1][j - 1] + prices[i])

        # 「至多 k 笔」允许少做或不做，取所有卖出层的最大值
        return max(sell[n - 1])


def test_solution() -> None:
    solution = Solution()
    # 官方示例 1：单笔最优 4 - 2 = 2
    assert solution.maxProfit(2, [2, 4, 1]) == 2
    # 官方示例 2：两笔 (6-2) + (3-0) = 7
    assert solution.maxProfit(2, [3, 2, 6, 5, 0, 3]) == 7
    # 边界：单天无法交易（k 被裁剪为 0）
    assert solution.maxProfit(100, [5]) == 0
    # 两天单调：只能做一笔 3 - 1 = 2
    assert solution.maxProfit(2, [1, 3]) == 2
    # 单调递减：不交易即最优
    assert solution.maxProfit(2, [7, 6, 4, 3, 1]) == 0
    # k 超过 n//2 时等价于不限次数（122 题）：拼出所有上坡 5 - 1 = 4
    assert solution.maxProfit(10, [1, 2, 3, 4, 5]) == 4
    # 两笔优于一笔：(4-1) + (8-2) = 9 > 单笔最大 8 - 1 = 7
    assert solution.maxProfit(2, [1, 4, 2, 8]) == 9
    # 三笔优于一两笔：(4-1) + (8-2) + (9-3) = 15，限两笔时 (8-1) + (9-3) = 13
    assert solution.maxProfit(3, [1, 4, 2, 8, 3, 9]) == 15
    assert solution.maxProfit(2, [1, 4, 2, 8, 3, 9]) == 13


if __name__ == "__main__":
    test_solution()
    print("✅ No.188 全部测试通过")
