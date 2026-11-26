"""
@file 3360.py
@brief LeetCode 3360. 移除石头游戏（Stone Removal Game）

@题目描述
    给定 1 到 50 颗石头，Alice 先手，与 Bob 轮流取石。第一手必须取 10 颗，
    之后每手必须比前一手少取 1 颗。无法取够的玩家输。返回 Alice 是否获胜。

@示例
    n = 12 时，Alice 取走 10 颗，剩下 2 颗，Bob 无法取 9 颗，返回 True。
    n = 1 时，Alice 无法完成第一手，返回 False。

@解题思路
    helpers 保存从 10 到 1 的取石数。下标 i 等于已完成的手数，取不够 helpers[i] 时判断胜负。
    已完成奇数手说明轮到 Bob 失败，Alice 获胜；偶数手则轮到 Alice 失败。
    前八手共需 52 颗，超过 n 的上限，所以循环最多成功七次。时间和额外空间均为 O(1)。
"""


class Solution:
    def canAliceWin(self, n: int) -> bool:
        if n < 10:
            return False

        helpers =list(range(10, 0, -1))
        for i in range(len(helpers)):
            if n < helpers[i]:
                return True if i % 2 == 1 else False
            n = n - helpers[i]

        return False

if __name__ == '__main__':
    s = Solution()
    ret = s.canAliceWin(n = 12)
    print(ret)


def test_solution() -> None:
    solution = Solution()
    # Alice 刚完成第 1、3、5、7 手的累计石数分别为 10、27、40、49。
    for n in range(1, 51):
        expected = 10 <= n < 19 or 27 <= n < 34 or 40 <= n < 45 or 49 <= n <= 50
        assert solution.canAliceWin(n) == expected, n
