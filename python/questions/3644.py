"""
@file 3644.py
@brief LeetCode 3644. 排序排列

@题目描述
    给你一个长度为 n 的整数数组 nums，其中 nums 是范围 [0..n-1] 内所有数字的一个排列。
    你可以在满足条件 nums[i] AND nums[j] == k 的情况下交换下标 i 和 j 的元素，
    其中 AND 表示按位与操作，k 是一个非负整数。
    返回可以使数组按非递减顺序排序的最大值 k（允许进行任意次这样的交换）。
    如果 nums 已经是有序的，返回 0。

@示例
    示例 1：
    输入：nums = [0,3,2,1]
    输出：1
    解释：k=1 时交换 nums[1]=3 和 nums[3]=1（3 AND 1 == 1），得到 [0,1,2,3]。

    示例 2：
    输入：nums = [0,1,3,2]
    输出：2
    解释：k=2 时交换 nums[2]=3 和 nums[3]=2（3 AND 2 == 2）。

    示例 3：
    输入：nums = [3,2,1,0]
    输出：0

@解题思路
    关键观察：k 是全体错位元素共同决定的，不是每个错位环各自最优取 max。
    一次合法交换要求两个值 AND 恰好等于 k，即两个值都包含 k 的全部 1 位；
    反过来说，某个错位值缺少的位，任何包含它的交换都无法带上——
    所以最大可行 k 就是所有错位值（nums[i] != i）的按位与：
    1. ret 初始化为 -1（全 1 位），逐个与错位值相与；
    2. 全部在位时 ret 保持 -1，按题意返回 0。
    验证方式：对每个 k 在真实交换状态空间做 BFS 可达性检查，
    与公式解在随机排列上对拍一致（含"两个错位环要求不同 k、答案归 0"的用例）。

    时间复杂度 O(n)，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/maximum-k-to-sort-a-permutation/description/
"""


class Solution:
    def sortPermutation(self, nums: list[int]) -> int:
        ret = -1
        for i in range(len(nums)):
            if nums[i] == i:
                continue
            ret &= nums[i]
        return 0 if ret == -1 else ret


def _can_sort_with_k(nums: list[int], k: int) -> bool:
    """朴素参照：固定 k 时，在真实交换状态空间里 BFS 判断能否排成非递减。"""
    from collections import deque

    start, target = tuple(nums), tuple(range(len(nums)))
    if start == target:
        return True
    seen = {start}
    q = deque([start])
    while q:
        s = q.popleft()
        for i in range(len(s)):
            for j in range(i + 1, len(s)):
                if s[i] & s[j] == k:
                    nxt = list(s)
                    nxt[i], nxt[j] = nxt[j], nxt[i]
                    t = tuple(nxt)
                    if t == target:
                        return True
                    if t not in seen:
                        seen.add(t)
                        q.append(t)
    return False


def _brute_answer(nums: list[int]) -> int:
    """对拍真值：k 从高到低第一个能排序的；已有序按题意直接返回 0。"""
    if nums == list(range(len(nums))):
        return 0
    for k in range(len(nums) - 1, -1, -1):
        if _can_sort_with_k(nums, k):
            return k
    return -1


def test_sort_permutation() -> None:
    # ---- 官方示例 ----
    s = Solution()
    assert s.sortPermutation([0, 3, 2, 1]) == 1  # 交换 3 和 1（3 AND 1 == 1）
    assert s.sortPermutation([0, 1, 3, 2]) == 2  # 交换 3 和 2（3 AND 2 == 2）
    assert s.sortPermutation([3, 2, 1, 0]) == 0  # 只有 k=0 可行

    # ---- 已有序按题意返回 0（即使任何 k 都"无需交换"）----
    assert s.sortPermutation([0, 1, 2, 3]) == 0
    assert s.sortPermutation([0]) == 0  # 单元素

    # ---- 错位集合的按位与 ----
    assert s.sortPermutation([1, 0]) == 0  # 错位 {1,0}，AND 含 0 位直接归零
    assert s.sortPermutation([0, 1, 2, 3, 4, 5, 7, 6]) == 6  # 错位 {7,6}，110 & 111 = 6

    # ---- 两个错位环各自可排但要求不同的 k：{3,2} 要 k=2，{6,4} 要 k=4 ----
    # 单一 k 能否借助中间元素同时排好两个环？用状态空间真值断言
    two_cycles = [0, 1, 3, 2, 6, 5, 4, 7]
    assert s.sortPermutation(two_cycles) == _brute_answer(two_cycles)

    # ---- 随机对拍：与状态空间 BFS 真值对照 ----
    import random

    random.seed(42)
    for _ in range(200):
        n = random.randint(1, 6)
        perm = list(range(n))
        random.shuffle(perm)
        want = _brute_answer(perm)
        got = s.sortPermutation(perm)
        assert got == want, f"nums={perm}: got {got}, want {want}"


if __name__ == "__main__":
    test_sort_permutation()
    print("✅ 3644 全部测试通过")
