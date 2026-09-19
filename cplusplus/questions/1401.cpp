// @题目描述:
// LeetCode 1401. 圆和矩形是否有重叠（Circle and Rectangle Overlapping）
// 给你一个以 (radius, xCenter, yCenter) 表示的圆，以及一个轴对齐矩形，
// 矩形以 (x1, y1, x2, y2) 表示，其中 (x1, y1) 是左下角坐标，
// (x2, y2) 是右上角坐标。
// 如果圆和矩形有重叠（即存在既属于圆又属于矩形的点），返回 true，
// 否则返回 false。
// 注意：圆周上的点也算属于圆，因此相切的情况算作重叠。
//
// @示例:
// 示例 1：
// 输入：radius = 1, xCenter = 0, yCenter = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
// 输出：true
// 解释：圆与矩形在边 x=1 处相切，存在公共点，算重叠。
// 示例 2：
// 输入：radius = 1, xCenter = 1, yCenter = 1, x1 = 1, y1 = -3, x2 = 2, y2 = -1
// 输出：false
// 示例 3：
// 输入：radius = 1, xCenter = 0, yCenter = 0, x1 = -1, y1 = -1, x2 = 3, y2 = 3
// 输出：true
// 解释：圆心在矩形内部，圆完全与矩形重叠。
//
// @解题思路:
// 最近点法。圆与矩形有公共点，等价于圆心到矩形的最近距离 <= radius。
// 把圆心钳制（clamp）到矩形范围上：横坐标钳到 [x1, x2]，纵坐标钳到
// [y1, y2]，得到矩形上距离圆心最近的点 (x, y)：
//   - 圆心在矩形内时，(x, y) 就是圆心本身，距离为 0，必然重叠；
//   - 圆心在矩形外时，(x, y) 落在矩形边界上。
// 再用勾股定理判断该点到圆心的距离平方是否 <= radius^2。
// 注意事项：
// - 题目判定「存在公共点」，圆周上的点属于圆，所以相切（距离 == radius）
//   算重叠，必须用 <= 而不是 <；
// - 全程用距离平方比较，避免开方与浮点误差；
// - radius <= 10^4，radius^2 <= 10^8，int 不会溢出。
//
// 复杂度分析：
// - 时间复杂度：O(1)，常数次比较与乘法。
// - 空间复杂度：O(1)。

#include <gtest/gtest.h>

#include <algorithm>

using namespace std;

class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        // 将圆心钳制到矩形范围内，得到矩形上离圆心最近的点
        int x = clamp(xCenter, x1, x2);
        int y = clamp(yCenter, y1, y2);

        // 最近点距离平方 <= 半径平方，即存在公共点；相切（相等）也算重叠
        return ((x - xCenter)*(x-xCenter) + (y - yCenter) * (y - yCenter)) <= radius * radius;
    }
};

TEST(Daily, 1401) {
    Solution s;

    // 示例 1：圆与矩形相切，算重叠
    EXPECT_TRUE(s.checkOverlap(1, 0, 0, 1, -1, 3, 1));

    // 示例 2：圆与矩形完全分离
    EXPECT_FALSE(s.checkOverlap(1, 1, 1, 1, -3, 2, -1));

    // 圆心在矩形内部，必然重叠
    EXPECT_TRUE(s.checkOverlap(1, 0, 0, -1, -1, 3, 3));

    // 圆在矩形远处，不重叠
    EXPECT_FALSE(s.checkOverlap(1, 10, 0, 1, -1, 3, 1));
}