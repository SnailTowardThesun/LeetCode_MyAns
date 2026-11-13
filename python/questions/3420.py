"""
@file 3420.py
@brief LeetCode 3420. 统计 K 次操作以内得到的非递减子数组数目（Count Non-Decreasing Subarrays After K Operations）

@题目描述
    给你一个长度为 n 的整数数组 nums 和一个整数 k。对于 nums 的每一个子数组，你可以
    进行至多 k 次操作，每次操作可以把子数组中任意一个元素加 1（各子数组相互独立，
    修改不保留）。返回经过至多 k 次操作后能变成非递减的子数组数目。
    非递减指每个元素都大于等于前一个元素。

@示例
    示例 1：
    输入：nums = [6,3,1,2,4,4], k = 7
    输出：17
    解释：全部 21 个子数组中，只有 [6,3,1]、[6,3,1,2]、[6,3,1,2,4]、[6,3,1,2,4,4]
    这 4 个（代价 8/12/14/16 超过 7）无法达成，21 - 4 = 17。

    示例 2：
    输入：nums = [6,3,1,3,6], k = 4
    输出：12

    数据范围：
    1 <= nums.length <= 1e5
    1 <= nums[i] <= 1e9
    1 <= k <= 1e9

@解题思路
    反向滑动窗口 + 单调双端队列（rating 2854 的关键在两个转化）：
    1. 单个子数组的最小代价：把每个元素抬到「左侧前缀最大值」即最优——任何合法的
       非递减结果逐点 >= 前缀最大值（归纳可证），取等号即最小代价
       cost = sum(max(nums[l..i]) - nums[i])。
    2. 双指针方向：固定左端 i 从右往左扫（反向窗口）。窗口向左扩时新元素会迫使
       一批右侧元素抬高，代价单调不减 -> 右端 j 只会单调左移 -> O(n) 均摊。
    3. 单调双端队列维护「调整后的窗口形态」：存 (值, 覆盖的连续元素个数) 分段，
       从 back（窗口左端）到 front（右端）值递减，即调整后数组倒过来读：
       - 新元素 num 从左侧进入：把所有值 < num 的段（都在 back 侧）抬高到 num，
         pop back 并累加代价 (num - 值) * 个数，最后合并压成一段 (num, 总个数)；
       - 代价超预算时右端弹出：最右元素被抬到了 front 段的值，退回
         front值 - nums[j]，个数减一（减到 0 则 pop front），j 左移。
    4. 每个左端 i 收缩完毕后累加 j - i + 1（合法右端点个数）即为答案。

    时间复杂度 O(n)（每个元素至多进出队列各一次），空间复杂度 O(n)
    数值范围：代价上限约 1e5 * 1e9 = 1e14，Python 大整数无忧；C++ 需 long long

来源：LeetCode
链接：https://leetcode.cn/problems/count-non-decreasing-subarrays-after-k-operations/description/
"""

from collections import deque


class Solution:
    def countNonDecreasingSubarrays(self, nums: list[int], k: int) -> int:
        ans = 0
        cost = 0
        # (调整后的值, 覆盖的连续元素个数)：back 是窗口左端（新元素进入侧），
        # front 是右端（超预算弹出侧）；从 back 到 front 值递减
        dq: deque[tuple[int, int]] = deque()

        j = len(nums) - 1
        for i in range(len(nums) - 1, -1, -1):
            num = nums[i]
            count = 1
            # 新元素从左侧进入：所有比它小的段（都在 back 侧）抬高到 num
            while dq and dq[-1][0] < num:
                next_num, next_count = dq.pop()
                count += next_count
                cost += (num - next_num) * next_count
            dq.append((num, count))

            # 代价超预算：从右侧收缩窗口
            while cost > k:
                right_num, right_count = dq.popleft()
                cost -= right_num - nums[j]
                j -= 1
                if right_count > 1:
                    dq.appendleft((right_num, right_count - 1))

            ans += j - i + 1

        return ans


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：21 个子数组中 4 个超预算，21 - 4 = 17 ----
    assert solution.countNonDecreasingSubarrays([6, 3, 1, 2, 4, 4], 7) == 17

    # ---- 官方示例 2 ----
    assert solution.countNonDecreasingSubarrays([6, 3, 1, 3, 6], 4) == 12

    # ---- 最小规模：单元素零代价 ----
    assert solution.countNonDecreasingSubarrays([5], 1) == 1

    # ---- 已经非递减：所有子数组都免费 ----
    assert solution.countNonDecreasingSubarrays([1, 2, 3, 4], 0) == 10

    # ---- 严格递减 + k=0：只有单元素子数组 ----
    assert solution.countNonDecreasingSubarrays([4, 3, 2, 1], 0) == 4

    # ---- 全相等：k=0 即可全部非递减 ----
    assert solution.countNonDecreasingSubarrays([2, 2, 2], 0) == 6

    # ---- 预算极大：全部子数组合法 ----
    assert solution.countNonDecreasingSubarrays([6, 3, 1, 2, 4, 4], 10**9) == 21


if __name__ == "__main__":
    test_solution()
    print("✅ No.3420 全部测试通过")
