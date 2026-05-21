//
// Created by hankun on 5/22/26.
//

/**
 * @题目描述
 * 3043. 最长公共前缀的长度
 * 给你两个正整数数组 arr1 和 arr2。
 * 一个正整数的前缀是由一个或多个数字组成的整数，从最左边开始。
 * 例如，123 是 12345 的前缀，而 234 不是。
 * 两个整数 a 和 b 的公共前缀是一个整数 c，使得 c 是 a 和 b 的前缀。
 * 例如，5655359 和 56554 的公共前缀是 565 和 5655，而 1223 和 43456 没有公共前缀。
 *
 * 你需要找到所有数对 (x, y) 之间的最长公共前缀的长度，其中 x 属于 arr1，y 属于 arr2。
 * 返回所有数对中最长公共前缀的长度。如果不存在公共前缀，返回 0。
 *
 * @示例
 * 示例 1：
 * 输入: arr1 = [1,10,100], arr2 = [1000]
 * 输出: 3
 * 解释:
 * 有 3 个数对 (arr1[i], arr2[j])：
 * - (1, 1000) 的最长公共前缀是 1
 * - (10, 1000) 的最长公共前缀是 10
 * - (100, 1000) 的最长公共前缀是 100
 * 最长公共前缀是 100，长度为 3
 *
 * 示例 2：
 * 输入: arr1 = [1,2,3], arr2 = [4,4,4]
 * 输出: 0
 * 解释: 任意数对之间都不存在公共前缀，返回 0
 *
 * @解题思路
 * 方法一：前缀集合法
 * 1. 将 arr1 中每个数字的所有前缀存入 unordered_set
 * 2. 遍历 arr2 中每个数字的所有前缀，检查是否在集合中
 * 3. 维护最大长度
 *
 * 时间复杂度: O(N * M)，其中 N 和 M 是数组长度，M 是数字的最大长度
 * 空间复杂度: O(N * M)
 *
 * 方法二：字典树（推荐）
 * 1. 将 arr1 中所有数字插入字典树
 * 2. 遍历 arr2 中每个数字，在字典树中搜索最长公共前缀
 * 3. 维护最大长度
 *
 * 时间复杂度: O(N * M)
 * 空间复杂度: O(N * M)
 */

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<string> prefixes;
        for (int num : arr1) {
            string s = to_string(num);
            for (int i = 1; i <= static_cast<int>(s.size()); ++i) {
                prefixes.insert(s.substr(0, i));
            }
        }

        int result = 0;
        for (int num : arr2) {
            string s = to_string(num);
            for (int i = static_cast<int>(s.size()); i >= 1; --i) {
                if (prefixes.find(s.substr(0, i)) != prefixes.end()) {
                    result = max(result, i);
                    break;
                }
            }
        }

        return result;
    }
};

TEST(Daily, 3043) {
    Solution s;

    auto arr1_1 = vector<int>{1, 10, 100};
    auto arr2_1 = vector<int>{1000};
    EXPECT_EQ(s.longestCommonPrefix(arr1_1, arr2_1), 3);

    auto arr1_2 = vector<int>{1, 2, 3};
    auto arr2_2 = vector<int>{4, 4, 4};
    EXPECT_EQ(s.longestCommonPrefix(arr1_2, arr2_2), 0);

    auto arr1_3 = vector<int>{123, 12345, 1234};
    auto arr2_3 = vector<int>{123456};
    EXPECT_EQ(s.longestCommonPrefix(arr1_3, arr2_3), 5);

    auto arr1_4 = vector<int>{100};
    auto arr2_4 = vector<int>{1};
    EXPECT_EQ(s.longestCommonPrefix(arr1_4, arr2_4), 1);
}