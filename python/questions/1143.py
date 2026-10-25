"""
@file 1143.py
@brief LeetCode 1143. Longest Common Subsequence

@题目描述
    给定两个字符串 text1 和 text2，返回它们最长公共子序列的长度。
    如果不存在公共子序列，返回 0。
    子序列可以由原字符串删除若干个（也可以不删）字符得到，
    但必须保持剩余字符的相对顺序。

@示例
    示例 1：
    输入：text1 = "abcde", text2 = "ace"
    输出：3
    解释：最长公共子序列是 "ace"。

    示例 2：
    输入：text1 = "abc", text2 = "abc"
    输出：3
    解释：最长公共子序列是 "abc"。

    示例 3：
    输入：text1 = "abc", text2 = "def"
    输出：0
    解释：两个字符串没有公共子序列。

@解题思路
    1. dp[i][j] 表示 text1 前 i 个字符与 text2 前 j 个字符的最长公共子序列长度；
    2. 若 text1[i - 1] == text2[j - 1]，则它们可以作为当前公共字符接到
       dp[i - 1][j - 1] 对应的子序列末尾，得 dp[i][j] = dp[i - 1][j - 1] + 1；
    3. 否则至少要舍弃其中一个末尾字符，取两侧最大值：
       dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])；
    4. 初始化第 0 行和第 0 列为 0，因为任意字符串与空串的公共子序列长度为 0。

    时间复杂度 O(mn)，空间复杂度 O(mn)。

来源：LeetCode
链接：https://leetcode.cn/problems/longest-common-subsequence/description/
"""


class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        m, n = len(text1), len(text2)
        dp = [[0] * (n + 1) for _ in range(m + 1)]

        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if text1[i - 1] == text2[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1] + 1
                else:
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

        return dp[m][n]


def test_solution() -> None:
    solution = Solution()

    # 官方示例
    assert solution.longestCommonSubsequence("abcde", "ace") == 3  # "ace"
    assert solution.longestCommonSubsequence("abc", "abc") == 3  # 两个字符串完全相同
    assert solution.longestCommonSubsequence("abc", "def") == 0  # 没有公共字符

    # 边界与重复字符
    assert solution.longestCommonSubsequence("a", "a") == 1  # 单字符相同
    assert solution.longestCommonSubsequence("a", "b") == 0  # 单字符不同
    assert solution.longestCommonSubsequence("aaaa", "aa") == 2  # 重复字符不能重复超过较短串次数

    # 子序列必须保持相对顺序
    assert solution.longestCommonSubsequence("abc", "cba") == 1  # 只能选一个公共字符
    assert solution.longestCommonSubsequence("abcde", "aec") == 2  # "ac"，不能取乱序的 "aec"

    # 交换参数后结果不变
    assert solution.longestCommonSubsequence("ace", "abcde") == 3

    # 较复杂的重复与穿插
    assert solution.longestCommonSubsequence("abcba", "abcbcba") == 5  # "abcba"
    assert solution.longestCommonSubsequence("aabaa", "azbaa") == 4  # "abaa"


if __name__ == "__main__":
    test_solution()
    print("✅ No.1143 全部测试通过")
