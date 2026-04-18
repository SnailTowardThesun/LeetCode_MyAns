//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 80.cpp
 * @brief LeetCode 80. 删除有序数组中的重复项 II
 *
 * @题目描述
 * 给你一个有序数组 nums，请你原地删除重复出现的元素，使每个元素最多出现两次，返回移除后数组的新长度。
 * 不要使用额外的数组空间，必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [1,1,1,2,2,3]
 * 输出：5
 * 解释：函数应返回新长度 5，前五个元素为 1, 1, 2, 2, 3
 *
 * 示例 2：
 * 输入：nums = [0,0,1,1,1,1,2,3,3]
 * 输出：7
 * 解释：函数应返回新长度 7，前七个元素为 0, 0, 1, 1, 2, 3, 3
 *
 * @解题思路
 * 1. 双指针法：
 *    - 使用两个指针，一个用于遍历数组，一个用于记录不重复元素的位置
 *    - 记录每个元素出现的次数，超过 2 次就跳过
 *
 * 2. 算法步骤：
 *    - 如果数组为空或长度小于等于 2，直接返回长度
 *    - 使用 startPosition 记录不重复元素的位置
 *    - 使用 isRepeated 记录当前元素是否已经重复过
 *    - 遍历数组，处理每个元素
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(1)
 */

#include <gtest/gtest.h>

using namespace std;

TEST(Daily, 80) {
    class Solution {
    public:
        int removeDuplicates(int A[], int n) {
            if (A == NULL || n == 0) return 0;
            int startPosition = 0;
            bool isRepeated = false;
            for (int i = 1; i < n; i++) {
                if (A[i] != A[startPosition]) {
                    isRepeated = false;
                    startPosition++;
                    A[startPosition] = A[i];
                } else {
                    if (isRepeated == false) {
                        startPosition++;
                        A[startPosition] = A[i];
                        isRepeated = true;
                    }
                }
            }
            return startPosition + 1;
        }
    };

    Solution s;
    
    // 测试用例 1
    int A1[] = {1, 1, 1, 2, 2, 3};
    EXPECT_EQ(s.removeDuplicates(A1, 6), 5);
    
    // 测试用例 2
    int A2[] = {0, 0, 1, 1, 1, 1, 2, 3, 3};
    EXPECT_EQ(s.removeDuplicates(A2, 9), 7);
    
    // 测试用例 3
    int A3[] = {1, 1};
    EXPECT_EQ(s.removeDuplicates(A3, 2), 2);
    
    // 测试用例 4
    int A4[] = {1};
    EXPECT_EQ(s.removeDuplicates(A4, 1), 1);
}
