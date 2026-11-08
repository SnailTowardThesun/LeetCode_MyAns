"""
@file top150_79.py
@brief LeetCode 79. Word Search（单词搜索）—— top150 面试经典 150 题「回溯」分类

@题目描述
    给定一个 m x n 网格 board 和一个字符串 word。如果 word 存在于网格中返回
    true，否则返回 false。单词必须按照字母顺序，通过上下左右相邻单元格内的字母
    构成一条路径（从一个单元格开始，每一步可以移动到相邻的一个单元格）；同一个
    单元格内的字母在一个单词中不允许被重复使用。

    提示：
    - m == board.length，n == board[i].length
    - 1 <= m, n <= 6
    - 1 <= word.length <= 15
    - board 与 word 仅由大小写英文字母组成（大小写敏感）

@示例
    示例 1：
    输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
    输出：true

    示例 2：
    输入：board 同示例 1，word = "SEE"
    输出：true

    示例 3：
    输入：board 同示例 1，word = "ABCB"
    输出：false（回到 B 必须复用已走过的格子）

    示例 4：
    输入：board = [["a","b"],["c","d"]], word = "abcd"
    输出：false（b 之后无相邻的 c）

@解题思路
    回溯（DFS）+ 原地标记：

    1. 枚举每个等于 word[0] 的格子作为起点，逐一启动 DFS 回溯；
    2. 当前格匹配 word[i] 后，向上下左右四个方向扩展，尝试匹配 word[i+1]；
    3. 进入格子时原地标记（如置 '#'），防止同一条路径内复用同一单元格；
       该分支探索完毕、返回之前必须恢复原字母——这正是回溯的「撤销选择」，
       若不恢复，失败分支留下的标记会污染棋盘，导致后续分支误判不可走；
    4. 匹配到最后一个字符（i == len(word) - 1）立即返回 True，逐层短路
       返回，不做多余搜索。

    网格最大 6x6、词长最长 15，递归深度至多 15，无深递归风险。

    时间复杂度 O(m·n·3^L)：L 为词长，起点至多 m·n 个，首步 4 个方向、之后
    每步至多 3 个方向（不回头走刚来的格子）；空间复杂度 O(L)（递归栈深度，
    原地标记不占额外空间）。

来源：LeetCode
链接：https://leetcode.cn/problems/word-search/description/
"""


class Solution:
    def exist(self, board: list[list[str]], word: str) -> bool:
        # TODO: 枚举每个等于 word[0] 的格子作为起点，逐一启动 DFS 回溯
        # TODO: 当前格匹配 word[i] 后向上下左右四方向扩展，尝试匹配 word[i+1]
        # TODO: 进入格子时原地标记（如置 '#'）防止路径内复用，返回前恢复原字母（撤销选择）
        # TODO: 匹配到最后一个字符立即返回 True 短路，避免多余搜索
        def dfs(board, i, j, no, word, visited):
            m, n = len(board), len(board[0])
            if no == len(word) - 1:
                return True
            no += 1
            if i + 1 < m:
                if board[i + 1][j] == word[no] and not visited[i + 1][j]:
                    visited[i + 1][j] = 1
                    if dfs(board, i + 1, j, no, word, visited):
                        return True
                    visited[i + 1][j] = 0
            if i - 1 >= 0:
                if board[i - 1][j] == word[no] and not visited[i - 1][j]:
                    visited[i - 1][j] = 1
                    if dfs(board, i - 1, j, no, word, visited):
                        return True
                    visited[i - 1][j] = 0
            if j + 1 < n:
                if board[i][j + 1] == word[no] and not visited[i][j + 1]:
                    visited[i][j + 1] = 1
                    if dfs(board, i, j + 1, no, word, visited):
                        return True
                    visited[i][j + 1] = 0
            if j - 1 >= 0:
                if board[i][j - 1] == word[no] and not visited[i][j - 1]:
                    visited[i][j - 1] = 1
                    if dfs(board, i, j - 1, no, word, visited):
                        return True
                    visited[i][j - 1] = 0

            return False

        m, n = len(board), len(board[0])
        if len(word) > m * n:
            return False
        for i in range(m):
            for j in range(n):
                visited = [[0] * n for _ in range(m)]
                visited[i][j] = 1
                if board[i][j] == word[0]:
                    if dfs(board, i, j, 0, word, visited):
                        return True

        return False


def test_solution() -> None:
    solution = Solution()
    assert not solution.exist([["a", "a"], ["A", "A"]], "aaa")

    assert not solution.exist([["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]], "ABCB")

    # ---- 官方示例 1：ABCCED 沿 A(0,0)→B→C→C→E→D 走通 ----
    assert solution.exist([["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]], "ABCCED")

    # ---- 官方示例 2：SEE 从 S(1,3) 出发，走下方 E(2,3)→E(2,2) ----
    assert solution.exist([["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]], "SEE")

    # ---- 官方示例 3：ABCB 回到 B 必须复用已走过的格子，false ----

    # ---- 官方示例 4：2x2 小写棋盘，b 之后无相邻 c，false ----
    assert not solution.exist([["a", "b"], ["c", "d"]], "abcd")

    # ---- 大小写敏感：同官方示例 1 棋盘，小写 abcced 匹配不到，false ----
    assert not solution.exist([["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]], "abcced")

    # ---- 单格棋盘：命中 ----
    assert solution.exist([["a"]], "a")

    # ---- 单格棋盘：未命中 ----
    assert not solution.exist([["a"]], "b")

    # ---- 回溯必备用例：word = "ABCESEEE" ----
    # C 之后棋盘上存在会走进死胡同的 E 分支，必须撤销标记回溯换路才能走通；
    # 已程序化验证：只标记不恢复（不会撤销选择）的错误实现在本例上误判
    # False，而它在官方示例 1 上仍能通过——本例专防此类缺陷
    assert solution.exist([["A", "B", "C", "E"], ["S", "F", "E", "S"], ["A", "D", "E", "E"]], "ABCESEEE")


if __name__ == "__main__":
    test_solution()
    print("✅ No.79 全部测试通过")
