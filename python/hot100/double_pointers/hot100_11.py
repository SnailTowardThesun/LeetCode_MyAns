"""
@file hot100_11.py
@brief LeetCode 11. 盛最多水的容器（Container With Most Water）— HOT 100

@题目描述
    给定一个长度为 n 的整数数组 height。有 n 条垂线，第 i 条线的两个端点是
    (i, 0) 和 (i, height[i])。找出其中的两条线，使得它们与 x 轴共同构成的容器
    可以容纳最多的水。返回容器可以储存的最大水量（不能倾斜容器）。

@示例
    示例 1：
    输入：height = [1,8,6,2,5,4,8,3,7]
    输出：49
    解释：选择第 1（高 8）与第 8（高 7）条线，面积 = min(8,7) * 7 = 49。

    示例 2：
    输入：height = [1,1]
    输出：1

    示例 3：
    输入：height = [4,3,2,1,4]
    输出：16（两端高 4，min(4,4) * 4 = 16）

    示例 4：
    输入：height = [1,2,1]
    输出：2

    数据范围：
    n == height.length
    2 <= n <= 1e5
    0 <= height[i] <= 1e4

@解题思路
    对撞双指针 + 移动短板：
    1. 面积 = min(height[left], height[right]) * (right - left)，受「短板」与
       「宽度」共同限制；
    2. 左右指针从两端出发（宽度最大起步），每轮先记录当前面积再收缩；
    3. 关键贪心：只移动较矮的一侧——移动较高侧时宽度变小、高度上限（短板）
       不变，面积只可能更小；移动短板虽然宽度也变小，但高度上限有机会变高，
       才可能找到更大面积；
    4. 两侧等高时移哪边都行（都不会漏解），本实现与 C++ 版一致选择移动左侧；
    5. 每轮恰好排除一条线，正确性由「被排除的线不可能再构成更优解」保证，
       n - 1 轮后指针相遇结束。

    时间复杂度 O(n)（每轮移动一个指针），空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/container-with-most-water/description/
"""


class Solution:
    def maxArea(self, height: list[int]) -> int:
        left, right = 0, len(height) - 1
        ret = 0
        while left < right:
            # 先记面积再收缩；面积受短板限制，宽度为两指针间距
            ret = max(ret, min(height[left], height[right]) * (right - left))
            # 只移动短板：移动高板不可能得到更大面积
            if height[left] > height[right]:
                right -= 1
            else:
                left += 1
        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：高 8 与高 7 的两条线 ----
    assert solution.maxArea([1, 8, 6, 2, 5, 4, 8, 3, 7]) == 49

    # ---- 官方示例 2：最小规模 ----
    assert solution.maxArea([1, 1]) == 1

    # ---- 官方示例 3：两端等高 ----
    assert solution.maxArea([4, 3, 2, 1, 4]) == 16

    # ---- 官方示例 4：中间高不如两端宽 ----
    assert solution.maxArea([1, 2, 1]) == 2

    # ---- 含 0 高度：短板为 0 的容器存不了水 ----
    assert solution.maxArea([0, 5]) == 0

    # ---- 递减序列：宽高折中，min(5,3)*2 = 6 ----
    assert solution.maxArea([5, 4, 3, 2, 1]) == 6


if __name__ == "__main__":
    test_solution()
    print("✅ No.11（HOT 100）全部测试通过")
