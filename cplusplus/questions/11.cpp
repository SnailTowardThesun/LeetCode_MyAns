//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 11.cpp
 * @brief LeetCode 11. 盛最多水的容器
 *
 * @题目描述
 * 给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai)。
 * 在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。
 * 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
 *
 * 注意：你不能倾斜容器。
 *
 * @示例
 * 示例 1：
 * 输入：[1,8,6,2,5,4,8,3,7]
 * 输出：49
 * 解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
 *
 * 示例 2：
 * 输入：[1,1]
 * 输出：1
 *
 * @解题思路
 * 1. 双指针法：
 *    - 使用两个指针，分别指向数组的开始和结束位置
 *    - 计算当前两个指针所形成的容器的面积
 *    - 移动高度较小的指针，因为移动高度较大的指针不会增加容器的面积
 *    - 重复上述过程，直到两个指针相遇
 *
 * 2. 算法步骤：
 *    - 初始化左指针 left 为 0，右指针 right 为数组长度减 1
 *    - 初始化最大面积 max_area 为 0
 *    - 当 left < right 时：
 *      a. 计算当前面积：min(height[left], height[right]) * (right - left)
 *      b. 更新最大面积
 *      c. 如果 height[left] <= height[right]，则 left++，否则 right--
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)，其中 n 是数组的长度
 *    - 空间复杂度: O(1)，只使用常数级别的额外空间
 */

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

TEST(Daily, 11) {
    class Solution {
    public:
        int maxArea(vector<int> &height) {
            int i = 0;
            int j = height.size() - 1;
            int result = 0;
            while (i < j) {
                int area = (j - i) * min(height[i], height[j]);
                result = max(result, area);
                if (height[i] <= height[j]) i++;
                else j--;
            }
            return result;
        }
    };

    Solution s;
    
    // 测试用例 1
    vector<int> height1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    EXPECT_EQ(s.maxArea(height1), 49);
    
    // 测试用例 2
    vector<int> height2 = {1, 1};
    EXPECT_EQ(s.maxArea(height2), 1);
    
    // 测试用例 3
    vector<int> height3 = {4, 3, 2, 1, 4};
    EXPECT_EQ(s.maxArea(height3), 16);
    
    // 测试用例 4
    vector<int> height4 = {1, 2, 1};
    EXPECT_EQ(s.maxArea(height4), 2);
}
