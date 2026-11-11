// @题目描述:
// 给你五个整数 cost1、cost2、costBoth、need1 和 need2。有三种类型的物品可以购买：
// - 类型 1 的物品花费 cost1，仅满足类型 1 的需求 1 个单位；
// - 类型 2 的物品花费 cost2，仅满足类型 2 的需求 1 个单位；
// - 类型 3 的物品花费 costBoth，同时满足类型 1 和类型 2 的需求各 1 个单位。
// 购买足够的物品使类型 1 的总需求至少为 need1、类型 2 的总需求至少为 need2，
// 返回满足需求的最小可能总花费。
//
// @示例:
// 输入：cost1 = 3, cost2 = 2, costBoth = 1, need1 = 3, need2 = 2
// 输出：3
// 解释：买 3 个类型 3 物品（3 * 1 = 3），类型 1 满足 3 >= 3，类型 2 满足 3 >= 2。
// 输入：cost1 = 5, cost2 = 4, costBoth = 15, need1 = 2, need2 = 3
// 输出：22（捆绑太贵，分开买 2*5 + 3*4 = 22）
// 输入：cost1 = 5, cost2 = 4, costBoth = 15, need1 = 0, need2 = 0
// 输出：0（无需购买）
//
// @解题思路:
// O(1) 贪心（本质是关于捆绑数量的线性目标函数，最优解落在端点）：
// 1. 需求为零直接返回 0；
// 2. 若 cost1 + cost2 <= costBoth（捆绑不便宜），全部单买：
//    need1*cost1 + need2*cost2；
// 3. 否则捆绑划算。设「多的一侧」为 large（需求 large_n、单价 large_c），
//    「少的一侧」为 small（需求 small_n）：
//    - 小侧的 small_n 个需求单位全部与 large 配成捆绑对，每对花 costBoth
//      （比 cost1 + cost2 便宜），共 small_n * costBoth；
//    - 剩余 (large_n - small_n) 个 large 单位，每单位取 min(large_c, costBoth)——
//      若捆绑价低于大侧单价，宁可多买捆绑浪费掉小侧覆盖也更便宜（示例 1 正是如此）；
// 4. 购买方案可写作 x 个捆绑 + y 个类型 1 + z 个类型 2，总花费是 x 的线性函数，
//    最优 x 必取 0 或 min(need1, need2) 或 max(need1, need2) 端点，上述贪心恰好
//    覆盖这些端点，故为全局最优。
//
// 复杂度分析：
// - 时间复杂度：O(1)
// - 空间复杂度：O(1)
// 数值安全：need 上限 1e9、单价上限 1e6，总额上限 1e15 > INT_MAX，必须用 long long

#include <gtest/gtest.h>

#include <algorithm>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        if (need1 == 0 && need2 == 0) {
            return 0;
        }

        // 捆绑不比分开买便宜：全部单买
        if ((cost1 + cost2) <= costBoth) {
            return 1LL * need1 * cost1 + 1LL * need2 * cost2;
        }

        // 捆绑划算：区分需求多/少的一侧（需求相等时任取一侧为 large；
        // 小侧单价用不到——其需求全部由捆绑覆盖）
        long long large_c = cost1;
        long long large_n = need1;
        long long small_n = need2;

        if (need1 < need2) {
            large_c = cost2;
            large_n = need2;
            small_n = need1;
        }

        // 少的一侧全部配成捆绑对，每对花 costBoth（比 cost1 + cost2 便宜）
        long long scope_score = small_n * costBoth;

        // 多的一侧剩余单位：单买 large_c，或继续买捆绑（浪费小侧覆盖）取便宜者
        long long diff_score = min((large_n - small_n) * large_c, (large_n - small_n) * costBoth);

        return scope_score + diff_score;
    }
};
}  // namespace

TEST(Daily, 3789) {
    Solution s;

    // 官方示例 1：捆绑价 1 低于任何单价，剩余的 large 单位也用捆绑覆盖更便宜
    EXPECT_EQ(s.minimumCost(3, 2, 1, 3, 2), 3);

    // 官方示例 2：捆绑太贵，全部分开买
    EXPECT_EQ(s.minimumCost(5, 4, 15, 2, 3), 22);

    // 官方示例 3：需求为零
    EXPECT_EQ(s.minimumCost(5, 4, 15, 0, 0), 0);

    // 单侧为零：只剩另一侧，每单位取 min(大侧单价, 捆绑价)
    EXPECT_EQ(s.minimumCost(100, 50, 1, 0, 3), 3);     // 捆绑价 1 < cost2，用捆绑覆盖
    EXPECT_EQ(s.minimumCost(100, 50, 60, 7, 0), 420);  // 大侧单价 100 > 捆绑价 60，用捆绑
    EXPECT_EQ(s.minimumCost(50, 100, 60, 7, 0), 350);  // 大侧单价 50 < 捆绑价 60，单买

    // 需求相等：无剩余差额，全部配对捆绑
    EXPECT_EQ(s.minimumCost(4, 4, 6, 5, 5), 30);

    // 对称性：need2 > need1 时大侧是类型 2
    EXPECT_EQ(s.minimumCost(2, 10, 3, 1, 4), 12);  // 1 对捆绑(3) + 3 * min(10,3) = 12

    // 溢出边界：1e9 需求 * 1e6 单价 = 1e15，必须 long long
    EXPECT_EQ(s.minimumCost(1000000, 1000000, 1000000, 1000000000, 1000000000), 1000000000000000LL);
}
