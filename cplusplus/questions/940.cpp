// @题目描述:
// LeetCode 940. 不同的子序列 II（Distinct Subsequences II）
// 给定一个字符串 s，计算 s 的不同非空子序列的个数。由于答案可能很大，
// 返回对 10^9 + 7 取余的结果。
// 子序列：通过原字符串删除一些（也可以不删）字符且不改变剩余字符相对顺序
// 生成的新字符串。两个子序列不同当且仅当它们在某个位置上的字符不同。
//
// @示例:
// 示例 1：
// 输入：s = "abc"
// 输出：7
// 解释：7 个不同的子序列分别是 "a", "b", "c", "ab", "ac", "bc", "abc"。
// 示例 2：
// 输入：s = "aba"
// 输出：6
// 解释：6 个不同的子序列分别是 "a", "b", "ab", "ba", "aa", "aba"。
// 示例 3：
// 输入：s = "aaa"
// 输出：3
// 解释：3 个不同的子序列分别是 "a", "aa", "aaa"。
//
// @解题思路:
// 计数 DP（按结尾字符去重）。设 dp[i][c] 表示只考虑 s 的前 i 个字符时，
// 以字符 c（'a'~'z'）结尾的不同子序列个数（对 1e9 + 7 取模）。
//
// 状态转移（处理第 i 个字符 ch = s[i-1]）：
// 1. 其余结尾字符的计数不受影响，故 dp[i] 先整体拷贝 dp[i-1]。
// 2. 以 ch 结尾的新计数直接覆盖旧值：
//    dp[i][ch] = sum(dp[i-1]) + 1
//    即把前一状态的每个不同子序列（含空串）末尾追加一个 ch，就得到全部
//    以 ch 结尾的不同子序列；"+1" 对应「空串 + ch」，即子序列 "ch" 本身。
// 3. 去重原理：覆盖式赋值天然消除重复——旧集合中每个以 ch 结尾的子序列
//    去掉末尾 ch 后仍是某个更短的子序列，会在第 2 步被重新扩展出来，
//    因此新的以 ch 结尾集合恰好覆盖旧集合且不含重复。
//
// 答案为 sum(dp[n])（n = s.size()），即所有结尾字符计数之和。
//
// 复杂度分析：
// - 时间复杂度：O(n * 26)，每个位置做一次 O(26) 的求和。
// - 空间复杂度：O(n * 26)；可只保留上一行，用滚动数组优化到 O(26)。

#include <gtest/gtest.h>

#include <numeric>
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        // dp[i][c]: 前 i 个字符中，以字符 c 结尾的不同子序列个数（模 MOD）
        vector<vector<int>> dp(s.size() + 1, vector<int>(26, 0));
        for (int i = 1; i <= s.size(); ++i) {
            dp[i] = dp[i - 1];
            // 以 s[i-1] 结尾的子序列 = 上一状态全部子序列（含空串）各追加该字符
            dp[i][s[i - 1] - 'a'] = (accumulate(dp[i - 1].begin(), dp[i - 1].end(), 0LL) + 1) % MOD;
        }
        return accumulate(dp[s.size()].begin(), dp[s.size()].end(), 0LL) % MOD;
    }
};

TEST(Daily, 940) {
    Solution s;

    // 基本用例：无重复字符
    EXPECT_EQ(s.distinctSubseqII("abc"), 7);  // a, b, c, ab, ac, bc, abc

    // 边界用例：含重复字符（考察去重）
    EXPECT_EQ(s.distinctSubseqII("aba"), 6);  // a, b, ab, ba, aa, aba
    EXPECT_EQ(s.distinctSubseqII("aaa"), 3);  // a, aa, aaa

    // 边界用例：单字符
    EXPECT_EQ(s.distinctSubseqII("a"), 1);
}
