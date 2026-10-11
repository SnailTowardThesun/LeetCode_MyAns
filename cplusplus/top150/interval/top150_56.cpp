//
// Created by hankun on 2026/10/1.
//

/**
 * @file top150_56.cpp
 * @brief LeetCode 56. 合并区间
 *
 * @题目描述
 * 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [start_i, end_i]。
 * 合并所有重叠的区间，并返回一个不重叠的区间数组，
 * 该数组需恰好覆盖输入中的所有区间。
 *
 * @示例
 * 示例 1：
 * 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
 * 输出：[[1,6],[8,10],[15,18]]
 * 解释：区间 [1,3] 和 [2,6] 重叠，将它们合并为 [1,6]。
 *
 * 示例 2：
 * 输入：intervals = [[1,4],[4,5]]
 * 输出：[[1,5]]
 * 解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
 *
 * @解题思路
 * 1. 排序 + 一次合并：
 *    - 将所有区间按起点升序排序
 *    - 遍历排序后的区间，维护结果列表 ret：
 *      a. 若 ret 为空，或当前区间起点大于 ret 最后一个区间的终点，
 *         说明无重叠，直接加入当前区间
 *      b. 否则有重叠，将 ret 最后一个区间的终点更新为两者终点的较大值
 *    - 排序后所有可合并的区间必然相邻，一次遍历即可完成
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n log n)，主要是排序开销
 *    - 空间复杂度: O(n)，用于存储结果（排序额外 O(log n)）
 */

#include <gtest/gtest.h>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    vector<vector<int> > merge(vector<vector<int> >& intervals) {
        vector<vector<int> > ret;

        if (intervals.empty()) {
            return ret;
        }

        sort(intervals.begin(), intervals.end());
        for (int i = 0; i < intervals.size(); ++i) {
            int left = intervals[i][0];
            int right = intervals[i][1];
            if (ret.empty() || ret.back()[1] < left) {
                ret.push_back({left, right});
            } else {
                ret.back()[1] = max(ret.back()[1], right);
            }
        }

        return ret;
    }
};
}  // namespace

TEST(top150, 56) {
    Solution s;
    vector<vector<int> > intervals{{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    auto ret = s.merge(intervals);
    EXPECT_EQ(ret.size(), 3);
}
