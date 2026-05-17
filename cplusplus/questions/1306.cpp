//
// Created by hankun on 5/17/26.
//

/**
 * @file 1306.cpp
 * @brief LeetCode 1306. Jump Game III（跳跃游戏 III）
 *
 * @题目描述
 * 给定一个整数数组 arr，以及一个起始位置 start。
 * 对于 arr 中的每个元素，可以跳转到索引 start + arr[start] 或 start - arr[start]。
 * 判定是否能够跳转到某个索引值为 0 的位置。
 * 如果可以返回 true，否则返回 false。
 *
 * @示例
 * 示例 1：
 * 输入：arr = [4,2,3,0,3,1,2], start = 5
 * 输出：true
 * 解释：
 * 起始位置 5 -> 索引 4 (5 - 1) -> 索引 0 (4 - 4) -> 到达值为 0 的位置
 *
 * 示例 2：
 * 输入：arr = [4,2,3,0,3,1,2], start = 0
 * 输出：true
 * 解释：
 * 起始位置 0 -> 索引 4 (0 + 4) -> 索引 0 (4 - 4) -> 到达值为 0 的位置
 *
 * 示例 3：
 * 输入：arr = [3,0,2,1,2], start = 2
 * 输出：false
 *
 * @解题思路
 * 使用深度优先搜索（DFS）+ 记忆化搜索：
 *
 * 1. DFS 递归搜索：
 *    - 从起始位置 start 开始
 *    - 尝试跳转到 start + arr[start] 和 start - arr[start]
 *    - 如果跳转到值为 0 的位置，返回 true
 *    - 如果跳转到已访问过的位置，返回 false
 *
 * 2. 记忆化搜索：
 *    - 使用 visited 数组记录已访问的位置
 *    - 避免重复访问导致无限循环
 *
 * 复杂度分析：
 * - 时间复杂度: O(n)，每个位置最多访问一次
 * - 空间复杂度: O(n)，用于 visited 数组和递归栈
 */

#include <gtest/gtest.h>
#include <vector>
using namespace std;

class Solution {
public:
    bool dfs(vector<int> &arr, int start, vector<bool> &visited) {
        if (start < 0 || start >= arr.size() || visited[start]) {
            return false;
        }

        if (arr[start] == 0) {
            return true;
        }
        visited[start] = true;
        if (start + arr[start] < arr.size()) {
            if (dfs(arr, start + arr[start], visited)) {
                return true;
            }
        }

        if (start - arr[start] < arr.size() && start - arr[start] >= 0) {
            if (dfs(arr, start - arr[start], visited)) {
                return true;
            }
        }

        return false;
    }

    bool canReach(vector<int> &arr, int start) {
        vector<bool> visited(arr.size(), false);
        return dfs(arr, start, visited);
    }
};

TEST(Daily, 1306) {
    Solution s;

    // 测试用例 1
    auto arr1 = vector<int>{4, 2, 3, 0, 3, 1, 2};
    EXPECT_TRUE(s.canReach(arr1, 5));

    // 测试用例 2
    auto arr2 = vector<int>{4, 2, 3, 0, 3, 1, 2};
    EXPECT_TRUE(s.canReach(arr2, 0));

    // 测试用例 3
    auto arr3 = vector<int>{3, 0, 2, 1, 2};
    EXPECT_FALSE(s.canReach(arr3, 2));
}
