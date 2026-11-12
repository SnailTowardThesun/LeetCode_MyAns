"""
@file top150_46.py
@brief LeetCode 46. Permutations（全排列）—— 面试经典 150 题 · 回溯分类

@题目描述
    给定一个不含重复数字的数组 nums，返回其所有可能的全排列。可以按任意
    顺序返回答案。

    提示：
    - 1 <= nums.length <= 6
    - -10 <= nums[i] <= 10
    - nums 中的所有整数 互不相同

@示例
    示例 1：
    输入：nums = [1,2,3]
    输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

    示例 2：
    输入：nums = [0,1]
    输出：[[0,1],[1,0]]

    示例 3：
    输入：nums = [1]
    输出：[[1]]

@解题思路
    把全排列看作「逐个位置选数」的决策树，用 path + used 数组回溯：
    1. 每层枚举所有下标，跳过 used[i] 为 True 的元素；
    2. 选择 nums[i] 时标记 used[i] 并追加到 path，递归填下一个位置；
    3. 返回时弹出 path 尾元素并撤销 used[i]，让兄弟分支独立选择；
    4. path 长度达到 n 时收集副本。即使输入只有一个元素，结果也不与
       输入共享列表；共 n! 个排列，每条路径唯一，无需额外去重。

    时间复杂度 O(n x n!)；辅助空间 O(n)（递归栈、path、used），
    不计 O(n x n!) 的输出空间。

来源：LeetCode
链接：https://leetcode.cn/problems/permutations/description/
"""


class Solution:
    def permute(self, nums: list[int]) -> list[list[int]]:
        ret: list[list[int]] = []
        path: list[int] = []
        used = [False] * len(nums)

        def backtrack() -> None:
            if len(path) == len(nums):
                ret.append(path.copy())
                return
            for i, value in enumerate(nums):
                if used[i]:
                    continue
                used[i] = True
                path.append(value)
                backtrack()
                path.pop()
                used[i] = False

        backtrack()
        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：[1,2,3] 的全部 6 个排列 ----
    assert sorted(solution.permute([1, 2, 3])) == [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]

    # ---- 官方示例 2：[0,1] 两个排列 ----
    assert sorted(solution.permute([0, 1])) == [[0, 1], [1, 0]]

    # ---- 官方示例 3：单元素只有自身 ----
    assert sorted(solution.permute([1])) == [[1]]

    # ---- 多元素：4 个互异数 -> 4! = 24 个排列，且含完全逆序的一个 ----
    result_4 = sorted(solution.permute([1, 2, 3, 4]))
    assert len(result_4) == 24
    assert [4, 3, 2, 1] in result_4

    # ---- 结果必须独立于输入，单元素也不能直接返回输入列表的引用 ----
    nums = [1]
    result = solution.permute(nums)
    result[0][0] = 9
    assert nums == [1]

    # ---- 约束上界：与标准库的全部 720 个排列逐项核对，兼查重复和漏解 ----
    from itertools import permutations

    nums = list(range(6))
    result = solution.permute(nums)
    assert sorted(map(tuple, result)) == list(permutations(nums))
    assert nums == list(range(6))

    # ---- 含负数：互异性与符号无关，仍是 3! = 6 个 ----
    assert sorted(solution.permute([0, -1, 1])) == [
        [-1, 0, 1],
        [-1, 1, 0],
        [0, -1, 1],
        [0, 1, -1],
        [1, -1, 0],
        [1, 0, -1],
    ]


if __name__ == "__main__":
    test_solution()
    print("✅ No.46 全部测试通过")
