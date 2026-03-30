//
// Created by 韩堃 on 2026/3/30.
//

/*
 * 题目：2840. 检查是否存在有效变换来得到目标字符串
 * 描述：给你两个字符串 s1 和 s2 ，两个字符串长度都为 n ，且只包含小写英文字母。
 *      你可以对两个字符串中的任意一个执行以下操作任意次：
 *      选择两个下标 i 和 j ，满足 i < j 且 j - i 是偶数，然后交换这个字符串中两个下标对应的字符。
 *      如果你可以让字符串 s1 和 s2 相等，那么返回 true ，否则返回 false 。
 *
 * 思路分析：
 * 1. 观察允许的操作：只能交换下标奇偶性相同的位置上的字符（因为 j - i 是偶数意味着 i 和 j 同奇偶）
 * 2. 因此，字符串中处于偶数位置的字符只能与其他偶数位置的字符交换
 * 3. 同理，奇数位置的字符只能与其他奇数位置的字符交换
 * 4. 结论：两个字符串中，偶数位置上的字符集合必须相同，奇数位置上的字符集合也必须相同
 *
 * 实现方式对比：
 * 1. 排序法（原始实现）：
 *    - 时间复杂度：O(n log n)，需要对字符数组进行排序
 *    - 空间复杂度：O(n)，需要额外的向量来存储字符
 * 2. 计数法（优化实现）：
 *    - 时间复杂度：O(n)，只需一次遍历
 *    - 空间复杂度：O(1)，使用固定大小的数组（26个字母）
 */

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
