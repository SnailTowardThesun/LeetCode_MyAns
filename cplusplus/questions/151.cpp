//
// Created by 韩堃 on 2026/4/18.
//

/**
 * @file 151.cpp
 * @brief LeetCode 151. 反转字符串中的单词
 *
 * @题目描述
 * 给你一个字符串 s，请你反转字符串中单词的顺序。
 * 单词是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的单词分隔开。
 * 返回的单词需用单个空格连接，并遵循单词间仅保留单个空格的形式。
 *
 * @示例
 * 示例 1：
 * 输入：s = "the sky is blue"
 * 输出："blue is sky the"
 *
 * 示例 2：
 * 输入：s = "  hello world  "
 * 输出："world hello"
 * 解释：返回的字符串中不能包含前导或尾随的空格
 *
 * 示例 3：
 * 输入：s = "a good   example"
 * 输出："example good a"
 * 解释：返回的字符串中单词间只有一个空格
 *
 * @解题思路
 * 1. 从后往前遍历法：
 *    - 从字符串末尾开始向前遍历
 *    - 跳过空格，找到单词的末尾
 *    - 然后继续向前遍历，找到单词的开头
 *    - 将每个单词添加到结果字符串中
 *
 * 2. 算法步骤：
 *    - 初始化结果字符串 ss
 *    - 从后向前遍历字符串 s
 *    - 跳过空格
 *    - 如果遇到非空格字符，开始收集单词
 *    - 将单词反转后添加到结果中
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)
 *    - 空间复杂度: O(1)，不计输出空间
 */

#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(Daily, 151) {
    class Solution {
    public:
        void reverseWords(string &s) {
            string ss;
            int i = s.length() - 1;
            while (i >= 0) {
                while (i >= 0 && s[i] == ' ') i--;
                if (i < 0) break;
                if (ss.length() != 0)
                    ss.push_back(' ');
                string temp;
                for (; i >= 0 && s[i] != ' '; i--)
                    temp.push_back(s[i]);
                reverse(temp.begin(), temp.end());
                ss.append(temp);
            }
            s = ss;
        }
    };

    Solution s;
    
    // 测试用例 1
    string s1 = "the sky is blue";
    s.reverseWords(s1);
    EXPECT_EQ(s1, "blue is sky the");
    
    // 测试用例 2
    string s2 = "  hello world  ";
    s.reverseWords(s2);
    EXPECT_EQ(s2, "world hello");
    
    // 测试用例 3
    string s3 = "a good   example";
    s.reverseWords(s3);
    EXPECT_EQ(s3, "example good a");
    
    // 测试用例 4
    string s4 = " ";
    s.reverseWords(s4);
    EXPECT_EQ(s4, "");
}
