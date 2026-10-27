"""
@file 3963.py
@brief LeetCode 3963. Create Grid With Exactly One Path（构造恰好一条路径的网格）

@题目描述
    给你两个整数 m 和 n，分别表示网格的行数和列数。
    请你构造任意一个只包含字符 '.' 和 '#' 的 m x n 网格，其中：
    - '.' 表示空单元格；
    - '#' 表示障碍物单元格。

    要求从左上角单元格 (0, 0) 走到右下角单元格 (m-1, n-1) 的有效路径恰好有一条。
    有效路径满足：每一步只能向右或向下移动，且只能经过空单元格。

    返回任意一个满足条件的网格。答案不唯一，判题程序会验证你构造的网格
    是否满足上述条件，无需与示例输出一致。

    提示：
    - 1 <= m, n <= 25

@示例
    示例 1：
    输入：m = 2, n = 3
    输出：["..#", "#.."]
    解释：唯一路径为 (0,0) -> (0,1) -> (1,1) -> (1,2)。

    示例 2：
    输入：m = 3, n = 3
    输出：["..#", "#..", "##."]
    解释：唯一路径为 (0,0) -> (0,1) -> (1,1) -> (1,2) -> (2,2)。

    示例 3：
    输入：m = 1, n = 4
    输出：["...."]
    解释：唯一路径为 (0,0) -> (0,1) -> (0,2) -> (0,3)。

@解题思路
    "恰好一条路径"翻译成构造语言：让每个可达空格都只有一种来路，任何岔路都被
    '#' 封死。最简单的是「Γ」形走廊：
    - 第 0 行全部填 '.'：从 (0,0) 只能一路向右走到 (0, n-1)（第 0 行下面的
     格子全是 '#'，中途无法向下）；
    - 其余每行填 '#' * (n-1) + '.'：只有最后一列留空，从 (0, n-1) 一路向下
      走到 (m-1, n-1)。
    全图唯一的走法就是"先右到底、再下到底"，路径数恰好为 1。
    两种退化被同一份代码自然覆盖，无需特判：m=1 时只剩全 '.' 的顶行；
    n=1 时每行 '#' * 0 + '.' 退化为单列全 '.'。

    时间复杂度 O(m·n)（构造 m 行字符串），空间复杂度 O(m·n)（返回的网格）

来源：LeetCode
链接：https://leetcode.cn/problems/create-grid-with-exactly-one-path/description/
"""


class Solution:
    def createGrid(self, m: int, n: int) -> list[str]:
        top = "." * n
        line = "#" * (n - 1) + "."
        ret = [top]
        for _ in range(m - 1):
            ret.append(line)
        return ret


def count_paths(grid: list[str]) -> int:
    """统计从 (0,0) 到 (m-1,n-1) 只向右/向下、只走 '.' 的路径数（判题同款验证逻辑）。"""
    m, n = len(grid), len(grid[0])
    dp = [[0] * n for _ in range(m)]
    dp[0][0] = 1 if grid[0][0] == "." else 0
    for i in range(m):
        for j in range(n):
            if grid[i][j] == "#":
                continue
            if i > 0:
                dp[i][j] += dp[i - 1][j]
            if j > 0:
                dp[i][j] += dp[i][j - 1]
    return dp[m - 1][n - 1]


def assert_valid_grid(grid: list[str], m: int, n: int) -> None:
    """答案不唯一：像判题程序一样按性质验证，而非比对具体输出。"""
    assert isinstance(grid, list), f"应返回 list[str]，实际 {type(grid).__name__}"
    assert len(grid) == m, f"行数应为 {m}，实际 {len(grid)}"
    assert all(isinstance(row, str) and len(row) == n for row in grid), f"每行长度应为 {n}"
    assert all(set(row) <= {".", "#"} for row in grid), "只能包含 '.' 和 '#'"
    assert count_paths(grid) == 1, "从左上到右下应恰好有一条路径"


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例（答案不唯一，按性质验证） ----
    assert_valid_grid(solution.createGrid(2, 3), 2, 3)
    assert_valid_grid(solution.createGrid(3, 3), 3, 3)
    assert_valid_grid(solution.createGrid(1, 4), 1, 4)

    # ---- 最小网格：1x1，路径就是起点本身 ----
    assert_valid_grid(solution.createGrid(1, 1), 1, 1)

    # ---- 单行 / 单列：任何 '#' 都会挡死唯一通道，必须全 '.' ----
    assert_valid_grid(solution.createGrid(1, 25), 1, 25)
    assert_valid_grid(solution.createGrid(25, 1), 25, 1)

    # ---- 最小方形 2x2：全 '.' 有两条路，必须用障碍压到一条 ----
    assert_valid_grid(solution.createGrid(2, 2), 2, 2)

    # ---- 窄长条：岔路多、障碍要交错放 ----
    assert_valid_grid(solution.createGrid(2, 25), 2, 25)
    assert_valid_grid(solution.createGrid(25, 2), 25, 2)

    # ---- 规模上限 25x25 ----
    assert_valid_grid(solution.createGrid(25, 25), 25, 25)


if __name__ == "__main__":
    test_solution()
    print("✅ No.3963 全部测试通过")
