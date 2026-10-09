// 2078. Two Furthest Houses With Different Colors
// 题目：https://leetcode.com/problems/two-furthest-houses-with-different-colors/
//
// @题目描述:
// 一排 n 栋房子，第 i 栋房子的颜色是 colors[i]。
// 返回两栋颜色不同房子之间的最大距离。若不存在这样的两栋房子，返回 -1。
//
// @示例:
// 示例 1：
// 输入：colors = [1,1,1,6,1,1,1]
// 输出：3
// 解释：首尾房子颜色均为 1，与中间的 6 之间最大距离为 3。
//
// 示例 2：
// 输入：colors = [0,1]
// 输出：1
//
// @解题思路:
// 1. 首先检查首尾元素是否不同，如果不同则直接返回最大距离（数组长度-1）
// 2. 如果首尾元素相同，遍历中间元素，寻找与首尾不同的元素
// 3. 计算每个不同元素到首尾的最大距离，取最大值作为结果
// 4. 时间复杂度：O(n)，空间复杂度：O(1)

#include <gtest/gtest.h>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& colors) {
        if(colors[0] != colors[colors.size() - 1]) {
            return colors.size() - 1;
        }
        int ret = INT_MIN;
        for (int i = 1; i < static_cast<int>(colors.size())-1; i++) {
            if (colors[i] != colors[0]) {
                int tmp = max(i, static_cast<int>(colors.size()) - 1 - i);
                ret = max(ret, tmp);
            }
        }

        return ret;
    }
};

TEST(Daily, 2078) {
    Solution sol;
    vector<int> colors = {1,1,1,6,1,1};
    EXPECT_EQ(sol.maxDistance(colors), 3);
}
