"""
@file hot100_15.py
@brief LeetCode 15. 三数之和（3Sum）— HOT 100

@题目描述
    给你一个整数数组 nums，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足
    i != j != k 且 nums[i] + nums[j] + nums[k] == 0。请你返回所有和为 0 且不重复
    的三元组。答案中不可以包含重复的三元组。

@示例
    示例 1：
    输入：nums = [-1,0,1,2,-1,-4]
    输出：[[-1,-1,2],[-1,0,1]]
    解释：nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0；不同的三元组是
    [-1,0,1] 和 [-1,-1,2]。

    示例 2：
    输入：nums = [0,1,1]
    输出：[]

    示例 3：
    输入：nums = [0,0,0]
    输出：[[0,0,0]]

    数据范围：
    3 <= nums.length <= 3000
    -1e5 <= nums[i] <= 1e5

@解题思路
    排序 + 枚举首元素 + 跳重双指针（O(n^2)，每个答案恰好生成一次）：
    1. 先排序——相同的值聚在一起，「跳过重复」才有意义；
    2. 枚举首元素 i：nums[i] > 0 时三数之和必 > 0，提前终止；
       i > 0 且 nums[i] == nums[i-1] 时跳过（同值首元素的答案已全部找完）；
    3. 内层用对撞双指针 left/right 找两数之和 == -nums[i]：
       和偏小左移 l，偏大右移 r；相等时记录答案，并各自跳过同值重复
       （l 右移直到新值，r 左移直到新值），保证同一组答案不会再次生成；
    4. 由三处跳重，答案天然无重复，直接 append 无需 set 去重。

    反面教材（本文件初版，LeetCode 超时）：对每个 i 用哈希 twoSum 扫
    nums[i+1:] 找出所有配对再 set 去重——全零数组 n=3000 时会生成约 450 万个
    重复候选元组（每个还要 sorted+tuple+hash），再叠加每轮 O(n) 的切片复制，
    时间与内存双双爆炸。O(n^2) 的框架没错，错在「先生成重复再去除」。

    时间复杂度 O(n^2)（排序 O(n log n) + 枚举 O(n) × 双指针 O(n)），
    空间复杂度 O(log n)（排序栈，不计输出）

来源：LeetCode
链接：https://leetcode.cn/problems/3sum/description/
"""


class Solution:
    def threeSum(self, nums: list[int]) -> list[list[int]]:
        nums.sort()  # 排序是跳重与双指针的前提
        n = len(nums)
        ret: list[list[int]] = []

        for i in range(n - 2):
            if nums[i] > 0:  # 最小的数都 > 0，后面不可能凑出 0
                break
            if i > 0 and nums[i] == nums[i - 1]:  # 首元素跳重：同值的答案已找完
                continue

            left, right = i + 1, n - 1
            while left < right:
                s = nums[i] + nums[left] + nums[right]
                if s < 0:
                    left += 1
                elif s > 0:
                    right -= 1
                else:
                    ret.append([nums[i], nums[left], nums[right]])
                    left += 1
                    right -= 1
                    while left < right and nums[left] == nums[left - 1]:  # 第二个数跳重
                        left += 1
                    while left < right and nums[right] == nums[right + 1]:  # 第三个数跳重
                        right -= 1

        return ret


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1 ----
    assert solution.threeSum([-1, 0, 1, 2, -1, -4]) == [[-1, -1, 2], [-1, 0, 1]]

    # ---- 官方示例 2：无解 ----
    assert solution.threeSum([0, 1, 1]) == []

    # ---- 官方示例 3：全零恰有一组 ----
    assert solution.threeSum([0, 0, 0]) == [[0, 0, 0]]

    # ---- 全零大数组：初版的超时用例，答案仍只有一组 ----
    assert solution.threeSum([0] * 3000) == [[0, 0, 0]]

    # ---- 最小规模 ----
    assert solution.threeSum([1, 2, 3]) == []

    # ---- 重复值密集：[-2,0,2] 与 [0,0,0] 两组（五个 0 自成一组）----
    assert solution.threeSum([-2] * 5 + [0] * 5 + [2] * 5) == [[-2, 0, 2], [0, 0, 0]]


if __name__ == "__main__":
    test_solution()
    print("✅ No.15（HOT 100）全部测试通过")
