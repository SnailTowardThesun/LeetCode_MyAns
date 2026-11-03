//
// Created by 韩堃 on 2026/11/3.
//

/**
 * @file 3736.cpp
 * @brief LeetCode 3736. 最小操作次数使数组元素相等 III（Minimum Moves to Equal Array Elements III）
 *
 * @题目描述
 * 给你一个整数数组 nums。一步操作中，你可以将任意单个元素 nums[i] 的值增加 1。
 * 返回使数组中所有元素相等所需的最小总操作次数。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [2,1,3]
 * 输出：3
 * 解释：将 nums[0] 从 2 增到 3（1 次），再将 nums[1] 从 1 增到 3（2 次），
 * 最终所有元素均为 3。
 *
 * 示例 2：
 * 输入：nums = [4,4,5]
 * 输出：2
 * 解释：两个 4 各增加 1 变为 5，共 2 次操作。
 *
 * 数据范围：
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 100
 *
 * @解题思路
 * 全部补齐到最大值：答案 = sum(max - nums[i]) = n * max - sum。
 * 1. 操作只能 +1 不能减，公共目标值 V 必须 >= 每个元素（大元素降不下去），
 *    即 V >= max；
 * 2. 每步操作使数组总和恰好增加 1，故总操作数 = n*V - sum，随 V 严格递增；
 * 3. V 取最小可行值 max 最优，答案 = n*max - sum——
 *    每个元素到 max 的缺口就是它各自需要的操作次数，缺口之和即总次数；
 * 4. 一趟遍历同时攒出 max 与 sum，避免排序（也不需要 sorted）；
 * 5. 系列对比：453（n-1 个元素 +1）等价于单元素 -1，目标锁死 min，
 *    答案 sum - n*min；462（单元素 ±1）目标自由选，聚拢中位数；
 *    本题单元素只能 +1，目标顶到 max。同一题面家族，操作规则一字之差。
 * 6. 溢出余量：n <= 100、值 <= 100，答案 <= 9801；mm * nums.size() 中 mm 提升
 *    为 size_t 参与乘法、long long 累加总和，均为稳妥余量而非必需。
 *
 * 复杂度分析：
 * - 时间复杂度：O(n)（单趟遍历）
 * - 空间复杂度：O(1)
 */

#include <gtest/gtest.h>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int minMoves(vector<int>& nums) {
        long long total = 0;  // 元素总和
        int mm = 0;           // 最大值（题目保证 nums[i] >= 1，0 起步安全）
        for (auto i : nums) {
            mm = max(mm, i);
            total += i;
        }

        // 答案 = n*max - sum：每个元素补到 max 的缺口之和
        return mm * nums.size() - total;
    }
};
}  // namespace

TEST(Daily, 3736) {
    Solution s;
    auto check = [&s](vector<int> nums, int expect) { EXPECT_EQ(s.minMoves(nums), expect); };
    // 官方示例
    check({2, 1, 3}, 3);  // 示例 1：2→3 一次、1→3 两次
    check({4, 4, 5}, 2);  // 示例 2：两个 4 各 +1
    // 边界：单元素 / 全相等（零成本）
    check({1}, 0);
    check({7, 7, 7}, 0);
    // 最大值在头部/尾部不影响结果
    check({100, 1}, 99);
    check({1, 100}, 99);
    // 多个最小值同时补齐：三个 1 各缺 99
    check({1, 1, 1, 100}, 297);
    // 多个最大值：缺口全在较小元素上
    check({5, 5, 3}, 2);
    // 无序小数组
    check({3, 1, 2}, 3);
    // 规模上界：99 个 1 + 1 个 100，答案 99*(100-1)=9801
    vector<int> worst(99, 1);
    worst.push_back(100);
    check(worst, 9801);
    // 满值域小数组：缺口 99+98+...+0 = 4950
    vector<int> full(100);
    for (int i = 0; i < 100; i++) {
        full[i] = i + 1;
    }
    check(full, 4950);
}
