//
// Created by 韩堃 on 2026/9/26.
//

// @题目描述:
// 给定两个长度相同的字符串 s 和 t，判断它们是否同构。
// 同构指 s 中的字符可以按某种一一对应关系替换得到 t，且不同字符不能映射到
// 同一个字符，一个字符也不能映射到多个字符（双向唯一）。
//
// @示例:
// 输入：s = "egg", t = "add"
// 输出：true（e->a, g->d）
//
// 输入：s = "foo", t = "bar"
// 输出：false
//
// @解题思路:
// 双向映射表。
// 1. container_s 记录 s->t 的映射，container_t 记录 t->s 的映射。
// 2. 逐对处理字符：首次出现则建立映射；之后核对已有映射是否与当前对应一致。
// 3. 任一方向不一致即返回 false。
// 必须双向检查，单向表无法发现「两个 s 字符映射到同一个 t 字符」。
//
// 复杂度分析：
// - 时间复杂度：O(n)。
// - 空间复杂度：O(k)，k 为字符种类数。

#include <gtest/gtest.h>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> container_s;
        unordered_map<char, char> container_t;
        for (auto i = 0; i < s.size(); i++) {

            if (container_s.count(s.at(i)) < 1) {
                container_s[s.at(i)] = t.at(i);
            }
            if (container_t.count(t.at(i)) < 1) {
                container_t[t.at(i)] = s.at(i);
            }
            if (container_s[s.at(i)] != t.at(i)) {
                return false;
            }
            if (container_t[t.at(i)] != s.at(i)) {
                return false;
            }
        }

        return true;
    }
};

TEST(top150, 205) {
    Solution s;
    // 同构：e->t, g->d 双向一一对应
    EXPECT_TRUE(s.isIsomorphic("egg", "add"));
    // 一对多冲突：a->a 且 c->a，不同构（原测试期望 true 是错误的）
    EXPECT_FALSE(s.isIsomorphic("badc", "baba"));
    // 映射冲突：o->a 出现两种原字符
    EXPECT_FALSE(s.isIsomorphic("foo", "bar"));
    // 经典同构示例
    EXPECT_TRUE(s.isIsomorphic("paper", "title"));
}
