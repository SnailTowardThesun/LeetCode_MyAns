"""
@file top150_200.py
@brief LeetCode 200. Number of Islands（岛屿数量）

@题目描述
    给你一个由 '1'（陆地）和 '0'（水）组成的二维网格 grid，
    请你计算网格中岛屿的数量。
    岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上
    相邻的陆地连接形成。此外，你可以假设该网格的四条边均被水包围。

@示例
    示例 1：
    输入：grid = [["1","1","1","1","0"],
                 ["1","1","0","1","0"],
                 ["1","1","0","0","0"],
                 ["0","0","0","0","0"]]
    输出：1

    示例 2：
    输入：grid = [["1","1","0","0","0"],
                 ["1","1","0","0","0"],
                 ["0","0","1","0","0"],
                 ["0","0","0","1","1"]]
    输出：3

@解题思路
    1. 并查集：把 m×n 网格的格子按行优先编号（i*n+j）作为节点，初始各自成集；
    2. 遍历网格，对每个陆地格，把上下左右相邻的陆地格与它合并
       （每对邻居会被两个方向各合并一次，并查集自动忽略重复合并）；
    3. 再次遍历，收集所有陆地格所在集合的根并去重，数量即为岛屿数
       （水格不参与计数）。

    时间复杂度 O(mn·α(mn))，空间复杂度 O(mn)。

来源：LeetCode
链接：https://leetcode.cn/problems/number-of-islands/description/
"""


class UnionFind:
    def __init__(self, n):
        self._parent = list(range(n))
        self._rank = [0] * n

    def find(self, x):
        if self._parent[x] != x:
            self._parent[x] = self.find(self._parent[x])

        return self._parent[x]

    def union(self, x, y):
        root_x, root_y = self.find(x), self.find(y)
        if root_x == root_y:
            return

        if self._rank[root_x] > self._rank[root_y]:
            self._parent[root_y] = root_x
        elif self._rank[root_x] < self._rank[root_y]:
            self._parent[root_x] = root_y
        else:
            self._parent[root_y] = root_x
            self._rank[root_x] += 1


class Solution:
    def numIslands(self, grid: list[list[str]]) -> int:
        m = len(grid)
        n = len(grid[0])
        uf = UnionFind(m * n)

        for i in range(m):
            for j in range(n):
                if grid[i][j] == "0":
                    continue

                # up, bottom, left, right
                if i > 0:  # up
                    if grid[i - 1][j] == "1":
                        uf.union(i * n + j, (i - 1) * n + j)
                if i < m - 1:
                    if grid[i + 1][j] == "1":
                        uf.union(i * n + j, (i + 1) * n + j)
                if j > 0:
                    if grid[i][j - 1] == "1":
                        uf.union(i * n + j, i * n + j - 1)
                if j < n - 1:
                    if grid[i][j + 1] == "1":
                        uf.union(i * n + j, i * n + j + 1)

        dic = set()
        for i in range(m):
            for j in range(n):
                if grid[i][j] == "1":
                    dic.add(uf.find(i * n + j))
        return len(dic)


def test_solution() -> None:
    solution = Solution()

    # 官方示例
    assert (
        solution.numIslands(
            [
                ["1", "1", "1", "1", "0"],
                ["1", "1", "0", "1", "0"],
                ["1", "1", "0", "0", "0"],
                ["0", "0", "0", "0", "0"],
            ]
        )
        == 1
    )
    assert (
        solution.numIslands(
            [
                ["1", "1", "0", "0", "0"],
                ["1", "1", "0", "0", "0"],
                ["0", "0", "1", "0", "0"],
                ["0", "0", "0", "1", "1"],
            ]
        )
        == 3
    )

    # 边界情况
    assert solution.numIslands([["1"]]) == 1  # 单格陆地
    assert solution.numIslands([["0"]]) == 0  # 单格水域
    assert solution.numIslands([["0", "0"], ["0", "0"]]) == 0  # 全是水
    assert solution.numIslands([["1", "1"], ["1", "1"]]) == 1  # 全是陆地，整格为一座岛
    assert solution.numIslands([["1", "0"], ["0", "1"]]) == 2  # 对角相邻不连通
    assert solution.numIslands([["0", "1"], ["1", "0"]]) == 2  # 反对角同理
    assert solution.numIslands([["1", "0", "1", "1", "0"]]) == 2  # 单行：水平相邻才连通
    assert solution.numIslands([["1"], ["1"], ["0"], ["1"]]) == 2  # 单列：竖直相邻才连通

    # 蛇形路径：上下左右交错连成一座岛
    assert (
        solution.numIslands(
            [
                ["1", "1", "1"],
                ["0", "0", "1"],
                ["1", "1", "1"],
                ["1", "0", "0"],
                ["1", "1", "1"],
            ]
        )
        == 1
    )

    # 环形陆地：中间的水洞不会把岛拆开
    assert solution.numIslands([["1", "1", "1"], ["1", "0", "1"], ["1", "1", "1"]]) == 1

    # 棋盘格：所有陆地互不相邻，各成一座岛
    assert (
        solution.numIslands(
            [
                ["1", "0", "1", "0"],
                ["0", "1", "0", "1"],
                ["1", "0", "1", "0"],
                ["0", "1", "0", "1"],
            ]
        )
        == 8
    )


if __name__ == "__main__":
    test_solution()
    print("✅ No.200 全部测试通过")
