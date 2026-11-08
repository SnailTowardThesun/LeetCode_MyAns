"""
@file top150_127.py
@brief LeetCode 127. Word Ladder（单词接龙）

@题目描述
    字典 wordList 中从单词 beginWord 到 endWord 的 转化序列 是一个按下标
    递增的单词序列：beginWord -> s1 -> s2 -> ... -> sk，满足：
    - 每一对相邻的单词恰好只差一个字母；
    - 序列中的每个 s_i（1 <= i <= k）都在 wordList 中——注意 beginWord
      不需要在 wordList 中；
    - sk == endWord。

    给你两个单词 beginWord 和 endWord，以及一个字典 wordList，返回从
    beginWord 到 endWord 的 最短转化序列 中的 单词数目 。如果不存在这样的
    转化序列，返回 0。

    提示：
    - 1 <= beginWord.length <= 10
    - endWord.length == beginWord.length
    - 1 <= wordList.length <= 5000
    - wordList[i].length == beginWord.length
    - beginWord、endWord 和 wordList[i] 由小写英文字母组成
    - beginWord != endWord
    - wordList 中的所有单词 互不相同

@示例
    示例 1：
    输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
    输出：5
    解释：最短转化序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog"，返回 5 个单词。

    示例 2：
    输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
    输出：0
    解释：endWord "cog" 不在字典中，无法完成转化。

@解题思路
    与 433（最小基因变化）同族：单词为节点、「恰差一个字母」连边，BFS 求
    隐式图最短路。两处关键差异/陷阱：

    1. 返回值是转化序列中的【单词数目】（= 边数 + 1），不是变化次数——
       hit -> hot -> dot -> dog -> cog 是 5 不是 4；
    2. N = 5000 个词两两比对邻接是 O(N^2 x L) ≈ 2.5 x 10^8 次字符比较，
       Python 会超时——用「通配符分桶」预建邻接：每个单词生成 L 个模式串
       （如 "hot" -> *ot / h*t / ho*），同一个模式桶里的单词两两互为邻居：
       - 建桶：O(N x L^2)（切片拼接）；
       - BFS 出队单词后，展开它所属的 L 个桶即为全部邻居；
       - 桶展开后清空（每桶只展开一次，已入队的词无需再见），
         总转移均摊 O(N x L)；
    3. BFS 从 beginWord 出发（它不必在字典中）；endWord 必须在字典中，
       不在则直接返回 0 提前剪枝；visited 在入队时标记。

    首次命中 endWord 时返回当前层数（层数从 1 起算，beginWord 即第 1 个
    单词）。

    时间复杂度 O(N x L^2)（建桶 + BFS，均摊）；空间复杂度 O(N x L^2)
    （桶中存切片字符串 + visited）。

来源：LeetCode
链接：https://leetcode.cn/problems/word-ladder/description/
"""

from collections import deque


class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: list[str]) -> int:
        word_set = set(wordList)
        if endWord not in word_set:
            return 0  # endWord 不在字典中，提前剪枝

        n = len(beginWord)
        # 通配符分桶：模式串 -> 同桶单词（同桶两两互为邻居）
        buckets: dict[str, list[str]] = {}
        for word in wordList:
            for i in range(n):
                buckets.setdefault(word[:i] + "*" + word[i + 1 :], []).append(word)

        visited = {beginWord}
        queue = deque([(beginWord, 1)])  # (单词, 转化序列中的单词数)
        while queue:
            curr, count = queue.popleft()
            if curr == endWord:
                return count
            for i in range(n):
                bucket = buckets.get(curr[:i] + "*" + curr[i + 1 :])
                if not bucket:
                    continue
                for word in bucket:
                    if word not in visited:
                        visited.add(word)
                        queue.append((word, count + 1))
                bucket.clear()  # 桶内单词已全部入队，清空避免重复展开
        return 0


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：hit->hot->dot->dog->cog，5 个单词 ----
    assert solution.ladderLength("hit", "cog", ["hot", "dot", "dog", "lot", "log", "cog"]) == 5

    # ---- 官方示例 2：endWord 不在字典，0 ----
    assert solution.ladderLength("hit", "cog", ["hot", "dot", "dog", "lot", "log"]) == 0

    # ---- 一条边：返回 2 个单词（不是 1 次变化） ----
    assert solution.ladderLength("hit", "hot", ["hot"]) == 2

    # ---- 邻居缺失走不通：hit 与 dot 差两位，0 ----
    assert solution.ladderLength("hit", "dot", ["dot"]) == 0

    # ---- endWord 在字典但与 beginWord 差三位且无桥，0 ----
    assert solution.ladderLength("hit", "cog", ["cog"]) == 0

    # ---- beginWord 也在字典中（允许但非必需） ----
    assert solution.ladderLength("a", "c", ["a", "b", "c"]) == 2

    # ---- 桶共享中间层：hot 同时是 hit 的邻居和 dot 的跳板 ----
    assert solution.ladderLength("hit", "cog", ["hot", "dot", "dog", "cog"]) == 5


if __name__ == "__main__":
    test_solution()
    print("✅ No.127 全部测试通过")
