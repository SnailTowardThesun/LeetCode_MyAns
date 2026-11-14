"""
@file hot100_49.py
@brief LeetCode 49. 字母异位词分组（Group Anagrams）— HOT 100

@题目描述
    给你一个字符串数组 strs，将字母异位词组合在一起。字母异位词是由重新排列源单词的
    所有字母得到的新单词，例如 "eat" 的字母异位词有 "ate"、"tea"。
    可以按任意顺序返回结果列表。

@示例
    示例 1：
    输入：strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
    输出：[["bat"], ["nat", "tan"], ["ate", "eat", "tea"]]

    示例 2：
    输入：strs = [""]
    输出：[[""]]

    示例 3：
    输入：strs = ["a"]
    输出：[["a"]]

    数据范围：
    1 <= strs.length <= 1e4
    0 <= strs[i].length <= 100
    strs[i] 仅包含小写字母

@解题思路
    排序串作哈希键：
    1. 异位词的本质特征：排序后的结果完全相同（"eat"/"tea"/"ate" 排序后都是 "aet"），
       这个特征天然适合做哈希表的 key；
    2. 遍历每个字符串，把排序结果作 key、原字符串追加到对应分组——
       defaultdict(list) 的自动建组正对应 C++ unordered_map operator[] 的语义，
       一行完成「查找 + 插入」；
    3. 收集哈希表所有 value 即答案，分组内顺序与输入顺序一致。

    时间复杂度 O(n·k·log k)，n 为串数、k 为串最大长度（每个串排序）
    空间复杂度 O(n·k)
    进阶：用 26 长度字符计数串作 key 可优化到 O(n·k)

来源：LeetCode
链接：https://leetcode.cn/problems/group-anagrams/description/
"""

from collections import defaultdict


class Solution:
    def groupAnagrams(self, strs: list[str]) -> list[list[str]]:
        container: defaultdict[str, list[str]] = defaultdict(list)
        for s in strs:
            key = "".join(sorted(s))  # 异位词排序后相同，作分组键
            container[key].append(s)  # key 不存在时自动建空组，一行完成查找+插入
        return list(container.values())


def test_solution() -> None:
    solution = Solution()

    def canonical(result: list[list[str]]) -> list[list[str]]:
        """分组间与组内都排序成规范形，消除「任意顺序返回」的干扰"""
        return sorted(sorted(g) for g in result)

    # ---- 官方示例 1：三组异位词 ----
    assert canonical(solution.groupAnagrams(["eat", "tea", "tan", "ate", "nat", "bat"])) == [
        ["ate", "eat", "tea"],
        ["bat"],
        ["nat", "tan"],
    ]

    # ---- 官方示例 2：单个空串自成一族 ----
    assert solution.groupAnagrams([""]) == [[""]]

    # ---- 官方示例 3：单字符 ----
    assert solution.groupAnagrams(["a"]) == [["a"]]

    # ---- 全部互为异位词：只分一组 ----
    assert canonical(solution.groupAnagrams(["abc", "cba", "bca"])) == [["abc", "bca", "cba"]]

    # ---- 无任何异位词：各自成组 ----
    assert canonical(solution.groupAnagrams(["ab", "cd"])) == [["ab"], ["cd"]]


if __name__ == "__main__":
    test_solution()
    print("✅ No.49（HOT 100）全部测试通过")
