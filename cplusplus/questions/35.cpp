//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 35.cpp
 * @brief LeetCode 35. 搜索插入位置
 *
 * @题目描述
 * 给定一个排序数组和一个目标值，如果在数组中找到目标值，则返回其索引。如果没有，请返回它将被插入的位置（假设数组中不存在重复元素）。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [1,3,5,6], target = 5
 * 输出：2
 *
 * 示例 2：
 * 输入：nums = [1,3,5,6], target = 2
 * 输出：1
 *
 * 示例 3：
 * 输入：nums = [1,3,5,6], target = 7
 * 输出：4
 *
 * @解题思路
 * 1. 线性搜索法：
 *    - 遍历数组，找到第一个大于等于目标值的位置
 *
 * 2. 算法步骤：
 *    - 遍历数组中的每个元素
 *    - 如果当前元素大于等于目标值，返回当前索引
 *    - 如果遍历结束都没找到，返回数组长度
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(1)
 */

#include <gtest/gtest.h>

using namespace std;

TEST(Daily, 35) {
    class Solution {
    public:
        int searchInsert(int A[], int n, int target) {
            int i = 0;
            for (i = 0; i < n; i++)
                if (target <= A[i])
                    return i;
            return i;
        }
    };

    Solution s;
    
    // 测试用例 1
    int A1[] = {1, 3, 5, 6};
    EXPECT_EQ(s.searchInsert(A1, 4, 5), 2);
    
    // 测试用例 2
    int A2[] = {1, 3, 5, 6};
    EXPECT_EQ(s.searchInsert(A2, 4, 2), 1);
    
    // 测试用例 3
    int A3[] = {1, 3, 5, 6};
    EXPECT_EQ(s.searchInsert(A3, 4, 7), 4);
    
    // 测试用例 4
    int A4[] = {1, 3, 5, 6};
    EXPECT_EQ(s.searchInsert(A4, 4, 0), 0);
}
