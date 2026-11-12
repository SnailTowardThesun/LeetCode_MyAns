"""
@file top150_39.py
@brief LeetCode 39. Combination Sum（组合总和）——面试经典 150 题 / 回溯分类

@题目描述
    给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target，找出
    candidates 中可以使数字和为目标数 target 的所有 不同组合，并以列表形式
    返回。candidates 的同一个数字可以 无限制重复被选取。如果至少一个数字的
    被选数量不同，则两种组合是不同的。

    可以按任意顺序返回这些组合。

    提示：
    - 1 <= candidates.length <= 30
    - 2 <= candidates[i] <= 40，且 candidates 中的元素互不相同
    - 1 <= target <= 40
    - 题目保证符合要求的组合数少于 150 个

@示例
    示例 1：
    输入：candidates = [2,3,6,7], target = 7
    输出：[[2,2,3],[7]]
    解释：2 和 3 是候选，2 + 2 + 3 = 7；7 也是候选，7 = 7。其余组合不满足。

    示例 2：
    输入：candidates = [2,3,5], target = 8
    输出：[[2,2,2,2],[2,3,3],[3,5]]

    示例 3：
    输入：candidates = [2], target = 1
    输出：[]

@解题思路
    排序 + 回溯（递归带 start 索引）：

    1. 先对 candidates 升序排序，为剪枝做准备（排序不改变解集，因为按
       任意顺序返回均可）；
    2. 回溯递归携带 start 索引——每层只从「当前及之后」的候选里选，
       强制组合内下标单调不减，保证得到的是组合（非排列）且不重复；
    3. 同一元素可重复选：递归时传 i 而非 i+1（允许下一层继续选第 i 个）；
    4. 剪枝：若 当前和 + 候选值 > target，因已排序，后面候选只会更大，
       直接 break 整层循环；
    5. 当前和恰好等于 target 时收集路径副本，回溯返回。

    时间复杂度：指数级（搜索树规模，与满足条件的组合数相关）；
    辅助空间：O(N + target / min(candidates))，N 为候选数，包含 sorted
    产生的副本、排序临时空间、递归栈及路径，不计输出。

来源：LeetCode
链接：https://leetcode.cn/problems/combination-sum/description/
"""


class Solution:
    def combinationSum(self, candidates: list[int], target: int) -> list[list[int]]:
        candidates = sorted(candidates)  # 升序排序，为剪枝做准备
        ret: list[list[int]] = []
        path: list[int] = []

        def backtrack(start: int, remaining: int) -> None:
            if remaining == 0:  # 当前和恰好等于 target，收集路径副本
                ret.append(path[:])
                return
            for i in range(start, len(candidates)):
                # 剪枝：已排序，当前候选已超缺口，后面只会更大
                if candidates[i] > remaining:
                    break
                path.append(candidates[i])
                backtrack(i, remaining - candidates[i])  # 传 i 非 i+1：允许重复选同一元素
                path.pop()

        backtrack(0, target)
        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：2+2+3 与 7 ----
    assert sorted(sorted(x) for x in solution.combinationSum([2, 3, 6, 7], 7)) == [[2, 2, 3], [7]]

    # ---- 官方示例 2：恰好三种组合 ----
    assert sorted(sorted(x) for x in solution.combinationSum([2, 3, 5], 8)) == [
        [2, 2, 2, 2],
        [2, 3, 3],
        [3, 5],
    ]

    # ---- 官方示例 3：最小候选 2 > target 1，无解 ----
    assert solution.combinationSum([2], 1) == []

    # ---- 同一元素重复选：3+3+3 = 9 ----
    assert sorted(sorted(x) for x in solution.combinationSum([3], 9)) == [[3, 3, 3]]

    # ---- 乱序输入：与官方示例 1 同解 ----
    assert sorted(sorted(x) for x in solution.combinationSum([7, 3, 2], 7)) == [[2, 2, 3], [7]]

    # ---- 无解：2a+4b=11 无非负整数解 ----
    assert solution.combinationSum([2, 4], 11) == []

    # ---- 混合重复：5+5+5 与 10+5 ----
    assert sorted(sorted(x) for x in solution.combinationSum([5, 10], 15)) == [[5, 5, 5], [5, 10]]


if __name__ == "__main__":
    test_solution()
    print("✅ No.39 全部测试通过")
