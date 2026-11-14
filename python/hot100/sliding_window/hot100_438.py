"""
@file hot100_438.py
@brief LeetCode 438. 找到字符串中所有字母异位词（Find All Anagrams in a String）— HOT 100

@题目描述
    给定两个字符串 s 和 p，找到 s 中所有 p 的异位词的子串，返回这些子串的起始
    索引列表。不考虑答案输出的顺序。异位词指由相同字母重排列形成的字符串（包括
    相同的字符串）。

@示例
    示例 1：
    输入：s = "cbaebabacd", p = "abc"
    输出：[0,6]
    解释：起始索引等于 0 的子串是 "cba"，它是 "abc" 的异位词；
    起始索引等于 6 的子串是 "bac"，也是 "abc" 的异位词。

    示例 2：
    输入：s = "abab", p = "ab"
    输出：[0,1,2]
    解释：起始索引等于 0/1/2 的子串 "ab"/"ba"/"ab" 都是 "ab" 的异位词。

    数据范围：
    1 <= s.length, p.length <= 3 * 1e4
    s 和 p 仅包含小写字母

@解题思路
    定长滑动窗口 + 26 计数数组：
    1. 窗口长度固定为 len(p)：先统计 p 的字母计数 p_count 与 s 首个窗口的
       s_count，相等则起始索引 0 入答案；
    2. 窗口右滑一格 = 「出一个进一个」的增量更新：s_count 减去离开窗口的
       s[i]、加上进入窗口的 s[i+len(p)]，避免每个窗口重新计数 O(k)；
    3. 每滑一步比较两个计数数组（26 个小写字母，比较 O(26)），相等则记录
       新左端 i+1；
    4. len(s) < len(p) 时无解，直接返回空。

    时间复杂度 O(n*26)（n 为 s 长度，每滑一步 O(26) 比较），空间复杂度 O(26)
    进阶：维护一个「计数差异个数」变量 differ（有多少字母计数不同），进出窗口
    时增量更新，可把每步比较降到 O(1)——见 567 题的写法。

来源：LeetCode
链接：https://leetcode.cn/problems/find-all-anagrams-in-a-string/description/
"""


class Solution:
    def findAnagrams(self, s: str, p: str) -> list[int]:
        if len(s) < len(p):
            return []

        s_count = [0] * 26
        p_count = [0] * 26
        for i in range(len(p)):
            p_count[ord(p[i]) - ord("a")] += 1
            s_count[ord(s[i]) - ord("a")] += 1

        ret = []
        if s_count == p_count:  # 首个窗口（起始索引 0）单独判定
            ret.append(0)

        # 窗口右滑：左端离开 s[i]，右端进入 s[i+len(p)]，新左端为 i+1
        for i in range(len(s) - len(p)):
            s_count[ord(s[i]) - ord("a")] -= 1
            s_count[ord(s[i + len(p)]) - ord("a")] += 1
            if s_count == p_count:
                ret.append(i + 1)

        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1 ----
    assert solution.findAnagrams("cbaebabacd", "abc") == [0, 6]

    # ---- 官方示例 2：滑步重叠的异位词 ----
    assert solution.findAnagrams("abab", "ab") == [0, 1, 2]

    # ---- s 比 p 短：无解 ----
    assert solution.findAnagrams("a", "ab") == []

    # ---- 窗口等于整串 ----
    assert solution.findAnagrams("abc", "cba") == [0]

    # ---- 无异位词（字母集不同）----
    assert solution.findAnagrams("abcd", "efg") == []

    # ---- 重复字母："aba" 排序后同为 "aab"，也是异位词 ----
    assert solution.findAnagrams("aabaa", "aab") == [0, 1, 2]
    assert solution.findAnagrams("aababaa", "aab") == [0, 1, 3, 4]


if __name__ == "__main__":
    test_solution()
    print("✅ No.438（HOT 100）全部测试通过")
