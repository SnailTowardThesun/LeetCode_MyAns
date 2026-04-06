//
// Created by 韩堃 on 2026/4/6.
//

/*
题目：874. Walking Robot Simulation

题目描述：
机器人在一个无限大小的网格上行走，从点 (0, 0) 处开始出发，面向北方。该机器人可以接收以下三种类型的命令：
- -2：向左转 90 度
- -1：向右转 90 度
- 1 <= x <= 9：向前移动 x 个单位长度

机器人在行走过程中始终不会离开网格。网格上有一些障碍物，它们的位置由障碍物数组给出。
如果机器人试图走到障碍物上方，那么它将停留在障碍物前面的最后一个有效位置，并且不再继续移动。

返回从原点到机器人所有经过的路径点（包括起点）的最大欧式距离的平方。

示例：
输入: commands = [4, -1, 3], obstacles = []
输出: 25
解释: 机器人将移动 4 个单位向北，然后右转，再移动 3 个单位向东。
此时机器人的位置是 (3, 4)，距离原点的距离是 5，所以返回 25。

输入: commands = [6, -1, -1, 6], obstacles = [[0,0]]
输出: 25
解释: 机器人被障碍物阻挡，最终停在 (6, 0)，距离原点的距离是 6，所以返回 36？
（注：原测试用例可能存在错误，正确的返回值应该是 36）

解题思路（当前实现）：
1. 使用pair<int, int>表示机器人的位置和方向
2. 定义change_position函数来处理方向的改变
3. 使用map存储障碍物的位置，方便查找
4. 模拟机器人的移动过程，每次移动一步
5. 计算并记录最大距离的平方

时间复杂度：O(n*m)，其中n是命令数量，m是每次移动的最大步数
空间复杂度：O(k)，其中k是障碍物数量

优化方案：
1. 使用更高效的数据结构存储障碍物，如unordered_set
2. 使用方向数组来简化方向处理
3. 优化坐标存储方式，将二维坐标转换为一维键
4. 减少不必要的计算

优化后的时间复杂度：O(n*m)，但常数项更小
优化后的空间复杂度：O(k)
*/

#include <gtest/gtest.h>

#include <map>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
   public:
    // 改变方向的函数
    // target: 当前方向向量 (-2: 左转, -1: 右转)
    pair<int, int> change_position(pair<int, int> target, int direction) {
        // 北 (0, 1)
        if (target.first == 0 && target.second == 1) {
            if (direction == -1) {  // 右转 -> 东
                return pair<int, int>{1, 0};
            }
            if (direction == -2) {  // 左转 -> 西
                return pair<int, int>{-1, 0};
            }
        };

        // 东 (1, 0)
        if (target.first == 1 && target.second == 0) {
            if (direction == -1) {  // 右转 -> 南
                return pair<int, int>{0, -1};
            }
            if (direction == -2) {  // 左转 -> 北
                return pair<int, int>{0, 1};
            }
        }

        // 南 (0, -1)
        if (target.first == 0 && target.second == -1) {
            if (direction == -1) {  // 右转 -> 西
                return pair<int, int>{-1, 0};
            }
            if (direction == -2) {  // 左转 -> 东
                return pair<int, int>{1, 0};
            }
        }

        // 西 (-1, 0)
        if (target.first == -1 && target.second == 0) {
            if (direction == -1) {  // 右转 -> 北
                return pair<int, int>(0, 1);
            }
            if (direction == -2) {  // 左转 -> 南
                return pair<int, int>(0, -1);
            }
        }

        return target;  // 默认返回原方向
    }

    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int max_distance = 0;
        // 使用map存储障碍物位置
        std::map<std::pair<int, int>, int> blocks;
        for (auto i : obstacles) {
            blocks[pair<int, int>{i[0], i[1]}] = 1;
        }

        pair<int, int> position{0, 0};   // 初始位置
        pair<int, int> direction{0, 1};  // 初始方向：北

        for (auto cmd : commands) {
            if (cmd == -1 || cmd == -2) {
                // 改变方向
                direction = change_position(direction, cmd);
                continue;
            }

            // 向前移动cmd步
            for (int j = 0; j < cmd; j++) {
                int new_x = position.first + direction.first;
                int new_y = position.second + direction.second;

                // 检查是否遇到障碍物
                if (blocks.find(pair<int, int>{new_x, new_y}) == blocks.end()) {
                    position.first = new_x;
                    position.second = new_y;

                    // 更新最大距离
                    int distance = position.first * position.first + position.second * position.second;
                    max_distance = max(max_distance, distance);
                } else {
                    // 遇到障碍物，停止移动
                    break;
                }
            }
        }

        // 原实现返回的是最终位置的距离，应该返回最大距离
        return max_distance;
    }
};

// 优化版本
class SolutionOptimse {
   public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int max_distance = 0;

        // 方向数组：北、东、南、西
        // 顺序是顺时针，方便处理转向
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int dir_idx = 0;  // 初始方向：北

        // 使用unordered_set存储障碍物，提高查找效率
        // 将二维坐标转换为字符串作为键
        unordered_set<string> obstacle_set;
        for (auto& obs : obstacles) {
            obstacle_set.insert(to_string(obs[0]) + "," + to_string(obs[1]));
        }

        int x = 0, y = 0;  // 初始位置

        for (int cmd : commands) {
            if (cmd == -1) {
                // 向右转90度
                dir_idx = (dir_idx + 1) % 4;
            } else if (cmd == -2) {
                // 向左转90度
                dir_idx = (dir_idx + 3) % 4;  // 等价于减1，避免负数
            } else {
                // 向前移动cmd步
                auto& dir = directions[dir_idx];
                for (int i = 0; i < cmd; i++) {
                    int new_x = x + dir.first;
                    int new_y = y + dir.second;

                    // 检查是否遇到障碍物
                    string key = to_string(new_x) + "," + to_string(new_y);
                    if (obstacle_set.find(key) == obstacle_set.end()) {
                        x = new_x;
                        y = new_y;

                        // 更新最大距离
                        int distance = x * x + y * y;
                        max_distance = max(max_distance, distance);
                    } else {
                        // 遇到障碍物，停止移动
                        break;
                    }
                }
            }
        }

        return max_distance;
    }
};

TEST(Daily, 874) {
    // 测试用例1：基本移动
    vector<int> commands1 = {4, -1, 3};
    vector<vector<int>> obstacles1 = {};
    Solution s1;
    int ret1 = s1.robotSim(commands1, obstacles1);
    EXPECT_EQ(ret1, 25);

    // 测试用例2：遇到障碍物
    vector<int> commands2 = {6, -1, -1, 6};
    vector<vector<int>> obstacles2 = {{0, 0}};
    Solution s2;
    int ret2 = s2.robotSim(commands2, obstacles2);
    EXPECT_EQ(ret2, 36);  // 正确值应该是36，而不是25

    // 测试优化版本
    SolutionOptimse so1;
    int ret_optimse1 = so1.robotSim(commands1, obstacles1);
    EXPECT_EQ(ret_optimse1, 25);

    SolutionOptimse so2;
    int ret_optimse2 = so2.robotSim(commands2, obstacles2);
    EXPECT_EQ(ret_optimse2, 36);
}
