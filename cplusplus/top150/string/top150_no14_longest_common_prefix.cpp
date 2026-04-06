/**
 * @file top150_no14_longest_common_prefix.cpp
 * @brief LeetCode 14. 最长公共前缀
 *
 * @题目描述
 * 编写一个函数来查找字符串数组中的最长公共前缀。如果不存在公共前缀，返回空字符串 ""。
 *
 * @示例
 * 示例 1：
 * 输入: strs = ["flower","flow","flight"]
 * 输出: "fl"
 *
 * 示例 2：
 * 输入: strs = ["dog","racecar","car"]
 * 输出: ""
 * 解释: 输入不存在公共前缀。
 *
 * @解题思路
 * 1. 纵向扫描法：
 *    - 以第一个字符串为基准
 *    - 逐个字符与其他字符串比较
 *    - 遇到不匹配的字符或某个字符串结束，则返回当前前缀
 *
 * 2. 横向扫描法：
 *    - 先求前两个字符串的公共前缀
 *    - 再用这个结果与第三个字符串求公共前缀
 *    - 依此类推，直到遍历完所有字符串
 *
 * 3. 分治法：
 *    - 将字符串数组分成两部分
 *    - 分别求两部分的公共前缀
 *    - 再求这两个前缀的公共前缀
 *
 * 4. 二分查找法：
 *    - 确定最短字符串的长度
 *    - 二分查找最长公共前缀的长度
 *
 * @复杂度分析
 * - 时间复杂度: O(S)，其中 S 是所有字符串中字符数量的总和
 * - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace std;

TEST(TOP150, No14_LongestCommonPrefix) {
    class Solution {
    public:
        string longest_common_prefix(vector<string>& strs) {
            if (strs.empty()) {
                return "";
            }

            auto pos = 0;
            auto is_end = false;
            while (pos < strs[0].size()) {
                auto t = strs[0].at(pos);
                for (auto i : strs) {
                    if (pos > int(i.size()) - 1) {
                        is_end = true;
                        break;
                    }

                    if (i.at(pos) != t) {
                        is_end = true;
                        break;
                    }
                }

                if (is_end) {
                    break;
                }

                pos++;
            }
            return strs[0].substr(0, pos);
        }
    };

    Solution solution;
    auto input = std::vector<std::string>{"flower", "flow", "flight"};
    auto ret = solution.longest_common_prefix(input);
    EXPECT_EQ(ret, "fl");
}
