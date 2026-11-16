"""
@file hot100_56.py
@brief LeetCode 56. 合并区间（Merge Intervals）— HOT 100

@题目描述
    以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] =
    [starti, endi]。请你合并所有重叠的区间，并返回一个不重叠的区间数组，
    该数组需恰好覆盖输入中的所有区间（两个区间仅有一次接触点也视为重叠）。

@示例
    示例 1：
    输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
    输出：[[1,6],[8,10],[15,18]]
    解释：区间 [1,3] 和 [2,6] 重叠，将它们合并为 [1,6]。

    示例 2：
    输入：intervals = [[1,4],[4,5]]
    输出：[[1,5]]
    解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

    数据范围：
    1 <= intervals.length <= 1e4
    intervals[i].length == 2
    0 <= starti <= endi <= 1e4

@解题思路
    排序 + 一次线性合并：
    1. 按区间左端点排序后，能合并的区间必然相邻——只需一遍扫描；
    2. 对每个区间：左端点严格大于结果末区间的右端点则开新区间，
       否则（重叠或恰好相触）并入末区间，右端点取两者较大值
       （max 处理「嵌套区间」：如 [1,4] 吞并 [2,3] 时右端点不回缩）；
    3. sorted() 返回新列表，不改动调用方的原数组。

    时间复杂度 O(n log n)（排序主导），空间复杂度 O(n)（排序与结果）

来源：LeetCode
链接：https://leetcode.cn/problems/merge-intervals/description/
"""


class Solution:
    def merge(self, intervals: list[list[int]]) -> list[list[int]]:
        intervals = sorted(intervals)  # 新列表，按左端点排序；可合并者必相邻

        ret: list[list[int]] = []
        for left, right in intervals:
            if not ret or left > ret[-1][1]:  # 严格大于才分开；相触（==）也算重叠
                ret.append([left, right])
            else:
                ret[-1][1] = max(right, ret[-1][1])  # max 保证嵌套区间右端点不回缩

        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.merge([[1, 3], [2, 6], [8, 10], [15, 18]]) == [[1, 6], [8, 10], [15, 18]]
    assert solution.merge([[1, 4], [4, 5]]) == [[1, 5]]  # 相触视为重叠

    # ---- 输入无序：排序后正常合并（期望值由暴力对照机器算出）----
    assert solution.merge([[1, 3], [2, 6], [15, 18], [8, 10]]) == [[1, 6], [8, 10], [15, 18]]
    assert solution.merge([[5, 6], [1, 2]]) == [[1, 2], [5, 6]]

    # ---- 嵌套区间：右端点取 max 不回缩 ----
    assert solution.merge([[1, 4], [2, 3]]) == [[1, 4]]

    # ---- 单区间 / 重复区间 ----
    assert solution.merge([[1, 1]]) == [[1, 1]]
    assert solution.merge([[2, 2], [2, 2]]) == [[2, 2]]


if __name__ == "__main__":
    test_solution()
    print("✅ No.56（HOT 100）全部测试通过")
