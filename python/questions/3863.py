"""
@file 3863.py
@brief LeetCode 3863. 将字符串排序的最小操作次数（Minimum Operations to Sort a String）

@题目描述
    给你一个由小写英文字母组成的字符串 s。
    一次操作中，你可以选择 s 的任意子字符串（但不能是整个字符串），并将其按非降序字母顺序排序。
    返回使 s 变为非降序有序的最少操作次数；如果不可能，返回 -1。

@示例
    示例 1：
    输入：s = "dog"
    输出：1
    解释：对子串 "og" 排序得 "go"，s 变为 "dgo"，已经有序。

    示例 2：
    输入：s = "card"
    输出：2
    解释：先排序 "car" 得 "acrd"，再排序 "rd" 得 "acdr"。

    示例 3：
    输入：s = "gf"
    输出：-1
    解释：长度为 2 时只能选单个字符的子串，排序不产生任何变化，不可能有序。

@解题思路
    按最值位置分类讨论（mn 为最小字符，mx 为最大字符）：
    1. 串已非降序 → 0；
    2. 长度为 2 且无序 → -1（真子串只剩单个字符，排序是无效操作）；
    3. s[0] == mn 或 s[n-1] == mx → 1（排序另一侧后整体必有序）；
    4. mn/mx 出现在中间 s[1..n-2] → 2（先换到端点，再排序剩余部分）；
    5. 其余情况（s[0] == mx 且 s[n-1] == mn，如 "cba"）→ 3。

    Python 陷阱：s 是 str 而 sorted(s) 返回 list，直接写 s == sorted(s) 恒为
    False（str 与 list 比较不报错、只返回 False），必须用 "".join(sorted(s))
    或 list(s) == sorted(s) 让两边类型一致。

    时间复杂度 O(n log n)（排序检查有序性），空间复杂度 O(n)

来源：LeetCode
链接：https://leetcode.cn/problems/minimum-operations-to-sort-a-string/description/
"""


class Solution:
    def minOperations(self, s: str) -> int:
        n = len(s)
        if s == "".join(sorted(s)):  # sorted(s) 是 list，需 join 回 str 再比较
            return 0
        if n == 2:
            return -1

        mx = max(s)
        mn = min(s)
        if s[0] == mn or s[n - 1] == mx:
            return 1
        for i in range(1, n - 1):
            if s[i] == mx or s[i] == mn:
                return 2
        return 3


def test_solution() -> None:
    solution = Solution()
    assert solution.minOperations("klo") == 0  # 已有序（含 join 比较正确性）
    assert solution.minOperations("dog") == 1  # 官方示例 1：排序 "og" 一次到位
    assert solution.minOperations("card") == 2  # 官方示例 2
    assert solution.minOperations("gf") == -1  # 官方示例 3：长度 2 无解
    assert solution.minOperations("bdac") == 2  # 最值出现在中间
    assert solution.minOperations("cba") == 3  # 最大在首、最小在尾


if __name__ == "__main__":
    test_solution()
    print("✅ No.3863 全部测试通过")
