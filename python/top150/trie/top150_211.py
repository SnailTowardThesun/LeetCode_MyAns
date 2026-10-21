"""
@file top150_211.py
@brief LeetCode 211. 添加与搜索单词 - 数据结构设计

@题目描述
    请你设计一个数据结构，支持添加新单词和查找字符串是否与任何先前添加的字符串匹配。
    实现词典类 WordDictionary：
    - WordDictionary() 初始化词典对象。
    - void addWord(word) 将 word 添加到词典中，可以对它进行匹配。
    - bool search(word) 如果数据结构中存在字符串与 word 匹配，返回 true；否则返回 false。
      word 中可能包含一些 '.'，每个 '.' 都可以表示任何一个字母。

@示例
    输入：["WordDictionary", "addWord", "addWord", "addWord", "search", "search", "search", "search"]
         [[], ["bad"], ["dad"], ["mad"], ["pad"], ["bad"], [".ad"], ["b.."]]
    输出：[null, null, null, null, false, true, true, true]

@解题思路
    Trie + 逐层候选集合（BFS 式展开）：
    1. 节点结构与 208 题一致：child（字符 -> 子节点）+ is_end（单词结尾标记），
       WordDictionary 类自身就是根节点；
    2. addWord 与普通 Trie 相同，逐字符下行插入；
    3. search 维护"当前层候选节点集合" curs，每个字符消耗一层：
       - '.'：把所有候选的所有孩子收进下一层；
       - 实字符：每个候选中名为该字符的孩子收进下一层；
       - 某层收完为空即失败（长度不同/断路自然返回 False）；
       - 全部字符消耗完后，候选中任一 is_end 为真即命中。
    两个易错点：
    - 多候选时不能只取第一个命中的就 break——其他分支可能才是词尾；
    - 字符接不上时必须让候选集落空，否则会拿旧候选的 is_end 误判成功。

    addWord O(L)；search 无点时 O(L)，最坏 O(26^(L-1))；空间 O(总字符数)

来源：LeetCode
链接：https://leetcode.cn/problems/design-add-and-search-words-data-structure/description/
"""


class WordDictionary:
    def __init__(self):
        self.child = {}
        self.is_end = False

    def addWord(self, word: str) -> None:
        cur = self
        for ch in word:
            if cur.child.get(ch) is None:
                cur.child[ch] = WordDictionary()
            cur = cur.child[ch]

        cur.is_end = True

    def search(self, word: str) -> bool:
        curs = [self]
        for ch in word:
            pre = curs
            curs = []
            for cur in pre:
                if ch == ".":
                    curs.extend(cur.child.values())
                elif cur.child.get(ch) is not None:
                    curs.append(cur.child[ch])

        for cur in curs:
            if cur.is_end:
                return True
        return False


def _naive_search(words: set[str], pattern: str) -> bool:
    """朴素参照解法：'.' 匹配恰好一个字符，仅用于对拍。"""
    return any(
        len(w) == len(pattern) and all(pc == "." or pc == wc for pc, wc in zip(pattern, w, strict=True)) for w in words
    )


def test_word_dictionary() -> None:
    # ---- 官方示例 ----
    wd = WordDictionary()
    wd.addWord("bad")
    wd.addWord("dad")
    wd.addWord("mad")
    assert not wd.search("pad")  # 精确失配
    assert wd.search("bad")  # 精确命中
    assert wd.search(".ad")  # 点在开头
    assert wd.search("b..")  # 点在尾部连续

    # ---- 通配符语义：'.' 恰好匹配一个字符 ----
    wd = WordDictionary()
    wd.addWord("a")
    assert wd.search(".")  # 单字符单词能被 "." 命中
    wd = WordDictionary()
    wd.addWord("ab")
    assert not wd.search(".")  # "." 只匹配一个字符，不匹配两个
    assert wd.search("..")
    assert not wd.search("...")  # 没有三个字符的单词

    # ---- 点在各个位置 ----
    wd = WordDictionary()
    wd.addWord("abc")
    assert wd.search("a.c") and wd.search(".bc") and wd.search("ab.")
    assert wd.search("...")  # 全点
    assert not wd.search("abcd")  # 长了
    assert not wd.search("a..c")  # 长度不同直接不匹配
    assert not wd.search("a.d")  # 点位置对了但实字符失配
    assert wd.search(".b.")  # 中间实字符命中，两端用点
    assert not wd.search("xyz")

    # ---- 单词互为前缀 ----
    wd = WordDictionary()
    wd.addWord("a")
    wd.addWord("ab")
    assert wd.search("a") and wd.search("ab")
    assert wd.search(".") and wd.search("..")
    assert not wd.search("...")

    # ---- 重复添加同一单词 ----
    wd = WordDictionary()
    wd.addWord("dup")
    wd.addWord("dup")
    assert wd.search("dup") and wd.search("d.p") and wd.search("...")

    # ---- 空字典上查询 ----
    wd = WordDictionary()
    assert not wd.search("a")
    assert not wd.search(".")

    # ---- 随机对拍：与朴素解法对照 ----
    import random

    def rand_word(max_len: int = 5) -> str:
        alphabet = "ab"  # 小字母表，制造高频分支碰撞
        return "".join(random.choice(alphabet) for _ in range(random.randint(1, max_len)))

    def dotify(w: str) -> str:
        """把 w 的随机若干位置替换成 '.'，让查询落在已添加单词的路径上。"""
        return "".join("." if random.random() < 0.4 else ch for ch in w)

    random.seed(42)
    for _ in range(3):
        wd = WordDictionary()
        words: set[str] = set()
        for _ in range(600):
            if random.random() < 0.3:
                w = rand_word()
                wd.addWord(w)
                words.add(w)
            else:
                r = random.random()
                if words and r < 0.5:
                    p = dotify(random.choice(sorted(words)))  # 已加单词加点
                elif words and r < 0.7:
                    base = random.choice(sorted(words))  # 已加单词截断（造长度差）
                    p = base[: max(1, len(base) - random.randint(1, 2))]
                    if len(p) < len(base) and random.random() < 0.5:
                        p += "." * (len(base) - len(p))
                else:
                    p = dotify(rand_word())  # 纯随机模式
                expect = _naive_search(words, p)
                assert wd.search(p) == expect, f"search({p!r}) 应为 {expect}，词库={sorted(words)}"


if __name__ == "__main__":
    test_word_dictionary()
    print("✅ top150_211 全部测试通过")
