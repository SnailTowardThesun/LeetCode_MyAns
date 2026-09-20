//
// Created by 韩堃 on 2026/9/21.
//
// @题目描述:
// LeetCode 3524. 求出数组的 X 值 I（Find X Value of Array I，第 446 场周赛）
// 给你一个由正整数组成的数组 nums 和一个正整数 k。
// 你可以执行一次操作：移除任意一对互不重叠的前缀和后缀（前缀、后缀都可以
// 为空），但移除后 nums 必须仍然非空。
// 数组的 x 值定义为：操作后剩余元素的乘积除以 k 余数为 x 的操作数量。
// 返回大小为 k 的数组 result，result[x] 即 x 值（0 <= x < k）。
//
// 关键转化：移除一个前缀和一个后缀后，剩余部分恰好是一个【非空连续子数组】；
// 反过来每个非空连续子数组都唯一对应一种操作（移除它前面的前缀和后面的后缀）。
// 因此 result[x] = 乘积模 k 等于 x 的非空子数组个数。
//
// @示例:
// 示例 1：
// 输入：nums = [1,2,3,4,5], k = 3
// 输出：[9,2,4]
// 示例 2：
// 输入：nums = [1,2,4,8,16,32], k = 4
// 输出：[18,1,2,0]
// 示例 3：
// 输入：nums = [1,1,2,1,1], k = 2
// 输出：[9,6]
//
// @解题思路:
// 按子数组【结尾位置】做动态规划。设 dp[r] 表示以当前遍历位置结尾、
// 乘积模 k 等于 r 的子数组个数。处理新元素 num（val = num % k）时：
// 1. 只含 num 的新单元素子数组：next[val] += 1；
// 2. 接在以上一位置结尾的子数组后面：
//    若原子数组乘积余数为 r，新余数为 (r * val) % k，
//    即 next[(r*val)%k] += dp[r]。
// 依据 (a*b) mod k = ((a mod k)*(b mod k)) mod k，全程只需维护余数。
// 每处理一个位置，把 next 的各余数计数累加进答案 ret（所有子数组按结尾
// 位置不重不漏地归类）。
// 注意：
// - 不能用「前缀积 + 除法」枚举子数组：模 k 下乘法逆元不一定存在
//   （k 不是质数或余数与 k 不互质），所以 DP 是正解；
// - 计数最大为 n(n+1)/2（n 可达 1e5，约 5e9），必须用 long long；
// - 余数乘法用 1LL 提升，防御整数溢出。
//
// 复杂度分析：
// - 时间复杂度：O(n*k)，k <= 5，实际接近 O(n)。
// - 空间复杂度：O(k)。

#include <gtest/gtest.h>

#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    vector<long long> resultArray(vector<int> &nums, int k) {
        // ret[r]：所有位置上，乘积模 k 余 r 的子数组个数之和
        vector<long long> ret(k, 0);

        // dp[r]：以上一位置结尾、乘积模 k 余 r 的子数组个数
        vector<long long> dp(k, 0);
        for (auto num : nums) {
            int val = num % k;
            vector<long long> next_dp(k, 0);
            // 以当前元素单独构成一个新子数组
            next_dp[val] += 1;

            // 把当前元素接到上一位置结尾的每个子数组后面
            for (int r = 0; r < k; r++) {
                if (dp[r] > 0) {
                    int next_val = (1LL * val * r ) % k;
                    next_dp[next_val] += dp[r];
                }
            }

            // 以当前位置结尾的子数组计入总答案
            for (int r = 0; r < k; r++) {
                ret[r] += next_dp[r];
            }

            dp = std::move(next_dp);
        }

        return ret;
    }
};

TEST(Daily, 3524) {
    Solution s;
    vector<int> nums{1, 2, 3, 4, 5};
    int k = 3;
    auto ret = s.resultArray(nums, k);
    EXPECT_EQ(vector<long long>({9,2,4}), ret);

    // 示例 2：共 21 个非空子数组，按余数分类为 [18,1,2,0]
    vector<int> nums2{1, 2, 4, 8, 16, 32};
    EXPECT_EQ(vector<long long>({18, 1, 2, 0}), s.resultArray(nums2, 4));

    // 示例 3
    vector<int> nums3{1, 1, 2, 1, 1};
    EXPECT_EQ(vector<long long>({9, 6}), s.resultArray(nums3, 2));

    // 边界用例：k = 1，所有子数组乘积模 1 都余 0，共 n(n+1)/2 = 6 个
    vector<int> nums4{7, 8, 9};
    EXPECT_EQ(vector<long long>({6}), s.resultArray(nums4, 1));
}
