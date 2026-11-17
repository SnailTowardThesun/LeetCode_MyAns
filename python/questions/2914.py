"""
@file 2914.py
@brief LeetCode 2914. 使二进制字符串变美丽的最少修改次数（Minimum Number of Changes to Make Binary String Beautiful）

@题目描述
    给你一个长度为偶数 n 的二进制字符串 s。
    如果 s 可以分割成若干子串，满足：
    - 每个子串长度均为偶数；
    - 每个子串只包含 1 或只包含 0（不混合）；
    则称 s 是「美丽的」。
    一次修改可以将一个字符翻转（0 变 1 或 1 变 0），返回使 s 美丽的最少修改次数。

@示例
    示例 1：
    输入：s = "1001"
    输出：2
    解释：改成 "1100" 或 "0011"，分割成 "11" + "00"。

    示例 2：
    输入：s = "10"
    输出：1

    示例 3：
    输入：s = "0000"
    输出：0

    数据范围：
    2 <= s.length <= 10^4
    s.length 为偶数
    s[i] 为 '0' 或 '1'

@解题思路
    相邻两两分组统计（贪心）：
    关键观察：任何合法的「均匀偶长块」（如 "0000"、"11"）都可以进一步切成
    两两一组的全同字符对而不增加修改次数，因此最优划分永远是相邻配对
    (s[0],s[1]), (s[2],s[3]), ...：
    - 对内相同：0 次修改；
    - 对内不同：改其中任意一个即全同，1 次修改。
    答案 = 不相等的对的个数。

    时间复杂度 O(n)，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/minimum-number-of-changes-to-make-binary-string-beautiful/description/
"""


class Solution:
    def minChanges(self, s: str) -> int:
        ret = 0
        # 相邻两两一组：组内不同则改任意一个，+1
        for i in range(0, len(s), 2):
            if s[i] != s[i + 1]:
                ret += 1
        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.minChanges("1001") == 2
    assert solution.minChanges("10") == 1
    assert solution.minChanges("0000") == 0

    # ---- 最小规模 ----
    assert solution.minChanges("00") == 0
    assert solution.minChanges("01") == 1

    # ---- 全交替：每对都要改 ----
    assert solution.minChanges("0101") == 2
    assert solution.minChanges("1010") == 2

    # ---- 已美丽：两两分组即可满足 ----
    assert solution.minChanges("1100") == 0
    assert solution.minChanges("110100") == 1  # "11"+"01"+"00"，中间对改一个

    # ---- 全同字符 ----
    assert solution.minChanges("1111") == 0


if __name__ == "__main__":
    test_solution()
    print("✅ No.2914 全部测试通过")
