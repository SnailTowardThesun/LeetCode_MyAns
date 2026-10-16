// @题目描述:
// 给你一个下标从 0 开始的整数数组 nums。
// 定义子数组 nums[i..j] 的不同计数为其中不同值的数目，
// 请返回 nums 中所有子数组的不同计数的平方和。
// 由于答案可能很大，返回其对 10^9 + 7 取模的结果。
// 数据范围：1 <= nums.length <= 10^5，1 <= nums[i] <= 10^5。
//
// @示例:
// 输入: nums = [1,2,1]
// 输出: 15
// 解释: 六个子数组的不同计数分别为 1、1、1、2、2、2，
//       平方和 = 1 + 1 + 1 + 4 + 4 + 4 = 15
//
// 输入: nums = [2,2]
// 输出: 3
// 解释: 三个子数组的不同计数均为 1，平方和 = 3
//
// @解题思路:
// 2913 的 Hard 加强版，n 放宽到 10^5，O(n^2) 暴力会超时，
// 需要 O(n log n) 的贡献法 + 懒标记线段树：
// 1. 枚举右端点 i，设 f(j) = 子数组 nums[j..i] 的不同计数，
//    答案为每个 i 下 s = Σ f(j)^2 的累加取模；
// 2. 平方和无法直接区间维护，利用恒等式 f^2 = 2*T(f) - f
//    （T(f) = 1+2+…+f 为三角形数），转为分别增量维护 ΣT 与 Σf：
//    当一段区间上每个 f 同时加 1 时，ΔΣT = Σf(旧值) + 区间长度，
//    ΔΣf = 区间长度，故 s 的增量 = 2*Σf(旧值) + 区间长度；
// 3. 设 x = nums[i] 上次出现的下标为 j（下标从 1 计，不存在则为 0），
//    则左端点落在 [j+1, i] 的子数组恰好新增一个不同值 x，
//    对这段的 f 整体 +1，其中「查询加一前的区间和 + 区间加一」
//    合并为线段树的一次递归遍历（query_and_add1）；
// 4. 线段树节点维护区间和 sum 与懒标记 todo（待下传的加值），
//    进入子节点前先下传标记，回溯时由左右子节点上传合并。
// 溢出检查：s <= n * n^2 = 10^15，线段树区间和 <= n^2 = 10^10，
// 均在 long long 范围内，每步对 ans 取模。
//
// 复杂度分析：
// - 时间复杂度：O(n log n)，每个元素一次线段树区间查询+更新
// - 空间复杂度：O(n)，线段树开 4n 个节点
//

#include <gtest/gtest.h>

#include <numeric>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
    vector<long long> sum;
    vector<int> todo;

    void do_(int o, int l, int r, int add) {
        sum[o] += (long long)add * (r - l + 1);
        todo[o] += add;
    }

    // o=1  [l,r] 1<=l<=r<=n
    // 把 [L,R] 加一，同时返回加一之前的区间和
    long long query_and_add1(int o, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            long long res = sum[o];
            do_(o, l, r, 1);
            return res;
        }

        int m = (l + r) / 2;
        int add = todo[o];
        if (add != 0) {
            do_(o * 2, l, m, add);
            do_(o * 2 + 1, m + 1, r, add);
            todo[o] = 0;
        }

        long long res = 0;
        if (L <= m) res += query_and_add1(o * 2, l, m, L, R);
        if (m < R) res += query_and_add1(o * 2 + 1, m + 1, r, L, R);
        sum[o] = sum[o * 2] + sum[o * 2 + 1];
        return res;
    }

   public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        sum.resize(n * 4);
        todo.resize(n * 4);

        long long ans = 0, s = 0;
        unordered_map<int, int> last;
        for (int i = 1; i <= n; i++) {
            int x = nums[i - 1];
            int j = last.count(x) ? last[x] : 0;
            s += query_and_add1(1, 1, n, j + 1, i) * 2 + i - j;
            ans = (ans + s) % 1'000'000'007;
            last[x] = i;
        }
        return ans;
    }
};
}  // namespace

TEST(Daily, 2916) {
    // Solution 内部线段树数组用 resize 分配，不清零旧值，
    // 每个用例须新建实例（与 LeetCode 每用例新实例的语义一致）
    {
        // 官方示例 1：六个子数组的不同计数 1、1、1、2、2、2
        Solution s;
        vector<int> nums = {1, 2, 1};
        EXPECT_EQ(s.sumCounts(nums), 15);
    }

    {
        // 官方示例 2：三个子数组的不同计数均为 1
        Solution s;
        vector<int> nums = {2, 2};
        EXPECT_EQ(s.sumCounts(nums), 3);
    }

    {
        // 手算用例：全不同元素 4*1 + 3*4 + 2*9 + 1*16 = 50
        Solution s;
        vector<int> nums = {1, 2, 3, 4};
        EXPECT_EQ(s.sumCounts(nums), 50);
    }

    // 随机小数组与 O(n^2) 暴力对拍
    mt19937 rng(2916);
    for (int t = 0; t < 200; t++) {
        int n = uniform_int_distribution<int>(1, 50)(rng);
        vector<int> nums(n);
        for (auto& x : nums) {
            x = uniform_int_distribution<int>(1, 5)(rng);
        }

        // 暴力：枚举全部子数组，哈希集合去重
        int brute = 0;
        for (int i = 0; i < n; i++) {
            unordered_set<int> st;
            for (int j = i; j < n; j++) {
                st.insert(nums[j]);
                brute += (int)st.size() * (int)st.size();
            }
        }

        Solution s;
        EXPECT_EQ(s.sumCounts(nums), brute);
    }

    {
        // 大规模取模：全不同元素时答案 = Σ (n-len+1)*len^2，n = 10^5
        const long long n = 100000, MOD = 1'000'000'007;
        vector<int> nums(n);
        iota(nums.begin(), nums.end(), 1);

        long long expect = 0;
        for (long long len = 1; len <= n; len++) {
            expect = (expect + (n - len + 1) * len % MOD * len) % MOD;
        }

        Solution s;
        EXPECT_EQ(s.sumCounts(nums), (int)expect);
    }
}
