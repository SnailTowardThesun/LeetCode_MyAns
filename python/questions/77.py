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

@解题思路（待实现）
    1. 回溯 DFS：维护当前路径 path 与枚举起点 start，
       每次从 start..n 中选一个数加入 path，递归后回溯撤销
    2. 收集条件：len(path) == k 时把 path 的拷贝加入结果集
    3. 剪枝：剩余可用数字 n - start + 1 不足以凑满 k 个时提前返回

    时间复杂度 O(C(n,k) * k)，空间复杂度 O(k)（递归栈 + path）

来源：LeetCode
链接：https://leetcode.cn/problems/combinations/description/
"""


class Solution:
    def combine(self, n: int, k: int) -> list[list[int]]:
        # TODO: 按上述回溯思路实现
        ...


def test_solution() -> None:
    solution = Solution()
    assert solution is not None  # TODO: 实现后替换为真实测试用例（含边界情况）


if __name__ == "__main__":
    s = Solution()
    print("TODO: 实现后运行", s.combine(4, 2))
