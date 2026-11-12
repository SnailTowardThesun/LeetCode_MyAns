"""
@file top150_52.py
@brief LeetCode 52. N-Queens II（N 皇后 II）— 面试经典 150 题 · 回溯

@题目描述
    n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此
    之间不能相互攻击（任意两个皇后不在同一行、同一列或同一斜线上）。

    给你一个整数 n，返回 n 皇后问题不同的解决方案的数量。

    提示：
    - 1 <= n <= 9

@示例
    示例 1：
    输入：n = 4
    输出：2
    解释：4 皇后问题存在两个不同的解法（官方题面给出两张 4×4 棋盘图，
    皇后 'Q' 分别位于两种互为镜像的摆法上，图略）。

    示例 2：
    输入：n = 1
    输出：1

@解题思路
    与 51（N 皇后）同题族，但只数解的数量、不需要输出棋盘，规模更小
    （n <= 9），是回溯计数的最纯样板：

    1. 按行回溯：每行恰好放置一个皇后，天然避开行冲突，递归参数即行号
       row，从 0 递增；
    2. 三个集合 O(1) 判占用：
       - cols：已占用的列号 col；
       - 主对角线（左上-右下方向）：row - col，同一条斜线上该差值恒定；
       - 副对角线（右上-左下方向）：row + col，同一条斜线上该和值恒定。
       候选列三集合均未占用才可放置，放置后标记、递归下一行、回溯撤销；
    3. 行指针走到 n 时，n 行全部合法放置，方案数 +1；无需维护棋盘路径。

    已知答案表（n = 1..9）：1, 0, 0, 2, 10, 4, 40, 92, 352
    （已用临时脚本以「三集合回溯」与「全排列暴力」两种独立实现交叉验证）。

    时间复杂度保守上界 O(n * n!)（每个非叶状态扫描 n 列，剪枝减少实际搜索量）；空间复杂度
    O(n)（递归深度 + 三个集合）。

来源：LeetCode
链接：https://leetcode.cn/problems/n-queens-ii/description/
"""


class Solution:
    def totalNQueens(self, n: int) -> int:
        def backtrack(row: int) -> int:
            if row == n:
                return 1
            else:
                count = 0
                for i in range(n):
                    if i in columns or row - i in diagonal1 or row + i in diagonal2:
                        continue
                    columns.add(i)
                    diagonal1.add(row - i)
                    diagonal2.add(row + i)
                    count += backtrack(row + 1)
                    columns.remove(i)
                    diagonal1.remove(row - i)
                    diagonal2.remove(row + i)
                return count

        columns = set()
        diagonal1 = set()
        diagonal2 = set()
        return backtrack(0)


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 2：1×1 棋盘唯一摆法 ----
    assert solution.totalNQueens(1) == 1

    # ---- n=2 / n=3 无解（皇后互相攻击无法避免） ----
    assert solution.totalNQueens(2) == 0
    assert solution.totalNQueens(3) == 0

    # ---- 官方示例 1：4 皇后恰有两个解 ----
    assert solution.totalNQueens(4) == 2

    # ---- n=5 / n=6：10 / 4 ----
    assert solution.totalNQueens(5) == 10
    assert solution.totalNQueens(6) == 4

    # ---- n=8 经典八皇后：92 ----
    assert solution.totalNQueens(8) == 92

    # ---- n=9 上界：352（注意：不是 10，已双脚本独立验证） ----
    assert solution.totalNQueens(9) == 352


if __name__ == "__main__":
    test_solution()
    print("✅ No.52 全部测试通过")
