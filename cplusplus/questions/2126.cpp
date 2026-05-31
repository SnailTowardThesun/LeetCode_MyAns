//
// Created by hankun on 5/24/26.
//

/**
 * @题目描述
 * 2126. 摧毁小行星
 * 给你一个整数 mass 表示行星的质量，以及一个整数数组 asteroids 表示行星带中小行星的质量。
 * 每个 asteroids[i] 是小行星的质量。
 * 如果满足以下条件，你可以选择下标 i 并摧毁第 i 个小行星：
 * - mass >= asteroids[i]
 * 摧毁一个小行星后，你获得它全部的质量，并加入到你的行星 mass 中。
 * 如果你能通过按任意顺序摧毁小行星来摧毁所有小行星，则返回 true；否则返回 false。
 *
 * @示例
 * 示例 1：
 * 输入: mass = 10, asteroids = [3,9,15]
 * 输出: true
 * 解释: 
 * - 首先摧毁质量为 3 的小行星，mass 变为 13
 * - 然后摧毁质量为 9 的小行星，mass 变为 22
 * - 最后摧毁质量为 15 的小行星，mass 变为 37
 *
 * 示例 2：
 * 输入: mass = 10, asteroids = [4,9,23]
 * 输出: false
 * 解释:
 * - 只能先摧毁质量为 4 的小行星，mass 变为 14
 * - 然后摧毁质量为 9 的小行星，mass 变为 23
 * - 但无法摧毁质量为 23 的小行星（mass = 23 < 23），返回 false
 *
 * 示例 3：
 * 输入: mass = 5, asteroids = [4,9,23,5]
 * 输出: false
 * 解释: 无法摧毁质量为 23 的小行星
 *
 * @解题思路
 * 方法：贪心算法
 * 1. 将小行星按质量从小到大排序
 * 2. 依次尝试摧毁每个小行星
 * 3. 如果当前质量 >= 小行星质量，则摧毁它并累加质量
 * 4. 否则返回 false
 *
 * 原理：为了最大化成功机会，应该先摧毁质量最小的小行星，积累更多质量。
 * 这是一个典型的贪心策略：每次选择当前可完成的最小任务，以留出更多可能性给后续任务。
 *
 * @复杂度分析
 * 时间复杂度: O(n log n)，排序需要 O(n log n)，遍历需要 O(n)
 * 空间复杂度: O(1)，不计排序栈空间
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool asteroidsDestroyed(int mass, const vector<int>& asteroids) {
        int64_t currentMass = mass;
        vector<int> sortedAsteroids = asteroids;
        sort(sortedAsteroids.begin(), sortedAsteroids.end());
        
        for (int asteroid : sortedAsteroids) {
            if (currentMass < asteroid) {
                return false;
            }
            currentMass += asteroid;
        }
        
        return true;
    }
};

#include <gtest/gtest.h>

TEST(Daily, 2126) {
    Solution s;

    EXPECT_TRUE(s.asteroidsDestroyed(10, vector<int>{3, 9, 15}));
    EXPECT_TRUE(s.asteroidsDestroyed(10, vector<int>{4, 9, 23}));
    EXPECT_TRUE(s.asteroidsDestroyed(5, vector<int>{4, 9, 23, 5}));
    
    EXPECT_TRUE(s.asteroidsDestroyed(1, vector<int>{1}));
    EXPECT_TRUE(s.asteroidsDestroyed(100, vector<int>{1, 2, 3, 4, 5}));
}