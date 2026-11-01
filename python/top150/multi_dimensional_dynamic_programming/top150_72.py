"""
@file top150_72.py
@brief LeetCode 72. Edit Distance（编辑距离）

@题目描述
    给你两个单词 word1 和 word2，请返回将 word1 转换成 word2 所使用的最少操作数。
    可以对一个单词进行如下三种操作：
      - 插入一个字符
      - 删除一个字符
      - 替换一个字符

@示例
    示例 1：
    输入：word1 = "horse", word2 = "ros"
    输出：3
    解释：horse -> rorse (将 'h' 替换为 'r') -> rorse -> rose (删除 'r') -> rose -> ros (删除 'e')

    示例 2：
    输入：word1 = "intention", word2 = "execution"
    输出：5

    数据范围：
    0 <= word1.length, word2.length <= 500
    word1 和 word2 由小写英文字母组成

@解题思路
    经典二维 DP：dp[i][j] = word1 前 i 个字符变成 word2 前 j 个字符的最少操作数。
    1. 边界：dp[i][0] = i（删除 i 次），dp[0][j] = j（插入 j 次）；一为空串时答案即另一串长度；
    2. 转移按"word1 的第 i 个字符如何对齐 word2 的第 j 个字符"分三种：
      - 插入：在 word1 末尾补上 word2[j]，dp[i][j-1] + 1（消耗 word2 一个字符）
      - 删除：删掉 word1[i]，dp[i-1][j] + 1（消耗 word1 一个字符）
      - 替换/保留：对齐两个末字符，dp[i-1][j-1] + (word1[i-1] != word2[j-1])，
        字符相同则代价 0（保留），不同则代价 1（替换）
    3. 三者取最小；"末字符相等时走对角线免费"正是编辑距离低于 n 的原因。

    时间复杂度 O(n1*n2)，空间复杂度 O(n1*n2)（滚动可 O(n2)）
"""


class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        n1, n2 = len(word1), len(word2)
        if n1 == 0 or n2 == 0:
            return n1 + n2  # 一为空串：答案即另一串长度（插入或删除整串）

        # dp[i][j]：word1 前 i 个字符变成 word2 前 j 个字符的最少操作数
        dp = [[0] * (n2 + 1) for _ in range(n1 + 1)]
        for i in range(n1 + 1):
            dp[i][0] = i  # 删除 i 次
        for j in range(n2 + 1):
            dp[0][j] = j  # 插入 j 次

        for i in range(1, n1 + 1):
            for j in range(1, n2 + 1):
                ins = dp[i][j - 1] + 1  # 插入 word2[j-1]
                dele = dp[i - 1][j] + 1  # 删除 word1[i-1]
                rep = dp[i - 1][j - 1] + (word1[i - 1] != word2[j - 1])  # 末字符对齐（同则保留）
                dp[i][j] = min(ins, dele, rep)

        return dp[n1][n2]


def test_solution() -> None:
    solution = Solution()
    # 官方示例
    assert solution.minDistance("horse", "ros") == 3
    assert solution.minDistance("intention", "execution") == 5
    # 边界：空串（三个方向各自的基础操作）
    assert solution.minDistance("", "") == 0
    assert solution.minDistance("", "abc") == 3  # 纯插入
    assert solution.minDistance("abc", "") == 3  # 纯删除
    # 相同串零成本；全不同则整串替换
    assert solution.minDistance("same", "same") == 0
    assert solution.minDistance("abc", "xyz") == 3
    # 单操作：替换 / 插入 / 删除各一
    assert solution.minDistance("a", "b") == 1  # 替换
    assert solution.minDistance("b", "ab") == 1  # 插入
    assert solution.minDistance("ab", "b") == 1  # 删除
    # 交换两字符 = 2（无法一步完成）
    assert solution.minDistance("ab", "ba") == 2
    # 经典长例（期望值经自顶向下递归参考验证）
    assert solution.minDistance("dinitrophenylhydrazine", "benzalphenylhydrazone") == 7


if __name__ == "__main__":
    test_solution()
    print("✅ No.72 全部测试通过")
