// @题目描述:
// 有效括号字符串仅由 '(' 和 ')' 构成，并满足：空字符串是有效括号串；
// 若 A 是有效括号串，则 (A) 也是；若 A、B 是有效括号串，则 AB 也是。
// 给你一个有效括号字符串 seq，请将其分成两个不相交的有效括号子序列 A 和 B，
// 使 A 和 B 的最大嵌套深度的最大值尽可能小。返回一个长度等于 seq.length() 的
// 答案数组 answer，answer[i] = 0 表示 seq[i] 属于 A，answer[i] = 1 表示属于 B。
//
// @示例:
// 示例 1：
// 输入：seq = "(()())"
// 输出：[0,1,1,1,1,0]
//
// 示例 2：
// 输入：seq = "()(())()"
// 输出：[0,0,0,1,1,0,0,0]
//
// @解题思路:
// 奇偶分组。
// 1. 维护当前嵌套深度 depth。
// 2. 遇到 '('：将其分配给 depth % 2 对应的组，然后 depth++。
// 3. 遇到 ')'：先 depth--，再将其分配给 depth % 2 对应的组。
// 这样同一深度的括号被交替分配到 A、B 两组，两组的最大深度都不超过原深度的一半，
// 从而使两组深度的最大值最小。
//
// 复杂度分析：
// - 时间复杂度：O(n)，单次遍历。
// - 空间复杂度：O(1)，不计返回数组。

#include <gtest/gtest.h>

#include <stack>
using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> ret(seq.size(), 0);

        int depth = 0;
        for (auto i = 0; i < seq.size(); ++i) {
            if (seq.at(i) == '(') {
                ret[i] = depth % 2;
                depth++;
            } else if (seq.at(i) == ')') {
                depth--;
                ret[i] = depth % 2;
            }
        }

        return ret;
    }
};
}  // namespace

TEST(Daily, 1111) {
    Solution s;
    auto seq = "(()())";
    auto ret = s.maxDepthAfterSplit(seq);
    EXPECT_EQ(vector<int>({0, 1, 1, 1, 1, 0}), ret);
}
