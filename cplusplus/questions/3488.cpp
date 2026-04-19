//
// Created by 韩堃 on 2026/4/16.
//
// 题目描述：
// 在一个环形数组中，对于每个查询位置，找到与该位置元素值相同的最近元素的距离。
// 环形数组意味着数组的首尾是相连的。
//
// 解题思路：
// 1. 使用哈希表记录每个元素值对应的所有位置
// 2. 对于每个查询位置，找到其对应元素值的所有位置
// 3. 使用二分查找找到查询位置在位置列表中的位置
// 4. 检查前一个和后一个位置的距离，同时考虑环形情况
// 5. 计算并返回最小距离
//

#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

class Solution {
   public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        vector<int> ret(queries.size(), -1);
        unordered_map<int, std::vector<int> > container;

        for (int i = 0; i < nums.size(); i++) {
            container[nums[i]].push_back(i);
        }

        int n = nums.size();
        for (auto i = 0; i < queries.size(); i++) {
            int query_pos = queries[i];
            int t = nums[query_pos];
            auto it = container.find(t);
            if (it->second.size() < 2) {
                continue;
            }

            int tmp_ret = INT_MAX;
            const auto& positions = it->second;
            auto current_pos = lower_bound(positions.begin(), positions.end(), query_pos);

            // 计算最小距离的辅助函数
            auto calculate_min_distance = [&](int pos) {
                int dir = abs(pos - query_pos);
                int cir = n - dir;
                return min(cir, dir);
            };

            // 检查前一个元素
            if (current_pos != positions.begin()) {
                tmp_ret = min(tmp_ret, calculate_min_distance(*(current_pos - 1)));
            } else if (positions.size() > 1) {
                // 环形情况：检查最后一个元素
                tmp_ret = min(tmp_ret, calculate_min_distance(positions.back()));
            }

            // 检查后一个元素
            if (current_pos != positions.end() - 1) {
                tmp_ret = min(tmp_ret, calculate_min_distance(*(current_pos + 1)));
            } else if (positions.size() > 1) {
                // 环形情况：检查第一个元素
                tmp_ret = min(tmp_ret, calculate_min_distance(positions.front()));
            }

            ret[i] = tmp_ret;
        }

        return ret;
    }
};

TEST(Daily, 3488) {
    Solution s;
    auto nums = vector<int>{1, 3, 1, 4, 1, 3, 2};
    auto queries = vector<int>{0, 3, 5};

    auto ret = s.solveQueries(nums, queries);
    EXPECT_EQ(ret.size(), 3);
}
