"""
@file top150_17.py
@brief LeetCode 17. Letter Combinations of a Phone Number（电话号码的字母组合）

@题目描述
    给定一个仅包含数字 2-9 的字符串 digits，返回所有它能表示的字母组合。
    按任意顺序返回答案。

    电话按键上数字到字母的映射如下（与九宫格键盘一致）：
    - 2 -> "abc"，3 -> "def"
    - 4 -> "ghi"，5 -> "jkl"
    - 6 -> "mno"，7 -> "pqrs"
    - 8 -> "tuv"，9 -> "wxyz"
    注意数字 0 和 1 不对应任何字母，题目保证输入不含它们。

    提示：
    - 0 <= digits.length <= 4
    - digits[i] 是范围 ['2', '9'] 内的一个数字

@示例
    示例 1：
    输入：digits = "23"
    输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
    解释：数字 2 对应 "abc"，数字 3 对应 "def"，两两配对得到 3 x 3 = 9 种组合。

    示例 2：
    输入：digits = ""
    输出：[]
    解释：没有输入数字，对应空组合列表（注意不是 [""]）。

    示例 3：
    输入：digits = "2"
    输出：["a","b","c"]

@解题思路
    本题属于 top150 回溯（backtracking）分类，是「子集/组合树」最朴素的
    入门形态——枚举的不是「选或不选」，而是「每位从各自的字母集合中选一个」：

    1. 数字 -> 字母映射表：2→"abc", 3→"def", 4→"ghi", 5→"jkl", 6→"mno",
       7→"pqrs", 8→"tuv", 9→"wxyz"。7 和 9 对应 4 个字母，其余是 3 个，
       这决定了分支因子最大为 4；
    2. 回溯：递归深度与 digits 的第几位对齐——每一层固定一位数字，枚举
       该数字对应的每个字母追加到当前路径，向下递归；当路径长度等于
       digits 长度时收集一条完整组合并回溯撤销。整棵递归树恰好是各键
       字母集合的笛卡尔积（itertools.product 的展开形态）；
    3. 空串是关键边界：digits == "" 时必须直接返回 []，不能进入回溯——
       否则「路径长度 == 0 == len(digits)」会立刻命中收集条件，错误地
       返回 [""]（一条空路径）。

    时间复杂度 O(4^n * n)：最坏每位 4 个字母，共 4^n 条组合，每条收集时
    拼接/拷贝需要 O(n)；空间复杂度 O(n)（递归栈深度 + 当前路径，不计
    输出）。

来源：LeetCode
链接：https://leetcode.cn/problems/letter-combinations-of-a-phone-number/description/
"""


class Solution:
    def letterCombinations(self, digits: str) -> list[str]:
        if not digits:
            return []

        letters = ("", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz")
        ret: list[str] = []
        path: list[str] = []

        def backtrack(index: int) -> None:
            if index == len(digits):
                ret.append("".join(path))
                return
            for letter in letters[int(digits[index])]:
                path.append(letter)
                backtrack(index + 1)
                path.pop()

        backtrack(0)
        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：2 x 3 两两配对，9 种组合 ----
    assert sorted(solution.letterCombinations("23")) == sorted(["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"])

    # ---- 官方示例 2：空串是关键边界，返回 [] 而非 [""] ----
    assert solution.letterCombinations("") == []

    # ---- 官方示例 3：单个数字 3 选 1 ----
    assert sorted(solution.letterCombinations("2")) == sorted(["a", "b", "c"])

    # ---- "234"：2/3/4 各 3 个字母，共 3*3*3 = 27 条组合，每条长 3 ----
    result = solution.letterCombinations("234")
    assert len(result) == 27
    assert all(len(comb) == 3 for comb in result)
    assert len(set(result)) == 27  # 无重复

    # ---- "7"：含 4 个字母的键单独枚举 ----
    assert sorted(solution.letterCombinations("7")) == sorted(["p", "q", "r", "s"])

    # ---- "9"：4 个字母 ----
    result = solution.letterCombinations("9")
    assert len(result) == 4
    assert sorted(result) == sorted(["w", "x", "y", "z"])

    # ---- "79"：两个 4 字母键相邻，4*4 = 16 条组合，每条长 2 ----
    result = solution.letterCombinations("79")
    assert len(result) == 16
    assert all(len(comb) == 2 for comb in result)
    assert len(set(result)) == 16  # 无重复


if __name__ == "__main__":
    test_solution()
    print("✅ No.17 全部测试通过")
