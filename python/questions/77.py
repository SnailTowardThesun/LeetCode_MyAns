"""
@file 77.py
@brief LeetCode 77. 组合（Combinations）

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
    解释：[1, n] = [1, 2, 3, 4] 中取 2 个数的所有组合。

    示例 2：
    输入：n = 1, k = 1
    输出：[[1]]

@解题思路
    1. 分治递归 dfs(arr, k)：枚举组合的首元素 start = arr[i]，
       其余 k-1 个数从后缀 arr[i+1:] 中递归选取
    2. 边界：k == 1 时每个元素自成一组；k > len(arr) 时无解返回空；
       k == len(arr) 时只剩「全选」一种
    3. 上层用 [start, *c] 把首元素与子组合逐个拼接收集

    时间复杂度 O(C(n,k) * k)，空间复杂度 O(k)（递归栈）

来源：LeetCode
链接：https://leetcode.cn/problems/combinations/description/
"""

from math import comb


class Solution:
    def combine(self, n: int, k: int) -> list[list[int]]:
        def dfs(arr: list[int], k: int) -> list[list[int]]:
            if k == 1:
                return [[i] for i in arr]
            if k > len(arr):
                return []
            if k == len(arr):
                return [arr]

            ret = []
            for i in range(len(arr)):
                start = arr[i]
                combines = dfs(arr[i + 1 :], k - 1)
                for c in combines:
                    ret.append([start, *c])

            return ret

        arr = list(range(n + 1))[1:]
        return dfs(arr, k)


def test_combine() -> None:
    solution = Solution()

    # 官方示例 1：n = 4, k = 2（题目允许任意顺序，排序后比较）
    assert sorted(solution.combine(4, 2)) == [
        [1, 2],
        [1, 3],
        [1, 4],
        [2, 3],
        [2, 4],
        [3, 4],
    ]

    # 官方示例 2：n = 1, k = 1
    assert sorted(solution.combine(1, 1)) == [[1]]

    # 边界：k = 1，每个数单独成组
    assert sorted(solution.combine(3, 1)) == [[1], [2], [3]]

    # 边界：k = n，只能全选
    assert sorted(solution.combine(3, 3)) == [[1, 2, 3]]

    # 规模较大：C(5, 3) = 10 个组合
    assert sorted(solution.combine(5, 3)) == [
        [1, 2, 3],
        [1, 2, 4],
        [1, 2, 5],
        [1, 3, 4],
        [1, 3, 5],
        [1, 4, 5],
        [2, 3, 4],
        [2, 3, 5],
        [2, 4, 5],
        [3, 4, 5],
    ]

    # 组合数量与数学组合数一致
    assert len(solution.combine(6, 2)) == comb(6, 2)
    assert len(solution.combine(10, 5)) == comb(10, 5)


if __name__ == "__main__":
    s = Solution()
    print(s.combine(4, 2))
