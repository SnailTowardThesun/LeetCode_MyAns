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

using namespace std;

class Solution {
public:
    int trap(int A[], int n) {
        if (n < 3) return 0;
        int pt = 0, pb = n - 1, com = 0, result = 0, tmp = 0;
        while (pt < pb) {
            if (A[pt] > com && A[pb] > com) {
                com = A[pt] < A[pb] ? A[pt] : A[pb];
                for (int i = pt + 1; i < pb; i++) {
                    int ii = A[i];
                    result += com < A[i] ? 0 : com - (A[i] < tmp ? tmp : A[i]);
                }
                tmp = com;
            }
            A[pt] < A[pb] ? pt++ : pb--;
        }
        return result;
    }
};

TEST(Daily, 42) {
    Solution s;
    
    // 测试用例 1
    int A1[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    EXPECT_EQ(s.trap(A1, 12), 6);
    
    // 测试用例 2
    int A2[] = {4, 2, 0, 3, 2, 5};
    EXPECT_EQ(s.trap(A2, 6), 9);
    
    // 测试用例 3
    int A3[] = {1, 0, 1};
    EXPECT_EQ(s.trap(A3, 3), 1);
}
