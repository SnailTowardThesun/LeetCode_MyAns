//
// Created by 韩堃 on 2026/9/26.
//

// @题目描述:
// 给你一个字符串 path，表示指向某文件或目录的 Unix 风格绝对路径（以 '/' 开头），
// 请将其转换为更加简洁的规范路径。规则：
// - 多个连续 '/' 视为单个 '/'；
// - "." 表示当前目录，忽略；
// - ".." 表示上级目录，向上跳一级（根目录的上级仍是根目录）；
// - 任何其他格式的点（如 "..."）视为文件/目录名。
// 返回的规范路径以单个 '/' 开头，目录间用单个 '/' 分隔，且不以 '/' 结尾（根目录除外）。
//
// @示例:
// 输入："/home/user/Documents/../Pictures"
// 输出："/home/user/Pictures"
//
// 输入："/home//foo/"
// 输出："/home/foo"
//
// @解题思路:
// 切分 token + 栈（vector）模拟目录层级。
// 1. 以 '/' 为分隔符，把路径切成非空 token 列表。
// 2. 逐个处理 token：
//    - ".."：弹出栈顶（栈空则留在根目录，什么都不做）；
//    - "."：跳过；
//    - 其他：入栈。
// 3. 从栈底到栈顶拼成 "/a/b/c"，去掉尾部多余 '/'。
//
// 复杂度分析：
// - 时间复杂度：O(n)，路径字符处理常数次。
// - 空间复杂度：O(n)，token 与栈存储。

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        string ret = "";

        vector<string> container;
        string tmp = "";
        for (auto i: path) {
            if (i == '/') {
                if (tmp != "") {
                    container.emplace_back(tmp);
                }
                tmp = "";
                continue;
            }
            tmp += i;
        }

        if (tmp != "") {
            container.emplace_back(tmp);
        }

        vector<string> simple_container;
        for (auto i: container) {
            if (i == "..") {
                if (!simple_container.empty()) {
                    simple_container.pop_back();
                }
            } else if (i == ".") {
                continue;
            } else {
                simple_container.emplace_back(i);
            }
        }

        ret = "/";
        for (auto i: simple_container) {
            ret += i;
            ret += '/';
        }

        if (ret.size() > 1 && ret.at(ret.size() - 1) == '/') {
            ret.pop_back();
        }

        return ret;
    }
};


TEST(top150, 71) {
    Solution s;
    auto path = "/home/user/Documents/../Pictures";
    auto ret = s.simplifyPath(path);
    EXPECT_EQ("/home/user/Pictures", ret);
}
