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
    top150 回溯分类第一题。把全排列看作「逐个位置选数」的决策树：本实现
    采用「固定首元素 + 递归剩余」的自顶向下分解，与经典的 used 数组回溯
    在决策树上是同一棵树，只是状态口径不同。

    1. dfs(nums) 返回 nums 的全部排列：单元素即递归终点，返回 [nums]
       本身（天然是副本）；
    2. 一般情况：枚举首位数字 cur = nums[i]——拷贝一份列表并 remove 掉
       cur（相当于 used 标记的"排除已选"），对剩余 n-1 个数递归求全
       排列；回程时把 cur insert(0, ...) 插回每个子排列头部，即得
       「以 cur 开头」的全部排列；
    3. 每层枚举 n 个不同的首位，互不重叠，恰好拼出 n! 个排列，无重复；
       拷贝列表代替了「选择/撤销」对——remove 是选择，新列表天然隔离
       了兄弟分支，无需显式撤销；
    4. 等价标准写法：path + used 数组回溯（每层从 0 扫到 n-1、used 剪枝，
       收集时拷贝 path）；另有交换法（swap 原地生成）与
       itertools.permutations 可选。

    时间复杂度 O(n x n!)：共 n! 个排列，每个排列构造 O(n)；拷贝列表使
    每层多 O(n)，仍被 n! 主项吸收。
    空间复杂度 O(n^2) 级：递归深度 O(n)，每层持有 O(n) 的列表拷贝。

来源：LeetCode
链接：https://leetcode.cn/problems/permutations/description/
"""


class Solution:
    def permute(self, nums: list[int]) -> list[list[int]]:
        def dfs(nums):
            ret = []
            if len(nums) == 1:
                return [nums]

            for i in range(len(nums)):
                tmp_nums = nums.copy()
                cur = tmp_nums[i]
                tmp_nums.remove(cur)
                sub = dfs(tmp_nums)
                for s in sub:
                    s.insert(0, cur)
                    ret.append(s)
            return ret

        return dfs(nums)


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：[1,2,3] 的全部 6 个排列 ----
    assert sorted(solution.permute([1, 2, 3])) == [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]

    # ---- 官方示例 2：[0,1] 两个排列 ----
    assert sorted(solution.permute([0, 1])) == [[0, 1], [1, 0]]

    # ---- 官方示例 3：单元素只有自身 ----
    assert sorted(solution.permute([1])) == [[1]]

    # ---- 上限规模：4 个互异数 -> 4! = 24 个排列，且含完全逆序的一个 ----
    result_4 = sorted(solution.permute([1, 2, 3, 4]))
    assert len(result_4) == 24
    assert [4, 3, 2, 1] in result_4

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
