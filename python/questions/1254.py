"""
@file 1254.py
@brief LeetCode 1254. Number of Closed Islands

@题目描述
    二维矩阵 grid 由 0（陆地）和 1（水域）组成。
    「岛屿」是由上下左右四个方向相邻的 0 组成的最大连通群，
    「封闭岛屿」是完全被 1（水域）包围的岛屿（不接触矩阵边界）。
    请返回封闭岛屿的数目。

@示例
    示例 1：
    输入：grid = [[1,1,1,1,1,1,1,0],
                 [1,0,0,0,0,1,1,0],
                 [1,0,1,0,1,1,1,0],
                 [1,0,0,0,0,1,0,1],
                 [1,1,1,1,1,1,1,0]]
    输出：2

    示例 2：
    输入：grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
    输出：1

@解题思路
    1. 使用并查集维护陆地连通性：把每对上下左右相邻的陆地格合并；
    2. 引入哨兵节点 0，把四条边界上的陆地格全部与它合并，
       表示「所在岛屿接触矩阵外缘，不可能是封闭岛屿」；
    3. 统计所有陆地格根节点的去重数量，得到陆地分量总数；
       若哨兵根也在集合中，说明存在边界岛屿分量，减 1 即为封闭岛屿数。

    时间复杂度 O(mn·α(mn))，空间复杂度 O(mn)。

来源：LeetCode
链接：https://leetcode.cn/problems/number-of-closed-islands/description/
"""


class UnionFind:
    """路径压缩 + 按秩合并的并查集。"""

    def __init__(self, n: int) -> None:
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # 路径压缩
        return self.parent[x]

    def union(self, x: int, y: int) -> None:
        root_x, root_y = self.find(x), self.find(y)
        if root_x == root_y:
            return

        # 按秩合并：矮树挂到高树下，避免树退化成链表
        if self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        elif self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1


class Solution:
    def closedIsland(self, grid: list[list[int]]) -> int:
        m, n = len(grid), len(grid[0])
        uf = UnionFind(m * n)
        land = 0

        # 四条边界上的陆地统一并入哨兵节点 0：所在岛屿必然接触矩阵外缘
        for i in range(m):
            if grid[i][0] == land:
                uf.union(i * n, 0)
            if grid[i][n - 1] == land:
                uf.union(i * n + n - 1, 0)
        for j in range(1, n - 1):
            if grid[0][j] == land:
                uf.union(j, 0)
            if grid[m - 1][j] == land:
                uf.union((m - 1) * n + j, 0)

        # 每个格子只需向左、向上尝试合并，即可覆盖每一对相邻陆地
        for i in range(m):
            for j in range(n):
                if grid[i][j] != land:
                    continue
                if i > 0 and grid[i - 1][j] == land:
                    uf.union(i * n + j, (i - 1) * n + j)
                if j > 0 and grid[i][j - 1] == land:
                    uf.union(i * n + j, i * n + j - 1)

        # 统计陆地连通分量的根，再排除与哨兵 0 同根的「边界岛屿」
        roots = {uf.find(i * n + j) for i in range(m) for j in range(n) if grid[i][j] == land}
        total = len(roots)
        if uf.find(0) in roots:
            total -= 1
        return total


def test_solution() -> None:
    solution = Solution()

    # 官方示例
    assert (
        solution.closedIsland(
            [
                [1, 1, 1, 1, 1, 1, 1, 0],
                [1, 0, 0, 0, 0, 1, 1, 0],
                [1, 0, 1, 0, 1, 1, 1, 0],
                [1, 0, 0, 0, 0, 1, 0, 1],
                [1, 1, 1, 1, 1, 1, 1, 0],
            ]
        )
        == 2
    )
    assert solution.closedIsland([[0, 0, 1, 0, 0], [0, 1, 0, 1, 0], [0, 1, 1, 1, 0]]) == 1
    assert (
        solution.closedIsland(
            [
                [1, 1, 1, 1, 1, 1, 1],
                [1, 0, 0, 0, 0, 0, 1],
                [1, 0, 1, 1, 1, 0, 1],
                [1, 0, 1, 0, 1, 0, 1],
                [1, 0, 1, 1, 1, 0, 1],
                [1, 0, 0, 0, 0, 0, 1],
                [1, 1, 1, 1, 1, 1, 1],
            ]
        )
        == 2
    )

    # 边界情况
    assert solution.closedIsland([[1]]) == 0  # 没有陆地
    assert solution.closedIsland([[0]]) == 0  # 单格陆地接触边界
    assert solution.closedIsland([[0, 0], [0, 0]]) == 0  # 全陆地必然接触边界
    assert solution.closedIsland([[1, 1, 1], [1, 0, 1], [1, 1, 1]]) == 1  # 单格被水域完全包围
    assert solution.closedIsland([[1, 1], [1, 0]]) == 0  # 角格陆地仍接触矩阵外缘
    assert solution.closedIsland([[1, 0, 1], [0, 1, 0], [1, 0, 1]]) == 0  # 陆地全部触边


if __name__ == "__main__":
    test_solution()
    print("✅ No.1254 全部测试通过")
