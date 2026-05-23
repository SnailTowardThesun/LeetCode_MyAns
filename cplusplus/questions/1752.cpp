//
// Created by hankun on 5/23/26.
//

/**
 * @题目描述
 * 1752. 检查数组是否经排序和轮转得到
 * 给你一个数组 nums 。nums 的源数组中，所有元素与 nums 相同，但按非递减顺序排列。
 * 如果 nums 能够由源数组轮转若干位置（包括 0 个位置）得到，则返回 true ；否则，返回 false 。
 * 源数组中可能存在重复项。
 * 注意：我们称数组 A 在轮转 x 个位置后得到长度相同的数组 B ，当它们满足 B[i] == A[(i+x) mod n] 。
 *
 * @示例
 * 示例 1：
 * 输入: nums = [3,4,5,1,2]
 * 输出: true
 * 解释: [1,2,3,4,5] 为有序的源数组。
 * 可以轮转 x=3 个位置，使新数组从值为 3 的元素开始：[3,4,5,1,2] 。
 *
 * 示例 2：
 * 输入: nums = [2,1,3,4]
 * 输出: false
 * 解释: 源数组无法经轮转得到 nums 。
 *
 * 示例 3：
 * 输入: nums = [1,2,3,4]
 * 输出: true
 * 解释: 源数组为 [1,2,3,4]，轮转 0 个位置得到 nums 。
 *
 * @解题思路
 * 方法：统计逆序对
 * 1. 遍历数组，统计 nums[i] > nums[i+1] 的次数
 * 2. 注意：数组是循环的，需要检查 nums[n-1] > nums[0]
 * 3. 如果逆序对数量 <= 1，则返回 true；否则返回 false
 *
 * 原理：
 * - 如果数组完全有序（轮转 0 次），则逆序对数量为 0
 * - 如果数组是轮转后的，则只有一个位置 nums[i] > nums[i+1]（即断点）
 * - 如果有多个逆序对，则说明数组不是排序后轮转的
 *
 * @复杂度分析
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool check(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int count = 0;
        
        for (int i = 0; i < n; ++i) {
            if (nums[i] > nums[(i + 1) % n]) {
                ++count;
            }
        }
        
        return count <= 1;
    }
};

#include <gtest/gtest.h>

TEST(Daily, 1752) {
    Solution s;

    // 测试用例 1：轮转后的数组
    auto nums1 = vector<int>{3, 4, 5, 1, 2};
    EXPECT_TRUE(s.check(nums1));

    // 测试用例 2：不是轮转后的数组
    auto nums2 = vector<int>{2, 1, 3, 4};
    EXPECT_FALSE(s.check(nums2));

    // 测试用例 3：完全有序（轮转 0 次）
    auto nums3 = vector<int>{1, 2, 3, 4};
    EXPECT_TRUE(s.check(nums3));

    // 测试用例 4：包含重复元素
    auto nums4 = vector<int>{2, 2, 2, 3, 1};
    EXPECT_TRUE(s.check(nums4));

    // 测试用例 5：只有一个元素
    auto nums5 = vector<int>{1};
    EXPECT_TRUE(s.check(nums5));

    // 测试用例 6：只有两个元素
    auto nums6 = vector<int>{1, 2};
    EXPECT_TRUE(s.check(nums6));
    auto nums7 = vector<int>{2, 1};
    EXPECT_TRUE(s.check(nums7));
}