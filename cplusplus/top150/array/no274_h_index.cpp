/**
 * @file no274_h_index.cpp
 * @brief LeetCode 274. H 指数
 *
 * @题目描述
 * 给你一个整数数组 citations，其中 citations[i] 表示研究者的第 i 篇论文被引用的次数。
 * 计算并返回该研究者的 h 指数。根据维基百科上 h 指数的定义：h 代表"高引用次数"，
 * 一名科研人员的 h 指数是指他（她）至少有 h 篇论文分别被引用了至少 h 次。
 * 且其余的 N - h 篇论文每篇被引用次数不超过 h 次。
 * 如果 h 有多种可能的值，h 指数是其中最大的那个。
 *
 * @示例
 * 示例 1：
 * 输入: citations = [3,0,6,1,5]
 * 输出: 3
 * 解释: 给定数组表示研究者总共有 5 篇论文，每篇论文相应的被引用了 3, 0, 6, 1, 5 次。
 *      由于研究者有 3 篇论文每篇至少被引用了 3 次，且其余两篇论文每篇被引用不多于 3 次，
 *      所以她的 h 指数是 3。
 *
 * 示例 2：
 * 输入: citations = [1,3,1]
 * 输出: 1
 *
 * @解题思路
 * 1. 排序法：
 *    - 将引用次数按降序排列
 *    - 找到最大的 h，使得 citations[h-1] >= h
 *    - 即找到第一个满足 citations[i] < i + 1 的位置
 *
 * 2. 计数排序法（优化）：
 *    - 使用一个数组统计引用次数的分布
 *    - 从后向前累加，找到满足条件的 h
 *    - 时间复杂度 O(n)，空间复杂度 O(n)
 *
 * @复杂度分析
 * - 时间复杂度: O(n log n)，需要对数组进行排序
 * - 空间复杂度: O(1) 或 O(log n)，取决于排序算法的空间复杂度
 */

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

TEST(TOP150, No274_HIndex) {
    class Solution {
    public:
        int h_index(vector<int>& citations) {
            std::sort(citations.begin(), citations.end(), std::greater<int>());
            auto ret = 0;

            for (auto i = 0; i < citations.size(); i++) {
                if (citations[i] > ret) {
                    ret++;
                }
            }

            return ret;
        }
    };

    Solution solution;
    std::vector<int> citations{3, 0, 6, 1, 5};
    auto ret = solution.h_index(citations);
    EXPECT_EQ(ret, 3);
}
