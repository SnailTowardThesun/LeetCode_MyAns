//
// Created by 韩堃 on 2026/4/6.
//

/*
题目：657. Judge Route Circle

题目描述：
在二维平面上，有一个机器人从原点 (0, 0) 开始。给出它的移动顺序，判断这个机器人在完成移动后是否在 (0, 0) 处结束。
移动顺序由字符串表示。字符 move[i] 表示其第 i 次移动。机器人的有效动作有 R（右），L（左），U（上）和 D（下）。

示例：
输入: "UD"
输出: true
解释：机器人向上移动一次，然后向下移动一次。所有移动完成后，机器人回到了原点。

输入: "LL"
输出: false
解释：机器人向左移动两次。它最终位于原点的左侧，距原点有两单位距离，没有回到原点。

解题思路：
1. 问题可以简化为统计机器人在水平和垂直方向的移动次数
2. 向上和向下移动相互抵消，向左和向右移动相互抵消
3. 如果最终水平和垂直方向的移动次数都为0，则机器人回到原点
4. 使用一个数组或变量来统计各个方向的移动次数
5. 遍历移动字符串，统计每个方向的移动次数
6. 检查上下移动次数是否相等，左右移动次数是否相等

时间复杂度：O(n)，其中n是移动字符串的长度
空间复杂度：O(1)，只使用常数级别的额外空间
*/

#include <gtest/gtest.h>

#include <string>
using namespace std;

class Solution {
   public:
    bool judgeCircle(string moves) {
        int up = 0, down = 0, left = 0, right = 0;

        // 统计各个方向的移动次数
        for (char move : moves) {
            if (move == 'U') {
                up++;
            } else if (move == 'D') {
                down++;
            } else if (move == 'L') {
                left++;
            } else if (move == 'R') {
                right++;
            }
        }

        // 检查是否回到原点
        return up == down && left == right;
    }
};

TEST(Daily, 657) {
    // 测试用例1：上下移动各一次，回到原点
    string moves1 = "UD";
    Solution s;
    auto ret1 = s.judgeCircle(moves1);
    EXPECT_TRUE(ret1);

    // 测试用例2：左右移动各一次，回到原点
    string moves2 = "LR";
    auto ret2 = s.judgeCircle(moves2);
    EXPECT_TRUE(ret2);

    // 测试用例3：只向左移动，不回到原点
    string moves3 = "LL";
    auto ret3 = s.judgeCircle(moves3);
    EXPECT_FALSE(ret3);

    // 测试用例4：复杂移动序列，回到原点
    string moves4 = "UDLR";
    auto ret4 = s.judgeCircle(moves4);
    EXPECT_TRUE(ret4);

    // 测试用例5：空字符串，回到原点
    string moves5 = "";
    auto ret5 = s.judgeCircle(moves5);
    EXPECT_TRUE(ret5);
}
