"""
@file 3882.py
@brief LeetCode 3882. 网格中的最小异或路径（Minimum XOR Path in a Grid）

@题目描述
    给你一个大小为 m * n 的二维整数数组 grid。
    你从左上角单元格 (0, 0) 出发，想要到达右下角单元格 (m - 1, n - 1)。
    每一步你只能向右或向下移动。
    一条路径的代价是路径上（包括起点和终点）所有单元格值的按位异或（XOR）。
    返回所有路径代价中的最小值。

@示例
    示例 1：
    输入：grid = [[1,2],[3,4]]
    输出：6
    解释：两条路径：右→下 1⊕2⊕4 = 7；下→右 1⊕3⊕4 = 6，取最小值 6。

    示例 2：
    输入：grid = [[6,7],[5,8]]
    输出：9
    解释：6⊕7⊕8 = 9；6⊕5⊕8 = 11，最小为 9。

    示例 3：
    输入：grid = [[2,7,5]]
    输出：0
    解释：单行网格只有一条路径，2⊕7⊕5 = 0。

    数据范围：
    1 <= m == grid.length <= 1000
    1 <= n == grid[i].length <= 1000
    m * n <= 1000
    0 <= grid[i][j] <= 1023

@解题思路
    记忆化 DFS + 最优性剪枝。
    1. 状态折叠：路径总数组合级爆炸（m*n<=1000 最坏约 C(61,30)≈2.3e17 条），但到达 (x,y) 后
       能得到的结果只取决于当前累计 XOR 值 pre，与前缀走法无关；而 pre 值域仅 0..1023 共 1024 种
       （值恰好 10 位）。把状态折叠成 (x, y, pre) 存入 vis，每个状态只展开一次。
    2. 剪枝：ret == 0 时立即停止一切展开——0 是非负 XOR 可能的最小值，已到手即全局最优。
    3. 注意状态必须含 pre：只记 (x, y) 会把"不同前缀到达同一格"误判为重复而漏解
       （如 [[1,5],[6,3]]，最优 4 恰在后枚举的分支上）。
    备注：无剪枝时 vis 最坏 ~10^6 个三元组（实测峰值 ~90MB 会 MLE）；若仍超内存，
    可改用每格一个 1024 位整数做位图标记（语义等价，内存降至 ~0.2MB）。

    时间复杂度 O(m*n*1024)，空间复杂度 O(m*n*1024)

来源：LeetCode
链接：https://leetcode.cn/problems/minimum-xor-path-in-a-grid/description/
"""


class Solution:
    def minCost(self, grid: list[list[int]]) -> int:
        ret = -1
        # 记忆化：已展开过的状态 (x, y, pre)。pre 必须进 key——不同前缀 XOR 到同一格子，后续并不等价
        vis = set()

        def dfs(x, y, grid: list[list[int]], pre=0) -> None:
            nonlocal ret
            m = len(grid)
            n = len(grid[0])

            state = (x, y, pre)
            if state in vis or ret == 0:  # 同一状态的整棵子树只会被完整走一次
                return
            vis.add(state)

            pre ^= grid[y][x]
            if x == n - 1 and y == m - 1:
                if ret == -1 or pre < ret:
                    ret = pre
                return

            if x < n - 1:
                dfs(x + 1, y, grid, pre)
            if y < m - 1:
                dfs(x, y + 1, grid, pre)

        dfs(0, 0, grid, 0)

        return ret


def test_solution() -> None:
    solution = Solution()
    # 官方示例
    assert solution.minCost([[1, 2], [3, 4]]) == 6  # 示例 1：下→右 1^3^4=6 优于 右→下 1^2^4=7
    assert solution.minCost([[6, 7], [5, 8]]) == 9  # 示例 2：6^7^8=9 优于 6^5^8=11
    assert solution.minCost([[2, 7, 5]]) == 0  # 示例 3：单行唯一路径 2^7^5=0
    # 边界：1×1 / 单列 / 全 0
    assert solution.minCost([[5]]) == 5  # 起点即终点，路径只含一个格子
    assert solution.minCost([[1023]]) == 1023  # 值域上界，也是可能的最大答案——答案哨兵不能比它小
    assert solution.minCost([[3], [1], [2]]) == 0  # 单列只能一路向下，3^1^2=0
    assert solution.minCost([[0, 0], [0, 0]]) == 0  # 全 0 网格
    # 陷阱：XOR 不是加法，贪心/求和思路会错
    assert solution.minCost([[1, 1, 1]]) == 1  # 奇数个相同值：成对相消后剩一个
    assert solution.minCost([[8, 8], [8, 8]]) == 8  # 路径长 m+n-1=3 为奇数，三个 8 抵不成 0
    assert solution.minCost([[1, 5], [6, 3]]) == 4  # 和最小的路径 1,5,3 给 7；真正最优是 1^6^3=4
    assert solution.minCost([[1023, 1], [2, 1023]]) == 1  # 两个 1023 相互抵消，答案与大值无关
    # 多路径组合（期望值经全路径枚举暴力验证）
    assert solution.minCost([[7, 1, 4], [2, 6, 3], [5, 0, 2]]) == 1  # 3×3，含 0
    assert (
        solution.minCost(
            [[3, 10, 14, 6, 6], [12, 14, 9, 14, 8], [14, 8, 8, 8, 9], [1, 7, 8, 14, 8], [3, 13, 15, 8, 10]]
        )
        == 2
    )  # 5×5，最优 XOR 恰为 2，排除"答案非 0 即大"的巧合实现


if __name__ == "__main__":
    test_solution()
    print("✅ No.3882 全部测试通过")
