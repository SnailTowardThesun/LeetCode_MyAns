//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 41.cpp
 * @brief LeetCode 41. 缺失的第一个正数
 *
 * @题目描述
 * 给你一个未排序的整数数组 nums，请你找出其中没有出现的最小的正整数。
 * 你必须实现时间复杂度为 O(n) 并且只使用常数级别额外空间的算法。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [1, 2, 0]
 * 输出：3
 *
 * 示例 2：
 * 输入：nums = [3, 4, -1, 1]
 * 输出：2
 *
 * 示例 3：
 * 输入：nums = [7, 8, 9, 11, 12]
 * 输出：1
 *
 * @解题思路
 * 1. 原地哈希法：
 *    - 将 [1, n] 范围内的值 x 放到下标 x-1
 *    - 遍历数组，第一个不满足 nums[i] == i + 1 的位置就是缺失的最小正数
 *
 * 2. 算法步骤：
 *    - 先判断 nums[i] 是否在 [1, n] 内，再减一计算目标下标
 *    - 目标位置已经有相同的值时停止交换，避免重复值造成循环
 *    - 再次遍历数组，找到第一个不满足 nums[i] == i + 1 的位置
 *    - 如果都满足，返回 n + 1
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)，每次交换至少固定一个位置，总交换次数不超过 n
 *    - 空间复杂度: O(1)，原地修改数组
 */

#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                int target = nums[i] - 1;
                std::swap(nums[i], nums[target]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) return i + 1;
        }
        return n + 1;
    }
};
}  // namespace

TEST(Daily, 41) {
    Solution s;

    // 测试用例 1
    vector<int> nums1{1, 2, 0};
    EXPECT_EQ(s.firstMissingPositive(nums1), 3);

    // 测试用例 2
    vector<int> nums2{3, 4, -1, 1};
    EXPECT_EQ(s.firstMissingPositive(nums2), 2);

    // 测试用例 3
    vector<int> nums3{7, 8, 9, 11, 12};
    EXPECT_EQ(s.firstMissingPositive(nums3), 1);

    // 测试用例 4
    vector<int> nums4{1, 1};
    EXPECT_EQ(s.firstMissingPositive(nums4), 2);

    // 旧实现会在检查最小整数时先减一，导致有符号溢出
    vector<int> extremes{numeric_limits<int>::min(), numeric_limits<int>::max(), 1};
    EXPECT_EQ(s.firstMissingPositive(extremes), 2);
}
