//
// Created by 韩堃 on 2026/4/13.
//

/*
题目：1848. 到目标元素的最小距离

题目描述：
给你一个整数数组 nums（下标从 0 开始）和两个整数 target 和 start。
请你找出一个下标 i，满足 nums[i] == target 且 abs(i - start) 最小化。
返回 abs(i - start) 的最小值。

解题思路：
1. 遍历数组，收集所有等于 target 的元素的下标
2. 遍历这些下标，计算每个下标与 start 的距离的绝对值
3. 找出最小的距离并返回

时间复杂度：O(n)，其中 n 是数组的长度
空间复杂度：O(k)，其中 k 是等于 target 的元素的个数
*/

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        vector<int> container;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == target) {
                container.push_back(i);
            }
        }

        int ret = INT_MAX;
        for (auto i : container) {
            ret = min(ret, abs(i - start));
        }
        return ret;
    }
};

TEST(Daily, 1848) {
    Solution s;

    auto nums = vector<int>{1, 2, 3, 4, 5};
    auto target = 5, start = 3;

    auto ret = s.getMinDistance(nums, target, start);
    EXPECT_EQ(ret, 1);
}
