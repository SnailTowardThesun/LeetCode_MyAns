//
// Created by hankun on 2026/10/10.
//

// @题目描述:
// 给定两个长度为 n 的正整数数组 nums1 和 nums2（下标从 0 开始）。
// 可以对 nums1 执行两类操作任意次（可以为 0 次）：
//   - 类型 1：任选下标 i，令 nums1[i] 加 1，最多共执行 k1 次；
//   - 类型 2：任选下标 i，令 nums1[i] 减 1，最多共执行 k2 次。
// 返回执行操作后 Σ(nums1[i] - nums2[i])^2 的最小值。
// 题目保证答案不超过 2^53 - 1。
// 数据范围：1 <= n <= 10^5，1 <= nums1[i], nums2[i] <= 10^5，0 <= k1, k2 <= 10^9。
//
// @示例:
// 输入：nums1 = [1,4,10,12], nums2 = [5,8,6,9], k1 = 1, k2 = 1
// 输出：43
// 解释：差值绝对值为 [4,4,4,3]，用 2 次操作把两个 4 降为 3，
//       得 [3,3,4,3]，平方和 = 9 + 9 + 16 + 9 = 43。
//
// @解题思路:
// 1. 每个位置的修改只影响该位置自身的差值，因此把总步数 step = k1 + k2
//    视作整体预算，每次操作让某个 |nums1[i] - nums2[i]| 减 1 最划算；
// 2. 用桶数组 arr[d] 统计「差值绝对值为 d」的位置个数（d 上限 1e5）；
// 3. 从大到小遍历 d，把高桶中的计数尽可能搬到低一档（每次搬运消耗 1 步/个），
//    等价于不断削平最大的差值，即贪心 + 桶排序；
// 4. 最后 Σ d^2 * arr[d] 即为答案。
//
// 复杂度分析：
// - 时间复杂度：O(n + M)，M 为差值上界 1e5；
// - 空间复杂度：O(M)。

#include <gtest/gtest.h>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long ret = 0;
        vector<long long> arr(1e5 + 1, 0);

        for (auto i = 0; i < n; i++) {
            arr[abs(nums1[i] - nums2[i])]++;
        }

        int step = k1 + k2;
        for (int i = arr.size() - 1; i > 0 && step > 0; i--) {
            int change = step < arr[i] ? step : arr[i];
            step -= change;
            arr[i - 1] += change;
            arr[i] -= change;
        }

        for (auto i = 0; i < arr.size(); i++) {
            ret += i * i * arr[i];
        }

        return ret;
    }
};
}  // namespace

TEST(Daily, 2333) {
    Solution s;
    vector<int> nums1{7, 11, 4, 19, 11, 5, 6, 1, 8};
    vector<int> nums2{4, 7, 6, 16, 12, 9, 10, 2, 10};
    auto k1 = 3, k2 = 6;
    auto ret = s.minSumSquareDiff(nums1, nums2, k1, k2);
    EXPECT_EQ(ret, 27);
}
