"""
@file 1385.py
@brief LeetCode 1385. 两个数组间的距离值（Find the Distance Value Between Two Arrays）

@题目描述
    给你两个整数数组 arr1 和 arr2，以及一个整数 d，请你返回两个数组间的「距离值」。
    「距离值」定义为满足此条件的元素数目：对于元素 arr1[i]，
    不存在任何元素 arr2[j] 满足 |arr1[i] - arr2[j]| <= d。

@示例
    示例 1：
    输入：arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
    输出：2
    解释：4 与 arr2 中所有元素的距离都大于 2，符合要求；5 同理；
    而 8 与 10 的距离为 2（<= d）、与 8 的距离为 0（<= d），不符合。

    示例 2：
    输入：arr1 = [1,4,2,3], arr2 = [-4,-3,6,10,20,30], d = 3
    输出：2

    数据范围：
    1 <= arr1.length, arr2.length <= 500
    -1000 <= arr1[i], arr2[j] <= 1000
    0 <= d <= 100

@解题思路
    暴力枚举 + 提前剪枝：
    1. 「距离值」就是一个计数器：统计 arr1 中有多少元素 i，
       满足 arr2 中任何元素 k 都有 |i - k| > d，
       即 arr2 与 i 的邻域区间 [i-d, i+d] 无交集；
    2. 对每个 i 先假设成立（is_match = True），内层一旦发现 |i-k| <= d
       立即置 False 并 break——找到第一个邻居即可否定，后续元素不必再看；
    3. 数据范围仅 500 x 500（至多 25 万次比较），O(n*m) 绰绰有余；
       若规模放大，可先排序 arr2 再用二分查找判断 [i-d, i+d] 内
       是否落有元素，优化到 O((n+m) log m)。

    时间复杂度 O(n*m)，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/find-the-distance-value-between-two-arrays/description/
"""


class Solution:
    def findTheDistanceValue(self, arr1: list[int], arr2: list[int], d: int) -> int:
        ret = 0
        for i in arr1:
            is_match = True  # 假设 i 符合：arr2 没有元素落在 [i-d, i+d]
            for k in arr2:
                if abs(i - k) <= d:  # 发现一个邻居即否定假设，提前跳出
                    is_match = False
                    break
            if is_match:
                ret += 1
        return ret


def test_solution() -> None:
    solution = Solution()
    # 官方示例
    assert solution.findTheDistanceValue([4, 5, 8], [10, 9, 1, 8], 2) == 2  # 示例 1：4、5 符合
    assert solution.findTheDistanceValue([1, 4, 2, 3], [-4, -3, 6, 10, 20, 30], 3) == 2  # 示例 2：1、2 符合
    # 边界：d = 0 退化为「精确匹配是否存在」
    assert solution.findTheDistanceValue([1, 2, 3], [3], 0) == 2  # 3 被精确命中
    assert solution.findTheDistanceValue([1, 2, 3], [4], 0) == 3  # 无精确命中，全部符合
    # 距离恰为 d（不符合）与 d+1（符合）的分界
    assert solution.findTheDistanceValue([5], [3], 2) == 0  # |5-3| = 2 <= d
    assert solution.findTheDistanceValue([5], [2], 2) == 1  # |5-2| = 3 > d
    assert solution.findTheDistanceValue([5], [8], 2) == 1  # |5-8| = 3 > d
    # 单元素数组 / 全部符合 / 全部不符合
    assert solution.findTheDistanceValue([7], [7], 100) == 0
    assert solution.findTheDistanceValue([1, 2, 3], [100, 200], 1) == 3
    # 负数邻域：|-5-0| = 5 > 4 符合，|-4-0| = 4 <= 4 不符合
    assert solution.findTheDistanceValue([-5, -4], [0], 4) == 1
    # 邻居在 arr2 中靠后才出现，验证 break 提前跳出后计数仍正确
    assert solution.findTheDistanceValue([10, 20], [100, 15, 25], 5) == 0


if __name__ == "__main__":
    test_solution()
    print("✅ No.1385 全部测试通过")
