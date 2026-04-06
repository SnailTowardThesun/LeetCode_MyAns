/**
 * @file top150_no134_gas_station.cpp
 * @brief LeetCode 134. 加油站
 *
 * @题目描述
 * 在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
 * 你有一辆油箱容量无限的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。
 * 你从其中的一个加油站出发，开始时油箱为空。
 * 给定两个整数数组 gas 和 cost，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，
 * 否则返回 -1。如果存在解，则保证它是唯一的。
 *
 * @示例
 * 示例 1：
 * 输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
 * 输出: 3
 * 解释:
 * 从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
 * 开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
 * 开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
 * 开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
 * 开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
 * 开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
 * 因此，3 可为起始索引。
 *
 * 示例 2：
 * 输入: gas = [2,3,4], cost = [3,4,3]
 * 输出: -1
 * 解释:
 * 你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
 * 我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
 * 开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
 * 开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
 * 你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
 * 因此无论如何，你都不可能绕环路行驶一周。
 *
 * @解题思路
 * 1. 贪心法：
 *    - 如果总油量 < 总消耗，则一定无解，返回 -1
 *    - 维护当前剩余油量和起始位置
 *    - 遍历每个加油站：
 *      - 剩余油量 += gas[i] - cost[i]
 *      - 如果剩余油量 < 0，说明从当前起始位置到 i 都不能作为起点
 *      - 将起始位置设为 i+1，剩余油量清零
 *    - 最后返回起始位置
 *
 * 2. 数学证明：
 *    - 如果总油量 >= 总消耗，一定有解
 *    - 从某个位置出发，如果中途油量不足，则该区间内的所有位置都不能作为起点
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，只需要遍历数组一次
 * - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>
#include <vector>
#include <climits>

using namespace std;

TEST(TOP150, No134_CanCompleteCircuit) {
    class Solution {
    public:
        int can_complete_circuit(vector<int>& gas, vector<int>& cost) {
            auto min_gas = INT_MAX;
            auto min_idx = 0;
            auto left = 0;

            for (auto i = 0; i < gas.size(); i++) {
                left += gas[i] - cost[i];
                if (min_gas > left) {
                    min_gas = left;
                    min_idx = i;
                }
            }

            return left < 0 ? -1 : (min_idx + 1) % gas.size();
        }
    };

    Solution solution;
    std::vector<int> gas{1, 2, 3, 4, 5};
    std::vector<int> cost{3, 4, 5, 1, 2};
    auto ret = solution.can_complete_circuit(gas, cost);
    EXPECT_EQ(ret, 3);
}
