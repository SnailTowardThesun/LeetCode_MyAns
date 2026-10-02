// @题目描述:
// 给你两个字符串 s1 和 s2，两个字符串长度都为 n，且只包含小写英文字母。
// 你可以对两个字符串中的任意一个执行以下操作任意次：
// 选择两个下标 i 和 j，满足 i < j 且 j - i 是偶数，然后交换这个字符串中两个下标对应的字符。
// 如果你可以让字符串 s1 和 s2 相等，那么返回 true，否则返回 false。
//
// @示例:
// 示例 1：
// 输入：s1 = "abcdba", s2 = "cabdab"
// 输出：true
// 解释：可以对 s1 执行以下操作使两字符串相等：
//   - 交换下标 0 和 2（差为 2），得到 "cbadba"
//   - 交换下标 1 和 3（差为 2），得到 "cdabba"
//   - ... 最终得到 "cabdab"
//
// 示例 2：
// 输入：s1 = "abe", s2 = "bea"
// 输出：false
//
// @解题思路:
// 关键观察：j - i 为偶数 ⟺ i 和 j 奇偶性相同。
// 因此，偶数下标的字符只能在偶数下标间重排，奇数下标同理。
// 结论：s1 和 s2 在偶数位置上的字符多重集必须相同，奇数位置上也必须相同。
//
// 实现采用计数法（优化版）：
// 1. 用两个长度 26 的数组 even_counts、odd_counts 分别统计奇偶位置的字符频率。
// 2. 一次遍历：s1 对应位置计数 +1，s2 对应位置计数 -1。
// 3. 若最终所有计数均为 0，说明奇偶位置字符多重集相同，返回 true；否则 false。
//
// 复杂度分析：
// - 时间复杂度：O(n)，单次遍历。
// - 空间复杂度：O(1)，仅使用固定大小的计数数组。

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>
using namespace std;

// 方法一：排序法（原始实现）
/*
class Solution {
public:
    bool helper(vector<char> s1, vector<char> s2) {
        std::sort(s1.begin(), s1.end());
        std::sort(s2.begin(), s2.end());
        if (s1.size() != s2.size()) {
            return false;
        }

        std::string tmp1(s1.begin(), s1.end());
        std::string tmp2(s2.begin(), s2.end());
        if (tmp1 != tmp2) {
            return false;
        }

        return true;
    }

    bool checkStrings(string s1, string s2) {
        vector<char> s1_1, s1_2;
        vector<char> s2_1, s2_2;
        for (auto i = 0; i < s1.length(); i++) {
            if (i % 2 == 0) {
                s1_2.push_back(s1[i]);
                s2_2.push_back(s2[i]);
            } else {
                s1_1.push_back(s1[i]);
                s2_1.push_back(s2[i]);
            }
        }

        if (!helper(s1_1, s2_1)) {
            return false;
        }

        if (!helper(s1_2, s2_2)) {
            return false;
        }

        return true;
    }
};
*/

// 方法二：计数法（优化实现）
class Solution {
   public:
    bool checkStrings(string s1, string s2) {
        vector<int> even_counts(26, 0);  // 偶数位置字符计数
        vector<int> odd_counts(26, 0);   // 奇数位置字符计数

        // 遍历两个字符串，统计偶数和奇数位置的字符频率
        for (int i = 0; i < s1.length(); i++) {
            if (i % 2 == 0) {
                // 偶数位置：s1的字符计数加1，s2的字符计数减1
                even_counts[s1[i] - 'a']++;
                even_counts[s2[i] - 'a']--;
            } else {
                // 奇数位置：s1的字符计数加1，s2的字符计数减1
                odd_counts[s1[i] - 'a']++;
                odd_counts[s2[i] - 'a']--;
            }
        }

        // 检查所有字符的计数是否为0
        // 如果为0，说明两个字符串在对应奇偶位置上的字符集合相同
        for (int i = 0; i < 26; i++) {
            if (even_counts[i] != 0 || odd_counts[i] != 0) {
                return false;
            }
        }

        return true;
    }
};

TEST(Daily, 2840) {
    Solution s;
    string s1 = "abcdba";
    string s2 = "cabdab";
    auto ret = s.checkStrings(s1, s2);
    EXPECT_TRUE(ret);
}
