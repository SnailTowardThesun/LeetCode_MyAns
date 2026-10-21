"""
@file top150_208.py
@brief LeetCode 208. 实现 Trie (前缀树)

@题目描述
    Trie（发音类似 "try"）或者说前缀树是一种树形数据结构，用于高效地存储和检索字符串
    数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。
    请你实现 Trie 类：
    - Trie() 初始化前缀树对象。
    - void insert(String word) 向前缀树中插入字符串 word。
    - boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即在检索之前
      已经插入）；否则返回 false。
    - boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为
      prefix，返回 true；否则返回 false。

@示例
    输入：["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
         [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
    输出：[null, null, true, false, true, null, true]

@解题思路
    节点即树：Trie 类本身就是一个节点，持有 is_end（是否为某个单词的结尾）和
    child（字符 -> 子节点）两个字段，根节点就是用户创建的那个 Trie 实例。
    1. insert：从根出发逐字符下行，缺失的子节点现场创建，走到末尾把 is_end 置真；
    2. find：逐字符下行，中途断路返回 0；走完返回 2（是单词结尾）或 1（只是前缀）；
    3. search 要求 find == 2（完整单词），startsWith 只要求 find != 0（路径存在，
       无论是否同时也是单词结尾——这正是最容易写错的地方）。

    时间复杂度 insert / search / startsWith 均为 O(L)，L 为字符串长度；
    空间复杂度 O(总字符数)

来源：LeetCode
链接：https://leetcode.cn/problems/implement-trie-prefix-tree/description/
"""


class Trie:
    def __init__(self):
        self.is_end = False
        self.child = {}

    def insert(self, word: str) -> None:
        cur = self
        for ch in word:
            if cur.child.get(ch) is None:
                cur.child[ch] = Trie()
            cur = cur.child[ch]

        cur.is_end = True

    def find(self, word: str) -> int:
        cur = self
        for ch in word:
            if cur.child.get(ch) is None:
                return 0
            cur = cur.child[ch]

        return 2 if cur.is_end else 1

    def search(self, word: str) -> bool:
        return self.find(word) == 2

    def startsWith(self, prefix: str) -> bool:
        return self.find(prefix) != 0


def test_trie() -> None:
    # ---- 官方示例：search 精确匹配，startsWith 前缀匹配 ----
    t = Trie()
    t.insert("apple")
    assert t.search("apple")  # 已插入的完整单词
    assert not t.search("app")  # 只是前缀，不算单词
    assert t.startsWith("app")  # 前缀存在
    t.insert("app")  # 把前缀本身也插成单词
    assert t.search("app")

    # ---- 边界：单词是另一单词的前缀 ----
    t = Trie()
    t.insert("app")
    t.insert("apple")
    assert t.search("app") and t.search("apple")
    assert not t.search("ap") and not t.search("appl")
    assert t.startsWith("a") and t.startsWith("appl") and t.startsWith("apple")
    assert not t.startsWith("apx") and not t.startsWith("b")

    # ---- 边界：前缀等于完整单词 / 超长前缀 ----
    assert t.startsWith("app") and t.startsWith("apple")
    assert not t.startsWith("apples")  # 比任何已插入单词都长

    # ---- 边界：重复插入同一单词 ----
    t = Trie()
    t.insert("code")
    t.insert("code")
    assert t.search("code")

    # ---- 边界：多个单词共享分支 ----
    t = Trie()
    for w in ["a", "ab", "abc", "abd"]:
        t.insert(w)
    assert t.search("a") and t.search("ab") and t.search("abc") and t.search("abd")
    assert not t.search("abcd") and not t.search("ad")
    assert t.startsWith("ab") and t.startsWith("abc")

    # ---- 随机对拍：与「集合 + startswith」朴素解法对照 ----
    import random

    def rand_word(max_len: int = 6) -> str:
        alphabet = "abc"
        return "".join(random.choice(alphabet) for _ in range(random.randint(1, max_len)))

    def shrink(w: str) -> str:
        """取 w 的随机非空前缀，让查询落在已插入单词的路径上。"""
        return w[: random.randint(1, len(w))]

    random.seed(42)
    for _ in range(3):
        t = Trie()
        words: set[str] = set()
        for _ in range(500):
            op = random.random()
            if op < 0.3:
                w = rand_word()
                t.insert(w)
                words.add(w)
            elif op < 0.65:
                if words and random.random() < 0.6:
                    w = shrink(random.choice(sorted(words)))
                else:
                    w = rand_word()
                assert t.search(w) == (w in words), f"search({w!r}) 应为 {w in words}"
            else:
                if words and random.random() < 0.6:
                    w = shrink(random.choice(sorted(words)))
                else:
                    w = rand_word()
                expect = any(x.startswith(w) for x in words)
                assert t.startsWith(w) == expect, f"startsWith({w!r}) 应为 {expect}"


if __name__ == "__main__":
    test_trie()
    print("✅ top150_208 全部测试通过")
