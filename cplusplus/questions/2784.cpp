//
// Created by hankun on 5/10/26.
//

/**
 * @file 2784.cpp
 * @brief LeetCode 2784. Check if Array is Good（检查数组是否良好）
 *
 * @题目描述
 * 给定一个整数数组 nums，如果数组是 "good" 的，返回 true，否则返回 false。
 * "good" 数组是指：该数组是 base[n] 的排列。
 * base[n] = [1, 2, ..., n-1, n, n]，长度为 n+1，包含 1 到 n-1 各一次，n 出现两次。
 * 例如：base[1] = [1, 1]，base[3] = [1, 2, 3, 3]。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [1, 3, 3, 2]
 * 输出：true
 * 解释：数组的最大元素是 3，所以 n = 3。数组是 base[3] = [1, 2, 3, 3] 的排列。
 *
 * 示例 2：
 * 输入：nums = [2, 1, 3]
 * 输出：false
 * 解释：数组的最大元素是 3，所以 n = 3。但数组长度为 3，而 base[3] 长度为 4，不可能相等。
 *
 * 示例 3：
 * 输入：nums = [1, 1]
 * 输出：true
 * 解释：数组的最大元素是 1，所以 n = 1。数组是 base[1] = [1, 1] 的排列。
 *
 * @解题思路
 * 使用计数法来判断数组是否为 good 数组：
 *
 * 1. 统计数组中每个元素出现的次数
 * 2. 验证以下条件：
 *    - 最大元素（n）必须出现恰好 2 次
 *    - 对于所有 i（1 ≤ i < n），每个元素必须恰好出现 1 次
 * 3. 如果以上条件都满足，返回 true；否则返回 false
 *
 * 复杂度分析：
 * - 时间复杂度: O(n)，只需要遍历数组一次
 * - 空间复杂度: O(n)，需要额外的数组存储计数
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
public:
    bool isGood(const vector<int>& nums) {
        int n = nums.size() - 1;
        vector<int> cnt(201);

        for (int x : nums) {
            ++cnt[x];
        }

        if (cnt[n] != 2) {
            return false;
        }

        for (int i = 1; i < n; ++i) {
            if (cnt[i] != 1) {
                return false;
            }
        }

        return true;
    }
};

TEST(Daily, 2784) {
    Solution s;

    EXPECT_TRUE(s.isGood(vector<int>{1, 3, 3, 2}));
    EXPECT_FALSE(s.isGood(vector<int>{2, 1, 3}));
    EXPECT_TRUE(s.isGood(vector<int>{1, 1}));
    EXPECT_FALSE(s.isGood(vector<int>{3, 4, 4, 1, 2, 1}));
}
