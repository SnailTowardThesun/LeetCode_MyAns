//
// Created by hankun on 5/24/26.
//

/**
 * @题目描述
 * 1340. 跳跃游戏 V
 * 给你一个整数数组 arr 和一个整数 d。每一步你可以从下标 i 跳到：
 * - i + x，其中 i + x < arr.length 且 0 < x <= d
 * - i - x，其中 i - x >= 0 且 0 < x <= d
 * 
 * 除此以外，你从下标 i 跳到下标 j 需要满足：
 * - arr[i] > arr[j]
 * - 对于所有满足 i < k < j 或 j < k < i 的下标 k，都有 arr[i] > arr[k]
 * 
 * 你可以选择数组的任意下标开始跳跃。请你返回你最多可以访问多少个下标。
 * 
 * @示例
 * 示例 1：
 * 输入: arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
 * 输出: 4
 * 解释: 可以从下标 10 出发，跳跃路径为 10 -> 8 -> 6 -> 7
 * 
 * 示例 2：
 * 输入: arr = [3,3,3,3,3], d = 3
 * 输出: 1
 * 解释: 任意两个相邻位置的高度相同，无法跳跃
 * 
 * 示例 3：
 * 输入: arr = [7,6,5,4,3,2,1], d = 1
 * 输出: 7
 * 解释: 可以从下标 0 出发，依次跳跃到每个位置
 * 
 * @解题思路
 * 方法：记忆化搜索 + 动态规划
 * 1. 定义 dfs(i) 表示从位置 i 开始跳跃能访问的最大下标数
 * 2. 对于每个位置 i，枚举所有可能的跳跃目标 j
 * 3. 跳跃条件：
 *    - |i - j| <= d
 *    - arr[i] > arr[j]
 *    - i 和 j 之间没有比 arr[i] 更高的位置
 * 4. 使用记忆化数组避免重复计算
 * 
 * @复杂度分析
 * 时间复杂度: O(n * d)
 * 空间复杂度: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = static_cast<int>(arr.size());
        vector<int> memo(n, -1);
        int result = 0;
        
        for (int i = 0; i < n; ++i) {
            result = max(result, dfs(arr, memo, d, i, n));
        }
        
        return result;
    }
    
private:
    int dfs(vector<int>& arr, vector<int>& memo, int d, int pos, int n) {
        if (memo[pos] != -1) {
            return memo[pos];
        }
        
        int maxLen = 1;
        
        for (int i = pos - 1; i >= max(0, pos - d); --i) {
            if (arr[i] >= arr[pos]) {
                break;
            }
            maxLen = max(maxLen, dfs(arr, memo, d, i, n) + 1);
        }
        
        for (int i = pos + 1; i <= min(n - 1, pos + d); ++i) {
            if (arr[i] >= arr[pos]) {
                break;
            }
            maxLen = max(maxLen, dfs(arr, memo, d, i, n) + 1);
        }
        
        memo[pos] = maxLen;
        return maxLen;
    }
};

#include <gtest/gtest.h>

TEST(Daily, 1340) {
    Solution s;

    vector<int> arr1{6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12};
    EXPECT_EQ(s.maxJumps(arr1, 2), 4);

    vector<int> arr2{3, 3, 3, 3, 3};
    EXPECT_EQ(s.maxJumps(arr2, 3), 1);

    vector<int> arr3{7, 6, 5, 4, 3, 2, 1};
    EXPECT_EQ(s.maxJumps(arr3, 1), 7);

    vector<int> arr4{1};
    EXPECT_EQ(s.maxJumps(arr4, 1), 1);
}