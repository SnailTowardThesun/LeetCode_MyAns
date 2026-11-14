"""
@file hot100_3.py
@brief LeetCode 3. 无重复字符的最长子串（Longest Substring Without Repeating Characters）— HOT 100

@题目描述
    给定一个字符串 s，请你找出其中不含有重复字符的最长子串的长度。

@示例
    示例 1：
    输入：s = "abcabcbb"
    输出：3
    解释：因为无重复字符的最长子串是 "abc"，长度为 3。

    示例 2：
    输入：s = "bbbbb"
    输出：1
    解释：因为无重复字符的最长子串是 "b"，长度为 1。

    示例 3：
    输入：s = "pwwkew"
    输出：3
    解释：因为无重复字符的最长子串是 "wke"，长度为 3。注意答案必须是子串的长度，
    "pwke" 是子序列而不是子串。

    数据范围：
    0 <= s.length <= 5 * 1e4
    s 由英文字母、数字、符号和空格组成

@解题思路
    滑动窗口 + set 收缩：
    1. right 逐位右扩：新字符不在窗口集合中，直接入集合并刷新最长；
    2. 遇到重复字符时，left 逐步收缩——沿途字符逐个移出集合，直到把与
       s[right] 相同的那个旧字符移过（它本身留在窗口：right 处的新出现接管它）；
    3. 不变量：窗口 [left, right] 内无重复，长度恒为 right - left + 1；
    4. right 走完整个串，每个字符至多进出窗口各一次。

    陷阱用例：'abba'（收缩时 a 已被移出，末尾的 a 不算重复）、'tmmzuxt'
    （t 早在窗口收缩时移出，末尾的 t 能重新入窗）——先查后加的集合收缩天然正确。

    时间复杂度 O(n)（left、right 各单调走一趟），空间复杂度 O(min(n, |Σ|))

来源：LeetCode
链接：https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/
"""


class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        n = len(s)
        if n == 0:
            return 0

        ret = 1  # 单字符自成合法窗口
        tmp = 1  # 当前窗口长度，恒等于 right - left + 1
        left, right = 0, 1
        container = {s[0]}  # 窗口内字符集合
        while right < n:
            if s[right] not in container:
                tmp += 1
                ret = max(ret, tmp)
                container.add(s[right])
            else:
                # 收缩到「与 s[right] 相同的旧字符」被移过为止：
                # 沿途字符移出集合；命中的那个字符不移出——right 处的新出现接管它
                while left <= right:
                    if s[left] == s[right]:
                        left += 1
                        tmp = right - left + 1
                        break
                    container.remove(s[left])
                    left += 1
                    tmp -= 1

            right += 1

        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.lengthOfLongestSubstring("abcabcbb") == 3
    assert solution.lengthOfLongestSubstring("bbbbb") == 1
    assert solution.lengthOfLongestSubstring("pwwkew") == 3

    # ---- 陷阱：收缩过程中旧字符已被移出，末尾同字符不算重复 ----
    assert solution.lengthOfLongestSubstring("abba") == 2
    assert solution.lengthOfLongestSubstring("tmmzuxt") == 5

    # ---- 边界：空串 / 单字符 / 空格 ----
    assert solution.lengthOfLongestSubstring("") == 0
    assert solution.lengthOfLongestSubstring("a") == 1
    assert solution.lengthOfLongestSubstring(" ") == 1

    # ---- 全不重复 ----
    assert solution.lengthOfLongestSubstring("abcdef") == 6


if __name__ == "__main__":
    test_solution()
    print("✅ No.3（HOT 100）全部测试通过")
