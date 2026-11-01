//
// Created by 韩堃 on 2026/11/1.
//

/**
 * @file 453.cpp
 * @brief LeetCode 453. 最小操作次数使数组元素相等（Minimum Moves to Equal Array Elements）
 *
 * @题目描述
 * 给你一个长度为 n 的整数数组 nums，每次操作将会使 n - 1 个元素增加 1。
 * 返回让数组所有元素相等的最小操作次数。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [1,2,3]
 * 输出：3
 * 解释：[1,2,3] => [2,3,3] => [3,4,3] => [4,4,4]（每次操作增加两个元素）。
 *
 * 示例 2：
 * 输入：nums = [1,1,1]
 * 输出：0
 *
 * 数据范围：
 * 1 <= n <= 10^5
 * -10^9 <= nums[i] <= 10^9
 * 答案保证符合 32-bit 整数范围（注意：中间量可能超出 int32，需用更宽类型计算）
 *
 * @解题思路
 * 补集转化（逆向思维）：
 * 1. 每次「给 n-1 个元素 +1」等价于「给 1 个元素 -1」：两种操作对所有元素间差值的
 *    影响完全相同，操作次数不变；
 * 2. 于是问题变为：每次选一个元素 -1 让全部相等的最少次数——把所有数都降到最小值即可，
 *    答案 = sum - n * min；
 * 3. 溢出：sum 与 n*min 量级可达 10^14 远超 int32（官方只保证最终答案在 32-bit 内），
 *    中间量必须用 long long；
 * 4. 一次遍历同时求 sum 与 min。
 *
 * 复杂度分析：
 * - 时间复杂度: O(n)
 * - 空间复杂度: O(1)
 */

#include <gtest/gtest.h>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int minMoves(vector<int>& nums) {
        long long sum = 0;
        int mn = nums[0];
        for (auto i : nums) {
            mn = min(mn, i);
            sum += i;
        }

        // mn * size() 显式走 long long：避免 int×size_t 的带符号/无符号混算
        return sum - mn * (long long)nums.size();
    }
};
}  // namespace

TEST(Daily, 453) {
    Solution s;
    auto check = [&s](vector<int> nums, int expect) { EXPECT_EQ(s.minMoves(nums), expect); };
    // 官方示例
    check({1, 2, 3}, 3);  // 示例 1：三次操作后全等
    check({1, 1, 1}, 0);  // 示例 2：初始已全等
    // 边界：单元素 / 全相等
    check({5}, 0);  // n=1 时每次操作加 0 个元素，天然全等
    check({7, 7, 7, 7}, 0);
    // 负数（约束允许 -1e9）
    check({-1, -5}, 4);
    check({-5, -3, -1}, 6);
    // 小规模混合（期望值经 BFS 全状态枚举暴力验证）
    check({1, 2}, 1);
    check({1, 0, 2}, 3);
    check({5, 1, 3, 2}, 7);
    // 大值与溢出：三个 -1e9 的和为 -3e9 超出 int32——中间量必须用 long long，
    // 而最终答案 2000000000 仍在 int32 内（官方保证）
    check({1, 1000000000}, 999999999);
    check({-1000000000, 1000000000}, 2000000000);
    check({-1000000000, -1000000000, 1000000000}, 2000000000);
}
