//
// Created by 韩堃 on 2026/9/26.
//
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
