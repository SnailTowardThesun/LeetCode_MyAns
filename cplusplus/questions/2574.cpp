//
// Created by hankun on 6/6/26.
//

/**
 * @file 2574.cpp
 * @brief LeetCode 2574. Left and Right Sum Differences（左右元素和的差值）
 *
 * @题目描述
 * 给你一个下标从 0 开始的整数数组 nums，请你找出一个下标从 0 开始的整数数组 answer，其中：
 * - answer.length == nums.length
 * - answer[i] = |leftSum[i] - rightSum[i]|
 *
 * 其中：
 * - leftSum[i] 是数组 nums 中下标 i 左侧元素之和。如果不存在对应的元素，leftSum[i] = 0。
 * - rightSum[i] 是数组 nums 中下标 i 右侧元素之和。如果不存在对应的元素，rightSum[i] = 0。
 *
 * 返回数组 answer。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [10,4,8,3]
 * 输出：[15,1,11,22]
 * 解释：
 * 数组 leftSum 为 [0,10,14,22]，数组 rightSum 为 [15,11,3,0]。
 * 数组 answer 为 [|0 - 15|, |10 - 11|, |14 - 3|, |22 - 0|] = [15,1,11,22]
 *
 * 示例 2：
 * 输入：nums = [1]
 * 输出：[0]
 * 解释：
 * 数组 leftSum 为 [0]，数组 rightSum 为 [0]。
 * 数组 answer 为 [|0 - 0|] = [0]
 *
 * @解题思路
 * 1. 前缀和数组法：
 *    - 创建 leftSum 数组，leftSum[i] 表示 nums[0..i-1] 的和
 *    - 创建 rightSum 数组，rightSum[i] 表示 nums[i+1..n-1] 的和
 *    - 遍历数组，计算 answer[i] = |leftSum[i] - rightSum[i]|
 *
 * 2. 算法步骤：
 *    - 初始化 leftSum 数组，leftSum[0] = 0，从左到右计算前缀和
 *    - 初始化 rightSum 数组，rightSum[n-1] = 0，从右到左计算后缀和
 *    - 遍历数组，计算每个位置的绝对差值
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)，需要遍历数组三次（计算左前缀和、右前缀和、计算结果）
 *    - 空间复杂度: O(n)，需要额外的数组存储前缀和
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> leftRightDifference(vector<int> &nums) {
        int n = nums.size();

        vector<int> left_pre(n, 0);
        for (int i = 1; i < n; i++) {
            left_pre[i] = nums[i - 1] + left_pre[i - 1];
        }

        vector<int> right_pre(n, 0);
        for (int i = n - 2; i >= 0; i--) {
            right_pre[i] = nums[i + 1] + right_pre[i + 1];
        }

        vector<int> ret;
        for (int i = 0; i < n; i++) {
            ret.push_back(abs(left_pre[i] - right_pre[i]));
        }

        return ret;
    }
};

TEST(Daily, 2574) {
    Solution s;
    vector<int> nums{10, 4, 8, 3};
    auto ret = s.leftRightDifference(nums);
    EXPECT_EQ(vector<int>({15,1,11,22}), ret);
}
