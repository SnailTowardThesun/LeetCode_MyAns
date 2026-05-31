//
// @题目描述: 给你一个整数数组 nums，判断是否存在三元组 (a, b, c) 满足 a + b + c = 0。
//            要求不能重复使用数组中同一个元素，且三元组不能重复。
//
// @示例: 输入: nums = [-1, 0, 1, 2, -1, -4]
//        输出: [[-1, -1, 2], [-1, 0, 1]]
//
// @解题思路: 先对数组排序，固定一个数k，然后使用双指针i和j在k右侧范围内查找。
//            如果nums[k] > 0，则三数之和不可能为0，退出循环。
//            如果nums[k] == nums[k-1]，说明是重复元素，跳过。
//            双指针移动时，要跳过重复元素以避免重复三元组。
//            时间复杂度: O(n^2)，空间复杂度: O(1) (不计排序额外空间)
//
// Created by hankun on 5/31/26.
//
#include <gtest/gtest.h>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        for (size_t k = 0; k < nums.size(); ++k) {
            if (nums[k] > 0) break;
            if (k > 0 && nums[k] == nums[k - 1]) continue;
            int target = 0 - nums[k];
            int i = k + 1, j = nums.size() - 1;
            while (i < j) {
                if (nums[i] + nums[j] == target) {
                    res.push_back({nums[k], nums[i], nums[j]});
                    while (i < j && nums[i] == nums[i + 1]) {
                        ++i;
                    }
                    while (i < j && nums[j] == nums[j - 1]) {
                        --j;
                    }

                    ++i;
                    --j;
                } else if (nums[i] + nums[j] < target) {
                    ++i;
                } else {
                    --j;
                }
            }
        }
        return res;
    }
};


TEST(top150, 15) {
    Solution s;
    vector<int> nums{-1, 0, 1, 2, -1, -4};
    auto ret = s.threeSum(nums);
    vector<vector<int>> expected{{-1, -1, 2}, {-1, 0, 1}};
    EXPECT_EQ(expected.size(), ret.size());
}