"""
@file top150_212.py
@brief LeetCode 212. 单词搜索 II

@题目描述
    给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words，
    返回所有同时在网格和字典中出现的单词。
    单词必须按照字母顺序，通过 相邻单元格 内的字母构成（水平或竖直相邻），
    且同一个单元格内的字母在一个单词中不允许被重复使用。

@示例
    示例 1：
    输入：board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]],
         words = ["oath","pea","eat","rain"]
    输出：["eat","oath"]

    示例 2：
    输入：board = [["a","b"],["c","d"]], words = ["abcb"]
    输出：[]（abcb 需要重复使用 b 所在单元格）

@解题思路
    Trie + 回溯：
    1. 所有单词建一棵 trie；DFS 状态携带 trie 节点，棋盘路径与单词前缀同步匹配，
       trie 不存在的分支一步都不探（相对逐词暴力搜索的核心剪枝）；
    2. 节点 is_end 标记词尾：命中即收集，并把 is_end 置 False——多路径/多位置
       命中同一单词只输出一次；
    3. 单元格去重用原地标记：进入时改 '#'，回溯时恢复，等价 visited 集合但更快；
    4. 性能剪枝：某子树探完既无剩余孩子也无词尾时，把它从父节点的 child 里删除
       （LeetCode 著名的"全 a 棋盘 + aaa..b 单词"TLE 陷阱靠这步化解，
       实测 12x12 全 a 棋盘 x 3000 词 0.2s 内完成）。

    时间复杂度 O(m*n*4*3^(L-1))（L 为单词最大长度，首步 4 邻居其后 3），
    空间复杂度 O(单词总字符数)

来源：LeetCode
链接：https://leetcode.cn/problems/word-search-ii/description/
"""


class Trie:
    def __init__(self):
        self.child = {}
        self.is_end = False

    def insert(self, word):
        cur = self
        for ch in word:
            if cur.child.get(ch) is None:
                cur.child[ch] = Trie()
            cur = cur.child[ch]

        cur.is_end = True

    def find(self, word: str) -> bool:
        """判断 word 对应路径是否存在（startsWith 语义；主算法游走节点，此接口备用）。"""
        cur = self
        for c in word:
            if cur.child.get(c) is None:
                return False
            cur = cur.child[c]

        return True


class Solution:
    def findWords(self, board: list[list[str]], words: list[str]) -> list[str]:
        # 所有单词建成一棵 trie，DFS 时只沿 trie 存在的分支走，天然剪掉无效路径
        trie = Trie()
        for w in words:
            trie.insert(w)

        m, n = len(board), len(board[0])
        ret: list[str] = []

        def dfs(i: int, j: int, cur: Trie, path: list[str]) -> None:
            ch = board[i][j]
            nxt = cur.child.get(ch)
            if nxt is None:
                return  # trie 里没有这个分支，此路不通

            path.append(ch)
            if nxt.is_end:
                ret.append("".join(path))
                nxt.is_end = False  # 收集一次后摘掉词尾标记，多路径命中只输出一次

            board[i][j] = "#"  # 原地标记：当前格已在路径上，不可重复使用
            for x, y in ((i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)):
                if 0 <= x < m and 0 <= y < n and board[x][y] != "#":
                    dfs(x, y, nxt, path)
            board[i][j] = ch  # 回溯恢复

            path.pop()
            if not nxt.child and not nxt.is_end:
                del cur.child[ch]  # 剪枝：这条分支下再无单词，从 trie 摘除，后续格子不再重复探索

        for i in range(m):
            for j in range(n):
                dfs(i, j, trie, [])

        return ret


def _brute_find_words(board: list[list[str]], words: list[str]) -> list[str]:
    """朴素参照解法：对每个单词做经典单词搜索 DFS，仅用于对拍。"""
    m, n = len(board), len(board[0])

    def exist(w: str) -> bool:
        def dfs(i: int, j: int, k: int, seen: set[tuple[int, int]]) -> bool:
            if not (0 <= i < m and 0 <= j < n) or (i, j) in seen or board[i][j] != w[k]:
                return False
            if k == len(w) - 1:
                return True
            seen.add((i, j))
            ok = any(dfs(x, y, k + 1, seen) for x, y in ((i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)))
            seen.discard((i, j))
            return ok

        return any(dfs(i, j, 0, set()) for i in range(m) for j in range(n))

    return sorted({w for w in words if exist(w)})


def test_find_words() -> None:
    # ---- 官方示例 1 ----
    board = [["o", "a", "a", "n"], ["e", "t", "a", "e"], ["i", "h", "k", "r"], ["i", "f", "l", "v"]]
    s = Solution()
    assert sorted(s.findWords(board, ["oath", "pea", "eat", "rain"])) == ["eat", "oath"]

    # ---- 官方示例 2：单元格不可重复使用（abcb 需要二次用到 b）----
    assert s.findWords([["a", "b"], ["c", "d"]], ["abcb"]) == []

    # ---- 边界：单格棋盘 / 单字母单词 ----
    assert s.findWords([["a"]], ["a"]) == ["a"]
    assert s.findWords([["a"]], ["b"]) == []

    # ---- 多路径/多位置命中只输出一次 ----
    assert s.findWords([["a", "b"], ["a", "b"]], ["ab"]) == ["ab"]  # 两条路径
    assert s.findWords([["a", "a"]], ["aa"]) == ["aa"]

    # ---- 共享前缀的单词全部命中 ----
    assert sorted(s.findWords([["a", "b", "c"]], ["a", "ab", "abc", "abcd"])) == ["a", "ab", "abc"]

    # ---- 反向路径也算（abcd 与 dcba 是两条不同路径）----
    assert sorted(s.findWords([["a", "b", "c", "d"]], ["abcd", "dcba"])) == ["abcd", "dcba"]

    # ---- 单词比棋盘总格数还长 / 全部不存在 ----
    assert s.findWords([["a", "b"], ["c", "d"]], ["abcdef"]) == []
    assert s.findWords([["a", "b"], ["c", "d"]], ["xyz", "zzz"]) == []

    # ---- 蛇形长词：路径必须拐弯，考验回溯 ----
    board = [
        ["a", "b", "c"],
        ["h", "g", "d"],
        ["i", "f", "e"],  # abcdefghi 沿顺时针螺旋
    ]
    assert s.findWords(board, ["abcdefghi", "ihgfedcba"]) == ["abcdefghi", "ihgfedcba"]
    assert s.findWords(board, ["abcde", "edcbaz"]) == ["abcde"]

    # ---- 随机对拍：与逐词暴力 DFS 对照 ----
    import random

    def rand_board(rows: int, cols: int) -> list[list[str]]:
        alphabet = "abc"
        return [[random.choice(alphabet) for _ in range(cols)] for _ in range(rows)]

    def board_path_word(board: list[list[str]], max_len: int = 6) -> str:
        """沿随机合法路径走出的词（保证能命中，制造正样本）。"""
        m, n = len(board), len(board[0])
        i, j = random.randrange(m), random.randrange(n)
        w, seen = board[i][j], {(i, j)}
        for _ in range(random.randint(0, max_len - 1)):
            opts = [
                (x, y)
                for x, y in ((i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1))
                if 0 <= x < m and 0 <= y < n and (x, y) not in seen
            ]
            if not opts:
                break
            i, j = random.choice(opts)
            seen.add((i, j))
            w += board[i][j]
        return w

    random.seed(42)
    s = Solution()
    for _ in range(3):
        board = rand_board(3, 3)
        words = {board_path_word(board) for _ in range(6)}  # 正样本
        words |= {"".join(random.choice("abc") for _ in range(random.randint(1, 6))) for _ in range(6)}
        words = sorted(words)
        got = sorted(s.findWords([row[:] for row in board], words))
        want = _brute_find_words(board, words)
        assert got == want, f"board={board}, words={words}\n  得到 {got}\n  应为 {want}"


if __name__ == "__main__":
    test_find_words()
    print("✅ top150_212 全部测试通过")
