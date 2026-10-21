"""
@file top150_149.py
@brief LeetCode 149. 直线上最多的点数

@题目描述
    给定一个平面上 n 个点的列表 points，其中 points[i] = [xi, yi]。
    返回位于同一条直线上点的最大数目。
    注意：points 中的所有点互不相同。

@示例
    示例 1：
    输入：points = [[1,1],[2,2],[3,3]]
    输出：3

    示例 2：
    输入：points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
    输出：4
    解释：直线 x + y = 5 经过 (1,4)、(2,3)、(3,2)、(4,1) 四个点。

@解题思路
    枚举锚点 + 斜率哈希：
    1. 依次把每个点 i 当作锚点，统计 i 到其后每个点 j 的斜率 k = dy / dx，
       斜率相同的点必与 i 同线；垂直线（dx = 0）统一记为 inf；
    2. 同一锚点下用哈希表 cnt 计数，出现最多的斜率就是过 i 的最多点共线数，
       结果 +1（补上锚点自己）；
    3. 所有点互不相同，保证不会出现重合点（重合点在所有方向上都共线）的歧义。
    注意浮点斜率理论上存在精度碰撞，更严谨的做法是把 dy/dx 用 gcd 约分成
    最简分数 (dy/g, dx/g) 并统一符号后作为哈希键。

    时间复杂度 O(n^2)，空间复杂度 O(n)（每轮锚点的哈希表）

来源：LeetCode
链接：https://leetcode.cn/problems/max-points-on-a-line/description/
"""

from cmath import inf


class Solution:
    def maxPoints(self, points: list[list[int]]) -> int:
        ret = 0
        for i in range(len(points)):
            cnt = {}
            for j in range(i + 1, len(points)):
                dx, dy = points[j][0] - points[i][0], points[j][1] - points[i][1]
                if dx != 0:
                    k = dy / dx
                else:
                    k = inf

                if cnt.get(k) is None:
                    cnt[k] = 1
                else:
                    cnt[k] += 1

                ret = max(ret, cnt[k])

        return ret + 1


if __name__ == "__main__":
    s = Solution()
    points = [[1, 1], [2, 2], [3, 3]]
    ret = s.maxPoints(points)
    print(ret)
