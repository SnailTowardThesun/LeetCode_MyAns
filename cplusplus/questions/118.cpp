//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 118.cpp
 * @brief LeetCode 118. 杨辉三角
 *
 * @题目描述
 * 给定一个非负整数 numRows，生成杨辉三角的前 numRows 行。
 * 在杨辉三角中，每个数是它左上方和右上方的数的和。
 *
 * @示例
 * 示例 1：
 * 输入：numRows = 5
 * 输出：[
 *      [1],
 *     [1,1],
 *    [1,2,1],
 *   [1,3,3,1],
 *  [1,4,6,4,1]
 * ]
 *
 * 示例 2：
 * 输入：numRows = 1
 * 输出：[[1]]
 *
 * @解题思路
 * 1. 杨辉三角的特性：
 *    - 每一行的第一个和最后一个元素都是 1
 *    - 中间的元素是上一行对应位置和前一个位置的和
 *
 * 2. 算法步骤：
 *    - 初始化一个二维向量来存储杨辉三角
 *    - 遍历每一行，从第 1 行到第 numRows 行
 *    - 对于每一行，首先添加 1 作为第一个元素
 *    - 然后计算中间元素，通过上一行的元素相加得到
 *    - 最后添加 1 作为最后一个元素
 *    - 将当前行添加到结果中
 *
 * 3. 实现细节：
 *    - 当 numRows 为 0 时，返回空向量
 *    - 使用一个一维向量来逐行构建，每次在末尾添加 1，然后从后往前更新中间元素
 *
 * 4. 复杂度分析：
 *    - 时间复杂度: O(n^2)，其中 n 是 numRows
 *    - 空间复杂度: O(n^2)，用于存储杨辉三角
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(Daily, 118) {
    class Solution {
    public:
        vector<vector<int>> generate(int numRows) {
            if (numRows == 0) return vector<vector<int>>();
            vector<int> level;
            vector<vector<int>> ret;
            for (int i = 1; i <= numRows; i++) {
                int k = (int)level.size();
                for (int j = k-1; j >= 1; j--)
                    level[j] += level[j-1];
                level.push_back(1);
                ret.push_back(level);
            }
            return ret;
        }
    };

    Solution s;
    
    // 测试用例 1
    auto result1 = s.generate(5);
    EXPECT_EQ(result1.size(), 5);
    EXPECT_EQ(result1[0], vector<int>({1}));
    EXPECT_EQ(result1[1], vector<int>({1, 1}));
    EXPECT_EQ(result1[2], vector<int>({1, 2, 1}));
    EXPECT_EQ(result1[3], vector<int>({1, 3, 3, 1}));
    EXPECT_EQ(result1[4], vector<int>({1, 4, 6, 4, 1}));
    
    // 测试用例 2
    auto result2 = s.generate(1);
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(result2[0], vector<int>({1}));
    
    // 测试用例 3
    auto result3 = s.generate(0);
    EXPECT_EQ(result3.size(), 0);
    
    // 测试用例 4
    auto result4 = s.generate(3);
    EXPECT_EQ(result4.size(), 3);
    EXPECT_EQ(result4[0], vector<int>({1}));
    EXPECT_EQ(result4[1], vector<int>({1, 1}));
    EXPECT_EQ(result4[2], vector<int>({1, 2, 1}));
}
