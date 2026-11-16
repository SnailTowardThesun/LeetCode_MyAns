"""
@file 2243.py
@brief LeetCode 2243. 计算字符串的数字和（Calculate Digit Sum of a String）

@题目描述
    给你一个由若干数字字符（0-9）组成的字符串 s 和一个整数 k。
    如果 s 的长度大于 k，可以执行一轮轮转操作：把 s 分割成长度为 k 的连续组
    （最后一组长度可能小于 k），再用每组数字之和组成的新字符串替换 s。
    不断执行直到 s 的长度小于等于 k，返回最终的 s。
    注意：组的和可能超过一位数（如 9+9=18），它以十进制形式拼进新串，
    下一轮分组按新串的「字符」重新划分——多 digit 和会被拆开重组。

@示例
    示例 1：
    输入：s = "11111222223", k = 3
    输出："135"
    解释：第一轮 111|112|222|23 -> 3+4+6+5 = "3465"；第二轮 346|5 -> 13+5 = "135"，
    长度 3 <= 3 结束。

    示例 2：
    输入：s = "00000000", k = 3
    输出："000"

    数据范围：
    1 <= s.length <= 100
    2 <= k <= 100
    s 仅由数字字符组成

@解题思路
    按题意模拟：
    1. arr 存当前串每位数字；len(s) <= k 时直接返回原串；
    2. 每轮按 k 切片分组求和，拼接成新串后重新解析每位数字——
       这一步是关键：和可能是两位数（如 13），下一轮的分组对象是
       新串的字符而非「和」，必须回到逐位表示；
    3. 每轮长度至少缩小到 ceil(n/k) 位的量级，轮数 O(log n)。

    时间复杂度 O(n·log_k n)（每轮 O(n)，长度按除以 k 缩减），空间复杂度 O(n)

来源：LeetCode
链接：https://leetcode.cn/problems/calculate-digit-sum-of-a-string/description/
"""


class Solution:
    def digitSum(self, s: str, k: int) -> str:
        ret = s
        arr = [int(i) for i in ret]
        while len(ret) > k:
            groups = [arr[i : i + k] for i in range(0, len(arr), k)]  # 最后一段可能不足 k
            arr = [sum(g) for g in groups]
            ret = "".join(map(str, arr))
            arr = [int(i) for i in ret]  # 和可能是两位数，按新串逐位重新解析

        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.digitSum("11111222223", 3) == "135"
    assert solution.digitSum("00000000", 3) == "000"

    # ---- 多位数和级联：经历 6 轮才到长度 <= k（期望值由参考实现机器算出）----
    assert solution.digitSum("01234567890", 2) == "27"

    # ---- 长度本就不超过 k：原样返回 ----
    assert solution.digitSum("1234", 4) == "1234"
    assert solution.digitSum("1", 2) == "1"

    # ---- 大和触发两位数拆分重组 ----
    assert solution.digitSum("999999999", 3) == "36"


if __name__ == "__main__":
    test_solution()
    print("✅ No.2243 全部测试通过")
