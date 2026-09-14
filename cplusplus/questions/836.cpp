//
// Created by 韩堃 on 2026/9/14.
//

// @题目描述:
// LeetCode 836. 矩形重叠（Rectangle Overlap）
// 矩形以 [x1, y1, x2, y2] 的形式表示，其中 (x1, y1) 为左下角的坐标，
// (x2, y2) 为右上角的坐标。矩形的上下边与 x 轴平行，左右边与 y 轴平行。
// 如果两个矩形相交的面积为正，则称它们重叠。仅在角或边上接触的两个矩形
// 不算重叠。给定两个矩形 rec1 和 rec2，重叠返回 true，否则返回 false。
//
// @示例:
// 示例 1：
// 输入：rec1 = [0,0,2,2], rec2 = [1,1,3,3]
// 输出：true
// 示例 2：
// 输入：rec1 = [0,0,1,1], rec2 = [1,0,2,1]
// 输出：false
// 解释：两个矩形仅在一条边上接触，相交面积为 0，不算重叠。
// 示例 3：
// 输入：rec1 = [0,0,1,1], rec2 = [2,2,3,3]
// 输出：false
//
// @解题思路:
// 区间投影法。把两个矩形分别投影到 x 轴与 y 轴：
// - x 轴投影区间分别为 [x1, x2]，其交叠部分为
//   [max(x1), min(x2)]，长度为正的条件是 max(x1) < min(x2)。
// - y 轴投影区间分别为 [y1, y2]，同理需 max(y1) < min(y2)。
// 两个矩形面积为正地重叠，当且仅当 x、y 两个方向的投影都严格相交。
// 注意必须用严格不等号「<」：相等意味着仅边（或角）接触，面积为 0，
// 按题意不算重叠。
//
// 复杂度分析：
// - 时间复杂度：O(1)，只做常数次比较。
// - 空间复杂度：O(1)，只使用常数个变量。

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // x 轴投影交叠区间 [max_left, min_right]，严格小于才有正长度
        int max_left = max(rec1[0], rec2[0]);
        int min_right = min(rec1[2], rec2[2]);

        // y 轴投影交叠区间 [max_bottom, min_top]，严格小于才有正长度
        int max_bottom = max(rec1[1], rec2[1]);
        int min_top = min(rec1[3], rec2[3]);

        // 两个方向都严格相交，矩形才面积为正地重叠
        return max_left < min_right && max_bottom < min_top;
    }
};

TEST(Daily, 836) {
    Solution s;

    // 基本用例：部分重叠
    vector<int> rec1{0, 0, 2, 2};
    vector<int> rec2{1, 1, 3, 3};
    EXPECT_TRUE(s.isRectangleOverlap(rec1, rec2));

    // 边界用例：仅在一条边上接触，面积为 0，不算重叠
    vector<int> rec3{0, 0, 1, 1};
    vector<int> rec4{1, 0, 2, 1};
    EXPECT_FALSE(s.isRectangleOverlap(rec3, rec4));

    // 边界用例：完全分离
    vector<int> rec5{0, 0, 1, 1};
    vector<int> rec6{2, 2, 3, 3};
    EXPECT_FALSE(s.isRectangleOverlap(rec5, rec6));
}