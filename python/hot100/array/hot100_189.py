"""
@file hot100_189.py
@brief LeetCode 189. 轮转数组（Rotate Array）— HOT 100

@题目描述
    给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
    要求尽量原地完成（不返回新数组，直接修改 nums）。

@示例
    示例 1：
    输入：nums = [1,2,3,4,5,6,7], k = 3
    输出：[5,6,7,1,2,3,4]

    示例 2：
    输入：nums = [-1,-100,3,99], k = 2
    输出：[3,99,-1,-100]

    数据范围：
    1 <= nums.length <= 1e5
    -2^31 <= nums[i] <= 2^31 - 1
    0 <= k <= 1e5

@解题思路
    尾段 + 头段切片拼接：
    1. k = k % n 去掉整圈轮转（k >= n 时等价于 k % n）；
    2. 右轮转 k 位 = 末尾 k 个元素搬到开头：新数组 = nums[n-k:] + nums[:n-k]；
    3. nums[:] = ... 是「就地覆写」：对切片赋值会修改原列表对象本身，
       而不是让局部变量指向新列表——这才是题目要求的原地效果
       （若写成 nums = ... 只改了局部引用，调用方看不到变化）。

    时间复杂度 O(n)，空间复杂度 O(n)（切片临时数组）
    进阶 O(1) 空间：三次翻转——整体翻转、翻前 k 个、翻后 n-k 个，
    翻转两两抵消让每个元素归位（见对应博客的 C++ 参考实现）。

来源：LeetCode
链接：https://leetcode.cn/problems/rotate-array/description/
"""


class Solution:
    def rotate(self, nums: list[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)

        k = k % n  # 去掉整圈轮转，k == n 时数组不变

        # 对切片赋值 = 就地覆写原列表（区别于 nums = ... 只改局部引用）
        nums[:] = nums[n - k :] + nums[: n - k]


def test_solution() -> None:
    solution = Solution()

    def run(nums: list[int], k: int) -> list[int]:
        solution.rotate(nums, k)
        return nums

    # ---- 官方示例 ----
    assert run([1, 2, 3, 4, 5, 6, 7], 3) == [5, 6, 7, 1, 2, 3, 4]
    assert run([-1, -100, 3, 99], 2) == [3, 99, -1, -100]

    # ---- k == 0 / k == n：数组不变（期望值由暴力对照机器算出）----
    assert run([1, 2, 3], 0) == [1, 2, 3]
    assert run([1, 2], 2) == [1, 2]

    # ---- k > n：先取模再轮转 ----
    assert run([1, 2], 3) == [2, 1]

    # ---- 单元素 + 巨大 k ----
    assert run([-1], 99) == [-1]


if __name__ == "__main__":
    test_solution()
    print("✅ No.189（HOT 100）全部测试通过")
