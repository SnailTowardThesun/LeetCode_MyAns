//
// Created by hankun on 2026/10/21.
//

// @题目描述:
// 3863. 将字符串排序的最小操作次数（Minimum Operations to Sort a String）— Medium
// 给你一个由小写英文字母组成的字符串 s。
// 一次操作中，你可以选择 s 的任意子字符串（但不能是整个字符串），
// 并将其按非降序字母顺序排序。
// 返回使 s 变为非降序有序的最少操作次数；如果不可能，返回 -1。
//
// @示例:
// 输入：s = "dog" 输出：1
// 解释：对子串 "og" 排序得 "go"，s 变为 "dgo"，已经有序。
// 输入：s = "card" 输出：2
// 解释：先排序 "car" 得 "acrd"，再排序 "rd" 得 "acdr"。
// 输入：s = "gf" 输出：-1
// 解释：长度为 2 时只能选单个字符的子串，排序不产生任何变化，不可能有序。
//
// @解题思路:
// 分类讨论（答案只能是 0、1、2、3 或 -1）：
// 1. 已非降序 → 0。
// 2. 长度为 2 且无序 → -1：真子串只有单个字符，排序是无效操作。
// 3. s[0] 是最小字符，或 s[n-1] 是最大字符 → 1：
//    前者排序后缀 s[1..n-1]，后者排序前缀 s[0..n-2]，首（尾）天然不破坏有序性。
// 4. 最小或最大字符出现在中间位置 s[1..n-2] → 2：
//    第一次操作把最值换到端点，第二次操作排序剩余部分。
// 5. 其余情况（s[0] 是最大且 s[n-1] 是最小）→ 3：
//    先用一次操作同时处理两个最值，再各用一次整理两侧，如 "cba"。
//
// 复杂度分析：
// - 时间复杂度：O(n)，is_sorted、minmax 与线性扫描各遍历一次。
// - 空间复杂度：O(1)。

#include <gtest/gtest.h>

using namespace std;

namespace {
    class Solution {
    public:
        int minOperations(string s) {
            int n = s.size();

            if (ranges::is_sorted(s.begin(), s.end())) {
                return 0;
            }

            if (n == 2) {
                return -1;
            }

            auto [mn, mx] = ranges::minmax(s);
            if (s.at(0) == mn || s.at(n - 1) == mx) {
                return 1;
            }

            for (int i = 1; i < n - 1; i++) {
                if (s.at(i) == mn || s.at(i) == mx) {
                    return 2;
                }
            }

            return 3;
        }
    };
}

TEST(Daily, 3863) {
    Solution s;
    auto ss = "dog";
    auto ret = s.minOperations(ss);
    EXPECT_EQ(ret, 1);   // 官方示例 1：排序 "og" 一次到位
    EXPECT_EQ(s.minOperations("card"), 2);  // 官方示例 2
    EXPECT_EQ(s.minOperations("gf"), -1);   // 官方示例 3
    EXPECT_EQ(s.minOperations("abc"), 0);   // 已有序
    EXPECT_EQ(s.minOperations("bdac"), 2);  // 最值出现在中间
    EXPECT_EQ(s.minOperations("cba"), 3);   // 最大在首、最小在尾
}
