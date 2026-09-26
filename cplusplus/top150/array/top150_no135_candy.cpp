/**
 * @file top150_no135_candy.cpp
 * @brief LeetCode 135. 分发糖果
 *
 * @题目描述
 * n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。
 * 你需要按照以下要求，给这些孩子分发糖果：
 * - 每个孩子至少分配到 1 个糖果。
 * - 相邻两个孩子评分更高的孩子会获得更多的糖果。
 * 请你给每个孩子分发糖果，计算并返回需要准备的糖果的最少数量。
 *
 * @示例
 * 示例 1：
 * 输入: ratings = [1,0,2]
 * 输出: 5
 * 解释: 你可以分别给第一个、第二个、第三个孩子分发 2、1、2 颗糖果。
 *
 * 示例 2：
 * 输入: ratings = [1,2,2]
 * 输出: 4
 * 解释: 你可以分别给第一个、第二个、第三个孩子分发 1、2、1 颗糖果。
 *      第三个孩子只得到 1 颗糖果，这满足题面中的两个条件。
 *
 * @解题思路
 * 1. 两次遍历法：
 *    - 先从左到右遍历：如果 ratings[i] > ratings[i-1]，则 candies[i] = candies[i-1] + 1
 *    - 再从右到左遍历：如果 ratings[i] > ratings[i+1]，则 candies[i] = max(candies[i], candies[i+1] + 1)
 *    - 最后取两个方向的最大值，确保同时满足左右两边的条件
 *
 * 2. 优化思路（常数空间）：
 *    - 可以只用一个数组，先从左到右，再从右到左更新
 *    - 或者直接在一次遍历中处理递增和递减序列
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，需要遍历数组两次
 * - 空间复杂度: O(n)，使用额外数组存储每个孩子的糖果数
 */

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int candy(vector<int> &ratings) {
        int n = ratings.size();
        // 每人先发 1 颗
        vector<int> candies(n, 1);

        // 从左到右：评分比左边高，则比左边多 1 颗
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        // 从右到左：评分比右边高，则至少比右边多 1 颗，取两种约束的最大值
        int ret = candies[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
            ret += candies[i];
        }

        return ret;
    }
};

TEST(TOP150, No135_Candy) {
    Solution solution;
    // 示例 1
    auto ratings = vector<int>{1, 0, 2};
    EXPECT_EQ(solution.candy(ratings), 5);

    // 示例 2：相等评分不强制递增
    auto ratings2 = vector<int>{1, 2, 2};
    EXPECT_EQ(solution.candy(ratings2), 4);

    // 边界：单人
    auto ratings3 = vector<int>{0};
    EXPECT_EQ(solution.candy(ratings3), 1);

    // 递减序列：糖果数为 4+3+2+1
    auto ratings4 = vector<int>{4, 3, 2, 1};
    EXPECT_EQ(solution.candy(ratings4), 10);
}
