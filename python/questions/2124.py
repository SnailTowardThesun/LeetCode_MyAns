"""
@file 2124.py
@brief LeetCode 2124. 检查是否所有 A 都在 B 之前（Check if All A's Appears Before All B's）

@题目描述
    给你一个仅由字符 'a' 和 'b' 组成的字符串 s。如果 s 中每个 'a' 都出现在
    每个 'b' 之后之前（即不存在某个 'b' 出现在某个 'a' 前面），返回 true；
    否则返回 false。

@示例
    示例 1：
    输入：s = "aaabbb"
    输出：True
    解释：所有 'a' 都在所有 'b' 之前。

    示例 2：
    输入：s = "abab"
    输出：False

    示例 3：
    输入：s = "bbb"
    输出：True（没有 'a'，条件自然满足）

    数据范围：
    1 <= s.length <= 100
    s[i] 为 'a' 或 'b'

@解题思路
    定位最后一个 'a'，检查其前缀无 'b'：
    1. 从右向左找最后一个 'a' 的下标 last_a（不存在则直接返回 True）；
    2. 再检查 s[0..last_a] 中没有 'b'——若 'b' 出现在最后一个 'a' 之前，
       即存在某个 'b' 在某个 'a' 前面，返回 False。
    等价的一行判定：'ba' not in s——字符只有 a/b 两种，任何「b 在 a 前」
    的违规序列必含相邻的 "ba" 对。

    时间复杂度 O(n)，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/check-if-all-as-appears-before-all-bs/description/
"""


class Solution:
    def checkString(self, s: str) -> bool:
        last_a = -1
        for i in range(len(s) - 1, -1, -1):  # 从右向左找最后一个 'a'
            if s[i] == "a":
                last_a = i
                break

        if last_a == -1:  # 没有 'a'，条件自然满足
            return True

        return "b" not in s[: last_a + 1]  # 最后一个 'a' 之前不得出现 'b'


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.checkString("aaabbb") is True
    assert solution.checkString("abab") is False
    assert solution.checkString("bbb") is True

    # ---- 最小规模（期望值由参考实现机器核对）----
    assert solution.checkString("a") is True
    assert solution.checkString("b") is True
    assert solution.checkString("ab") is True
    assert solution.checkString("ba") is False

    # ---- 尾部违规：'a' 出现在 'b' 之后 ----
    assert solution.checkString("bbba") is False
    assert solution.checkString("aabbb") is True


if __name__ == "__main__":
    test_solution()
    print("✅ No.2124 全部测试通过")
