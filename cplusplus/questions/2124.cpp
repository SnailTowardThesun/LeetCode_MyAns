// @题目描述:
// 给你一个仅由字符 'a' 和 'b' 组成的字符串 s。如果 s 中每个 'a' 都出现在
// 每个 'b' 之前（即不存在某个 'b' 出现在某个 'a' 前面），返回 true；否则
// 返回 false。
//
// @示例:
// 输入：s = "aaabbb" 输出：true（所有 'a' 都在所有 'b' 之前）
// 输入：s = "abab" 输出：false
// 输入：s = "bbb" 输出：true（没有 'a'，条件自然满足）
//
// @解题思路:
// 定位最后一个 'a'，检查其前缀无 'b'：
// 1. 从右向左找最后一个 'a' 的下标 last_a（不存在则直接返回 true）；
// 2. 再检查 s[0..last_a] 中没有 'b'——'b' 出现在最后一个 'a' 之前即违规。
// 等价的一行判定：s 中不含相邻子串 "ba"。
//
// 复杂度分析：
// - 时间复杂度：O(n)
// - 空间复杂度：O(1)

#include <gtest/gtest.h>

#include <string>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    bool checkString(string s) {
        int last_a = -1;
        for (int i = s.size() - 1; i >= 0; i--) {  // 从右向左找最后一个 'a'
            if (s.at(i) == 'a') {
                last_a = i;
                break;
            }
        }

        for (int i = last_a; i >= 0; i--) {  // 最后一个 'a' 之前不得出现 'b'
            if (s.at(i) == 'b') {
                return false;
            }
        }

        return true;  // last_a == -1（无 'a'）时循环不执行，同样走到这里
    }
};
}  // namespace

TEST(Daily, 2124) {
    Solution s;

    // 官方示例
    EXPECT_TRUE(s.checkString("aaabbb"));
    EXPECT_FALSE(s.checkString("abab"));
    EXPECT_TRUE(s.checkString("bbb"));

    // 最小规模
    EXPECT_TRUE(s.checkString("a"));
    EXPECT_TRUE(s.checkString("b"));
    EXPECT_TRUE(s.checkString("ab"));
    EXPECT_FALSE(s.checkString("ba"));

    // 尾部违规与正常
    EXPECT_FALSE(s.checkString("bbba"));
    EXPECT_TRUE(s.checkString("aabbb"));
}
