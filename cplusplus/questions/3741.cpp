//
// Created by 韩堃 on 2026/4/11.
//

/*
题目：3741. 最小距离

题目描述：
给定一个整数数组 nums，计算数组中相同元素之间的最小距离。
具体来说，对于数组中每一个元素，找到与其值相同的其他元素的位置，计算它们之间的距离，然后取所有距离中的最小值。
如果数组中没有重复元素，返回 -1。

解题思路：
1. 使用哈希表记录每个元素出现的所有位置
2.
对于每个元素，如果它出现了至少3次（因为需要计算两个距离），则计算相邻两次出现的距离的两倍（因为题目要求的是相同元素之间的最小距离，这里可能是指连续三个相同元素之间的中间距离）
3. 遍历所有元素的位置列表，计算最小距离
4. 如果没有找到符合条件的距离，返回 -1
*/

#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

class Solution {
   public:
    int minimumDistance(vector<int>& nums) {
        unordered_map<int, std::vector<int>> container;
        for (int i = 0; i < nums.size(); ++i) {
            container[nums[i]].push_back(i);
        }

        int ret = INT_MAX;
        for (auto i : container) {
            auto values = i.second;
            for (int j = 2; j < values.size(); ++j) {
                ret = min(ret, (values[j] - values[j - 2]) * 2);
            }
        }

        return ret == INT_MAX ? -1 : ret;
    }
};

TEST(Daily, 3741) {
    Solution s;
    vector<int> nums{1, 2, 1, 1, 3};
    auto ret = s.minimumDistance(nums);
    EXPECT_EQ(ret, 6);
}
