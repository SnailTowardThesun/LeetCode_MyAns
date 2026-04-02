/**
 * @file no42_trapping_rain_water.cpp
 * @brief LeetCode 42. 接雨水
 *
 * @题目描述
 * 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 *
 * @示例
 * 示例 1：
 * 输入: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * 输出: 6
 * 解释: 上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，
 *      可以接 6 个单位的雨水（蓝色部分表示雨水）。
 *
 * 示例 2：
 * 输入: height = [4,2,0,3,2,5]
 * 输出: 9
 *
 * @解题思路
 * 1. 双指针法（最优）：
 *    - 维护左右两个指针，以及左右两边的最大高度
 *    - 每次移动高度较小的一边的指针
 *    - 如果当前高度小于该边的最大高度，则可以接雨水，接水量 = 最大高度 - 当前高度
 *    - 否则更新最大高度
 *    - 时间复杂度 O(n)，空间复杂度 O(1)
 *
 * 2. 动态规划法：
 *    - 预先计算每个位置左边和右边的最大高度
 *    - 每个位置的接水量 = min(左边最大, 右边最大) - 当前高度
 *    - 时间复杂度 O(n)，空间复杂度 O(n)
 *
 * 3. 单调栈法：
 *    - 使用单调递减栈
 *    - 当遇到比栈顶高的柱子时，计算可以接的雨水
 *    - 时间复杂度 O(n)，空间复杂度 O(n)
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，只需要遍历数组一次
 * - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

TEST(TOP150, No42_TrapRainWater) {
    class Solution {
    public:
        int trap(vector<int>& height) {
            int ret = 0;

            int left_point = 0;
            int right_point = static_cast<int>(height.size()) - 1;

            int left_max = 0;
            int right_max = 0;

            while (left_point < right_point) {
                left_max = std::max(left_max, height[left_point]);
                right_max = std::max(right_max, height[right_point]);
                if (left_max < right_max) {
                    ret += (left_max - height[left_point]);
                    left_point++;
                } else {
                    ret += (right_max - height[right_point]);
                    right_point--;
                }
            }

            return ret;
        }
    };

    Solution solution;
    std::vector<int> height{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    auto ret = solution.trap(height);
    EXPECT_EQ(ret, 6);
}
