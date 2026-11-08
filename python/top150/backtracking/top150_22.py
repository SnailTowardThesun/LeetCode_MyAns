"""
@file top150_22.py
@brief LeetCode 22. Generate Parentheses（括号生成）——面试经典 150 题·回溯

@题目描述
    数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的
    并且 有效的 括号组合。

    提示：
    - 1 <= n <= 8

@示例
    示例 1：
    输入：n = 3
    输出：["((()))","(()())","(())()","()(())","()()()"]

    示例 2：
    输入：n = 1
    输出：["()"]

@解题思路
    回溯（top150 回溯分类）。一个括号串「有效」等价于：任意前缀中左括号
    数量 >= 右括号数量，且总数恰好各 n 个。据此在构造过程中维护已放的
    左括号数 open 与右括号数 close 两个计数，无需事后校验合法性：

    1. open < n：左括号还没放满，可以放 '('；
    2. close < open：右括号数未超过左括号数（前缀合法条件），可以放 ')'；
    3. 当前串长度到达 2n 时收集结果，回溯撤销选择继续穷举。

    每一步只在合法分支上扩展，搜索树中所有叶子都是有效组合。n 对括号
    的有效组合数是卡特兰数 C_n（n=1..8 依次为 1, 2, 5, 14, 42, 132,
    429, 1430）。

    时间复杂度 O(4^n / sqrt(n))（卡特兰数渐近）；空间复杂度 O(n)
    （递归深度 + 当前路径）。

来源：LeetCode
链接：https://leetcode.cn/problems/generate-parentheses/description/
"""


class Solution:
    def generateParenthesis(self, n: int) -> list[str]:
        # TODO 回溯：维护已放左括号数 open 与右括号数 close——
        #   open < n 时可放 '('，close < open 时可放 ')'，
        #   串长达到 2n 时收集结果，回溯撤销选择
        ret = set()

        def dfs(path, n, left, right):
            if left > n:
                return
            if right > left:
                return

            if len(path) == 2 * n:
                ret.add(path)

            dfs(path + "(", n, left + 1, right)
            dfs(path + ")", n, left, right + 1)

        dfs("", n, 0, 0)

        return list(ret)


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：n=3，5 个组合（卡特兰数 C_3 = 5） ----
    assert sorted(solution.generateParenthesis(3)) == sorted(["((()))", "(()())", "(())()", "()(())", "()()()"])

    # ---- 官方示例 2：n=1 ----
    assert sorted(solution.generateParenthesis(1)) == ["()"]

    # ---- n=2：卡特兰数 C_2 = 2 个，列出全部 ----
    assert sorted(solution.generateParenthesis(2)) == ["(())", "()()"]

    # ---- n=4：卡特兰数 C_4 = 14 个，数量断言 ----
    assert len(solution.generateParenthesis(4)) == 14

    # ---- n=8：约束上界，卡特兰数 C_8 = 1430 个，数量断言 ----
    assert len(solution.generateParenthesis(8)) == 1430


if __name__ == "__main__":
    test_solution()
    print("✅ No.22 全部测试通过")
