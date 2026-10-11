//
// Created by hankun on 2026/10/2.
//

/**
 * @file top150_57.cpp
 * @brief LeetCode 57. 插入区间
 *
 * @题目描述
 * 给你一个无重叠的、按照区间起始端点排序的区间列表 intervals，
 * 其中 intervals[i] = [start_i, end_i] 表示第 i 个区间的开始和结束。
 * 再给你一个区间 newInterval，表示新的区间 [start, end]。
 * 将 newInterval 插入到 intervals 中，使得 intervals 依然按照起始端点排序，
 * 且区间之间不重叠（如有必要，可以合并区间）。
 * 返回插入后的区间列表。
 *
 * @示例
 * 示例 1：
 * 输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
 * 输出：[[1,5],[6,9]]
 * 解释：新区间 [2,5] 与 [1,3] 重叠，合并为 [1,5]。
 *
 * 示例 2：
 * 输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 * 输出：[[1,2],[3,10],[12,16]]
 * 解释：新区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠，合并为 [3,10]。
 *
 * @解题思路
 * 1. 排序 + 定位重叠区间：
 *    - 先按区间起点排序，保证列表有序
 *    - 扫描找到与新区间重叠的起始下标 begin（第一个终点大于新起点的区间）
 *      和结束下标 end（最后一个起点小于新终点的区间）
 *    - begin 之前的区间与新区间无重叠，直接加入结果
 *    - 重叠部分与新区间合并为一个区间：起点取重叠区间的最小起点，
 *      终点取重叠区间终点与新终点的较大值
 *    - end 之后的区间无重叠，直接加入结果
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n log n)，主要是排序开销
 *    - 空间复杂度: O(n)，用于存储结果
 */

#include <gtest/gtest.h>
using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    vector<vector<int> > insert(vector<vector<int> >& intervals, vector<int>& newInterval) {
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

        vector<vector<int> > ret;
        int left = newInterval[0];
        int right = newInterval[1];
        int begin = -1;
        int end = -1;
        for (auto i = 0; i < intervals.size(); i++) {
            auto v = intervals[i];
            if (begin == -1 && v[1] > left) {
                begin = i;
            }

            if (v[0] < right) {
                end = i;
            }
        }

        for (auto i = 0; i < begin; i++) {
            ret.push_back(intervals[i]);
        }

        auto ev = intervals[end][1] > right ? intervals[end][1] : right;
        ret.push_back(vector<int>{intervals[begin][0], ev});

        for (auto i = end + 1; i < intervals.size(); i++) {
            ret.push_back(intervals[i]);
        }

        return ret;
    }
};
}  // namespace

TEST(top150, 57) {
    Solution s;
    vector<vector<int> > intervals = {{1, 3}, {6, 9}};
    vector<int> newInterval = {2, 5};
    auto ret = s.insert(intervals, newInterval);
    EXPECT_EQ(ret.size(), 2);
}
