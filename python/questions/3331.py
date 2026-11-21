"""
@file 3331.py
@brief LeetCode 3331. 修改后子树的大小（Find Subtree Sizes After Changes）

@题目描述
    给定一个 n 个节点的有根树，节点编号 0 到 n-1，编号 0 是根节点。parent[i]
    是节点 i 的父节点，parent[0] == -1；字符串 s，s[i] 是节点 i 上的字符。
    你需要对每个节点 i 找到最近的祖先 j（j 是 i 的祖先），满足 s[j] == s[i]，
    将 parent[i] 修改为 j（对每个节点基于原树独立判断）。修改全部完成后，
    返回大小为 n 的数组 ans，其中 ans[i] 是节点 i 的子树大小。

@示例
    示例 1：
    输入：parent = [-1,0,0,1,1,1], s = "abaabc"
    输出：[6,3,1,1,1,1]
    解释：节点 3('a') 最近的 'a' 祖先是 0，改挂到 0；
    其余节点的最近同字符祖先就是原父节点（或不存在），不变。
    新树：0 → {1,2,3}，1 → {4,5}。

    示例 2：
    输入：parent = [-1,0,4,0,1], s = "ababa"
    输出：[5,1,1,1,2]

    数据范围：
    1 <= n <= 1e5
    parent[0] == -1，0 < parent[i] <= n-1（对 i > 0，此处按题意为 0 <= parent[i] < n）
    s 仅由小写英文组成

@解题思路
    原树 DFS + 字符栈「重归属」：
    1. 按原树建孩子表，从根 DFS；records[c] 是当前 DFS 路径上字符为 c 的
       节点栈（进入压栈、离开弹栈，栈顶即「最近的同字符祖先」）；
    2. 进入 u：ans[u] += 1（自身），s[u] 压栈；
    3. 对每个原孩子 i：先递归算完 i 的新子树（返回时 ans[i] 已是 i 在新树
       中的子树大小），再决定归属——records[s[i]] 非空则栈顶是 i 的最近同
       字符祖先（改挂目标 nu），为空则保持原父 u；
    4. ans[nu] += ans[i]：把 i 的整棵新子树搬到 nu 名下；注意 ans[i] 本身
       不清零——它就是 i 的最终子树大小；
    5. 全程先算完再归属，天然处理「改挂目标也在更深处被改挂」的级联情形。

    时间复杂度 O(n)，空间复杂度 O(n)
    注：递归实现依赖较深的栈，LeetCode 判题环境上限高可通过；本地 CPython
    默认递归上限 1000，测试用小规模用例覆盖等价边界即可。

来源：LeetCode
链接：https://leetcode.cn/problems/find-subtree-sizes-after-changes/description/
"""

from collections import defaultdict


class Solution:
    def findSubtreeSizes(self, parent: list[int], s: str) -> list[int]:
        n = len(parent)
        old_map: defaultdict[int, list[int]] = defaultdict(list)
        for i in range(1, n):
            old_map[parent[i]].append(i)  # 原树孩子表

        records: defaultdict[str, list[int]] = defaultdict(list)  # 字符 -> DFS 路径栈
        ans = [0] * n

        def helper(u: int) -> None:
            ans[u] += 1  # 自身
            records[s[u]].append(u)  # 进入压栈：栈顶即最近同字符祖先
            for i in old_map[u]:
                helper(i)  # 返回时 ans[i] 已是 i 在新树的子树大小
                nu = records[s[i]][-1] if records[s[i]] else u  # 改挂目标：无同字符祖先则维持原父
                ans[nu] += ans[i]  # 整棵新子树搬到 nu 名下，ans[i] 不清零
            records[s[u]].pop()  # 离开弹栈

        helper(0)

        return ans


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.findSubtreeSizes([-1, 0, 0, 1, 1, 1], "abaabc") == [6, 3, 1, 1, 1, 1]
    assert solution.findSubtreeSizes([-1, 0, 4, 0, 1], "ababa") == [5, 1, 1, 1, 2]

    # ---- 全同字符：改挂目标都是原父，树不变（期望值由暴力对照机器算出）----
    assert solution.findSubtreeSizes([-1, 0, 0], "aaa") == [3, 1, 1]

    # ---- 全异字符链：无任何改挂，子树大小即深度倒序 ----
    assert solution.findSubtreeSizes([-1, 0, 1, 2], "abcd") == [4, 3, 2, 1]

    # ---- 单节点 ----
    assert solution.findSubtreeSizes([-1], "a") == [1]

    # ---- 跨层改挂：节点 2('a') 跳过 'b' 挂到根；节点 3 的最近 'a' 祖先是原父 2，维持 ----
    assert solution.findSubtreeSizes([-1, 0, 1, 2], "abaa") == [4, 1, 2, 1]


if __name__ == "__main__":
    test_solution()
    print("✅ No.3331 全部测试通过")
