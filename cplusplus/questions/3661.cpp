//
// Created by 韩堃 on 2026/4/3.
//

/*
题目：3661. 可以被机器人摧毁的最大墙壁数目

题目描述：
一条无限长的直线上分布着一些机器人和墙壁。给你整数数组 robots，distance 和 walls：
- robots[i] 是第 i 个机器人的位置
- distance[i] 是第 i 个机器人的射程
- walls[j] 是第 j 个墙壁的位置

每个机器人有一颗子弹，可以向左或向右发射，最远距离为 distance[i] 米。
子弹会摧毁其射程内路径上的每一堵墙。
机器人是固定的障碍物：如果子弹在到达墙壁前击中另一个机器人，它会立即在该机器人处停止，无法继续前进。
返回机器人可以摧毁墙壁的最大数量。

注意：墙壁和机器人的位置都是唯一的。

解题思路：
1. 首先对机器人和墙壁的位置进行排序，方便后续计算
2. 对于每个机器人，计算其向左和向右可以到达的最远位置（考虑其他机器人的阻挡）
3. 对于每个方向，计算该方向上可以摧毁的墙壁数量
4. 选择每个机器人的最优方向，使得总摧毁墙壁数量最大

具体步骤：
1. 将机器人按位置排序
2. 将墙壁排序并去重（虽然题目说位置唯一，但为了保险起见）
3. 对每个机器人，计算其向左的最远位置：
   - 初始最远位置为 robots[i] - distance[i]
   - 找到左边最近的机器人，取其位置和初始最远位置的最大值
4. 计算其向右的最远位置：
   - 初始最远位置为 robots[i] + distance[i]
   - 找到右边最近的机器人，取其位置和初始最远位置的最小值
5. 对于每个方向，使用二分查找计算该范围内的墙壁数量
6. 选择每个机器人的最优方向，累加到总结果中
*/

#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

struct Item {
    int position;
    int distance;
};

class Solution {
   public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = robots.size();
        vector<Item> container_robots;
        for (int i = 0; i < n; ++i) {
            container_robots.push_back({robots[i], distance[i]});
        }

        // 对机器人按位置排序
        sort(container_robots.begin(), container_robots.end(),
             [](const Item& a, const Item& b) { return a.position < b.position; });

        // 对墙壁排序并去重
        sort(walls.begin(), walls.end());
        walls.erase(unique(walls.begin(), walls.end()), walls.end());

        // 记录哪些墙壁已经被摧毁
        unordered_map<int, bool> destroyed;
        for (int wall : walls) {
            destroyed[wall] = false;
        }

        // 为每个机器人计算向左和向右可以摧毁的墙壁
        vector<vector<int>> left_walls(n);
        vector<vector<int>> right_walls(n);

        for (int i = 0; i < n; ++i) {
            int pos = container_robots[i].position;
            int dist = container_robots[i].distance;

            // 计算向左的最远位置
            int left_start = pos - dist;
            if (i > 0) {
                left_start = max(left_start, container_robots[i - 1].position + 1);
            }

            // 计算向右的最远位置
            int right_end = pos + dist;
            if (i < n - 1) {
                right_end = min(right_end, container_robots[i + 1].position - 1);
            }

            // 收集向左可以摧毁的墙壁
            if (left_start <= pos) {
                auto left_it = lower_bound(walls.begin(), walls.end(), left_start);
                auto right_it = upper_bound(walls.begin(), walls.end(), pos);
                for (auto it = left_it; it != right_it; ++it) {
                    left_walls[i].push_back(*it);
                }
            }

            // 收集向右可以摧毁的墙壁
            if (pos <= right_end) {
                auto left_it = lower_bound(walls.begin(), walls.end(), pos);
                auto right_it = upper_bound(walls.begin(), walls.end(), right_end);
                for (auto it = left_it; it != right_it; ++it) {
                    right_walls[i].push_back(*it);
                }
            }
        }

        // 选择每个机器人的最优方向，优先选择摧毁更多未被摧毁的墙壁的方向
        int total = 0;
        for (int i = 0; i < n; ++i) {
            // 计算向左可以摧毁的未被摧毁的墙壁数量
            int left_count = 0;
            for (int wall : left_walls[i]) {
                if (!destroyed[wall]) {
                    left_count++;
                }
            }

            // 计算向右可以摧毁的未被摧毁的墙壁数量
            int right_count = 0;
            for (int wall : right_walls[i]) {
                if (!destroyed[wall]) {
                    right_count++;
                }
            }

            // 选择摧毁墙壁数量多的方向
            if (left_count > right_count) {
                for (int wall : left_walls[i]) {
                    if (!destroyed[wall]) {
                        destroyed[wall] = true;
                        total++;
                    }
                }
            } else {
                for (int wall : right_walls[i]) {
                    if (!destroyed[wall]) {
                        destroyed[wall] = true;
                        total++;
                    }
                }
            }
        }

        return total;
    }
};

TEST(Daily, 3661) {
    Solution s;
    vector<int> robots{63, 56, 40, 45, 4,  9,  44, 69, 55, 26, 73, 15, 12, 60, 43, 39, 37, 74, 36,
                       34, 13, 23, 66, 14, 11, 42, 72, 3,  57, 10, 53, 8,  70, 17, 58, 61, 30, 32};
    vector<int> distance{8, 7, 4, 8, 9, 5, 2, 4, 5, 2, 6, 9, 5, 9, 5, 3, 7, 6, 9,
                         2, 8, 7, 4, 3, 5, 1, 7, 5, 1, 3, 5, 3, 5, 4, 8, 7, 6, 4};
    vector<int> walls{6, 22, 50, 52, 20, 9, 23, 75, 26, 21, 60, 58, 41, 28, 30};
    auto ret = s.maxWalls(robots, distance, walls);
    EXPECT_EQ(15, ret);
}

TEST(Daily, 3661_2) {
    Solution s;
    vector<int> robots{10, 2};
    vector<int> distance{5, 1};
    vector<int> walls{5, 2, 7};
    auto ret = s.maxWalls(robots, distance, walls);
    EXPECT_EQ(3, ret);
}
