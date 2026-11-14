"""
@file hot100_283.py
@brief LeetCode 283. 移动零（Move Zeroes）— HOT 100

@题目描述
    给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的
    相对顺序。请尽量减少操作次数（必须在不复制数组的情况下原地对数组进行操作）。

@示例
    示例 1：
    输入：nums = [0,1,0,3,12]
    输出：[1,3,12,0,0]

    示例 2：
    输入：nums = [0]
    输出：[0]

    数据范围：
    1 <= nums.length <= 1e4
    -2^31 <= nums[i] <= 2^31 - 1

@解题思路
    快慢双指针（原地交换）：
    1. slow 指向「下一个非零元素应落位」的位置——它同时是当前最靠左的零；
    2. fast 向右扫描，遇到非零元素就与 nums[slow] 交换后 slow 前进一格；
    3. 不变量：循环中任意时刻 nums[0..slow) 全是非零且保持原相对顺序，
       nums[slow..fast) 全是零——交换只把零换到后面、非零换到前面，两边的
       相对顺序都不被破坏；
    4. slow == fast（前缀没有零）时交换是自己和自己，无害，无需特判。

    时间复杂度 O(n)（一次遍历，每个元素至多被交换一次），空间复杂度 O(1)
    反面教材（本文件初版）：遇到零就 pop 出来 append 到末尾——pop 中间的零
    要整体搬移后半段，最坏 O(n^2)；且弹出后新滑入 left 的元素被 left++ 跳过，
    相邻两个零会漏处理（[0,0,1] 会错成 [0,1,0]）。

来源：LeetCode
链接：https://leetcode.cn/problems/move-zeroes/description/
"""


class Solution:
    def moveZeroes(self, nums: list[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        slow = 0  # 下一个非零元素的落位；也即当前最靠左的零
        for fast in range(len(nums)):
            if nums[fast] != 0:
                nums[slow], nums[fast] = nums[fast], nums[slow]
                slow += 1


def test_solution() -> None:
    solution = Solution()

    def run(nums: list[int]) -> list[int]:
        solution.moveZeroes(nums)
        return nums

    # ---- 官方示例 1 ----
    assert run([0, 1, 0, 3, 12]) == [1, 3, 12, 0, 0]

    # ---- 官方示例 2：单个零 ----
    assert run([0]) == [0]

    # ---- 相邻零（初版 pop+append 写法的翻车用例）----
    assert run([0, 0, 1]) == [1, 0, 0]
    assert run([0, 0, 1, 0]) == [1, 0, 0, 0]

    # ---- 没有零：原样不动 ----
    assert run([1, 2, 3]) == [1, 2, 3]

    # ---- 全是零：原样不动 ----
    assert run([0, 0, 0]) == [0, 0, 0]

    # ---- 零在后半段 ----
    assert run([2, 0, 1]) == [2, 1, 0]


if __name__ == "__main__":
    test_solution()
    print("✅ No.283（HOT 100）全部测试通过")
