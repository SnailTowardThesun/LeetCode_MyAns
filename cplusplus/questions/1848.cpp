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
1. 遍历数组，对于每个等于 target 的元素
2. 计算当前元素下标与 start 的距离的绝对值
3. 维护并更新最小距离
4. 遍历完成后返回最小距离

时间复杂度：O(n)，其中 n 是数组的长度
空间复杂度：O(1)，只使用了常数级的额外空间
*/

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int ret = INT_MAX;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == target) {
                ret = min(ret, abs(i - start));
            }
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
