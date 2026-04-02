/**
 * @file no238_product_of_array_except_self.cpp
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

TEST(TOP150, No238_ProductExceptSelf) {
    class Solution {
    public:
        vector<int> product_except_self(vector<int>& nums) {
            std::vector<int> ret(nums.begin(), nums.end());

            int zero_count = 0;
            int64_t total = 1;

            for (auto i = 0; i < nums.size(); i++) {
                if (nums[i] == 0) {
                    zero_count++;
                } else {
                    total *= nums[i];
                }
            }

            if (zero_count >= 2) {
                return std::vector<int>(nums.size(), 0);
            }

            for (auto i = 0; i < nums.size(); i++) {
                if (zero_count == 1) {
                    if (nums[i] == 0) {
                        ret[i] = total;
                    } else {
                        ret[i] = 0;
                    }
                } else {
                    ret[i] = total / nums[i];
                }
            }

            return ret;
        }
    };
    Solution solution;
    std::vector<int> nums{1, 2, 3, 4};
    auto ret = solution.product_except_self(nums);
    EXPECT_EQ(ret.size(), 4);
}
