"""
@file top150_427.py
@brief LeetCode 427. 建立四叉树

@题目描述
    给你一个 n × n 矩阵 grid，矩阵中每个元素都是 0 或 1（n 是 2 的幂）。请你将 grid 表示为四叉树，返回根节点。

    四叉树节点定义：
    - val：节点存储的值（叶子节点为对应区域的值 0/1）
    - isLeaf：该节点是否为叶节点
    - topLeft / topRight / bottomLeft / bottomRight：四个孩子指针

    构建规则：
    如果当前要表示的网格区域内所有值相同（全 0 或全 1），则 isLeaf = True，val 为该值，四个孩子均为空；
    否则 isLeaf = False（此时 val 可为任意值，判题时忽略），把区域分成四个子区域并递归构建四个孩子。

    输出说明：四叉树以层序遍历序列化，每个节点输出为 [isLeaf, val]，孩子顺序为
    topLeft、topRight、bottomLeft、bottomRight，叶节点不再展开。

@示例
    示例 1：
    输入：grid = [[0,1],[1,0]]
    输出：[[0,1],[1,0],[1,1],[1,1],[1,0]]

    示例 2：
    输入：grid = [[1,1,1,1,0,0,0,0],
                 [1,1,1,1,0,0,0,0],
                 [1,1,1,1,1,1,1,1],
                 [1,1,1,1,1,1,1,1],
                 [1,1,1,1,0,0,0,0],
                 [1,1,1,1,0,0,0,0],
                 [1,1,1,1,0,0,0,0],
                 [1,1,1,1,0,0,0,0]]
    输出：[[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
    解释：n = 8；topLeft 与 bottomLeft 全 1、bottomRight 全 0，均为叶节点；topRight 需再分四块。
    （本文件测试使用省略 null 填充的等价层序表示）

    提示：n == grid.length == grid[i].length，n == 2^x（0 <= x <= 6），grid 中只含 0/1

@解题思路
    分治递归：dfs(r0, c0, r1, c1) 处理左上角 (r0, c0)、右下角 (r1, c1) 的半开区间子矩阵：
    1. 用 all() 判断区域内值是否全相同，相同则直接建叶节点（val 取该值），四个孩子为空；
    2. 否则按行列中点切成左上/右上/左下/右下四块分别递归——注意左下块的列起点是 c0 而非 r0，
       传混后空区间上 all() 恒为 True，会凭空多出叶节点；
    3. 非叶节点的 val 无意义（判题时忽略）。

    时间复杂度 O(n² log n)（每层至多全量扫描 O(n²)，共 log n 层；改用二维前缀和判同值可优化到 O(n²)），
    空间复杂度 O(log n)（递归栈）

来源：LeetCode
链接：https://leetcode.cn/problems/construct-quad-tree/description/
"""

from leetcode_common import QuadNode, quad_to_list


class Solution:
    def construct(self, grid: list[list[int]]) -> QuadNode:
        def dfs(r0, c0, r1, c1):
            if all(grid[r0][c0] == grid[i][j] for i in range(r0, r1) for j in range(c0, c1)):
                return QuadNode(grid[r0][c0] == 1, True)
            return QuadNode(
                True,
                False,
                dfs(r0, c0, (r0 + r1) // 2, (c0 + c1) // 2),
                dfs(r0, (c0 + c1) // 2, (r0 + r1) // 2, c1),
                dfs((r0 + r1) // 2, c0, r1, (c0 + c1) // 2),
                dfs((r0 + r1) // 2, (c0 + c1) // 2, r1, c1),
            )

        return dfs(0, 0, len(grid), len(grid))


def _normalize(levels: list[list[int]]) -> list[list[int]]:
    """非叶节点的 val 判题时忽略，比较前统一置 1（与官方序列化展示一致）。"""
    return [[1, v] if is_leaf == 1 else [0, 1] for is_leaf, v in levels]


def test_solution() -> None:
    solution = Solution()

    # 官方示例 1：2x2 对角交错，根非叶，四个孩子均为叶
    assert _normalize(quad_to_list(solution.construct([[0, 1], [1, 0]]))) == [
        [0, 1],
        [1, 0],
        [1, 1],
        [1, 1],
        [1, 0],
    ]

    # 官方示例 2：8x8，官方输出含 null 填充，此处为等价的去 null 层序表示
    grid8 = [
        [1, 1, 1, 1, 0, 0, 0, 0],
        [1, 1, 1, 1, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1, 0, 0, 0, 0],
        [1, 1, 1, 1, 0, 0, 0, 0],
        [1, 1, 1, 1, 0, 0, 0, 0],
        [1, 1, 1, 1, 0, 0, 0, 0],
    ]
    assert _normalize(quad_to_list(solution.construct(grid8))) == [
        [0, 1],
        [1, 1],
        [0, 1],
        [1, 1],
        [1, 0],
        [1, 0],
        [1, 0],
        [1, 1],
        [1, 1],
    ]

    # 边界：1x1 矩阵本身就是叶节点
    assert _normalize(quad_to_list(solution.construct([[0]]))) == [[1, 0]]

    # 全等值：无论规模多大都是单叶节点
    assert _normalize(quad_to_list(solution.construct([[1, 1], [1, 1]]))) == [[1, 1]]
    assert _normalize(quad_to_list(solution.construct([[0, 0], [0, 0]]))) == [[1, 0]]
    assert _normalize(quad_to_list(solution.construct([[1] * 4 for _ in range(4)]))) == [[1, 1]]

    # 4x4 仅左上角为 0：根与 topLeft 非叶，topLeft 的左上孩子为 0 叶，其余为 1 叶
    grid_corner = [[1] * 4 for _ in range(4)]
    grid_corner[0][0] = 0
    assert _normalize(quad_to_list(solution.construct(grid_corner))) == [
        [0, 1],
        [0, 1],
        [1, 1],
        [1, 1],
        [1, 1],
        [1, 0],
        [1, 1],
        [1, 1],
        [1, 1],
    ]


if __name__ == "__main__":
    test_solution()
    print("✅ 427 全部测试通过")
