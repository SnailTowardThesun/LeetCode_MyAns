"""
@file hot100_76.py
@brief LeetCode 76. 最小覆盖子串（Minimum Window Substring）— HOT 100

@题目描述
    给你一个字符串 s 和一个字符串 t。返回 s 中涵盖 t 所有字符的最小子串。
    如果不存在，返回空字符串 ""。如果存在，题目保证答案唯一。

@示例
    示例 1：
    输入：s = "ADOBECODEBANC", t = "ABC"
    输出："BANC"
    解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。

    示例 2：
    输入：s = "a", t = "a"
    输出："a"

    示例 3：
    输入：s = "a", t = "aa"
    输出：""
    解释：t 中两个字符 'a' 应在子串中同时出现，s 中只有一个，无解。

    数据范围：
    m == s.length, n == t.length
    1 <= m, n <= 1e5
    s 和 t 由英文字母组成

@解题思路
    滑动窗口 + Counter 超集比较（Python 3.10+ 支持 multiset 比较）：
    1. cnt_t 记录 t 的字符需求；cnt_s 记录当前窗口字符数；
    2. right 右扩：纳入 s[right] 后，若 cnt_s >= cnt_t（multiset 超集，
       即每个字符的出现次数都不少于需求），窗口已覆盖 t；
    3. 覆盖时收缩 left：先记录当前更短的答案，再吐出 s[left] 继续收缩，
       直到不再覆盖——保证每个 right 找到的是「以其为右端的最短覆盖窗」；
    4. ans_left == -1 表示从未覆盖过，返回空串。
    cnt_s 中会出现零/负值条目（吐出过头），但零不影响超集判定，
    负值只出现在 t 不需要的字符上，同样不影响。

    时间复杂度 O(m·|Σ|)：每步 right/left 至多移动一次，每次超集比较
    O(|Σ|)（|Σ| <= 52 个英文字母）；进阶可用「欠账字符种数」变量把比较
    降到 O(1)——每进出窗口增量更新，为 0 即覆盖。

来源：LeetCode
链接：https://leetcode.cn/problems/minimum-window-substring/description/
"""

from collections import Counter


class Solution:
    def minWindow(self, s: str, t: str) -> str:
        cnt_s: Counter = Counter()
        cnt_t: Counter = Counter(t)
        ans_left, ans_right = -1, len(s)  # 记录最优窗口（闭区间），-1 表示未覆盖过

        left = 0
        for right in range(len(s)):
            cnt_s[s[right]] += 1
            while cnt_s >= cnt_t:  # multiset 超集：窗口覆盖 t，收缩左端找更短
                if right - left < ans_right - ans_left:
                    ans_left, ans_right = left, right
                cnt_s[s[left]] -= 1
                left += 1

        return "" if ans_left == -1 else s[ans_left : ans_right + 1]


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.minWindow("ADOBECODEBANC", "ABC") == "BANC"
    assert solution.minWindow("a", "a") == "a"
    assert solution.minWindow("a", "aa") == ""

    # ---- t 的字符 s 完全没有 ----
    assert solution.minWindow("abc", "d") == ""

    # ---- 重复字符需求：s 恰好两个 a ----
    assert solution.minWindow("aa", "aa") == "aa"

    # ---- 覆盖窗口在中间：b 与两个 a 之间隔着 x，最短覆盖是 "bxaa" ----
    assert solution.minWindow("xxbxaax", "aab") == "bxaa"
    assert solution.minWindow("ab", "b") == "b"

    # ---- 大小写敏感：A 不覆盖 a ----
    assert solution.minWindow("Ab", "a") == ""


if __name__ == "__main__":
    test_solution()
    print("✅ No.76（HOT 100）全部测试通过")
