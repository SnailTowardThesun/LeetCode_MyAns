"""
@file top150_77.py
@brief LeetCode 77. Combinations（组合）——top150 回溯分类

@题目描述
    给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。

    可以按任何顺序返回答案。

    提示：
    - 1 <= n <= 20
    - 1 <= k <= n

@示例
    示例 1：
    输入：n = 4, k = 2
    输出：[[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
    解释：[1,n] 中所有可能的 2 个数的组合，共 C(4,2) = 6 个。

    示例 2：
    输入：n = 1, k = 1
    输出：[[1]]

@解题思路
    组合问题不区分顺序（{1,2} 与 {2,1} 是同一个组合），关键是让路径严格
    递增以消除重复——本实现只传下一个候选值 start，共用一条 path：

    1. path 收满 k 个数时收集副本；
    2. 设还缺 remaining 个数，当前候选 value 最大只能为 n-remaining+1，
       否则后面不足 remaining-1 个数，直接剪掉；
    3. 选择 value 后递归 backtrack(value+1)，返回时弹出它；不切片、
       不缓存子问题的全部组合，辅助空间只随路径深度增长；
    4. 结果共 C(n, k) 个组合。

    时间复杂度 O(C(n,k) x k)（每个组合构造 O(k)）；空间复杂度 O(k)
    （递归深度，不计输出）。

来源：LeetCode
链接：https://leetcode.cn/problems/combinations/description/
"""


class Solution:
    def combine(self, n: int, k: int) -> list[list[int]]:
        ret: list[list[int]] = []
        path: list[int] = []

        def backtrack(start: int) -> None:
            remaining = k - len(path)
            if remaining == 0:
                ret.append(path.copy())
                return
            # 选 value 后，后面还须留出 remaining - 1 个数。
            for value in range(start, n - remaining + 2):
                path.append(value)
                backtrack(value + 1)
                path.pop()

        backtrack(1)
        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：n=4, k=2，C(4,2)=6 个组合 ----
    assert sorted(solution.combine(4, 2)) == [[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]]

    # ---- 官方示例 2：n=1, k=1，唯一组合 ----
    assert sorted(solution.combine(1, 1)) == [[1]]

    # ---- n=5, k=3：C(5,3)=10 个，抽查首尾边界组合 ----
    result_5_3 = sorted(solution.combine(5, 3))
    assert len(result_5_3) == 10
    assert [1, 2, 5] in result_5_3  # 跨度最大：含最小起点与最大终点
    assert [3, 4, 5] in result_5_3  # 最晚起点的组合

    # ---- k=n：只能选满 [1,n]，唯一组合 ----
    assert sorted(solution.combine(4, 4)) == [[1, 2, 3, 4]]

    # ---- 上界规模 n=20, k=1：20 个单元素组合 ----
    result_20_1 = sorted(solution.combine(20, 1))
    assert len(result_20_1) == 20
    assert result_20_1 == [[i] for i in range(1, 21)]

    # ---- 小规模穷举对照标准库，覆盖剪枝上界、漏解与重复解 ----
    from itertools import combinations

    for n in range(1, 9):
        for k in range(1, n + 1):
            assert sorted(map(tuple, solution.combine(n, k))) == list(combinations(range(1, n + 1), k))


if __name__ == "__main__":
    test_solution()
    print("✅ No.77 全部测试通过")
