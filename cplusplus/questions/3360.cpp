// @题目描述
// 给定 1 到 50 颗石头，Alice 和 Bob 轮流取石。Alice 先取 10 颗，之后每手必须比上一手少取 1 颗。
// 无法取够的玩家输，返回 Alice 是否获胜。
//
// @示例
// n = 12 时，Alice 取 10 颗后剩 2 颗，Bob 无法取 9 颗，返回 true。
// n = 1 时，Alice 无法完成第一手，返回 false。
//
// @解题思路
// 按 10、9、8……的顺序扣除石头，直到剩余石头不足。若已完成奇数手，下一个失败的是 Bob。
// 前八手共需 52 颗，题目最多给 50 颗，因此至多成功取七次。时间和额外空间均为 O(1)。

#include <gtest/gtest.h>

namespace {
class Solution {
   public:
    bool canAliceWin(int n) {
        int take = 10;
        int moves = 0;
        while (take > 0 && n >= take) {
            n -= take;
            --take;
            ++moves;
        }
        return moves % 2 == 1;
    }
};
}  // namespace

TEST(Daily, 3360) {
    Solution solution;
    for (int n = 1; n <= 50; ++n) {
        const bool expected = (10 <= n && n < 19) || (27 <= n && n < 34) || (40 <= n && n < 45) || (49 <= n && n <= 50);
        EXPECT_EQ(solution.canAliceWin(n), expected) << "n = " << n;
    }
}
