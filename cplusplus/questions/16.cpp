//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 16.cpp
 * @brief LeetCode 16. 最接近的三数之和
 *
 * @题目描述
 * 给定一个整数数组 nums 和一个目标值 target，
 * 找出 nums 中的三个整数，使得这三个数的和与 target 最接近。
 * 返回这三个数的和。
 * 假设每组输入只存在唯一答案。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [-1, 2, 1, -4], target = 1
 * 输出：2
 * 解释：与 target 最接近的三个数之和是 -1 + 2 + 1 = 2
 *
 * 示例 2：
 * 输入：nums = [0, 0, 0], target = 1
 * 输出：0
 *
 * @解题思路
 * 1. 排序 + 双指针法：
 *    - 对数组进行排序
 *    - 固定一个数 nums[pos]，使用双指针寻找另外两个数
 *    - 计算当前三数之和与 target 的接近程度
 *
 * 2. 算法步骤：
 *    - 对数组进行排序
 *    - 初始化最接近的结果为 nums[0] + nums[1] + nums[2]
 *    - 遍历数组，固定 nums[pos]
 *    - 使用双指针 left = pos + 1，right = n - 1
 *    - 计算当前三数之和
 *    - 更新最接近的结果
 *    - 如果当前和大于 target，right--；如果小于 target，left++
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n^2)，其中 n 是数组的长度
 *    - 空间复杂度: O(1)，只使用常数级别的额外空间
 */

#include <gtest/gtest.h>
#include <vector>
#include <limits>

using namespace std;

TEST(Daily, 16) {
    class Solution {
    public:
        int threeSumClosest(vector<int>& nums, int target) {
            int ret = std::numeric_limits<int>::max() - abs(target);

            std::sort(nums.begin(), nums.end());
            int pos = 0;

            while ((pos < nums.size() - 1) && (nums[pos] < target || ret == std::numeric_limits<int>::max() - abs(target))) {
                int leftPointer = pos + 1;
                int rightPointer = nums.size() - 1;
                while (leftPointer != rightPointer) {
                    auto tmpResult = nums[pos] + nums[leftPointer] + nums[rightPointer];
                    ret = abs(tmpResult - target) < abs(ret - target) ? tmpResult : ret;
                    if (ret == target) {
                        break;
                    }
                    if (tmpResult < target) {
                        leftPointer++;
                    }
                    else {
                        rightPointer--;
                    }
                }
                pos++;
            }

            return ret;
        }
    };

    Solution s;
    
    // 测试用例 1
    vector<int> nums1 = {-1, 2, 1, -4};
    EXPECT_EQ(s.threeSumClosest(nums1, 1), 2);
    
    // 测试用例 2
    vector<int> nums2 = {0, 0, 0};
    EXPECT_EQ(s.threeSumClosest(nums2, 1), 0);
    
    // 测试用例 3
    vector<int> nums3 = {1, 1, 1, 0};
    EXPECT_EQ(s.threeSumClosest(nums3, -100), 2);
}
