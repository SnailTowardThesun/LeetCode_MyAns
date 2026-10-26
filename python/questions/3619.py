"""
@file 3619.py
@brief LeetCode 3619. Count Islands With Total Value Divisible by K（总价值可以被 K 整除的岛屿数目）

@题目描述
    给你一个 m x n 的矩阵 grid 和一个正整数 k。
    一个「岛屿」是由正整数（表示陆地）组成、且陆地间四方向连通
    （水平或垂直）的区域；值为 0 的格子是水。
    一个岛屿的总价值是该岛屿中所有单元格的值之和。
    返回总价值可以被 k 整除的岛屿数量。

@示例
    示例 1：
    输入：grid = [[0,2,1,0,0],
                 [0,5,0,0,5],
                 [0,0,1,0,0],
                 [0,1,4,7,0],
                 [0,2,0,0,8]], k = 5
    输出：2
    解释：网格中有四座岛，总价值分别为 8、5、15、8，
    其中 5 和 15 可以被 5 整除。

    示例 2：
    输入：grid = [[3,0,3,0],
                 [0,3,0,3],
                 [3,0,3,0]], k = 3
    输出：6
    解释：六座单格岛，每座总价值 3 都能被 3 整除。

@解题思路
    1. 并查集：格子按行优先编号（i*n+j）作为节点，初始各自成集；
    2. 遍历网格，对每个陆地格（值 != 0，本题陆地是任意正整数而非固定 1），
       把上下左右相邻的陆地格与它合并；
    3. 再次遍历，把每个陆地格的值累加到它所在集合的根上，
       得到每座岛的总价值；
    4. 统计总价值能被 k 整除的岛屿数量。

    时间复杂度 O(mn·α(mn))，空间复杂度 O(mn)。

来源：LeetCode
链接：https://leetcode.cn/problems/count-islands-with-total-value-divisible-by-k/description/
"""


class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        root_x, root_y = self.find(x), self.find(y)
        if root_x == root_y:
            return

        if self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        elif self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1


class Solution:
    def countIslands(self, grid: list[list[int]], k: int) -> int:
        if len(grid) == 0:
            return 0

        if len(grid[0]) == 0:
            return 0

        m, n = len(grid), len(grid[0])
        uf = UnionFind(m * n)
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 0:
                    continue
                if j > 0:
                    if grid[i][j - 1] != 0:
                        uf.union(i * n + j, i * n + j - 1)
                if j < n - 1:
                    if grid[i][j + 1] != 0:
                        uf.union(i * n + j, i * n + j + 1)
                if i > 0:
                    if grid[i - 1][j] != 0:
                        uf.union(i * n + j, (i - 1) * n + j)
                if i < m - 1:
                    if grid[i + 1][j] != 0:
                        uf.union(i * n + j, (i + 1) * n + j)
        dic = {}
        for i in range(m):
            for j in range(n):
                if grid[i][j] != 0:
                    root = uf.find(i * n + j)
                    if dic.get(root, None) is None:
                        dic[root] = grid[i][j]
                    else:
                        dic[root] += grid[i][j]

        ret = 0
        for _, v in dic.items():
            if v % k == 0:
                ret += 1
        return ret


def test_solution() -> None:
    solution = Solution()

    # 官方示例
    assert (
        solution.countIslands(
            [
                [0, 2, 1, 0, 0],
                [0, 5, 0, 0, 5],
                [0, 0, 1, 0, 0],
                [0, 1, 4, 7, 0],
                [0, 2, 0, 0, 8],
            ],
            5,
        )
        == 2
    )
    assert solution.countIslands([[3, 0, 3, 0], [0, 3, 0, 3], [3, 0, 3, 0]], 3) == 6

    # 边界情况
    assert solution.countIslands([[0, 0], [0, 0]], 5) == 0  # 全是水，没有岛屿
    assert solution.countIslands([[0]], 1) == 0  # 单格水
    assert solution.countIslands([[5]], 5) == 1  # 单格陆地，总价值恰为 k
    assert solution.countIslands([[5]], 3) == 0  # 单格陆地，总价值不被 k 整除
    assert solution.countIslands([[1, 0], [0, 1]], 1) == 2  # 对角不连通，是两座岛
    assert solution.countIslands([[1000000]], 1000000) == 1  # 值域上界

    # 判定对象是「总和」而不是单个格子：每格 2 都不被 4 整除，但总和 4 可以
    assert solution.countIslands([[2, 2]], 4) == 1
    # 反例：中间隔水，两座单格岛各自总和 2，都不被 4 整除
    assert solution.countIslands([[2, 0, 2]], 4) == 0

    # 求和要覆盖整座岛：横向三格和为 3 才整除，两格和为 2 则不整除
    assert solution.countIslands([[1, 1, 1]], 3) == 1
    assert solution.countIslands([[1, 1]], 3) == 0

    # 蛇形整座岛：2+1+1+3+1+1 = 9，拐弯的格子不能漏加
    assert solution.countIslands([[0, 2, 1], [0, 1, 0], [3, 1, 1]], 9) == 1

    # 跨四行的蛇形岛 1+6+2+10 = 19 恰好整除 k；单格岛 11 和 8 都不整除
    assert solution.countIslands([[0, 0, 0], [0, 0, 1], [11, 0, 6], [0, 10, 2], [0, 0, 0], [8, 0, 0]], 19) == 1

    # k = 1 时任何总价值都可整除：退化为数岛屿个数（示例 1 网格共四座岛）
    assert (
        solution.countIslands(
            [
                [0, 2, 1, 0, 0],
                [0, 5, 0, 0, 5],
                [0, 0, 1, 0, 0],
                [0, 1, 4, 7, 0],
                [0, 2, 0, 0, 8],
            ],
            1,
        )
        == 4
    )


if __name__ == "__main__":
    test_solution()
    print("✅ No.3619 全部测试通过")
