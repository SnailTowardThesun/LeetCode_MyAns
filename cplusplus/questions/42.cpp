//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 42.cpp
 * @brief LeetCode 42. 接雨水
 *
 * @题目描述
 * 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子下雨之后能接多少雨水。
 *
 * @示例
 * 示例 1：
 * 输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * 输出：6
 *
 * 示例 2：
 * 输入：height = [4,2,0,3,2,5]
 * 输出：9
 *
 * @解题思路
 * 1. 双指针法：
 *    - 使用两个指针从两端向中间遍历
 *    - 维护左右两边的最高柱子
 *    - 根据左右最高柱子计算每个位置能接的雨水量
 *
 * 2. 算法步骤：
 *    - 初始化左右指针和最大高度
 *    - 遍历数组，根据左右最高柱子计算雨水量
 *    - 移动较低一侧的指针
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(1)
 */

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int trap(vector<int>& height) {
        const int n = static_cast<int>(height.size());
        if (n < 3) return 0;
        int left = 0, right = n - 1;
        int left_max = 0, right_max = 0, result = 0;
        while (left < right) {
            // 较低一侧的水位由本侧最大高度决定，每个位置只结算一次。
            if (height[left] <= height[right]) {
                left_max = max(left_max, height[left]);
                result += left_max - height[left++];
            } else {
                right_max = max(right_max, height[right]);
                result += right_max - height[right--];
            }
        }
        return result;
    }
};
}  // namespace

TEST(Daily, 42) {
    Solution s;

    // 测试用例 1
    vector<int> A1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    EXPECT_EQ(s.trap(A1), 6);

    // 测试用例 2
    vector<int> A2 = {4, 2, 0, 3, 2, 5};
    EXPECT_EQ(s.trap(A2), 9);

    // 测试用例 3
    vector<int> A3 = {1, 0, 1};
    EXPECT_EQ(s.trap(A3), 1);

    vector<int> empty;
    EXPECT_EQ(s.trap(empty), 0);
    vector<int> flat = {2, 2, 2};
    EXPECT_EQ(s.trap(flat), 0);

    // 两侧逐层升高的斜坡会让旧实现反复扫描内部；水量为 10000 的平方。
    vector<int> valley;
    for (int h = 10000; h >= 0; --h) valley.push_back(h);
    for (int h = 1; h <= 10000; ++h) valley.push_back(h);
    EXPECT_EQ(s.trap(valley), 100000000);

    // 穷举小数组，与逐列计算左右最高柱子的参照算法比较。
    for (int mask = 0; mask < 4096; ++mask) {
        vector<int> heights(6);
        int encoded = mask, expected = 0;
        for (int& h : heights) {
            h = encoded % 4;
            encoded /= 4;
        }
        for (int i = 0; i < 6; ++i) {
            int lmax = *max_element(heights.begin(), heights.begin() + i + 1);
            int rmax = *max_element(heights.begin() + i, heights.end());
            expected += min(lmax, rmax) - heights[i];
        }
        EXPECT_EQ(s.trap(heights), expected);
    }
}
