//
// Created by 韩堃 on 2026/4/1.
//

/**
 * @file 2751.cpp
 * @brief LeetCode 2751. 机器人碰撞 (Robot Collisions)
 *
 * @题目描述
 * 现有 n 个机器人，编号从 1 开始，每个机器人包含在路线上的位置、健康度和移动方向。
 *
 * 给定三个数组：
 * - positions: 机器人在数轴上的位置（所有位置互不相同）
 * - healths:   机器人的健康值
 * - directions: 机器人的移动方向，'L' 表示向左，'R' 表示向右
 *
 * 所有机器人以相同速度同时沿指定方向移动。
 * 如果两个机器人在移动过程中占据相同位置，它们会发生碰撞。
 *
 * @碰撞规则
 * 1. 健康值较低的机器人被移除，健康值较高的机器人健康值减 1，继续沿原方向移动
 * 2. 如果两个机器人健康值相同，则两者都被移除
 *
 * @任务
 * 返回所有存活机器人的健康值，按原始输入顺序排列。
 * 如果没有幸存者，返回空数组。
 *
 * @示例 1
 * 输入: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions = "RRRRR"
 * 输出: [2,17,9,15,10]
 * 解释: 所有机器人都向右移动，不会发生碰撞。
 *
 * @示例 2
 * 输入: positions = [3,5,2,6], healths = [10,10,15,12], directions = "RLRL"
 * 输出: [14]
 * 解释:
 * - 机器人1(位置3,R)和机器人2(位置5,L)会碰撞，两者健康值相同(10)，都被移除
 * - 机器人3(位置2,R)和机器人4(位置6,L)会碰撞，机器人4健康值较低(12<15)，被移除
 *   机器人3健康值变为 15-1=14
 * - 最终只有机器人3存活，返回 [14]
 *
 * @示例 3
 * 输入: positions = [1,2,5,6], healths = [10,10,11,11], directions = "RLRL"
 * 输出: []
 * 解释: 两对机器人分别碰撞，健康值都相同，全部被移除。
 *
 * @约束条件
 * - 1 <= n <= 10^5
 * - 1 <= positions[i], healths[i] <= 10^9
 * - directions[i] 为 'L' 或 'R'
 * - positions 中的所有值互不相同
 *
 * @解题思路
 * 本题使用栈来模拟碰撞过程，核心思想如下：
 *
 * 1. 预处理：按位置排序
 *    - 由于机器人位置无序，首先创建一个索引数组 idx = [0, 1, ..., n-1]
 *    - 按 positions 值对 idx 进行排序，得到从左到右的机器人顺序
 *
 * 2. 栈模拟碰撞：
 *    - 遍历按位置排序后的机器人
 *    - 对于向右移动的机器人('R')，直接压入栈中
 *    - 对于向左移动的机器人('L')，它会与栈顶向右移动的机器人发生碰撞
 *
 * 3. 碰撞处理（当前机器人向左移动时）：
 *    - 当栈不为空且当前机器人健康值 > 0 时，持续碰撞
 *    - 比较当前机器人与栈顶机器人的健康值：
 *      a) 栈顶健康值 > 当前健康值：当前机器人被移除(health=0)，栈顶健康值-1
 *      b) 栈顶健康值 < 当前健康值：栈顶机器人被移除(出栈)，当前健康值-1，继续与新的栈顶碰撞
 *      c) 两者相等：都被移除(当前health=0，栈顶出栈)，停止碰撞
 *
 * 4. 结果收集：
 *    - 遍历 healths 数组，收集所有 health > 0 的值
 *    - 这些值按原始输入顺序排列，符合题目要求
 *
 * @复杂度分析
 * - 时间复杂度: O(n log n)，主要来自排序操作
 * - 空间复杂度: O(n)，用于存储索引数组和栈
 *
 * @关键点
 * - 只有"向右移动的机器人"会被压入栈中
 * - "向左移动的机器人"会触发碰撞检查
 * - 碰撞可能连续发生（当前机器人击败多个栈中机器人）
 * - 最终结果是按原始编号顺序，而非位置顺序
 */

#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        // 创建索引数组 [0, 1, ..., n-1]
        vector<int> idx(n);
        // iota: 用递增序列填充数组，idx 变为 [0, 1, 2, ..., n-1]
        iota(idx.begin(), idx.end(), 0);
        // 按位置排序索引，得到从左到右的机器人顺序
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return positions[a] < positions[b];
        });

        // 栈用于存储向右移动的机器人索引
        // 栈中机器人按位置从左到右排列（栈底到栈顶）
        vector<int> stk;

        // 按位置顺序遍历所有机器人
        for (int i : idx) {
            if (directions[i] == 'R') {
                // 向右移动的机器人：直接入栈，等待后续向左移动的机器人来碰撞
                stk.push_back(i);
                continue;
            }

            // 向左移动的机器人：需要与栈中向右移动的机器人碰撞
            // 碰撞条件：栈不为空 且 当前机器人仍然存活(health > 0)
            while (!stk.empty() && healths[i] > 0) {
                int j = stk.back();  // 栈顶机器人（最靠近当前机器人的向右移动机器人）

                if (healths[j] > healths[i]) {
                    // 情况1：栈顶机器人更强
                    // 当前机器人被摧毁
                    healths[i] = 0;
                    // 栈顶机器人健康值减1，但继续留在栈中
                    healths[j]--;
                } else if (healths[j] < healths[i]) {
                    // 情况2：当前机器人更强
                    // 栈顶机器人被摧毁（出栈）
                    stk.pop_back();
                    healths[j] = 0;
                    // 当前机器人健康值减1，但继续存活，可能与新的栈顶碰撞
                    healths[i]--;
                } else {
                    // 情况3：两者健康值相等
                    // 两者都被摧毁
                    healths[i] = 0;
                    healths[j] = 0;
                    stk.pop_back();  // 栈顶出栈
                    break;  // 当前机器人也被移除，停止碰撞
                }
            }
        }

        // 收集结果：所有健康值大于0的机器人
        // 由于我们遍历原始 healths 数组，结果自然按原始输入顺序排列
        vector<int> ans;
        for (int h : healths) {
            if (h > 0) {
                ans.push_back(h);
            }
        }
        return ans;
    }
};

TEST(Daily, 2751) {
    Solution s;

    // 示例2：存在碰撞的情况
    vector<int> positions{3, 5, 2, 6};
    vector<int> healths{10, 10, 15, 12};
    string directions{"RLRL"};

    auto ret = s.survivedRobotsHealths(positions, healths, directions);
    vector<int> expected{14};
    EXPECT_EQ(expected, ret);
}
