"""
@file top150_5.py
@brief LeetCode 5. Longest Palindromic Substring（最长回文子串）

@题目描述
    给你一个字符串 s，找到 s 中最长的回文子串。如果存在多个最长回文子串，返回其中任意一个。

@示例
    示例 1：
    输入：s = "babad"
    输出："bab"
    解释："aba" 同样是符合题意的答案。

    示例 2：
    输入：s = "cbbd"
    输出："bb"

    数据范围：
    1 <= s.length <= 1000
    s 仅由数字和英文字母组成

@解题思路
    区间 DP：dp[i][j] = s[i..j] 是否回文。
    1. 初始化：单字符 dp[i][i] = True；
    2. 按子串长度从 2 到 n 枚举，i 为左端点、j = i + length - 1 为右端点：
       - s[i] != s[j]：不回文（dp 初值即 False，显式赋值一次更清晰）；
       - s[i] == s[j]：长度 <= 3（两端夹 0 或 1 个字符）直接 True，
         否则取决于内部子串 dp[i+1][j-1]；
    3. 过程中记录最长回文的起点与长度，返回 s[begin:begin+max_len]。
    备注：dp 初值全 False，"s[i] != s[j] 分支"在语义上可省，但显式写出更直观；
    初版此处误写为 == 比较（碰巧因初值 False 而行为正确），ruff B015/E712 可查出。

    时间复杂度 O(n^2)，空间复杂度 O(n^2)
"""


class Solution:
    def longestPalindrome(self, s: str) -> str:
        if len(s) < 2:
            return s

        n = len(s)
        dp = [[False] * n for _ in range(n)]
        for i in range(n):
            dp[i][i] = True

        max_len = 1
        begin = 0

        for length in range(2, n + 1):  # 枚举子串长度
            for i in range(n):  # 枚举左端点
                j = length + i - 1  # 右端点
                if j >= n:
                    break

                if s[i] != s[j]:
                    dp[i][j] = False  # 初版误写为 ==（比较无效果，幸而初值即 False）
                else:
                    if j - i < 3:  # 长度 2 或 3：两端相等即回文
                        dp[i][j] = True
                    else:
                        dp[i][j] = dp[i + 1][j - 1]  # 取决于内部子串
                if dp[i][j] and j - i + 1 > max_len:
                    max_len = j - i + 1
                    begin = i

        return s[begin : begin + max_len]


def test_solution() -> None:
    solution = Solution()
    # 官方示例（答案不唯一时接受任一合法解）
    assert solution.longestPalindrome("babad") in ("bab", "aba")
    assert solution.longestPalindrome("cbbd") == "bb"
    # 边界：单字符 / 无回文的双字符
    assert solution.longestPalindrome("a") == "a"
    assert solution.longestPalindrome("ac") in ("a", "c")
    assert solution.longestPalindrome("bb") == "bb"
    # 唯一答案：整串回文（奇/偶长度）、回文在中段
    assert solution.longestPalindrome("abcba") == "abcba"
    assert solution.longestPalindrome("abccba") == "abccba"
    assert solution.longestPalindrome("forgeeksskeegfor") == "geeksskeeg"
    assert solution.longestPalindrome("abacab") == "bacab"
    assert solution.longestPalindrome("aaaa") == "aaaa"
    # 无奇偶中心回文时返回任一单字符（多解按属性校验）
    r = solution.longestPalindrome("abcda")
    assert len(r) == 1 and r in "abcda"
    # 长输入上界：全同字符整串即最长；"abc" 周期填充中嵌入唯一长回文（暴力核验唯一性）
    assert solution.longestPalindrome("a" * 1000) == "a" * 1000
    assert solution.longestPalindrome("abc" * 332 + "q" * 7 + "abc") == "q" * 7


if __name__ == "__main__":
    test_solution()
    print("✅ No.5 全部测试通过")
