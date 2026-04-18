//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 15.cpp
 * @brief LeetCode 15. 三数之和
 *
 * @题目描述
 * 给你一个整数数组 nums，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k，
 * 同时还满足 nums[i] + nums[j] + nums[k] == 0。
 * 请你返回所有和为 0 的不重复三元组。
 *
 * 注意：答案中不可以包含重复的三元组。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [-1, 0, 1, 2, -1, -4]
 * 输出：[[-1, -1, 2], [-1, 0, 1]]
 *
 * 示例 2：
 * 输入：nums = [0, 1, 1]
 * 输出：[]
 *
 * 示例 3：
 * 输入：nums = [0, 0, 0]
 * 输出：[[0, 0, 0]]
 *
 * @解题思路
 * 1. 排序 + 双指针法：
 *    - 首先对数组进行排序
 *    - 固定一个数 nums[k]，然后使用双指针在剩余部分寻找两个数，使它们的和等于 -nums[k]
 *
 * 2. 算法步骤：
 *    - 对数组进行排序
 *    - 遍历排序后的数组，固定 nums[k]
 *    - 如果 nums[k] > 0，则后面的数都大于 0，三数之和不可能为 0，直接 break
 *    - 如果 nums[k] 与前一个数相同，跳过以避免重复
 *    - 使用双指针 left = k + 1，right = n - 1
 *    - 如果三数之和等于 0，添加到结果集
 *    - 如果三数之和大于 0，right--
 *    - 如果三数之和小于 0，left++
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n^2)，其中 n 是数组的长度
 *    - 空间复杂度: O(1)，只使用常数级别的额外空间（不考虑输出空间）
 */

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

TEST(Daily, 15) {
    class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            vector<vector<int>> res;
            std::sort(nums.begin(), nums.end());

            for (int k = 0; k < nums.size(); ++k) {
                if (nums[k] > 0) {
                    break;
                }

                if (k > 0 && nums[k] == nums[k - 1]) {
                    continue;
                }

                int target = 0 - nums[k];
                int i = k + 1, j = nums.size() - 1;
                while (i < j) {
                    if (nums[i] + nums[j] == target) {
                        res.push_back({ nums[k], nums[i], nums[j] });
                        while (i < j && nums[i] == nums[i + 1]) ++i;
                        while (i < j && nums[j] == nums[j - 1]) --j;
                        ++i; --j;
                    }
                    else if (nums[i] + nums[j] < target) {
                        ++i;
                    }
                    else {
                        --j;
                    }
                }
            }
            return res;
        }
    };

    Solution s;
    
    // 测试用例 1
    vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    auto result1 = s.threeSum(nums1);
    EXPECT_EQ(result1.size(), 2);
    
    // 测试用例 2
    vector<int> nums2 = {0, 1, 1};
    auto result2 = s.threeSum(nums2);
    EXPECT_EQ(result2.size(), 0);
    
    // 测试用例 3
    vector<int> nums3 = {0, 0, 0};
    auto result3 = s.threeSum(nums3);
    EXPECT_EQ(result3.size(), 1);
    EXPECT_EQ(result3[0], vector<int>({0, 0, 0}));
    
    // 测试用例 4
    vector<int> nums4 = {-2, 0, 0, 2, 2};
    auto result4 = s.threeSum(nums4);
    EXPECT_EQ(result4.size(), 1);
}
