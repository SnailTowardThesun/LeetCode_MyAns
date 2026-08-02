// @题目描述:
// LeetCode 877. 石子游戏（Stone Game）
// 亚历克斯和李用几堆石子在做游戏。偶数堆石子排成一行，每堆都有正整数颗石子。
// 两人轮流，亚历克斯先开始。每一回合，玩家可以从行的开始或结束处取走整堆石子。
// 当没有石子堆时游戏结束，石子总数最多的玩家获胜。返回 true 表示亚历克斯获胜。
// 题目保证：piles.length 为偶数，sum(piles) 为奇数。
//
// @示例:
// 示例：
// 输入：piles = [5, 3, 4, 5]
// 输出：true
// 解释：亚历克斯先手。可选 5（左），剩 [3, 4, 5]，李取 5，剩 [3, 4]，
//       亚历克斯取 4，剩 [3]，李取 3。亚历克斯 9 颗，李 8 颗，亚历克斯获胜。
//       （亚历克斯也可先取左 5，最终总能获胜。）
//
// @解题思路:
// 数学法 O(1)。利用题目约束「石子堆数为偶数」与「总和为奇数」可证先手必胜。
//
// 证明：
// 1. 设堆数为 n（偶数），按下标分为两组：
//    - A 组：偶数下标 piles[0], piles[2], ..., piles[n-2]
//    - B 组：奇数下标 piles[1], piles[3], ..., piles[n-1]
// 2. 先手亚历克斯可「强制」拿走某一组的全部石子：
//    - 若想拿 A 组：先取 piles[0]（偶数下标）。取后剩余两端 piles[1] 与 piles[n-1]
//      均为奇数下标（属 B 组），后手李被迫从 B 组取；李取完后又会暴露偶数下标，
//      亚历克斯继续取 A 组。如此交替，亚历克斯拿走全部 A 组。
//    - 若想拿 B 组：先取 piles[n-1]（奇数下标，因 n 为偶数故 n-1 为奇）。
//      取后剩余两端 piles[0] 与 piles[n-2] 均为偶数下标（属 A 组），李被迫取 A 组，
//      亚历克斯继续取 B 组。亚历克斯拿走全部 B 组。
// 3. 由于 sum(piles) 为奇数，sum(A) + sum(B) 为奇数，故 sum(A) ≠ sum(B)
//    （若相等则和为偶数，矛盾）。
// 4. 亚历克斯比较 sum(A) 与 sum(B)，选择较大的一组，必胜。
// 因此直接返回 true。
//
// 复杂度分析：
// - 时间复杂度：O(1)。
// - 空间复杂度：O(1)。
//
// 备注：本题也可用与 486 相同的 minimax 记忆化搜索 O(n^2) 求解，但本题特殊约束
//       下数学法可降至 O(1)。

#include <gtest/gtest.h>

#include <vector>

using namespace std;

class Solution {
   public:
    bool stoneGame(vector<int>& piles) { return true; }
};

TEST(Daily, 877) {
    Solution s;

    // 基本用例
    auto piles1 = vector<int>{5, 3, 4, 5};
    EXPECT_TRUE(s.stoneGame(piles1));

    // 边界用例
    auto piles2 = vector<int>{3, 7};  // 两堆，亚历克斯取较大值 7
    EXPECT_TRUE(s.stoneGame(piles2));
    auto piles3 = vector<int>{7, 3};  // 两堆，亚历克斯取较大值 7
    EXPECT_TRUE(s.stoneGame(piles3));
    auto piles4 = vector<int>{1, 2, 3, 4};  // 四堆，先手必胜
    EXPECT_TRUE(s.stoneGame(piles4));
    auto piles5 = vector<int>{4, 3, 2, 1};  // 四堆，先手必胜
    EXPECT_TRUE(s.stoneGame(piles5));
}
