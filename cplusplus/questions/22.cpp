//
// Created by hankun on 2026/10/2.
//

/**
 * @file 22.cpp
 * @brief LeetCode 22. 括号生成
 *
 * @题目描述
 * 数字 n 代表生成括号的对数，请你设计一个函数，
 * 用于能够生成所有可能的并且有效的括号组合。
 *
 * @示例
 * 示例 1：
 * 输入：n = 3
 * 输出：["((()))","(()())","(())()","()(())","()()()"]
 *
 * 示例 2：
 * 输入：n = 1
 * 输出：["()"]
 *
 * @解题思路
 * 1. DFS 回溯 + 剪枝：
 *    - 维护当前路径 path、已用左括号数 left、已用右括号数 right
 *    - 剪枝规则：
 *      a. left 超过 n 时不允许再加 '('（左括号用尽）
 *      b. right 大于 left 时不允许再加 ')'（右括号不能先于左括号出现）
 *    - 每层递归尝试两种选择：
 *      a. 加 '('：left 加一
 *      b. 加 ')'：right 加一
 *    - 当 path 长度达到 2n 时，说明左右括号各用完 n 个且全程合法，
 *      收集当前组合
 *    - 剪枝保证了生成的每个组合都天然有效，无需事后校验
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(4^n / sqrt(n))，合法组合数为卡特兰数
 *    - 空间复杂度: O(n)，递归栈深度与 path 长度
 */

#include <gtest/gtest.h>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    void dfs(string path, vector<string>& container, int n, int left, int right) {
        if (left > n) {
            return;
        }
        if (right > left) {
            return;
        }

        if (path.length() == n * 2) {
            container.push_back(path);
            return;
        }

        dfs(path + "(", container, n, left + 1, right);
        dfs(path + ")", container, n, left, right + 1);
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        dfs("", ret, n, 0, 0);
        // auto valid = [](string str) {
        //     stack<string> st;
        //     for (int i = 0; i < str.length(); i++) {
        //         if (str[i] == '(') {
        //             st.push(str.substr(0, i));
        //         } else if (str[i] == ')') {
        //             if (st.empty()) {
        //                 return false;
        //             }
        //             st.pop();
        //         }
        //     }

        //     return st.empty();
        // };

        // vector<string> ans;
        // for (int i = 0; i < container.size(); i++) {
        //     if (valid(container[i])) {
        //         ans.push_back(container[i]);
        //     }
        // }
        return ret;
    }
};
}  // namespace

TEST(Daily, 22) {
    Solution s;
    auto ret = s.generateParenthesis(3);
    EXPECT_EQ(ret.size(), 5);
    for (int i = 0; i < ret.size(); i++) {
        cout << ret[i] << endl;
    }
}
