"""
@file top150_130.py
@brief LeetCode 130. Surrounded Regions（被围绕的区域）

@题目描述
    给你一个 m x n 的矩阵 board，由若干字符 'X' 和 'O' 组成，捕获所有被围绕的区域：
    - 连接：一个单元格与水平或垂直方向上相邻的单元格连接。
    - 区域：连接所有 'O' 的单元格来形成一个区域。
    - 围绕：如果您可以用 'X' 单元格连接这个区域，并且区域中没有任何单元格位于 board 边缘，
      则该区域被 'X' 单元格围绕。
    通过 原地 将输入矩阵中的所有 'O' 替换为 'X' 来 捕获被围绕的区域。你不需要返回任何值。

    提示：
    - m == board.length，n == board[i].length，1 <= m, n <= 200
    - board[i][j] 为 'X' 或 'O'

@示例
    示例 1：
    输入：board = [["X","X","X","X"],
                   ["X","O","O","X"],
                   ["X","O","X","X"],
                   ["X","X","X","X"]]
    输出：[["X","X","X","X"],
           ["X","X","X","X"],
           ["X","X","X","X"],
           ["X","X","X","X"]]
    解释：任何边界上的 'O' 都不会被填充为 'X'。任何不在边界上、也不与边界上的 'O'
         相连的 'O' 最终都会被填充为 'X'。只有水平或垂直相邻才算"相连"。

    示例 2：
    输入：board = [["X"]]
    输出：[["X"]]

@解题思路
    并查集：把 m×n 个格子按行优先编号（i*n+j）作为节点，初始各自成集。
    1. 遍历网格，对每个 'O' 格，只把它与「左」「上」两个相邻的 'O' 格合并——
       行优先遍历时，右、下两条边会在轮到那些格子时被连上，每条边恰好合并一次；
    2. 扫一遍四条边界，把边界格所在集合的根收进 edges 集合（X 格自成一集、从未与 O
       合并，混在里面无害）——这些分量"挨着边界"，不能翻；
    3. 再遍历一次网格，'O' 格若其根不在 edges 中，说明整块区域不与任何边界格连通，
       即被 'X' 围绕，原地改为 'X'。

    时间复杂度 O(mn·α(mn))，空间复杂度 O(mn)。

来源：LeetCode
链接：https://leetcode.cn/problems/surrounded-regions/description/
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
    def solve(self, board: list[list[str]]) -> None:
        """原地修改 board，不返回任何值。"""
        m, n = len(board), len(board[0])
        uf = UnionFind(m * n)
        for i in range(m):
            for j in range(n):
                if board[i][j] == "X":
                    continue
                # 行优先遍历只需连"左"和"上"：右边和下边的边轮到那些格子时自然会连，避免每条边合并两次
                if j > 0:
                    if board[i][j - 1] == "O":
                        uf.union(i * n + j, i * n + j - 1)
                if i > 0:
                    if board[i - 1][j] == "O":
                        uf.union(i * n + j, (i - 1) * n + j)
        edges = set()
        for i in [0, m - 1]:
            for j in range(n):
                edges.add(uf.find(i * n + j))
        for i in [0, n - 1]:
            for j in range(m):
                edges.add(uf.find(j * n + i))
        for i in range(m):
            for j in range(n):
                if board[i][j] != "O":
                    continue
                root = uf.find(i * n + j)
                if root not in edges:
                    board[i][j] = "X"


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    board = [
        ["X", "X", "X", "X"],
        ["X", "O", "O", "X"],
        ["X", "O", "X", "X"],
        ["X", "X", "X", "X"],
    ]
    solution.solve(board)
    assert board == [
        ["X", "X", "X", "X"],
        ["X", "X", "X", "X"],
        ["X", "X", "X", "X"],
        ["X", "X", "X", "X"],
    ]

    board = [["X"]]
    solution.solve(board)
    assert board == [["X"]]

    # ---- 边界：单格 'O' 本身就在边界上，不翻转 ----
    board = [["O"]]
    solution.solve(board)
    assert board == [["O"]]

    # ---- 边界：全是 'X'，无事发生 ----
    board = [["X", "X"], ["X", "X"]]
    solution.solve(board)
    assert board == [["X", "X"], ["X", "X"]]

    # ---- 边界：全是 'O'，每个格子都连到边界，全部保留 ----
    board = [["O", "O", "O"], ["O", "O", "O"], ["O", "O", "O"]]
    solution.solve(board)
    assert board == [["O", "O", "O"], ["O", "O", "O"], ["O", "O", "O"]]

    # ---- 边界：单行 / 单列，所有格子都位于边界 ----
    board = [["O", "X", "O", "O", "X"]]
    solution.solve(board)
    assert board == [["O", "X", "O", "O", "X"]]

    board = [["O"], ["X"], ["O"], ["O"]]
    solution.solve(board)
    assert board == [["O"], ["X"], ["O"], ["O"]]

    # ---- 两个互不相连的内部 'O'，都被围绕，都翻转 ----
    board = [
        ["X", "X", "X", "X", "X"],
        ["X", "O", "X", "O", "X"],
        ["X", "X", "X", "X", "X"],
    ]
    solution.solve(board)
    assert board == [
        ["X", "X", "X", "X", "X"],
        ["X", "X", "X", "X", "X"],
        ["X", "X", "X", "X", "X"],
    ]

    # ---- 内部区域通过一条"管道"连到底边，整块保留 ----
    board = [
        ["X", "X", "X", "X", "X"],
        ["X", "O", "O", "X", "X"],
        ["X", "X", "O", "O", "X"],
        ["X", "X", "X", "O", "X"],
    ]
    solution.solve(board)
    assert board == [
        ["X", "X", "X", "X", "X"],
        ["X", "O", "O", "X", "X"],
        ["X", "X", "O", "O", "X"],
        ["X", "X", "X", "O", "X"],
    ]

    # ---- 一块被围绕 + 一块连边界：只翻前者 ----
    board = [
        ["X", "X", "X", "X", "X", "X"],
        ["X", "O", "O", "X", "O", "X"],
        ["X", "X", "X", "X", "O", "X"],
        ["X", "X", "X", "X", "O", "O"],
    ]
    solution.solve(board)
    assert board == [
        ["X", "X", "X", "X", "X", "X"],
        ["X", "X", "X", "X", "O", "X"],
        ["X", "X", "X", "X", "O", "X"],
        ["X", "X", "X", "X", "O", "O"],
    ]

    # ---- 对角线不算相连：中心 'O' 只与边界 'O' 斜向接触，仍被围绕 ----
    board = [
        ["O", "X", "X"],
        ["X", "O", "X"],
        ["X", "X", "O"],
    ]
    solution.solve(board)
    assert board == [
        ["O", "X", "X"],
        ["X", "X", "X"],
        ["X", "X", "O"],
    ]

    # ---- 'X' 环内的 2x2 'O' 块整体翻转 ----
    board = [
        ["X", "X", "X", "X"],
        ["X", "O", "O", "X"],
        ["X", "O", "O", "X"],
        ["X", "X", "X", "X"],
    ]
    solution.solve(board)
    assert board == [
        ["X", "X", "X", "X"],
        ["X", "X", "X", "X"],
        ["X", "X", "X", "X"],
        ["X", "X", "X", "X"],
    ]

    # ---- 'O' 环包住一个内部 'X'：环连边界全部保留，中心 'X' 原样 ----
    board = [
        ["O", "O", "O"],
        ["O", "X", "O"],
        ["O", "O", "O"],
    ]
    solution.solve(board)
    assert board == [
        ["O", "O", "O"],
        ["O", "X", "O"],
        ["O", "O", "O"],
    ]

    # ---- 蛇形：从上边界蜿蜒到内部，整条路径保留；旁边孤立的 'O' 翻转 ----
    board = [
        ["X", "O", "X", "X", "X"],
        ["X", "O", "O", "O", "X"],
        ["X", "X", "X", "O", "X"],
        ["X", "O", "X", "O", "X"],
        ["X", "X", "X", "X", "X"],
    ]
    solution.solve(board)
    assert board == [
        ["X", "O", "X", "X", "X"],
        ["X", "O", "O", "O", "X"],
        ["X", "X", "X", "O", "X"],
        ["X", "X", "X", "O", "X"],
        ["X", "X", "X", "X", "X"],
    ]


if __name__ == "__main__":
    test_solution()
    print("✅ No.130 全部测试通过")
