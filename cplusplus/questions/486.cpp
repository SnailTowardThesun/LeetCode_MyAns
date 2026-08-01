// @题目描述:
// 给你一个整数数组 nums。玩家 1 和玩家 2 基于数组中的数字轮流转弯取数，
// 每次只能从数组的任意一端（左端或右端）取一个数字。
// 玩家 1 先手，两人都采用最优策略。当所有数字被取完后，得分高者获胜。
// 如果得分相等，视为玩家 1 获胜。返回 true 表示玩家 1 能获胜，否则返回 false。
//
// @示例:
// 示例 1：
// 输入：nums = [1, 5, 2]
// 输出：false
// 解释：玩家 1 先手。若取 1，玩家 2 可取 5（剩 [5,2] 取 5），玩家 1 取 2，
//       得分 3 < 7；若取 2，玩家 2 取 5，玩家 1 取 1，得分 3 < 7。玩家 1 必败。
//
// 示例 2：
// 输入：nums = [1, 5, 233, 7]
// 输出：true
// 解释：玩家 1 先取 1，剩 [5, 233, 7]。无论玩家 2 取 5 还是 7，
//       玩家 1 都能取到 233，最终得分 234，玩家 2 得分 12，玩家 1 获胜。
//
// @解题思路:
// 记忆化搜索（Minimax 思路）。定义 dfs(l, r) 为当前玩家在子数组 nums[l..r] 上
// 能取得的最大「分数差」（当前玩家得分 − 对手得分）。
// 1. 边界：l == r 时，只剩一个数，当前玩家取走，分差为 nums[l]。
// 2. 转移：当前玩家有两种选择：
//    - 取左端 nums[l]：对手在 [l+1, r] 上作为先手获得 dfs(l+1, r) 的分差，
//      所以当前玩家的净分差为 nums[l] - dfs(l+1, r)。
//    - 取右端 nums[r]：同理净分差为 nums[r] - dfs(l, r-1)。
//    - 两者取较大值：dfs(l, r) = max(nums[l] - dfs(l+1, r), nums[r] - dfs(l, r-1))。
// 3. 玩家 1 作为全局先手，能获胜当且仅当 dfs(0, n-1) >= 0。
// 注意：递推式中用「减号」而非「加号」，因为对手的分差要从当前玩家得分中扣除。
//
// 复杂度分析：
// - 时间复杂度：O(n^2)，共有 n(n+1)/2 个子问题，每个 O(1) 转移。
// - 空间复杂度：O(n^2)，记忆化数组大小为 n×n。

#include <gtest/gtest.h>

#include <vector>

using namespace std;

class Solution {
   public:
    int dfs(vector<int>& nums, int l, int r, vector<vector<int>>& memory) {
        auto& ret = memory[l][r];

        if (ret != -1) {
            return ret;
        }

        if (l == r) {
            ret = nums[l];
            return ret;
        }
        ret = max(nums[l] - dfs(nums, l + 1, r, memory), nums[r] - dfs(nums, l, r - 1, memory));
        return ret;
    }

    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> memory(n, vector<int>(n, -1));

        return dfs(nums, 0, n - 1, memory) >= 0;
    }
};

TEST(Daily, 486) {
    Solution s;

    // 基本用例
    auto nums1 = vector<int>{1, 5, 2};
    EXPECT_FALSE(s.predictTheWinner(nums1));
    auto nums2 = vector<int>{1, 5, 233, 7};
    EXPECT_TRUE(s.predictTheWinner(nums2));

    // 边界用例
    auto nums3 = vector<int>{0};
    EXPECT_TRUE(s.predictTheWinner(nums3));  // 单元素
    auto nums4 = vector<int>{1, 1};
    EXPECT_TRUE(s.predictTheWinner(nums4));  // 平局，玩家 1 获胜
    auto nums5 = vector<int>{1, 2};
    EXPECT_TRUE(s.predictTheWinner(nums5));  // 两元素，玩家 1 取较大值 2
    auto nums6 = vector<int>{2, 1};
    EXPECT_TRUE(s.predictTheWinner(nums6));  // 玩家 1 取较大值 2
}
