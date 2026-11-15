"""
@file 1524.py
@brief LeetCode 1524. 和为奇数的子数组数目（Number of Sub-arrays With Odd Sum）

@题目描述
    给你一个整数数组 arr。返回其中和为奇数的子数组的数目。由于答案可能很大，
    请返回它对 10^9 + 7 取余的结果。

@示例
    示例 1：
    输入：arr = [1,3,5]
    输出：4
    解释：奇数和的子数组为 [1]、[3]、[5]、[1,3,5]。

    示例 2：
    输入：arr = [2,4,6]
    输出：0

    示例 3：
    输入：arr = [1,2,3,4,5,6,7]
    输出：16

    数据范围：
    1 <= arr.length <= 1e5
    1 <= arr[i] <= 100

@解题思路
    前缀和奇偶配对计数（与 560 同款套路，把「等值查询」换成「奇偶差查询」）：
    1. 子数组 nums[i..j] 的和 = s[j+1] - s[i]（前缀和，s[0] = 0），
       和为奇数 <=> 两个前缀和奇偶性不同；
    2. 扫描每个前缀和，只记它的奇偶：当前为偶时，与此前所有奇前缀配对出奇和
       子数组，反之亦然——只需两个计数器 odd/even；
    3. even 初值 1：空前缀 s[0] = 0 是偶数，漏掉它「从下标 0 开始的奇和子数组」
       就查不到；
    4. 偶数次相减才为偶，配对计数不重不漏；答案累计完统一取模。

    时间复杂度 O(n)，空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/number-of-sub-arrays-with-odd-sum/description/
"""

MOD = 10**9 + 7


class Solution:
    def numOfSubarrays(self, arr: list[int]) -> int:
        prefix = 0
        odd, even = 0, 1  # even 初值 1：空前缀 s[0]=0 计为偶
        ret = 0
        for x in arr:
            prefix += x
            if prefix % 2 == 0:
                ret += odd  # 偶前缀 - 奇前缀 = 奇和子数组
                even += 1
            else:
                ret += even  # 奇前缀 - 偶前缀 = 奇和子数组
                odd += 1

        return ret % MOD


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 ----
    assert solution.numOfSubarrays([1, 3, 5]) == 4
    assert solution.numOfSubarrays([2, 4, 6]) == 0
    assert solution.numOfSubarrays([1, 2, 3, 4, 5, 6, 7]) == 16

    # ---- 最小规模：单个奇数 ----
    assert solution.numOfSubarrays([1]) == 1

    # ---- 单个偶数 ----
    assert solution.numOfSubarrays([2]) == 0

    # ---- 混合奇偶：[1] 与 [1,2]（和 3）两段 ----
    assert solution.numOfSubarrays([1, 2]) == 2
    assert solution.numOfSubarrays([2, 1]) == 2

    # ---- 大数取模：1e5 个 1，奇数长度子数组总数（期望值经暴力+公式双重核对）----
    assert solution.numOfSubarrays([1] * 100000) == 500049986


if __name__ == "__main__":
    test_solution()
    print("✅ No.1524 全部测试通过")
