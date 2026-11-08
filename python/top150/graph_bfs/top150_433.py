"""
@file top150_433.py
@brief LeetCode 433. Minimum Genetic Mutation（最小基因变化）

@题目描述
    一条基因序列由 8 个字符表示，每个字符都属于 'A'、'C'、'G'、'T' 之一。

    假设我们要把一个基因序列 start 变化为目标基因序列 end，每次变化只改变
    一个字符。变化后的基因必须位于基因库 bank 中（合法的基因变化）。

    给定两个长度为 8 的基因序列 start 和 end，以及一个基因库 bank，找出并
    返回完成变化所需的最少变化次数。如果无法完成此基因变化，返回 -1。

    注：起始基因序列 start 是合法的，但它并不一定会出现在基因库中；
    end 必须出现在基因库中才是合法目标。

    提示：
    - start.length == end.length == bank[i].length == 8
    - start、end、bank[i] 仅由字符 'A'、'C'、'G'、'T' 组成
    - 0 <= bank.length <= 10

@示例
    示例 1：
    输入：start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
    输出：1

    示例 2：
    输入：start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
    输出：2
    解释："AACCGGTT" -> "AACCGGTA"（第 8 位 T->A）-> "AAACGGTA"（第 3 位 C->A）。

    示例 3：
    输入：start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
    输出：3
    解释：每次变化一位，三位依次从 A 变到 C。

@解题思路
    「每次变一个字符、中间状态必须在 bank 中」——把每个基因串看成节点，
    「恰有一个字符不同且后继在 bank 中」连边，start 到 end 的最少变化次数
    就是隐式图最短路，边权全 1——BFS。bank.length <= 10，图极小：

    1. BFS 从 startGene 出发，visited 集合判重（bank 转成 set 辅助判断也行，
       但 bank 本就 <= 10，直接逐个比对邻接即可）；
    2. 出队基因 curr 后，枚举 bank 中每个基因：逐位比较 8 个字符，
       恰有 1 位不同即为邻居（每步至多 10 x 8 次字符比较）；
    3. 首次遇到 endGene 返回当前步数 + 1；队空仍未到达返回 -1；
    4. endGene 不在 bank 中时不会有任何邻居等于它，自然走到 -1——无需特判；
       start == end 且 end 在 bank 中时，出队即命中，返回 0。

    时间复杂度 O(B^2 x L)（B = len(bank) <= 10，L = 8：每个入队基因都要与
    全库比对一遍邻接）；空间复杂度 O(B)（visited + 队列）。

来源：LeetCode
链接：https://leetcode.cn/problems/minimum-genetic-mutation/description/
"""

from collections import deque


class Solution:
    def minMutation(self, startGene: str, endGene: str, bank: list[str]) -> int:
        def one_diff(a: str, b: str) -> bool:
            # 恰有一位字符不同（题目保证两串等长 8，strict=False 安全）
            return sum(x != y for x, y in zip(a, b, strict=False)) == 1

        visited = {startGene}
        queue = deque([(startGene, 0)])  # (基因串, 已变化次数)
        while queue:
            curr, steps = queue.popleft()
            if curr == endGene:
                return steps
            for gene in bank:
                if gene not in visited and one_diff(curr, gene):
                    visited.add(gene)
                    queue.append((gene, steps + 1))
        return -1


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：一步到位 ----
    assert solution.minMutation("AACCGGTT", "AACCGGTA", ["AACCGGTA"]) == 1

    # ---- 官方示例 2：借道 AACCGGTA，两步 ----
    assert solution.minMutation("AACCGGTT", "AAACGGTA", ["AACCGGTA", "AACCGCTA", "AAACGGTA"]) == 2

    # ---- 官方示例 3：三位逐个变，三步 ----
    assert solution.minMutation("AAAAACCC", "AACCCCCC", ["AAAACCCC", "AAACCCCC", "AACCCCCC"]) == 3

    # ---- end 不在 bank 中：目标非法，-1 ----
    assert solution.minMutation("AACCGGTT", "AACCGGTA", []) == -1

    # ---- bank 有基因但接不拢：与 start 差一位、与 end 差两位，链断裂 ----
    assert solution.minMutation("AACCGGTT", "AACCGGTA", ["AAACGGTT"]) == -1

    # ---- start == end 且在 bank 中：零次变化 ----
    assert solution.minMutation("AACCGGTA", "AACCGGTA", ["AACCGGTA"]) == 0


if __name__ == "__main__":
    test_solution()
    print("✅ No.433 全部测试通过")
