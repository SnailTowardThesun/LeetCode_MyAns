// 题目：2833. 离起点最远的距离
// 描述：给你一个字符串 moves，其中只包含字符 'L'、'R' 和 '_'。
//       字符串中的下划线 '_' 可以表示为 'L' 或 'R'。
//       计算从起点 (0, 0) 出发执行完所有移动后的最远欧几里得距离平方。
// 示例：
// 输入：moves = "L_RL__R"
// 输出：3
// 解释：将 '_' 全部视为 'R'，最远情况下路径为 "RRRLRR"，
//      最终位置为 (3, 0)，距离为 |3| = 3

#include <gtest/gtest.h>
#include <climits>

using namespace std;

class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        // 统计L、R和_的数量
        int ls = 0, rs = 0, ms = 0;
        for (auto i: moves) {
            switch (i) {
                case 'L': ls++;
                    break;
                case 'R': rs++;
                    break;
                default: ms++;
                    break;
            }
        }

        // 要达到最远距离，将所有_都转化为朝向多的方向
        return ls > rs ? ls + ms - rs : rs + ms - ls;
    }
};

TEST(Daily, 2833) {
    Solution s;
    // 测试用例1：基本示例
    auto moves1 = "L_RL__R";
    EXPECT_EQ(s.furthestDistanceFromOrigin(moves1), 3);

    // 测试用例2：全是_
    auto moves2 = "___";
    EXPECT_EQ(s.furthestDistanceFromOrigin(moves2), 3);

    // 测试用例3：L比R多
    auto moves3 = "LLLRRR";
    EXPECT_EQ(s.furthestDistanceFromOrigin(moves3), 0);

    // 测试用例4：全是L
    auto moves4 = "LLLL";
    EXPECT_EQ(s.furthestDistanceFromOrigin(moves4), 4);

    // 测试用例5：全是R
    auto moves5 = "RRRR";
    EXPECT_EQ(s.furthestDistanceFromOrigin(moves5), 4);
}
