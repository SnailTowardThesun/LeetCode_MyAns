//
// Created by 韩堃 on 2026/9/25.
//
// @题目描述:
// LeetCode 1096. 花括号展开 II（Brace Expansion II）
// 在给定表达式中，花括号外的每个字母按顺序连接；花括号内用逗号分隔
// 的选项是「或」关系，展开为所有可能组合。表达式可以嵌套花括号。
// 返回所有可能字符串的列表，按字典序排序，且不含重复。
//
// 规则要点：
// - 并列（花括号外相邻）= 笛卡尔积；
// - 花括号内逗号分隔 = 并集（取其一）。
//
// @示例:
// 示例 1：
// 输入：expression = "{a,b}{c,{d,e}}"
// 输出：["ac","ad","ae","bc","bd","be"]
// 示例 2：
// 输入：expression = "{{a,z},a{b,c},{ab,z}}"
// 输出：["a","ab","ac","z"]
// 解释：去重后按字典序。
//
// @解题思路:
// 栈模拟。维护两个集合：
// - res：当前「逗号分隔」层累积的并集（取其一）；
// - cur：当前正在拼接的「并列」积的集合。
// 用栈保存每层进入 '{' 前的 (res, cur)。
// 遍历字符：
// 1. 字母 c：cur 中每个串末尾追加 c（并列，更新积）；
// 2. ','：把 cur 并入 res（这一组并列结束，开始下一个候选），cur 重置为 {""}；
// 3. '{'：把当前 (res, cur) 压栈，res、cur 都重置，开始解析括号内；
// 4. '}'：先把 cur 并入 res 得到括号内所有候选 sub_arr；弹出外层 (res, cur)，
//    令 cur = 外层 cur × sub_arr（笛卡尔积，因为括号整体作为并列的一项）。
// 遍历结束，把最后的 cur 并入 res，排序后返回。
// 用 unordered_set 自动去重，最终 sort 保证字典序。
//
// 复杂度分析：
// - 时间复杂度：与结果集大小相关，指数级，本题数据规模可接受。
// - 空间复杂度：与结果集大小同阶。

#include <gtest/gtest.h>
#include <algorithm>
#include <stack>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        using SET = unordered_set<string>;
        // 栈元素：(进入当前 '{' 前的并集 res, 并列积 cur)
        stack<pair<SET, SET> > container;
        SET res;
        SET cur{""};

        for (auto ch: expression) {
            if (ch >= 'a' && ch <= 'z') {
                // 并列：cur 中每个串末尾追加该字母
                SET tmp;
                for (auto s: cur) {
                    tmp.insert(s + ch);
                }

                cur = tmp;
            } else if (ch == ',') {
                // 逗号：当前并列组结束，cur 并入 res
                res.insert(cur.begin(), cur.end());
                cur = {""};
            } else if (ch == '{') {
                // 保存上下文，进入括号内层
                container.emplace(std::move(res), std::move(cur));
                res = {};
                cur = {""};
            } else if (ch == '}') {
                // 括号内所有候选 = res ∪ cur
                res.insert(cur.begin(), cur.end());
                auto sub_arr = std::move(res);

                // 恢复外层上下文
                res = container.top().first;
                cur = container.top().second;

                container.pop();

                // 括号整体作为并列的一项：cur = 外层 cur × sub_arr
                SET tmp;
                for (auto i: cur) {
                    for (auto j: sub_arr) {
                        tmp.insert(i + j);
                    }
                }

                cur = tmp;
            }
        }

        // 最后一组 cur 并入 res
        res.insert(cur.begin(), cur.end());

        vector<string> ret(res.begin(), res.end());
        sort(ret.begin(), ret.end());
        return ret;
    }
};


TEST(Daily, 1096) {
    Solution s;
    auto expression = "{a,b}{c,{d,e}}";
    auto ret = s.braceExpansionII(expression);
    EXPECT_EQ(ret.size(), 6);
    EXPECT_EQ(ret, vector<string>({"ac", "ad", "ae", "bc", "bd", "be"}));

    // 示例 2：含去重与字典序
    EXPECT_EQ(s.braceExpansionII("{{a,z},a{b,c},{ab,z}}"),
              vector<string>({"a", "ab", "ac", "z"}));

    // 简单并列
    EXPECT_EQ(s.braceExpansionII("a{b,c}"), vector<string>({"ab", "ac"}));

    // 嵌套花括号
    EXPECT_EQ(s.braceExpansionII("{x{a,b}}"), vector<string>({"xa", "xb"}));
}
