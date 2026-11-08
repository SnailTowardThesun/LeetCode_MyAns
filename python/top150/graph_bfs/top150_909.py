"""
@file top150_909.py
@brief LeetCode 909. Snakes and Ladders（蛇梯棋）

@题目描述
    给你一个 n x n 的整数矩阵 board，方格按从 1 到 n^2 编号，以「牛耕式转行」
    （boustrophedon）方式放置——从左下角开始（即 board[n - 1][0]），每一行
    交替方向。

    从方格 1 出发，按如下规则移动：
    - 选择目标方格 next，编号范围 [curr + 1, min(curr + 6, n^2)]——模拟掷骰子，
      无论棋盘多大，目的地最多 6 个（掷出超过 n^2 的部分无效）；
    - 若 next 处有蛇或梯子（board 对应格 != -1），则必须传送到 board 上的
      目的地；否则移动到 next；
    - 蛇或梯子每次掷骰至多生效一次：若目的地是另一条蛇/梯子的起点，
      不再继续传送（不成链）；
    - 到达方格 n^2 时游戏结束。

    返回到达方格 n^2 所需的最少掷骰次数；无法到达则返回 -1。

    提示：
    - n == board.length == board[i].length，2 <= n <= 20
    - board[i][j] 的值是 -1 或范围 [1, n^2] 中的整数
    - 方格 1 和 n^2 不是任何蛇或梯子的起点

@示例
    示例 1：
    输入：board = [[-1,-1,-1,-1,-1,-1],
                   [-1,-1,-1,-1,-1,-1],
                   [-1,-1,-1,-1,-1,-1],
                   [-1,35,-1,-1,13,-1],
                   [-1,-1,-1,-1,-1,-1],
                   [-1,15,-1,-1,-1,-1]]
    输出：4
    解释：
    - 第 1 步：掷出 1，从方格 1 到方格 2，方格 2 有梯子，传送到方格 15；
    - 第 2 步：掷出 2，从方格 15 到方格 17，方格 17 有蛇，传送到方格 13；
    - 第 3 步：掷出 1，从方格 13 到方格 14，方格 14 有梯子，传送到方格 35；
    - 第 4 步：掷出 1，从方格 35 到最后一个方格 36。返回 4。

    示例 2：
    输入：board = [[-1,-1],[-1,3]]
    输出：1
    解释：掷出 3 直接到达方格 4（也可掷出 1 踩中方格 2 的梯子传送到 3，
         但仍需再掷一次，不是最优）。

@解题思路
    「最少掷骰次数」= 方格 1 到 n^2 在隐式图上的最短路，边权全为 1——BFS。

    1. 编号 -> 坐标转换（蛇形 + 自底向上，本题唯一的实现陷阱）：
       q, r = divmod(label - 1, n)，则 row = n - 1 - q（自底向上数行）；
       q 为偶数的行自左向右，col = r；q 为奇数的行自右向左，col = n - 1 - r；
    2. BFS 从方格 1 出发，visited 集合在入队时标记；出队 curr，枚举
       next ∈ [curr + 1, min(curr + 6, n^2)]；
    3. next 处 board 值 != -1 时实际落点为该值（必须传送，且只传送一次，
       不链式续传）；visited 记的也是传送后的实际落点，不是掷骰落点 next；
    4. 落点 == n^2 时返回当前步数 + 1；队空仍未到达则返回 -1。

    时间复杂度 O(n^2)（n^2 个方格各入队一次，每次枚举 6 个转移）；
    空间复杂度 O(n^2)（visited + 队列）。

来源：LeetCode
链接：https://leetcode.cn/problems/snakes-and-ladders/description/
"""

from collections import deque


class Solution:
    def snakesAndLadders(self, board: list[list[int]]) -> int:
        n = len(board)
        n2 = n * n

        def label_to_pos(label: int) -> tuple[int, int]:
            # 蛇形编号 -> (row, col)：自底向上数行，行方向逐行交替
            q, r = divmod(label - 1, n)
            row = n - 1 - q
            col = r if q % 2 == 0 else n - 1 - r
            return row, col

        visited = {1}
        queue = deque([(1, 0)])  # (方格编号, 已掷骰次数)
        while queue:
            curr, steps = queue.popleft()
            for nxt in range(curr + 1, min(curr + 6, n2) + 1):
                r, c = label_to_pos(nxt)
                # 踩中蛇/梯子必须传送，且只传送一次（不链式续传）
                dest = board[r][c] if board[r][c] != -1 else nxt
                if dest == n2:
                    return steps + 1
                # 判重记的是传送后的实际落点，不是掷骰落点 next
                if dest not in visited:
                    visited.add(dest)
                    queue.append((dest, steps + 1))
        return -1


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：梯子/蛇交替借用，4 步 ----
    board = [
        [-1, -1, -1, -1, -1, -1],
        [-1, -1, -1, -1, -1, -1],
        [-1, -1, -1, -1, -1, -1],
        [-1, 35, -1, -1, 13, -1],
        [-1, -1, -1, -1, -1, -1],
        [-1, 15, -1, -1, -1, -1],
    ]
    assert solution.snakesAndLadders(board) == 4

    # ---- 官方示例 2：一步掷到终点 ----
    assert solution.snakesAndLadders([[-1, -1], [-1, 3]]) == 1

    # ---- 全空盘：n^2 = 4，掷出 3 一步直达 ----
    assert solution.snakesAndLadders([[-1, -1], [-1, -1]]) == 1

    # ---- 3~8 号格全是送回 2 号的蛇：所有通路被锁死，不可达 ----
    assert solution.snakesAndLadders([[2, 2, -1], [2, 2, 2], [-1, -1, 2]]) == -1

    # ---- 4 号格有蛇回送，但 3 + 6 可直达 9：绕开蛇 2 步到达 ----
    assert solution.snakesAndLadders([[-1, -1, -1], [-1, -1, 2], [-1, -1, -1]]) == 2

    # ---- 踩中梯子起点必须传送：掷 2 落到 3 号梯子直达 4 ----
    assert solution.snakesAndLadders([[4, -1], [-1, 3]]) == 1


if __name__ == "__main__":
    test_solution()
    print("✅ No.909 全部测试通过")
