/**
 * @file top150_no238_product_of_array_except_self.cpp
 * @brief LeetCode 238. 除自身以外数组的乘积
 *
 * @题目描述
 * 给你一个整数数组 nums，返回数组 answer，其中 answer[i] 等于 nums 中除 nums[i]
 * 之外其余各元素的乘积。题目数据保证数组 nums之中任意元素的全部前缀元素和后缀的
 * 乘积都在 32 位整数范围内。请不要使用除法，且在 O(n) 时间复杂度内完成此题。
 *
 * @示例
 * 示例 1：
 * 输入: nums = [1,2,3,4]
 * 输出: [24,12,8,6]
 *
 * 示例 2：
 * 输入: nums = [-1,1,0,-3,3]
 * 输出: [0,0,9,0,0]
 *
 * @解题思路
 * 1. 前缀积和后缀积法：
 *    - 先计算每个位置左侧所有元素的乘积（前缀积）
 *    - 再计算每个位置右侧所有元素的乘积（后缀积）
 *    - answer[i] = 前缀积[i] * 后缀积[i]
 *    - 可以用输出数组存储前缀积，再用一个变量维护后缀积，空间复杂度优化到 O(1)
 *
 * 2. 特殊情况处理：
 *    - 统计数组中 0 的个数
 *    - 如果没有 0，正常计算总乘积然后除以当前元素
 *    - 如果有 1 个 0，只有该位置的结果非 0
 *    - 如果有 2 个或以上 0，所有结果都是 0
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，需要遍历数组两次
 * - 空间复杂度: O(1)，不考虑输出数组的空间（或 O(n) 使用额外数组）
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;


class Solution {
public:
    vector<int> productExceptSelf(vector<int> &nums) {
        vector<int> left;
        vector<int> right;
        int n = nums.size();

        left.push_back(nums[0]);
        right.push_back(nums[n - 1]);
        for (int i = 1; i < n; i++) {
            left.push_back(nums[i] * left[left.size() - 1]);
        }

        for (int i = n - 2; i >= 0; i--) {
            right.push_back(nums[i] * right[right.size() - 1]);
        }

        vector<int> ret;
        ret.push_back(right[n-2]);
        for (int i = 1; i < n - 1; i++) {
            ret.push_back(left[i-1] * right[n-i-2]);
        }
        ret.push_back(left[n-2]);
        return ret;
    }
};

TEST(TOP150, No238_ProductExceptSelf) {
    Solution solution;
    std::vector<int> nums{1, 2, 3, 4};
    auto ret = solution.productExceptSelf(nums);
    EXPECT_EQ(ret.size(), 4);
}
