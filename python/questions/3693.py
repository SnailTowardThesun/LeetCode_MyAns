"""
@file 3693.py
@brief LeetCode 3693. 爬楼梯 II（Climbing Stairs II）

@题目描述
    你正在爬一个有 n + 1 级台阶的楼梯，台阶编号从 0 到 n。给定长度为 n 的整数数组
    costs，其中 costs[i] 是第 i 级台阶的成本（题目声称下标从 1 开始，实际传参仍是
    0-based 数组——第 j 级台阶的代价取 costs[j-1]）。
    从第 i 级台阶只能跳到第 i+1、i+2 或 i+3 级台阶；从 i 跳到 j 的成本定义为
    costs[j] + (j - i)^2。从第 0 级台阶出发（初始 cost = 0），返回到达第 n 级台阶
    所需的最小总成本。

@示例
    示例 1：
    输入：n = 4, costs = [1,2,3,4]
    输出：13
    解释：最优路径 0 -> 1 -> 2 -> 4，三跳成本 (1+1) + (2+1) + (4+4) = 2+3+8 = 13。

    示例 2：
    输入：n = 4, costs = [5,1,6,2]
    输出：11（最优路径 0 -> 2 -> 4：(1+4) + (2+4) = 5+6 = 11）

    示例 3：
    输入：n = 3, costs = [9,8,3]
    输出：12（一步到位 0 -> 3：3 + 9 = 12）

    数据范围：
    1 <= n == costs.length <= 1e5
    1 <= costs[i] <= 1e4

@解题思路
    线性 DP：dp[j] 表示到达第 j 级台阶的最小总成本。
    1. 转移方程：dp[j] = min(dp[j-1] + costs[j-1] + 1, dp[j-2] + costs[j-1] + 4,
       dp[j-3] + costs[j-1] + 9)，三步跳距的平方代价分别为 1/4/9；
    2. 起点在第 0 级免费，dp[0] = 0；j = 1 时只有 0 -> 1 一种跳法，
       j = 2 时可从 0 直跳或经 1 中转，单独初始化；j >= 3 起三项转移齐全；
    3. 落点成本 costs[j-1] 对三种跳距相同，提出 min 外不改变结果；
    4. 约束保证 n >= 1，无需处理 n = 0。答案即 dp[n]。

    时间复杂度 O(n)，空间复杂度 O(n)（可滚动至 O(1)，n <= 1e5 无需优化）
    数值安全：总成本上界 n * (max(costs) + 9) ≈ 1e5 * 10009 ≈ 1.0e9 < 2^31-1

来源：LeetCode
链接：https://leetcode.cn/problems/climbing-stairs-ii/description/
"""


class Solution:
    def climbStairs(self, n: int, costs: list[int]) -> int:
        dp = [0] * (n + 1)

        # 第 1 级：只能从 0 直跳一步
        dp[1] = costs[0] + 1
        if n == 1:
            return dp[1]

        # 第 2 级：从 0 直跳两步，或经第 1 级中转
        dp[2] = min(costs[1] + 1 + dp[1], costs[1] + 4)
        if n == 2:
            return dp[2]

        # 第 3 级起三项转移齐全；落点成本 costs[i-1] 三种跳距相同，留在 min 内直观表达
        for i in range(3, n + 1):
            dp[i] = min(costs[i - 1] + 1 + dp[i - 1], min(costs[i - 1] + 4 + dp[i - 2], costs[i - 1] + 9 + dp[i - 3]))

        return dp[n]


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：最优路径 0 -> 1 -> 2 -> 4 ----
    assert solution.climbStairs(4, [1, 2, 3, 4]) == 13

    # ---- 官方示例 2：最优路径 0 -> 2 -> 4，跨过昂贵的第 1 级 ----
    assert solution.climbStairs(4, [5, 1, 6, 2]) == 11

    # ---- 官方示例 3：一步到位 0 -> 3，付出 9 的平方代价 ----
    assert solution.climbStairs(3, [9, 8, 3]) == 12

    # ---- 最小规模：单级台阶只能直跳一步 ----
    assert solution.climbStairs(1, [7]) == 8

    # ---- 两级台阶：直跳 (9+4) 便宜于中转 (8 + 9+1) ----
    assert solution.climbStairs(2, [7, 9]) == 13

    # ---- 混合贪心陷阱：n=5 最优是 1,2,2 组合（经 1、3、5），逐级爬反而更贵 ----
    assert solution.climbStairs(5, [2, 3, 1, 4, 2]) == 14


if __name__ == "__main__":
    test_solution()
    print("✅ No.3693 全部测试通过")
