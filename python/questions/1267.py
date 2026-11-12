"""
@file 1267.py
@brief LeetCode 1267. Count Servers that Communicate（统计参与通信的服务器）

@题目描述
    给你一个 m x n 的整数矩阵 grid 表示一个服务器中心的数据分布图：
    - grid[i][j] = 1 表示单元格 (i, j) 处有一台服务器；
    - grid[i][j] = 0 表示该单元格没有服务器。

    两台服务器位于同一行或同一列，就说它们可以通信。

    统计并返回能够与至少一台其他服务器通信的服务器数目。

    提示：
    - 1 <= m, n <= 250
    - grid[i][j] 为 0 或 1

@示例
    示例 1：
    输入：grid = [[1,0],[0,1]]
    输出：0
    解释：没有服务器可以与其他服务器通信。

    示例 2：
    输入：grid = [[1,0],[1,1]]
    输出：3
    解释：三台服务器都能与至少一台其他服务器通信。

    示例 3：
    输入：grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
    输出：4
    解释：第一行的两台服务器互相通信；第三列的两台服务器互相通信。
    右下角的服务器与谁都不在同一行列，不计入。

@解题思路
    「同一行或同一列即可通信」意味着一台服务器能否通信，只取决于它所在的
    行、列里是否还有别的服务器——与连通块的形状无关，用不着 DFS/并查集：

    1. 第一遍扫描：统计每行的服务器数 row_cnt 和每列的服务器数 col_cnt；
    2. 第二遍扫描：对每个 grid[i][j] == 1 的格子，若 row_cnt[i] > 1 或
       col_cnt[j] > 1，说明同行/同列至少还有一台服务器，计入答案；
    3. 返回计数。

    相比按连通分量做 DFS/并查集（分量大小 >= 2 即全计入），计数法一遍公式
    就能判定，且完全无递归——本题 m、n 达 250，蛇形连通块可长达 6 万格，
    朴素 DFS 会撞 Python 默认递归上限（参考 No.3882 的经验）。

    时间复杂度 O(m * n)（两遍线性扫描）；空间复杂度 O(m + n)（行列计数表）。

来源：LeetCode
链接：https://leetcode.cn/problems/count-servers-that-communicate/description/
"""


class Solution:
    def countServers(self, grid: list[list[int]]) -> int:
        m, n = len(grid), len(grid[0])

        row_cnt = [0] * m
        col_cnt = [0] * n

        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    row_cnt[i] += 1
                    col_cnt[j] += 1

        ret = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    if row_cnt[i] > 1 or col_cnt[j] > 1:
                        ret += 1

        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：无同行同列，全部孤立 ----
    assert solution.countServers([[1, 0], [0, 1]]) == 0

    # ---- 官方示例 2：三台全部互通 ----
    assert solution.countServers([[1, 0], [1, 1]]) == 3

    # ---- 官方示例 3：两组互通 + 一个孤立 ----
    assert solution.countServers([[1, 1, 0, 0], [0, 0, 1, 0], [0, 0, 1, 0], [0, 0, 0, 1]]) == 4

    # ---- 最小规模：单台服务器无法通信 ----
    assert solution.countServers([[1]]) == 0

    # ---- 同一行多台：全部计入 ----
    assert solution.countServers([[1, 1, 1]]) == 3

    # ---- 同一列多台：全部计入 ----
    assert solution.countServers([[1], [1], [1]]) == 3

    # ---- 全 1 的 2x2：四台全部计入 ----
    assert solution.countServers([[1, 1], [1, 1]]) == 4

    # ---- 对角线摆放：不同行不同列，全部孤立 ----
    assert solution.countServers([[1, 0, 0], [0, 1, 0], [0, 0, 1]]) == 0

    # ---- 四角互通、中心孤立：只数四角 ----
    assert solution.countServers([[1, 0, 1], [0, 1, 0], [1, 0, 1]]) == 4


if __name__ == "__main__":
    test_solution()
    print("✅ No.1267 全部测试通过")
