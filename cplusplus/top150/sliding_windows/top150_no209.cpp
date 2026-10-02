//
// Created by hankun on 6/20/26.
//

// @题目描述:
// 给定含有 n 个正整数的数组和正整数 target，找出满足「子数组元素和 >= target」的
// 最短连续子数组，返回其长度；不存在则返回 0。
//
// @示例:
// 输入：target = 7, nums = [2,3,1,2,4,3]
// 输出：2
// 解释：子数组 [4,3] 是满足条件的最短子数组。
//
// @解题思路:
// 滑动窗口（数组元素全为正是收缩窗口的前提）。
// 1. 右指针逐个纳入元素并累加 sum。
// 2. sum >= target 时，记录当前窗口长度并不断从左侧移出元素，直到 sum < target。
// 3. 全过程未找到合法窗口（结果仍为 INT_MAX）返回 0。
//
// 复杂度分析：
// - 时间复杂度：O(n)，每个元素最多进出窗口一次。
// - 空间复杂度：O(1)。

#include <gtest/gtest.h>

#include <climits>
#include <vector>

using namespace std;

class Solution {
   public:
    int minSubArrayLen(int target, vector<int> &nums) {
        int n = nums.size();
        int left = 0;
        int sum = 0;
        int result = INT_MAX;

        for (int right = 0; right < n; right++) {
            sum += nums[right];

            while (sum >= target) {
                result = min(result, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }

        return result == INT_MAX ? 0 : result;
    }
};

TEST(TOP150, 209) {
    auto target = 7;
    vector<int> nums{2, 3, 1, 2, 4, 3};
    Solution s;
    auto ret = s.minSubArrayLen(target, nums);
    EXPECT_EQ(ret, 2);
}
