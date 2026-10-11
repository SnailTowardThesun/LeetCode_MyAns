//
// Created by hankun on 2026/10/1.
//

/**
 * @file top150_49.cpp
 * @brief LeetCode 49. 字母异位词分组
 *
 * @题目描述
 * 给你一个字符串数组 strs，将字母异位词组合在一起。
 * 字母异位词是由重新排列源单词的所有字母得到的新单词，
 * 例如 "eat" 的字母异位词有 "ate"、"tea"。
 * 可以按任意顺序返回结果列表。
 *
 * @示例
 * 示例 1：
 * 输入：strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
 * 输出：[["bat"], ["nat", "tan"], ["ate", "eat", "tea"]]
 *
 * 示例 2：
 * 输入：strs = [""]
 * 输出：[[""]]
 *
 * 示例 3：
 * 输入：strs = ["a"]
 * 输出：[["a"]]
 *
 * @解题思路
 * 1. 排序作为哈希键：
 *    - 字母异位词排序后的结果完全相同（如 "eat"、"tea"、"ate" 排序后都是 "aet"）
 *    - 遍历每个字符串，将其排序后的结果作为哈希表的 key
 *    - 原字符串加入该 key 对应的分组列表中
 *    - 最后收集哈希表中所有分组即为答案
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n * k log k)，其中 n 是字符串数量，k 是字符串最大长度
 *    - 空间复杂度: O(n * k)，用于存储哈希表和结果
 */

#include <gtest/gtest.h>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    vector<vector<string> > groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string> > container;
        for (auto str : strs) {
            auto sorted = str;
            sort(sorted.begin(), sorted.end());
            container[sorted].emplace_back(str);
        }

        vector<vector<string> > ret;
        for (auto it : container) {
            ret.emplace_back(it.second);
        }

        return ret;
    }
};
}  // namespace

TEST(top150, 49) {
    Solution s;
    vector<string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    auto ret = s.groupAnagrams(strs);
    EXPECT_EQ(ret.size(), 3);
}
