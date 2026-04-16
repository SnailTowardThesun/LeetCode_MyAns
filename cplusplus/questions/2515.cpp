//
// Created by 韩堃 on 2026/4/15.
//

/*
题目：2515. 到目标字符串的最短距离 II

题目描述：
给你一个下标从 0 开始的环形字符串数组 words 和一个字符串 target。环形数组意味着数组首尾相连。
同时给你一个整数 startIndex。

你的任务是找到从 startIndex 出发到最近的 target 字符串的距离。
如果 target 不在 words 中，返回 -1。

注意：距离是指从 startIndex 到目标字符串的下标移动的最小步数，移动可以是顺时针或逆时针。

解题思路：
1. 首先遍历数组，收集所有等于 target 的元素的下标
2. 如果没有找到 target，返回 -1
3. 对于每个 target 元素的下标，计算从 startIndex 到该下标的顺时针和逆时针距离
4. 取所有距离中的最小值作为结果返回

时间复杂度：O(n)，其中 n 是数组的长度
空间复杂度：O(k)，其中 k 是等于 target 的元素的个数
*/

#include <gtest/gtest.h>

#include <vector>

using namespace std;

class Solution {
   public:
    int closestTarget(vector<string>& words, string target, int startIndex) {
        vector<int> poss;
        for (int i = 0; i < words.size(); ++i) {
            if (words[i] == target) {
                poss.push_back(i);
            }
        }

        if (poss.empty()) {
            return -1;
        }

        int ret = INT_MAX;
        int n = words.size();
        for (auto pos : poss) {
            int direct_dist = abs(pos - startIndex);
            int circular_dist = n - direct_dist;
            int tmp = min(direct_dist, circular_dist);
            ret = min(ret, tmp);
        }

        return ret;
    }
};

TEST(Daily, 2515) {
    Solution s;
    auto words = vector<string>{"hsdqinnoha", "mqhskgeqzr", "zemkwvqrww", "zemkwvqrww", "daljcrktje",
                                "fghofclnwp", "djwdworyka", "cxfpybanhd", "fghofclnwp", "fghofclnwp"};
    auto target = "zemkwvqrww";
    auto startIndex = 8;

    auto ret = s.closestTarget(words, target, startIndex);
    EXPECT_EQ(ret, 4);
}
