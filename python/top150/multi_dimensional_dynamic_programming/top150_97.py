"""
@file top150_97.py
@brief LeetCode 97. Interleaving String（交错字符串）

@题目描述
    给定三个字符串 s1、s2、s3，请判断 s3 是否由 s1 和 s2 交错组成。
    两个字符串 s 和 t 交错的定义与过程如下，其中每个字符串都会被分割成若干非空子串：
        s = s1 + s2 + ... + sn
        t = t1 + t2 + ... + tm
        |n - m| <= 1
    交错是 s1 + t1 + s2 + t2 + ... 或 t1 + s1 + t2 + s2 + ...（注意：分割出的子串需保持原序）。

@示例
    示例 1：
    输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
    输出：True

    示例 2：
    输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
    输出：False

    示例 3：
    输入：s1 = "", s2 = "", s3 = ""
    输出：True

    数据范围：
    0 <= s1.length, s2.length <= 100
    0 <= s3.length <= 200
    s1、s2、s3 由小写英文字母组成

@解题思路
    二维 DP：dp[i][j] = s3 前 i+j 个字符能否由 s1 前 i 个与 s2 前 j 个交错组成。
    1. 长度先判：len(s1) + len(s2) != len(s3) 直接 False；
    2. 边界：dp[0][0] = True；首列 dp[i][0] 要求 s1 前 i 个恰为 s3 前 i 个的前缀链；
       首行 dp[0][j] 同理对应 s2；
    3. 转移：s3 的第 i+j 个字符（下标 i+j-1）只能来自 s1 的第 i 个或 s2 的第 j 个——
       dp[i][j] = (dp[i-1][j] 且 s1[i-1]==s3[i+j-1]) 或 (dp[i][j-1] 且 s2[j-1]==s3[i+j-1])；
       两串字符可能相同（歧义），两个来源都必须尝试，这也是双指针贪心不可行的原因。

    时间复杂度 O(n1*n2)，空间复杂度 O(n1*n2)（滚动可 O(n2)）
"""


class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        n1, n2, n3 = len(s1), len(s2), len(s3)
        if n1 + n2 != n3:
            return False
        # dp[i][j]：s3[:i+j] 能否由 s1[:i] 与 s2[:j] 交错组成
        dp = [[False] * (n2 + 1) for _ in range(n1 + 1)]
        dp[0][0] = True
        for i in range(1, n1 + 1):  # 首列：只消耗 s1
            dp[i][0] = dp[i - 1][0] and s1[i - 1] == s3[i - 1]
        for j in range(1, n2 + 1):  # 首行：只消耗 s2
            dp[0][j] = dp[0][j - 1] and s2[j - 1] == s3[j - 1]
        for i in range(1, n1 + 1):
            for j in range(1, n2 + 1):
                if dp[i - 1][j] and s1[i - 1] == s3[i + j - 1]:  # 第 i+j 个字符取自 s1
                    dp[i][j] = True
                elif dp[i][j - 1] and s2[j - 1] == s3[i + j - 1]:  # 取自 s2（歧义时两条都试）
                    dp[i][j] = True

        return dp[n1][n2]


def test_solution() -> None:
    solution = Solution()
    # 官方示例
    assert solution.isInterleave("aabcc", "dbbca", "aadbbcbcac") is True
    assert solution.isInterleave("aabcc", "dbbca", "aadbbbaccc") is False
    assert solution.isInterleave("", "", "") is True
    # 边界：某一串为空，另一串须恰为 s3（含前缀失配）
    assert solution.isInterleave("", "abc", "abc") is True
    assert solution.isInterleave("", "abc", "abd") is False
    assert solution.isInterleave("abc", "", "abc") is True
    # 长度不符直接 False（即使字符都对得上）
    assert solution.isInterleave("ab", "cd", "abc") is False
    # 单字符与基本交错
    assert solution.isInterleave("a", "b", "ab") is True
    assert solution.isInterleave("a", "b", "ba") is True
    assert solution.isInterleave("ab", "cd", "acbd") is True
    # 歧义用例：同一字符两条来源都可行时，贪心（固定先取某一串）会错
    assert solution.isInterleave("aa", "ab", "aaba") is True
    assert solution.isInterleave("aa", "ab", "abaa") is True
    assert solution.isInterleave("aaa", "aaa", "aaaaaa") is True
    # 随机用例（期望值经带备忘递归暴力验证）
    assert solution.isInterleave("aabc", "abad", "aababadc") is True


if __name__ == "__main__":
    test_solution()
    print("✅ No.97 全部测试通过")
