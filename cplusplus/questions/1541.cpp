//
// Created by hankun on 2026/10/9.
//

/**
 * @file 1541.cpp
 * @brief LeetCode 1541. 平衡括号字符串的最少插入次数
 *
 * @题目描述
 * 给你一个括号字符串 s，它只包含字符 '(' 和 ')'。
 * 一个平衡的括号字符串需满足：每个左括号 '(' 都必须对应两个连续的右括号 "))"。
 * 空字符串也视为平衡的。返回使 s 平衡所需的最少插入次数。
 * 可以在任意位置插入 '(' 或 ')'。
 *
 * @示例
 * 示例 1：
 * 输入：s = "(()))"
 * 输出：1
 * 解释：在第二个 ')' 后插入一个 '(' 即可平衡。
 *
 * 示例 2：
 * 输入：s = "()))"
 * 输出：3
 *
 * 示例 3：
 * 输入：s = "()()"
 * 输出：0
 *
 * @解题思路
 * 1. 一次遍历 + 贪心计数：
 *    - 维护变量 l 表示当前未匹配的 '(' 数量，ret 记录需要插入的次数
 *    - 遇到 '(' 时 l 加一
 *    - 遇到 ')' 时：
 *      a. 若 l > 0，用现有的 '(' 匹配（l 减一）
 *      b. 否则说明缺少 '('，需插入一个（ret 加一）
 *      c. 接着检查下一个字符：若也是 ')' 则成对消耗（i 跳过）
 *      d. 否则这个 ')' 缺少配对，需再插入一个 ')'（ret 加一）
 *    - 遍历结束后，每个未匹配的 '(' 还需要两个 ')'，即 ret += l * 2
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n)，其中 n 是字符串长度
 *    - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int minInsertions(string s) {
        int ret = 0;
        int l = 0;

        for (auto i = 0; i < s.size(); ++i) {
            if (s.at(i) == '(') {
                l++;
                continue;
            }

            if (l > 0) {
                l--;
            } else {
                ret++;
            }

            if (i < s.size() - 1 && s.at(i + 1) == ')') {
                i++;
            } else {
                ret++;
            }
        }

        ret += l * 2;

        return ret;
    }
};
}  // namespace

TEST(Daily, 1541) {
    Solution s;
    auto ss = "()())))()";
    auto ret = s.minInsertions(ss);
    EXPECT_EQ(3, ret);
}
