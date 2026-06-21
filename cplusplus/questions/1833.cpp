// @题目描述：夏日炎炎，小男孩 Tony 想买一些雪糕消消暑。商店中新到 n 支雪糕，用数组 costs 表示雪糕的定价，其中 costs[i] 表示第 i 支雪糕的现金价格。Tony 一共有 coins 现金可以用于消费，他想要买尽可能多的雪糕。
// 给你价格数组 costs 和现金量 coins，请你计算并返回 Tony 用 coins 现金能够买到的雪糕的最大数量。注意：Tony 可以按任意顺序购买雪糕。
//
// @示例：
// 示例 1：
// 输入：costs = [1,3,2,4,1], coins = 7
// 输出：4
// 解释：Tony 可以买下标为 0、1、2、4 的雪糕，总价为 1 + 3 + 2 + 1 = 7
//
// 示例 2：
// 输入：costs = [10,6,8,7,7,8], coins = 5
// 输出：0
// 解释：Tony 没有足够的钱买任何一支雪糕
//
// 示例 3：
// 输入：costs = [1,6,3,1,2,5], coins = 20
// 输出：6
// 解释：Tony 可以买下所有的雪糕，总价为 1 + 6 + 3 + 1 + 2 + 5 = 18
//
// @解题思路：贪心算法。要购买尽可能多的雪糕，应该优先购买价格最便宜的雪糕。
// 步骤：
// 1. 将雪糕价格数组按升序排序
// 2. 依次累加价格，直到总和超过 coins
// 3. 返回累加的雪糕数量
//
// 复杂度分析：
// - 时间复杂度：O(n log n)，主要是排序的时间复杂度
// - 空间复杂度：O(log n)，排序所需的栈空间

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        sort(costs.begin(), costs.end());
        int count = 0;
        int total = 0;
        for (int cost : costs) {
            total += cost;
            if (total > coins) {
                return count;
            }
            count++;
        }
        return costs.size();
    }
};

TEST(Daily, 1833) {
    Solution s;
    vector<int> costs1{1, 3, 2, 4, 1};
    EXPECT_EQ(s.maxIceCream(costs1, 7), 4);

    vector<int> costs2{10, 6, 8, 7, 7, 8};
    EXPECT_EQ(s.maxIceCream(costs2, 5), 0);

    vector<int> costs3{1, 6, 3, 1, 2, 5};
    EXPECT_EQ(s.maxIceCream(costs3, 20), 6);

    vector<int> costs4{};
    EXPECT_EQ(s.maxIceCream(costs4, 10), 0);
}
